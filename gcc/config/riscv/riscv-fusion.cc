/* Subroutines used for instruction fusion for RISC-V.
   Copyright (C) 2011-2026 Free Software Foundation, Inc.

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
#include "regs.h"
#include "insn-config.h"
#include "recog.h"
#include "function.h"
#include "memmodel.h"
#include "emit-rtl.h"
#include "tm_p.h"
#include "regset.h"
#include "basic-block.h"
#include "insn-attr.h"
#include "sched-int.h"
#include "riscv-protos.h"

/* Implement TARGET_SCHED_MACRO_FUSION_P.  Return true if target supports
   instruction fusion of some sort.  */

bool
riscv_macro_fusion_p (void)
{
  return riscv_get_fusible_ops () != RISCV_FUSE_NOTHING;
}

/* Return true iff the instruction fusion described by OP is enabled.  */

static bool
riscv_fusion_enabled_p(enum riscv_fusion_pairs op)
{
  return riscv_get_fusible_ops () & op;
}

/* Return the next possible fusible insn.  */

rtx_insn *
riscv_next_fusible_insn (rtx_insn *insn)
{
  while (insn)
    {
      insn = NEXT_INSN (insn);

      if (insn == 0)
	break;

      if (!NONDEBUG_INSN_P (insn))
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

/* Matches an add:
   (set (reg:DI rd) (plus:SI (reg:SI rs1) (reg:SI rs2))) */

static bool
riscv_set_is_add (rtx set)
{
  return (GET_CODE (SET_SRC (set)) == PLUS
	  && REG_P (XEXP (SET_SRC (set), 0))
	  && REG_P (XEXP (SET_SRC (set), 1))
	  && REG_P (SET_DEST (set)));
}

/* Matches an addi:
   (set (reg:DI rd) (plus:SI (reg:SI rs1) (const_int imm))) */

static bool
riscv_set_is_addi (rtx set)
{
  return (GET_CODE (SET_SRC (set)) == PLUS
	  && REG_P (XEXP (SET_SRC (set), 0))
	  && CONST_INT_P (XEXP (SET_SRC (set), 1))
	  && REG_P (SET_DEST (set)));
}

/* Matches an add.uw:
  (set (reg:DI rd)
    (plus:DI (zero_extend:DI (reg:SI rs1)) (reg:DI rs2))) */

static bool
riscv_set_is_adduw (rtx set)
{
  return (GET_CODE (SET_SRC (set)) == PLUS
	  && GET_CODE (XEXP (SET_SRC (set), 0)) == ZERO_EXTEND
	  && REG_P (XEXP (XEXP (SET_SRC (set), 0), 0))
	  && REG_P (XEXP (SET_SRC (set), 1))
	  && REG_P (SET_DEST (set)));
}

/* Matches a shNadd:
  (set (reg:DI rd)
       (plus:DI (ashift:DI (reg:DI rs1) (const_int N)) (reg:DI rS2)) */

static bool
riscv_set_is_shNadd (rtx set)
{
  return (GET_CODE (SET_SRC (set)) == PLUS
	  && GET_CODE (XEXP (SET_SRC (set), 0)) == ASHIFT
	  && REG_P (XEXP (XEXP (SET_SRC (set), 0), 0))
	  && CONST_INT_P (XEXP (XEXP (SET_SRC (set), 0), 1))
	  && (INTVAL (XEXP (XEXP (SET_SRC (set), 0), 1)) == 1
	      || INTVAL (XEXP (XEXP (SET_SRC (set), 0), 1)) == 2
	      || INTVAL (XEXP (XEXP (SET_SRC (set), 0), 1)) == 3)
	  && REG_P (SET_DEST (set)));
}

/* Matches a shNadd.uw:
  (set (reg:DI rd)
       (plus:DI (and:DI (ashift:DI (reg:DI rs1) (const_int N))
			(const_int N))
		(reg:DI rs2)) */

static bool
riscv_set_is_shNadduw (rtx set)
{
  return (GET_CODE (SET_SRC (set)) == PLUS
	  && GET_CODE (XEXP (SET_SRC (set), 0)) == AND
	  && GET_CODE (XEXP (XEXP (SET_SRC (set), 0), 0)) == ASHIFT
	  && REG_P (XEXP (XEXP (XEXP (SET_SRC (set), 0), 0), 0))
	  && CONST_INT_P (XEXP (XEXP (XEXP (SET_SRC (set), 0), 0), 1))
	  && (INTVAL (XEXP (XEXP (XEXP (SET_SRC (set), 0), 0), 1)) == 1
	      || INTVAL (XEXP (XEXP (XEXP (SET_SRC (set), 0), 0), 1)) == 2
	      || INTVAL (XEXP (XEXP (XEXP (SET_SRC (set), 0), 0), 1)) == 3)
	  && REG_P (SET_DEST (set)));
}

/* Return TRUE if two addresses can be fused.  */

static bool
riscv_fused_addr_p (rtx addr0, rtx addr1, bool is_load)
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

  /* Check if the mode is allowed for ARC-V fusion restrictions.
     Loads: allow SI, HI, and QI modes.
     Stores: allow only SI mode.  */
  if (TARGET_ARCV_FUSION)
    {
      machine_mode mode = GET_MODE (addr0);
      bool mode_allowed = ((is_load && (mode == SImode
					|| mode == HImode
					|| mode == QImode))
			    || (!is_load && mode == SImode));

      if (!mode_allowed)
	return false;
    }

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
riscv_arith_type_insn_p (rtx_insn *insn)
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

/* Return true if PREV and CURR constitute an ordered load/store + op/opimm
   pair, for the purposes of macro-op fusion.
   This is a more general form that combines load+arith and store+arith.  */

static bool
riscv_ls_update (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);

  enum attr_type p_type = get_attr_type (prev);
  /* Check if the prev instruction is load or store.  */
  if (!(p_type == TYPE_LOAD || p_type == TYPE_STORE))
    return false;

  gcc_assert (prev_set && curr_set);

  if (!riscv_arith_type_insn_p (curr))
    return false;

  rtx c_src = SET_SRC (curr_set);
  rtx c_dest = SET_DEST (curr_set);

  /* Check if curr has at least one register source.  */
  if (CONST_INT_P (c_src)
      || (!CONST_INT_P (c_src) && !REG_P (XEXP (c_src, 0))))
    return false;

  int c_rs1 = REGNO (XEXP (c_src, 0));
  int c_rd  = REGNO (c_dest);

  /* Check if there is a second source register.  */
  bool has_rs2 = (GET_RTX_LENGTH (GET_CODE (c_src)) > 1
		  && REG_P (XEXP (c_src, 1)));

  int c_rs2 = has_rs2 ? REGNO (XEXP (c_src, 1)) : -1;

  switch (p_type)
    {
    case TYPE_LOAD:
      {
       rtx p_src_addr = XEXP (SET_SRC (prev_set), 0);
       if (!REG_P (p_src_addr))
	 return false;

       int p_rs = REGNO (p_src_addr);
       int p_rd = REGNO (SET_DEST (prev_set));

       return (p_rs == c_rs1
	       && p_rs != p_rd
	       && p_rd != c_rd
	       && (!has_rs2 /* Fused LD + OP.  */
		   || p_rd != c_rs2)); /* Fused LD + OP-IMM.  */
      }

    case TYPE_STORE:
      {
       rtx p_dst_addr = XEXP (SET_DEST (prev_set), 0);
       if (!REG_P (p_dst_addr))
	 return false;

       int p_rs = REGNO (p_dst_addr);

       return (p_rs == c_rs1
	       && (!has_rs2 /* Fused ST + OP.  */
		   || p_rs == c_rs2)); /* Fused ST + OP-IMM.  */
      }

    default:
      return false;
    }
}

/* Return true if PREV and CURR constitute an ordered load/store + lui pair, for
   the purposes of macro-op fusion.  */

static bool
riscv_memop_lui_pair_p (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);

  gcc_assert (prev_set);
  gcc_assert (curr_set);

  /* Check if curr is a LUI instruction:
     - LUI via HIGH: (set (reg:X rd) (high (const_int)))
     - LUI via immediate: (set (reg:X rd) (const_int UPPER_IMM_20))  */
  bool is_lui = (REG_P (SET_DEST (curr_set))
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

/* Implement TARGET_SCHED_MACRO_FUSION_PAIR_P.  Return true if PREV and CURR
   should be kept together during scheduling.  */

bool
riscv_macro_fusion_pair_p (rtx_insn *prev, rtx_insn *curr)
{
  /* If fusion is not enabled, then there's nothing to do.  */
  if (!riscv_macro_fusion_p ())
    return false;

  /* If PREV is already marked as fused, then we can't fuse CURR with PREV
     and if we were to fuse them we'd end up with a blob of insns that
     essentially are an atomic unit which is bad for scheduling.  */
  if (SCHED_GROUP_P (prev))
    return false;

  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  /* prev and curr are simple SET insns i.e. no flag setting or branching.  */
  bool simple_sets_p = prev_set && curr_set && !any_condjump_p (curr);
  bool sched1 = can_create_pseudo_p ();

  unsigned int prev_dest_regno = (prev_set && REG_P (SET_DEST (prev_set))
				  ? REGNO (SET_DEST (prev_set))
				  : FIRST_PSEUDO_REGISTER);
  unsigned int curr_dest_regno = (curr_set && REG_P (SET_DEST (curr_set))
				  ? REGNO (SET_DEST (curr_set))
				  : FIRST_PSEUDO_REGISTER);

  if (simple_sets_p
      && (riscv_fusion_enabled_p (RISCV_FUSE_ZEXTW)
	  || riscv_fusion_enabled_p (RISCV_FUSE_ZEXTWS))
      && (sched1 || prev_dest_regno == curr_dest_regno))
    {
      /* We are trying to match the following:
	   prev (slli) == (set (reg:DI rD)
			       (ashift:DI (reg:DI rS) (const_int 32)))
	   curr (slri) == (set (reg:DI rD)
			       (lshiftrt:DI (reg:DI rD) (const_int <shift>)))
	 with <shift> being either 32 for FUSE_ZEXTW, or
			 `less than 32 for FUSE_ZEXTWS. */

      if (GET_CODE (SET_SRC (prev_set)) == ASHIFT
	  && GET_CODE (SET_SRC (curr_set)) == LSHIFTRT
	  && REG_P (SET_DEST (prev_set))
	  && REG_P (SET_DEST (curr_set))
	  && REG_P (XEXP (SET_SRC (curr_set), 0))
	  && REGNO (XEXP (SET_SRC (curr_set), 0)) == curr_dest_regno
	  && CONST_INT_P (XEXP (SET_SRC (prev_set), 1))
	  && CONST_INT_P (XEXP (SET_SRC (curr_set), 1))
	  && INTVAL (XEXP (SET_SRC (prev_set), 1)) == 32
	  && ((INTVAL (XEXP (SET_SRC (curr_set), 1)) == 32
	       && riscv_fusion_enabled_p (RISCV_FUSE_ZEXTW) )
	      || (INTVAL (XEXP (SET_SRC (curr_set), 1)) < 32
		  && riscv_fusion_enabled_p (RISCV_FUSE_ZEXTWS))))
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_ZEXTWS\n");
	  return true;
	}
    }

  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_ZEXTH)
      && (sched1 || prev_dest_regno == curr_dest_regno))
    {
      /* We are trying to match the following:
	   prev (slli) == (set (reg:DI rD)
			       (ashift:DI (reg:DI rS) (const_int 48)))
	   curr (slri) == (set (reg:DI rD)
			       (lshiftrt:DI (reg:DI rD) (const_int 48))) */

      if (GET_CODE (SET_SRC (prev_set)) == ASHIFT
	  && GET_CODE (SET_SRC (curr_set)) == LSHIFTRT
	  && REG_P (SET_DEST (prev_set))
	  && REG_P (SET_DEST (curr_set))
	  && REG_P (XEXP (SET_SRC (curr_set), 0))
	  && REGNO (XEXP (SET_SRC (curr_set), 0)) == curr_dest_regno
	  && CONST_INT_P (XEXP (SET_SRC (prev_set), 1))
	  && CONST_INT_P (XEXP (SET_SRC (curr_set), 1))
	  && INTVAL (XEXP (SET_SRC (prev_set), 1)) == 48
	  && INTVAL (XEXP (SET_SRC (curr_set), 1)) == 48)
	{
	  if (dump_file)
	    fprintf (dump_file,"RISCV_FUSE_ZEXTH\n");
	  return true;
	}
    }

  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_LDINDEXED)
      && (sched1 || prev_dest_regno == curr_dest_regno))
    {
      /* We are trying to match the following:
	   prev (add) == (set (reg:DI rD)
			      (plus:DI (reg:DI rS1) (reg:DI rS2))
	   curr (ld)  == (set (reg:DI rD)
			      (mem:DI (reg:DI rD))) */

      if (MEM_P (SET_SRC (curr_set))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && REG_P (XEXP (SET_SRC (curr_set), 0))
	  && REG_P (XEXP (SET_SRC (curr_set), 0))
	  && REGNO (XEXP (SET_SRC (curr_set), 0)) == prev_dest_regno
	  && GET_CODE (SET_SRC (prev_set)) == PLUS
	  && REG_P (XEXP (SET_SRC (prev_set), 0))
	  && REG_P (XEXP (SET_SRC (prev_set), 1)))
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_LDINDEXED\n");
	  return true;
	}

      /* We are trying to match the following:
	   prev (add) == (set (reg:DI rD)
			      (plus:DI (reg:DI rS1) (reg:DI rS2)))
	   curr (lw)  == (set (any_extend:DI (mem:SUBX (reg:DI rD)))) */

      if ((GET_CODE (SET_SRC (curr_set)) == SIGN_EXTEND
	   || (GET_CODE (SET_SRC (curr_set)) == ZERO_EXTEND))
	  && MEM_P (XEXP (SET_SRC (curr_set), 0))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && REG_P (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
	  && REGNO (XEXP (XEXP (SET_SRC (curr_set), 0), 0)) == prev_dest_regno
	  && GET_CODE (SET_SRC (prev_set)) == PLUS
	  && REG_P (XEXP (SET_SRC (prev_set), 0))
	  && REG_P (XEXP (SET_SRC (prev_set), 1)))
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_LDINDEXED\n");
	  return true;
	}
    }

  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_EXPANDED_LD)
      && (sched1 || prev_dest_regno == curr_dest_regno))
    {
      /* For the "expanded add/load fusion" family we have 2 main
	 categories: memory loads with displacement (i.e. with imm offset)
	 and loads without displacement (i.e. with offset = x0).

	 For loads without displacement we'll need:
	 - add + ld (done in RISCV_FUSE_LDINDEXED)
	 - addi + ld (done in RISCV_FUSE_LDPREINCREMENT)
	 - shNadd + ld
	 - add.uw + lw
	 - shNadd.uw + lw

	 For loads with displacement/immediates:
	 with lw with immediate):
	 - add + ld with displacement
	 - addi + ld with displacement
	 - shNadd + ld with displacement
	 - add.uw + lw with displacement
	 - shNadd.uw + lw with displacement */

      /* We're trying to match a curr_set ld with displacement:
	  prev (add|addi) = (set (reg:DI rd) (...))
	  curr (ld)  == (set (reg:DI rD)
		(mem:DI (plus:DI (reg:DI rD) (const_int IMM12)))) */
      if (MEM_P (SET_SRC (curr_set))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && GET_CODE (XEXP (SET_SRC (curr_set), 0)) == PLUS
	  && REG_P (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
	  && REGNO (XEXP (XEXP (SET_SRC (curr_set), 0), 0)) == prev_dest_regno)
	{
	  if (riscv_set_is_add (prev_set))
	    {
	      if (dump_file)
		fprintf (dump_file, "RISCV_FUSE_EXPANDED_LD\n");
	      return true;
	    }

	  if (riscv_set_is_addi (prev_set))
	    {
	      if (dump_file)
		fprintf (dump_file, "RISCV_FUSE_EXPANDED_LD\n");
	      return true;
	    }

	  if (riscv_set_is_shNadd (prev_set))
	    {
	      if (dump_file)
		fprintf (dump_file, "RISCV_FUSE_EXPANDED_LD\n");
	      return true;
	    }
	}

      /* We're trying to match a ld without displacement:
	  prev (addi|shNadd) = (reg:DI rD) (...))
	  curr (ld)  == (set (reg:DI rD)
			     (mem:DI (reg:DI rD))) */
      if (MEM_P (SET_SRC (curr_set))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && REG_P (XEXP (SET_SRC (curr_set), 0))
	  && REGNO (XEXP (SET_SRC (curr_set), 0)) == prev_dest_regno)
	{
	  if (riscv_set_is_addi (prev_set))
	    {
	      if (dump_file)
		fprintf (dump_file, "RISCV_FUSE_EXPANDED_LD\n");
	      return true;
	    }

	  if (riscv_set_is_shNadd (prev_set))
	    {
	      if (dump_file)
		fprintf (dump_file, "RISCV_FUSE_EXPANDED_LD\n");
	      return true;
	    }
	}

      /* We're trying to match a curr_set lw with displacement:
	  prev (add.uw|shNadd.uw) = (set (reg:DI rd) (...))
	  curr (lw)  == (set (reg:DI rd)
		(any_extend:DI (mem:SUBX (plus:DI ((reg:DI rd)
						   (const_int IMM)))) */
      if ((GET_CODE (SET_SRC (curr_set)) == SIGN_EXTEND
	   || (GET_CODE (SET_SRC (curr_set)) == ZERO_EXTEND))
	  && MEM_P (XEXP (SET_SRC (curr_set), 0))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && GET_CODE (XEXP (XEXP (SET_SRC (curr_set), 0), 0)) == PLUS
	  && REG_P (XEXP (XEXP (XEXP (SET_SRC (curr_set), 0), 0), 0))
	  && (REGNO (XEXP (XEXP (XEXP (SET_SRC (curr_set), 0), 0), 0))
	      == prev_dest_regno))
	{
	  if (riscv_set_is_adduw (prev_set))
	    {
	      if (dump_file)
		fprintf (dump_file, "RISCV_FUSE_EXPANDED_LD\n");
	      return true;
	    }

	  if (riscv_set_is_shNadduw (prev_set))
	    {
	      if (dump_file)
		fprintf (dump_file, "RISCV_FUSE_EXPANDED_LD\n");
	      return true;
	    }
	}

      /* We're trying to match a curr_set lw without displacement:
	  prev (add.uw|shNadd.uw) = (set (reg:DI rd) (...))
	  curr (ld|lh|lw)  == (set (reg:DI rd)
		(any_extend:DI (mem:SUBX (reg:DI rsd)))) */
      if ((GET_CODE (SET_SRC (curr_set)) == SIGN_EXTEND
	   || (GET_CODE (SET_SRC (curr_set)) == ZERO_EXTEND))
	  && MEM_P (XEXP (SET_SRC (curr_set), 0))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && REG_P (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
	  && REGNO (XEXP (XEXP (SET_SRC (curr_set), 0), 0)) == prev_dest_regno)
	{
	  if (riscv_set_is_adduw (prev_set))
	    {
	      if (dump_file)
		fprintf (dump_file, "RISCV_FUSE_EXPANDED_LD\n");
	      return true;
	    }

	  if (riscv_set_is_shNadduw (prev_set))
	    {
	      if (dump_file)
		fprintf (dump_file, "RISCV_FUSE_EXPANDED_LD\n");
	      return true;
	    }
	}
    }

  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_LDPREINCREMENT)
      && (sched1 || prev_dest_regno == curr_dest_regno))
    {
      /* We are trying to match the following:
	   prev (add) == (set (reg:DI rS)
			      (plus:DI (reg:DI rS) (const_int))
	   curr (ld)  == (set (reg:DI rD)
			      (mem:DI (reg:DI rS))) */

      if (MEM_P (SET_SRC (curr_set))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && REG_P (XEXP (SET_SRC (curr_set), 0))
	  && REGNO (XEXP (SET_SRC (curr_set), 0)) == prev_dest_regno
	  && GET_CODE (SET_SRC (prev_set)) == PLUS
	  && REG_P (XEXP (SET_SRC (prev_set), 0))
	  && CONST_INT_P (XEXP (SET_SRC (prev_set), 1)))
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_LDPREINCREMENT\n");
	  return true;
	}
    }

  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_LUI_ADDI)
      && (sched1 || prev_dest_regno == curr_dest_regno))
    {
      /* We are trying to match the following:
	   prev (lui)  == (set (reg:DI rD) (const_int UPPER_IMM_20))
	   curr (addi) == (set (reg:DI rD)
			       (plus:DI (reg:DI rD) (const_int IMM12))) */

      if ((GET_CODE (SET_SRC (curr_set)) == LO_SUM
	   || (GET_CODE (SET_SRC (curr_set)) == PLUS
	       && CONST_INT_P (XEXP (SET_SRC (curr_set), 1))
	       && SMALL_OPERAND (INTVAL (XEXP (SET_SRC (curr_set), 1)))))
	  && (GET_CODE (SET_SRC (prev_set)) == HIGH
	      || (CONST_INT_P (SET_SRC (prev_set))
		  && LUI_OPERAND (INTVAL (SET_SRC (prev_set))))))
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_LUI_ADDI\n");
	  return true;
	}
    }

  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_AUIPC_ADDI)
      && (sched1 || prev_dest_regno == curr_dest_regno))
    {
      /* We are trying to match the following:
	   prev (auipc) == (set (reg:DI rD) (unspec:DI [...] UNSPEC_AUIPC))
	   curr (addi)  == (set (reg:DI rD)
				(plus:DI (reg:DI rD) (const_int IMM12)))
	 and
	   prev (auipc) == (set (reg:DI rD) (unspec:DI [...] UNSPEC_AUIPC))
	   curr (addi)  == (set (reg:DI rD)
				(lo_sum:DI (reg:DI rD) (const_int IMM12))) */

      if (GET_CODE (SET_SRC (prev_set)) == UNSPEC
	  && XINT (SET_SRC (prev_set), 1) == UNSPEC_AUIPC
	  && (GET_CODE (SET_SRC (curr_set)) == LO_SUM
	      || (GET_CODE (SET_SRC (curr_set)) == PLUS
		  && CONST_INT_P (XEXP (SET_SRC (curr_set), 1))
		  && SMALL_OPERAND (INTVAL (XEXP (SET_SRC (curr_set), 1))))))

	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_AUIPC_ADDI\n");
	  return true;
	}
    }

  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_LUI_LD)
      && (sched1 || prev_dest_regno == curr_dest_regno))
    {
      /* We are trying to match the following:
	   prev (lui)  == (set (reg:DI rD) (const_int UPPER_IMM_20))
	   curr (ld)  == (set (reg:DI rD)
			      (mem:DI (plus:DI (reg:DI rD) (const_int IMM12)))) */

      /* A LUI_OPERAND accepts (const_int 0), but we won't emit that as LUI.  So
	 reject that case explicitly.  */
      if (CONST_INT_P (SET_SRC (prev_set))
	  && SET_SRC (prev_set) != CONST0_RTX (GET_MODE (SET_DEST (prev_set)))
	  && LUI_OPERAND (INTVAL (SET_SRC (prev_set)))
	  && MEM_P (SET_SRC (curr_set))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && GET_CODE (XEXP (SET_SRC (curr_set), 0)) == PLUS
	  && REG_P (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
	  && REGNO (XEXP (XEXP (SET_SRC (curr_set), 0), 0)) == prev_dest_regno)
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_LUI_LD\n");
	  return true;
	}

      if (GET_CODE (SET_SRC (prev_set)) == HIGH
	  && MEM_P (SET_SRC (curr_set))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && GET_CODE (XEXP (SET_SRC (curr_set), 0)) == LO_SUM
	  && REG_P (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
	  && REGNO (XEXP (XEXP (SET_SRC (curr_set), 0), 0)) == prev_dest_regno)
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_LUI_LD\n");
	  return true;
	}

      if (GET_CODE (SET_SRC (prev_set)) == HIGH
	  && (GET_CODE (SET_SRC (curr_set)) == SIGN_EXTEND
	      || GET_CODE (SET_SRC (curr_set)) == ZERO_EXTEND)
	  && MEM_P (XEXP (SET_SRC (curr_set), 0))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && (GET_CODE (XEXP (XEXP (SET_SRC (curr_set), 0), 0)) == LO_SUM
	      && REG_P (XEXP (XEXP (XEXP (SET_SRC (curr_set), 0), 0), 0))
	      && (REGNO (XEXP (XEXP (XEXP (SET_SRC (curr_set), 0), 0), 0))
		  == prev_dest_regno)))
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_LUI_LD\n");
	  return true;
	}
    }

  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_AUIPC_LD)
      && (sched1 || prev_dest_regno == curr_dest_regno))
    {
      /* We are trying to match the following:
	   prev (auipc) == (set (reg:DI rD) (unspec:DI [...] UNSPEC_AUIPC))
	   curr (ld)  == (set (reg:DI rD)
			      (mem:DI (plus:DI (reg:DI rD) (const_int IMM12)))) */

      if (GET_CODE (SET_SRC (prev_set)) == UNSPEC
	  && XINT (prev_set, 1) == UNSPEC_AUIPC
	  && MEM_P (SET_SRC (curr_set))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && GET_CODE (XEXP (SET_SRC (curr_set), 0)) == PLUS)
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_AUIPC_LD\n");
	  return true;
	}
    }

  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_CACHE_ALIGNED_STD))
    {
      /* We are trying to match the following:
	   prev (sd) == (set (mem (plus (reg sp|fp) (const_int)))
			      (reg rS1))
	   curr (sd) == (set (mem (plus (reg sp|fp) (const_int)))
			      (reg rS2)) */

      if (MEM_P (SET_DEST (prev_set))
	  && MEM_P (SET_DEST (curr_set))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  /* We can probably relax this condition.  The documentation is a bit
	     unclear about sub-word cases.  So we just model DImode for now.  */
	  && GET_MODE (SET_DEST (curr_set)) == DImode
	  && GET_MODE (SET_DEST (prev_set)) == DImode)
	{
	  rtx base_prev, base_curr, offset_prev, offset_curr;

	  extract_base_offset_in_addr (SET_DEST (prev_set), &base_prev, &offset_prev);
	  extract_base_offset_in_addr (SET_DEST (curr_set), &base_curr, &offset_curr);

	  /* Proceed only if we find both bases, both bases are register and
	     bases are the same register.  */
	  if (base_prev != NULL_RTX && base_curr != NULL_RTX
	      && REG_P (base_prev) && REG_P (base_curr)
	      && REGNO (base_prev) != REGNO (base_curr)
	      /* The alignment of hte base pointer is more useful than the
		 alignment of the memory reference for determining if we're
		 on opposite sides of a cache line.  */
	      && REGNO_POINTER_ALIGN (ORIGINAL_REGNO (base_prev)) >= 128)
	    {
	      /* The two stores must be contained within opposite halves of the
		 same 16 byte aligned block of memory.  We know the pointer
		 has suitable alignment, so we just need to check the offsets
		 of the two stores for suitable alignment.  */

	      /* Get the smaller offset into OFFSET_PREV.  */
	      if (INTVAL (offset_prev) > INTVAL (offset_curr))
		std::swap (offset_prev, offset_curr);

	      /* We have a match if the smaller offset (OFFSET_PREV) is 16
		 byte aligned and the higher offset is 8 bytes more than the
		 lower offset.  */
	      if ((INTVAL (offset_prev) % 16) == 0
		  && (INTVAL (offset_prev) + 8 == INTVAL (offset_curr)))
		{
		  if (dump_file)
		    fprintf (dump_file, "RISCV_FUSE_ALIGNED_STD\n");
		  return true;
		}
	    }
	}
    }

  /* More general form of the RISCV_FUSE_CACHE_ALIGNED_STD.  The
     major difference is the dependency on the stores being opposite
     halves of a cache line is dropped.  Instead the lowest address
     needs 2X the alignment of the object and the higher address
     immediately followed the first object.  */
  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_ALIGNED_STD))
    {
      /* We are trying to match the following:
	prev (sd) == (set (mem (plus (reg rS1) (const_int)))
			  (reg rS2))
	curr (sd) == (set (mem (plus (reg rS1) (const_int)))
			  (reg rS3)) */

      if (MEM_P (SET_DEST (prev_set))
	  && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
	  && MEM_P (SET_DEST (curr_set))
	  /* Stores must have the same width */
	  && GET_MODE (SET_DEST (curr_set)) == GET_MODE (SET_DEST (prev_set)))
	{
	  rtx base_prev, base_curr, offset_prev, offset_curr;
	  unsigned mode_size;

	  extract_base_offset_in_addr (SET_DEST (prev_set),
				       &base_prev, &offset_prev);
	  extract_base_offset_in_addr (SET_DEST (curr_set),
				       &base_curr, &offset_curr);

	  /* Proceed only if we find both bases, both bases
	     are registers and bases are the same register.  */
	  if (base_prev != NULL_RTX && base_curr != NULL_RTX
	      && REG_P (base_prev) && REG_P (base_curr)
	      && REGNO (base_prev) == REGNO (base_curr))
	    {
	      machine_mode mode = GET_MODE (SET_DEST (curr_set));
	      mode_size = estimated_poly_value (GET_MODE_SIZE (mode));

	      HOST_WIDE_INT offset_prev_int = INTVAL (offset_prev);
	      HOST_WIDE_INT offset_curr_int = INTVAL (offset_curr);

	      /* Get the smaller offset into OFFSET_PREV_INT.  */
	      if (offset_prev_int > offset_curr_int)
		std::swap (offset_prev_int, offset_curr_int);

	      /* We've normalized, so we need to check that the lower
		 address is aligned to 2X the size of the object.  The
		 higher address must be the lower address plus the
		 size of the object.  */
	      if (((offset_prev_int % (2 * mode_size)) == 0)
		  && offset_prev_int + mode_size == offset_curr_int)
		{
		  if (dump_file)
		    fprintf (dump_file, "RISCV_FUSE_ALIGNED_STD\n");
		  return true;
		}
	    }
	}
    }

  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_BFEXT)
      && (sched1 || prev_dest_regno == curr_dest_regno))
    {
      /* We are trying to match the following:
	   prev (slli) == (set (reg:DI rD)
			       (ashift:DI (reg:DI rS) (const_int)))
	   curr (srli) == (set (reg:DI rD)
			       (lshiftrt:DI (reg:DI rD) (const_int))) */

      if (GET_CODE (SET_SRC (prev_set)) == ASHIFT
	  && (GET_CODE (SET_SRC (curr_set)) == LSHIFTRT
	      || GET_CODE (SET_SRC (curr_set)) == ASHIFTRT)
	  && REG_P (SET_DEST (prev_set))
	  && REG_P (SET_DEST (curr_set))
	  && REGNO (XEXP (SET_SRC (curr_set), 0)) == prev_dest_regno
	  && CONST_INT_P (XEXP (SET_SRC (prev_set), 1))
	  && CONST_INT_P (XEXP (SET_SRC (curr_set), 1)))
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_BFEXT\n");
	  return true;
	}
    }

  if (simple_sets_p && riscv_fusion_enabled_p (RISCV_FUSE_B_ALUI)
      && (sched1 || prev_dest_regno == curr_dest_regno))
    {
      /* We are trying to match the following:
	  prev (orc.b) == (set (reg rD)
				(unspec (reg rS1)))
	  curr (not) == (set (reg rD2) (not (reg rD))) */

      if (GET_CODE (SET_SRC (prev_set)) == UNSPEC
	  && GET_CODE (SET_SRC (curr_set)) == NOT
	  && XINT (SET_SRC (prev_set), 1) == UNSPEC_ORC_B
	  && REG_P (SET_DEST (prev_set))
	  && REG_P (SET_DEST (curr_set))
	  && REG_P (XEXP (SET_SRC (curr_set), 0))
	  && REGNO (XEXP (SET_SRC (curr_set), 0)) == prev_dest_regno)
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_B_ALUI\n");
	  return true;
	}

      /* We are trying to match the following:
	  prev (ctz) == (set (reg rD) (ctz (reg rS1)))
	  curr (andi) == (set (reg rD)
				(and (reg rD) (const_int 63))) */

      if (GET_CODE (SET_SRC (prev_set)) == CTZ
	  && GET_CODE (SET_SRC (curr_set)) == AND
	  && CONST_INT_P (XEXP (SET_SRC (curr_set), 1))
	  && INTVAL (XEXP (SET_SRC (curr_set), 1)) == 63
	  && REG_P (SET_DEST (prev_set))
	  && REG_P (SET_DEST (curr_set))
	  && REG_P (XEXP (SET_SRC (curr_set), 0))
	  && REGNO (XEXP (SET_SRC (curr_set), 0)) == prev_dest_regno)
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_B_ALUI\n");
	  return true;
	}

      /* We are trying to match the following:
	  prev (sub) == (set (reg rD)
				(minus (const_int 0) (reg rS2))
	  curr (max) == (set (reg rD)
				(smax (reg rD) (reg rS2))) */

      if (GET_CODE (SET_SRC (prev_set)) == MINUS
	  && (XEXP (SET_SRC (prev_set), 0)
	      == CONST0_RTX (GET_MODE (SET_SRC (prev_set))))
	  && CONST_INT_P (XEXP (SET_SRC (prev_set), 0))
	  && GET_CODE (SET_SRC (curr_set)) == SMAX
	  && REG_P (SET_DEST (prev_set))
	  && REG_P (SET_DEST (curr_set))
	  && REG_P (XEXP (SET_SRC (curr_set), 0))
	  && REGNO (XEXP (SET_SRC (curr_set), 0)) == prev_dest_regno
	  && REG_P (XEXP (SET_SRC (prev_set), 1))
	  && REG_P (XEXP (SET_SRC (curr_set), 1))
	  && (REGNO (XEXP (SET_SRC (prev_set), 1))
	      == REGNO (XEXP (SET_SRC (curr_set), 1))))
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_B_ALUI\n");
	  return true;
	}

      /* We are trying to match the following:
	  prev (neg) == (set (reg rD) (neg (reg rS1)))
	  curr (max) == (set (reg rD)
				(smax (reg rD) (reg rS1))) */

      if (GET_CODE (SET_SRC (prev_set)) == NEG
	  && GET_CODE (SET_SRC (curr_set)) == SMAX
	  && REG_P (SET_DEST (prev_set))
	  && REG_P (SET_DEST (curr_set))
	  && REG_P (XEXP (SET_SRC (curr_set), 0))
	  && REGNO (XEXP (SET_SRC (curr_set), 0)) == prev_dest_regno
	  && REG_P (XEXP (SET_SRC (prev_set), 0))
	  && REG_P (XEXP (SET_SRC (curr_set), 1))
	  && (REGNO (XEXP (SET_SRC (prev_set), 0))
	      == REGNO (XEXP (SET_SRC (curr_set), 1))))
	{
	  if (dump_file)
	    fprintf (dump_file, "RISCV_FUSE_B_ALUI\n");
	  return true;
	}
    }

  /* Fuse multiply-add pair:
     prev: (set rd_mult (mult rs1 rs2))
     curr: (set rd_add (plus rd_mult rs3))  */
  if (riscv_fusion_enabled_p (RISCV_FUSE_MULT_ADD)
      && prev_set && curr_set
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
	  fprintf (dump_file, "RISCV_FUSE_MULT_ADD (op0)\n");
	return true;
       }

      if (REG_P (XEXP (curr_plus, 1))
	&& REGNO (XEXP (curr_plus, 1)) == mult_dest_regno)
       {
	if (dump_file)
	  fprintf (dump_file, "RISCV_FUSE_MULT_ADD (op1)\n");
	return true;
       }
    }

  /* Fuse logical shift left with logical shift right (bit-extract pattern):
     prev: (set rd (ashift rs imm1))
     curr: (set rd (lshiftrt rd imm2))
     This handles general bit-extraction patterns beyond the specific
     ZEXTW/ZEXTH cases (32/32 and 48/48) that are handled upstream.  */
  if (riscv_fusion_enabled_p (RISCV_FUSE_SHIFT_BITEXTRACT)
      && prev_set && curr_set
      && GET_CODE (SET_SRC (prev_set)) == ASHIFT
      && GET_CODE (SET_SRC (curr_set)) == LSHIFTRT
      && REG_P (SET_DEST (prev_set))
      && REG_P (SET_DEST (curr_set))
      && REGNO (SET_DEST (prev_set)) == REGNO (SET_DEST (curr_set))
      && REGNO (SET_DEST (prev_set)) == REGNO (XEXP (SET_SRC (curr_set), 0))
      && CONST_INT_P (XEXP (SET_SRC (prev_set), 1))
      && CONST_INT_P (XEXP (SET_SRC (curr_set), 1)))
    {
      HOST_WIDE_INT shift_left = INTVAL (XEXP (SET_SRC (prev_set), 1));
      HOST_WIDE_INT shift_right = INTVAL (XEXP (SET_SRC (curr_set), 1));

      /* Avoid duplicating ZEXTW (32/32) and ZEXTH (48/48) patterns
	 which are already handled by upstream code.  */
      if (!((shift_left == 32 && shift_right == 32)
	    || (shift_left == 48 && shift_right == 48)))
       {
	 if (dump_file)
	   fprintf (dump_file, "RISCV_FUSE_SHIFT_BITEXTRACT\n");
	 return true;
       }
    }

  /* Fuse load-immediate with a dependent conditional branch:
     prev: (set rd imm)
     curr: (if_then_else (cond rd ...) ...)  */
  if (riscv_fusion_enabled_p (RISCV_FUSE_LI_BRANCH)
      && get_attr_type (prev) == TYPE_MOVE
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
	   fprintf (dump_file, "RISCV_FUSE_LI_BRANCH\n");
	 return true;
       }
      return false;
    }

  /* Do not fuse loads/stores before sched2.  */
  if (!reload_completed || sched_fusion)
    return false;

  /* Don't handle anything with a jump past this point.  */
  if (!simple_sets_p)
    return false;

  /* Fuse adjacent loads.  */
  if (riscv_fusion_enabled_p (RISCV_FUSE_ADJACENT_LOAD)
      && get_attr_type (prev) == TYPE_LOAD
      && get_attr_type (curr) == TYPE_LOAD)
    {
      if (riscv_fused_addr_p (SET_SRC (prev_set), SET_SRC (curr_set), true))
       {
	 if (dump_file)
	   fprintf (dump_file, "RISCV_FUSE_ADJACENT_LOAD\n");
	 return true;
       }
    }

  /* Fuse adjacent stores.  */
  if (riscv_fusion_enabled_p (RISCV_FUSE_ADJACENT_STORE)
      && get_attr_type (prev) == TYPE_STORE
      && get_attr_type (curr) == TYPE_STORE)
    {
      if (riscv_fused_addr_p (SET_DEST (prev_set), SET_DEST (curr_set), false))
       {
	 if (dump_file)
	   fprintf (dump_file, "RISCV_FUSE_ADJACENT_STORE\n");
	 return true;
       }
    }

  /* Look ahead 1 insn to prioritize adjacent load/store pairs.
     If curr and next form a better fusion opportunity, defer this fusion.  */
  rtx_insn *next = riscv_next_fusible_insn (curr);
  if (next)
    {
      rtx next_set = single_set (next);

      /* Defer if next instruction forms an adjacent load pair with curr.  */
      if (next_set
	  && riscv_fusion_enabled_p (RISCV_FUSE_ADJACENT_LOAD)
	  && get_attr_type (curr) == TYPE_LOAD
	  && get_attr_type (next) == TYPE_LOAD
	  && riscv_fused_addr_p (SET_SRC (curr_set), SET_SRC (next_set), true))
       return false;

      /* Defer if next instruction forms an adjacent store pair with curr.  */
      if (next_set
	  && riscv_fusion_enabled_p (RISCV_FUSE_ADJACENT_STORE)
	  && get_attr_type (curr) == TYPE_STORE
	  && get_attr_type (next) == TYPE_STORE
	  && riscv_fused_addr_p (SET_DEST (curr_set),
				 SET_DEST (next_set), false))
       return false;
    }

  /* Fuse a pre- or post-update memory operation:
     Examples: load+add, add+load, store+add, add+store.  */
  if (riscv_fusion_enabled_p (RISCV_FUSE_LS_UPDATE))
    {
      if (riscv_ls_update (prev, curr))
       {
	 if (dump_file)
	   fprintf (dump_file, "RISCV_FUSE_LS_UPDATE (prev, curr)\n");
	 return true;
       }
      if (riscv_ls_update (curr, prev))
       {
	 if (dump_file)
	   fprintf (dump_file, "RISCV_FUSE_LS_UPDATE (curr, prev)\n");
	 return true;
       }
    }

  /* Fuse a memory operation preceded or followed by a LUI:
     Examples: load+lui, lui+load, store+lui, lui+store.  */
  if (riscv_fusion_enabled_p (RISCV_FUSE_MEMOP_LUI))
    {
      if (riscv_memop_lui_pair_p (prev, curr))
       {
	 if (dump_file)
	   fprintf (dump_file, "RISCV_FUSE_MEMOP_LUI (prev, curr)\n");
	 return true;
       }
      if (riscv_memop_lui_pair_p (curr, prev))
       {
	 if (dump_file)
	   fprintf (dump_file, "RISCV_FUSE_MEMOP_LUI (curr, prev)\n");
	 return true;
       }
    }

  /* Fuse load-immediate with a store of the destination register:
     prev: (set rd imm)
     curr: (set (mem ...) rd)  */
  if (riscv_fusion_enabled_p (RISCV_FUSE_LI_STORE)
      && get_attr_type (prev) == TYPE_MOVE
      && get_attr_move_type (prev) == MOVE_TYPE_CONST
      && get_attr_type (curr) == TYPE_STORE)
    {
      rtx store_src = SET_SRC (curr_set);
      rtx load_dest = SET_DEST (prev_set);

      if (REG_P (store_src) && REG_P (load_dest)
	  && REGNO (store_src) == REGNO (load_dest))
       {
	if (dump_file)
	  {
	    if (GET_MODE (store_src) != GET_MODE (load_dest))
	      fprintf (dump_file, "RISCV_FUSE_LI_STORE (subreg)\n");
	    else
	      fprintf (dump_file, "RISCV_FUSE_LI_STORE\n");
	  }
	return true;
       }
    }

  return false;
}
