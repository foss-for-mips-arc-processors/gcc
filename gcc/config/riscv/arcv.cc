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
  rtx_insn *next = next_insn (curr);
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
