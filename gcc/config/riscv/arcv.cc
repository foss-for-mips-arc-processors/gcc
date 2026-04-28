/* Subroutines used for code generation for Synopsys ARC-V processors.
   Copyright (C) 2025 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#define IN_TARGET_CODE 1

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "target.h"
#include "rtl.h"
#include "tree.h"
#include "memmodel.h"
#include "tm.h"
#include "optabs.h"
#include "regs.h"
#include "emit-rtl.h"
#include "recog.h"
#include "diagnostic-core.h"
#include "stor-layout.h"
#include "alias.h"
#include "fold-const.h"
#include "output.h"
#include "insn-attr.h"
#include "flags.h"
#include "explow.h"
#include "calls.h"
#include "varasm.h"
#include "expr.h"
#include "tm_p.h"
#include "df.h"
#include "reload.h"
#include "sched-int.h"
#include "tm-constrs.h"

/* Scheduler state tracking for dual-pipe ARCV architectures.  */

struct arcv_sched_state {
  /* True if the ALU pipe has been scheduled for the current cycle.
     The ALU pipe handles arithmetic, logical, and other computational
     instructions.  */
  int alu_pipe_scheduled_p;

  /* True if pipe B has been scheduled for the current cycle.
     Pipe B is the second execution pipe, typically used for memory
     operations (loads/stores) but can also handle other instructions.  */
  int pipeB_scheduled_p;

  /* The last instruction that was scheduled.  Used to detect fusion
     opportunities by looking ahead at the next instruction to be
     scheduled.  */
  rtx_insn *last_scheduled_insn;

  /* Cached value of how many more instructions can be issued in the
     current cycle.  Updated as instructions are scheduled and pipes
     become occupied.  */
  short cached_can_issue_more;
};

static struct arcv_sched_state sched_state;

/* Return the next possible fusible insn.  */

static rtx_insn *
arcv_next_fusible_insn (rtx_insn *insn)
{
  while (insn)
    {
      insn = NEXT_INSN (insn);

      if (insn == 0)
	break;

      if (DEBUG_INSN_P (insn)
	  || NOTE_P (insn))
	continue;

      if (NOTE_INSN_BASIC_BLOCK_P (insn))
	return NULL;

      if (GET_CODE (insn) == CODE_LABEL
	  || GET_CODE (insn) == BARRIER
	  || GET_CODE (PATTERN (insn)) == USE)
	continue;

      if (JUMP_TABLE_DATA_P (insn))
	return NULL;

      break;
    }

  return insn;
}

/* Return TRUE if the target microarchitecture supports macro-op
   fusion for two memory operations of mode MODE (the direction
   of transfer is determined by the IS_LOAD parameter).  */

static bool
arcv_pair_fusion_mode_allowed_p (machine_mode mode, bool is_load)
{
  if (!TARGET_ARCV_RHX100)
    return true;

  return ((is_load && (mode == SImode
		     || mode == HImode
		     || mode == QImode))
	 || (!is_load && mode == SImode));
}

/* Return TRUE if two addresses can be fused.  */

static bool
arcv_fused_addr_p (rtx addr0, rtx addr1, bool is_load)
{
  rtx base0, base1, tmp;
  HOST_WIDE_INT off0 = 0, off1 = 0;

  if (GET_CODE (addr0) == SIGN_EXTEND || GET_CODE (addr0) == ZERO_EXTEND)
    addr0 = XEXP (addr0, 0);

  if (GET_CODE (addr1) == SIGN_EXTEND || GET_CODE (addr1) == ZERO_EXTEND)
    addr1 = XEXP (addr1, 0);

  if (!MEM_P (addr0) || !MEM_P (addr1))
    return false;

  /* Require the accesses to have the same mode.  */
  if (GET_MODE (addr0) != GET_MODE (addr1))
    return false;

  /* Check if the mode is allowed.  */
  if (!arcv_pair_fusion_mode_allowed_p (GET_MODE (addr0), is_load))
    return false;

  rtx reg0 = XEXP (addr0, 0);
  rtx reg1 = XEXP (addr1, 0);

  if (GET_CODE (reg0) == PLUS)
    {
      base0 = XEXP (reg0, 0);
      tmp = XEXP (reg0, 1);
      if (!CONST_INT_P (tmp))
	return false;
      off0 = INTVAL (tmp);
    }
  else if (REG_P (reg0))
    base0 = reg0;
  else
    return false;

  if (GET_CODE (reg1) == PLUS)
    {
      base1 = XEXP (reg1, 0);
      tmp = XEXP (reg1, 1);
      if (!CONST_INT_P (tmp))
	return false;
      off1 = INTVAL (tmp);
    }
  else if (REG_P (reg1))
    base1 = reg1;
  else
    return false;

  /* Check if we have the same base.  */
  gcc_assert (REG_P (base0) && REG_P (base1));
  if (REGNO (base0) != REGNO (base1))
    return false;

  /* Fuse adjacent aligned addresses.  */
  if ((off0 % GET_MODE_SIZE (GET_MODE (addr0)).to_constant () == 0)
      && (abs (off1 - off0) == GET_MODE_SIZE (GET_MODE (addr0)).to_constant ()))
    return true;

  return false;
}

/* Helper function to check if instruction type is arithmetic-like.  */

static bool
arcv_arith_type_insn_p (rtx_insn *insn)
{
  enum attr_type type = get_attr_type (insn);

  return (type == TYPE_ARITH
	 || type == TYPE_LOGICAL
	 || type == TYPE_SHIFT
	 || type == TYPE_SLT
	 || type == TYPE_BITMANIP
	 || type == TYPE_MIN
	 || type == TYPE_MAX
	 || type == TYPE_MINU
	 || type == TYPE_MAXU
	 || type == TYPE_CLZ
	 || type == TYPE_CTZ);
}

/* Helper to check if curr's source operand is valid for fusion.  */

static bool
arcv_arith_src_p (rtx curr_set)
{
  rtx src = SET_SRC (curr_set);

  /* Immediate operand or register operand.  */
  return CONST_INT_P (src) || REG_P (XEXP (src, 0));
}

/* Helper to check if curr operation is compatible with load's destination.  */

static bool
arcv_load_arith_pair_p (rtx prev_set, rtx curr_set)
{
  rtx load_addr = XEXP (SET_SRC (prev_set), 0);
  rtx load_dest = SET_DEST (prev_set);
  rtx arith_src = XEXP (SET_SRC (curr_set), 0);
  rtx arith_dest = SET_DEST (curr_set);

  /* Address register must be a register.  */
  if (!REG_P (load_addr))
    return false;

  /* Address register must match first source operand of arithmetic op.  */
  if (REGNO (load_addr) != REGNO (arith_src))
    return false;

  /* Address register must not be the load destination (no clobber).  */
  if (REGNO (load_addr) == REGNO (load_dest))
    return false;

  /* Load and arithmetic destinations must be different.  */
  if (REGNO (load_dest) == REGNO (arith_dest))
    return false;

  /* Check operand constraints for different arithmetic formats.  */
  rtx src = SET_SRC (curr_set);

  /* Unary operation: (set (reg:X rd1) (not (reg:X rs1))).  */
  if (GET_RTX_LENGTH (GET_CODE (src)) == 1)
    return true;

  /* Immediate operation: (set (reg:X rd2) (op (reg:X rs1) (const_int))).  */
  if (CONST_INT_P (XEXP (src, 1)))
    return true;

  /* Binary register operation: ensure load dest != second source register.  */
  if (REGNO (load_dest) != REGNO (XEXP (src, 1)))
    return true;

  return false;
}

/* Helper to check if curr operation is compatible with store's address.  */

static bool
arcv_store_arith_pair_p (rtx prev_set, rtx curr_set)
{
  rtx store_addr = XEXP (SET_DEST (prev_set), 0);
  rtx arith_src = XEXP (SET_SRC (curr_set), 0);

  /* Address register must be a register.  */
  if (!REG_P (store_addr))
    return false;

  /* Address register must match first source operand of arithmetic op.  */
  if (REGNO (store_addr) != REGNO (arith_src))
    return false;

  /* Check operand constraints for different arithmetic formats.  */
  rtx src = SET_SRC (curr_set);

  /* Unary operation.  */
  if (GET_RTX_LENGTH (GET_CODE (src)) == 1)
    return true;

  /* Immediate operation.  */
  if (CONST_INT_P (XEXP (src, 1)))
    return true;

  /* Binary register operation: store addr == second source is OK.  */
  if (REGNO (store_addr) == REGNO (XEXP (src, 1)))
    return true;

  return false;
}

/* Return true if PREV and CURR constitute an ordered load/store + op/opimm
   pair, for the purposes of ARCV-specific macro-op fusion.  */
static bool
arcv_memop_arith_pair_p (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);

  gcc_assert (prev_set);
  gcc_assert (curr_set);

  /* Check if curr is an arithmetic-type instruction.  */
  if (!arcv_arith_type_insn_p (curr))
    return false;

  /* Check if curr has valid source operands.  */
  if (!arcv_arith_src_p (curr_set))
    return false;

  /* Check for load + arithmetic fusion.  */
  if (get_attr_type (prev) == TYPE_LOAD)
    return arcv_load_arith_pair_p (prev_set, curr_set);

  /* Check for store + arithmetic fusion.  */
  if (get_attr_type (prev) == TYPE_STORE)
    return arcv_store_arith_pair_p (prev_set, curr_set);

  return false;
}


/* Return true if PREV and CURR constitute an ordered load/store + lui pair, for
   the purposes of ARCV-specific macro-op fusion.  */

static bool
arcv_memop_lui_pair_p (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);

  gcc_assert (prev_set);
  gcc_assert (curr_set);

  /* Check if curr is a LUI instruction:
     - LUI via HIGH: (set (reg:X rd) (high (const_int)))
     - LUI via immediate: (set (reg:X rd) (const_int UPPER_IMM_20))  */
  bool is_lui = (REG_P (curr)
		&& ((get_attr_type (curr) == TYPE_MOVE
		&& GET_CODE (SET_SRC (curr_set)) == HIGH)
		|| (CONST_INT_P (SET_SRC (curr_set))
		&& LUI_OPERAND (INTVAL (SET_SRC (curr_set))))));

  if (!is_lui)
    return false;

  /* Check for load + LUI fusion:
     Load and LUI destinations must be different to avoid hazard.  */
  if (get_attr_type (prev) == TYPE_LOAD)
    return REGNO (SET_DEST (prev_set)) != REGNO (SET_DEST (curr_set));

  /* Check for store + LUI fusion (always allowed).  */
  if (get_attr_type (prev) == TYPE_STORE)
    return true;

  return false;
}


/* Return true if PREV and CURR should be kept together during scheduling.  */

bool
arcv_macro_fusion_pair_p (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);

  /* Fuse multiply-add pair:
     prev: (set rd_mult (mult rs1 rs2))
     curr: (set rd_add (plus rd_mult rs3))  */
  if (prev_set && curr_set
      && GET_CODE (SET_SRC (prev_set)) == MULT
      && GET_CODE (SET_SRC (curr_set)) == PLUS)
    {
      rtx curr_plus = SET_SRC (curr_set);
      rtx mult_dest = SET_DEST (prev_set);
      unsigned int mult_dest_regno = REGNO (mult_dest);

      /* Check if multiply result is used in either operand of the addition.  */
      if (REG_P (XEXP (curr_plus, 0))
	 && REGNO (XEXP (curr_plus, 0)) == mult_dest_regno)
       {
	 if (dump_file)
	   fprintf (dump_file, "ARCV_FUSE_MULT_ADD (op0)\n");
	 return true;
       }

      if (REG_P (XEXP (curr_plus, 1))
	 && REGNO (XEXP (curr_plus, 1)) == mult_dest_regno)
       {
	 if (dump_file)
	   fprintf (dump_file, "ARCV_FUSE_MULT_ADD (op1)\n");
	 return true;
       }
    }

  /* Fuse logical shift left with logical shift right (bit-extract pattern):
     prev: (set rd (ashift rs imm1))
     curr: (set rd (lshiftrt rd imm2))  */
  if (prev_set && curr_set
      && GET_CODE (SET_SRC (prev_set)) == ASHIFT
      && GET_CODE (SET_SRC (curr_set)) == LSHIFTRT
      && REGNO (SET_DEST (prev_set)) == REGNO (SET_DEST (curr_set))
      && REGNO (SET_DEST (prev_set)) == REGNO (XEXP (SET_SRC (curr_set), 0)))
    {
      if (dump_file)
	fprintf (dump_file, "ARCV_FUSE_SHIFT_BITEXTRACT\n");
      return true;
    }

  /* Fuse load-immediate with a dependent conditional branch:
     prev: (set rd imm)
     curr: (if_then_else (cond rd ...) ...)  */
  if (get_attr_type (prev) == TYPE_MOVE
      && get_attr_move_type (prev) == MOVE_TYPE_CONST
      && any_condjump_p (curr))
    {
      if (!curr_set)
       return false;

      rtx comp = XEXP (SET_SRC (curr_set), 0);
      rtx prev_dest = SET_DEST (prev_set);

      if ((REG_P (XEXP (comp, 0)) && XEXP (comp, 0) == prev_dest)
	  || (REG_P (XEXP (comp, 1)) && XEXP (comp, 1) == prev_dest))
	{
	  if (dump_file)
	    fprintf (dump_file, "ARCV_FUSE_LI_BRANCH\n");
	  return true;
	}
      return false;
    }

  /* Do not fuse loads/stores before sched2.  */
  if (!reload_completed || sched_fusion)
    return false;

  /* prev and curr are simple SET insns i.e. no flag setting or branching.  */
  bool simple_sets_p = prev_set && curr_set && !any_condjump_p (curr);

  /* Don't handle anything with a jump past this point.  */
  if (!simple_sets_p)
    return false;

  /* Fuse adjacent loads.  */
  if (get_attr_type (prev) == TYPE_LOAD
      && get_attr_type (curr) == TYPE_LOAD)
    {
      if (arcv_fused_addr_p (SET_SRC (prev_set), SET_SRC (curr_set), true))
	{
	  if (dump_file)
	    fprintf (dump_file, "ARCV_FUSE_ADJACENT_LOAD\n");
	  return true;
	}
    }

  /* Fuse adjacent stores.  */
  if (get_attr_type (prev) == TYPE_STORE
      && get_attr_type (curr) == TYPE_STORE)
    {
      if (arcv_fused_addr_p (SET_DEST (prev_set), SET_DEST (curr_set), false))
	{
	  if (dump_file)
	    fprintf (dump_file, "ARCV_FUSE_ADJACENT_STORE\n");
	  return true;
	}
    }

  /* Look ahead 1 insn to prioritize adjacent load/store pairs.
     If curr and next form a better fusion opportunity, defer this fusion.  */
  rtx_insn *next = arcv_next_fusible_insn (curr);
  if (next)
    {
      rtx next_set = single_set (next);

      /* Defer if next instruction forms an adjacent load pair with curr.  */
      if (next_set
	 && get_attr_type (curr) == TYPE_LOAD
	 && get_attr_type (next) == TYPE_LOAD
	 && arcv_fused_addr_p (SET_SRC (curr_set), SET_SRC (next_set), true))
	return false;

      /* Defer if next instruction forms an adjacent store pair with curr.  */
      if (next_set
	 && get_attr_type (curr) == TYPE_STORE
	 && get_attr_type (next) == TYPE_STORE
	 && arcv_fused_addr_p (SET_DEST (curr_set), SET_DEST (next_set), false))
	return false;
    }

  /* Fuse a pre- or post-update memory operation:
     Examples: load+add, add+load, store+add, add+store.  */
  if (arcv_memop_arith_pair_p (prev, curr))
    {
      if (dump_file)
	fprintf (dump_file, "ARCV_FUSE_MEMOP_ARITH (prev, curr)\n");
      return true;
    }
  if (arcv_memop_arith_pair_p (curr, prev))
    {
      if (dump_file)
	fprintf (dump_file, "ARCV_FUSE_MEMOP_ARITH (curr, prev)\n");
      return true;
    }

  /* Fuse a memory operation preceded or followed by a LUI:
     Examples: load+lui, lui+load, store+lui, lui+store.  */
  if (arcv_memop_lui_pair_p (prev, curr))
    {
      if (dump_file)
	fprintf (dump_file, "ARCV_FUSE_MEMOP_LUI (prev, curr)\n");
      return true;
    }
  if (arcv_memop_lui_pair_p (curr, prev))
    {
      if (dump_file)
	fprintf (dump_file, "ARCV_FUSE_MEMOP_LUI (curr, prev)\n");
      return true;
    }

  /* Fuse load-immediate with a store of the destination register:
     prev: (set rd imm)
     curr: (set (mem ...) rd)  */
  if (get_attr_type (prev) == TYPE_MOVE
      && get_attr_move_type (prev) == MOVE_TYPE_CONST
      && get_attr_type (curr) == TYPE_STORE)
    {
      rtx store_src = SET_SRC (curr_set);
      rtx load_dest = SET_DEST (prev_set);

      if (REG_P (store_src) && store_src == load_dest)
       {
	 if (dump_file)
	   fprintf (dump_file, "ARCV_FUSE_LI_STORE\n");
	 return true;
       }

      if (SUBREG_P (store_src) && SUBREG_REG (store_src) == load_dest)
       {
	 if (dump_file)
	   fprintf (dump_file, "ARCV_FUSE_LI_STORE (subreg)\n");
	 return true;
       }
    }

  return false;
}

/* Initialize ARCV scheduler state at the beginning of scheduling.  */

void
arcv_sched_init (void)
{
  sched_state.last_scheduled_insn = 0;
}

/* Try to reorder ready queue to promote ARCV fusion opportunities.
   Returns the number of instructions that can be issued this cycle.  */

int
arcv_sched_reorder2 (rtx_insn **ready, int *n_readyp)
{
  if (sched_fusion)
    return sched_state.cached_can_issue_more;

  if (!sched_state.cached_can_issue_more)
    return 0;

  /* Fuse double load/store instances missed by sched_fusion.  */
  if (!sched_state.pipeB_scheduled_p && sched_state.last_scheduled_insn
      && ready && *n_readyp > 0
      && !SCHED_GROUP_P (sched_state.last_scheduled_insn)
      && (get_attr_type (sched_state.last_scheduled_insn) == TYPE_LOAD
	  || get_attr_type (sched_state.last_scheduled_insn) == TYPE_STORE))
    {
      for (int i = 1; i <= *n_readyp; i++)
	{
	  rtx_insn* next_insn = arcv_next_fusible_insn (ready[*n_readyp - i]);
	  /* Try to fuse the last_scheduled_insn with.  */
	  /* Fuse only with nondebug insn.  */
	  if (NONDEBUG_INSN_P (ready[*n_readyp - i])
	      /* Which have not been already fused.  */
	      && !SCHED_GROUP_P (ready[*n_readyp - i])
	      && (!next_insn || !SCHED_GROUP_P (next_insn))
	      && arcv_macro_fusion_pair_p (sched_state.last_scheduled_insn,
					   ready[*n_readyp - i]))
	    {
	      std::swap (ready[*n_readyp - 1], ready[*n_readyp - i]);
	      SCHED_GROUP_P (ready[*n_readyp - 1]) = 1;
	      sched_state.pipeB_scheduled_p = 1;
	      return sched_state.cached_can_issue_more;
	    }
	}
      sched_state.pipeB_scheduled_p = 1;
    }

  /* Try to fuse a non-memory last_scheduled_insn.  */
  if ((!sched_state.alu_pipe_scheduled_p || !sched_state.pipeB_scheduled_p)
      && sched_state.last_scheduled_insn && ready && *n_readyp > 0
      && !SCHED_GROUP_P (sched_state.last_scheduled_insn)
      && (get_attr_type (sched_state.last_scheduled_insn) != TYPE_LOAD
	  && get_attr_type (sched_state.last_scheduled_insn) != TYPE_STORE))
    {
      for (int i = 1; i <= *n_readyp; i++)
	{
	  rtx_insn* next_insn = arcv_next_fusible_insn (ready[*n_readyp - i]);
	  if (NONDEBUG_INSN_P (ready[*n_readyp - i])
	      && !SCHED_GROUP_P (ready[*n_readyp - i])
	      && active_insn_p (ready[*n_readyp - i])
	      && (!next_insn || !SCHED_GROUP_P (next_insn))
	      && arcv_macro_fusion_pair_p (sched_state.last_scheduled_insn,
					   ready[*n_readyp - i]))
	    {
	      if (GET_CODE (PATTERN (ready[*n_readyp - i])) == USE)
		continue;

	      if (get_attr_type (ready[*n_readyp - i]) == TYPE_LOAD
		  || get_attr_type (ready[*n_readyp - i]) == TYPE_STORE)
	      {
		if (sched_state.pipeB_scheduled_p)
		  continue;
		else
		  sched_state.pipeB_scheduled_p = 1;
	      }
	      else if (!sched_state.alu_pipe_scheduled_p)
		sched_state.alu_pipe_scheduled_p = 1;
	      else
		sched_state.pipeB_scheduled_p = 1;

	      std::swap (ready[*n_readyp - 1], ready[*n_readyp - i]);
	      SCHED_GROUP_P (ready[*n_readyp - 1]) = 1;
	      return sched_state.cached_can_issue_more;
	    }
	}
      sched_state.alu_pipe_scheduled_p = 1;
    }

  /* When pipe B is scheduled, we can have no more memops this cycle.  */
  if (sched_state.pipeB_scheduled_p && *n_readyp > 0
      && NONDEBUG_INSN_P (ready[*n_readyp - 1])
      && recog_memoized (ready[*n_readyp - 1]) >= 0
      && !SCHED_GROUP_P (ready[*n_readyp - 1])
      && (get_attr_type (ready[*n_readyp - 1]) == TYPE_LOAD
	  || get_attr_type (ready[*n_readyp - 1]) == TYPE_STORE))
  {
    if (sched_state.alu_pipe_scheduled_p)
      return 0;

    for (int i = 2; i <= *n_readyp; i++)
      {
	rtx_insn* next_insn = arcv_next_fusible_insn (ready[*n_readyp - i]);
	if ((NONDEBUG_INSN_P (ready[*n_readyp - i])
	     && recog_memoized (ready[*n_readyp - i]) >= 0
	     && get_attr_type (ready[*n_readyp - i]) != TYPE_LOAD
	     && get_attr_type (ready[*n_readyp - i]) != TYPE_STORE
	     && !SCHED_GROUP_P (ready[*n_readyp - i])
	     && (!next_insn || !SCHED_GROUP_P (next_insn)))
	    || (next_insn && NONDEBUG_INSN_P (next_insn)
		&& recog_memoized (next_insn) >= 0
		&& get_attr_type (next_insn) != TYPE_LOAD
		&& get_attr_type (next_insn) != TYPE_STORE))
	  {
	    std::swap (ready[*n_readyp - 1], ready[*n_readyp - i]);
	    sched_state.alu_pipe_scheduled_p = 1;
	    sched_state.cached_can_issue_more = 1;
	    return 1;
	  }
      }
    return 0;
  }

  /* If all else fails, schedule a single instruction.  */
  if (ready && *n_readyp > 0
      && NONDEBUG_INSN_P (ready[*n_readyp - 1])
      && recog_memoized (ready[*n_readyp - 1]) >= 0)
  {
    rtx_insn *insn = ready[*n_readyp - 1];
    enum attr_type insn_type = get_attr_type (insn);

    /* Memory operations go to pipeB if available.  */
    if (!sched_state.pipeB_scheduled_p
	&& (insn_type == TYPE_LOAD || insn_type == TYPE_STORE))
    {
      sched_state.pipeB_scheduled_p = 1;
    }
    /* Non-memory operations go to ALU pipe.  */
    else if (insn_type != TYPE_LOAD && insn_type != TYPE_STORE)
    {
      sched_state.alu_pipe_scheduled_p = 1;
    }
  }

  return sched_state.cached_can_issue_more;
}

int
arcv_sched_adjust_priority (rtx_insn *insn, int priority)
{
  if (DEBUG_INSN_P (insn) || GET_CODE (PATTERN (insn)) == USE
      || GET_CODE (PATTERN (insn)) == CLOBBER)
    return priority;

  /* Bump the priority of fused load-store pairs for easier
     scheduling of the memory pipe.  The specific increase
     value is determined empirically.  */
  rtx_insn *next = arcv_next_fusible_insn (insn);
  if (next && INSN_P (next) && SCHED_GROUP_P (next)
      && ((get_attr_type (insn) == TYPE_STORE
	   && get_attr_type (next) == TYPE_STORE)
	 || (get_attr_type (insn) == TYPE_LOAD
	     && get_attr_type (next) == TYPE_LOAD)))
    return priority + 1;

  return priority;
}

/* Adjust scheduling cost for ARCV fusion.  */

int
arcv_sched_adjust_cost (rtx_insn *insn, int dep_type, int cost)
{
  if (dep_type == REG_DEP_ANTI && !SCHED_GROUP_P (insn))
    return cost + 1;

  return cost;
}

/* If INSN is a load or store of address in the form of [base+offset],
   extract the two parts and set to BASE and OFFSET.  IS_LOAD is set
   to TRUE if it's a load.  Return TRUE if INSN is such an instruction,
   otherwise return FALSE.  */

static bool
arcv_fusion_load_store (rtx_insn *insn, rtx *base, rtx *offset,
			machine_mode *mode, bool *is_load)
{
  rtx x, dest, src;

  gcc_assert (INSN_P (insn));
  x = PATTERN (insn);
  if (GET_CODE (x) != SET)
    return false;

  src = SET_SRC (x);
  dest = SET_DEST (x);

  if ((GET_CODE (src) == SIGN_EXTEND || GET_CODE (src) == ZERO_EXTEND)
      && MEM_P (XEXP (src, 0)))
    src = XEXP (src, 0);

  if (REG_P (src) && MEM_P (dest))
    {
      *is_load = false;
      if (extract_base_offset_in_addr (dest, base, offset))
	*mode = GET_MODE (dest);
    }
  else if (MEM_P (src) && REG_P (dest))
    {
      *is_load = true;
      if (extract_base_offset_in_addr (src, base, offset))
	*mode = GET_MODE (src);
    }
  else
    return false;

  return (*base != NULL_RTX && *offset != NULL_RTX);
}

void
arcv_sched_fusion_priority (rtx_insn *insn, int max_pri, int *fusion_pri,
			     int *pri)
{
  rtx base, offset;
  machine_mode mode = SImode;
  bool is_load;

  gcc_assert (INSN_P (insn));

  /* Default priority for non-fusible instructions.  */
  int default_pri = max_pri - 1;

  /* Check if this is a fusible load/store instruction.  */
  if (!arcv_fusion_load_store (insn, &base, &offset, &mode, &is_load)
      || !arcv_pair_fusion_mode_allowed_p (mode, is_load))
    {
      *pri = default_pri;
      *fusion_pri = default_pri;
      return;
    }

  /* Start with half the default priority to distinguish fusible from
     non-fusible instructions.  */
  int priority = default_pri / 2;

  /* Scale priority by access width - narrower accesses get lower priority.
     HImode: divide by 2, QImode: divide by 4.  This encourages wider
     accesses to be scheduled together.  */
  if (mode == HImode)
    priority /= 2;
  else if (mode == QImode)
    priority /= 4;

  /* Factor in base register: instructions with smaller register numbers
     get higher priority.  The shift by 20 bits ensures this is the most
     significant component of the priority.  */
  const int BASE_REG_SHIFT = 20;
  const int BASE_REG_MASK = 0xff;
  priority -= ((REGNO (base) & BASE_REG_MASK) << BASE_REG_SHIFT);

  /* Calculate fusion priority: group loads/stores with adjacent addresses
     into the same scheduling group.  We divide the offset by (mode_size * 2)
     to group pairs of adjacent accesses, then shift left by 1 to make room
     for the load/store bit.  */
  int off_val = (int)(INTVAL (offset));
  int addr_group = off_val / (GET_MODE_SIZE (mode).to_constant () * 2);
  *fusion_pri = priority - (addr_group << 1) + is_load;

  /* Factor in the actual offset value: instructions with smaller offsets
     get higher priority.  We use only the lower 20 bits to avoid overflow.  */
  const int OFFSET_MASK = 0xfffff;
  if (off_val >= 0)
    priority -= (off_val & OFFSET_MASK);
  else
    priority += ((-off_val) & OFFSET_MASK);

  *pri = priority;
}

bool
arcv_can_issue_more_p (int issue_rate, int more)
{
  /* Beginning of cycle - reset variables.  */
  if (more == issue_rate)
    {
      sched_state.alu_pipe_scheduled_p = 0;
      sched_state.pipeB_scheduled_p = 0;
    }

  if (sched_state.alu_pipe_scheduled_p && sched_state.pipeB_scheduled_p)
    {
      sched_state.cached_can_issue_more = 0;
      return false;
    }

  sched_state.cached_can_issue_more = more;

  return true;
}

int
arcv_sched_variable_issue (rtx_insn *insn, int more)
{
  rtx_insn *next = arcv_next_fusible_insn (insn);
  if (next && INSN_P (next)
      && SCHED_GROUP_P (next))
    {
      if (get_attr_type (insn) == TYPE_LOAD
	  || get_attr_type (insn) == TYPE_STORE
	  || get_attr_type (next) == TYPE_LOAD
	  || get_attr_type (next) == TYPE_STORE)
	sched_state.pipeB_scheduled_p = 1;
      else
	sched_state.alu_pipe_scheduled_p = 1;
    }

  if (get_attr_type (insn) == TYPE_ALU_FUSED
      || get_attr_type (insn) == TYPE_IMUL_FUSED)
    {
      sched_state.alu_pipe_scheduled_p = 1;
      more -= 1;
    }

  sched_state.last_scheduled_insn = insn;
  sched_state.cached_can_issue_more = more - 1;

  return sched_state.cached_can_issue_more;
}
