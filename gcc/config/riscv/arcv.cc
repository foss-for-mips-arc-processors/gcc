/* Subroutines used for code generation for ARC-V processors.
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

/* Check if RTX matches multiply-high pattern:
   (set (reg:DI DEST)
    (truncate:DI (lshiftrt:TI (mult:TI (extend:TI (OP0))
					(extend:TI (OP1)))
				(const_int 64)))  */

static bool
is_multiply_high_pattern_p (rtx src)
{
  if (GET_CODE (src) != SET)
    return false;
  rtx truncate = SET_SRC (src);

  if (GET_CODE (truncate) != TRUNCATE)
    return false;

  rtx lshiftrt = XEXP (truncate, 0);
  if (GET_CODE (lshiftrt) != LSHIFTRT)
    return false;

  rtx shift_amount = XEXP (lshiftrt, 1);
  rtx mult = XEXP (lshiftrt, 0);

  if (GET_CODE (shift_amount) != CONST_INT || INTVAL (shift_amount) != 64)
    return false;

  if (GET_CODE (mult) != MULT)
    return false;

  return true;
}

/* Extract register operands and destinition from multiply high-part pattern.
  returns true if successful.
*/

static bool
get_mulh_operands (rtx set_rtx, rtx *op0, rtx *op1, rtx *dest)
{
  if (!is_multiply_high_pattern_p (set_rtx)) return false;

  rtx mulh_pattern = SET_SRC (set_rtx);

  rtx lshiftrt = XEXP (mulh_pattern, 0);
  rtx mult = XEXP (lshiftrt, 0);

  rtx operand0 = XEXP (mult, 0);
  rtx operand1 = XEXP (mult, 1);

  /* Strip zero_extend/sign_extend.  */
  if (GET_CODE (operand0) == ZERO_EXTEND || GET_CODE (operand0) == SIGN_EXTEND)
    operand0 = XEXP (operand0, 0);
  if (GET_CODE (operand1) == ZERO_EXTEND || GET_CODE (operand1) == SIGN_EXTEND)
    operand1 = XEXP (operand1, 0);

  /* Strip subreg.  */
  if (GET_CODE (operand0) == SUBREG)
    operand0 = SUBREG_REG (operand0);
  if (GET_CODE (operand1) == SUBREG)
    operand1 = SUBREG_REG (operand1);

  if (!REG_P (operand0) || !REG_P (operand1))
    return false;

  rtx dest_reg = SET_DEST (set_rtx);
  if (!REG_P (dest_reg))
    return false;

  *op0 = operand0;
  *op1 = operand1;
  *dest = dest_reg;
  return true;
}

bool
arcv_macro_bonded_mul_pair_p (rtx_insn *prev, rtx_insn *curr)
{
  rtx prev_set = single_set (prev);
  rtx curr_set = single_set (curr);

  /* Bond mul hi part and mul low part pair:
     prev: (set rd_hi (mulh(u/s) rs1 rs2))
     curr: (set rd_lo (mul rs1 rs2))
     where rd_hi != rs1 && rd_hi != rs2.  */
  if (prev_set && curr_set
      && GET_CODE (SET_SRC (curr_set)) == MULT)
    {
      rtx prev_op0, prev_op1, prev_dest, curr_dest;
      if (get_mulh_operands (prev_set, &prev_op0, &prev_op1, &prev_dest))
	{
	  rtx curr_src = SET_SRC (curr_set);
	  curr_dest = SET_DEST (curr_set);

	  rtx curr_op0 = XEXP (curr_src, 0);
	  rtx curr_op1 = XEXP (curr_src, 1);

	  if (REG_P (prev_op0) && REG_P (prev_op1)
		&& REG_P (curr_op0) && REG_P (curr_op1)
		&& REGNO (prev_op0) == REGNO (curr_op0)
		&& REGNO (prev_op1) == REGNO (curr_op1)
		&& REGNO (prev_dest) != REGNO (prev_op0)
		&& REGNO (prev_dest) != REGNO (prev_op1))
	    {
	      if (dump_file)
		fprintf (dump_file,
		      "ARCV_BONDED_MUL_HI_LO_PAIR high part: %d, low part: %d\n",
		      INSN_UID (prev),
		      INSN_UID (curr));
	      return true;
	    }
	}
    }

  return false;
}

bool
arcv_rpx100_depends_on_lowpart_bonded_mul (rtx_insn *insn, int dep_type, rtx_insn *dep_insn)
{
  if (dep_type != REG_DEP_TRUE)
    return false;

  rtx_insn *prev_insn = prev_nondebug_insn (dep_insn);
  if (!prev_insn)
    return false;

  if (!arcv_macro_bonded_mul_pair_p (prev_insn, dep_insn))
    return false;

  if (dump_file)
    fprintf (dump_file,
	"ARCV_BONDED_MUL_ADJUST_COST\t insn: %d, high_part: %d, low_part: %d\n",
	INSN_UID (insn), INSN_UID (prev_insn), INSN_UID (dep_insn));

  return true;
}

/* Adjust scheduling cost for ARCV fusion.  */

int
arcv_sched_adjust_cost (rtx_insn *insn, int dep_type, rtx_insn *dep_insn, int cost)
{
  /* Check for bonded 64-bit multiply pair on arcv_rpx100.  */
  if (riscv_microarchitecture == arcv_rpx100
      && arcv_rpx100_depends_on_lowpart_bonded_mul (insn, dep_type, dep_insn))
    return cost - 1;

  if (dep_type == REG_DEP_ANTI && !SCHED_GROUP_P (insn))
    return cost + 1;

  return cost;
}
