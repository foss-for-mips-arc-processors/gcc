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
#include "expmed.h"
#include "explow.h"
#include "insn-config.h"
#include "insn-attr.h"
#include "emit-rtl.h"
#include "optabs-tree.h"

/* Return true if each physical word of OP is a logical immediate.  Check
   the complete bit pattern, rather than the range of individual lanes.  */

bool
riscv_p_bitwise_imm_p (rtx op)
{
  if (!CONST_VECTOR_P (op))
    return false;

  machine_mode mode = GET_MODE (op);
  if (mode != PV4QImode && mode != PV2HImode
      && mode != PV8QImode && mode != PV4HImode && mode != PV2SImode)
    return false;

  unsigned int bytes = GET_MODE_SIZE (mode).to_constant ();
  scalar_int_mode part_mode = bytes == 4 || !TARGET_64BIT ? SImode : DImode;
  unsigned int part_bytes = GET_MODE_SIZE (part_mode);
  for (unsigned int offset = 0; offset < bytes; offset += part_bytes)
    {
      rtx part = simplify_subreg (part_mode, op, mode, offset);
      if (!part || !CONST_INT_P (part) || !SMALL_OPERAND (INTVAL (part)))
	return false;
    }
  return true;
}

/* Return true if LO and HI can be read as one aligned PV4HI value.
   Preserve the little-endian lane order and the exact accessed range.  */

bool
riscv_p_small_pack_mems_p (rtx lo, rtx hi)
{
  if (!MEM_P (lo) || !MEM_P (hi)
      || GET_MODE (lo) != PV2HImode || GET_MODE (hi) != PV2HImode
      || MEM_VOLATILE_P (lo) || MEM_VOLATILE_P (hi)
      || MEM_ADDR_SPACE (lo) != MEM_ADDR_SPACE (hi)
      || MEM_ALIAS_SET (lo) != MEM_ALIAS_SET (hi)
      || MEM_ALIGN (lo) < 64
      || side_effects_p (XEXP (lo, 0)) || side_effects_p (XEXP (hi, 0)))
    return false;

  rtx next = plus_constant (Pmode, XEXP (lo, 0), 4);
  return rtx_equal_p (next, XEXP (hi, 0))
    && memory_address_addr_space_p (PV4HImode, XEXP (lo, 0),
				    MEM_ADDR_SPACE (lo));
}

/* Construct the full load after riscv_p_small_pack_mems_p succeeds.
   Neither half's expression or trapping promise describes the full range.  */

rtx
riscv_p_small_pack_mem (rtx lo, rtx hi)
{
  gcc_assert (riscv_p_small_pack_mems_p (lo, hi));
  rtx mem = adjust_address (lo, PV4HImode, 0);
  set_mem_expr (mem, NULL_TREE);
  clear_mem_offset (mem);
  MEM_NOTRAP_P (mem) = MEM_NOTRAP_P (lo) && MEM_NOTRAP_P (hi);
  MEM_READONLY_P (mem) = MEM_READONLY_P (lo) && MEM_READONLY_P (hi);
  return mem;
}

/* Classify a full-register product whose operands are extended words.
   Return 0 for signed inputs, 1 for unsigned inputs, 2 for signed/unsigned
   inputs, 3 for unsigned/signed inputs, or -1 if neither range is known.
   The bit information is used only while splitting, not as a persistent
   condition on an instruction that would need the same facts after IRA.  */

static int
riscv_p_round_mulhi_kind (rtx lhs, rtx rhs)
{
  bool ls = num_sign_bit_copies (lhs, DImode) >= 33;
  bool rs = num_sign_bit_copies (rhs, DImode) >= 33;
  bool lu = (nonzero_bits (lhs, DImode) & ~GET_MODE_MASK (SImode)) == 0;
  bool ru = (nonzero_bits (rhs, DImode) & ~GET_MODE_MASK (SImode)) == 0;
  if (ls && rs)
    return 0;
  if (lu && ru)
    return 1;
  if (ls && ru)
    return 2;
  if (lu && rs)
    return 3;
  return -1;
}

/* Return whether LHS and RHS can use a packed word product.  */

bool
riscv_p_round_mulhi_p (rtx lhs, rtx rhs)
{
  return riscv_p_round_mulhi_kind (lhs, rhs) >= 0;
}

/* A same-signed unrounded product followed by a logical shift already
   has an efficient scalar implementation.  In particular, replacing a
   compressed shift by a word zero extension can increase code size.  */

bool
riscv_p_mulhi_p (rtx lhs, rtx rhs, bool unsigned_p)
{
  int kind = riscv_p_round_mulhi_kind (lhs, rhs);
  return kind >= 0 && (!unsigned_p || kind >= 2);
}

/* Extract a rounded product's high word, with logical extension if
   UNSIGNED_P.  KIND is the input classification, or -1 to infer it from
   full-register values.  Account for both packed result lanes before
   extracting the low word; a packed word result is not an ABI-sign-extended
   scalar.  */

void
riscv_p_expand_round_mulhi (rtx target, rtx lhs, rtx rhs, bool unsigned_p,
			  int kind)
{
  if (kind < 0)
    kind = riscv_p_round_mulhi_kind (lhs, rhs);
  gcc_assert (IN_RANGE (kind, 0, 3) && TARGET_64BIT);
  rtx result = gen_reg_rtx (PV2SImode);
  lhs = gen_lowpart (PV2SImode, lhs);
  rhs = gen_lowpart (PV2SImode, rhs);
  if (kind == 0)
    emit_insn (gen_riscv_pmulhr_i32x2 (result, lhs, rhs));
  else if (kind == 1)
    emit_insn (gen_riscv_pmulhru_u32x2 (result, lhs, rhs));
  else if (kind == 2)
    emit_insn (gen_riscv_pmulhrsu_i32x2 (result, lhs, rhs));
  else
    emit_insn (gen_riscv_pmulhrsu_i32x2 (result, rhs, lhs));
  convert_move (target, gen_lowpart (SImode, result), unsigned_p);
}

/* Return a full register with the same low word as OP.  Input signedness
   is already recorded in the selected packed operation, so its upper
   word need not preserve an explicit scalar zero extension.  */

static rtx
riscv_p_mulhi_acc_operand (rtx op)
{
  if (GET_MODE (op) == SImode)
    {
      if (SUBREG_P (op) && GET_MODE (SUBREG_REG (op)) == DImode
	  && subreg_lowpart_p (op))
	return SUBREG_REG (op);
      rtx result = gen_reg_rtx (DImode);
      convert_move (result, op, false);
      return result;
    }
  if (GET_CODE (op) == AND)
    return XEXP (op, 0);
  if (GET_CODE (op) == SIGN_EXTEND || GET_CODE (op) == ZERO_EXTEND)
    return riscv_p_mulhi_acc_operand (XEXP (op, 0));
  return op;
}

/* Return a packed register with the same low word as OP.  The caller must
   discard the upper lane of the packed result before using this value.  */

rtx
riscv_p_low_word_packed_operand (rtx op)
{
  gcc_assert (GET_MODE (op) == PV2SImode
	      && rvp_low_word_packed_operand (op, PV2SImode));
  if (register_operand (op, PV2SImode))
    return op;
  return gen_lowpart (PV2SImode,
		      riscv_p_mulhi_acc_operand (SUBREG_REG (op)));
}

/* Extract an unrounded word product's high word.  Prove and freeze input
   signedness before discarding scalar extensions.  The complete packed
   output remains explicit even though only its low word is consumed.  */

void
riscv_p_expand_mulhi (rtx target, rtx lhs, rtx rhs, bool unsigned_p)
{
  int kind = riscv_p_round_mulhi_kind (lhs, rhs);
  gcc_assert (IN_RANGE (kind, 0, 3) && TARGET_64BIT);
  lhs = gen_lowpart (PV2SImode, riscv_p_mulhi_acc_operand (lhs));
  rhs = gen_lowpart (PV2SImode, riscv_p_mulhi_acc_operand (rhs));
  rtx result = gen_reg_rtx (PV2SImode);
  if (kind == 0)
    emit_insn (gen_riscv_pmulh_i32x2 (result, lhs, rhs));
  else if (kind == 1)
    emit_insn (gen_riscv_pmulhu_u32x2 (result, lhs, rhs));
  else if (kind == 2)
    emit_insn (gen_riscv_pmulhsu_i32x2 (result, lhs, rhs));
  else
    emit_insn (gen_riscv_pmulhsu_i32x2 (result, rhs, lhs));
  convert_move (target, gen_lowpart (SImode, result), unsigned_p);
}

/* Add a word product's high word to ACC modulo 2^32.  ROUND_P adds 2^31
   before extracting the product.  KIND has the same meaning as in
   riscv_p_expand_round_mulhi.  Model both result lanes and then extend
   the scalar result, so no upper bits of a live GPR are silently changed.  */

void
riscv_p_expand_mulhi_acc (rtx target, rtx lhs, rtx rhs, rtx acc,
			bool round_p, int kind)
{
  if (kind < 0)
    kind = riscv_p_round_mulhi_kind (lhs, rhs);
  gcc_assert (IN_RANGE (kind, 0, 3) && TARGET_64BIT);
  lhs = gen_lowpart (PV2SImode, riscv_p_mulhi_acc_operand (lhs));
  rhs = gen_lowpart (PV2SImode, riscv_p_mulhi_acc_operand (rhs));
  if (kind == 3)
    std::swap (lhs, rhs);
  rtx initial = gen_lowpart (PV2SImode, riscv_p_mulhi_acc_operand (acc));
  rtx result = gen_reg_rtx (PV2SImode);
  if (round_p)
    {
      if (kind == 0)
	emit_insn (gen_riscv_p_mhracc_pv2si (result, lhs, rhs, initial));
      else if (kind == 1)
	emit_insn (gen_riscv_p_mhraccu_pv2si (result, lhs, rhs, initial));
      else
	emit_insn (gen_riscv_p_mhraccsu_pv2si (result, lhs, rhs, initial));
    }
  else
    {
      if (kind == 0)
	emit_insn (gen_riscv_p_mhacc_pv2si (result, lhs, rhs, initial));
      else if (kind == 1)
	emit_insn (gen_riscv_p_mhaccu_pv2si (result, lhs, rhs, initial));
      else
	emit_insn (gen_riscv_p_mhaccsu_pv2si (result, lhs, rhs, initial));
    }
  convert_move (target, gen_lowpart (SImode, result), false);
}

/* Pack COUNT bytes from VALS, starting at FIRST, using pair operations.
   Each stage consumes only the defined low bits of the preceding stage.  */

static rtx
riscv_p_pack_bytes (rtx vals, unsigned int first, unsigned int count)
{
  if (count == 2)
    {
      rtx lo = force_reg (QImode, XVECEXP (vals, 0, first));
      rtx hi = force_reg (QImode, XVECEXP (vals, 0, first + 1));
      if (BYTES_BIG_ENDIAN)
	std::swap (lo, hi);
      rtx result = gen_reg_rtx (HImode);
      emit_insn (gen_riscv_p_pack_byteshi (result, lo, hi));
      return result;
    }

  gcc_assert (count == 4 || (TARGET_64BIT && count == 8));
  rtx lo = riscv_p_pack_bytes (vals, first, count / 2);
  rtx hi = riscv_p_pack_bytes (vals, first + count / 2, count / 2);
  machine_mode mode = count == 4 ? PV2HImode : PV2SImode;
  rtx result = gen_reg_rtx (mode);
  if (count == 4)
    emit_insn (gen_ppaire_concatpv2hi (result, lo, hi));
  else
    emit_insn (gen_pack_concatpv2si (result, lo, hi));
  return gen_lowpart (count == 4 ? SImode : DImode, result);
}

/* Pack COUNT elements from VALS, starting at FIRST, into a scalar register.
   Each element is zero-extended before shifting; no insertion needs to
   preserve undefined or already-written bits in a partial vector.  */

static rtx
riscv_p_pack_elements (scalar_int_mode mode, scalar_mode inner_mode,
		       rtx vals, unsigned int first, unsigned int count)
{
  /* Pairing variable bytes avoids the masks, shifts and ORs needed for a
     scalar construction.  Leave constants to the scalar path, where
     constant folding and omitted zero elements can be cheaper.  */
  if (inner_mode == QImode && count >= 2)
    {
      bool variable_p = true;
      for (unsigned int i = 0; i < count; ++i)
	variable_p &= !CONST_INT_P (XVECEXP (vals, 0, first + i));
      if (variable_p)
	{
	  rtx result = riscv_p_pack_bytes (vals, first, count);
	  return convert_modes (mode, GET_MODE (result), result, true);
	}
    }
  if (TARGET_64BIT && inner_mode == HImode && count == 2 && mode == SImode)
    {
      rtx pair = gen_reg_rtx (PV2HImode);
      rtx lo = force_reg (HImode, XVECEXP (vals, 0, first));
      rtx hi = force_reg (HImode, XVECEXP (vals, 0, first + 1));
      emit_insn (gen_ppaire_concatpv2hi (pair, lo, hi));
      return gen_lowpart (SImode, pair);
    }
  unsigned int bits = GET_MODE_BITSIZE (inner_mode);
  scalar_int_mode arithmetic_mode = as_a<scalar_int_mode> (word_mode);
  rtx result = NULL_RTX;
  for (unsigned int i = 0; i < count; ++i)
    {
      if (XVECEXP (vals, 0, first + i) == CONST0_RTX (inner_mode))
	continue;
      unsigned int shift = (BYTES_BIG_ENDIAN ? count - 1 - i : i) * bits;
      /* The highest element determines the sign extension of a word on
	 RV64.  Keep that extension explicit instead of widening a word OR
	 with unspecified upper bits.  Lower elements cannot change it.  */
      scalar_int_mode shift_mode = shift + bits == GET_MODE_BITSIZE (mode)
	? mode : arithmetic_mode;
      rtx value = convert_modes (shift_mode, inner_mode,
				XVECEXP (vals, 0, first + i), true);
      if (shift)
	value = expand_shift (LSHIFT_EXPR, shift_mode, value, shift,
			      NULL_RTX, true);
      value = convert_modes (arithmetic_mode, shift_mode, value, false);
      result = result ? expand_binop (arithmetic_mode, ior_optab, result,
				      value, NULL_RTX, true, OPTAB_DIRECT)
		      : value;
      gcc_assert (result);
    }
  return result ? gen_lowpart (mode, result) : CONST0_RTX (mode);
}

/* Initialize TARGET from the scalar elements in VALS.  Build repeated
   groups once and broadcast them in a wider packed mode.  Keep a complete
   scalar fallback for nonperiodic constructors.  */

void
riscv_p_expand_vec_init (rtx target, rtx vals)
{
  machine_mode mode = GET_MODE (target);
  scalar_mode inner_mode = GET_MODE_INNER (mode);
  unsigned int bits = GET_MODE_BITSIZE (inner_mode);
  unsigned int count = GET_MODE_NUNITS (mode).to_constant ();
  unsigned int bytes = GET_MODE_SIZE (mode).to_constant ();
  bool constant_p = true;
  bool repeatable_p = true;

  gcc_assert (TARGET_RVP && (bytes == 4 || bytes == 8)
	      && GET_CODE (vals) == PARALLEL
	      && XVECLEN (vals, 0) == (int) count);

  for (unsigned int i = 0; i < count; ++i)
    {
      rtx value = XVECEXP (vals, 0, i);
      constant_p &= CONST_INT_P (value);
      repeatable_p &= (CONST_INT_P (value)
		       || register_operand (value, inner_mode));
    }

  if (constant_p)
    {
      emit_move_insn (target, gen_rtx_CONST_VECTOR (mode, XVEC (vals, 0)));
      return;
    }

  for (unsigned int period = 1;
       repeatable_p && period < count && period * bits <= 32; period *= 2)
    {
      bool matches = true;
      for (unsigned int i = period; i < count; ++i)
	if (!rtx_equal_p (XVECEXP (vals, 0, i),
			  XVECEXP (vals, 0, i % period)))
	  {
	    matches = false;
	    break;
	  }
      if (!matches)
	continue;

      scalar_int_mode group_mode
	= int_mode_for_size (period * bits, 0).require ();
      rtx group = XVECEXP (vals, 0, 0);
      if (period != 1)
	{
	  scalar_int_mode packing_mode = group_mode == SImode
	    ? SImode : as_a<scalar_int_mode> (word_mode);
	  group = gen_lowpart (group_mode,
			       riscv_p_pack_elements (packing_mode, inner_mode,
					      vals, 0, period));
	}

      if (!TARGET_64BIT && group_mode == SImode)
	{
	  /* Keep word copies visible to subreg lowering.  Consumers of one
	     half need not materialize a complete register-pair broadcast.  */
	  rtx result = gen_reg_rtx (mode);
	  group = force_reg (SImode, group);
	  emit_move_insn (gen_lowpart (SImode, result), group);
	  emit_move_insn (gen_highpart (SImode, result), group);
	  emit_move_insn (target, result);
	  return;
	}

      machine_mode broadcast_mode = mode;
      if (period * bits == 16)
	broadcast_mode = bytes == 4 ? PV2HImode : PV4HImode;
      else if (period * bits == 32)
	broadcast_mode = PV2SImode;
      rtx result = expand_vector_broadcast (broadcast_mode,
					   force_reg (group_mode, group));
      gcc_assert (result);
      emit_move_insn (target, gen_lowpart (mode, result));
      return;
    }

  /* Do not coalesce memory operands, especially volatile loads.  Each
     scalar value must be consumed in its original constructor position.
     Use a temporary if TARGET could overwrite an input element.  */
  rtx result = reg_overlap_mentioned_p (target, vals)
    ? gen_reg_rtx (mode) : target;
  if (inner_mode != QImode)
    {
      emit_move_insn (result, CONST0_RTX (mode));
      for (unsigned int i = 0; i < count; ++i)
	if (XVECEXP (vals, 0, i) != CONST0_RTX (inner_mode))
	  store_bit_field (result, bits, i * bits, 0, 0, inner_mode,
			   XVECEXP (vals, 0, i), false, false);
      if (result != target)
	emit_move_insn (target, result);
      return;
    }

  unsigned int chunk = MIN (bytes, UNITS_PER_WORD);
  scalar_int_mode chunk_mode = chunk == 4 ? SImode : DImode;
  unsigned int per_chunk = chunk * BITS_PER_UNIT / bits;
  for (unsigned int offset = 0; offset < bytes; offset += chunk)
    {
      rtx value = riscv_p_pack_elements
	(chunk_mode, inner_mode, vals, offset * BITS_PER_UNIT / bits,
	 per_chunk);
      emit_move_insn (simplify_gen_subreg (chunk_mode, result, mode, offset),
		      value);
    }
  if (result != target)
    emit_move_insn (target, result);
}

/* Compute one physical halfword of the modular multiply-add/subtract SRC.
   WORD is its containing word's byte offset and HIGH_P selects its high
   halfword.  Extend the truncated result into DEST according to UNSIGNED_P.
   Signed scalar products have the required low bits for either signedness
   of the packed input lanes.  */

void
riscv_p_expand_mul_acc_lane (rtx dest, rtx src, unsigned int word,
			   bool high_p, bool unsigned_p)
{
  machine_mode mode = GET_MODE (src);
  gcc_assert (TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()
	      && (mode == PV2HImode || mode == PV4HImode)
	      && (GET_CODE (src) == PLUS || GET_CODE (src) == MINUS)
	      && word % 4 == 0
	      && word + 4 <= GET_MODE_SIZE (mode).to_constant ());
  bool product_first = GET_CODE (XEXP (src, 0)) == MULT;
  rtx product = XEXP (src, product_first ? 0 : 1);
  rtx acc = XEXP (src, product_first ? 1 : 0);
  gcc_assert (GET_CODE (product) == MULT);
  rtx a = simplify_gen_subreg (SImode, XEXP (product, 0), mode, word);
  rtx b = simplify_gen_subreg (SImode, XEXP (product, 1), mode, word);
  acc = simplify_gen_subreg (SImode, acc, mode, word);
  if (high_p)
    {
      rtx temp = gen_reg_rtx (SImode);
      emit_insn (gen_lshrsi3 (temp, acc, GEN_INT (16)));
      acc = temp;
    }

  rtx result = gen_reg_rtx (SImode);
  if (GET_CODE (src) == PLUS)
    {
      if (high_p)
	emit_insn (gen_maddhisi4tt (result, a, b, acc));
      else
	emit_insn (gen_maddhisi4 (result, gen_lowpart (HImode, a),
				gen_lowpart (HImode, b), acc));
    }
  else
    {
      if (high_p)
	emit_insn (gen_mul_h11 (result, a, b));
      else
	emit_insn (gen_mulhisi3 (result, gen_lowpart (HImode, a),
				gen_lowpart (HImode, b)));
      emit_insn (gen_subsi3 (result, product_first ? result : acc,
			    product_first ? acc : result));
    }
  rtx low = gen_lowpart (HImode, result);
  emit_insn (unsigned_p ? gen_zero_extendhisi2 (dest, low)
		       : gen_extendhisi2 (dest, low));
}

/* Widen consecutive bytes or halfwords, preserving their order.  PSEXT
   alone is not sufficient: it extends the low part of each already-wide
   lane, whereas the input here contains tightly packed narrow lanes.  */

void
riscv_p_expand_extend (rtx dest, rtx src, bool unsigned_p)
{
  if (GET_MODE (dest) == PV4HImode)
    emit_insn (unsigned_p ? gen_riscv_pwcvtu_u16x4 (dest, src)
			 : gen_riscv_pwcvt_i16x4 (dest, src));
  else
    {
      gcc_assert (GET_MODE (dest) == PV2SImode);
      emit_insn (unsigned_p ? gen_riscv_pwcvtu_u32x2 (dest, src)
			   : gen_riscv_pwcvt_i32x2 (dest, src));
    }
}

/* Return the low or high 32 bits of an eight-byte packed vector as MODE.
   A highpart subreg of a pseudo is not valid on RV64.  */

static rtx
riscv_p_vector_half (rtx src, machine_mode mode, bool high_p)
{
  if (!high_p)
    return gen_lowpart (mode, src);
  if (!TARGET_64BIT)
    return gen_highpart (mode, src);

  rtx tmp = gen_reg_rtx (DImode);
  emit_insn (gen_lshrdi3 (tmp, gen_lowpart (DImode, src), GEN_INT (32)));
  return gen_lowpart (mode, tmp);
}

/* Unpack half of SRC into twice-as-wide lanes in DEST.  */

void
riscv_p_expand_unpack (rtx dest, rtx src, bool unsigned_p, bool high_p)
{
  machine_mode half_mode = GET_MODE (src) == PV8QImode
			   ? PV4QImode : PV2HImode;
  riscv_p_expand_extend (dest, riscv_p_vector_half (src, half_mode, high_p),
			 unsigned_p);
}

/* Truncate the lanes of LO and HI and concatenate the results.  */

void
riscv_p_expand_pack (rtx dest, rtx lo, rtx hi)
{
  machine_mode half_mode = GET_MODE (dest) == PV8QImode
			   ? PV4QImode : PV2HImode;
  rtx low = gen_reg_rtx (half_mode);
  rtx high = gen_reg_rtx (half_mode);
  if (half_mode == PV4QImode)
    {
      emit_insn (gen_truncpv4hipv4qi2 (low, lo));
      emit_insn (gen_truncpv4hipv4qi2 (high, hi));
    }
  else
    {
      emit_insn (gen_truncpv2sipv2hi2 (low, lo));
      emit_insn (gen_truncpv2sipv2hi2 (high, hi));
    }

  if (TARGET_64BIT)
    {
      rtx tmp = gen_reg_rtx (PV2SImode);
      rtx concat = gen_rtx_VEC_CONCAT (PV2SImode, gen_lowpart (SImode, low),
				      gen_lowpart (SImode, high));
      emit_insn (gen_rtx_SET (tmp, concat));
      emit_move_insn (dest, gen_lowpart (GET_MODE (dest), tmp));
    }
  else
    {
      emit_move_insn (gen_lowpart (half_mode, dest), low);
      emit_move_insn (gen_highpart (half_mode, dest), high);
    }
}

/* Sum lanes modulo the element width.  Signed and unsigned lane sums have
   the same low bits.  PREDSUM computes a wider signed result, which we
   truncate only after reducing all lanes.  */

void
riscv_p_expand_reduc_plus (rtx dest, rtx src)
{
  machine_mode mode = GET_MODE (src);
  if (mode == PV2SImode)
    {
      rtx low = riscv_p_vector_half (src, SImode, false);
      rtx high = riscv_p_vector_half (src, SImode, true);
      emit_insn (gen_addsi3 (dest, low, high));
      return;
    }

  rtx sum = gen_reg_rtx (Xmode);
  bool bytes_p = mode == PV4QImode || mode == PV8QImode;
  if (TARGET_64BIT)
    {
      /* A four-byte vector does not define the upper half of its GPR.
	 Clear those bits before reducing all XLEN bits.  */
      if (known_eq (GET_MODE_SIZE (mode), 4))
	{
	  rtx wide = gen_reg_rtx (DImode);
	  emit_insn (gen_zero_extendsidi2 (wide, gen_lowpart (SImode, src)));
	  src = gen_lowpart (bytes_p ? PV8QImode : PV4HImode, wide);
	}
      emit_insn (bytes_p
		 ? gen_riscv_predsum_i8x8_i64_rv64 (sum, src, const0_rtx)
		 : gen_riscv_predsum_i16x4_i64_rv64 (sum, src, const0_rtx));
    }
  else if (mode == PV4QImode)
    emit_insn (gen_riscv_predsum_i8x4_i32_rv32 (sum, src, const0_rtx));
  else if (mode == PV2HImode)
    emit_insn (gen_riscv_predsum_i16x2_i32_rv32 (sum, src, const0_rtx));
  else
    {
      gcc_assert (mode == PV8QImode || mode == PV4HImode);
      emit_insn (bytes_p
		 ? gen_riscv_predsum_i8x8_i32_rv32 (sum, src, const0_rtx)
		 : gen_riscv_predsum_i16x4_i32_rv32 (sum, src, const0_rtx));
    }
  emit_move_insn (dest, gen_lowpart (GET_MODE (dest), sum));
}

/* Accumulate four halfword products into a doubleword, without truncating
   the products or their sum to a word.  The mixed-sign optab supplies the
   unsigned operand first, unlike the P instructions.  */

void
riscv_p_expand_dot_product_64 (rtx dest, rtx a, rtx b, rtx acc,
			       bool unsigned_p, bool mixed_p)
{
  if (mixed_p)
    std::swap (a, b);

  /* Keep the accumulator in the destination pseudo so that its incoming
     value can coalesce with the loop PHI.  A separate DI pseudo would
     leave copies across the scalar/vector mode boundary.  Preserve a
     distinct temporary if the output overlaps either multiplicand;
     RV32 still needs the upper halves after its first accumulation.  */
  bool direct_p = (REG_P (dest) && REGNO (dest) >= FIRST_PSEUDO_REGISTER
		   && !reg_overlap_mentioned_p (dest, a)
		   && !reg_overlap_mentioned_p (dest, b));
  rtx sum = direct_p ? gen_lowpart (DImode, dest) : gen_reg_rtx (DImode);
  emit_move_insn (sum, gen_lowpart (DImode, acc));
  if (TARGET_64BIT)
    emit_insn (mixed_p
	       ? gen_riscv_pm4addasu_i16x4_rv64 (sum, a, b)
	       : unsigned_p
	       ? gen_riscv_pm4addau_u16x4_rv64 (sum, a, b)
	       : gen_riscv_pm4adda_i16x4_rv64 (sum, a, b));
  else
    for (unsigned int byte = 0; byte < 8; byte += 4)
      {
	rtx lhs = simplify_gen_subreg (PV2HImode, a, PV4HImode, byte);
	rtx rhs = simplify_gen_subreg (PV2HImode, b, PV4HImode, byte);
	emit_insn (mixed_p
		   ? gen_riscv_pm2waddasu_i64_rmw (sum, lhs, rhs)
		   : unsigned_p
		   ? gen_riscv_pm2waddau_u64_rmw (sum, lhs, rhs)
		   : gen_riscv_pm2wadda_i64_rmw (sum, lhs, rhs));
      }
  if (!direct_p)
    emit_move_insn (gen_lowpart (DImode, dest), sum);
}

/* Return true if REG has a complete constant-zero definition before INSN
   in the same basic block, with no intervening definition or clobber.
   Do not remove that definition here: later DCE must preserve any uses
   by other instructions, packed inputs or exceptional successors.  */

bool
riscv_p_zero_accumulator_p (rtx reg, rtx_insn *insn)
{
  gcc_assert (reload_completed && REG_P (reg) && GP_REG_P (REGNO (reg)));

  rtx_insn *head = BB_HEAD (BLOCK_FOR_INSN (insn));
  for (rtx_insn *prev = PREV_INSN (insn);
       prev && prev != PREV_INSN (head); prev = PREV_INSN (prev))
    {
      if (!NONDEBUG_INSN_P (prev))
	continue;
      if (CALL_P (prev) || JUMP_P (prev)
	  || volatile_insn_p (PATTERN (prev)))
	return false;
      if (reg_set_p (reg, prev))
	{
	  rtx set = PATTERN (prev);
	  return GET_CODE (set) == SET
	    && rtx_equal_p (SET_DEST (set), reg)
	    && SET_SRC (set) == const0_rtx
	    && !RTX_FRAME_RELATED_P (prev);
	}
    }
  return false;
}

/* Return true if the native register containing word REG holds a byte SAD
   result before INSN.  A native RV64 result is at most 2040.  Search only
   recent instructions in this basic block, since word extensions are
   common and an unbounded search could be quadratic.  */

bool
riscv_p_sad_word_result_p (rtx reg, rtx_insn *insn)
{
  gcc_assert (TARGET_64BIT && reload_completed && REG_P (reg)
	      && GET_MODE (reg) == SImode && GP_REG_P (REGNO (reg)));
  rtx native = gen_rtx_REG (DImode, REGNO (reg));
  rtx_insn *head = BB_HEAD (BLOCK_FOR_INSN (insn));
  unsigned int remaining = 16;
  for (rtx_insn *prev = PREV_INSN (insn);
       prev && prev != PREV_INSN (head); prev = PREV_INSN (prev))
    {
      if (!NONDEBUG_INSN_P (prev))
	continue;
      if (remaining-- == 0 || CALL_P (prev) || JUMP_P (prev)
	  || volatile_insn_p (PATTERN (prev)))
	return false;
      if (reg_set_p (native, prev))
	{
	  rtx set = PATTERN (prev);
	  if (GET_CODE (set) != SET
	      || !rtx_equal_p (SET_DEST (set), native)
	      || RTX_FRAME_RELATED_P (prev))
	    return false;
	  rtx src = SET_SRC (set);
	  return GET_CODE (src) == UNSPEC && GET_MODE (src) == DImode
	    && XINT (src, 1) == UNSPEC_PABDSUMU;
	}
    }
  return false;
}

/* Accumulate byte or halfword differences for a reassociable reduction.
   Keep word accumulation modular; RV64 PABDSUMAU.B instead accumulates
   into a single doubleword and would carry between the partial sums.  */

void
riscv_p_expand_sad (rtx dest, rtx a, rtx b, rtx acc, bool unsigned_p)
{
  machine_mode mode = GET_MODE (a);
  gcc_assert (mode == PV8QImode || mode == PV4HImode);
  if (mode == PV4HImode || !unsigned_p)
    {
      rtx diff = gen_reg_rtx (mode);
      if (mode == PV4HImode)
	emit_insn (unsigned_p ? gen_uabdpv4hi3 (diff, a, b)
		   : gen_sabdpv4hi3 (diff, a, b));
      else
	emit_insn (gen_sabdpv8qi3 (diff, a, b));

      /* Even signed inputs can differ by 255 or 65535.  Their absolute
	 differences must therefore feed an unsigned reduction.  */

      if (GET_MODE (dest) == PV1DImode)
	{
	  rtx output = gen_lowpart (DImode, dest);
	  rtx input = gen_lowpart (DImode, acc);
	  emit_insn (mode == PV8QImode
		     ? gen_riscv_predsumu_u8x8_u64 (output, diff, input)
		     : gen_riscv_predsumu_u16x4_u64 (output, diff, input));
	}
      else
	{
	  rtx ones = force_reg (mode, CONST1_RTX (mode));
	  emit_insn (mode == PV4HImode
		     ? gen_udot_prodpv2sipv4hi (dest, diff, ones, acc)
		     : gen_udot_prodpv2sipv8qi (dest, diff, ones, acc));
	}
      return;
    }

  if (GET_MODE (dest) == PV2SImode)
    {
      if (TARGET_64BIT)
	{
	  /* SAD reductions do not require a particular distribution of the
	     partial sums.  Sum all eight differences into the low word,
	     leaving the high word zero, then add modulo the word width.
	     This avoids the constant needed by the byte dot product without
	     allowing a low-word carry to enter the high accumulator.  */
	  rtx sum = gen_reg_rtx (DImode);
	  emit_insn (gen_riscv_pabdsumu_di_rv64
		     (sum, gen_lowpart (DImode, a), gen_lowpart (DImode, b)));
	  emit_insn (gen_addpv2si3 (dest, gen_lowpart (PV2SImode, sum), acc));
	}
      else
	{
	  rtx sum[2];
	  for (unsigned int i = 0; i < 2; ++i)
	    {
	      sum[i] = gen_reg_rtx (SImode);
	      emit_move_insn (sum[i], riscv_subword (acc, i));
	      emit_insn (gen_riscv_pabdsumau_si_rv32
			 (sum[i], riscv_subword (a, i), riscv_subword (b, i)));
	    }
	  /* Consume both inputs before writing a possibly overlapping pair.  */
	  emit_move_insn (riscv_subword (dest, false), sum[0]);
	  emit_move_insn (riscv_subword (dest, true), sum[1]);
	}
      return;
    }

  gcc_assert (GET_MODE (dest) == PV1DImode);
  if (!TARGET_64BIT)
    {
      rtx sum = gen_reg_rtx (DImode);
      emit_insn (gen_riscv_pabdsumu_u8x8_u64 (sum, a, b));
      emit_insn (gen_adddi3 (gen_lowpart (DImode, dest), sum,
			    gen_lowpart (DImode, acc)));
      return;
    }

  /* Let the incoming accumulator coalesce with the destination, but do
     not overwrite either input before the read-modify-write operation.  */
  bool direct_p = (REG_P (dest) && REGNO (dest) >= FIRST_PSEUDO_REGISTER
		   && !reg_overlap_mentioned_p (dest, a)
		   && !reg_overlap_mentioned_p (dest, b));
  rtx sum = direct_p ? gen_lowpart (DImode, dest) : gen_reg_rtx (DImode);
  emit_move_insn (sum, gen_lowpart (DImode, acc));
  emit_insn (gen_riscv_pabdsumau_di_rv64
	     (sum, gen_lowpart (DImode, a), gen_lowpart (DImode, b)));
  if (!direct_p)
    emit_move_insn (gen_lowpart (DImode, dest), sum);
}

/* Preserve the full native result of RV64 byte and halfword zero extensions.
   A plain SI destination hides the zero high bits from packed scalar idioms.
   Use a promoted lowpart view without duplicating or widening any load.  */

bool
riscv_p_expand_zero_extend (rtx dest, rtx src)
{
  if (!TARGET_RVP || !TARGET_64BIT || TARGET_BIG_ENDIAN
      || GET_MODE (dest) != SImode)
    return false;

  gcc_assert (GET_MODE (src) == QImode || GET_MODE (src) == HImode);
  rtx value = gen_reg_rtx (DImode);
  emit_insn (gen_rtx_SET (value, gen_rtx_ZERO_EXTEND (DImode, src)));
  rtx low = gen_lowpart (SImode, value);
  SUBREG_PROMOTED_VAR_P (low) = 1;
  /* Both extensions are valid for unsigned byte and halfword values.
     Prefer the signed form used by ordinary RV64 word operations.  */
  SUBREG_PROMOTED_SET (low, SRP_SIGNED);
  emit_move_insn (dest, low);
  return true;
}

/* Compute an absolute difference of proven unsigned halfword values.
   Zero-extend to a complete physical word before interpreting the operands
   as packed halfwords.  Only the low lane can then contribute a result.  */

void
riscv_p_expand_scalar_uabd (rtx dest, rtx lhs, rtx rhs)
{
  rtx inputs[2] = { lhs, rhs };
  for (rtx &input : inputs)
    {
      /* A low word view can already have a fully zero-extended parent.
	 Do not infer that property from the low word's range alone.  */
      if (SUBREG_P (input) && known_eq (SUBREG_BYTE (input), 0)
	  && GET_MODE (SUBREG_REG (input)) == word_mode
	  && (nonzero_bits (SUBREG_REG (input), word_mode)
	      & ~HOST_WIDE_INT_UC (65535)) == 0)
	input = SUBREG_REG (input);
      else
	input = force_reg (word_mode, convert_to_mode (word_mode, input, true));
    }
  rtx value = GET_MODE (dest) == word_mode ? dest : gen_reg_rtx (word_mode);
  emit_insn (TARGET_64BIT
	     ? gen_riscv_p_scalar_uabdhidi (value, inputs[0], inputs[1])
	     : gen_riscv_p_scalar_uabdhisi (value, inputs[0], inputs[1]));
  if (value != dest)
    {
      gcc_assert (TARGET_64BIT && GET_MODE (dest) == SImode);
      rtx low = gen_lowpart (SImode, value);
      SUBREG_PROMOTED_VAR_P (low) = 1;
      /* The result fits in an unsigned halfword, so either extension is
	 valid.  Preserve the normal RV64 signed word-result convention.  */
      SUBREG_PROMOTED_SET (low, SRP_SIGNED);
      emit_move_insn (dest, low);
    }
}

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
	/* result = ~(op1 > op2) */
	enum rtx_code base_code = (code == LE) ? GT : GTU;
	tmp = gen_reg_rtx (mode);
	emit_move_insn (tmp, gen_rtx_fmt_ee (base_code, mode, op1, op2));
	emit_insn (gen_rtx_SET (result, gen_rtx_NOT (mode, tmp)));
      }
      break;

    case GT:
    case GTU:
      emit_move_insn (result, gen_rtx_fmt_ee (code, mode, op1, op2));
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

/* Multiply the low or high half of the input lanes, widening each product.
   RV32 has a direct widening instruction.  On RV64, interleave the operands
   so each source pair occupies one wide lane before using the cross product.
   ZIP8HP and ZIP16HP select the high halves without separate shifts.  */

void
riscv_p_expand_widen_mult (rtx dest, rtx op1, rtx op2, bool unsigned_p,
			   bool high_p)
{
  machine_mode mode = GET_MODE (op1);
  bool bytes_p = mode == PV8QImode;
  if (!TARGET_64BIT)
    {
      machine_mode half_mode = bytes_p ? PV4QImode : PV2HImode;
      op1 = riscv_p_vector_half (op1, half_mode, high_p);
      op2 = riscv_p_vector_half (op2, half_mode, high_p);
      if (bytes_p)
	emit_insn (unsigned_p ? gen_riscv_pwmulu_u16x4 (dest, op1, op2)
			      : gen_riscv_pwmul_i16x4 (dest, op1, op2));
      else
	emit_insn (unsigned_p ? gen_riscv_pwmulu_u32x2 (dest, op1, op2)
			      : gen_riscv_pwmul_i32x2 (dest, op1, op2));
      return;
    }

  unsigned int nunits = GET_MODE_NUNITS (mode).to_constant ();
  int indices[8];
  for (unsigned int i = 0; i < nunits; ++i)
    indices[i] = i / 2 + (high_p ? nunits / 2 : 0);

  rtx zipped = gen_reg_rtx (mode);
  if (bytes_p)
    {
      emit_vec_merge_with_select<8> (zipped, mode, op1, op2, indices, 0xaa);
      emit_insn (unsigned_p ? gen_riscv_pmulu_b01_u16x4 (dest, zipped, zipped)
			    : gen_riscv_pmul_b01_i16x4 (dest, zipped, zipped));
    }
  else
    {
      emit_vec_merge_with_select<4> (zipped, mode, op1, op2, indices, 0xa);
      emit_insn (unsigned_p ? gen_riscv_pmulu_h01_u32x2 (dest, zipped, zipped)
			    : gen_riscv_pmul_h01_i32x2 (dest, zipped, zipped));
    }
}

/* Multiply four bytes or two halfwords on RV64, widening each product.
   ACC, when nonnull, is a pair of word accumulators.  For equal signedness,
   interleave the inputs and use the cross product.  A mixed product instead
   needs each input in the low half of its wide lane; OP1 is the signed input.
   Zero widening preserves its sign bit for PMULSU/PMACCSU to interpret.  */

void
riscv_p_split_widen_mult (rtx dest, rtx op1, rtx op2, rtx acc,
			  bool unsigned_p, bool mixed_p)
{
  bool bytes_p = GET_MODE (dest) == PV4HImode;
  gcc_assert (TARGET_64BIT && (!acc || !bytes_p));
  machine_mode mode = bytes_p ? PV8QImode : PV4HImode;
  if (mixed_p)
    {
      rtx lhs = gen_reg_rtx (GET_MODE (dest));
      rtx rhs = gen_reg_rtx (GET_MODE (dest));
      if (bytes_p)
	{
	  emit_insn (gen_riscv_pwcvtu_u16x4_rv64 (lhs, op1));
	  emit_insn (gen_riscv_pwcvtu_u16x4_rv64 (rhs, op2));
	}
      else
	{
	  emit_insn (gen_riscv_pwcvtu_u32x2_rv64 (lhs, op1));
	  emit_insn (gen_riscv_pwcvtu_u32x2_rv64 (rhs, op2));
	}
      lhs = gen_lowpart (mode, lhs);
      rhs = gen_lowpart (mode, rhs);
      if (acc)
	emit_insn (gen_riscv_pmaccsu_h00_i32x2 (dest, acc, lhs, rhs));
      else if (bytes_p)
	emit_insn (gen_riscv_pmulsu_b00_i16x4 (dest, lhs, rhs));
      else
	emit_insn (gen_riscv_pmulsu_h00_i32x2 (dest, lhs, rhs));
      return;
    }

  rtx zipped = gen_reg_rtx (mode);
  if (bytes_p)
    {
      emit_insn (gen_riscv_pzip_i8x8_rv64 (zipped, op1, op2));
      emit_insn (unsigned_p ? gen_riscv_pmulu_b01_u16x4 (dest, zipped, zipped)
			    : gen_riscv_pmul_b01_i16x4 (dest, zipped, zipped));
    }
  else
    {
      emit_insn (gen_riscv_pzip_i16x4_rv64 (zipped, op1, op2));
      if (acc)
	emit_insn (unsigned_p
		   ? gen_riscv_pmaccu_h01_u32x2 (dest, acc, zipped, zipped)
		   : gen_riscv_pmacc_h01_i32x2 (dest, acc, zipped, zipped));
      else
	emit_insn (unsigned_p ? gen_riscv_pmulu_h01_u32x2 (dest, zipped, zipped)
			      : gen_riscv_pmul_h01_i32x2 (dest, zipped, zipped));
    }
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

/* Return the first or second logical half of a packed vector.  */

static rtx
riscv_pext_logical_half (machine_mode mode, rtx value, bool second)
{
  return second != TARGET_BIG_ENDIAN ? gen_highpart (mode, value)
				    : gen_lowpart (mode, value);
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
      rtx result = gen_reg_rtx (vmode);
      rtx src0 = riscv_pext_logical_half (SImode, op0, op0_odd);
      rtx src1 = riscv_pext_logical_half (SImode, op1, op1_odd);
      emit_move_insn (riscv_pext_logical_half (SImode, result, false), src0);
      emit_move_insn (riscv_pext_logical_half (SImode, result, true), src1);
      emit_move_insn (target, result);
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

/* Emit the RV32 double-wide ppair patterns for the register-pair modes
   (PV8QI, PV4HI).  The vec_merge/vec_select form used on RV64 defeats
   register-pair allocation here, so emit the unspec patterns that take
   the pair directly.  op0_odd/op1_odd pick the ppaire/ppaireo/ppairoe/
   ppairo variant exactly as in the merge-based emitters.  */

static void
riscv_emit_ppair_rv32_unspec (rtx target, machine_mode vmode, rtx op0, rtx op1,
                              bool op0_odd, bool op1_odd)
{
  /* Hardware pairs are ordered from the low lane, whereas logical lanes
     start at the high end of each word on big-endian targets.  */
  if (TARGET_BIG_ENDIAN)
    {
      std::swap (op0, op1);
      bool old_op0_odd = op0_odd;
      op0_odd = !op1_odd;
      op1_odd = !old_op0_odd;
    }
  rtx (*gen) (rtx, rtx, rtx);
  if (vmode == PV8QImode)
    gen = (!op0_odd && !op1_odd) ? gen_riscv_ppaire_u8x8_rv32
	 : (!op0_odd) ? gen_riscv_ppaireo_u8x8_rv32
	 : (!op1_odd) ? gen_riscv_ppairoe_u8x8_rv32
	 : gen_riscv_ppairo_u8x8_rv32;
  else
    gen = (!op0_odd && !op1_odd) ? gen_riscv_ppaire_u16x4_rv32
	 : (!op0_odd) ? gen_riscv_ppaireo_u16x4_rv32
	 : (!op1_odd) ? gen_riscv_ppairoe_u16x4_rv32
	 : gen_riscv_ppairo_u16x4_rv32;
  emit_insn (gen (target, op0, op1));
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
  /* On RV32, PV4HI is a register pair; use the double-wide unspec form.  */
  if (!TARGET_64BIT && vmode == PV4HImode)
    {
      riscv_emit_ppair_rv32_unspec (target, vmode, op0, op1, op0_odd, op1_odd);
      return;
    }

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
      rtx low = gen_lowpart (SImode, op0);
      rtx high = gen_lowpart (SImode, op1);
      /* Preserve physical halves when constructing logical elements.  */
      emit_insn (gen_rtx_SET (packed,
			      gen_rtx_VEC_CONCAT (PV2SImode,
					TARGET_BIG_ENDIAN ? high : low,
					TARGET_BIG_ENDIAN ? low : high)));
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
      bool high = (indices[0] >= 2) != TARGET_BIG_ENDIAN;
      emit_move_insn (target, high ? riscv_pv8qi_highpart (wide)
				  : gen_lowpart (PV4QImode, wide));
      return;
    }

  /* On RV32, PV4HI is a register pair; zip from lower or upper halfword halves. */
  if (!TARGET_64BIT && vmode == PV4HImode)
    {
      bool second = indices[0] >= 2;
      machine_mode hmode = PV2HImode;
      rtx a_half = riscv_pext_logical_half (hmode, op0, second);
      rtx b_half = riscv_pext_logical_half (hmode, op1, second);
      rtx result = gen_reg_rtx (vmode);
      rtx first = riscv_pext_logical_half (hmode, result, false);
      rtx last = riscv_pext_logical_half (hmode, result, true);
      riscv_emit_ppair_2_elem (first, hmode, a_half, b_half, false, false);
      riscv_emit_ppair_2_elem (last, hmode, a_half, b_half, true, true);
      emit_move_insn (target, result);
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
      if (TARGET_BIG_ENDIAN)
	{
	  /* Use physical narrowing explicitly: a logical TRUNCATE would
	     describe different halfword values on a big-endian target.
	     RV32 puts the numeric high word in the first hardware register;
	     RV64 instead needs the sources exchanged before concatenation.  */
	  if (TARGET_64BIT)
	    std::swap (op0, op1);
	  rtx wide = gen_lowpart (PV4HImode, riscv_concat_pv4qi (op0, op1));
	  if (indices[0] == 0)
	    emit_insn (gen_riscv_pncvth_u8x4 (target, wide));
	  else
	    emit_insn (gen_riscv_pncvt_u8x4 (target, wide));
	  return;
	}
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
      rtx a_first = riscv_pext_logical_half (hmode, op0, false);
      rtx a_last = riscv_pext_logical_half (hmode, op0, true);
      rtx b_first = riscv_pext_logical_half (hmode, op1, false);
      rtx b_last = riscv_pext_logical_half (hmode, op1, true);
      rtx result = gen_reg_rtx (vmode);
      rtx first = riscv_pext_logical_half (hmode, result, false);
      rtx last = riscv_pext_logical_half (hmode, result, true);
      riscv_emit_ppair_2_elem (first, hmode, a_first, a_last,
			      use_odd, use_odd);
      riscv_emit_ppair_2_elem (last, hmode, b_first, b_last,
			      use_odd, use_odd);
      emit_move_insn (target, result);
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
      rtx result = gen_reg_rtx (vmode);
      rtx res_lo = gen_lowpart (hmode, result);
      rtx res_hi = gen_highpart (hmode, result);
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
      emit_move_insn (target, result);
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
  /* On RV32, PV8QI is a register pair; use the double-wide unspec form.  */
  if (!TARGET_64BIT)
    {
      riscv_emit_ppair_rv32_unspec (target, vmode, op0, op1, op0_odd, op1_odd);
      return;
    }

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
      rtx result = gen_reg_rtx (vmode);
      rtx res_lo = gen_lowpart (hmode, result);
      rtx res_hi = gen_highpart (hmode, result);
      /* rev8 {7..0}: swap halves and byte-reverse each (needs Zbb rev8).
	 rev16 {6,7,4,5,2,3,0,1}: swap halves and halfword-swap each.  */
      const int rev8_idx[] = {3, 2, 1, 0};
      const int rev16_idx[] = {2, 3, 0, 1};
      const int *half_idx = (indices[0] == 7) ? rev8_idx : rev16_idx;
      riscv_emit_rev_4_elem (res_lo, hmode, op_hi, half_idx);
      riscv_emit_rev_4_elem (res_hi, hmode, op_lo, half_idx);
      emit_move_insn (target, result);
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

  /* Swap adjacent bytes within each halfword.  Keep this separate from
     the table shared by byte and halfword modes.  */
  if (vmode == PV4QImode || vmode == PV8QImode)
    {
      const int indices[] = { 1, 0, 3, 2, 5, 4, 7, 6 };
      unsigned int len = GET_MODE_NUNITS (vmode).to_constant ();
      vec_perm_match_type match
	= match_vec_perm_pattern (indices, len, sel);
      if (match != ERROR_MATCH)
	{
	  if (!testing_p)
	    {
	      rtx src = match == SWAPPED_MATCH ? op1 : op0;
	      src = force_reg (vmode, src);
	      emit_insn (vmode == PV4QImode
			 ? gen_riscv_bswap16_pv4qi (target, src)
			 : gen_riscv_bswap16_pv8qi (target, src));
	    }
	  return true;
	}
    }

  /* Reverse bytes within each word, without reversing word order.  */
  if (vmode == PV8QImode)
    {
      const int indices[] = { 3, 2, 1, 0, 7, 6, 5, 4 };
      vec_perm_match_type match = match_vec_perm_pattern (indices, 8, sel);
      if (match != ERROR_MATCH)
	{
	  if (!testing_p)
	    {
	      rtx src = match == SWAPPED_MATCH ? op1 : op0;
	      emit_insn (gen_riscv_bswap32_pv8qi (target,
					       force_reg (vmode, src)));
	    }
	  return true;
	}
    }

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
		    riscv_emit_rev_4_elem (target, vmode,
					  swap_operands ? op1 : op0, idx);
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
		    riscv_emit_rev_8_elem (target, vmode,
					  swap_operands ? op1 : op0, idx);
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

