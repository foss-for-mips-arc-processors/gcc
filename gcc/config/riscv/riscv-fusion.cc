/* Subroutines used for instruction fusion for RISC-V.
   Copyright (C) 2026 Free Software Foundation, Inc.

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
riscv_fusion_enabled_p (enum riscv_fusion_pairs op)
{
  return riscv_get_fusible_ops () & op;
}

/* Return true if PREV_SET and CURR_SET satisfy the same-dest constraint
   required by most fusion rules: when we are past register allocation
   (i.e. can_create_pseudo_p () is false), the destination registers of
   the two sets must be the same physical register.  */

static bool
riscv_fusion_same_dest_p (rtx prev_set, rtx curr_set)
{
  if (can_create_pseudo_p ())
    return true;

  unsigned int prev_dest_regno = (REG_P (SET_DEST (prev_set))
				  ? REGNO (SET_DEST (prev_set))
				  : FIRST_PSEUDO_REGISTER);
  unsigned int curr_dest_regno = (REG_P (SET_DEST (curr_set))
				  ? REGNO (SET_DEST (curr_set))
				  : FIRST_PSEUDO_REGISTER);

  return prev_dest_regno == curr_dest_regno;
}

/* Matches an add:
   (set (reg:DI rd) (plus:SI (reg:SI rs1) (reg:SI rs2))) */

static bool
riscv_set_is_add_p (rtx set)
{
  return (GET_CODE (SET_SRC (set)) == PLUS
	  && REG_P (XEXP (SET_SRC (set), 0))
	  && REG_P (XEXP (SET_SRC (set), 1))
	  && REG_P (SET_DEST (set)));
}

/* Matches an addi:
   (set (reg:DI rd) (plus:SI (reg:SI rs1) (const_int imm))) */

static bool
riscv_set_is_addi_p (rtx set)
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
riscv_set_is_adduw_p (rtx set)
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
riscv_set_is_shNadd_p (rtx set)
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
riscv_set_is_shNadduw_p (rtx set)
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

void
riscv_sched_fusion_priority (rtx_insn *insn, int max_pri, int *fusion_pri,
			     int *pri)
{
  if (TARGET_ARCV_FUSION
      && arcv_sched_fusion_priority (insn, max_pri, fusion_pri, pri))
    return;

  /* Default priority.  */
  *pri = max_pri - 1;
  *fusion_pri = max_pri - 1;
}

/* Return TRUE if two memory operands can be fused based on their addresses.
   Checks if MEM0 and MEM1 have the same base register with adjacent offsets,
   making them suitable for fusion (e.g., adjacent load/store pairs).  */

static bool
riscv_adjacent_memops_p (rtx mem0, rtx mem1, bool is_load)
{
  rtx base0, base1, tmp;
  HOST_WIDE_INT off0 = 0, off1 = 0;

  if (GET_CODE (mem0) == SIGN_EXTEND || GET_CODE (mem0) == ZERO_EXTEND)
    mem0 = XEXP (mem0, 0);

  if (GET_CODE (mem1) == SIGN_EXTEND || GET_CODE (mem1) == ZERO_EXTEND)
    mem1 = XEXP (mem1, 0);

  if (!MEM_P (mem0) || !MEM_P (mem1))
    return false;

  /* Require the accesses to have the same mode.  */
  if (GET_MODE (mem0) != GET_MODE (mem1))
    return false;

  /* Check if the mode is allowed for ARC-V fusion restrictions.  */
  if (TARGET_ARCV_FUSION
	  && !arcv_pair_fusion_mode_allowed_p (GET_MODE (mem0), is_load))
    return false;

  rtx mem_addr0 = XEXP (mem0, 0);
  rtx mem_addr1 = XEXP (mem1, 0);

  if (GET_CODE (mem_addr0) == PLUS)
    {
      base0 = XEXP (mem_addr0, 0);
      tmp = XEXP (mem_addr0, 1);
      if (!CONST_INT_P (tmp))
       return false;
      off0 = INTVAL (tmp);
    }
  else if (REG_P (mem_addr0))
    base0 = mem_addr0;
  else
    return false;

  if (GET_CODE (mem_addr1) == PLUS)
    {
      base1 = XEXP (mem_addr1, 0);
      tmp = XEXP (mem_addr1, 1);
      if (!CONST_INT_P (tmp))
       return false;
      off1 = INTVAL (tmp);
    }
  else if (REG_P (mem_addr1))
    base1 = mem_addr1;
  else
    return false;

  /* Check if we have the same base.  */
  gcc_assert (REG_P (base0) && REG_P (base1));
  if (REGNO (base0) != REGNO (base1))
    return false;

  /* Fuse adjacent aligned addresses.  */
  if ((off0 % GET_MODE_SIZE (GET_MODE (mem0)).to_constant () == 0)
      && (abs (off1 - off0) == GET_MODE_SIZE (GET_MODE (mem0)).to_constant ()))
    return true;

  return false;
}

/* Return true if CURR should not be fused with PREV because CURR and the
   next fusible insn form a better adjacent load/store pair.  */

static bool
riscv_defer_for_adjacent_memop_p (rtx_insn *curr)
{
  rtx_insn *next = next_nonnote_nondebug_insn_bb (curr);
  if (!next)
    return false;

  rtx curr_set = single_set (curr);
  rtx next_set = single_set (next);
  if (!curr_set || !next_set)
    return false;

  /* Defer if next instruction forms an adjacent load pair with curr.  */
  if (riscv_fusion_enabled_p (RISCV_FUSE_ADJACENT_LOAD)
      && get_attr_type (curr) == TYPE_LOAD
      && get_attr_type (next) == TYPE_LOAD
      && riscv_adjacent_memops_p (SET_SRC (curr_set), SET_SRC (next_set), true))
    return true;

  /* Defer if next instruction forms an adjacent store pair with curr.  */
  if (riscv_fusion_enabled_p (RISCV_FUSE_ADJACENT_STORE)
      && get_attr_type (curr) == TYPE_STORE
      && get_attr_type (next) == TYPE_STORE
      && riscv_adjacent_memops_p (SET_DEST (curr_set),
				  SET_DEST (next_set), false))
    return true;

  return false;
}

/* Return true if PREV and CURR constitute an ordered load/store + op/opimm
   pair, for the purposes of macro-op fusion.
   This is a more general form that combines load+arith and store+arith.  */

static bool
riscv_memop_arith_fusion_p (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);

  /* Both instructions must be simple SETs.  */
  if (!prev_set || !curr_set)
    return false;

  /* Ensure prev_set and curr_set are actually SET patterns.  */
  if (GET_CODE (prev_set) != SET || GET_CODE (curr_set) != SET)
    return false;

  enum attr_type p_type = get_attr_type (prev);
  /* Check if the prev instruction is load or store.  */
  if (!(p_type == TYPE_LOAD || p_type == TYPE_STORE))
    return false;

  /* Check if curr is an arithmetic-like instruction.  */
  enum attr_type c_type = get_attr_type (curr);
  if (!(c_type == TYPE_ARITH
	|| c_type == TYPE_LOGICAL
	|| c_type == TYPE_SHIFT
	|| c_type == TYPE_SLT
	|| c_type == TYPE_BITMANIP
	|| c_type == TYPE_MIN
	|| c_type == TYPE_MAX
	|| c_type == TYPE_MINU
	|| c_type == TYPE_MAXU
	|| c_type == TYPE_CLZ
	|| c_type == TYPE_CTZ
	|| c_type == TYPE_MOVE))
    return false;

  rtx c_src = SET_SRC (curr_set);
  rtx c_dest = SET_DEST (curr_set);

  /* Curr destination must be a register.  */
  if (!REG_P (c_dest))
    return false;

  if (CONSTANT_P (c_src))
    return false;

  int c_rs1;
  int c_rs2;
  bool has_rs2;

  /* Move.  */
  if (REG_P (c_src))
    {
      c_rs1 = REGNO (c_src);
      has_rs2 = false;
    }
  /* Arithmetic.  */
  else if (REG_P (XEXP (c_src, 0)))
    {
      c_rs1 = REGNO (XEXP (c_src, 0));
      has_rs2 = (GET_RTX_LENGTH (GET_CODE (c_src)) > 1
		 && REG_P (XEXP (c_src, 1)));
      c_rs2 = has_rs2 ? REGNO (XEXP (c_src, 1)) : -1;
    }
  else
    return false;

  int c_rd = REGNO (c_dest);

  switch (p_type)
    {
    case TYPE_LOAD:
      {
       rtx p_src = SET_SRC (prev_set);
       rtx p_dest = SET_DEST (prev_set);

       /* Load destination must be a register.  */
       if (!REG_P (p_dest))
	 return false;

       /* Handle loads with sign/zero extension.  */
       if (GET_CODE (p_src) == SIGN_EXTEND || GET_CODE (p_src) == ZERO_EXTEND)
	 p_src = XEXP (p_src, 0);

       /* Load source must be a memory operand.  */
       if (!MEM_P (p_src))
	 return false;

       rtx p_src_addr = XEXP (p_src, 0);
       if (!REG_P (p_src_addr))
	 return false;

       int p_rs = REGNO (p_src_addr);
       int p_rd = REGNO (p_dest);

       return (p_rs == c_rs1
	       && p_rs != p_rd
	       && p_rd != c_rd
	       && (!has_rs2
		   || p_rd != c_rs2));
      }

    case TYPE_STORE:
      {
       rtx p_dest = SET_DEST (prev_set);

       /* Store destination must be a memory operand.  */
       if (!MEM_P (p_dest))
	 return false;

       rtx p_dst_addr = XEXP (p_dest, 0);
       if (!REG_P (p_dst_addr))
	 return false;

       int p_rs = REGNO (p_dst_addr);

       return (p_rs == c_rs1
	       && (!has_rs2
		   || p_rs == c_rs2));
      }

    default:
      return false;
    }
}

/* Check for RISCV_FUSE_ZEXTW and RISCV_FUSE_ZEXTWS fusion.
   prev (slli) == (set (reg:DI rD) (ashift:DI (reg:DI rS) (const_int 32)))
   curr (srli) == (set (reg:DI rD) (lshiftrt:DI (reg:DI rD) (const_int N)))
   with N being 32 for FUSE_ZEXTW, or less than 32 for FUSE_ZEXTWS.  */

static bool
riscv_fuse_zextws (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (!riscv_fusion_same_dest_p (prev_set, curr_set))
    return false;

  if (GET_CODE (SET_SRC (prev_set)) == ASHIFT
      && GET_CODE (SET_SRC (curr_set)) == LSHIFTRT
      && REG_P (SET_DEST (prev_set))
      && REG_P (SET_DEST (curr_set))
      && REG_P (XEXP (SET_SRC (curr_set), 0))
      && REGNO (XEXP (SET_SRC (curr_set), 0)) == REGNO (SET_DEST (curr_set))
      && CONST_INT_P (XEXP (SET_SRC (prev_set), 1))
      && CONST_INT_P (XEXP (SET_SRC (curr_set), 1))
      && INTVAL (XEXP (SET_SRC (prev_set), 1)) == 32
      && ((INTVAL (XEXP (SET_SRC (curr_set), 1)) == 32
	   && riscv_fusion_enabled_p (RISCV_FUSE_ZEXTW))
	  || (INTVAL (XEXP (SET_SRC (curr_set), 1)) < 32
	      && riscv_fusion_enabled_p (RISCV_FUSE_ZEXTWS))))
    return true;

  return false;
}

/* Check for RISCV_FUSE_ZEXTH fusion.
   prev (slli) == (set (reg:DI rD) (ashift:DI (reg:DI rS) (const_int 48)))
   curr (srli) == (set (reg:DI rD) (lshiftrt:DI (reg:DI rD) (const_int 48)))  */

static bool
riscv_fuse_zexth (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (!riscv_fusion_same_dest_p (prev_set, curr_set))
    return false;

  if (GET_CODE (SET_SRC (prev_set)) == ASHIFT
      && GET_CODE (SET_SRC (curr_set)) == LSHIFTRT
      && REG_P (SET_DEST (prev_set))
      && REG_P (SET_DEST (curr_set))
      && REG_P (XEXP (SET_SRC (curr_set), 0))
      && REGNO (XEXP (SET_SRC (curr_set), 0)) == REGNO (SET_DEST (curr_set))
      && CONST_INT_P (XEXP (SET_SRC (prev_set), 1))
      && CONST_INT_P (XEXP (SET_SRC (curr_set), 1))
      && INTVAL (XEXP (SET_SRC (prev_set), 1)) == 48
      && INTVAL (XEXP (SET_SRC (curr_set), 1)) == 48)
    return true;

  return false;
}

/* Check for RISCV_FUSE_LDINDEXED fusion.
   prev (add) == (set (reg:DI rD) (plus:DI (reg:DI rS1) (reg:DI rS2)))
   curr (ld)  == (set (reg:DI rD) (mem:DI (reg:DI rD)))  */

static bool
riscv_fuse_ldindexed (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (!riscv_fusion_same_dest_p (prev_set, curr_set))
    return false;

  if (MEM_P (SET_SRC (curr_set))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && REG_P (XEXP (SET_SRC (curr_set), 0))
      && REGNO (XEXP (SET_SRC (curr_set), 0)) == REGNO (SET_DEST (prev_set))
      && GET_CODE (SET_SRC (prev_set)) == PLUS
      && REG_P (XEXP (SET_SRC (prev_set), 0))
      && REG_P (XEXP (SET_SRC (prev_set), 1)))
    return true;

  /* curr (lw) == (set (any_extend:DI (mem:SUBX (reg:DI rD)))).  */
  if ((GET_CODE (SET_SRC (curr_set)) == SIGN_EXTEND
       || (GET_CODE (SET_SRC (curr_set)) == ZERO_EXTEND))
      && MEM_P (XEXP (SET_SRC (curr_set), 0))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && REG_P (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
      && (REGNO (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
	  == REGNO (SET_DEST (prev_set)))
      && GET_CODE (SET_SRC (prev_set)) == PLUS
      && REG_P (XEXP (SET_SRC (prev_set), 0))
      && REG_P (XEXP (SET_SRC (prev_set), 1)))
    return true;

  return false;
}

/* Check for RISCV_FUSE_EXPANDED_LD fusion.
   Covers add/addi/shNadd + ld (with or without displacement) and
   add.uw/shNadd.uw + lw (with or without displacement).  */

static bool
riscv_fuse_expanded_ld (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (!riscv_fusion_same_dest_p (prev_set, curr_set))
    return false;

  /* Match ld with displacement:
     curr (ld) == (set (reg:DI rD)
		       (mem:DI (plus:DI (reg:DI rD) (const_int IMM12))))  */
  if (MEM_P (SET_SRC (curr_set))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && GET_CODE (XEXP (SET_SRC (curr_set), 0)) == PLUS
      && REG_P (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
      && (REGNO (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
	  == REGNO (SET_DEST (prev_set))))
    {
      if (riscv_set_is_add_p (prev_set)
	  || riscv_set_is_addi_p (prev_set)
	  || riscv_set_is_shNadd_p (prev_set))
	return true;
    }

  /* Match ld without displacement:
     curr (ld) == (set (reg:DI rD) (mem:DI (reg:DI rD))).  */
  if (MEM_P (SET_SRC (curr_set))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && REG_P (XEXP (SET_SRC (curr_set), 0))
      && REGNO (XEXP (SET_SRC (curr_set), 0)) == REGNO (SET_DEST (prev_set)))
    {
      if (riscv_set_is_addi_p (prev_set)
	  || riscv_set_is_shNadd_p (prev_set))
	return true;
    }

  /* Match lw with displacement.  */
  if ((GET_CODE (SET_SRC (curr_set)) == SIGN_EXTEND
       || (GET_CODE (SET_SRC (curr_set)) == ZERO_EXTEND))
      && MEM_P (XEXP (SET_SRC (curr_set), 0))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && GET_CODE (XEXP (XEXP (SET_SRC (curr_set), 0), 0)) == PLUS
      && REG_P (XEXP (XEXP (XEXP (SET_SRC (curr_set), 0), 0), 0))
      && (REGNO (XEXP (XEXP (XEXP (SET_SRC (curr_set), 0), 0), 0))
	  == REGNO (SET_DEST (prev_set))))
    {
      if (riscv_set_is_adduw_p (prev_set)
	  || riscv_set_is_shNadduw_p (prev_set))
	return true;
    }

  /* Match lw without displacement.  */
  if ((GET_CODE (SET_SRC (curr_set)) == SIGN_EXTEND
       || (GET_CODE (SET_SRC (curr_set)) == ZERO_EXTEND))
      && MEM_P (XEXP (SET_SRC (curr_set), 0))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && REG_P (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
      && (REGNO (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
	  == REGNO (SET_DEST (prev_set))))
    {
      if (riscv_set_is_adduw_p (prev_set)
	  || riscv_set_is_shNadduw_p (prev_set))
	return true;
    }

  return false;
}

/* Check for RISCV_FUSE_LDPREINCREMENT fusion.
   prev (addi) == (set (reg:DI rS) (plus:DI (reg:DI rS) (const_int)))
   curr (ld)   == (set (reg:DI rD) (mem:DI (reg:DI rS)))  */

static bool
riscv_fuse_ldpreincrement (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (!riscv_fusion_same_dest_p (prev_set, curr_set))
    return false;

  if (MEM_P (SET_SRC (curr_set))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && REG_P (XEXP (SET_SRC (curr_set), 0))
      && REGNO (XEXP (SET_SRC (curr_set), 0)) == REGNO (SET_DEST (prev_set))
      && GET_CODE (SET_SRC (prev_set)) == PLUS
      && REG_P (XEXP (SET_SRC (prev_set), 0))
      && CONST_INT_P (XEXP (SET_SRC (prev_set), 1)))
    return true;

  return false;
}

/* Check for RISCV_FUSE_LUI_ADDI fusion.
   prev (lui)  == (set (reg:DI rD) (const_int UPPER_IMM_20))
   curr (addi) == (set (reg:DI rD) (plus:DI (reg:DI rD) (const_int IMM12)))  */

static bool
riscv_fuse_lui_addi (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (!riscv_fusion_same_dest_p (prev_set, curr_set))
    return false;

  if ((GET_CODE (SET_SRC (curr_set)) == LO_SUM
       || (GET_CODE (SET_SRC (curr_set)) == PLUS
	   && CONST_INT_P (XEXP (SET_SRC (curr_set), 1))
	   && SMALL_OPERAND (INTVAL (XEXP (SET_SRC (curr_set), 1)))))
      && (GET_CODE (SET_SRC (prev_set)) == HIGH
	  || (CONST_INT_P (SET_SRC (prev_set))
	      && LUI_OPERAND (INTVAL (SET_SRC (prev_set))))))
    return true;

  return false;
}

/* Check for RISCV_FUSE_AUIPC_ADDI fusion.
   prev (auipc) == (set (reg:DI rD) (unspec:DI UNSPEC_AUIPC))
   curr (addi)  == (set (reg:DI rD) (plus:DI (reg:DI rD) (const_int)))  */

static bool
riscv_fuse_auipc_addi (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (!riscv_fusion_same_dest_p (prev_set, curr_set))
    return false;

  if (GET_CODE (SET_SRC (prev_set)) == UNSPEC
      && XINT (SET_SRC (prev_set), 1) == UNSPEC_AUIPC
      && (GET_CODE (SET_SRC (curr_set)) == LO_SUM
	  || (GET_CODE (SET_SRC (curr_set)) == PLUS
	      && CONST_INT_P (XEXP (SET_SRC (curr_set), 1))
	      && SMALL_OPERAND (INTVAL (XEXP (SET_SRC (curr_set), 1))))))
    return true;

  return false;
}

/* Check for RISCV_FUSE_LUI_LD fusion.
   prev (lui) == (set (reg:DI rD) (const_int UPPER_IMM_20))
   curr (ld)  == (set (reg:DI rD) (mem:DI (plus:DI (reg:DI rD) ...)))  */

static bool
riscv_fuse_lui_ld (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (!riscv_fusion_same_dest_p (prev_set, curr_set))
    return false;

  /* A LUI_OPERAND accepts (const_int 0), but we won't emit that as LUI.
     Reject that case explicitly.  */
  if (CONST_INT_P (SET_SRC (prev_set))
      && SET_SRC (prev_set) != CONST0_RTX (GET_MODE (SET_DEST (prev_set)))
      && LUI_OPERAND (INTVAL (SET_SRC (prev_set)))
      && MEM_P (SET_SRC (curr_set))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && GET_CODE (XEXP (SET_SRC (curr_set), 0)) == PLUS
      && REG_P (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
      && (REGNO (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
	  == REGNO (SET_DEST (prev_set))))
    return true;

  if (GET_CODE (SET_SRC (prev_set)) == HIGH
      && MEM_P (SET_SRC (curr_set))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && GET_CODE (XEXP (SET_SRC (curr_set), 0)) == LO_SUM
      && REG_P (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
      && (REGNO (XEXP (XEXP (SET_SRC (curr_set), 0), 0))
	  == REGNO (SET_DEST (prev_set))))
    return true;

  if (GET_CODE (SET_SRC (prev_set)) == HIGH
      && (GET_CODE (SET_SRC (curr_set)) == SIGN_EXTEND
	  || GET_CODE (SET_SRC (curr_set)) == ZERO_EXTEND)
      && MEM_P (XEXP (SET_SRC (curr_set), 0))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && (GET_CODE (XEXP (XEXP (SET_SRC (curr_set), 0), 0)) == LO_SUM
	  && REG_P (XEXP (XEXP (XEXP (SET_SRC (curr_set), 0), 0), 0))
	  && (REGNO (XEXP (XEXP (XEXP (SET_SRC (curr_set), 0), 0), 0))
	      == REGNO (SET_DEST (prev_set)))))
    return true;

  return false;
}

/* Check for RISCV_FUSE_AUIPC_LD fusion.
   prev (auipc) == (set (reg:DI rD) (unspec:DI UNSPEC_AUIPC))
   curr (ld)    == (set (reg:DI rD) (mem:DI (plus:DI (reg:DI rD) ...)))  */

static bool
riscv_fuse_auipc_ld (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (!riscv_fusion_same_dest_p (prev_set, curr_set))
    return false;

  if (GET_CODE (SET_SRC (prev_set)) == UNSPEC
      && XINT (SET_SRC (prev_set), 1) == UNSPEC_AUIPC
      && MEM_P (SET_SRC (curr_set))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && GET_CODE (XEXP (SET_SRC (curr_set), 0)) == PLUS)
    return true;

  return false;
}

/* Check for RISCV_FUSE_CACHE_ALIGNED_STD fusion.
   prev (sd) == (set (mem (plus (reg sp|fp) (const_int))) (reg rS1))
   curr (sd) == (set (mem (plus (reg sp|fp) (const_int))) (reg rS2))  */

static bool
riscv_fuse_cache_aligned_std (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (MEM_P (SET_DEST (prev_set))
      && MEM_P (SET_DEST (curr_set))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      /* We can probably relax this condition.  The documentation is a bit
	 unclear about sub-word cases.  So we just model DImode for now.  */
      && GET_MODE (SET_DEST (curr_set)) == DImode
      && GET_MODE (SET_DEST (prev_set)) == DImode)
    {
      rtx base_prev, base_curr, offset_prev, offset_curr;

      extract_base_offset_in_addr (SET_DEST (prev_set),
				   &base_prev, &offset_prev);
      extract_base_offset_in_addr (SET_DEST (curr_set),
				   &base_curr, &offset_curr);

      /* Proceed only if we find both bases, both bases are register and
	 bases are the same register.  */
      if (base_prev != NULL_RTX && base_curr != NULL_RTX
	  && REG_P (base_prev) && REG_P (base_curr)
	  && REGNO (base_prev) == REGNO (base_curr)
	  /* The alignment of the base pointer is more useful than the
	     alignment of the memory reference for determining if we're
	     on opposite sides of a cache line.  */
	  && REGNO_POINTER_ALIGN (ORIGINAL_REGNO (base_prev)) >= 128)
	{
	  /* The two stores must be contained within opposite halves of
	     the same 16 byte aligned block of memory.  We know the
	     pointer has suitable alignment, so we just need to check
	     the offsets of the two stores for suitable alignment.  */

	  /* Get the smaller offset into OFFSET_PREV.  */
	  if (INTVAL (offset_prev) > INTVAL (offset_curr))
	    std::swap (offset_prev, offset_curr);

	  /* We have a match if the smaller offset (OFFSET_PREV) is 16
	     byte aligned and the higher offset is 8 bytes more than
	     the lower offset.  */
	  if ((INTVAL (offset_prev) % 16) == 0
	      && (INTVAL (offset_prev) + 8 == INTVAL (offset_curr)))
	    return true;
	}
    }

  return false;
}

/* Check for RISCV_FUSE_ALIGNED_STD fusion.  More general form of
   RISCV_FUSE_CACHE_ALIGNED_STD.  The dependency on the stores being
   opposite halves of a cache line is dropped.  Instead the lowest
   address needs 2X the alignment of the object and the higher address
   immediately follows the first object.  */

static bool
riscv_fuse_aligned_std (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (MEM_P (SET_DEST (prev_set))
      && SCALAR_INT_MODE_P (GET_MODE (SET_DEST (curr_set)))
      && MEM_P (SET_DEST (curr_set))
      /* Stores must have the same width.  */
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
	    return true;
	}
    }

  return false;
}

/* Check for RISCV_FUSE_BFEXT fusion.
   prev (slli) == (set (reg:DI rD) (ashift:DI (reg:DI rS) (const_int)))
   curr (srli) == (set (reg:DI rD) (lshiftrt:DI (reg:DI rD) (const_int)))  */

static bool
riscv_fuse_bfext (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (!riscv_fusion_same_dest_p (prev_set, curr_set))
    return false;

  if (GET_CODE (SET_SRC (prev_set)) == ASHIFT
      && (GET_CODE (SET_SRC (curr_set)) == LSHIFTRT
	  || GET_CODE (SET_SRC (curr_set)) == ASHIFTRT)
      && REG_P (SET_DEST (prev_set))
      && REG_P (SET_DEST (curr_set))
      && REGNO (XEXP (SET_SRC (curr_set), 0)) == REGNO (SET_DEST (prev_set))
      && CONST_INT_P (XEXP (SET_SRC (prev_set), 1))
      && CONST_INT_P (XEXP (SET_SRC (curr_set), 1)))
    return true;

  return false;
}

/* Check for RISCV_FUSE_B_ALUI fusion.
   Covers orc.b+not, ctz+andi, sub+smax, neg+smax patterns.  */

static bool
riscv_fuse_b_alui (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (!riscv_fusion_same_dest_p (prev_set, curr_set))
    return false;

  /* orc.b + not.  */
  if (GET_CODE (SET_SRC (prev_set)) == UNSPEC
      && GET_CODE (SET_SRC (curr_set)) == NOT
      && XINT (SET_SRC (prev_set), 1) == UNSPEC_ORC_B
      && REG_P (SET_DEST (prev_set))
      && REG_P (SET_DEST (curr_set))
      && REG_P (XEXP (SET_SRC (curr_set), 0))
      && REGNO (XEXP (SET_SRC (curr_set), 0)) == REGNO (SET_DEST (prev_set)))
    return true;

  /* ctz + andi.  */
  if (GET_CODE (SET_SRC (prev_set)) == CTZ
      && GET_CODE (SET_SRC (curr_set)) == AND
      && CONST_INT_P (XEXP (SET_SRC (curr_set), 1))
      && INTVAL (XEXP (SET_SRC (curr_set), 1)) == 63
      && REG_P (SET_DEST (prev_set))
      && REG_P (SET_DEST (curr_set))
      && REG_P (XEXP (SET_SRC (curr_set), 0))
      && REGNO (XEXP (SET_SRC (curr_set), 0)) == REGNO (SET_DEST (prev_set)))
    return true;

  /* sub + smax (abs pattern).  */
  if (GET_CODE (SET_SRC (prev_set)) == MINUS
      && (XEXP (SET_SRC (prev_set), 0)
	  == CONST0_RTX (GET_MODE (SET_SRC (prev_set))))
      && GET_CODE (SET_SRC (curr_set)) == SMAX
      && REG_P (SET_DEST (prev_set))
      && REG_P (SET_DEST (curr_set))
      && REG_P (XEXP (SET_SRC (curr_set), 0))
      && REGNO (XEXP (SET_SRC (curr_set), 0)) == REGNO (SET_DEST (prev_set))
      && REG_P (XEXP (SET_SRC (prev_set), 1))
      && REG_P (XEXP (SET_SRC (curr_set), 1))
      && (REGNO (XEXP (SET_SRC (prev_set), 1))
	  == REGNO (XEXP (SET_SRC (curr_set), 1))))
    return true;

  /* neg + smax (abs pattern).  */
  if (GET_CODE (SET_SRC (prev_set)) == NEG
      && GET_CODE (SET_SRC (curr_set)) == SMAX
      && REG_P (SET_DEST (prev_set))
      && REG_P (SET_DEST (curr_set))
      && REG_P (XEXP (SET_SRC (curr_set), 0))
      && REGNO (XEXP (SET_SRC (curr_set), 0)) == REGNO (SET_DEST (prev_set))
      && REG_P (XEXP (SET_SRC (prev_set), 0))
      && REG_P (XEXP (SET_SRC (curr_set), 1))
      && (REGNO (XEXP (SET_SRC (prev_set), 0))
	  == REGNO (XEXP (SET_SRC (curr_set), 1))))
    return true;

  return false;
}

/* Check for RISCV_FUSE_MULT_ADD fusion.
   On RV32:
   prev (mul) == (set (reg rD) (mult:SI (reg:SI rS1) (reg:SI rS2)))
   curr (add) == (set (reg rD) (plus:SI (reg:SI rD) (reg:SI rS3)))

   On RV64 the result may be sign-extended to DI:
   prev (mul) == (set (reg:DI rD) (sign_extend:DI (mult:SI ...)))
   curr (add) == (set (reg:DI rD) (sign_extend:DI (plus:SI ...)))  */

static bool
riscv_fuse_mult_add (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set)
    return false;

  rtx prev_src = SET_SRC (prev_set);
  rtx curr_src = SET_SRC (curr_set);
  if (GET_CODE (prev_src) == SIGN_EXTEND
      && GET_MODE (prev_src) == DImode
      && GET_MODE (XEXP (prev_src, 0)) == SImode)
    prev_src = XEXP (prev_src, 0);
  if (GET_CODE (curr_src) == SIGN_EXTEND
      && GET_MODE (curr_src) == DImode
      && GET_MODE (XEXP (curr_src, 0)) == SImode)
    curr_src = XEXP (curr_src, 0);

  if (GET_CODE (prev_src) != MULT || GET_MODE (prev_src) != SImode
      || GET_CODE (curr_src) != PLUS || GET_MODE (curr_src) != SImode)
    return false;

  rtx mult_dest = SET_DEST (prev_set);
  if (!REG_P (mult_dest))
    return false;
  unsigned int mult_dest_regno = REGNO (mult_dest);

  /* Check if multiply result is used in either operand of the addition.  */
  if (REG_P (XEXP (curr_src, 0))
      && REGNO (XEXP (curr_src, 0)) == mult_dest_regno)
    return true;

  if (REG_P (XEXP (curr_src, 1))
      && REGNO (XEXP (curr_src, 1)) == mult_dest_regno)
    return true;

  return false;
}

/* Check for RISCV_FUSE_LI_BRANCH fusion.
   prev (li)     == (set (reg:DI rD) (const_int N))
   curr (branch) == conditional branch using rD  */

static bool
riscv_fuse_li_branch (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set)
    return false;

  if (get_attr_type (prev) != TYPE_MOVE
      || get_attr_move_type (prev) != MOVE_TYPE_CONST)
    return false;

  if (!any_condjump_p (curr))
    return false;

  rtx prev_dest = SET_DEST (prev_set);
  if (!REG_P (prev_dest))
    return false;

  /* Check if the loaded register is used in the branch condition.  */
  rtx cond = XEXP (SET_SRC (curr_set), 0);
  unsigned int prev_dest_regno = REGNO (prev_dest);
  if ((REG_P (XEXP (cond, 0)) && REGNO (XEXP (cond, 0)) == prev_dest_regno)
      || (REG_P (XEXP (cond, 1)) && REGNO (XEXP (cond, 1)) == prev_dest_regno))
    return true;

  return false;
}

/* Check for RISCV_FUSE_ADJACENT_LOAD fusion.
   prev (ld) == (set (reg:SI rD1) (mem:SI (plus:DI (reg:DI rB) (const_int OFF1))))
   curr (ld) == (set (reg:SI rD2) (mem:SI (plus:DI (reg:DI rB) (const_int OFF2))))
   where OFF2 == OFF1 + 4 or OFF2 == OFF1 - 4  */

static bool
riscv_fuse_adjacent_load (rtx_insn *prev, rtx_insn *curr)
{
  /* Do not fuse loads/stores before sched2.  */
  if (!reload_completed || sched_fusion)
    return false;

  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (get_attr_type (prev) != TYPE_LOAD
      || get_attr_type (curr) != TYPE_LOAD)
    return false;

  return riscv_adjacent_memops_p (SET_SRC (prev_set), SET_SRC (curr_set), true);
}

/* Check for RISCV_FUSE_ADJACENT_STORE fusion.
   prev (st) == (set (mem:SI (plus:DI (reg:DI rB) (const_int OFF1))) (reg:SI rS1))
   curr (st) == (set (mem:SI (plus:DI (reg:DI rB) (const_int OFF2))) (reg:SI rS2))
   where OFF2 == OFF1 + MODE_SIZE or OFF2 == OFF1 - MODE_SIZE  */

static bool
riscv_fuse_adjacent_store (rtx_insn *prev, rtx_insn *curr)
{
  /* Do not fuse loads/stores before sched2.  */
  if (!reload_completed || sched_fusion)
    return false;

  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (get_attr_type (prev) != TYPE_STORE
      || get_attr_type (curr) != TYPE_STORE)
    return false;

  return riscv_adjacent_memops_p (SET_DEST (prev_set), SET_DEST (curr_set), false);
}

/* Check for RISCV_FUSE_LS_UPDATE fusion (load/store with address update).
   Covers both LD+ADDI and ADDI+ST patterns.
   prev (ld)   == (set (reg:DI rD) (mem:DI (reg:DI rA)))
   curr (addi) == (set (reg:DI rA) (plus:DI (reg:DI rA) (const_int)))
   OR
   prev (addi) == (set (reg:DI rA) (plus:DI (reg:DI rA) (const_int)))
   curr (st)   == (set (mem:DI (reg:DI rA)) (reg:DI rS))  */

static bool
riscv_fuse_ls_update (rtx_insn *prev, rtx_insn *curr)
{
  /* Do not fuse loads/stores before sched2.  */
  if (!reload_completed || sched_fusion)
    return false;

  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  /* Look ahead 1 insn to prioritize adjacent load/store pairs.  */
  if (riscv_defer_for_adjacent_memop_p (curr))
    return false;

  /* Match a memory access followed by a dependent arithmetic op, or the
     arithmetic op followed by the memory access (load+op, op+load,
     store+op, op+store).  */
  return (riscv_memop_arith_fusion_p (prev, curr)
	  || riscv_memop_arith_fusion_p (curr, prev));
}

static bool
riscv_lui_st_pair_p (rtx_insn *lui, rtx_insn *store, rtx lui_set)
{
  return (get_attr_type (store) == TYPE_STORE
	  && REG_P (SET_DEST (lui_set))
	  && ((get_attr_type (lui) == TYPE_MOVE
	       && GET_CODE (SET_SRC (lui_set)) == HIGH)
	      || (CONST_INT_P (SET_SRC (lui_set))
		  && LUI_OPERAND (INTVAL (SET_SRC (lui_set))))));
}

/* Check for RISCV_FUSE_LUI_ST fusion.
   prev (lui) == (set (reg:DI rD) (const_int UPPER_IMM_20))
   curr (st)  == (set (mem:DI (plus:DI (reg:DI rX) (const_int))) (reg:DI rS))
   OR (reversed)
   prev (st)  == (set (mem:DI (plus:DI (reg:DI rX) (const_int))) (reg:DI rS))
   curr (lui) == (set (reg:DI rD) (const_int UPPER_IMM_20))  */

static bool
riscv_fuse_lui_st (rtx_insn *prev, rtx_insn *curr)
{
  /* Do not fuse loads/stores before sched2.  */
  if (!reload_completed || sched_fusion)
    return false;

  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  /* Look ahead 1 insn to prioritize adjacent load/store pairs.  */
  if (riscv_defer_for_adjacent_memop_p (curr))
    return false;

  /* Check for LUI + store.  */
  if (riscv_lui_st_pair_p (prev, curr, prev_set))
    return true;

  /* Check for store + LUI (reversed).  */
  return riscv_lui_st_pair_p (curr, prev, curr_set);
}

/* Check for RISCV_FUSE_LI_STORE fusion.
   prev (li) == (set (reg:DI rT) (const_int IMM))
   curr (st) == (set (mem:DI (plus:DI (reg:DI rB) (const_int))) (reg:DI rT))  */

static bool
riscv_fuse_li_store (rtx_insn *prev, rtx_insn *curr)
{
  /* Do not fuse loads/stores before sched2.  */
  if (!reload_completed || sched_fusion)
    return false;

  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  /* Look ahead 1 insn to prioritize adjacent load/store pairs.  */
  if (riscv_defer_for_adjacent_memop_p (curr))
    return false;

  if (get_attr_type (prev) == TYPE_MOVE
      && get_attr_move_type (prev) == MOVE_TYPE_CONST
      && get_attr_type (curr) == TYPE_STORE
      && REG_P (SET_SRC (curr_set)) && REG_P (SET_DEST (prev_set))
      && REGNO (SET_SRC (curr_set)) == REGNO (SET_DEST (prev_set)))
    return true;

  return false;
}

/* Check for RISCV_FUSE_LUI_LD_REV fusion (reversed LUI+LD).
   prev (ld)  == (set (reg:DI rD1) (mem:DI (plus:DI (reg:DI rX) (const_int IMM12))))
   curr (lui) == (set (reg:DI rD2) (const_int UPPER_IMM_20))
   where rD1 != rD2  */

static bool
riscv_fuse_lui_ld_rev (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);
  if (!prev_set || !curr_set || any_condjump_p (curr))
    return false;

  if (get_attr_type (prev) == TYPE_LOAD
      && REG_P (SET_DEST (prev_set))
      && REG_P (SET_DEST (curr_set))
      && (GET_CODE (SET_SRC (curr_set)) == HIGH
	  || (CONST_INT_P (SET_SRC (curr_set))
	      && LUI_OPERAND (INTVAL (SET_SRC (curr_set)))))
      && REGNO (SET_DEST (prev_set)) != REGNO (SET_DEST (curr_set)))
    return true;

  return false;
}

/* Type for a fusion checker function.  Takes the two candidate insns
   and returns true if they should be fused.  */

typedef bool (*fusion_checker_fn) (rtx_insn *, rtx_insn *);

/* Descriptor for a single fusion rule.  */

struct riscv_fusion_entry
{
  /* The fusion operation flag to check enablement.  For entries that
     check multiple flags (ZEXTW/ZEXTWS), use the bitwise OR.  */
  unsigned int op_flags;

  /* The checker function.  */
  fusion_checker_fn checker;

  /* The fusion type name used in dump output.  */
  const char *fusion_type;
};

/* Table of all fusion rules.  */

static const struct riscv_fusion_entry riscv_fusion_table[] =
{
  { RISCV_FUSE_ZEXTW | RISCV_FUSE_ZEXTWS,
    riscv_fuse_zextws, "RISCV_FUSE_ZEXTWS" },
  { RISCV_FUSE_ZEXTH,
    riscv_fuse_zexth, "RISCV_FUSE_ZEXTH" },
  { RISCV_FUSE_LDINDEXED,
    riscv_fuse_ldindexed, "RISCV_FUSE_LDINDEXED" },
  { RISCV_FUSE_EXPANDED_LD,
    riscv_fuse_expanded_ld, "RISCV_FUSE_EXPANDED_LD" },
  { RISCV_FUSE_LDPREINCREMENT,
    riscv_fuse_ldpreincrement, "RISCV_FUSE_LDPREINCREMENT" },
  { RISCV_FUSE_LUI_ADDI,
    riscv_fuse_lui_addi, "RISCV_FUSE_LUI_ADDI" },
  { RISCV_FUSE_AUIPC_ADDI,
    riscv_fuse_auipc_addi, "RISCV_FUSE_AUIPC_ADDI" },
  { RISCV_FUSE_LUI_LD,
    riscv_fuse_lui_ld, "RISCV_FUSE_LUI_LD" },
  { RISCV_FUSE_AUIPC_LD,
    riscv_fuse_auipc_ld, "RISCV_FUSE_AUIPC_LD" },
  { RISCV_FUSE_CACHE_ALIGNED_STD,
    riscv_fuse_cache_aligned_std, "RISCV_FUSE_CACHE_ALIGNED_STD" },
  { RISCV_FUSE_ALIGNED_STD,
    riscv_fuse_aligned_std, "RISCV_FUSE_ALIGNED_STD" },
  { RISCV_FUSE_BFEXT,
    riscv_fuse_bfext, "RISCV_FUSE_BFEXT" },
  { RISCV_FUSE_B_ALUI,
    riscv_fuse_b_alui, "RISCV_FUSE_B_ALUI" },
  { RISCV_FUSE_MULT_ADD,
    riscv_fuse_mult_add, "RISCV_FUSE_MULT_ADD" },
  { RISCV_FUSE_LI_BRANCH,
    riscv_fuse_li_branch, "RISCV_FUSE_LI_BRANCH" },
  { RISCV_FUSE_ADJACENT_LOAD,
    riscv_fuse_adjacent_load, "RISCV_FUSE_ADJACENT_LOAD" },
  { RISCV_FUSE_ADJACENT_STORE,
    riscv_fuse_adjacent_store, "RISCV_FUSE_ADJACENT_STORE" },
  { RISCV_FUSE_LS_UPDATE,
    riscv_fuse_ls_update, "RISCV_FUSE_LS_UPDATE" },
  { RISCV_FUSE_LUI_ST,
    riscv_fuse_lui_st, "RISCV_FUSE_LUI_ST" },
  { RISCV_FUSE_LI_STORE,
    riscv_fuse_li_store, "RISCV_FUSE_LI_STORE" },
  { RISCV_FUSE_LUI_LD_REV,
    riscv_fuse_lui_ld_rev, "RISCV_FUSE_LUI_LD_REV" },
};

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

  for (size_t i = 0; i < ARRAY_SIZE (riscv_fusion_table); i++)
    {
      const struct riscv_fusion_entry *entry = &riscv_fusion_table[i];

      /* Check if this fusion type is enabled.  */
      if (!(riscv_get_fusible_ops () & entry->op_flags))
	continue;

      if (entry->checker (prev, curr))
	{
	  if (dump_file)
	    fprintf (dump_file, "%s\n", entry->fusion_type);
	  return true;
	}
    }

  return false;
}
