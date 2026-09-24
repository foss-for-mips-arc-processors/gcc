/* Subroutines for RISC-V P (Packed SIMD) Extension for GNU compiler.
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
#include "gimple.h"
#include "tm_p.h"
#include "optabs.h"
#include "recog.h"
#include "diagnostic-core.h"
#include "expr.h"
#include "explow.h"
#include "insn-config.h"
#include "insn-attr.h"
#include "emit-rtl.h"
#include "optabs-tree.h"

/* Expand RVP vector comparison.
   Implements vec_cmp<mode><mode> and vec_cmpu<mode><mode> patterns.  */
void
riscv_p_expand_vec_cmp (rtx *operands)
{
  enum rtx_code code = GET_CODE (operands[1]);
  rtx result = operands[0];
  rtx op1 = operands[2];
  rtx op2 = operands[3];
  machine_mode mode = GET_MODE (result);
  rtx tmp;

  switch (code)
    {
    case EQ:
      emit_move_insn (result, gen_rtx_EQ (mode, op1, op2));
      break;

    case NE:
      /* result = ~(op1 == op2) */
      tmp = gen_reg_rtx (mode);
      emit_move_insn (tmp, gen_rtx_EQ (mode, op1, op2));
      emit_insn (gen_rtx_SET (result, gen_rtx_NOT (mode, tmp)));
      break;

    case LT:
    case LTU:
      emit_move_insn (result, gen_rtx_fmt_ee (code, mode, op1, op2));
      break;

    case LE:
    case LEU:
      {
	/* result = ~(op2 < op1) */
	enum rtx_code base_code = (code == LE) ? LT : LTU;
	tmp = gen_reg_rtx (mode);
	emit_move_insn (tmp, gen_rtx_fmt_ee (base_code, mode, op2, op1));
	emit_insn (gen_rtx_SET (result, gen_rtx_NOT (mode, tmp)));
      }
      break;

    case GT:
    case GTU:
      {
	/* result = (op2 < op1) */
	enum rtx_code base_code = (code == GT) ? LT : LTU;
	emit_move_insn (result, gen_rtx_fmt_ee (base_code, mode, op2, op1));
      }
      break;

    case GE:
    case GEU:
      {
	/* result = ~(op1 < op2) */
	enum rtx_code base_code = (code == GE) ? LT : LTU;
	tmp = gen_reg_rtx (mode);
	emit_move_insn (tmp, gen_rtx_fmt_ee (base_code, mode, op1, op2));
	emit_insn (gen_rtx_SET (result, gen_rtx_NOT (mode, tmp)));
      }
      break;

    default:
      gcc_unreachable ();
    }
}

/* Expand RVP vector conditional mask operation.
   Implements vcond_mask_<mode><mode> pattern.

   Implements: result = mask ? op1 : op2
   For each element i: result[i] = mask[i] ? op1[i] : op2[i]

   Optimizations:
   1. If (op1 == -1 && op2 == 0): result = mask
   2. If (op1 == 0 && op2 == -1): result = ~mask
   3. General case: result = (mask & op1) | (~mask & op2)  */
void
riscv_p_expand_vcond_mask (rtx *operands)
{
  rtx result = operands[0];
  rtx op1 = operands[1];
  rtx op2 = operands[2];
  rtx mask = operands[3];
  machine_mode mode = GET_MODE (result);

  /* Optimize: mask ? -1 : 0 -> mask */
  if (op1 == CONSTM1_RTX (mode) && op2 == CONST0_RTX (mode))
    {
      emit_move_insn (result, mask);
      return;
    }

  /* Optimize: mask ? 0 : -1 -> ~mask */
  if (op1 == CONST0_RTX (mode) && op2 == CONSTM1_RTX (mode))
    {
      emit_insn (gen_rtx_SET (result, gen_rtx_NOT (mode, mask)));
      return;
    }

  /* GENERAL CASE: result = (mask & op1) | (~mask & op2)
     Use vector bitwise operations directly.  */

  /* Handle constant operands - copy them into registers.  */
  if (CONST_VECTOR_P (op1))
    op1 = force_reg (mode, op1);
  if (CONST_VECTOR_P (op2))
    op2 = force_reg (mode, op2);

  rtx not_mask = gen_reg_rtx (mode);
  rtx tmp1 = gen_reg_rtx (mode);
  rtx tmp2 = gen_reg_rtx (mode);

  /* not_mask = ~mask */
  emit_insn (gen_rtx_SET (not_mask, gen_rtx_NOT (mode, mask)));

  /* tmp1 = mask & op1 */
  emit_insn (gen_rtx_SET (tmp1, gen_rtx_AND (mode, mask, op1)));

  /* tmp2 = ~mask & op2 */
  emit_insn (gen_rtx_SET (tmp2, gen_rtx_AND (mode, not_mask, op2)));

  /* result = tmp1 | tmp2 */
  emit_insn (gen_rtx_SET (result, gen_rtx_IOR (mode, tmp1, tmp2)));
}

static rtx
build_sel_parallel (const unsigned N, const int *idx)
{
  rtvec v = rtvec_alloc (N);
  for (unsigned i = 0; i < N; ++i)
    RTVEC_ELT (v, i) = GEN_INT (idx[i]);
  return gen_rtx_PARALLEL (VOIDmode, v);
}

/* Helper function to emit zip pattern with vec_merge */
template<unsigned N>
void emit_vec_merge_with_select (rtx target, machine_mode vmode,
                                 rtx op0, rtx op1, const int *idx,
                                 const int mask)
{
  rtx sel0 = build_sel_parallel (N, idx);
  rtx sel1 = build_sel_parallel (N, idx);
  emit_insn (gen_rtx_SET (target,
             gen_rtx_VEC_MERGE (vmode,
                                gen_rtx_VEC_SELECT (vmode, op1, sel1),
                                gen_rtx_VEC_SELECT (vmode, op0, sel0),
                                GEN_INT (mask))));
}

/* Helper function to emit unzip pattern with vec_concat */
template<unsigned N>
void emit_vec_concat_with_select (rtx target, machine_mode vmode,
                                  machine_mode sel_mode,
                                  rtx op0, rtx op1, const int *idx)
{
  rtx sel0 = build_sel_parallel (N/2, idx);
  rtx sel1 = build_sel_parallel (N/2, idx);
  emit_insn (gen_rtx_SET (target,
             gen_rtx_VEC_CONCAT (vmode,
                                 gen_rtx_VEC_SELECT (sel_mode, op0, sel0),
                                 gen_rtx_VEC_SELECT (sel_mode, op1, sel1))));
}

/* Emit ppair RTL pattern for 2-element vectors using vec_merge/vec_select.
   Supports both PV2HI and PV2SI modes.
   op0_odd/op1_odd: false = even selector {0,0}, true = odd selector {1,1}

   Patterns:
   - ppaire:  op0_odd=false, op1_odd=false (even/even)
   - ppaireo: op0_odd=false, op1_odd=true  (even/odd)
   - ppairoe: op0_odd=true,  op1_odd=false (odd/even)
   - ppairo:  op0_odd=true,  op1_odd=true  (odd/odd)  */

static void
riscv_emit_ppair_2_elem (rtx target, machine_mode vmode, rtx op0, rtx op1,
                         bool op0_odd, bool op1_odd)
{
  /* On RV32, PV2SI is a register pair; implement as two SImode moves. */
  if (!TARGET_64BIT && vmode == PV2SImode)
    {
      rtx src0 = op0_odd ? gen_highpart (SImode, op0) : gen_lowpart (SImode, op0);
      rtx src1 = op1_odd ? gen_highpart (SImode, op1) : gen_lowpart (SImode, op1);
      emit_move_insn (gen_lowpart (SImode, target), src0);
      emit_move_insn (gen_highpart (SImode, target), src1);
      return;
    }

  int base0 = op0_odd ? 1 : 0;
  int base1 = op1_odd ? 1 : 0;
  const int nelems = 2;
  const int mask = 0b10;

  rtx sel0 = gen_rtx_PARALLEL (VOIDmode,
                               gen_rtvec (nelems, GEN_INT (base0), GEN_INT (base0)));
                                          
  rtx sel1 = gen_rtx_PARALLEL (VOIDmode,
                               gen_rtvec (nelems, GEN_INT (base1), GEN_INT (base1)));

  rtx vec_sel_op0 = gen_rtx_VEC_SELECT (vmode, op0, sel0);
  rtx vec_sel_op1 = gen_rtx_VEC_SELECT (vmode, op1, sel1);

  rtx result = gen_rtx_VEC_MERGE (vmode, vec_sel_op1, vec_sel_op0,
                                  GEN_INT (mask));

  emit_insn (gen_rtx_SET (target, result));
}

/* Emit ppair RTL pattern for 4-element vectors using vec_merge/vec_select.
   Supports both PV4QI and PV4HI modes.
   op0_odd/op1_odd: false = even selector {0,0,2,2}, true = odd selector {1,1,3,3}

   Patterns:
   - ppaire:  op0_odd=false, op1_odd=false (even/even)
   - ppaireo: op0_odd=false, op1_odd=true  (even/odd)
   - ppairoe: op0_odd=true,  op1_odd=false (odd/even)
   - ppairo:  op0_odd=true,  op1_odd=true  (odd/odd)  */

static void
riscv_emit_ppair_4_elem (rtx target, machine_mode vmode, rtx op0, rtx op1,
                         bool op0_odd, bool op1_odd)
{
  int base0 = op0_odd ? 1 : 0;
  int base1 = op1_odd ? 1 : 0;
  const int nelems = 4;
  const int elem_offset = 2;
  const int mask = 0b1010;

  rtx sel0 = gen_rtx_PARALLEL (VOIDmode,
                               gen_rtvec (nelems, GEN_INT (base0), GEN_INT (base0),
                                           GEN_INT (base0 + elem_offset),
                                           GEN_INT (base0 + elem_offset)));

  rtx sel1 = gen_rtx_PARALLEL (VOIDmode,
                               gen_rtvec (nelems, GEN_INT (base1), GEN_INT (base1),
                                           GEN_INT (base1 + elem_offset),
                                           GEN_INT (base1 + elem_offset)));

  rtx vec_sel_op0 = gen_rtx_VEC_SELECT (vmode, op0, sel0);
  rtx vec_sel_op1 = gen_rtx_VEC_SELECT (vmode, op1, sel1);

  rtx result = gen_rtx_VEC_MERGE (vmode, vec_sel_op1, vec_sel_op0,
                                  GEN_INT (mask));

  emit_insn (gen_rtx_SET (target, result));
}

/* Return a PV8QI holding OP0 in its low half and OP1 in its high half.  */

static rtx
riscv_concat_pv4qi (rtx op0, rtx op1)
{
  if (TARGET_64BIT)
    {
      rtx packed = gen_reg_rtx (PV2SImode);
      emit_insn (gen_rtx_SET (packed,
			      gen_rtx_VEC_CONCAT (PV2SImode,
						  gen_lowpart (SImode, op0),
						  gen_lowpart (SImode, op1))));
      return gen_lowpart (PV8QImode, packed);
    }

  rtx wide = gen_reg_rtx (PV8QImode);
  emit_move_insn (gen_lowpart (PV4QImode, wide), op0);
  emit_move_insn (gen_highpart (PV4QImode, wide), op1);
  return wide;
}

/* Return the high PV4QI half of the PV8QI value WIDE.  */

static rtx
riscv_pv8qi_highpart (rtx wide)
{
  if (!TARGET_64BIT)
    return gen_highpart (PV4QImode, wide);

  /* validate_subreg rejects a non-lowpart 4-byte subreg of a 64-bit pseudo.  */
  rtx shifted = gen_reg_rtx (DImode);
  emit_insn (gen_lshrdi3 (shifted, gen_lowpart (DImode, wide), GEN_INT (32)));
  return gen_lowpart (PV4QImode, shifted);
}

static void
riscv_emit_zip_4_elem (rtx target, machine_mode vmode, rtx op0, rtx op1,
                       const int *indices)
{
  /* zip8p/wzip8p interleaves all eight bytes of the two 32-bit sources; the
     low half of that is the even zip and the high half is the odd one.  */
  if (vmode == PV4QImode)
    {
      rtx wide = gen_reg_rtx (PV8QImode);
      emit_insn (gen_riscv_zip8p_pv4qi (wide, op0, op1));
      emit_move_insn (target, indices[0] >= 2 ? riscv_pv8qi_highpart (wide)
					      : gen_lowpart (PV4QImode, wide));
      return;
    }

  /* On RV32, PV4HI is a register pair; zip from lower or upper halfword halves. */
  if (!TARGET_64BIT && vmode == PV4HImode)
    {
      /* zip16p (indices[0]==0): from lower halves; zip16hp (indices[0]==2): upper. */
      bool use_hi = (indices[0] >= 2);
      machine_mode hmode = PV2HImode;
      rtx a_half = use_hi ? gen_highpart (hmode, op0) : gen_lowpart (hmode, op0);
      rtx b_half = use_hi ? gen_highpart (hmode, op1) : gen_lowpart (hmode, op1);
      rtx res_lo = gen_lowpart (hmode, target);
      rtx res_hi = gen_highpart (hmode, target);
      riscv_emit_ppair_2_elem (res_lo, hmode, a_half, b_half, false, false);
      riscv_emit_ppair_2_elem (res_hi, hmode, a_half, b_half, true, true);
      return;
    }
  const int mask = 0b1010;
  emit_vec_merge_with_select<4> (target, vmode, op0, op1, indices, mask);
}

static void
riscv_emit_unzip_4_elem (rtx target, machine_mode vmode, machine_mode sel_mode,
                         rtx op0, rtx op1, const int *indices)
{
  /* Viewed as PV4HI, the concatenation of the two sources has one halfword per
     source byte pair, so the even unzip is the low byte of each halfword and
     the odd unzip is the high byte.  */
  if (vmode == PV4QImode)
    {
      rtx wide = gen_lowpart (PV4HImode, riscv_concat_pv4qi (op0, op1));
      if (indices[0] != 0)
	emit_insn (gen_riscv_pncvth_b (target, wide));
      else
	emit_insn (gen_truncpv4hipv4qi2 (target, wide));
      return;
    }

  /* On RV32, PV4HI is a register pair; unzip by applying ppair across halves. */
  if (!TARGET_64BIT && vmode == PV4HImode)
    {
      /* unzip16p (indices[0]==0): even halfwords; unzip16hp (indices[0]==1): odd. */
      bool use_odd = (indices[0] != 0);
      machine_mode hmode = PV2HImode;
      rtx a_lo = gen_lowpart (hmode, op0);
      rtx a_hi = gen_highpart (hmode, op0);
      rtx b_lo = gen_lowpart (hmode, op1);
      rtx b_hi = gen_highpart (hmode, op1);
      rtx res_lo = gen_lowpart (hmode, target);
      rtx res_hi = gen_highpart (hmode, target);
      riscv_emit_ppair_2_elem (res_lo, hmode, a_lo, a_hi, use_odd, use_odd);
      riscv_emit_ppair_2_elem (res_hi, hmode, b_lo, b_hi, use_odd, use_odd);
      return;
    }
  emit_vec_concat_with_select<4> (target, vmode, sel_mode, op0, op1, indices);
}

static void
riscv_emit_rev_4_elem (rtx target, machine_mode vmode, rtx op, const int *indices)
{
  /* On RV32, PV4HI is a register pair; decompose the reversal. */
  if (!TARGET_64BIT && vmode == PV4HImode)
    {
      machine_mode hmode = PV2HImode;
      rtx op_lo = gen_lowpart (hmode, op);
      rtx op_hi = gen_highpart (hmode, op);
      rtx res_lo = gen_lowpart (hmode, target);
      rtx res_hi = gen_highpart (hmode, target);
      if (indices[0] == 3)
	{
	  /* Full reverse {3,2,1,0}: swap halves and reverse within each half.
	     ppairoe.h(x,x) = {x[1], x[0]} reverses a PV2HI.  */
	  riscv_emit_ppair_2_elem (res_lo, hmode, op_hi, op_hi, true, false);
	  riscv_emit_ppair_2_elem (res_hi, hmode, op_lo, op_lo, true, false);
	}
      else
	{
	  /* Halfword-pair swap {2,3,0,1}: just swap the two 32-bit halves.  */
	  emit_move_insn (res_lo, op_hi);
	  emit_move_insn (res_hi, op_lo);
	}
      return;
    }
  rtx sel = build_sel_parallel (4, indices);
  rtx result = gen_rtx_VEC_SELECT (vmode, op, sel);
  emit_insn (gen_rtx_SET (target, result));
}

/* Helper function to emit ppairxx.b in PV8QImode which has 8 elements.
 
 ppaire.b RTL pattern for PV8QI mode using vec_merge/vec_select.
   Pattern: rd[0]=op0[0], rd[1]=op1[0], rd[2]=op0[2], rd[3]=op1[2],
            rd[4]=op0[4], rd[5]=op1[4], rd[6]=op0[6], rd[7]=op1[6]  
 ppaireo.b RTL pattern for PV8QI mode using vec_merge/vec_select.
   Pattern: rd[0]=op0[0], rd[1]=op1[1], rd[2]=op0[2], rd[3]=op1[3],
            rd[4]=op0[4], rd[5]=op1[5], rd[6]=op0[6], rd[7]=op1[7]  
 ppairoe.b RTL pattern for PV8QI mode using vec_merge/vec_select.
   Pattern: rd[0]=op0[1], rd[1]=op1[0], rd[2]=op0[3], rd[3]=op1[2],
            rd[4]=op0[5], rd[5]=op1[4], rd[6]=op0[7], rd[7]=op1[6]  
 ppairo.b RTL pattern for PV8QI mode using vec_merge/vec_select.
   Pattern: rd[0]=op0[1], rd[1]=op1[1], rd[2]=op0[3], rd[3]=op1[3],
            rd[4]=op0[5], rd[5]=op1[5], rd[6]=op0[7], rd[7]=op1[7]  */

static void
riscv_emit_ppair_8_elem (rtx target, machine_mode vmode, rtx op0, rtx op1,
                         bool op0_odd, bool op1_odd)
{
  int base0 = op0_odd ? 1 : 0;
  int base1 = op1_odd ? 1 : 0;
  const int nelems = 8;
  const int elem_offset = 2;
  const int mask = 0b10101010;
  rtx sel0 = gen_rtx_PARALLEL (VOIDmode, gen_rtvec (nelems, GEN_INT (base0), GEN_INT (base0),
                                                   GEN_INT (base0 + elem_offset),
                                                   GEN_INT (base0 + elem_offset),
                                                   GEN_INT (base0 + 2*elem_offset),
                                                   GEN_INT (base0 + 2*elem_offset),
                                                   GEN_INT (base0 + 3*elem_offset),
                                                   GEN_INT (base0 + 3*elem_offset)));
  rtx sel1 = gen_rtx_PARALLEL (VOIDmode, gen_rtvec (nelems, GEN_INT (base1), GEN_INT (base1),
                                                   GEN_INT (base1 + elem_offset),
                                                   GEN_INT (base1 + elem_offset),
                                                   GEN_INT (base1 + 2*elem_offset),
                                                   GEN_INT (base1 + 2*elem_offset),
                                                   GEN_INT (base1 + 3*elem_offset),
                                                   GEN_INT (base1 + 3*elem_offset)));
  rtx vec_sel_op0 = gen_rtx_VEC_SELECT (vmode, op0, sel0);
  rtx vec_sel_op1 = gen_rtx_VEC_SELECT (vmode, op1, sel1);

  rtx result = gen_rtx_VEC_MERGE (vmode, vec_sel_op1, vec_sel_op0,
                                 GEN_INT (mask));

  emit_insn (gen_rtx_SET (target, result));
}

static void
riscv_emit_zip_8_elem (rtx target, machine_mode vmode,
                       rtx op0, rtx op1, const int *indices)
{
  const int mask = 0b10101010;
  emit_vec_merge_with_select<8> (target, vmode, op0, op1, indices, mask);
}

static void
riscv_emit_unzip_8_elem (rtx target, machine_mode vmode, machine_mode sel_mode,
                         rtx op0, rtx op1, const int *indices)
{
  emit_vec_concat_with_select<8> (target, vmode, sel_mode, op0, op1, indices);
}

static void
riscv_emit_rev_8_elem (rtx target, machine_mode vmode, rtx op, const int *indices)
{
  /* On RV32, PV8QI is a register pair; decompose the reversal. */
  if (!TARGET_64BIT && vmode == PV8QImode)
    {
      machine_mode hmode = PV4QImode;
      rtx op_lo = gen_lowpart (hmode, op);
      rtx op_hi = gen_highpart (hmode, op);
      rtx res_lo = gen_lowpart (hmode, target);
      rtx res_hi = gen_highpart (hmode, target);
      /* rev8 {7..0}: swap halves and byte-reverse each (needs Zbb rev8).
	 rev16 {6,7,4,5,2,3,0,1}: swap halves and halfword-swap each.  */
      const int rev8_idx[] = {3, 2, 1, 0};
      const int rev16_idx[] = {2, 3, 0, 1};
      const int *half_idx = (indices[0] == 7) ? rev8_idx : rev16_idx;
      riscv_emit_rev_4_elem (res_lo, hmode, op_hi, half_idx);
      riscv_emit_rev_4_elem (res_hi, hmode, op_lo, half_idx);
      return;
    }
  rtx sel = build_sel_parallel (8, indices);
  rtx result = gen_rtx_VEC_SELECT (vmode, op, sel);
  emit_insn (gen_rtx_SET (target, result));
}

typedef enum {
  /* No match pattern found */
  ERROR_MATCH = 0,
  /* Match with the normal pattern */
  NORMAL_MATCH = 1,
  /* Match with the swapped pattern */
  SWAPPED_MATCH = 2
} vec_perm_match_type;

/* Helper function to check if permutation indices match a pattern,
   considering both normal and swapped operand order.
   Returns: 0 if no match, 1 if normal match, 2 if swapped match.  */
static vec_perm_match_type
match_vec_perm_pattern (const int *pattern, unsigned len,
                        const vec_perm_indices &sel)
{
  if (!known_eq (sel.length (), len))
    return ERROR_MATCH;

  /* Try normal pattern match.  */
  bool normal_match = true;
  for (unsigned i = 0; i < len; i++)
    {
      if (!known_eq (sel[i], pattern[i]))
	{
	  normal_match = false;
	  break;
	}
    }
  if (normal_match)
    return NORMAL_MATCH;

  /* Try swapped pattern match.
     For swapped patterns, indices from op0 (< len) become indices from op1 (>= len)
     and vice versa. So we need to check if sel[i] matches pattern[i] with
     operands swapped: if pattern[i] < len, check sel[i] == pattern[i] + len,
     otherwise check sel[i] == pattern[i] - len.  */
  bool swapped_match = true;
  for (int i = 0; i < len; i++)
    {
      int expected = (pattern[i] < len) ? (pattern[i] + len) : (pattern[i] - len);
      if (!known_eq (sel[i], expected))
	{
	  swapped_match = false;
	  break;
	}
    }
  if (swapped_match)
    return SWAPPED_MATCH;

  return ERROR_MATCH;
}

typedef enum {
  /* permutation for ppair.* instructions */
  PAIR_PERM_TYPE = 0,
  /* permutation for zip.* instructions */
  ZIP_PERM_TYPE = 1,
  /* permutation for unzip.* instructions */
  UNZIP_PERM_TYPE = 2,
  /* permutation for rev16 instructions */
  REV_PERM_TYPE = 3
} perm_type_t;

/* Pattern table entry for N-element vector permutations.  */
template<int N>
struct vec_perm_pattern {
  const int indices[N];
  bool op0_odd;
  bool op1_odd;
  perm_type_t perm;
};

/* Supported 2-element vector permutation patterns.
   Only non-swapped patterns are stored; swapped patterns are detected
   and normalized at runtime.  */
static const vec_perm_pattern<2> vec_perm_patterns_2elem[] = {
  /* ppaire: op0_even, op1_even  */
  {{0, 2}, false, false, PAIR_PERM_TYPE},
  /* ppaireo: op0_even, op1_odd  */
  {{0, 3}, false, true, PAIR_PERM_TYPE},
  /* ppairoe: op0_odd, op1_even  */
  {{1, 2}, true, false, PAIR_PERM_TYPE},
  /* ppairo: op0_odd, op1_odd  */
  {{1, 3}, true, true, PAIR_PERM_TYPE}
};

/* Supported 4-element vector permutation patterns.
   Only non-swapped patterns are stored; swapped patterns are detected
   and normalized at runtime.  This table is shared by PV4QImode and
   PV4HImode; every entry applies to both.  */
static const vec_perm_pattern<4> vec_perm_patterns_4elem[] = {
  /* ppaire: op0_even, op1_even  */
  {{0, 4, 2, 6}, false, false, PAIR_PERM_TYPE},
  /* ppaireo: op0_even, op1_odd  */
  {{0, 5, 2, 7}, false, true, PAIR_PERM_TYPE},
  /* ppairoe: op0_odd, op1_even  */
  {{1, 4, 3, 6}, true, false, PAIR_PERM_TYPE},
  /* ppairo: op0_odd, op1_odd  */
  {{1, 5, 3, 7}, true, true, PAIR_PERM_TYPE},
  /* zip16p: don't care the even-odd */
  {{0, 4, 1, 5}, false, false, ZIP_PERM_TYPE},
  /* zip16hp: don't care the even-odd */
  {{2, 6, 3, 7}, false , false, ZIP_PERM_TYPE},
  /* unzip16p: don't care the even-odd */
  {{0, 2, 4, 6}, false, false, UNZIP_PERM_TYPE},
  /* unzip16hp: don't care the even-odd */
  {{1, 3, 5, 7}, false, false, UNZIP_PERM_TYPE},
  /* PV4HImode rev16 / PV4QImode rev8: don't care the even-odd.  */
  {{3, 2, 1, 0}, false, false, REV_PERM_TYPE},
  /* PV4HImode word swap / PV4QImode rev16: don't care the even-odd.  */
  {{2, 3, 0, 1}, false, false, REV_PERM_TYPE}
};

/* Supported 8-element vector permutation patterns.
   Only non-swapped patterns are stored; swapped patterns are detected
   and normalized at runtime.  */
static const vec_perm_pattern<8> vec_perm_patterns_8elem[] = {
  /* ppaire: op0_even, op1_even  */
  {{0, 8, 2, 10, 4, 12, 6, 14}, false, false, PAIR_PERM_TYPE},
  /* ppaireo: op0_even, op1_odd  */
  {{0, 9, 2, 11, 4, 13, 6, 15}, false, true, PAIR_PERM_TYPE},
  /* ppairoe: op0_odd, op1_even  */
  {{1, 8, 3, 10, 5, 12, 7, 14}, true, false, PAIR_PERM_TYPE},
  /* ppairo: op0_odd, op1_odd  */
  {{1, 9, 3, 11, 5, 13, 7, 15}, true, true, PAIR_PERM_TYPE},
  /* zip8p: don't care the even-odd */
  {{0, 8, 1, 9, 2, 10, 3, 11}, false, false, ZIP_PERM_TYPE},
  /* zip8hp: don't care the even-odd */
  {{4, 12, 5, 13, 6, 14, 7, 15}, false, false, ZIP_PERM_TYPE},
  /* unzip8p: don't care the even-odd */
  {{0, 2, 4, 6, 8, 10, 12, 14}, false, false, UNZIP_PERM_TYPE},
  /* unzip8hp: don't care the even-odd */
  {{1, 3, 5, 7, 9, 11, 13, 15}, false, false, UNZIP_PERM_TYPE},
  /* rev8: don't care the even-odd */
  {{7, 6, 5, 4, 3, 2, 1, 0}, false, false, REV_PERM_TYPE},
  /* rev16: don't care the even-odd */
  {{6, 7, 4, 5, 2, 3, 0, 1}, false, false, REV_PERM_TYPE}
};

/* Implement P extension vec_perm_const pattern matching.
   Similar to RVV's expand_vec_perm_const, this function tries various
   pattern matchers in sequence and emits the appropriate instruction.  */

bool
riscv_expand_pext_vec_perm_const (machine_mode vmode, machine_mode op_mode,
                                  rtx target, rtx op0, rtx op1,
                                  const vec_perm_indices &sel)
{
  bool testing_p = (target == NULL_RTX);

  /* All patterns below build the result from OP0/OP1 in VMODE.  Narrowing
     permutes, where the operands are wider than the result, have no P
     extension implementation; leave them to generic lowering.  */
  if (op_mode != vmode)
    return false;

  if (vmode == PV4QImode || vmode == PV4HImode)
    {
      for (const auto &pattern : vec_perm_patterns_4elem)
	{
	  vec_perm_match_type match_result = match_vec_perm_pattern (pattern.indices,
                                                                     4, sel);
	  if (match_result != ERROR_MATCH)
	    {
	      if (testing_p)
		return true;

              op0 = force_reg (vmode, op0);
              op1 = force_reg (vmode, op1);

	      /* match_result: 1 = normal match, 2 = swapped match.  */
              bool swap_operands = (match_result == SWAPPED_MATCH);

              switch (pattern.perm) {

                case PAIR_PERM_TYPE:
                  if (swap_operands)
                    riscv_emit_ppair_4_elem (target, vmode, op1, op0,
                                             pattern.op0_odd, pattern.op1_odd);
                  else
                    riscv_emit_ppair_4_elem (target, vmode, op0, op1,
                                             pattern.op0_odd, pattern.op1_odd);
                  break;

                case ZIP_PERM_TYPE:
                  {
                    const int idx[4] = {pattern.indices[0], pattern.indices[0],
                                        pattern.indices[2], pattern.indices[2]};
                    if (swap_operands)
                      riscv_emit_zip_4_elem (target, vmode, op1, op0, idx);
                    else
                      riscv_emit_zip_4_elem (target, vmode, op0, op1, idx);
                  }
                  break;

                case UNZIP_PERM_TYPE:
                  {
                    const int idx[2] = {pattern.indices[0], pattern.indices[1]};
                    if (swap_operands)
                      riscv_emit_unzip_4_elem (target, vmode, PV2HImode, op1, op0, idx);
                    else
                      riscv_emit_unzip_4_elem (target, vmode, PV2HImode, op0, op1, idx); 
                  }
                  break;

                case REV_PERM_TYPE:
                  {
                    const int idx[4] = {pattern.indices[0], pattern.indices[1],
                                        pattern.indices[2], pattern.indices[3]};
                    riscv_emit_rev_4_elem (target, vmode, op0, idx);
                  }
                  break;
              }
	      return true;
	    }
	}
    }
  else if (vmode == PV8QImode)
    {
      for (const auto &pattern : vec_perm_patterns_8elem)
	{
	  vec_perm_match_type match_result = match_vec_perm_pattern (pattern.indices,
                                                                     8, sel);
	  if (match_result != ERROR_MATCH)
	    {
	      /* On RV32, PV8QI is a register pair.  ZIP and UNZIP require
		 sequential byte selection across register boundaries, which has
		 no efficient RV32 P-extension implementation.  Fall back to
		 generic GCC lowering for these patterns.  */
	      if (!TARGET_64BIT && (pattern.perm == ZIP_PERM_TYPE
				    || pattern.perm == UNZIP_PERM_TYPE))
		return false;

	      if (testing_p)
		return true;
 
              op0 = force_reg (vmode, op0);
              op1 = force_reg (vmode, op1);

              /* match_result: 1 = normal match, 2 = swapped match.  */
              bool swap_operands = (match_result == SWAPPED_MATCH);

              switch (pattern.perm) {
        
                case PAIR_PERM_TYPE:
                  if (swap_operands)
                    riscv_emit_ppair_8_elem (target, vmode, op1, op0,
                                             pattern.op0_odd, pattern.op1_odd);
                  else
                    riscv_emit_ppair_8_elem (target, vmode, op0, op1,
                                             pattern.op0_odd, pattern.op1_odd);
                  break;

                case ZIP_PERM_TYPE:
                  {
                    const int idx[8] = {pattern.indices[0], pattern.indices[0],
                                        pattern.indices[2], pattern.indices[2],
                                        pattern.indices[4], pattern.indices[4],
                                        pattern.indices[6], pattern.indices[6]};
                    if (swap_operands)
                      riscv_emit_zip_8_elem (target, vmode, op1, op0, idx);
                    else
                      riscv_emit_zip_8_elem (target, vmode, op0, op1, idx);
                  }
                  break;

                case UNZIP_PERM_TYPE:
                  {
                    const int idx[4] = {pattern.indices[0], pattern.indices[1],
                                        pattern.indices[2], pattern.indices[3]};
                    if (swap_operands)
                      riscv_emit_unzip_8_elem (target, vmode, PV4QImode, op1, op0, idx);
                    else
                      riscv_emit_unzip_8_elem (target, vmode, PV4QImode, op0, op1, idx);
                  }
                  break;

                case REV_PERM_TYPE:
                  {
                     const int idx[8] = {pattern.indices[0], pattern.indices[1],
                                         pattern.indices[2], pattern.indices[3],
                                         pattern.indices[4], pattern.indices[5],
                                         pattern.indices[6], pattern.indices[7]};
                    riscv_emit_rev_8_elem (target, vmode, op0, idx);                   
                  }
                  break;
              }
	      return true;
	    }
	}
    }
  else if (vmode == PV2HImode || vmode == PV2SImode)
    {
      for (const auto &pattern : vec_perm_patterns_2elem)
        {
          vec_perm_match_type match_result = match_vec_perm_pattern (pattern.indices,
                                                                     2, sel);
          if (match_result != ERROR_MATCH)
            {
              if (testing_p)
                return true;

              op0 = force_reg (vmode, op0);
              op1 = force_reg (vmode, op1);

              /* match_result: 1 = normal match, 2 = swapped match.  */
              bool swap_operands = (match_result == SWAPPED_MATCH);
              if (swap_operands)
                riscv_emit_ppair_2_elem (target, vmode, op1, op0,
                                          pattern.op0_odd, pattern.op1_odd);
              else
                riscv_emit_ppair_2_elem (target, vmode, op0, op1,
                                          pattern.op0_odd, pattern.op1_odd);
              return true;
            }
        }
    }

  return false;
}

