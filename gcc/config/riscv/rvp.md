;; Machine description for RISC-V Packed (RVP) extension
;; Copyright (C) 2025 Free Software Foundation, Inc.

;; This file is part of GCC.

;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.

;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

(include "rvp-iterators.md")

(define_c_enum "unspec" [
  UNSPEC_RVP_SCALAR_UABDHI
  UNSPEC_RVP_SCALAR_UABDAQI
])

;; A one-element vector is a scalar doubleword in a GPR (or a GPR pair).
;; Keep it separate from the packed-lane arithmetic iterators.
(define_expand "movpv1di"
  [(set (match_operand:PV1DI 0 "")
	(match_operand:PV1DI 1 ""))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  if (riscv_legitimize_move (PV1DImode, operands[0], operands[1]))
    DONE;
  /* Do not let emit_move_insn canonicalize these equal-sized subregs
     back into a PV1DI move.  */
  emit_insn (gen_movdi (gen_lowpart (DImode, operands[0]),
			gen_lowpart (DImode, operands[1])));
  DONE;
})

(define_expand "movmisalignpv1di"
  [(set (match_operand:PV1DI 0 "nonimmediate_operand")
	(match_operand:PV1DI 1 "general_operand"))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  emit_move_insn (operands[0], operands[1]);
  DONE;
})

(define_expand "vec_initpv1didi"
  [(match_operand:PV1DI 0 "register_operand")
   (match_operand 1 "")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  emit_move_insn (gen_lowpart (DImode, operands[0]), XVECEXP (operands[1], 0, 0));
  DONE;
})

(define_expand "vec_duplicatepv1di"
  [(set (match_operand:PV1DI 0 "register_operand")
	(vec_duplicate:PV1DI (match_operand:DI 1 "register_operand")))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  emit_move_insn (gen_lowpart (DImode, operands[0]), operands[1]);
  DONE;
})

(define_expand "vec_extractpv1didi"
  [(match_operand:DI 0 "register_operand")
   (match_operand:PV1DI 1 "register_operand")
   (match_operand 2 "const_0_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  emit_move_insn (operands[0], gen_lowpart (DImode, operands[1]));
  DONE;
})

(define_expand "reduc_plus_scal_pv1di"
  [(match_operand:DI 0 "register_operand")
   (match_operand:PV1DI 1 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  emit_move_insn (operands[0], gen_lowpart (DImode, operands[1]));
  DONE;
})

(define_expand "addpv1di3"
  [(set (match_operand:PV1DI 0 "register_operand")
	(plus:PV1DI (match_operand:PV1DI 1 "register_operand")
		   (match_operand:PV1DI 2 "register_operand")))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  emit_insn (gen_adddi3 (gen_lowpart (DImode, operands[0]),
			gen_lowpart (DImode, operands[1]),
			gen_lowpart (DImode, operands[2])));
  DONE;
})

;; Move patterns for all packed vector modes
;; 4-byte vectors (PV4QI/PV2HI): supported on both RV32 and RV64
;; 8-byte vectors (PV8QI/PV4HI/PV2SI): RV64 uses single register, RV32 uses register pairs
(define_expand "mov<mode>"
  [(set (match_operand:PVMOVE 0 "")
	(match_operand:PVMOVE 1 ""))]
  "TARGET_RVP"
{
  if (riscv_legitimize_move (<MODE>mode, operands[0], operands[1]))
    DONE;
})

;; Reuse the scalar-aligned expansion for packed memory references.  This
;; also avoids stack temporaries when a view conversion requires a move
;; whose alignment is smaller than the packed mode's alignment.
(define_expand "movmisalign<mode>"
  [(set (match_operand:PVMOVE 0 "nonimmediate_operand")
	(match_operand:PVMOVE 1 "general_operand"))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  DONE;
})

;; Single-register move for packed vectors
;; - 4-byte vectors (PV4QI, PV2HI): always use single register on both RV32 and RV64
;; - 8-byte vectors (PV8QI, PV4HI, PV2SI): use single register on RV64 only
;; Note: PVALL iterator already has the correct TARGET_64BIT conditions for 8-byte modes
(define_insn "*mov<mode>_internal"
  [(set (match_operand:PVALL 0 "nonimmediate_operand" "=r,r,r,r, m,  *f,*f,*r,*f,*m")
	(match_operand:PVALL 1 "move_operand"         " r,T,vc,m,rJ,*r*J,*m,*f,*f,*f"))]
  "TARGET_RVP
   && (register_operand (operands[0], <MODE>mode)
       || reg_or_0_operand (operands[1], <MODE>mode))"
  { return riscv_output_move (operands[0], operands[1]); }
  [(set_attr "move_type" "move,const,const,load,store,mtc,fpload,mfc,fmove,fpstore")
   (set_attr "type" "move,move,move,load,store,mtc,fpload,mfc,fmove,fpstore")
   (set_attr "mode" "<MODE>")])

;; 8-byte vectors on RV32: register pairs
;; Even register pairs use PMV.DBS/DHS/DWS (handled by riscv_output_move).
;; Other register pairs and memory/FP alternatives split after reload.
;; Const vectors: PV8QI/PV4HI use PLI.DB/DH patterns; PV2SI with small
;; duplicate values split into two li, large values load from memory.
(define_insn_and_split "*mov<mode>_32bit"
  [(set (match_operand:PV64 0 "nonimmediate_operand" "=R,r,r,r,m,  *f,*f,*r,*f,*m")
	(match_operand:PV64 1 "move_operand"         " R,r,vc,m,r,*J*r,*m,*f,*f,*f"))]
  "!TARGET_64BIT && TARGET_RVP
   && (register_operand (operands[0], <MODE>mode)
       || reg_or_0_operand (operands[1], <MODE>mode))"
  { return riscv_output_move (operands[0], operands[1]); }
  "&& reload_completed && riscv_split_64bit_move_p (operands[0], operands[1])"
  [(const_int 0)]
  {
    riscv_split_doubleword_move (operands[0], operands[1]);
    DONE;
  }
  [(set_attr "move_type" "move,move,const,load,store,mtc,fpload,mfc,fmove,fpstore")
   (set_attr "type" "move,move,move,load,store,mtc,fpload,mfc,fmove,fpstore")
   (set_attr "mode" "<MODE>")])

;; A selected modular halfword product does not need the other products
;; or a packed result.  Signed and unsigned multiplication have identical
;; low 16 bits.  Match the existing subreg extraction so that ordinary
;; extracts remain available to other multiply and reduction patterns.
(define_insn_and_split "*rvp_extract_mul_<mode><u>"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(any_extend:SI
	  (match_operator:HI 3 "rvp_subreg_operator"
	    [(mult:RVP_EXTRACT_H
	       (match_operand:RVP_EXTRACT_H 1 "register_operand" "r")
	       (match_operand:RVP_EXTRACT_H 2 "register_operand" "r"))])))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()
   && SUBREG_BYTE (operands[3]).is_constant ()
   && SUBREG_BYTE (operands[3]).to_constant () % 2 == 0
   && SUBREG_BYTE (operands[3]).to_constant ()
      < GET_MODE_SIZE (<MODE>mode).to_constant ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  unsigned int byte = SUBREG_BYTE (operands[3]).to_constant ();
  rtx a = simplify_gen_subreg (SImode, operands[1], <MODE>mode,
			      byte & ~3U);
  rtx b = simplify_gen_subreg (SImode, operands[2], <MODE>mode,
			      byte & ~3U);
  rtx product = gen_reg_rtx (SImode);
  if (((byte & 2) != 0) != TARGET_BIG_ENDIAN)
    emit_insn (gen_mul_h11 (product, a, b));
  else
    emit_insn (gen_mulhisi3 (product, gen_lowpart (HImode, a),
			   gen_lowpart (HImode, b)));
  emit_insn (gen_<optab>hisi2 (operands[0], gen_lowpart (HImode, product)));
  DONE;
}
  [(set_attr "type" "multi")
   (set_attr "length" "8")])

;; A right shift by 16 selects the high physical half of a word in either
;; byte order.  Preserve the extension of the truncated halfword product.
(define_insn_and_split "*rvp_extract_mul_high_<mode>_<optab>"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(any_shiftrt:SI
	  (match_operator:SI 3 "rvp_subreg_operator"
	    [(mult:RVP_EXTRACT_H
	       (match_operand:RVP_EXTRACT_H 1 "register_operand" "r")
	       (match_operand:RVP_EXTRACT_H 2 "register_operand" "r"))])
	  (const_int 16)))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()
   && SUBREG_BYTE (operands[3]).is_constant ()
   && SUBREG_BYTE (operands[3]).to_constant () % 4 == 0
   && SUBREG_BYTE (operands[3]).to_constant ()
      < GET_MODE_SIZE (<MODE>mode).to_constant ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  unsigned int byte = SUBREG_BYTE (operands[3]).to_constant ();
  rtx a = simplify_gen_subreg (SImode, operands[1], <MODE>mode, byte);
  rtx b = simplify_gen_subreg (SImode, operands[2], <MODE>mode, byte);
  rtx product = gen_reg_rtx (SImode);
  emit_insn (gen_mul_h11 (product, a, b));
  if (<CODE> == ASHIFTRT)
    emit_insn (gen_extendhisi2 (operands[0], gen_lowpart (HImode, product)));
  else
    emit_insn (gen_zero_extendhisi2 (operands[0],
				   gen_lowpart (HImode, product)));
  DONE;
}
  [(set_attr "type" "multi")
   (set_attr "length" "8")])

;; Extract only the observable lane of a modular multiply-add/subtract.
;; Leave shared full-vector results available to their other consumers.
(define_insn_and_split "*rvp_extract_<rvp_lane_arith:optab>_mul_<mode><u>"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(any_extend:SI
	  (match_operator:HI 4 "rvp_subreg_operator"
	    [(rvp_lane_arith:RVP_EXTRACT_H
	       (mult:RVP_EXTRACT_H
		 (match_operand:RVP_EXTRACT_H 1 "register_operand" "r")
		 (match_operand:RVP_EXTRACT_H 2 "register_operand" "r"))
	       (match_operand:RVP_EXTRACT_H 3 "register_operand" "r"))])))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()
   && SUBREG_BYTE (operands[4]).is_constant ()
   && SUBREG_BYTE (operands[4]).to_constant () % 2 == 0
   && SUBREG_BYTE (operands[4]).to_constant ()
      < GET_MODE_SIZE (<MODE>mode).to_constant ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  unsigned int byte = SUBREG_BYTE (operands[4]).to_constant ();
  bool high_p = ((byte & 2) != 0) != TARGET_BIG_ENDIAN;
  riscv_p_expand_mul_acc_lane (operands[0], SUBREG_REG (operands[4]),
			      byte & ~3U, high_p,
			      <any_extend:CODE> == ZERO_EXTEND);
  DONE;
}
  [(set_attr "type" "multi")
   (set (attr "length")
	(if_then_else
	  (match_test "(((SUBREG_BYTE (operands[4]).to_constant () & 2) != 0)
		       != TARGET_BIG_ENDIAN)")
	  (const_int <rvp_lane_high_length>)
	  (const_int <rvp_lane_length>)))])

(define_insn_and_split "*rvp_extract_<rvp_lane_arith:optab>_mul_high_<mode>_<any_shiftrt:optab>"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(any_shiftrt:SI
	  (match_operator:SI 4 "rvp_subreg_operator"
	    [(rvp_lane_arith:RVP_EXTRACT_H
	       (mult:RVP_EXTRACT_H
		 (match_operand:RVP_EXTRACT_H 1 "register_operand" "r")
		 (match_operand:RVP_EXTRACT_H 2 "register_operand" "r"))
	       (match_operand:RVP_EXTRACT_H 3 "register_operand" "r"))])
	  (const_int 16)))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()
   && SUBREG_BYTE (operands[4]).is_constant ()
   && SUBREG_BYTE (operands[4]).to_constant () % 4 == 0
   && SUBREG_BYTE (operands[4]).to_constant ()
      < GET_MODE_SIZE (<MODE>mode).to_constant ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  unsigned int byte = SUBREG_BYTE (operands[4]).to_constant ();
  riscv_p_expand_mul_acc_lane (operands[0], SUBREG_REG (operands[4]),
			      byte, true, <any_shiftrt:CODE> == LSHIFTRT);
  DONE;
}
  [(set_attr "type" "multi")
   (set_attr "length" "<rvp_lane_high_length>")])

;; Subtraction is not commutative: also match accumulator minus product.
(define_insn_and_split "*rvp_extract_acc_sub_mul_<mode><u>"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(any_extend:SI
	  (match_operator:HI 4 "rvp_subreg_operator"
	    [(minus:RVP_EXTRACT_H
	       (match_operand:RVP_EXTRACT_H 3 "register_operand" "r")
	       (mult:RVP_EXTRACT_H
		 (match_operand:RVP_EXTRACT_H 1 "register_operand" "r")
		 (match_operand:RVP_EXTRACT_H 2 "register_operand" "r")))])))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()
   && SUBREG_BYTE (operands[4]).is_constant ()
   && SUBREG_BYTE (operands[4]).to_constant () % 2 == 0
   && SUBREG_BYTE (operands[4]).to_constant ()
      < GET_MODE_SIZE (<MODE>mode).to_constant ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  unsigned int byte = SUBREG_BYTE (operands[4]).to_constant ();
  bool high_p = ((byte & 2) != 0) != TARGET_BIG_ENDIAN;
  riscv_p_expand_mul_acc_lane (operands[0], SUBREG_REG (operands[4]),
			      byte & ~3U, high_p, <CODE> == ZERO_EXTEND);
  DONE;
}
  [(set_attr "type" "multi")
   (set (attr "length")
	(if_then_else
	  (match_test "(((SUBREG_BYTE (operands[4]).to_constant () & 2) != 0)
		       != TARGET_BIG_ENDIAN)")
	  (const_int 16) (const_int 12)))])

(define_insn_and_split "*rvp_extract_acc_sub_mul_high_<mode>_<optab>"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(any_shiftrt:SI
	  (match_operator:SI 4 "rvp_subreg_operator"
	    [(minus:RVP_EXTRACT_H
	       (match_operand:RVP_EXTRACT_H 3 "register_operand" "r")
	       (mult:RVP_EXTRACT_H
		 (match_operand:RVP_EXTRACT_H 1 "register_operand" "r")
		 (match_operand:RVP_EXTRACT_H 2 "register_operand" "r")))])
	  (const_int 16)))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()
   && SUBREG_BYTE (operands[4]).is_constant ()
   && SUBREG_BYTE (operands[4]).to_constant () % 4 == 0
   && SUBREG_BYTE (operands[4]).to_constant ()
      < GET_MODE_SIZE (<MODE>mode).to_constant ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  unsigned int byte = SUBREG_BYTE (operands[4]).to_constant ();
  riscv_p_expand_mul_acc_lane (operands[0], SUBREG_REG (operands[4]),
			      byte, true, <CODE> == LSHIFTRT);
  DONE;
}
  [(set_attr "type" "multi")
   (set_attr "length" "16")])

;; Binary Arithmetic Operations

;; The RV64 instructions operate independently on each word.  Describe only
;; the low word; an ABI return or a wider use must extend it normally.
(define_insn "rvp_<optab>si3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(rvp_sat_op:SI (match_operand:SI 1 "register_operand" "r")
		       (match_operand:SI 2 "register_operand" "r")))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    return "p<insn>.w\t%0, %1, %2";
  return "<insn>\t%0, %1, %2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; Unified pattern for all binary arithmetic operations
;;   - Basic: padd.b/h/w, psub.b/h/w
;;   - Saturating signed: psadd.b/h/w, pssub.b/h/w
;;   - Saturating unsigned: psaddu.b/h/w, pssubu.b/h/w
;;   - Min/max signed: pmin.b/h/w, pmax.b/h/w
;;   - Min/max unsigned: pminu.b/h/w, pmaxu.b/h/w

;; Single-register pattern for 4-byte vectors (RV32/RV64)
;; Standard pattern name for optab lookup
(define_insn "<rvp_optab><mode>3"
  [(set (match_operand:PV32 0 "register_operand" "=r")
	(rvp_binop:PV32 (match_operand:PV32 1 "register_operand" "r")
			(match_operand:PV32 2 "register_operand" "r")))]
  "TARGET_RVP"
  "<rvp_insn>.<rvp_width>\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; 4-byte packed vector negation (PV4QI/PV2HI, RV32/RV64).
;; pneg.<b,h> rd, rs is an assembler alias for psub.<b,h> rd, x0, rs.
(define_insn "neg<mode>2"
  [(set (match_operand:PV32 0 "register_operand" "=r")
	(neg:PV32 (match_operand:PV32 1 "register_operand" "r")))]
  "TARGET_RVP"
  "pneg.<rvp_width>\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

(define_insn "*<rvp_widen_optab><rvp_narrow><rvp_ext_mode>3"
  [(set (match_operand:RVP_DWIDTH_EXT 0 "register_operand" "=r")
        (rvp_widen_op:RVP_DWIDTH_EXT
                    (any_extend:RVP_DWIDTH_EXT
                      (match_operand:<HALFMODE> 1 "register_operand" "r"))
                    (any_extend:RVP_DWIDTH_EXT
                      (match_operand:<HALFMODE> 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_64BIT"
  "<rvp_widen_insn><u>.<rvp_extend_width>\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

(define_insn "mul<rvp_ext_mode>3"
  [(set (match_operand:PVHW 0 "register_operand" "=r")
        (mult:PVHW (match_operand:PVHW 1 "register_operand" "r")
                   (match_operand:PVHW 2 "register_operand" "r")))]
  "TARGET_RVP && (!TARGET_64BIT || can_create_pseudo_p ())"
  "#"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Preserve full-width multiplication through combine on RV64 too.  If it
;; does not fold into a widening product, compute the low bits of each lane.
;; Signed and unsigned products have the same low half.
(define_split
  [(set (match_operand:PV4HI 0 "register_operand")
	(mult:PV4HI (match_operand:PV4HI 1 "register_operand")
		   (match_operand:PV4HI 2 "register_operand")))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()"
  [(const_int 0)]
{
  rtx even = gen_reg_rtx (PV2SImode);
  rtx odd = gen_reg_rtx (PV2SImode);
  emit_insn (gen_riscv_pmul_h00_i32x2 (even, operands[1], operands[2]));
  emit_insn (gen_riscv_pmul_h11_i32x2 (odd, operands[1], operands[2]));
  emit_insn (gen_riscv_ppaire_i16x4_rv64 (operands[0],
					gen_lowpart (PV4HImode, even),
					gen_lowpart (PV4HImode, odd)));
  DONE;
})

(define_split
  [(set (match_operand:PV2SI 0 "register_operand")
	(mult:PV2SI (match_operand:PV2SI 1 "register_operand")
		   (match_operand:PV2SI 2 "register_operand")))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()"
  [(const_int 0)]
{
  rtx low = gen_reg_rtx (SImode);
  rtx high = gen_reg_rtx (SImode);
  /* Consume the low words first, allowing the shifts to overwrite their
     inputs and use compressed instructions when optimizing for size.  */
  emit_insn (gen_mulsi3 (low, gen_lowpart (SImode, operands[1]),
		       gen_lowpart (SImode, operands[2])));
  rtx lhs_high = gen_reg_rtx (DImode);
  rtx rhs_high = gen_reg_rtx (DImode);
  emit_insn (gen_lshrdi3 (lhs_high, gen_lowpart (DImode, operands[1]),
			GEN_INT (32)));
  emit_insn (gen_lshrdi3 (rhs_high, gen_lowpart (DImode, operands[2]),
			GEN_INT (32)));
  emit_insn (gen_mulsi3 (high, gen_lowpart (SImode, lhs_high),
		       gen_lowpart (SImode, rhs_high)));
  /* LOW and HIGH name physical words, but VEC_CONCAT describes logical
     element order.  The first element occupies the high word on BE.  */
  emit_insn (gen_rtx_SET (operands[0],
			gen_rtx_VEC_CONCAT (PV2SImode,
					    TARGET_BIG_ENDIAN ? high : low,
					    TARGET_BIG_ENDIAN ? low : high)));
  DONE;
})

;; Masks used only by a word product need not occupy complete register
;; pairs.  Keep the expression together until its scalar expansion.
(define_insn_and_split "*rvp_masked_mulpv2si3"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(mult:PV2SI
	  (and:PV2SI
	    (match_operand:PV2SI 1 "register_operand" "r")
	    (match_operand:PV2SI 2 "riscv_p_bitwise_operand" "Wpl"))
	  (and:PV2SI
	    (match_operand:PV2SI 3 "register_operand" "r")
	    (match_operand:PV2SI 4 "riscv_p_bitwise_operand" "Wpl"))))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()
   && riscv_p_bitwise_imm_p (operands[2])
   && riscv_p_bitwise_imm_p (operands[4])"
  "#"
  "&& 1"
  [(const_int 0)]
{
  rtx product[2];
  for (unsigned int i = 0; i < 2; ++i)
    {
      rtx lhs = gen_reg_rtx (SImode);
      rtx rhs = gen_reg_rtx (SImode);
      emit_insn (gen_andsi3 (lhs, riscv_subword (operands[1], i != 0),
			    riscv_subword (operands[2], i != 0)));
      emit_insn (gen_andsi3 (rhs, riscv_subword (operands[3], i != 0),
			    riscv_subword (operands[4], i != 0)));
      product[i] = gen_reg_rtx (SImode);
      emit_insn (gen_mulsi3 (product[i], lhs, rhs));
    }
  /* Consume both inputs before writing any overlapping destination.  */
  for (unsigned int i = 0; i < 2; ++i)
    emit_move_insn (riscv_subword (operands[0], i != 0), product[i]);
  DONE;
}
  [(set_attr "type" "imul")
   (set_attr "length" "32")])

;; Split PV2SI multiplication into element-wise scalar multiplications
;; when the pattern cannot be combined into more efficient forms (like PWMUL).
;; On RV32, PV2SI use register pairs,
;; so we split the 64-bit vector into two 32-bit parts and multiply element-wise.
(define_split
  [(set (match_operand:PV2SI 0 "register_operand")
        (mult:PV2SI (match_operand:PV2SI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")))]
  "TARGET_RVP && !TARGET_64BIT"
  [(const_int 0)]
{
  rtx dest_lo = riscv_subword (operands[0], false);
  rtx dest_hi = riscv_subword (operands[0], true);
  rtx src1_lo = riscv_subword (operands[1], false);
  rtx src1_hi = riscv_subword (operands[1], true);
  rtx src2_lo = riscv_subword (operands[2], false);
  rtx src2_hi = riscv_subword (operands[2], true);

  /* For PV2SI: multiply single 32-bit element in each word.
     In both cases, we use the scalar MUL instruction on each word.  */
  emit_insn (gen_mulsi3 (dest_lo, src1_lo, src2_lo));
  emit_insn (gen_mulsi3 (dest_hi, src1_hi, src2_hi));
  DONE;
})

;; Lower an unfused RV32 PV4HI product with MUL.H00/MUL.H11 and PACK
;; (PPAIRE.H) to retain the low half of each product.  Use scalar bitwise
;; RTL for PACK so its meaning is independent of vector element order.
;; Read both source words before writing either result word, allowing
;; complete source-pair reuse.
(define_split
  [(set (match_operand:PV4HI 0 "register_operand")
        (mult:PV4HI (match_operand:PV4HI 1 "register_operand")
                    (match_operand:PV4HI 2 "register_operand")))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()"
  [(const_int 0)]
{
  rtx products[4];
  for (unsigned int i = 0; i < 2; ++i)
    {
      rtx op1 = riscv_subword (operands[1], i != 0);
      rtx op2 = riscv_subword (operands[2], i != 0);
      products[2 * i] = gen_reg_rtx (SImode);
      products[2 * i + 1] = gen_reg_rtx (SImode);
      emit_insn (gen_mulhisi3 (products[2 * i], gen_lowpart (HImode, op1),
			     gen_lowpart (HImode, op2)));
      emit_insn (gen_mul_h11 (products[2 * i + 1], op1, op2));
    }

  for (unsigned int i = 0; i < 2; ++i)
    {
      rtx dest = riscv_subword (operands[0], i != 0);
      emit_insn (gen_riscv_xpack_si_hi_2
		 (dest, products[2 * i + 1], GEN_INT (16),
		  gen_lowpart (HImode, products[2 * i])));
    }

  DONE;
})

(define_insn "*pwmul<su><rvp_narrow>3"
  [(set (match_operand:PVHW 0 "register_operand" "=r")
        (mult:PVHW (any_extend:PVHW (match_operand:<HALFMODE> 1 "register_operand" "r"))
                   (any_extend:PVHW (match_operand:<HALFMODE> 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmul<u>.<rvp_extend_width>\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_code_attr rvp_other_extend
  [(sign_extend "zero_extend") (zero_extend "sign_extend")])

(define_code_attr rvp_mixed_operands
  [(sign_extend "%1, %2") (zero_extend "%2, %1")])

(define_insn "*pwmul<su>mixed<rvp_narrow>3"
  [(set (match_operand:PVHW 0 "register_operand" "=r")
	(mult:PVHW
	  (any_extend:PVHW
	    (match_operand:<HALFMODE> 1 "register_operand" "r"))
	  (<rvp_other_extend>:PVHW
	    (match_operand:<HALFMODE> 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmulsu.<rvp_extend_width>\t%0, <rvp_mixed_operands>"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*pwmacc<su>pv2hi3"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (plus:PV2SI (mult:PV2SI (any_extend:PV2SI (match_operand:PV2HI 1 "register_operand" "r"))
                                (any_extend:PV2SI (match_operand:PV2HI 2 "register_operand" "r")))
                    (match_operand:PV2SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmacc<u>.h\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*pwmacc<su>mixedpv2hi3"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(plus:PV2SI
	  (mult:PV2SI
	    (any_extend:PV2SI (match_operand:PV2HI 1 "register_operand" "r"))
	    (<rvp_other_extend>:PV2SI
	      (match_operand:PV2HI 2 "register_operand" "r")))
	  (match_operand:PV2SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmaccsu.h\t%0, <rvp_mixed_operands>"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Scalar Q15 multiplication.  Extend each input to the full register so
;; every unused halfword is zero or minus one and cannot saturate.
(define_expand "<rvp_qmul_optab>hi3"
  [(set (match_operand:HI 0 "register_operand")
	(unspec:HI [(match_operand:HI 1 "register_operand")
		    (match_operand:HI 2 "register_operand")]
	 RVP_QMUL_OP))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && !TARGET_VECTOR"
{
  rtx op1 = convert_to_mode (word_mode, operands[1], false);
  rtx op2 = convert_to_mode (word_mode, operands[2], false);
  machine_mode mode = TARGET_64BIT ? PV4HImode : PV2HImode;
  rtx dest = gen_reg_rtx (mode);
  op1 = gen_lowpart (mode, op1);
  op2 = gen_lowpart (mode, op2);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_<rvp_qmul_half>_i16x4_rv64 (dest, op1, op2));
  else
    emit_insn (gen_riscv_<rvp_qmul_half>_i16x2 (dest, op1, op2));
  emit_move_insn (operands[0], gen_lowpart (HImode, dest));
  DONE;
})

;; Scalar Q31 multiplication.  Sign-extend both inputs on RV64 so the unused
;; high lanes cannot saturate, and model the complete packed result write.
(define_expand "<rvp_qmul_optab>si3"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:SI 1 "register_operand")
		    (match_operand:SI 2 "register_operand")]
	 RVP_QMUL_OP))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && !TARGET_VECTOR"
{
  if (TARGET_64BIT)
    {
      rtx op1 = convert_to_mode (DImode, operands[1], false);
      rtx op2 = convert_to_mode (DImode, operands[2], false);
      rtx dest = gen_reg_rtx (PV2SImode);
      emit_insn (gen_riscv_<rvp_scalar_mul_packed>
		 (dest, gen_lowpart (PV2SImode, op1),
		  gen_lowpart (PV2SImode, op2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, dest));
    }
  else
    emit_insn (gen_riscv_<rvp_scalar_mul_builtin>_rv32
	       (operands[0], operands[1], operands[2]));
  DONE;
})

;; Saturating scaled multiplication used by vectorized fixed-point code.
(define_expand "<rvp_qmul_optab><mode>3"
  [(set (match_operand:RVP_QMUL 0 "register_operand")
	(unspec:RVP_QMUL [(match_operand:RVP_QMUL 1 "register_operand")
			 (match_operand:RVP_QMUL 2 "register_operand")]
	 RVP_QMUL_OP))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && !TARGET_VECTOR"
{
  if (<MODE>mode == PV2HImode)
    emit_insn (gen_riscv_<rvp_qmul_half>_i16x2
	       (operands[0], operands[1], operands[2]));
  else if (<MODE>mode == PV4HImode)
    emit_insn (gen_riscv_<rvp_qmul_half>_i16x4
	       (operands[0], operands[1], operands[2]));
  else if (TARGET_64BIT)
    emit_insn (gen_riscv_<rvp_scalar_mul_packed>
	       (operands[0], operands[1], operands[2]));
  else
    {
      /* RV32 has scalar Q31 products.  Use a fresh pair so overlapping
	 inputs remain intact until both lane results have been computed.  */
      rtx dest = gen_reg_rtx (PV2SImode);
      rtx op1 = force_reg (PV2SImode, operands[1]);
      rtx op2 = force_reg (PV2SImode, operands[2]);
      for (unsigned int byte = 0; byte < 8; byte += 4)
	{
	  rtx lane = simplify_gen_subreg (SImode, dest, PV2SImode, byte);
	  rtx a = simplify_gen_subreg (SImode, op1, PV2SImode, byte);
	  rtx b = simplify_gen_subreg (SImode, op2, PV2SImode, byte);
	  emit_insn (gen_riscv_<rvp_scalar_mul_builtin>_rv32 (lane, a, b));
	}
      emit_move_insn (operands[0], dest);
    }
  DONE;
})

;; The shifted product of two signed halfwords is in [-32767, 32768].
;; Clamping its upper end therefore gives the signed Q15 product.  Keep
;; the extension separate so a subsequent narrowing can discard it.
(define_split
  [(set (match_operand:PV2SI 0 "register_operand")
	(smin:PV2SI
	  (ashiftrt:PV2SI
	    (mult:PV2SI
	      (sign_extend:PV2SI
		(match_operand:PV2HI 1 "register_operand"))
	      (sign_extend:PV2SI
		(match_operand:PV2HI 2 "register_operand")))
	    (const_int 15))
	  (match_operand:PV2SI 3 "immediate_operand")))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && can_create_pseudo_p ()
   && riscv_const_vector_broadcast_val_p (operands[3], 32767)"
  [(set (match_dup 4)
	(unspec:PV2HI [(match_dup 1) (match_dup 2)] UNSPEC_PMULQ))
   (set (match_dup 0) (sign_extend:PV2SI (match_dup 4)))]
  "{ operands[4] = gen_reg_rtx (PV2HImode); }")

(define_split
  [(set (match_operand:PV2SI 0 "register_operand")
	(smin:PV2SI
	  (ashiftrt:PV2SI
	    (plus:PV2SI
	      (mult:PV2SI
		(sign_extend:PV2SI
		  (match_operand:PV2HI 1 "register_operand"))
		(sign_extend:PV2SI
		  (match_operand:PV2HI 2 "register_operand")))
	      (match_operand:PV2SI 3 "immediate_operand"))
	    (const_int 15))
	  (match_operand:PV2SI 4 "immediate_operand")))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && can_create_pseudo_p ()
   && riscv_const_vector_broadcast_val_p (operands[3], 16384)
   && riscv_const_vector_broadcast_val_p (operands[4], 32767)"
  [(set (match_dup 5)
	(unspec:PV2HI [(match_dup 1) (match_dup 2)] UNSPEC_PMULQR))
   (set (match_dup 0) (sign_extend:PV2SI (match_dup 5)))]
  "{ operands[5] = gen_reg_rtx (PV2HImode); }")

;; Keep the rounding constant inside the product so combine can also see
;; the shift and upper clamp.  An unfused product still uses the ordinary
;; widening multiply-accumulate sequence.
(define_insn_and_split "*rvp_q15_round_product"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(plus:PV2SI
	  (mult:PV2SI
	    (sign_extend:PV2SI
	      (match_operand:PV2HI 1 "register_operand" "r"))
	    (sign_extend:PV2SI
	      (match_operand:PV2HI 2 "register_operand" "r")))
	  (match_operand:PV2SI 3 "immediate_operand" "i")))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && can_create_pseudo_p ()
   && riscv_const_vector_broadcast_val_p (operands[3], 16384)"
  "#"
  "&& 1"
  [(set (match_dup 4) (match_dup 3))
   (set (match_dup 0)
	(plus:PV2SI
	  (mult:PV2SI (sign_extend:PV2SI (match_dup 1))
		     (sign_extend:PV2SI (match_dup 2)))
	  (match_dup 4)))]
  "{ operands[4] = gen_reg_rtx (PV2SImode); }"
  [(set_attr "type" "simd")
   (set (attr "length") (if_then_else (match_test "TARGET_64BIT")
				     (const_int 16) (const_int 12)))])

;; Keep widening multiplication visible through combine, including the
;; accumulation when available.  RV64 uses ZIP followed by a packed product;
;; split before register allocation because these sequences need temporaries.
(define_insn_and_split "*pwmul<su><rvp_narrow>3_rv64"
  [(set (match_operand:PVHW 0 "register_operand" "=r")
	(mult:PVHW
	  (any_extend:PVHW
	    (match_operand:<HALFMODE> 1 "register_operand" "r"))
	  (any_extend:PVHW
	    (match_operand:<HALFMODE> 2 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  riscv_p_split_widen_mult (operands[0], operands[1], operands[2], NULL_RTX,
			    <CODE> == ZERO_EXTEND, false);
  DONE;
}
  [(set_attr "type" "simd")
   (set_attr "length" "8")])

(define_insn_and_split "*pwmul<su>mixed<rvp_narrow>3_rv64"
  [(set (match_operand:PVHW 0 "register_operand" "=r")
	(mult:PVHW
	  (any_extend:PVHW
	    (match_operand:<HALFMODE> 1 "register_operand" "r"))
	  (<rvp_other_extend>:PVHW
	    (match_operand:<HALFMODE> 2 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  if (<CODE> == ZERO_EXTEND)
    std::swap (operands[1], operands[2]);
  riscv_p_split_widen_mult (operands[0], operands[1], operands[2], NULL_RTX,
			    false, true);
  DONE;
}
  [(set_attr "type" "simd")
   (set_attr "length" "12")])

(define_insn_and_split "*pwmacc<su>pv2hi3_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(plus:PV2SI
	  (mult:PV2SI
	    (any_extend:PV2SI (match_operand:PV2HI 1 "register_operand" "r"))
	    (any_extend:PV2SI (match_operand:PV2HI 2 "register_operand" "r")))
	  (match_operand:PV2SI 3 "register_operand" "r")))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  riscv_p_split_widen_mult (operands[0], operands[1], operands[2], operands[3],
			    <CODE> == ZERO_EXTEND, false);
  DONE;
}
  [(set_attr "type" "simd")
   (set_attr "length" "12")])

(define_insn_and_split "*pwmacc<su>mixedpv2hi3_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(plus:PV2SI
	  (mult:PV2SI
	    (any_extend:PV2SI (match_operand:PV2HI 1 "register_operand" "r"))
	    (<rvp_other_extend>:PV2SI
	      (match_operand:PV2HI 2 "register_operand" "r")))
	  (match_operand:PV2SI 3 "register_operand" "r")))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  if (<CODE> == ZERO_EXTEND)
    std::swap (operands[1], operands[2]);
  riscv_p_split_widen_mult (operands[0], operands[1], operands[2], operands[3],
			    false, true);
  DONE;
}
  [(set_attr "type" "simd")
   (set_attr "length" "16")])

(define_insn_and_split "mulpv2hi3"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (mult:PV2HI (match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  /* PV2HI is a 32-bit word containing two 16-bit elements [e0, e1].
     mul.h00 multiplies lower 16-bit elements: result in lower 16 bits
     mul.h11 multiplies upper 16-bit elements: result in lower 16 bits
     We pack them: (mul.h11 << 16) | (mul.h00 & 0xFFFF) */

  rtx temp_e0 = gen_reg_rtx (SImode);  /* element 0 result */
  rtx temp_e1 = gen_reg_rtx (SImode);  /* element 1 result */

  /* mul_h00 expects HImode operands: extract lower 16 bits as HImode */
  rtx src1_lo = gen_lowpart (HImode, operands[1]);
  rtx src2_lo = gen_lowpart (HImode, operands[2]);

  /* mul_h11 expects SImode operands, so convert PV2HI to SI for the pattern */
  rtx src1_si = gen_lowpart (SImode, operands[1]);
  rtx src2_si = gen_lowpart (SImode, operands[2]);

  emit_insn (gen_mulhisi3 (temp_e0, src1_lo, src2_lo));
  emit_insn (gen_mul_h11 (temp_e1, src1_si, src2_si));

  rtx result_lo = gen_lowpart (HImode, temp_e0);
  rtx result_hi = gen_lowpart (HImode, temp_e1);
  /* The low product occupies the low bits on either endian target.
     VEC_CONCAT describes element order, so use bitwise RTL instead when
     that order differs.  Retain little-endian lane folding otherwise.  */
  if (TARGET_BIG_ENDIAN)
    emit_insn (gen_riscv_xpack_si_hi_2
	       (gen_lowpart (SImode, operands[0]), temp_e1, GEN_INT (16),
		result_lo));
  else
    emit_insn (gen_ppaire_concatpv2hi (operands[0], result_lo, result_hi));

  DONE;
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*packed_mul_h_b00"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (mult:PV2HI (vec_concat:PV2HI 
                      (sign_extend:HI (subreg:QI (match_operand:PV4QI 1 "register_operand" "r") 0))
                      (subreg:HI (sign_extract:SI (subreg:SI (match_dup 1) 0)
                                                  (const_int 8)
                                                  (const_int 16)) 0))
                    (vec_concat:PV2HI 
                      (sign_extend:HI (subreg:QI (match_operand:PV4QI 2 "register_operand" "r") 0))
                      (subreg:HI (sign_extract:SI (subreg:SI (match_dup 2) 0)
                                                  (const_int 8)
                                                  (const_int 16)) 0))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmul.h.b00\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*packed_mul_h_b01"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (mult:PV2HI (vec_concat:PV2HI
                      (ashiftrt:HI (subreg:HI (match_operand:PV4QI 1 "register_operand" "r") 0)
                                   (const_int 8))
                      (subreg:HI (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                              (const_int 24)) 0))
                    (vec_concat:PV2HI
                      (sign_extend:HI (subreg:QI (match_operand:PV4QI 2 "register_operand" "r") 0))
                      (subreg:HI (sign_extract:SI (subreg:SI (match_dup 2) 0)
                                                  (const_int 8)
                                                  (const_int 16)) 0))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmul.h.b01\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*packed_mul_h_b01_alt"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (mult:PV2HI (vec_concat:PV2HI
                      (sign_extend:HI (subreg:QI (match_operand:PV4QI 1 "register_operand" "r") 0))
                      (subreg:HI (sign_extract:SI (subreg:SI (match_dup 1) 0)
                                                  (const_int 8)
                                                  (const_int 16)) 0))
                    (vec_concat:PV2HI
                      (ashiftrt:HI (subreg:HI (match_operand:PV4QI 2 "register_operand" "r") 0)
                                   (const_int 8))
                      (subreg:HI (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                              (const_int 24)) 0))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmul.h.b01\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*packed_mul_h_b11"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (mult:PV2HI (vec_concat:PV2HI
                      (ashiftrt:HI (subreg:HI (match_operand:PV4QI 1 "register_operand" "r") 0)
                                   (const_int 8))
                      (subreg:HI (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                              (const_int 24)) 0))
                    (vec_concat:PV2HI
                      (ashiftrt:HI (subreg:HI (match_operand:PV4QI 2 "register_operand" "r") 0)
                                   (const_int 8))
                      (subreg:HI (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                              (const_int 24)) 0))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmul.h.b11\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; 8-byte vectors: RV64 single register, RV32 register pair
;; riscv_hard_regno_mode_ok rejects odd base registers for 8-byte modes on
;; RVP+RV32, so "r" is sufficient; no separate register-pair constraint needed.
(define_insn "<rvp_optab><mode>3"
  [(set (match_operand:PV64 0 "register_operand" "=r")
	(rvp_binop:PV64 (match_operand:PV64 1 "register_operand" " r")
			(match_operand:PV64 2 "register_operand" " r")))]
  "TARGET_RVP"
  "<rvp_insn>.%d0\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; 8-byte packed vector negation (PV8QI/PV4HI/PV2SI, RV64 single reg,
;; RV32 reg pair).  pneg.<d><b,h,w> rd, rs is an assembler alias for
;; psub.<d><b,h,w> rd, x0, rs.
(define_insn "neg<mode>2"
  [(set (match_operand:PV64 0 "register_operand" "=r")
	(neg:PV64 (match_operand:PV64 1 "register_operand" " r")))]
  "TARGET_RVP"
  "pneg.%d0\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; 4-byte packed vector shift (PV4QI/PV2HI, RV32 and RV64).
;; The standard ashl/lshr/ashr optabs match directly without broadcasting
;; the amount into a vector first.
(define_insn "<rvp_shift_optab><mode>3"
  [(set (match_operand:PV32 0 "register_operand" "=r, r")
	(shift_op:PV32
	  (match_operand:PV32 1 "register_operand" "r, r")
	  (match_operand:SI 2 "reg_or_int_operand" "r, I")))]
  "TARGET_RVP"
  "@
   <rvp_shift_insn>.<rvp_width>s\t%0,%1,%2
   <rvp_shift_insn>i.<rvp_width>\t%0,%1,%2"
  [(set_attr "type" "shift")
   (set_attr "mode" "<MODE>")])

;; 8-byte packed vector shift: RV64 single register, RV32 register pair
(define_insn "<rvp_shift_optab><mode>3"
  [(set (match_operand:PV64 0 "register_operand" "=r, r")
	(shift_op:PV64
	  (match_operand:PV64 1 "register_operand" "r, r")
	  (match_operand:SI 2 "reg_or_int_operand" "r, I")))]
  "TARGET_RVP"
  "@
   <rvp_shift_insn>.%d0s\t%0,%1,%2
   <rvp_shift_insn>i.%d0\t%0,%1,%2"
  [(set_attr "type" "shift")
   (set_attr "mode" "<MODE>")])

;; Packed multiply high for the single-register modes (pmulh.b/.h/.w).
(define_insn "<mulh_prefix>mul<mode>3_highpart"
  [(set (match_operand:PVMULH1 0 "register_operand" "=r")
        (any_mulh:PVMULH1
          (match_operand:PVMULH1 1 "register_operand" "r")
          (match_operand:PVMULH1 2 "register_operand" "r")))]
  "TARGET_RVP"
  "<pmulh_mnem>.<rvp_width>\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; Packed multiply high for the 8-byte byte/halfword modes.  PMULH has no
;; double-wide encoding, so RV32 (register pair) splits into two single-register
;; pmulh while RV64 stays a single instruction.  The RV32 alternative is
;; early-clobber so a crossed destination/source pair cannot clobber a source
;; half mid-split.
(define_insn_and_split "<mulh_prefix>mul<mode>3_highpart"
  [(set (match_operand:PV64QH 0 "register_operand" "=r,&r")
        (any_mulh:PV64QH
          (match_operand:PV64QH 1 "register_operand" "r,r")
          (match_operand:PV64QH 2 "register_operand" "r,r")))]
  "TARGET_RVP"
  "@
   <pmulh_mnem>.<rvp_width>\t%0,%1,%2
   #"
  "&& !TARGET_64BIT && reload_completed"
  [(set (match_dup 3) (any_mulh:<rvp_pairhalf> (match_dup 5) (match_dup 7)))
   (set (match_dup 4) (any_mulh:<rvp_pairhalf> (match_dup 6) (match_dup 8)))]
  {
    operands[3] = gen_lowpart (<rvp_pairhalf>mode, operands[0]);
    operands[4] = gen_highpart (<rvp_pairhalf>mode, operands[0]);
    operands[5] = gen_lowpart (<rvp_pairhalf>mode, operands[1]);
    operands[6] = gen_highpart (<rvp_pairhalf>mode, operands[1]);
    operands[7] = gen_lowpart (<rvp_pairhalf>mode, operands[2]);
    operands[8] = gen_highpart (<rvp_pairhalf>mode, operands[2]);
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")
   (set_attr_alternative "enabled"
     [(if_then_else (match_test "TARGET_64BIT")
	(const_string "yes") (const_string "no"))
      (if_then_else (match_test "!TARGET_64BIT")
	(const_string "yes") (const_string "no"))])])

;; MACC.H00/MACCU.H00: Widening multiply-accumulate (bottom x bottom)
;; MACC.H00:  rd = rd + sext(rs1[15:0]) * sext(rs2[15:0])
;; MACCU.H00: rd = rd + zext(rs1[15:0]) * zext(rs2[15:0])
;; Pattern name with * to work alongside the [u]maddhisi4 expander in riscv.md
(define_insn "*rvp_<u>maddhisi4"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI (mult:SI (any_extend:SI
			    (match_operand:HI 1 "register_operand" "r"))
			  (any_extend:SI
			    (match_operand:HI 2 "register_operand" "r")))
		 (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "macc<u>.h00\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; MACC.W00/MACCU.W00: Widening multiply-accumulate (bottom x bottom)
;; MACC.W00:  rd = rd + sext(rs1[31:0]) * sext(rs2[31:0])
;; MACCU.W00: rd = rd + zext(rs1[31:0]) * zext(rs2[31:0])
;; Pattern name with * to work alongside the [u]maddsidi4 expander below
(define_insn "*rvp_<u>macc_w00"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(plus:DI (mult:DI (any_extend:DI
			    (match_operand:SI 1 "register_operand" "r"))
			  (any_extend:DI
			    (match_operand:SI 2 "register_operand" "r")))
		 (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && TARGET_64BIT"
  "macc<u>.w00\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "DI")])

;; MACC.H01/MACCU.H01: Multiply-accumulate (bottom x top)
;; MACC.H01:  rd = rd + sext(rs1[15:0]) * sext(rs2[31:16])
;; MACCU.H01: rd = rd + zext(rs1[15:0]) * zext(rs2[31:16])
;; Note: H10 (top x bottom) can be achieved by swapping operands.
;; GCC canonicalizes to [u]maddhisi4tb (top x bottom in RTL order).
(define_insn "<u>maddhisi4tb"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI (mult:SI (<su_shiftrt>:SI
			    (match_operand:SI 1 "register_operand" "r")
			    (const_int 16))
			  (any_extend:SI
			    (match_operand:HI 2 "register_operand" "r")))
		 (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "macc<u>.h01\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; MACC.W01/MACCU.W01: Multiply-accumulate (bottom x top)
;; MACC.W01:  rd = rd + sext(rs1[31:0]) * sext(rs2[63:32])
;; MACCU.W01: rd = rd + zext(rs1[31:0]) * zext(rs2[63:32])
;; Note: W10 (top x bottom) can be achieved by swapping operands.
;; GCC canonicalizes to [u]maddsidi4tb (top x bottom in RTL order).
(define_insn "<u>macc_w01"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(plus:DI (mult:DI (<su_shiftrt>:DI
			    (match_operand:DI 1 "register_operand" "r")
			    (const_int 32))
			  (any_extend:DI
			    (match_operand:SI 2 "register_operand" "r")))
		 (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && TARGET_64BIT"
  "macc<u>.w01\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "DI")])

;; MACC.H11/MACCU.H11: Multiply-accumulate (top x top)
;; MACC.H11:  rd = rd + sext(rs1[31:16]) * sext(rs2[31:16])
;; MACCU.H11: rd = rd + zext(rs1[31:16]) * zext(rs2[31:16])
(define_insn "<shiftrt_su>maddhisi4tt"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI (mult:SI (any_shiftrt:SI
			    (match_operand:SI 1 "register_operand" "r")
			    (const_int 16))
			  (any_shiftrt:SI
			    (match_operand:SI 2 "register_operand" "r")
			    (const_int 16)))
		 (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "macc<shiftrt_su>.h11\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; MACC.W11/MACCU.W11: Multiply-accumulate (top x top)
;; MACC.W11:  rd = rd + sext(rs1[63:32]) * sext(rs2[63:32])
;; MACCU.W11: rd = rd + zext(rs1[63:32]) * zext(rs2[63:32])
(define_insn "<shiftrt_su>macc_w11"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(plus:DI (mult:DI (any_shiftrt:DI
			    (match_operand:DI 1 "register_operand" "r")
			    (const_int 32))
			  (any_shiftrt:DI
			    (match_operand:DI 2 "register_operand" "r")
			    (const_int 32)))
		 (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && TARGET_64BIT"
  "macc<shiftrt_su>.w11\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "DI")])

;; usmulhisi3: Unsigned x Signed widening multiply (halfword -> word)
;; Standard pattern name from GCC internals.
;; GCC's convention: operand 1 is unsigned, operand 2 is signed.
;; MULSU.H00: rd = sext(rs1[15:0]) * zext(rs2[15:0])
;; Two patterns for different operand orderings from GCC.
(define_insn "usmulhisi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(mult:SI (zero_extend:SI
		   (match_operand:HI 1 "register_operand" "r"))
		 (sign_extend:SI
		   (match_operand:HI 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulsu.h00\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*usmulhisi3_alt"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(mult:SI (sign_extend:SI
		   (match_operand:HI 1 "register_operand" "r"))
		 (zero_extend:SI
		   (match_operand:HI 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulsu.h00\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; MULSU.H11: Signed x Unsigned widening multiply (top halfword -> word)
;; rd = sext(rs1[31:16]) * zext(rs2[31:16])
;; Two patterns for different operand orderings from GCC.
(define_insn "*usmulhisi3tt"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(mult:SI (lshiftrt:SI
		   (match_operand:SI 1 "register_operand" "r")
		   (const_int 16))
		 (ashiftrt:SI
		   (match_operand:SI 2 "register_operand" "r")
		   (const_int 16))))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulsu.h11\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*usmulhisi3tt_alt"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(mult:SI (ashiftrt:SI
		   (match_operand:SI 1 "register_operand" "r")
		   (const_int 16))
		 (lshiftrt:SI
		   (match_operand:SI 2 "register_operand" "r")
		   (const_int 16))))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulsu.h11\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "mul<shiftrt_su>_h11"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(mult:SI (shift_extend:SI
		   (match_operand:SI 1 "register_operand" "r")
		   (const_int 16))
		 (shift_extend:SI
		   (match_operand:SI 2 "register_operand" "r")
		   (const_int 16))))]
  "TARGET_RVP && !TARGET_64BIT"
  "mul<shiftrt_su>.h11\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*mul<shiftrt_su>_w11"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(mult:DI (shift_extend:DI
		   (match_operand:DI 1 "register_operand" "r")
		   (const_int 32))
		 (shift_extend:DI
		   (match_operand:DI 2 "register_operand" "r")
		   (const_int 32))))]
  "TARGET_RVP && TARGET_64BIT"
  "mul<shiftrt_su>.w11\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "DI")])

(define_insn "*mul<u>_h01"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(mult:SI (<su_shiftrt>:SI
		   (match_operand:SI 1 "register_operand" "r")
		   (const_int 16))
		 (any_extend:SI
		   (match_operand:HI 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_64BIT"
  "mul<u>.h01\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*mul<u>_w01"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(mult:DI (<su_shiftrt>:DI
		   (match_operand:DI 1 "register_operand" "r")
		   (const_int 32))
		 (any_extend:DI
		   (match_operand:SI 2 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT"
  "mul<u>.w01\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "DI")])

;; Intermediate pattern for MULH.H0.
;; Fuse the halfword sign-extend into the widening signed multiply so combine
;; can subsequently match the (product >> 16) highpart form as MULH.H0.  If the
;; highpart form is not built, split back into sext.h + wmul.
(define_insn_and_split "*rvp_mulh_h0_widen"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(mult:DI (sign_extend:DI (match_operand:HI 1 "register_operand" "r"))
		 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "#"
  "&& can_create_pseudo_p ()"
  [(const_int 0)]
{
  rtx tmp = gen_reg_rtx (SImode);
  emit_insn (gen_extendhisi2 (tmp, operands[1]));
  emit_insn (gen_rtx_SET (operands[0],
			  gen_rtx_MULT (DImode,
					gen_rtx_SIGN_EXTEND (DImode, tmp),
					gen_rtx_SIGN_EXTEND (DImode,
							     operands[2]))));
  DONE;
}
  [(set_attr "type" "imul")
   (set_attr "mode" "DI")])

;; MULH.H0: rd = (rs1 * sext(rs2[15:0])) >> 16
;; The signed 32x16 product is 48 bits; taking bits [47:16] of the 64-bit
;; product yields (hi_word << 16) | (lo_word >>u 16), which is the form combine
;; builds once *rvp_mulh_h0_widen has fused the halfword sign-extend into the
;; widening multiply.
(define_insn "*rvp_mulh_h0"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI
	  (lshiftrt:SI
	    (mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" "r"))
		     (match_operand:SI 2 "register_operand" "r"))
	    (const_int 16))
	  (ashift:SI
	    (subreg:SI
	      (mult:DI (sign_extend:DI (match_dup 1))
		       (sign_extend:DI (match_dup 2))) 4)
	    (const_int 16))))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "mulh.h0\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; Intermediate pattern for MULH.H1.
;; This is the generic 32x32 (product >> 16) form combine builds first; a later
;; substitution of the halfword extract into operand 1 turns it into
;; *rvp_mulh_h1.  If that substitution never happens, split back into a widening
;; multiply plus the shift/merge sequence this form came from.
(define_insn_and_split "*rvp_mulh_h1_inter"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI
	  (lshiftrt:SI
	    (mult:SI (match_operand:SI 1 "register_operand" "r")
		     (match_operand:SI 2 "register_operand" "r"))
	    (const_int 16))
	  (ashift:SI
	    (subreg:SI
	      (mult:DI (sign_extend:DI (match_dup 1))
		       (sign_extend:DI (match_dup 2))) 4)
	    (const_int 16))))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "#"
  "&& can_create_pseudo_p ()"
  [(const_int 0)]
{
  rtx prod = gen_reg_rtx (DImode);
  rtx lo = gen_reg_rtx (SImode);
  rtx hi = gen_reg_rtx (SImode);

  emit_insn (gen_mulsidi3 (prod, operands[1], operands[2]));
  emit_insn (gen_lshrsi3 (lo, gen_lowpart (SImode, prod), GEN_INT (16)));
  emit_insn (gen_ashlsi3 (hi, gen_highpart (SImode, prod), GEN_INT (16)));
  emit_insn (gen_addsi3 (operands[0], hi, lo));
  DONE;
}
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*rvp_mulh_h1"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (plus:SI
          (lshiftrt:SI
            (mult:SI (ashiftrt:SI (subreg:SI (match_operand:PV2HI 1 "register_operand" "r") 0)
                                  (const_int 16))
                     (match_operand:SI 2 "register_operand" "r"))
            (const_int 16))
          (ashift:SI
            (subreg:SI
              (mult:DI (sign_extend:DI
                         (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                      (const_int 16)))
                       (sign_extend:DI
                         (match_dup 2))) 4)
            (const_int 16))))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "mulh.h1\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])       

;; Intermediate rtl pattern for pm2wadd.h/pm2wsub.h
;; If combine does not fold this further into *pm2waddh_intermediate, split
;; it into a real mul.h11 (16x16->32 multiply) followed by a sign-extend to
;; DI, reusing the low word of the DI destination as the multiply's scratch.
;; The resulting sign_extend:DI is matched by *extendsidi2_rvp (wadd).
(define_insn_and_split "*widen_multiply_high_high_pv2hi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(mult:DI (sign_extend:DI
                   (ashiftrt:SI
		     (match_operand:SI 1 "register_operand" "r")
		     (const_int 16)))
		 (sign_extend:DI
                   (ashiftrt:SI
		     (match_operand:SI 2 "register_operand" "r")
		     (const_int 16)))))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "#"
  "&& reload_completed"
  [(set (match_dup 3)
	(mult:SI (ashiftrt:SI (match_dup 1) (const_int 16))
		 (ashiftrt:SI (match_dup 2) (const_int 16))))
   (set (match_dup 0)
	(sign_extend:DI (match_dup 3)))]
  {
    operands[3] = gen_lowpart (SImode, operands[0]);
  }
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; Intermediate rtl pattern for pm2wadd.h/pm2wsub.h
;; Same split strategy as above, using mul.h00 for the low-low case.
(define_insn_and_split "*widen_multiply_low_low_pv2hi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(mult:DI (sign_extend:DI
		   (match_operand:HI 1 "register_operand" "r"))
		 (sign_extend:DI
		   (match_operand:HI 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "#"
  "&& reload_completed"
  [(set (match_dup 3)
	(mult:SI (sign_extend:SI (match_dup 1))
		 (sign_extend:SI (match_dup 2))))
   (set (match_dup 0)
	(sign_extend:DI (match_dup 3)))]
  {
    operands[3] = gen_lowpart (SImode, operands[0]);
  }
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; Intermediate rtl pattern for PM2WADD.H combine
;; If combine does not fold this all the way into *pm2waddh, split into a
;; widening high*high multiply (staged in operand 0, further split by
;; *widen_multiply_high_high_pv2hi into mul.h11 + sign-extend) followed by a
;; wmacc accumulating the low*low term. wmacc ties its accumulator input to
;; its output via the "0" constraint, so operand 0 must be an aligned
;; register pair ("R"), like *smulsidi3_rvp/*rvp_widen_smaddsidi4 require.
(define_insn_and_split "*pm2waddh_intermediate"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                          (sign_extend:DI (match_operand:SI 2 "register_operand" "r")))
                 (mult:DI (sign_extend:DI (ashiftrt:SI (subreg:SI (match_operand:PV2HI 3 "register_operand" "r") 0)
                                                       (const_int 16)))
                          (sign_extend:DI (ashiftrt:SI (subreg:SI (match_operand:PV2HI 4 "register_operand" "r") 0)
                                                       (const_int 16))))))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "#"
  "&& reload_completed"
  [(set (match_dup 0)
	(mult:DI (sign_extend:DI (ashiftrt:SI (subreg:SI (match_dup 3) 0) (const_int 16)))
		 (sign_extend:DI (ashiftrt:SI (subreg:SI (match_dup 4) 0) (const_int 16)))))
   (set (match_dup 0)
	(plus:DI (mult:DI (sign_extend:DI (match_dup 1)) (sign_extend:DI (match_dup 2)))
		 (match_dup 0)))]
  ""
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])                

 (define_insn "*pm2waddh"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (plus:DI (mult:DI (sign_extend:DI (subreg:HI (match_operand:PV2HI 1 "register_operand" "r") 0))
                          (sign_extend:DI (subreg:HI (match_operand:PV2HI 2 "register_operand" "r") 0)))
                 (mult:DI (sign_extend:DI (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                                       (const_int 16)))
                          (sign_extend:DI (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                                       (const_int 16))))))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "pm2wadd.h\t%0, %1, %2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; Intermediate rtl pattern for PM2WADD.HX combine
;; Not directly matched by a single instruction:
;; each mixes one full-SI factor with a sign-extended halfword extracted
;; from a PV2HI register, and there's no fused "mulw01"-style op for that.
;; So materialize both extracted halves with srai into scratch regs, then
;; use wmul + wmacc (both requiring an aligned "R" pair, tied to operand 0
;; via wmacc's "0" constraint, hence operand 0 is "R" here too).
(define_insn_and_split "*pm2waddhx_intermediate"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                          (sign_extend:DI (ashiftrt:SI
                                            (subreg:SI (match_operand:PV2HI 2 "register_operand" "r") 0)
                                            (const_int 16))))
                 (mult:DI (sign_extend:DI (ashiftrt:SI (subreg:SI (match_operand:PV2HI 3 "register_operand" "r") 0)
                                                       (const_int 16)))
                          (sign_extend:DI (match_operand:SI 4 "register_operand" "r")))))
   (clobber (match_scratch:SI 5 "=&r"))
   (clobber (match_scratch:SI 6 "=&r"))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "#"
  "&& reload_completed"
  [(set (match_dup 5) (ashiftrt:SI (subreg:SI (match_dup 2) 0) (const_int 16)))
   (set (match_dup 6) (ashiftrt:SI (subreg:SI (match_dup 3) 0) (const_int 16)))
   (set (match_dup 0)
	(mult:DI (sign_extend:DI (match_dup 1)) (sign_extend:DI (match_dup 5))))
   (set (match_dup 0)
	(plus:DI (mult:DI (sign_extend:DI (match_dup 6)) (sign_extend:DI (match_dup 4)))
		 (match_dup 0)))]
  ""
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*pm2waddhx"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (plus:DI (mult:DI (sign_extend:DI (subreg:HI (match_operand:PV2HI 1 "register_operand" "r") 0))
                          (sign_extend:DI (ashiftrt:SI
                                            (subreg:SI (match_operand:PV2HI 2 "register_operand" "r") 0)
                                            (const_int 16))))
                 (mult:DI (sign_extend:DI (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                                       (const_int 16)))
                          (sign_extend:DI (subreg:HI (match_dup 2) 0)))))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "pm2wadd.hx\t%0, %1, %2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*pm2add_h"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (plus:SI (mult:SI (sign_extend:SI (subreg:HI (match_operand:PV2HI 1 "register_operand" "r") 0))
                          (sign_extend:SI (subreg:HI (match_operand:PV2HI 2 "register_operand" "r") 0)))
                 (mult:SI (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                       (const_int 16))
                          (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                       (const_int 16)))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2add.h\t%0, %1, %2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*pm2addhx"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (plus:SI (mult:SI (ashiftrt:SI (subreg:SI (match_operand:PV2HI 1 "register_operand" "r") 0)
                                       (const_int 16))
                          (sign_extend:SI (subreg:HI (match_operand:PV2HI 2 "register_operand" "r") 0)))
                 (mult:SI (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                       (const_int 16))
                          (sign_extend:SI (subreg:HI (match_dup 1) 0)))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2add.hx\t%0, %2, %1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

 (define_insn "*pm2wsubh"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (minus:DI (mult:DI (sign_extend:DI (subreg:HI (match_operand:PV2HI 1 "register_operand" "r") 0))
                           (sign_extend:DI (subreg:HI (match_operand:PV2HI 2 "register_operand" "r") 0)))
                  (mult:DI (sign_extend:DI (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                                        (const_int 16)))
                           (sign_extend:DI (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                                        (const_int 16))))))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "pm2wsub.h\t%0, %1, %2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*pm2sub_h"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (minus:SI (mult:SI (sign_extend:SI (subreg:HI (match_operand:PV2HI 1 "register_operand" "r") 0))
                          (sign_extend:SI (subreg:HI (match_operand:PV2HI 2 "register_operand" "r") 0)))
                 (mult:SI (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                       (const_int 16))
                          (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                       (const_int 16)))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2sub.h\t%0, %2, %1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*pm2adda_h"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (plus:SI
          (plus:SI (mult:SI (sign_extend:SI (subreg:HI (match_operand:PV2HI 1 "register_operand" "r") 0))
                            (sign_extend:SI (subreg:HI (match_operand:PV2HI 2 "register_operand" "r") 0)))
                   (mult:SI (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                         (const_int 16))
                            (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                         (const_int 16))))
          (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2adda.h\t%0, %1, %2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*pm2suba_h"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (plus:SI
          (minus:SI (mult:SI (sign_extend:SI (subreg:HI (match_operand:PV2HI 1 "register_operand" "r") 0))
                             (sign_extend:SI (subreg:HI (match_operand:PV2HI 2 "register_operand" "r") 0)))
                    (mult:SI (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                          (const_int 16))
                             (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                          (const_int 16))))
          (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2suba.h\t%0, %2, %1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*pm2suba_h_alt"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (plus:SI
          (minus:SI (mult:SI (sign_extend:SI (subreg:HI (match_operand:PV2HI 1 "register_operand" "r") 0))
                             (sign_extend:SI (subreg:HI (match_operand:PV2HI 2 "register_operand" "r") 0)))
                    (mult:SI (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                          (const_int 16))
                             (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                          (const_int 16))))
          (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2suba.h\t%0, %1, %2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*pm2subh_alt"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (minus:SI (mult:SI (sign_extend:SI (subreg:HI (match_operand:PV2HI 1 "register_operand" "r") 0))
                          (sign_extend:SI (subreg:HI (match_operand:PV2HI 2 "register_operand" "r") 0)))
                 (mult:SI (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                       (const_int 16))
                          (ashiftrt:SI (subreg:SI (match_dup 1) 0)
                                       (const_int 16)))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2sub.h\t%0, %2, %1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*pm2subhx"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (minus:SI (mult:SI (ashiftrt:SI (subreg:SI (match_operand:PV2HI 1 "register_operand" "r") 0)
                                       (const_int 16))
                          (sign_extend:SI (subreg:HI (match_operand:PV2HI 2 "register_operand" "r") 0)))
                 (mult:SI (ashiftrt:SI (subreg:SI (match_dup 2) 0)
                                       (const_int 16))
                          (sign_extend:SI (subreg:HI (match_dup 1) 0)))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2sub.hx\t%0, %2, %1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; MACCSU.H00: Signed-unsigned multiply-accumulate (bottom x bottom)
;; rd = rd + sext(rs1[15:0]) * zext(rs2[15:0])
;; Two patterns for different operand orderings from GCC.
(define_insn "*rvp_usmaddhisi4"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI (mult:SI (zero_extend:SI
			    (match_operand:HI 1 "register_operand" "r"))
			  (sign_extend:SI
			    (match_operand:HI 2 "register_operand" "r")))
		 (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "maccsu.h00\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*rvp_usmaddhisi4_alt"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI (mult:SI (sign_extend:SI
			    (match_operand:HI 1 "register_operand" "r"))
			  (zero_extend:SI
			    (match_operand:HI 2 "register_operand" "r")))
		 (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "maccsu.h00\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; MACCSU.W00: Signed-unsigned multiply-accumulate (bottom x bottom)
(define_insn "*rvp_usmaddsidi4"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(plus:DI (mult:DI (zero_extend:DI
			    (match_operand:SI 1 "register_operand" "r"))
			  (sign_extend:DI
			    (match_operand:SI 2 "register_operand" "r")))
		 (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && TARGET_64BIT"
  "maccsu.w00\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "DI")])

(define_insn "*rvp_usmaddsidi4_alt"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(plus:DI (mult:DI (sign_extend:DI
			    (match_operand:SI 1 "register_operand" "r"))
			  (zero_extend:DI
			    (match_operand:SI 2 "register_operand" "r")))
		 (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && TARGET_64BIT"
  "maccsu.w00\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "DI")])

;; MACCSU.H11: Signed-unsigned multiply-accumulate (top x top)
;; rd = rd + sext(rs1[31:16]) * zext(rs2[31:16])
;; Two patterns for different operand orderings from GCC.
(define_insn "*rvp_usmaddhisi4tt"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI (mult:SI (lshiftrt:SI
			    (match_operand:SI 1 "register_operand" "r")
			    (const_int 16))
			  (ashiftrt:SI
			    (match_operand:SI 2 "register_operand" "r")
			    (const_int 16)))
		 (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "maccsu.h11\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*rvp_usmaddhisi4tt_alt"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI (mult:SI (ashiftrt:SI
			    (match_operand:SI 1 "register_operand" "r")
			    (const_int 16))
			  (lshiftrt:SI
			    (match_operand:SI 2 "register_operand" "r")
			    (const_int 16)))
		 (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "maccsu.h11\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; MACCSU.W11: Signed-unsigned multiply-accumulate (top x top)
(define_insn "*rvp_usmaddsidi4tt"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(plus:DI (mult:DI (lshiftrt:DI
			    (match_operand:DI 1 "register_operand" "r")
			    (const_int 32))
			  (ashiftrt:DI
			    (match_operand:DI 2 "register_operand" "r")
			    (const_int 32)))
		 (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && TARGET_64BIT"
  "maccsu.w11\t%0,%2,%1"
  [(set_attr "type" "imul")
   (set_attr "mode" "DI")])

(define_insn "*rvp_usmaddsidi4tt_alt"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(plus:DI (mult:DI (ashiftrt:DI
			    (match_operand:DI 1 "register_operand" "r")
			    (const_int 32))
			  (lshiftrt:DI
			    (match_operand:DI 2 "register_operand" "r")
			    (const_int 32)))
		 (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && TARGET_64BIT"
  "maccsu.w11\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "DI")])

;; Average the full-precision sum or difference, rounding toward -Inf.
;; Extend before arithmetic: a wrapping narrow PLUS or MINUS followed by
;; a shift is not equivalent.  This also preserves the borrow bit in an
;; unsigned subtraction before truncating the shifted result.
(define_expand "<u><savg_optab><mode>3_floor"
  [(set (match_operand:PVMOVE 0 "register_operand")
	(truncate:PVMOVE
	  (ashiftrt:<PVALL_EXT>
	    (avg_op:<PVALL_EXT>
	      (any_extend:<PVALL_EXT>
		(match_operand:PVMOVE 1 "register_operand"))
	      (any_extend:<PVALL_EXT>
		(match_operand:PVMOVE 2 "register_operand")))
	    (const_int 1))))]
  "TARGET_RVP")

(define_insn "*rvp_<avg_insn><u><mode>"
  [(set (match_operand:PVALL 0 "register_operand" "=r")
	(truncate:PVALL
	  (ashiftrt:<PVALL_EXT>
	    (avg_op:<PVALL_EXT>
	      (any_extend:<PVALL_EXT>
		(match_operand:PVALL 1 "register_operand" "r"))
	      (any_extend:<PVALL_EXT>
		(match_operand:PVALL 2 "register_operand" "r")))
	    (const_int 1))))]
  "TARGET_RVP"
  "<avg_insn><u>.<rvp_width>\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

(define_insn "*rvp_<avg_insn><u><mode>_pair"
  [(set (match_operand:PV64 0 "register_operand" "=R")
	(truncate:PV64
	  (ashiftrt:<PVALL_EXT>
	    (avg_op:<PVALL_EXT>
	      (any_extend:<PVALL_EXT>
		(match_operand:PV64 1 "register_operand" "r"))
	      (any_extend:<PVALL_EXT>
		(match_operand:PV64 2 "register_operand" "r")))
	    (const_int 1))))]
  "TARGET_RVP && !TARGET_64BIT"
  "<avg_insn><u>.<rvp_dwidth>\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; Averaging a signed value with one is a rounded one-bit shift.  Match
;; the widened addition so that the largest input cannot wrap.  These
;; insns also preserve the single-instruction form after GIMPLE folding.
(define_insn "*rvp_round_avg_one_<mode>"
  [(set (match_operand:RVP_ROUND 0 "register_operand" "=r")
	(truncate:RVP_ROUND
	  (ashiftrt:<PVALL_EXT>
	    (plus:<PVALL_EXT>
	      (sign_extend:<PVALL_EXT>
		(match_operand:RVP_ROUND 1 "register_operand" "r"))
	      (match_operand:<PVALL_EXT> 2 "const_1_operand" ""))
	    (const_int 1))))]
  "TARGET_RVP && (TARGET_64BIT || <MODE>mode == PV2HImode)"
  "psrari.<rvp_width>\t%0,%1,1"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "*rvp_round_avg_one_<mode>_pair"
  [(set (match_operand:PVHW 0 "register_operand" "=R")
	(truncate:PVHW
	  (ashiftrt:<PVALL_EXT>
	    (plus:<PVALL_EXT>
	      (sign_extend:<PVALL_EXT>
		(match_operand:PVHW 1 "register_operand" "r"))
	      (match_operand:<PVALL_EXT> 2 "const_1_operand" ""))
	    (const_int 1))))]
  "TARGET_RVP && !TARGET_64BIT"
  "psrari.<rvp_dwidth>\t%0,%1,1"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;; Vector comparison expander for signed comparisons
(define_expand "vec_cmp<mode><mode>"
  [(set (match_operand:PCMP 0 "register_operand")
	(match_operator:PCMP 1 "comparison_operator"
	  [(match_operand:PCMP 2 "register_operand")
	   (match_operand:PCMP 3 "register_operand")]))]
  "TARGET_RVP"
{
  riscv_p_expand_vec_cmp (operands);
  DONE;
})

;; Vector comparison expander for unsigned comparisons
(define_expand "vec_cmpu<mode><mode>"
  [(set (match_operand:PCMP 0 "register_operand")
	(match_operator:PCMP 1 "comparison_operator"
	  [(match_operand:PCMP 2 "register_operand")
	   (match_operand:PCMP 3 "register_operand")]))]
  "TARGET_RVP"
{
  riscv_p_expand_vec_cmp (operands);
  DONE;
})

;; Vector conditional mask operation
;; Implements: result = mask ? op1 : op2
;; For each element i: result[i] = mask[i] ? op1[i] : op2[i]
(define_expand "vcond_mask_<mode><mode>"
  [(set (match_operand:PCMP 0 "register_operand")
	(if_then_else:PCMP
	  (match_operand:PCMP 3 "register_operand")
	  (match_operand:PCMP 1 "nonmemory_operand")
	  (match_operand:PCMP 2 "nonmemory_operand")))]
  "TARGET_RVP"
{
  riscv_p_expand_vcond_mask (operands);
  DONE;
})

;; Keep encodable masks visible until the packed operations are split.
(define_expand "<optab><mode>3"
  [(set (match_operand:PVMOVE 0 "register_operand")
	(any_bitwise:PVMOVE (match_operand:PVMOVE 1 "register_operand")
			   (match_operand:PVMOVE 2 "riscv_p_bitwise_operand")))]
  "TARGET_RVP")

;; Bitwise operations for 4-byte vector modes (always single register).
(define_insn "*rvp_<optab><mode>3"
  [(set (match_operand:PV32 0 "register_operand" "=r")
	(any_bitwise:PV32 (match_operand:PV32 1 "register_operand" "r")
			  (match_operand:PV32 2 "register_operand" "r")))]
  "TARGET_RVP"
  "<insn>\t%0,%1,%2"
  [(set_attr "type" "logical")
   (set_attr "mode" "<MODE>")])

;; Bitwise operations for 8-byte vectors on RV64 (single register instruction).
(define_insn "*rvp_<optab><mode>3_rv64"
  [(set (match_operand:PV64 0 "register_operand" "=r")
	(any_bitwise:PV64 (match_operand:PV64 1 "register_operand" "r")
			  (match_operand:PV64 2 "register_operand" "r")))]
  "TARGET_RVP && TARGET_64BIT"
  "<insn>\t%0,%1,%2"
  [(set_attr "type" "logical")
   (set_attr "mode" "<MODE>")])

;; Bitwise operations for 8-byte vectors on RV32 (register pair).
;; Early-clobber prevents crossed overlap with a source pair.  The tied
;; alternatives allow exact overlap with one source without extra moves;
;; the other source still cannot overlap that destination pair.
(define_insn_and_split "<optab><mode>3_rv32"
  [(set (match_operand:PV64 0 "register_operand" "=&r,&r,&r")
	(any_bitwise:PV64 (match_operand:PV64 1 "register_operand" "0,r,r")
			  (match_operand:PV64 2 "register_operand" "r,0,r")))]
  "TARGET_RVP && !TARGET_64BIT"
  "#"
  "&& reload_completed"
  [(set (match_dup 3) (any_bitwise:SI (match_dup 5) (match_dup 7)))
   (set (match_dup 4) (any_bitwise:SI (match_dup 6) (match_dup 8)))]
  {
    operands[3] = gen_lowpart (SImode, operands[0]);
    operands[4] = gen_highpart (SImode, operands[0]);
    operands[5] = gen_lowpart (SImode, operands[1]);
    operands[6] = gen_highpart (SImode, operands[1]);
    operands[7] = gen_lowpart (SImode, operands[2]);
    operands[8] = gen_highpart (SImode, operands[2]);
  }
  [(set_attr "type" "logical")
   (set_attr "mode" "<MODE>")])

;; Each scalar word uses an ordinary logical immediate.  With just one
;; register input, order the writes to preserve any overlapping source.
;; Expose RV32 scalar-pair inputs before allocation so their independent
;; words need not remain a single live range.  Keep packed inputs intact.
(define_insn_and_split "*rvp_<optab><mode>3_imm"
  [(set (match_operand:PVMOVE 0 "register_operand" "=r")
	(any_bitwise:PVMOVE
	  (match_operand:PVMOVE 1 "register_operand" "r")
	  (match_operand:PVMOVE 2 "riscv_p_bitwise_operand" "Wpl")))]
  "TARGET_RVP && riscv_p_bitwise_imm_p (operands[2])"
  "#"
  "&& (reload_completed
       || (!TARGET_64BIT && can_create_pseudo_p ()
	   && known_eq (GET_MODE_SIZE (<MODE>mode), 8)
	   && SUBREG_P (operands[1])
	   && GET_MODE (SUBREG_REG (operands[1])) == DImode))"
  [(const_int 0)]
{
  unsigned int bytes = GET_MODE_SIZE (<MODE>mode).to_constant ();
  scalar_int_mode part_mode = bytes == 4 || !TARGET_64BIT ? SImode : DImode;
  unsigned int part_bytes = GET_MODE_SIZE (part_mode);
  unsigned int count = bytes / part_bytes;
  rtx dest[2], src[2], mask[2];
  for (unsigned int i = 0; i < count; ++i)
    {
      unsigned int offset = i * part_bytes;
      dest[i] = simplify_gen_subreg (part_mode, operands[0], <MODE>mode,
				    offset);
      src[i] = simplify_gen_subreg (part_mode, operands[1], <MODE>mode,
				   offset);
      mask[i] = simplify_gen_subreg (part_mode, operands[2], <MODE>mode,
				    offset);
    }
  if (count == 2 && reg_overlap_mentioned_p (dest[0], src[1]))
    {
      std::swap (dest[0], dest[1]);
      std::swap (src[0], src[1]);
      std::swap (mask[0], mask[1]);
    }
  for (unsigned int i = 0; i < count; ++i)
    emit_insn (gen_rtx_SET (dest[i],
			   gen_rtx_<CODE> (part_mode, src[i], mask[i])));
  DONE;
}
  [(set_attr "type" "logical")
   (set_attr "mode" "<MODE>")
   (set (attr "length")
	(if_then_else (match_test "!TARGET_64BIT
				  && known_eq (GET_MODE_SIZE (<MODE>mode), 8)")
		      (const_int 8) (const_int 4)))])

;; Packed forms of the Zbb inverted logical operations.  Keep the complete
;; expression until after reload so combine can also build masked moves.
;; On RV32, packed pairs start at even registers: complete source pairs can
;; overlap the destination, but their low and high halves cannot cross.
(define_insn_and_split "*rvp_<optab>_not<mode>"
  [(set (match_operand:PVMOVE 0 "register_operand" "=r")
	(bitmanip_bitwise:PVMOVE
	  (not:PVMOVE (match_operand:PVMOVE 1 "register_operand" "r"))
	  (match_operand:PVMOVE 2 "register_operand" "r")))]
  "TARGET_RVP && (TARGET_ZBB || TARGET_ZBKB)"
{
  if (!TARGET_64BIT && known_eq (GET_MODE_SIZE (<MODE>mode), 8))
    return "#";
  return "<insn>n\t%0,%2,%1";
}
  "&& !TARGET_64BIT && known_eq (GET_MODE_SIZE (<MODE>mode), 8)
   && reload_completed"
  [(set (match_dup 3)
	(bitmanip_bitwise:SI (not:SI (match_dup 4)) (match_dup 5)))
   (set (match_dup 6)
	(bitmanip_bitwise:SI (not:SI (match_dup 7)) (match_dup 8)))]
{
  for (unsigned int i = 0; i < 3; ++i)
    {
      operands[i + 3] = gen_lowpart (SImode, operands[i]);
      operands[i + 6] = gen_highpart (SImode, operands[i]);
    }
}
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "<MODE>")
   (set (attr "length")
	(if_then_else (match_test "!TARGET_64BIT
				  && known_eq (GET_MODE_SIZE (<MODE>mode), 8)")
		      (const_int 8) (const_int 4)))])

(define_insn_and_split "*rvp_xor_not<mode>"
  [(set (match_operand:PVMOVE 0 "register_operand" "=r")
	(not:PVMOVE
	  (xor:PVMOVE (match_operand:PVMOVE 1 "register_operand" "r")
		      (match_operand:PVMOVE 2 "register_operand" "r"))))]
  "TARGET_RVP && (TARGET_ZBB || TARGET_ZBKB)"
{
  if (!TARGET_64BIT && known_eq (GET_MODE_SIZE (<MODE>mode), 8))
    return "#";
  return "xnor\t%0,%1,%2";
}
  "&& !TARGET_64BIT && known_eq (GET_MODE_SIZE (<MODE>mode), 8)
   && reload_completed"
  [(set (match_dup 3) (not:SI (xor:SI (match_dup 4) (match_dup 5))))
   (set (match_dup 6) (not:SI (xor:SI (match_dup 7) (match_dup 8))))]
{
  for (unsigned int i = 0; i < 3; ++i)
    {
      operands[i + 3] = gen_lowpart (SImode, operands[i]);
      operands[i + 6] = gen_highpart (SImode, operands[i]);
    }
}
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "<MODE>")
   (set (attr "length")
	(if_then_else (match_test "!TARGET_64BIT
				  && known_eq (GET_MODE_SIZE (<MODE>mode), 8)")
		      (const_int 8) (const_int 4)))])

;; Bitwise NOT for 4-byte vector modes (always single register)
(define_insn "one_cmpl<mode>2"
  [(set (match_operand:PV32 0 "register_operand" "=r")
	(not:PV32 (match_operand:PV32 1 "register_operand" "r")))]
  "TARGET_RVP"
  "not\t%0,%1"
  [(set_attr "type" "logical")
   (set_attr "mode" "<MODE>")])

;; Bitwise NOT for 8-byte vectors.
;; RV64: single register instruction.
;; RV32: register pair; split into two 32-bit NOT operations after reload.
(define_insn_and_split "one_cmpl<mode>2"
  [(set (match_operand:PV64 0 "register_operand" "=r")
	(not:PV64 (match_operand:PV64 1 "register_operand" "r")))]
  "TARGET_RVP"
  {
    if (TARGET_64BIT)
      return "not\t%0,%1";
    return "#";
  }
  "&& !TARGET_64BIT && reload_completed"
  [(set (match_dup 2) (not:SI (match_dup 4)))
   (set (match_dup 3) (not:SI (match_dup 5)))]
  {
    operands[2] = gen_lowpart (SImode, operands[0]);
    operands[3] = gen_highpart (SImode, operands[0]);
    operands[4] = gen_lowpart (SImode, operands[1]);
    operands[5] = gen_highpart (SImode, operands[1]);
  }
  [(set_attr "type" "logical")
   (set_attr "mode" "<MODE>")])

;; ============================================================================
;; PLI/PLUI: Packed Load Immediate Instructions
;; ============================================================================
;;
;; PLI.B rd, imm8   - Broadcast 8-bit value to all bytes
;; PLI.H rd, imm10  - Broadcast 10-bit signed value to all halfwords
;; PLI.W rd, imm10  - Broadcast 10-bit signed value to all words (RV64)
;; PLUI.H rd, imm10 - Broadcast (imm10 << 6) to all halfwords
;; PLUI.W rd, imm10 - Broadcast (imm10 << 22) to all words (RV64)
;;
;; These patterns are handled by riscv_output_move via riscv_output_pli.

;; Initialize packed vectors from scalar elements, including repeated groups.
(define_expand "vec_init<mode><rvp_inner_mode>"
  [(match_operand:PVMOVE 0 "register_operand")
   (match_operand 1 "")]
  "TARGET_RVP"
{
  riscv_p_expand_vec_init (operands[0], operands[1]);
  DONE;
})

;; vec_duplicate patterns for PLI.B/PLI.H/PLI.W
(define_insn "*riscv_pli_vec"
  [(set (match_operand:PVALL 0 "register_operand" "=r")
	(vec_duplicate:PVALL
	  (match_operand:<PVALL_ELT> 1 "const_int_operand" "<dpli>")))]
  "TARGET_RVP"
  "pli.<rvp_width>\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; vec_duplicate patterns for PLUI.H/PLUI.W
(define_insn "*riscv_plui_vec"
  [(set (match_operand:PVPLUI 0 "register_operand" "=r")
	(vec_duplicate:PVPLUI
	  (match_operand:<PVALL_ELT> 1 "const_int_operand" "<dplui>")))]
  "TARGET_RVP"
  {
    operands[2] = GEN_INT (INTVAL (operands[1]) >> <plui_shift>);
    return "plui.<rvp_width>\t%0,%2";
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; PLI.DB/DH: RV32 register-pair variants for 8-byte vectors.
;; Same immediate constraints as PLI.B/H, but use register pairs.
(define_insn "*riscv_pli_d_vec"
  [(set (match_operand:PV64QH 0 "register_operand" "=R")
	(vec_duplicate:PV64QH
	  (match_operand:<PVALL_ELT> 1 "const_int_operand" "<dpli>")))]
  "!TARGET_64BIT && TARGET_RVP"
  "pli.<rvp_dwidth>\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; PLUI.DH: RV32 register-pair variant for PV4HI.
(define_insn "*riscv_plui_dh"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
	(vec_duplicate:PV4HI
	  (match_operand:HI 1 "const_int_operand" "Yph06")))]
  "!TARGET_64BIT && TARGET_RVP"
  {
    operands[2] = GEN_INT (INTVAL (operands[1]) >> 6);
    return "plui.dh\t%0,%2";
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "PV4HI")])

;; ============================================================================
;; PMV.BS/HS/WS: vec_duplicate for register (non-constant) scalars.
;; PMV.xS rd, rs == PADD.xS rd, x0, rs: broadcast low element of rs.
;; ============================================================================

;; 4-byte vectors: PMV.BS (byte) and PMV.HS (halfword), both ISAs.
(define_insn "vec_duplicate<mode>"
  [(set (match_operand:PV32 0 "register_operand" "=r")
	(vec_duplicate:PV32
	  (match_operand:<PVALL_ELT> 1 "register_operand" "r")))]
  "TARGET_RVP"
  "pmv.<rvp_width>s\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; 8-byte vectors: RV64 single register; RV32 register pair.
(define_insn "vec_duplicate<mode>"
  [(set (match_operand:PV64 0 "register_operand" "=r")
	(vec_duplicate:PV64
	  (match_operand:<PVALL_ELT> 1 "register_operand" "r")))]
  "TARGET_RVP"
  "pmv.%d0s\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; ============================================================================
;; PADD.BS/HS/WS: packed add with scalar second operand.
;; rd[i] = rs1[i] + low_element(rs2)  for all lanes i.
;; ============================================================================

;; 4-byte vectors (PV4QI/PV2HI), always single register.
(define_insn "*padd_<rvp_width>s<mode>"
  [(set (match_operand:PV32 0 "register_operand" "=r")
	(plus:PV32
	  (match_operand:PV32 1 "register_operand" "r")
	  (vec_duplicate:PV32
	    (match_operand:<PVALL_ELT> 2 "register_operand" "r"))))]
  "TARGET_RVP"
  "padd.<rvp_width>s\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; Commuted form: scalar first.
(define_insn "*padd_<rvp_width>s<mode>_rev"
  [(set (match_operand:PV32 0 "register_operand" "=r")
	(plus:PV32
	  (vec_duplicate:PV32
	    (match_operand:<PVALL_ELT> 2 "register_operand" "r"))
	  (match_operand:PV32 1 "register_operand" "r")))]
  "TARGET_RVP"
  "padd.<rvp_width>s\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; 8-byte vectors: RV64 single register (.bs/.hs/.ws), RV32 pair (.dbs/.dhs/.dws).
(define_insn "*padd_s<mode>"
  [(set (match_operand:PV64 0 "register_operand" "=r")
	(plus:PV64
	  (match_operand:PV64 1 "register_operand" "r")
	  (vec_duplicate:PV64
	    (match_operand:<PVALL_ELT> 2 "register_operand" "r"))))]
  "TARGET_RVP"
  "padd.%d0s\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; Commuted form: scalar first.
(define_insn "*padd_s<mode>_rev"
  [(set (match_operand:PV64 0 "register_operand" "=r")
	(plus:PV64
	  (vec_duplicate:PV64
	    (match_operand:<PVALL_ELT> 2 "register_operand" "r"))
	  (match_operand:PV64 1 "register_operand" "r")))]
  "TARGET_RVP"
  "padd.%d0s\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; A full-width extension of a halfword swap can retain the compact
;; rev8/shift sequence without restricting native narrow consumers.
(define_insn_and_split "*bswaphi_<su>_<mode>_rvp"
  [(set (match_operand:X 0 "register_operand" "=r")
	(any_extend:X
	  (bswap:HI (match_operand:HI 1 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_ZBB"
  "#"
  "&& reload_completed"
  [(set (match_dup 0) (bswap:X (match_dup 2)))
   (set (match_dup 0) (match_dup 3))]
{
  operands[2] = gen_lowpart (<MODE>mode, operands[1]);
  operands[3] = gen_rtx_fmt_ee (<CODE> == ZERO_EXTEND ? LSHIFTRT : ASHIFTRT,
			       <MODE>mode, operands[0],
			       GEN_INT (GET_MODE_BITSIZE (<MODE>mode) - 16));
}
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "<MODE>")
   (set_attr "length" "8")])

;; Only the low halfword is defined for a scalar HImode byte swap.  Do not
;; imply that the other bits are zero; callers may require an extension.
(define_insn "riscv_bswaphi2"
  [(set (match_operand:HI 0 "register_operand" "=r")
	(bswap:HI (match_operand:HI 1 "register_operand" "r")))]
  "TARGET_RVP"
  "ppairoe.b\t%0,%1,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "HI")])

;; Byte reversal within each halfword, without reversing halfword order.
(define_insn "riscv_bswap16_pv4qi"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
	(vec_select:PV4QI
	  (match_operand:PV4QI 1 "register_operand" "r")
	  (parallel [(const_int 1) (const_int 0)
		     (const_int 3) (const_int 2)])))]
  "TARGET_RVP"
  "ppairoe.b\t%0,%1,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "PV4QI")])

(define_insn "riscv_bswap16_pv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
	(vec_select:PV8QI
	  (match_operand:PV8QI 1 "register_operand" "r")
	  (parallel [(const_int 1) (const_int 0)
		     (const_int 3) (const_int 2)
		     (const_int 5) (const_int 4)
		     (const_int 7) (const_int 6)])))]
  "TARGET_RVP"
  "ppairoe.%d0\t%0,%1,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "PV8QI")])

;; Reverse bytes within each word.  After allocation, reuse the result
;; for the intermediate byte swap.  PV8QI pairs cannot partially overlap.
(define_insn_and_split "riscv_bswap32_pv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
	(vec_select:PV8QI
	  (match_operand:PV8QI 1 "register_operand" "r")
	  (parallel [(const_int 3) (const_int 2)
		     (const_int 1) (const_int 0)
		     (const_int 7) (const_int 6)
		     (const_int 5) (const_int 4)])))]
  "TARGET_RVP"
  "#"
  "&& reload_completed"
  [(set (match_dup 0)
	(vec_select:PV8QI (match_dup 1)
	  (parallel [(const_int 1) (const_int 0)
		     (const_int 3) (const_int 2)
		     (const_int 5) (const_int 4)
		     (const_int 7) (const_int 6)])))
   (set (match_dup 0)
	(vec_select:PV8QI (match_dup 0)
	  (parallel [(const_int 2) (const_int 3)
		     (const_int 0) (const_int 1)
		     (const_int 6) (const_int 7)
		     (const_int 4) (const_int 5)])))]
  ""
  [(set_attr "type" "simd")
   (set_attr "mode" "PV8QI")
   (set_attr "length" "8")])

(define_insn "*riscv_swap_halfwords_pv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
	(vec_select:PV8QI
	  (match_operand:PV8QI 1 "register_operand" "r")
	  (parallel [(const_int 2) (const_int 3)
		     (const_int 0) (const_int 1)
		     (const_int 6) (const_int 7)
		     (const_int 4) (const_int 5)])))]
  "TARGET_RVP"
{
  return TARGET_64BIT ? "ppairoe.h\t%0,%1,%1" : "ppairoe.dh\t%0,%1,%1";
}
  [(set_attr "type" "simd")
   (set_attr "mode" "PV8QI")])

;; Pack operations for scalar mode
;; Element reversal of PV2HI: ppairoe.h with rs1 == rs2 interleaves the odd
;; and even halfwords of the source, which for one 32-bit register is the
;; halfword reversal (__riscv_prev_i16x2/u16x2).
(define_insn "*prev_pv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
	(vec_select:PV2HI
	  (match_operand:PV2HI 1 "register_operand" "r")
	  (parallel [(const_int 1) (const_int 0)])))]
  "TARGET_RVP"
  "ppairoe.h\t%0,%1,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

(define_insn "*ppairoe_h_1"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(ior:SI (ashift:SI (match_operand:SI 1 "register_operand" "r")
                       (const_int 16))
		    (lshiftrt:SI (match_operand:SI 2 "register_operand" "r")
                         (const_int 16))))]
  "TARGET_RVP"
  "ppairoe.h\t%0, %2, %1"
  [(set_attr "type"  "arith")
   (set_attr "mode"  "SI")])

(define_insn "*ppairoe_h_2"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(ior:SI (lshiftrt:SI (match_operand:SI 1 "register_operand" "r")
                       (const_int 16))
		    (ashift:SI (match_operand:SI 2 "register_operand" "r")
                         (const_int 16))))]
  "TARGET_RVP"
  "ppairoe.h\t%0, %1, %2"
  [(set_attr "type"  "arith")
   (set_attr "mode"  "SI")])

(define_insn "*ppairoe_w_1"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ior:DI (ashift:DI (match_operand:DI 2 "register_operand" "r")
                      (const_int 32))
		    (lshiftrt:DI (match_operand:DI 1 "register_operand" "r")
                         (const_int 32))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairoe.w\t%0, %1, %2"
  [(set_attr "type"  "arith")
   (set_attr "mode"  "DI")])

(define_insn "*ppaireo_h_1"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ior:SI (and:SI (match_operand:SI 1 "register_operand" "r")
                    (const_int -65536))
            (and:SI (match_operand:SI 2 "register_operand" "r")
                    (const_int 65535))))]
  "TARGET_RVP"
  "ppaireo.h\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*ppaireo_h_2"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ior:SI (and:SI (match_operand:SI 1 "register_operand" "r")
                    (const_int -65536))
            (zero_extend:SI (match_operand:HI 2 "register_operand" "r"))))]
  "TARGET_RVP"
  "ppaireo.h\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*ppaireo_h_3"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (ior:SI (zero_extend:SI (match_operand:HI 2 "register_operand" "r"))
            (and:SI (match_operand:SI 1 "register_operand" "r")
                    (const_int -65536))))]
  "TARGET_RVP"
  "ppaireo.h\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*ppaireo_w_1"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (ior:DI (and:DI (match_operand:DI 1 "register_operand" "r")
                    (const_int -4294967296))
            (and:DI (match_operand:DI 2 "register_operand" "r")
                    (const_int 4294967295))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaireo.w\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*ppaireo_w_2"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (ior:DI (and:DI (match_operand:DI 1 "register_operand" "r")
                    (const_int -4294967296))
            (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaireo.w\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*ppaireo_w_3"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (ior:DI (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))
            (and:DI (match_operand:DI 1 "register_operand" "r")
                    (const_int -4294967296))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaireo.w\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*ppairo_h"
  [(set (match_operand:SI 0 "register_operand" "=r")
     (ior:SI (and:SI (match_operand:SI 1 "register_operand" "r")
                     (const_int -65536))
             (lshiftrt:SI (match_operand:SI 2 "register_operand" "r")
                          (const_int 16))))]
  "TARGET_RVP"
  "ppairo.h\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*ppairo_w"
  [(set (match_operand:DI 0 "register_operand" "=r")
     (ior:DI (and:DI (match_operand:DI 1 "register_operand" "r")
                     (const_int -4294967296))
             (lshiftrt:DI (match_operand:DI 2 "register_operand" "r")
                          (const_int 32))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.w\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Pack vector pattern

(define_expand "vec_setpv2hi"
  [(match_operand:PV2HI 0 "register_operand" "")
   (match_operand:HI 1 "register_operand" "")
   (match_operand:SI 2 "immediate_operand" "")]
  "TARGET_RVP"
{
  HOST_WIDE_INT pos = INTVAL (operands[2]);
  if (pos > 1)
    gcc_unreachable ();
  HOST_WIDE_INT elem = (HOST_WIDE_INT) 1 << pos;
  emit_insn (gen_vec_setv2hi_internal (operands[0], operands[1],
				       operands[0], GEN_INT (elem)));
  DONE;
})

(define_insn "vec_setv2hi_internal"
  [(set (match_operand:PV2HI 0 "register_operand" "=r, r")
    (vec_merge:PV2HI
      (vec_duplicate:PV2HI
        (match_operand:HI 1 "register_operand" "r, r"))
      (match_operand:PV2HI 2 "register_operand" "r, r")
      (match_operand:SI 3 "immediate_operand" "k01, k02")))]
  "TARGET_RVP"
{
  if ((which_alternative == 0) != TARGET_BIG_ENDIAN)
    return "ppaireo.h\t%0, %1, %2";
  return "ppaire.h\t%0, %2, %1";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_expand "vec_setpv2si"
  [(match_operand:PV2SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:SI 2 "immediate_operand" "")]
  "TARGET_RVP && TARGET_64BIT"
{
  HOST_WIDE_INT pos = INTVAL (operands[2]);
  if (pos > 1)
    gcc_unreachable ();
  HOST_WIDE_INT elem = (HOST_WIDE_INT) 1 << pos;
  emit_insn (gen_vec_setv2si_internal (operands[0], operands[1],
				       operands[0], GEN_INT (elem)));
  DONE;
})

(define_insn "vec_setv2si_internal"
  [(set (match_operand:PV2SI 0 "register_operand" "=r, r")
    (vec_merge:PV2SI
      (vec_duplicate:PV2SI
        (match_operand:SI 1 "register_operand" "r, r"))
      (match_operand:PV2SI 2 "register_operand" "r, r")
      (match_operand:SI 3 "immediate_operand" "k01, k02")))]
  "TARGET_RVP && TARGET_64BIT"
{
  if ((which_alternative == 0) != TARGET_BIG_ENDIAN)
    return "ppaireo.w\t%0, %1, %2";
  return "pack\t%0, %2, %1";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Only the low halfword is defined.  PPAIRE.B takes the low byte from each
;; source, so neither source needs extending to XLEN first.
(define_insn "riscv_p_pack_byteshi"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (ior:HI
          (zero_extend:HI (match_operand:QI 1 "register_operand" "r"))
          (ashift:HI
            (zero_extend:HI (match_operand:QI 2 "register_operand" "r"))
            (const_int 8))))]
  "TARGET_RVP"
  "ppaire.b\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "HI")])

;; Only the low word is defined; PPAIRE.H does not sign-extend bit 31.
(define_insn "riscv_p_pack_halfwordssi"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(ior:SI
	  (ashift:SI (match_operand:SI 1 "register_operand" "r")
		     (const_int 16))
	  (zero_extend:SI (match_operand:HI 2 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; Keep the promoted scalar form and expose the low-word result before
;; allocation.  Unlike PACKW, this operation needs an explicit sign
;; extension after PPAIRE.H.
(define_insn_and_split "*riscv_p_pack_halfwordsdi_sext_hi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ior:DI
	  (ashift:DI
	    (sign_extend:DI (match_operand:HI 1 "register_operand" "r"))
	    (const_int 16))
	  (zero_extend:DI (match_operand:HI 2 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_ZBKB"
  "#"
  "&& 1"
  [(set (match_dup 3)
	(ior:SI (ashift:SI (match_dup 4) (const_int 16))
		(zero_extend:SI (match_dup 2))))
   (set (match_dup 0) (sign_extend:DI (match_dup 3)))]
{
  operands[3] = gen_lowpart (SImode, operands[0]);
  operands[4] = gen_lowpart (SImode, operands[1]);
}
  [(set_attr "type" "arith")
   (set_attr "length" "8")
   (set_attr "mode" "DI")])

(define_insn_and_split "*riscv_p_pack_halfwordsdi_sext_si"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ior:DI
	  (sign_extend:DI
	    (ashift:SI (match_operand:SI 1 "register_operand" "r")
		       (const_int 16)))
	  (zero_extend:DI (match_operand:HI 2 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_ZBKB"
  "#"
  "&& 1"
  [(set (match_dup 3)
	(ior:SI (ashift:SI (match_dup 1) (const_int 16))
		(zero_extend:SI (match_dup 2))))
   (set (match_dup 0) (sign_extend:DI (match_dup 3)))]
  "operands[3] = gen_lowpart (SImode, operands[0]);"
  [(set_attr "type" "arith")
   (set_attr "length" "8")
   (set_attr "mode" "DI")])

;; Narrow a masked insertion before extending its result.  The low field
;; fits in a halfword within its low word, but may not yet have been
;; substituted by combine.  Keeping its HI view lets a later combination
;; absorb the field producer without assuming anything about the high
;; input's upper word.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(any_extend:DI
	  (match_operator:SI 3 "subreg_lowpart_operator"
	    [(ior:DI
	       (and:DI (match_operand:DI 1 "register_operand")
		       (const_int -65536))
	       (match_operand:DI 2 "register_operand"))])))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()
   && (nonzero_bits (operands[2], DImode)
       & HOST_WIDE_INT_UC (0xffff0000)) == 0"
  [(set (match_dup 4)
	(ior:SI (and:SI (match_dup 5) (const_int -65536))
		(zero_extend:SI (match_dup 6))))
   (set (match_dup 0) (any_extend:DI (match_dup 4)))]
{
  operands[4] = gen_reg_rtx (SImode);
  operands[5] = gen_lowpart (SImode, operands[1]);
  operands[6] = gen_lowpart (HImode, operands[2]);
})

;; Zero extension can instead be folded into the high field's mask.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(ior:DI
	  (and:DI (match_operand:DI 1 "register_operand")
		  (const_int 4294901760))
	  (match_operand:DI 2 "register_operand")))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()
   && (nonzero_bits (operands[2], DImode) & ~HOST_WIDE_INT_UC (65535)) == 0"
  [(set (match_dup 3)
	(ior:SI (and:SI (match_dup 4) (const_int -65536))
		(zero_extend:SI (match_dup 5))))
   (set (match_dup 0) (zero_extend:DI (match_dup 3)))]
{
  operands[3] = gen_reg_rtx (SImode);
  operands[4] = gen_lowpart (SImode, operands[1]);
  operands[5] = gen_lowpart (HImode, operands[2]);
})

;; An explicitly extended SI field has the same low-halfword bound.  Its
;; upper bits are defined by the extension, unlike a paradoxical subreg.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(ior:DI
	  (and:DI (match_operand:DI 1 "register_operand")
		  (const_int 4294901760))
	  (zero_extend:DI (match_operand:SI 2 "register_operand"))))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()
   && (nonzero_bits (operands[2], SImode) & ~HOST_WIDE_INT_UC (65535)) == 0"
  [(set (match_dup 3)
	(ior:SI (and:SI (match_dup 4) (const_int -65536))
		(zero_extend:SI (match_dup 5))))
   (set (match_dup 0) (zero_extend:DI (match_dup 3)))]
{
  operands[3] = gen_reg_rtx (SImode);
  operands[4] = gen_lowpart (SImode, operands[1]);
  operands[5] = gen_lowpart (HImode, operands[2]);
})

;; Substituting a halfword extraction into the narrowed insertion can
;; leave a redundant AND.  Its low half is all ones, while its high half
;; repeats the high field already selected by the inner AND.  Recognize
;; this as an instruction too, since a two-insn combine does not try
;; machine-description splits.
(define_insn_and_split "*riscv_p_pair_odd_halfwordssi_mask"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(and:SI
	  (ior:SI
	    (and:SI (match_operand:SI 1 "register_operand" "r")
		    (const_int -65536))
	    (lshiftrt:SI (match_operand:SI 2 "register_operand" "r")
			 (const_int 16)))
	  (ior:SI (match_dup 1) (const_int 65535))))]
  "TARGET_RVP && TARGET_64BIT"
  "#"
  "&& 1"
  [(set (match_dup 0)
	(ior:SI (and:SI (match_dup 1) (const_int -65536))
		(lshiftrt:SI (match_dup 2) (const_int 16))))]
  ""
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; A promoted word insertion can lose its explicit sign extension during
;; combine.  Only use the low-word pair when the preserved high part is
;; already sign-extended.  Record that proof before allocation, since the
;; pair instruction itself does not define a sign-extended DI result.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(ior:DI
	  (and:DI (match_operand:DI 1 "register_operand")
		  (const_int -65536))
	  (zero_extend:DI (match_operand:HI 2 "register_operand"))))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()
   && num_sign_bit_copies (operands[1], DImode) >= 33"
  [(set (match_dup 3)
	(ior:SI (and:SI (match_dup 4) (const_int -65536))
		(zero_extend:SI (match_dup 2))))
   (set (match_dup 0) (sign_extend:DI (match_dup 3)))]
{
  operands[3] = gen_reg_rtx (SImode);
  operands[4] = gen_lowpart (SImode, operands[1]);
})

(define_split
  [(set (match_operand:DI 0 "register_operand")
	(ior:DI
	  (and:DI (match_operand:DI 1 "register_operand")
		  (const_int -65536))
	  (zero_extract:DI (match_operand:DI 2 "register_operand")
			   (const_int 16) (const_int 16))))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()
   && num_sign_bit_copies (operands[1], DImode) >= 33"
  [(set (match_dup 3)
	(ior:SI (and:SI (match_dup 4) (const_int -65536))
		(lshiftrt:SI (match_dup 5) (const_int 16))))
   (set (match_dup 0) (sign_extend:DI (match_dup 3)))]
{
  operands[3] = gen_reg_rtx (SImode);
  operands[4] = gen_lowpart (SImode, operands[1]);
  operands[5] = gen_lowpart (SImode, operands[2]);
})

;; Here the shifted signed halfword makes the extension explicit, while
;; the extracted low field cannot affect the result sign bit.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(ior:DI
	  (ashift:DI
	    (sign_extend:DI (match_operand:HI 1 "register_operand"))
	    (const_int 16))
	  (zero_extract:DI (match_operand:DI 2 "register_operand")
			   (const_int 16) (const_int 16))))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()"
  [(set (match_dup 3)
	(ior:SI (ashift:SI (match_dup 4) (const_int 16))
		(lshiftrt:SI (match_dup 5) (const_int 16))))
   (set (match_dup 0) (sign_extend:DI (match_dup 3)))]
{
  operands[3] = gen_reg_rtx (SImode);
  operands[4] = gen_lowpart (SImode, operands[1]);
  operands[5] = gen_lowpart (SImode, operands[2]);
})

;; Scalar views of the two halfword pairs in a 64-bit register.  Keep the
;; masks recognizable on their own so that combine can first absorb their
;; constant loads, then combine the two fields.  The masks are
;; 0x0000ffff0000ffff and 0xffff0000ffff0000, respectively.
(define_insn "*riscv_p_mask_even_halfwordsdi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(and:DI (match_operand:DI 1 "register_operand" "r")
		(const_int 281470681808895)))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0, %1, zero"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*riscv_p_mask_odd_halfwordsdi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(and:DI (match_operand:DI 1 "register_operand" "r")
		(const_int -281470681808896)))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaireo.h\t%0, zero, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*riscv_p_shift_even_halfwordsdi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(and:DI
	  (ashift:DI (match_operand:DI 1 "register_operand" "r")
		     (const_int 16))
	  (const_int -281470681808896)))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0, zero, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*riscv_p_shift_odd_halfwordsdi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(and:DI
	  (lshiftrt:DI (match_operand:DI 1 "register_operand" "r")
		      (const_int 16))
	  (const_int 281470681808895)))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.h\t%0, %1, zero"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*riscv_p_pair_even_halfwordsdi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ior:DI
	  (and:DI
	    (ashift:DI (match_operand:DI 1 "register_operand" "r")
		       (const_int 16))
	    (const_int -281470681808896))
	  (and:DI (match_operand:DI 2 "register_operand" "r")
		  (const_int 281470681808895))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*riscv_p_pair_even_halfwordsdi_commuted"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ior:DI
	  (and:DI (match_operand:DI 1 "register_operand" "r")
		  (const_int 281470681808895))
	  (and:DI
	    (ashift:DI (match_operand:DI 2 "register_operand" "r")
		       (const_int 16))
	    (const_int -281470681808896))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*riscv_p_pair_even_odd_halfwordsdi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ior:DI
	  (and:DI (match_operand:DI 1 "register_operand" "r")
		  (const_int 281470681808895))
	  (and:DI (match_operand:DI 2 "register_operand" "r")
		  (const_int -281470681808896))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaireo.h\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*riscv_p_pair_even_odd_halfwordsdi_commuted"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ior:DI
	  (and:DI (match_operand:DI 1 "register_operand" "r")
		  (const_int -281470681808896))
	  (and:DI (match_operand:DI 2 "register_operand" "r")
		  (const_int 281470681808895))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaireo.h\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*riscv_p_pair_odd_even_halfwordsdi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ior:DI
	  (and:DI
	    (ashift:DI (match_operand:DI 1 "register_operand" "r")
		       (const_int 16))
	    (const_int -281470681808896))
	  (and:DI
	    (lshiftrt:DI (match_operand:DI 2 "register_operand" "r")
			(const_int 16))
	    (const_int 281470681808895))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairoe.h\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*riscv_p_pair_odd_even_halfwordsdi_commuted"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ior:DI
	  (and:DI
	    (lshiftrt:DI (match_operand:DI 1 "register_operand" "r")
			(const_int 16))
	    (const_int 281470681808895))
	  (and:DI
	    (ashift:DI (match_operand:DI 2 "register_operand" "r")
		       (const_int 16))
	    (const_int -281470681808896))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairoe.h\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*riscv_p_pair_odd_halfwordsdi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ior:DI
	  (and:DI
	    (lshiftrt:DI (match_operand:DI 1 "register_operand" "r")
			(const_int 16))
	    (const_int 281470681808895))
	  (and:DI (match_operand:DI 2 "register_operand" "r")
		  (const_int -281470681808896))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.h\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*riscv_p_pair_odd_halfwordsdi_commuted"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ior:DI
	  (and:DI (match_operand:DI 1 "register_operand" "r")
		  (const_int -281470681808896))
	  (and:DI
	    (lshiftrt:DI (match_operand:DI 2 "register_operand" "r")
			(const_int 16))
	    (const_int 281470681808895))))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.h\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Concatenate two halfwords into a PV2HI vector.  PPAIRE.H packs the low
;; halfword of each operand into a 32-bit word, which is what is needed for
;; both RV32 and RV64; on RV64 a plain PACK would instead concatenate the
;; full 32-bit halves and produce a wrong result.  On RV32 PPAIRE.H is an
;; alias of PACK, so this is also correct there.  VEC_CONCAT names logical
;; elements, whereas the instruction puts its first source in the low bits.
(define_insn "ppaire_concatpv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (vec_concat:PV2HI
          (match_operand:HI 1 "register_operand" "r") 
          (match_operand:HI 2 "register_operand" "r")))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppaire.h\t%0, %2, %1"
			   : "ppaire.h\t%0, %1, %2";
}
  [(set_attr "type"  "arith")
   (set_attr "mode"  "SI")])

(define_insn "pack_concatpv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (vec_concat:PV2SI
          (match_operand:SI 1 "register_operand" "r") 
          (match_operand:SI 2 "register_operand" "r")))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "pack\t%0, %2, %1"
			   : "pack\t%0, %1, %2";
}
  [(set_attr "type"  "arith")
   (set_attr "mode"  "DI")])

;; ppaireo.h pattern: take bottom of first operand and top of second operand
;; Matches vec_concat where the top element comes from a shift (extracting top half)
;; For little-endian: ppaireo.h Rd, Ra, Rb means Rd[0] = Ra[0], Rd[1] = Rb[1]
(define_insn "ppaireo_concatpv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (vec_concat:PV2HI
          (match_operand:HI 1 "register_operand" "r") 
          (subreg:HI (lshiftrt:SI
                       (match_operand:SI 2 "register_operand" "r") 
                       (const_int 16)) 0)))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
  "ppaireo.h\t%0, %1, %2"
  [(set_attr "type"  "arith")
   (set_attr "mode"  "SI")])

;; ppaireo.w pattern: take bottom of first operand and top of second operand
;; Matches vec_concat where the top element comes from a shift (extracting top word)
;; For little-endian: ppaireo.w Rd, Ra, Rb means Rd[0] = Ra[0], Rd[1] = Rb[1]
(define_insn "*ppaireo_concatpv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (vec_concat:PV2SI
          (match_operand:SI 1 "register_operand" "r") 
          (subreg:SI (lshiftrt:DI
                       (match_operand:DI 2 "register_operand" "r") 
                       (const_int 32)) 0)))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "ppaireo.w\t%0, %1, %2"
  [(set_attr "type"  "arith")
   (set_attr "mode"  "DI")])

;; ppairoe.h pattern: take top of first operand and bottom of second operand
;; Matches vec_concat where the top element comes from a shift (extracting top half)
;; For little-endian: ppairoe.h Rd, Ra, Rb means Rd[0] = Ra[1], Rd[1] = Rb[0]
(define_insn "*ppairoe_concatpv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (vec_concat:PV2HI
          (subreg:HI (lshiftrt:SI
                       (match_operand:SI 1 "register_operand" "r")
                       (const_int 16)) 0)
          (match_operand:HI 2 "register_operand" "r")))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
  "ppairoe.h\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; ppairoe.w pattern: take top of first operand and bottom of second operand
;; Matches vec_concat where the top element comes from a shift (extracting top word)
;; For little-endian: ppairoe.w Rd, Ra, Rb means Rd[0] = Ra[1], Rd[1] = Rb[0]
(define_insn "*ppairoe_concatpv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (vec_concat:PV2SI
          (subreg:SI (lshiftrt:DI
                       (match_operand:DI 1 "register_operand" "r")
                       (const_int 32)) 0)
          (match_operand:SI 2 "register_operand" "r")))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "ppairoe.w\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; ppairo.h pattern: take top of first operand and top of second operand
;; Matches vec_concat where the top element comes from a shift (extracting top half)
;; For little-endian: ppairo.h Rd, Ra, Rb means Rd[0] = Ra[1], Rd[1] = Rb[1]
(define_insn "*ppairo_concatpv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (vec_concat:PV2HI
          (subreg:HI (lshiftrt:SI
                       (match_operand:SI 1 "register_operand" "r")
                       (const_int 16)) 0)
          (subreg:HI (lshiftrt:SI
                       (match_operand:SI 2 "register_operand" "r")
                       (const_int 16)) 0)))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
  "ppairo.h\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; ppairo.w pattern: take top of first operand and top of second operand
;; Matches vec_concat where the top element comes from a shift (extracting top word)
;; For little-endian: ppairo.w Rd, Ra, Rb means Rd[0] = Ra[1], Rd[1] = Rb[1]
(define_insn "*ppairo_concatpv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (vec_concat:PV2SI
          (subreg:SI (lshiftrt:DI
                       (match_operand:DI 1 "register_operand" "r")
                       (const_int 32)) 0)
          (subreg:SI (lshiftrt:DI
                       (match_operand:DI 2 "register_operand" "r")
                       (const_int 32)) 0)))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "ppairo.w\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; ============================================================================
;; Pair instructions (PV2HI mode) (PV2SI mode)
;; ============================================================================
(define_insn "*ppaireh_mergepv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (vec_merge:PV2HI
          (vec_select:PV2HI (match_operand:PV2HI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)]))
          (vec_select:PV2HI (match_operand:PV2HI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)]))
          (const_int 2)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppairo.h\t%0, %2,%1"
			   : "ppaire.h\t%0, %1, %2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*ppaireoh_mergepv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (vec_merge:PV2HI
          (vec_select:PV2HI (match_operand:PV2HI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)]))
          (vec_select:PV2HI (match_operand:PV2HI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)]))
          (const_int 2)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppaireo.h\t%0, %2,%1"
			   : "ppaireo.h\t%0, %1, %2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*ppairoeh_mergepv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (vec_merge:PV2HI
          (vec_select:PV2HI (match_operand:PV2HI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)]))
          (vec_select:PV2HI (match_operand:PV2HI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)]))
          (const_int 2)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppairoe.h\t%0, %2,%1"
			   : "ppairoe.h\t%0, %1, %2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*ppairoh_mergepv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (vec_merge:PV2HI
          (vec_select:PV2HI (match_operand:PV2HI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)]))
          (vec_select:PV2HI (match_operand:PV2HI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)]))
          (const_int 2)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppaire.h\t%0, %2,%1"
			   : "ppairo.h\t%0, %1, %2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*ppairew_mergepv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (vec_merge:PV2SI
          (vec_select:PV2SI (match_operand:PV2SI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)]))
          (vec_select:PV2SI (match_operand:PV2SI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)]))
          (const_int 2)))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "ppairo.w\t%0,%2,%1"
			   : "pack\t%0, %1, %2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*ppaireow_mergepv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (vec_merge:PV2SI
          (vec_select:PV2SI (match_operand:PV2SI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)]))
          (vec_select:PV2SI (match_operand:PV2SI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)]))
          (const_int 2)))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "ppaireo.w\t%0, %2,%1"
			   : "ppaireo.w\t%0, %1, %2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*ppairoew_mergepv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (vec_merge:PV2SI
          (vec_select:PV2SI (match_operand:PV2SI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)]))
          (vec_select:PV2SI (match_operand:PV2SI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)]))
          (const_int 2)))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "ppairoe.w\t%0, %2,%1"
			   : "ppairoe.w\t%0, %1, %2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*ppairow_mergepv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (vec_merge:PV2SI
          (vec_select:PV2SI (match_operand:PV2SI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)]))
          (vec_select:PV2SI (match_operand:PV2SI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)]))
          (const_int 2)))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "ppaire.w\t%0, %2,%1"
			   : "ppairo.w\t%0, %1, %2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; ============================================================================
;; Pair instructions (PV4QI mode) (PV4HI mode)
;; ============================================================================

;; PPAIRE.B using vec_merge + vec_select
;; Result: rd[0]=op1[0], rd[1]=op2[0], rd[2]=op1[2], rd[3]=op2[2]
;; vec_select produces {op[0], op[0], op[2], op[2]} for each operand
;; vec_merge with mask 0b1010 selects alternating elements
(define_insn "*ppaireb_mergepv4qi"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (vec_merge:PV4QI
          (vec_select:PV4QI (match_operand:PV4QI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)]))
          (vec_select:PV4QI (match_operand:PV4QI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)]))
          (const_int 10)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppairo.b\t%0,%2,%1"
			   : "ppaire.b\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; PPAIRE.H using vec_merge + vec_select
;; Result: rd[0]=op1[0], rd[1]=op2[0], rd[2]=op1[2], rd[3]=op2[2]
;; vec_select produces {op[0], op[0], op[2], op[2]} for each operand
;; vec_merge with mask 0b1010 selects alternating elements
(define_insn "*ppaireh_mergepv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (vec_merge:PV4HI
          (vec_select:PV4HI (match_operand:PV4HI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)]))
          (vec_select:PV4HI (match_operand:PV4HI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)]))
          (const_int 10)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppairo.%d0\t%0,%2,%1"
			   : "ppaire.%d0\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "PV4HI")])

;; PPAIREO.B using vec_merge + vec_select
;; Result: rd[0]=op1[0], rd[1]=op2[1], rd[2]=op1[2], rd[3]=op2[3]
;; vec_select on op1: {0, 0, 2, 2}, on op2: {1, 1, 3, 3}
;; vec_merge with mask 0b1010 selects alternating elements
(define_insn "*ppaireob_mergepv4qi"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (vec_merge:PV4QI
          (vec_select:PV4QI (match_operand:PV4QI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)]))
          (vec_select:PV4QI (match_operand:PV4QI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)]))
          (const_int 10)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppaireo.b\t%0,%2,%1"
			   : "ppaireo.b\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; PPAIREO.H using vec_merge + vec_select
;; Result: rd[0]=op1[0], rd[1]=op2[1], rd[2]=op1[2], rd[3]=op2[3]
;; vec_select on op1: {0, 0, 2, 2}, on op2: {1, 1, 3, 3}
;; vec_merge with mask 0b1010 selects alternating elements
(define_insn "*ppaireoh_mergepv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (vec_merge:PV4HI
          (vec_select:PV4HI (match_operand:PV4HI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)]))
          (vec_select:PV4HI (match_operand:PV4HI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)]))
          (const_int 10)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppaireo.%d0\t%0,%2,%1"
			   : "ppaireo.%d0\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "PV4HI")])

;; PPAIROE.B using vec_merge + vec_select
;; Result: rd[0]=op1[1], rd[1]=op2[0], rd[2]=op1[3], rd[3]=op2[2]
;; vec_select on op1: {1, 1, 3, 3}, on op2: {0, 0, 2, 2}
;; vec_merge with mask 0b1010 selects alternating elements
(define_insn "*ppairoeb_mergepv4qi"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (vec_merge:PV4QI
          (vec_select:PV4QI (match_operand:PV4QI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)]))
          (vec_select:PV4QI (match_operand:PV4QI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)]))
          (const_int 10)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppairoe.b\t%0,%2,%1"
			   : "ppairoe.b\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; PPAIROE.H using vec_merge + vec_select
;; Result: rd[0]=op1[1], rd[1]=op2[0], rd[2]=op1[3], rd[3]=op2[2]
;; vec_select on op1: {1, 1, 3, 3}, on op2: {0, 0, 2, 2}
;; vec_merge with mask 0b1010 selects alternating elements
(define_insn "*ppairoeh_mergepv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (vec_merge:PV4HI
          (vec_select:PV4HI (match_operand:PV4HI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)]))
          (vec_select:PV4HI (match_operand:PV4HI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)]))
          (const_int 10)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppairoe.%d0\t%0,%2,%1"
			   : "ppairoe.%d0\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "PV4HI")])

;; PPAIRO.B using vec_merge + vec_select
;; Result: rd[0]=op1[1], rd[1]=op2[1], rd[2]=op1[3], rd[3]=op2[3]
;; vec_select on op1: {1, 1, 3, 3}, on op2: {1, 1, 3, 3}
;; vec_merge with mask 0b1010 selects alternating elements
(define_insn "ppairob_mergepv4qi"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (vec_merge:PV4QI
          (vec_select:PV4QI (match_operand:PV4QI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)]))
          (vec_select:PV4QI (match_operand:PV4QI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)]))
          (const_int 10)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppaire.b\t%0,%2,%1"
			   : "ppairo.b\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; PPAIRO.H using vec_merge + vec_select
;; Result: rd[0]=op1[1], rd[1]=op2[1], rd[2]=op1[3], rd[3]=op2[3]
;; vec_select on op1: {1, 1, 3, 3}, on op2: {1, 1, 3, 3}
;; vec_merge with mask 0b1010 selects alternating elements
(define_insn "*ppairoh_mergepv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (vec_merge:PV4HI
          (vec_select:PV4HI (match_operand:PV4HI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)]))
          (vec_select:PV4HI (match_operand:PV4HI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)]))
          (const_int 10)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppaire.%d0\t%0,%2,%1"
			   : "ppairo.%d0\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "PV4HI")])

;; ============================================================================
;; Pair instructions (PV8QI mode)
;; ============================================================================
;; PPAIRE.B: pairs low bytes from each 16-bit halfword
;; Result = {s2[55:48]@s1[55:48], s2[39:32]@s1[39:32], s2[23:16]@s1[23:16], s2[7:0]@s1[7:0]}
;; For V8QI: combines bytes from two operands element-wise
;; Pattern: rd[0]=op0[0], rd[1]=op1[0], rd[2]=op0[2], rd[3]=op1[2], rd[4]=op0[4], rd[5]=op1[4],
;;          rd[6]=op0[6], rd[7]=op1[6]
;; VEC_PERM indices: {0, 8, 2, 10, 4, 12, 6, 14}
(define_insn "*ppaireb_mergepv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (vec_merge:PV8QI
          (vec_select:PV8QI (match_operand:PV8QI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)
                                       (const_int 4) (const_int 4)
                                       (const_int 6) (const_int 6)]))
          (vec_select:PV8QI (match_operand:PV8QI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)
                                       (const_int 4) (const_int 4)
                                       (const_int 6) (const_int 6)]))
          (const_int 170)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppairo.%d0\t%0,%2,%1"
			   : "ppaire.%d0\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "PV8QI")])

;; PPAIREO.B: pairs low bytes from op0 and high bytes from op1
;; Result = {s2[63:56]@s1[55:48], s2[47:40]@s1[39:32], s2[31:24]@s1[23:16], s2[15:8]@s1[7:0]} 
;; For V8QI: combines bytes from two operands element-wise
;; Pattern: rd[0]=op0[0], rd[1]=op1[1], rd[2]=op0[2], rd[3]=op1[3], rd[4]=op0[4], rd[5]=op1[5],
;;          rd[6]=op0[6], rd[7]=op1[7]
;; VEC_PERM indices: {0, 9, 2, 11, 4, 13, 6, 15}
(define_insn "*ppaireob_mergepv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (vec_merge:PV8QI
          (vec_select:PV8QI (match_operand:PV8QI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)
                                       (const_int 5) (const_int 5)
                                       (const_int 7) (const_int 7)]))
          (vec_select:PV8QI (match_operand:PV8QI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)
                                       (const_int 4) (const_int 4)
                                       (const_int 6) (const_int 6)]))
          (const_int 170)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppaireo.%d0\t%0,%2,%1"
			   : "ppaireo.%d0\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "PV8QI")])

;; PPAIROE.B: pairs high bytes from op0 and low bytes from op1
;; Result = {s2[55:48]@s1[63:56], s2[39:32]@s1[47:40], s2[23:16]@s1[31:24], s2[7:0]@s1[15:8]}
;; For V8QI: combines bytes from two operands element-wise
;; Pattern: rd[0]=op0[1], rd[1]=op1[0], rd[2]=op0[3], rd[3]=op1[2], rd[4]=op0[5], rd[5]=op1[4],
;;          rd[6]=op0[7], rd[7]=op1[6]
;; VEC_PERM indices: {1, 8, 3, 10, 5, 12, 7, 14}
(define_insn "*ppairoeb_mergepv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (vec_merge:PV8QI
          (vec_select:PV8QI (match_operand:PV8QI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 2) (const_int 2)
                                       (const_int 4) (const_int 4)
                                       (const_int 6) (const_int 6)]))
          (vec_select:PV8QI (match_operand:PV8QI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)
                                       (const_int 5) (const_int 5)
                                       (const_int 7) (const_int 7)]))
          (const_int 170)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppairoe.%d0\t%0,%2,%1"
			   : "ppairoe.%d0\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "PV8QI")])

;; PPAIRO.B: pairs high bytes from op0 and high bytes from op1
;; Result = {s2[63:56]@s1[63:56], s2[47:40]@s1[47:40], s2[31:24]@s1[31:24], s2[15:8]@s1[15:8]}
;; For V8QI: combines bytes from two operands element-wise
;; Pattern: rd[0]=op0[1], rd[1]=op1[1], rd[2]=op0[3], rd[3]=op1[3], rd[4]=op0[5], rd[5]=op1[5],
;;          rd[6]=op0[7], rd[7]=op1[7]
;; VEC_PERM indices: {1, 9, 3, 11, 5, 13, 7, 15}
(define_insn "*ppairob_mergepv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (vec_merge:PV8QI
          (vec_select:PV8QI (match_operand:PV8QI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)
                                       (const_int 5) (const_int 5)
                                       (const_int 7) (const_int 7)]))
          (vec_select:PV8QI (match_operand:PV8QI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 1)
                                       (const_int 3) (const_int 3)
                                       (const_int 5) (const_int 5)
                                       (const_int 7) (const_int 7)]))
          (const_int 170)))]
  "TARGET_RVP"
{
  return TARGET_BIG_ENDIAN ? "ppaire.%d0\t%0,%2,%1"
			   : "ppairo.%d0\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "PV8QI")])

;; =========================================================================
;; zip8p/zip8hp
;; =========================================================================
(define_insn "*zip_mergepv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (vec_merge:PV8QI
          (vec_select:PV8QI (match_operand:PV8QI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 1) (const_int 1)
                                       (const_int 2) (const_int 2)
                                       (const_int 3) (const_int 3)]))
          (vec_select:PV8QI (match_operand:PV8QI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 1) (const_int 1)
                                       (const_int 2) (const_int 2)
                                       (const_int 3) (const_int 3)]))
          (const_int 170)))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "zip8hp\t%0,%2,%1" : "zip8p\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*ziph_mergepv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (vec_merge:PV8QI
          (vec_select:PV8QI (match_operand:PV8QI 2 "register_operand" "r")
                            (parallel [(const_int 4) (const_int 4)
                                       (const_int 5) (const_int 5)
                                       (const_int 6) (const_int 6)
                                       (const_int 7) (const_int 7)]))
          (vec_select:PV8QI (match_operand:PV8QI 1 "register_operand" "r")
                            (parallel [(const_int 4) (const_int 4)
                                       (const_int 5) (const_int 5)
                                       (const_int 6) (const_int 6)
                                       (const_int 7) (const_int 7)]))
          (const_int 170)))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "zip8p\t%0,%2,%1" : "zip8hp\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Byte-granularity zip of two 32-bit vectors into a 64-bit one.  zip8p and
;; wzip8p are the same operation -- both read only the low 32 bits of each
;; source -- and differ only in whether the 64-bit result is one register or an
;; even-odd pair, which the PV8QI mode already expresses.  The PV4QI zip
;; permutes take the low or high half of this result.
(define_expand "riscv_zip8p_pv4qi"
  [(set (match_operand:PV8QI 0 "register_operand")
	(vec_select:PV8QI
	  (vec_concat:PV8QI (match_operand:PV4QI 1 "register_operand")
			    (match_operand:PV4QI 2 "register_operand"))
	  (parallel [(const_int 0) (const_int 4)
		     (const_int 1) (const_int 5)
		     (const_int 2) (const_int 6)
		     (const_int 3) (const_int 7)])))]
  "TARGET_RVP"
{
  if (!TARGET_64BIT && TARGET_BIG_ENDIAN)
    {
      /* WZIP writes its low word to the even register.  Adapt that
	 physical pair to GCC's big-endian vector word order.  */
      rtx raw = gen_reg_rtx (PV8QImode);
      rtx result = gen_reg_rtx (PV8QImode);
      emit_insn (gen_riscv_pzip_i8x8_rv32 (raw, operands[2], operands[1]));
      emit_move_insn (gen_highpart (PV4QImode, result),
		     gen_lowpart (PV4QImode, raw));
      emit_move_insn (gen_lowpart (PV4QImode, result),
		     gen_highpart (PV4QImode, raw));
      emit_move_insn (operands[0], result);
      DONE;
    }
})

(define_insn "*riscv_zip8p_pv4qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
	(vec_select:PV8QI
	  (vec_concat:PV8QI (match_operand:PV4QI 1 "register_operand" "r")
			    (match_operand:PV4QI 2 "register_operand" "r"))
	  (parallel [(const_int 0) (const_int 4)
		     (const_int 1) (const_int 5)
		     (const_int 2) (const_int 6)
		     (const_int 3) (const_int 7)])))]
  "TARGET_RVP && (TARGET_64BIT || !TARGET_BIG_ENDIAN)"
  {
    if (TARGET_64BIT)
      return TARGET_BIG_ENDIAN ? "zip8p\t%0,%2,%1" : "zip8p\t%0,%1,%2";
    return "wzip8p\t%0, %1, %2";
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; =========================================================================
;; zip16p/zip16hp
;; =========================================================================
(define_insn "*zip_mergepv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (vec_merge:PV4HI
          (vec_select:PV4HI (match_operand:PV4HI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 1) (const_int 1)]))
          (vec_select:PV4HI (match_operand:PV4HI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 0)
                                       (const_int 1) (const_int 1)]))
          (const_int 10)))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "zip16hp\t%0,%2,%1" : "zip16p\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*ziph_mergepv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (vec_merge:PV4HI
          (vec_select:PV4HI (match_operand:PV4HI 2 "register_operand" "r")
                            (parallel [(const_int 2) (const_int 2)
                                       (const_int 3) (const_int 3)]))
          (vec_select:PV4HI (match_operand:PV4HI 1 "register_operand" "r")
                            (parallel [(const_int 2) (const_int 2)
                                       (const_int 3) (const_int 3)]))
          (const_int 10)))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "zip16p\t%0,%2,%1" : "zip16hp\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; =========================================================================
;; unzip8p/unzip8hp
;; =========================================================================
(define_insn "*unzip_concatpv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (vec_concat:PV8QI
          (vec_select:PV4QI (match_operand:PV8QI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 2)
                                       (const_int 4) (const_int 6)]))
          (vec_select:PV4QI (match_operand:PV8QI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 2)
                                       (const_int 4) (const_int 6)]))))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "unzip8hp\t%0,%2,%1" : "unzip8p\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*unziph_concatpv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (vec_concat:PV8QI
          (vec_select:PV4QI (match_operand:PV8QI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 3)
                                       (const_int 5) (const_int 7)]))
          (vec_select:PV4QI (match_operand:PV8QI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 3)
                                       (const_int 5) (const_int 7)]))))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "unzip8p\t%0,%2,%1" : "unzip8hp\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; =========================================================================
;; unzip16p/unzip16hp
;; =========================================================================
(define_insn "*unzip_concatpv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (vec_concat:PV4HI
          (vec_select:PV2HI (match_operand:PV4HI 1 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 2)]))
          (vec_select:PV2HI (match_operand:PV4HI 2 "register_operand" "r")
                            (parallel [(const_int 0) (const_int 2)]))))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "unzip16hp\t%0,%2,%1" : "unzip16p\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*unziph_concatpv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (vec_concat:PV4HI
          (vec_select:PV2HI (match_operand:PV4HI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 3)]))
          (vec_select:PV2HI (match_operand:PV4HI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 3)]))))]
  "TARGET_RVP && TARGET_64BIT"
{
  return TARGET_BIG_ENDIAN ? "unzip16p\t%0,%2,%1" : "unzip16hp\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; =========================================================================
;; rev16 
;; =========================================================================
(define_insn "*rev16_pv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (vec_select: PV4HI (match_operand:PV4HI 1 "register_operand" "r")
                           (parallel [(const_int 3) (const_int 2)
                                      (const_int 1) (const_int 0)])))]
  "TARGET_RVP && TARGET_64BIT"
  "rev16\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*rev16_pv8qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (vec_select: PV8QI (match_operand:PV8QI 1 "register_operand" "r")
                           (parallel [(const_int 6) (const_int 7)
                                      (const_int 4) (const_int 5)
                                      (const_int 2) (const_int 3)
                                      (const_int 0) (const_int 1)])))]
  "TARGET_RVP && TARGET_64BIT"
  "rev16\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; PV4QI {2,3,0,1} swaps the two halfwords of a 32-bit value.  rev16 is not
;; usable here: it is RV64-only and reverses the halfwords of the whole 64-bit
;; register, which leaves the result in the upper word.  ppairoe.h works per
;; 32-bit word, so with both sources equal it swaps the halfwords in place on
;; either XLEN.
(define_insn "*swap16_pv4qi"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (vec_select: PV4QI (match_operand:PV4QI 1 "register_operand" "r")
                           (parallel [(const_int 2) (const_int 3)
                                      (const_int 0) (const_int 1)])))]
  "TARGET_RVP"
  "ppairoe.h\t%0, %1, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; PV4HI {2,3,0,1} swaps the two words of a 64-bit value.  On RV32 PV4HI is a
;; register pair and riscv_emit_rev_4_elem swaps the halves directly, so this
;; only has to cover RV64.
(define_insn "*swap32_pv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (vec_select: PV4HI (match_operand:PV4HI 1 "register_operand" "r")
                           (parallel [(const_int 2) (const_int 3)
                                      (const_int 0) (const_int 1)])))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairoe.w\t%0, %1, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; =========================================================================
;; Sign/Zero Extension for RV32 with RVP
;; =========================================================================
;; On RV32 with RVP, we want to keep sign_extend and zero_extend as single
;; RTX operations so they can be matched by widening instructions like WADD/WADDU.
;; Without these patterns, GCC would expand them into subreg operations.

;; Sign extend SI to DI on RV32
;; This pattern is matched by the extendsidi2 expander in riscv.md
(define_insn "*extendsidi2_rvp"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (sign_extend:DI (match_operand:SI 1 "register_operand" "r")))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "wadd\t%0, %1, zero"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Zero extend SI to DI on RV32
;; This pattern is matched by the zero_extendsidi2 expander in riscv.md
(define_insn "*zero_extendsidi2_rvp"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (zero_extend:DI (match_operand:SI 1 "register_operand" "r")))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "waddu\t%0, %1, zero"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; =========================================================================
;; Widening Add Instructions (WADD/WADDU)
;; =========================================================================
;; WADD: Widening signed add - takes two 32-bit operands, produces 64-bit result
;; WADDU: Widening unsigned add - takes two 32-bit unsigned operands, produces 64-bit result
;;
;; Operation: rd_p = sign_extend(rs1) + sign_extend(rs2)
;; Result stored in register pair: X[2*rd_p] = result[31:0], X[2*rd_p+1] = result[63:32]
;; Only available on RV32 (on RV64, use regular 64-bit add)

;; Signed widening add (WADD)
;; This pattern matches: (long long)a + (long long)b
(define_insn "*waddsi3"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "wadd\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Signed widening sub (WSUB)
;; This pattern matches: (long long)a - (long long)b
(define_insn "*wsubsi3"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (minus:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                  (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "wsub\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Unsigned widening add (WADDU)
;; This pattern matches: (unsigned long long)a + (unsigned long long)b
(define_insn "*waddusi3"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "waddu\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Unsigned widening sub (WSUBU)
;; This pattern matches: (unsigned long long)a - (unsigned long long)b
(define_insn "*wsubusi3"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (minus:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                  (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "wsubu\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Widening accumulate (WADDA/WADDAU)
;; rd = acc + sign_extend(rs1) + sign_extend(rs2)
;;   - rd is a DI register pair (R constraint)
;;   - rs1, rs2 are 32-bit registers sign-extended to DI
;;   - "acc" is a DI accumulator tied to rd by the "0" constraint
(define_insn "*wadda<su>si3"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI (plus:DI (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
                          (any_extend:DI (match_operand:SI 2 "reg_or_0_operand" "rJ")))
                       (match_operand:DI 3 "register_operand" "0")))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "wadda<u>\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Rtl pattern for wadda(u) when the operand has x0 register.
(define_insn "*<su>extend_add"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (match_operand:DI 2 "register_operand" "0")))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "wadda<u>\t%0, %1, zero"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Widening subtract accumulate (WSUBA/WSUBAU)
;; rd = acc + <su>_extend(rs1) - <su>_extend(rs2)
;;   - rd is a DI register pair (R constraint)
;;   - rs1, rs2 are 32-bit registers sign-extended to DI accroding
;;     to <su> (sign-extended for WSUBA, zero-extended for WSUBAU)
;;   - "acc" is a DI accumulator tied to rd by the "0" constraint
(define_insn "*wsuba<su>si3"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI (minus:DI (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
                          (any_extend:DI (match_operand:SI 2 "register_operand" "r")))
                       (match_operand:DI 3 "register_operand" "0")))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "wsuba<u>\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; DI-mode addition for RV32 with RVP
;; Uses ADDD instruction; operands must be register pairs (R constraint)
(define_insn "*adddi3_rvp32"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI (match_operand:DI 1 "register_operand" "R")
                 (match_operand:DI 2 "register_operand" "R")))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "addd\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; DI-mode subtraction for RV32 with RVP
;; Uses SUBD instruction; op2 must be a register pair (R), op1 may also be the
;; zero literal (reg_or_0_operand + j constraint) so that the canonical
;; (minus:DI (const_int 0) reg) negation form emits "subd rd, x0, rs2" (= negd)
;; instead of failing recog at vregs.
(define_insn "*subdi3_rvp32"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (minus:DI (match_operand:DI 1 "reg_or_0_operand" "jR")
                  (match_operand:DI 2 "register_operand" "R")))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "subd\t%0, %z1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*negdi2_rvp32_neg"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (neg:DI (match_operand:DI 1 "register_operand" "R")))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "negd\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; MUL.H00
(define_insn "<u>mulhisi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (mult:SI (any_extend:SI (match_operand:HI 1 "register_operand" "r"))
                 (any_extend:SI (match_operand:HI 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_64BIT"
  "mul<u>.h00\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; MUL.W00
(define_insn "*rvp_mul<u>_w_00"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (mult:DI (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (any_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT"
  "mul<u>.w00\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; MULSU.H00
(define_insn "*rvp_mulsu_h00"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (mult:SI (zero_extend:SI (match_operand:HI 1 "register_operand" "r"))
                 (sign_extend:SI (match_operand:HI 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulsu.h00\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; MULSU.W00
(define_insn "*rvp_mulsu_w00"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT"
  "mulsu.w00\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; widen-multiply for RV32 with RVP
(define_insn "*smulsidi3_rvp"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "wmul\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*umulsidi3_rvp"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "wmulu\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*sumulsidi3_rvp"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP && !TARGET_BIG_ENDIAN"
  "wmulsu\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; -------------------------------------------------------------------------
;; Word products take bits 63:32, optionally after adding exactly 2^31.
;; These are not scaled MULHRS optabs or saturating Q-format products.

;; An unrounded full-register product can use packed word multiplication
;; only when both operands are extended words.  Preserve the requested
;; signed or unsigned interpretation of the extracted high word.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(any_shiftrt:DI
	  (mult:DI (match_operand:DI 1 "rvp_word_product_operand")
		   (match_operand:DI 2 "rvp_word_product_operand"))
	  (const_int 32)))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && riscv_p_mulhi_p (operands[1], operands[2], <CODE> == LSHIFTRT)"
  [(const_int 0)]
{
  riscv_p_expand_mulhi (operands[0], operands[1], operands[2],
			<CODE> == LSHIFTRT);
  DONE;
})

(define_split
  [(set (match_operand:DI 0 "register_operand")
	(zero_extract:DI
	  (mult:DI (match_operand:DI 1 "rvp_word_product_operand")
		   (match_operand:DI 2 "rvp_word_product_operand"))
	  (const_int 32) (const_int 32)))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && riscv_p_mulhi_p (operands[1], operands[2], true)"
  [(const_int 0)]
{
  riscv_p_expand_mulhi (operands[0], operands[1], operands[2], true);
  DONE;
})

(define_split
  [(set (match_operand:SI 0 "nonimmediate_operand")
	(subreg:SI
	  (any_shiftrt:DI
	    (mult:DI (match_operand:DI 1 "rvp_word_product_operand")
		     (match_operand:DI 2 "rvp_word_product_operand"))
	    (const_int 32)) 0))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && riscv_p_round_mulhi_p (operands[1], operands[2])"
  [(const_int 0)]
{
  riscv_p_expand_mulhi (operands[0], operands[1], operands[2], true);
  DONE;
})

(define_insn "*rvp_round_mulh<u>_si"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(subreg:SI
	  (plus:DI
	    (mult:DI
	      (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
	      (any_extend:DI (match_operand:SI 2 "register_operand" "r")))
	    (const_int 2147483648)) 4))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "mulhr<u>\t%0, %1, %2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "*rvp_round_mulh<su>mixed_si"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(subreg:SI
	  (plus:DI
	    (mult:DI
	      (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
	      (<rvp_other_extend>:DI
		(match_operand:SI 2 "register_operand" "r")))
	    (const_int 2147483648)) 4))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "mulhrsu\t%0, <rvp_mixed_operands>"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

;; Combine can remove the explicit extensions of known word-valued DI
;; registers.  Prove their range when splitting and freeze that choice in
;; the packed operation.  Do not carry range-dependent recognition to IRA.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(any_shiftrt:DI
	  (plus:DI (mult:DI (match_operand:DI 1 "register_operand")
			   (match_operand:DI 2 "register_operand"))
		   (const_int 2147483648))
	  (const_int 32)))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && riscv_p_round_mulhi_p (operands[1], operands[2])"
  [(const_int 0)]
{
  riscv_p_expand_round_mulhi (operands[0], operands[1], operands[2],
			    <CODE> == LSHIFTRT);
  DONE;
})

;; Loop results commonly go directly to memory.  Keep the arithmetic and
;; the store as separate instructions instead of requiring a register
;; destination before combine can recognize the rounded product.
(define_insn_and_split "*rvp_round_mulh<u>_store"
  [(set (match_operand:SI 0 "memory_operand" "=m")
	(subreg:SI
	  (plus:DI
	    (mult:DI
	      (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
	      (any_extend:DI (match_operand:SI 2 "register_operand" "r")))
	    (const_int 2147483648)) 4))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(set (match_dup 3)
	(subreg:SI
	  (plus:DI
	    (mult:DI (any_extend:DI (match_dup 1))
		     (any_extend:DI (match_dup 2)))
	    (const_int 2147483648)) 4))
   (set (match_dup 0) (match_dup 3))]
{
  operands[3] = gen_reg_rtx (SImode);
}
  [(set_attr "type" "store")
   (set_attr "mode" "SI")
   (set_attr "length" "8")])

(define_insn_and_split "*rvp_round_mulh<su>mixed_store"
  [(set (match_operand:SI 0 "memory_operand" "=m")
	(subreg:SI
	  (plus:DI
	    (mult:DI
	      (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
	      (<rvp_other_extend>:DI
		(match_operand:SI 2 "register_operand" "r")))
	    (const_int 2147483648)) 4))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(set (match_dup 3)
	(subreg:SI
	  (plus:DI
	    (mult:DI (any_extend:DI (match_dup 1))
		     (<rvp_other_extend>:DI (match_dup 2)))
	    (const_int 2147483648)) 4))
   (set (match_dup 0) (match_dup 3))]
{
  operands[3] = gen_reg_rtx (SImode);
}
  [(set_attr "type" "store")
   (set_attr "mode" "SI")
   (set_attr "length" "8")])

;; Unsigned ABI inputs can retain their explicit word extensions instead
;; of becoming known word-valued DI registers.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(any_shiftrt:DI
	  (plus:DI
	    (mult:DI
	      (any_extend:DI (match_operand:SI 1 "register_operand"))
	      (any_extend:DI (match_operand:SI 2 "register_operand")))
	    (const_int 2147483648))
	  (const_int 32)))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()"
  [(const_int 0)]
{
  riscv_p_expand_round_mulhi (operands[0], operands[1], operands[2],
			    <any_shiftrt:CODE> == LSHIFTRT,
			    <any_extend:CODE> == ZERO_EXTEND ? 1 : 0);
  DONE;
})

(define_split
  [(set (match_operand:SI 0 "memory_operand")
	(match_operator:SI 3 "subreg_lowpart_operator"
	  [(any_shiftrt:DI
	    (plus:DI (mult:DI (match_operand:DI 1 "register_operand")
			     (match_operand:DI 2 "register_operand"))
		     (const_int 2147483648))
	    (const_int 32))]))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && riscv_p_round_mulhi_p (operands[1], operands[2])"
  [(const_int 0)]
{
  riscv_p_expand_round_mulhi (operands[0], operands[1], operands[2], true);
  DONE;
})

;; Multiply-high accumulation wraps in the destination word.  It must not
;; be confused with Q-format saturation or a full-width accumulator.
;; Identify the complete fused operation for instruction costing without
;; changing its scheduling type or charging for the implicit rounding bias.
(define_attr "rvp_mulhi_acc" "no,yes,word" (const_string "no"))

(define_insn "*rvp_mulh<u>_acc_si"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI
	  (subreg:SI
	    (mult:DI
	      (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
	      (any_extend:DI (match_operand:SI 2 "register_operand" "r"))) 4)
	  (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "mhacc<u>\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "rvp_mulhi_acc" "yes")
   (set_attr "mode" "SI")])

(define_insn "*rvp_mulh<su>mixed_acc_si"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI
	  (subreg:SI
	    (mult:DI
	      (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
	      (<rvp_other_extend>:DI
		(match_operand:SI 2 "register_operand" "r"))) 4)
	  (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "mhaccsu\t%0,<rvp_mixed_operands>"
  [(set_attr "type" "simd")
   (set_attr "rvp_mulhi_acc" "yes")
   (set_attr "mode" "SI")])

(define_insn "*rvp_round_mulh<u>_acc_si"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI
	  (subreg:SI
	    (plus:DI
	      (mult:DI
		(any_extend:DI (match_operand:SI 1 "register_operand" "r"))
		(any_extend:DI (match_operand:SI 2 "register_operand" "r")))
	      (const_int 2147483648)) 4)
	  (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "mhracc<u>\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "rvp_mulhi_acc" "yes")
   (set_attr "mode" "SI")])

(define_insn "*rvp_round_mulh<su>mixed_acc_si"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI
	  (subreg:SI
	    (plus:DI
	      (mult:DI
		(any_extend:DI (match_operand:SI 1 "register_operand" "r"))
		(<rvp_other_extend>:DI
		  (match_operand:SI 2 "register_operand" "r")))
	      (const_int 2147483648)) 4)
	  (match_operand:SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "mhraccsu\t%0,<rvp_mixed_operands>"
  [(set_attr "type" "simd")
   (set_attr "rvp_mulhi_acc" "yes")
   (set_attr "mode" "SI")])

;; RV64 combines a word addition with a high-word extraction.  Freeze the
;; input range classification while splitting, before IRA loses the facts.
(define_int_iterator RVP_WORD_ACC
  [UNSPEC_PMHACC UNSPEC_PMHACCU UNSPEC_PMHACCSU
   UNSPEC_PMHRACC UNSPEC_PMHRACCU UNSPEC_PMHRACCSU])

(define_int_attr rvp_word_acc
  [(UNSPEC_PMHACC "mhacc") (UNSPEC_PMHACCU "mhaccu")
   (UNSPEC_PMHACCSU "mhaccsu") (UNSPEC_PMHRACC "mhracc")
   (UNSPEC_PMHRACCU "mhraccu") (UNSPEC_PMHRACCSU "mhraccsu")])

;; Keep the accumulator as an input until allocation ties it to the output.
;; This avoids an explicit copy in combine's replacement sequence.
(define_insn "riscv_p_<rvp_word_acc>_pv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(unspec:PV2SI
	  [(match_operand:PV2SI 3 "register_operand" "0")
	   (match_operand:PV2SI 1 "register_operand" "r")
	   (match_operand:PV2SI 2 "register_operand" "r")]
	  RVP_WORD_ACC))]
  "TARGET_RVP && TARGET_64BIT"
  "p<rvp_word_acc>.w\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

;; Scalar consumers discard the upper packed result lane.  Remove explicit
;; input word extensions only in this context, and keep the complete packed
;; definition in the replacement so allocation accounts for both lanes.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(any_extend:DI
	  (subreg:SI
	    (unspec:PV2SI
	      [(match_operand:PV2SI 3 "rvp_low_word_packed_operand")
	       (match_operand:PV2SI 1 "rvp_low_word_packed_operand")
	       (match_operand:PV2SI 2 "rvp_low_word_packed_operand")]
	      RVP_WORD_ACC) 0)))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && (!register_operand (operands[1], PV2SImode)
       || !register_operand (operands[2], PV2SImode)
       || !register_operand (operands[3], PV2SImode))"
  [(const_int 0)]
{
  rtx result = gen_reg_rtx (PV2SImode);
  for (int i = 1; i <= 3; ++i)
    operands[i] = riscv_p_low_word_packed_operand (operands[i]);
  emit_insn (gen_riscv_p_<rvp_word_acc>_pv2si (result, operands[1],
					   operands[2], operands[3]));
  convert_move (operands[0], gen_lowpart (SImode, result),
		<CODE> == ZERO_EXTEND);
  DONE;
})

(define_split
  [(set (match_operand:SI 0 "register_operand")
	(subreg:SI
	  (unspec:PV2SI
	    [(match_operand:PV2SI 3 "rvp_low_word_packed_operand")
	     (match_operand:PV2SI 1 "rvp_low_word_packed_operand")
	     (match_operand:PV2SI 2 "rvp_low_word_packed_operand")]
	    RVP_WORD_ACC) 0))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && (!register_operand (operands[1], PV2SImode)
       || !register_operand (operands[2], PV2SImode)
       || !register_operand (operands[3], PV2SImode))"
  [(const_int 0)]
{
  rtx result = gen_reg_rtx (PV2SImode);
  for (int i = 1; i <= 3; ++i)
    operands[i] = riscv_p_low_word_packed_operand (operands[i]);
  emit_insn (gen_riscv_p_<rvp_word_acc>_pv2si (result, operands[1],
					   operands[2], operands[3]));
  emit_move_insn (operands[0], gen_lowpart (SImode, result));
  DONE;
})

;; Keep the complete unsigned word sum at the addition until splitting.
;; A direct combine split can place its first instruction before an
;; intervening accumulator load.  Explicit extensions record signedness
;; without relying on range information after combine.
(define_insn_and_split "*rvp_umulhi_acc_word"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI
	  (plus:SI
	    (subreg:SI
	      (zero_extract:DI
		(mult:DI
		  (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
		  (zero_extend:DI (match_operand:SI 2 "register_operand" "r")))
		(const_int 32) (const_int 32)) 0)
	    (match_operand:SI 3 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  riscv_p_expand_mulhi_acc (operands[0], operands[1], operands[2],
			    operands[3], false, 1);
  DONE;
}
  [(set_attr "type" "simd")
   (set_attr "rvp_mulhi_acc" "word")
   (set_attr "mode" "DI")
   (set_attr "length" "8")])

(define_split
  [(set (match_operand:SI 0 "nonimmediate_operand")
	(plus:SI
	  (subreg:SI
	    (zero_extract:DI
	      (mult:DI
		(zero_extend:DI (match_operand:SI 1 "register_operand"))
		(zero_extend:DI (match_operand:SI 2 "register_operand")))
	      (const_int 32) (const_int 32)) 0)
	  (match_operand:SI 3 "register_operand")))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()"
  [(const_int 0)]
{
  riscv_p_expand_mulhi_acc (operands[0], operands[1], operands[2],
			    operands[3], false, 1);
  DONE;
})

(define_split
  [(set (match_operand:DI 0 "register_operand")
	(sign_extend:DI
	  (plus:SI
	    (subreg:SI
	      (zero_extract:DI
		(mult:DI
		  (match_operand:DI 1 "rvp_word_product_operand")
		  (match_operand:DI 2 "rvp_word_product_operand"))
		(const_int 32) (const_int 32)) 0)
	    (match_operand:SI 3 "register_operand"))))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && riscv_p_round_mulhi_p (operands[1], operands[2])"
  [(const_int 0)]
{
  riscv_p_expand_mulhi_acc (operands[0], operands[1], operands[2],
			    operands[3], false);
  DONE;
})

(define_split
  [(set (match_operand:DI 0 "register_operand")
	(sign_extend:DI
	  (plus:SI
	    (subreg:SI
	      (any_shiftrt:DI
		(mult:DI
		  (match_operand:DI 1 "rvp_word_product_operand")
		  (match_operand:DI 2 "rvp_word_product_operand"))
		(const_int 32)) 0)
	    (match_operand:SI 3 "register_operand"))))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && riscv_p_round_mulhi_p (operands[1], operands[2])"
  [(const_int 0)]
{
  riscv_p_expand_mulhi_acc (operands[0], operands[1], operands[2],
			    operands[3], false);
  DONE;
})

;; Also fold a packed multiply-high already selected by an earlier split.
;; Only its low word is consumed; the complete packed result is still
;; represented in the replacement instruction.
(define_int_iterator RVP_MULHI_ACC
  [UNSPEC_PMULH UNSPEC_PMULHU UNSPEC_PMULHSU
   UNSPEC_PMULHR UNSPEC_PMULHRU UNSPEC_PMULHRSU])

;; The same low-word proof applies without an accumulator.  Do not include
;; saturating Q-format products, whose unused lanes may affect VXSAT.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(any_extend:DI
	  (subreg:SI
	    (unspec:PV2SI
	      [(match_operand:PV2SI 1 "rvp_low_word_packed_operand")
	       (match_operand:PV2SI 2 "rvp_low_word_packed_operand")]
	      RVP_MULHI_ACC) 0)))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && (!register_operand (operands[1], PV2SImode)
       || !register_operand (operands[2], PV2SImode))"
  [(const_int 0)]
{
  rtx result = gen_reg_rtx (PV2SImode);
  operands[1] = riscv_p_low_word_packed_operand (operands[1]);
  operands[2] = riscv_p_low_word_packed_operand (operands[2]);
  emit_insn (gen_riscv_<rvp_scalar_mul_packed> (result, operands[1],
					    operands[2]));
  convert_move (operands[0], gen_lowpart (SImode, result),
		<CODE> == ZERO_EXTEND);
  DONE;
})

(define_split
  [(set (match_operand:SI 0 "register_operand")
	(subreg:SI
	  (unspec:PV2SI
	    [(match_operand:PV2SI 1 "rvp_low_word_packed_operand")
	     (match_operand:PV2SI 2 "rvp_low_word_packed_operand")]
	    RVP_MULHI_ACC) 0))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && (!register_operand (operands[1], PV2SImode)
       || !register_operand (operands[2], PV2SImode))"
  [(const_int 0)]
{
  rtx result = gen_reg_rtx (PV2SImode);
  operands[1] = riscv_p_low_word_packed_operand (operands[1]);
  operands[2] = riscv_p_low_word_packed_operand (operands[2]);
  emit_insn (gen_riscv_<rvp_scalar_mul_packed> (result, operands[1],
					    operands[2]));
  emit_move_insn (operands[0], gen_lowpart (SImode, result));
  DONE;
})

(define_int_attr rvp_mulhi_acc_kind
  [(UNSPEC_PMULH "0") (UNSPEC_PMULHU "1") (UNSPEC_PMULHSU "2")
   (UNSPEC_PMULHR "0") (UNSPEC_PMULHRU "1") (UNSPEC_PMULHRSU "2")])

(define_int_attr rvp_mulhi_acc_round
  [(UNSPEC_PMULH "false") (UNSPEC_PMULHU "false")
   (UNSPEC_PMULHSU "false") (UNSPEC_PMULHR "true")
   (UNSPEC_PMULHRU "true") (UNSPEC_PMULHRSU "true")])

(define_split
  [(set (match_operand:DI 0 "register_operand")
	(sign_extend:DI
	  (plus:SI
	    (subreg:SI
	      (unspec:PV2SI
		[(match_operand:PV2SI 1 "register_operand")
		 (match_operand:PV2SI 2 "register_operand")]
		RVP_MULHI_ACC) 0)
	    (match_operand:SI 3 "register_operand"))))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()"
  [(const_int 0)]
{
  riscv_p_expand_mulhi_acc (operands[0], gen_lowpart (DImode, operands[1]),
			    gen_lowpart (DImode, operands[2]), operands[3],
			    <rvp_mulhi_acc_round>, <rvp_mulhi_acc_kind>);
  DONE;
})

;; A store consumes only the modular word sum.  Matching it together with
;; the addition lets combine place the fused operation after an intervening
;; accumulator load, rather than at the earlier multiply's position.
(define_split
  [(set (match_operand:SI 0 "nonimmediate_operand")
	(plus:SI
	  (subreg:SI
	    (unspec:PV2SI
	      [(match_operand:PV2SI 1 "register_operand")
	       (match_operand:PV2SI 2 "register_operand")]
	      RVP_MULHI_ACC) 0)
	  (match_operand:SI 3 "register_operand")))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()"
  [(const_int 0)]
{
  riscv_p_expand_mulhi_acc (operands[0], gen_lowpart (DImode, operands[1]),
			    gen_lowpart (DImode, operands[2]), operands[3],
			    <rvp_mulhi_acc_round>, <rvp_mulhi_acc_kind>);
  DONE;
})

;; -------------------------------------------------------------------------
;; USATI - Unsigned Saturation Immediate
;; -------------------------------------------------------------------------
;; Saturates a signed value to an unsigned n-bit range [0, 2^n - 1].
;; If rs1 < 0, result is 0.
;; If rs1 > (2^n - 1), result is (2^n - 1).
;; Otherwise, result is rs1.
;;
;; Recognize smin(smax(x, 0), (1 << N) - 1) pattern for USATI.
;; Requires Zbb extension for smax/smin RTL operations.

(define_insn "*usati_alt<X:mode>"
  [(set (match_operand:X 0 "register_operand" "=r")
	(smax:X (smin:X (match_operand:X 1 "register_operand" "r")
			(match_operand:X 2 "const_int_operand" "n"))
		(const_int 0)))]
  "TARGET_RVP
   && IN_RANGE (exact_log2 (INTVAL (operands[2]) + 1), 1,
		GET_MODE_BITSIZE (<X:MODE>mode) - 1)"
{
  operands[2] = GEN_INT (exact_log2 (INTVAL (operands[2]) + 1));
  return "usati\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "<X:MODE>")])

(define_insn "*usati<X:mode>"
  [(set (match_operand:X 0 "register_operand" "=r")
	(smin:X (smax:X (match_operand:X 1 "register_operand" "r")
			(const_int 0))
		(match_operand:X 2 "const_int_operand" "n")))]
  "TARGET_RVP
   && IN_RANGE (exact_log2 (INTVAL (operands[2]) + 1), 1,
		GET_MODE_BITSIZE (<X:MODE>mode) - 1)"
{
  operands[2] = GEN_INT (exact_log2 (INTVAL (operands[2]) + 1));
  return "usati\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "<X:MODE>")])

;; -------------------------------------------------------------------------
;; PNCLIPI / PNCLIPIU (RV32), PNCLIPP / PNCLIPUP (RV64) - Narrowing clips
;; -------------------------------------------------------------------------

;; A byte result comes from PV4HI and a halfword result from PV2SI, so the
;; source is always an 8-byte mode, a register pair on RV32.  The RV32 forms
;; hold a shift amount in the instruction; the RV64 ones have no shift field,
;; so a shifted clip needs a separate packed shift there.

(define_insn "<sat_trunc_optab><mode><rvp_narrow>2"
  [(set (match_operand:<rvp_narrow_mode> 0 "register_operand" "=r")
	(any_sat_trunc:<rvp_narrow_mode>
	  (match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")))]
  "TARGET_RVP"
  {
    if (TARGET_64BIT)
      return "<nclip_pair_insn>.<rvp_extend_width>\t%0, %1, zero";
    return "<nclip_imm_insn>.<rvp_extend_width>\t%0, %1, 0";
  }
  [(set_attr "type" "arith")
   (set (attr "mode") (if_then_else (match_test "TARGET_64BIT")
				     (const_string "DI") (const_string "SI")))])

;; Narrow and pack two signed vectors, with the first source in the low half.
;; RV32 needs two clips, each reading an even-odd register pair.  Complete
;; both clips before assembling the result, so overlapping inputs survive.
(define_expand "vec_pack_ssat_<mode>"
  [(match_operand:<rvp_pack_mode> 0 "register_operand")
   (match_operand:RVP_DWIDTH_EXT 1 "register_operand")
   (match_operand:RVP_DWIDTH_EXT 2 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && !TARGET_VECTOR"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_p_vec_pack_ssat_<mode> (operands[0], operands[1],
					      operands[2]));
  else
    {
      rtx lo = gen_reg_rtx (<rvp_narrow_mode>mode);
      rtx hi = gen_reg_rtx (<rvp_narrow_mode>mode);
      emit_insn (gen_sstrunc<mode><rvp_narrow>2 (lo, operands[1]));
      emit_insn (gen_sstrunc<mode><rvp_narrow>2 (hi, operands[2]));
      emit_move_insn (gen_lowpart (<rvp_narrow_mode>mode, operands[0]), lo);
      emit_move_insn (gen_highpart (<rvp_narrow_mode>mode, operands[0]), hi);
    }
  DONE;
})

;; Two word-sized inputs form the source pair for a single byte clip.
(define_expand "vec_pack_ssat_pv2hi"
  [(match_operand:PV4QI 0 "register_operand")
   (match_operand:PV2HI 1 "register_operand")
   (match_operand:PV2HI 2 "register_operand")]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN && !TARGET_VECTOR"
{
  rtx combined = gen_reg_rtx (PV4HImode);
  emit_move_insn (gen_lowpart (PV2HImode, combined), operands[1]);
  emit_move_insn (gen_highpart (PV2HImode, combined), operands[2]);
  emit_insn (gen_sstruncpv4hipv4qi2 (operands[0], combined));
  DONE;
})

;; Logical vector order matches PNCLIPP register order on little-endian RV64.
(define_insn "riscv_p_vec_pack_ssat_<mode>"
  [(set (match_operand:<rvp_pack_mode> 0 "register_operand" "=r")
	(vec_concat:<rvp_pack_mode>
	  (ss_truncate:<rvp_narrow_mode>
	    (match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r"))
	  (ss_truncate:<rvp_narrow_mode>
	    (match_operand:RVP_DWIDTH_EXT 2 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN && !TARGET_VECTOR"
  "pnclipp.<rvp_extend_width>\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Keeps the truncation visible to combine so the clip patterns below can
;; absorb it.  Unmatched instances stay as PNCVT, which packs the low half of
;; each lane and so preserves true truncation semantics, unlike the saturating
;; clips.  PNCVT.B is pnsrli.b rd, rs1_p, 0 on RV32 and unzip8p rd, rs1, x0 on
;; RV64; PNCVT.H is pnsrli.h rd, rs1_p, 0 and unzip16p rd, rs1, x0.
(define_insn "trunc<mode><rvp_narrow>2"
  [(set (match_operand:<rvp_narrow_mode> 0 "register_operand" "=r")
	(truncate:<rvp_narrow_mode>
	  (match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    return <MODE>mode == PV4HImode ? "unzip8p\t%0, %1, zero"
				  : "unzip16p\t%0, %1, zero";
  return "pncvt.<rvp_extend_width>\t%0, %1";
}
  [(set_attr "type" "arith")
   (set (attr "mode") (if_then_else (match_test "TARGET_64BIT")
				     (const_string "DI") (const_string "SI")))])

;; Combine two truncated halves and their word concatenation into a single
;; two-source unzip.  Keep the individual truncations during expansion so
;; the saturating clip patterns can still match before this combination.
(define_insn "*rvp_pack_trunc_<mode>"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(vec_concat:PV2SI
	  (subreg:SI
	    (truncate:<rvp_narrow_mode>
	      (match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")) 0)
	  (subreg:SI
	    (truncate:<rvp_narrow_mode>
	      (match_operand:RVP_DWIDTH_EXT 2 "register_operand" "r")) 0)))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN"
{
  return <MODE>mode == PV4HImode ? "unzip8p\t%0,%1,%2"
			       : "unzip16p\t%0,%1,%2";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; The odd-byte counterpart of PNCVT.B: pnsrli.b rd, rs1_p, 8 on RV32 and
;; unzip8hp rd, rs1, x0 on RV64.  Used by the PV4QI odd unzip permute.
(define_insn "riscv_pncvth_b"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
	(truncate:PV4QI
	  (lshiftrt:PV4HI (match_operand:PV4HI 1 "register_operand" "r")
			  (const_int 8))))]
  "TARGET_RVP"
{
  return TARGET_64BIT ? "unzip8hp\t%0, %1, zero" : "pncvth.b\t%0, %1";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; Adjacent small loads can form the source pair without register copies.
(define_insn_and_split "*riscv_p_pack_trunc_load_pv2hi"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
	(truncate:PV4QI
	  (vec_concat:PV4HI
	    (match_operand:PV2HI 1 "memory_operand" "m")
	    (match_operand:PV2HI 2 "memory_operand" "m"))))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && !TARGET_VECTOR
   && can_create_pseudo_p ()
   && riscv_p_small_pack_mems_p (operands[1], operands[2])"
  "#"
  "&& 1"
  [(const_int 0)]
{
  rtx mem = riscv_p_small_pack_mem (operands[1], operands[2]);
  rtx combined = force_reg (PV4HImode, mem);
  emit_insn (gen_truncpv4hipv4qi2 (operands[0], combined));
  DONE;
}
  [(set_attr "type" "load")
   (set_attr "mode" "DI")
   (set (attr "length") (if_then_else (match_test "TARGET_64BIT")
				       (const_int 8) (const_int 12)))])

;; Keep the small pack as one operation, allowing combine to absorb both
;; source clamps and their shared bound before splitting the fallback.
(define_insn_and_split "riscv_p_pack_trunc_pv2hi"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
	(truncate:PV4QI
	  (vec_concat:PV4HI
	    (match_operand:PV2HI 1 "register_operand" "r")
	    (match_operand:PV2HI 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && !TARGET_VECTOR
   && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  rtx combined;
  if (TARGET_64BIT)
    {
      rtx pair = gen_reg_rtx (PV2SImode);
      emit_insn (gen_pack_concatpv2si (pair, gen_lowpart (SImode, operands[1]),
				     gen_lowpart (SImode, operands[2])));
      combined = gen_lowpart (PV4HImode, pair);
    }
  else
    {
      combined = gen_reg_rtx (PV4HImode);
      /* Define the full pseudo with an undefined upper half.  Other
	 register operands cannot always be widened into a register pair.  */
      if (REG_P (operands[1]) && !HARD_REGISTER_P (operands[1]))
	emit_move_insn (combined, gen_rtx_SUBREG (PV4HImode, operands[1], 0));
      else
	emit_move_insn (gen_lowpart (PV2HImode, combined), operands[1]);
      emit_move_insn (gen_highpart (PV2HImode, combined), operands[2]);
    }
  emit_insn (gen_truncpv4hipv4qi2 (operands[0], combined));
  DONE;
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")
   (set (attr "length") (if_then_else (match_test "TARGET_64BIT")
				       (const_int 8) (const_int 12)))])

(define_expand "vec_pack_trunc_pv2hi"
  [(match_operand:PV4QI 0 "register_operand" "")
   (match_operand:PV2HI 1 "register_operand" "")	; lo half
   (match_operand:PV2HI 2 "register_operand" "")]	; hi half
  "TARGET_RVP"
{
  if (!TARGET_BIG_ENDIAN && !TARGET_VECTOR)
    {
      emit_insn (gen_riscv_p_pack_trunc_pv2hi (operands[0], operands[1],
					    operands[2]));
      DONE;
    }
  rtx combined;
  if (TARGET_64BIT)
    {
      /* On RV64 validate_subreg rejects a non-lowpart 4-byte subreg of a
	 PV4HI pseudo, so build the pair with a PACK (ppaire.w) instead.  */
      rtx combined_v = gen_reg_rtx (PV2SImode);
      emit_insn (gen_rtx_SET (combined_v,
			      gen_rtx_VEC_CONCAT (PV2SImode,
						  gen_lowpart (SImode,
							       operands[1]),
						  gen_lowpart (SImode,
							       operands[2]))));
      combined = gen_lowpart (PV4HImode, combined_v);
    }
  else
    {
      combined = gen_reg_rtx (PV4HImode);
      emit_move_insn (gen_lowpart (PV2HImode, combined), operands[1]);
      emit_move_insn (gen_highpart (PV2HImode, combined), operands[2]);
    }
  emit_insn (gen_truncpv4hipv4qi2 (operands[0], combined));
  DONE;
})

;; A clamp to the exact result range followed by a truncation is a saturating
;; truncation, but combine does not canonicalise either shape into one, so
;; catch them and rewrite.  Only the exact range qualifies: a narrower bound is
;; a different operation.
(define_insn_and_split "*sstrunc_<mode>_clamp"
  [(set (match_operand:<rvp_narrow_mode> 0 "register_operand" "=r")
	(truncate:<rvp_narrow_mode>
	  (smax:RVP_DWIDTH_EXT
	    (smin:RVP_DWIDTH_EXT (match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")
			    (match_operand:RVP_DWIDTH_EXT 2 "immediate_operand"))
	    (match_operand:RVP_DWIDTH_EXT 3 "immediate_operand"))))]
  "TARGET_RVP
   && riscv_const_vector_broadcast_val_p (operands[2], <rvp_narrow_smax>)
   && riscv_const_vector_broadcast_val_p (operands[3], <rvp_narrow_smin>)"
  "#"
  "&& 1"
  [(set (match_dup 0)
	(ss_truncate:<rvp_narrow_mode> (match_dup 1)))]
  ""
  [(set_attr "type" "arith")
   (set (attr "mode") (if_then_else (match_test "TARGET_64BIT")
				     (const_string "DI") (const_string "SI")))])

;; See *sstrunc_<mode>_clamp.  The signed clamp smax (smin (x, UMAX), 0) must
;; not be rewritten here: it maps negatives to 0, while the clip maps them to
;; UMAX.
(define_insn_and_split "*ustrunc_<mode>_umin"
  [(set (match_operand:<rvp_narrow_mode> 0 "register_operand" "=r")
	(truncate:<rvp_narrow_mode>
	  (umin:RVP_DWIDTH_EXT (match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")
			  (match_operand:RVP_DWIDTH_EXT 2 "immediate_operand"))))]
  "TARGET_RVP
   && riscv_const_vector_broadcast_val_p (operands[2], <rvp_narrow_umax>)"
  "#"
  "&& 1"
  [(set (match_dup 0)
	(us_truncate:<rvp_narrow_mode> (match_dup 1)))]
  ""
  [(set_attr "type" "arith")
   (set (attr "mode") (if_then_else (match_test "TARGET_64BIT")
				     (const_string "DI") (const_string "SI")))])

;; Pack two exact unsigned clamps directly.  The one-source clamp patterns
;; above retain TRUNCATE (UMIN) until splitting, so match that representation
;; as well as keeping the source lane order used by VEC_CONCAT.
(define_insn "*rvp_pack_ustrunc_<mode>"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(vec_concat:PV2SI
	  (subreg:SI
	    (truncate:<rvp_narrow_mode>
	      (umin:RVP_DWIDTH_EXT
		(match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")
		(match_operand:RVP_DWIDTH_EXT 3 "immediate_operand"))) 0)
	  (subreg:SI
	    (truncate:<rvp_narrow_mode>
	      (umin:RVP_DWIDTH_EXT
		(match_operand:RVP_DWIDTH_EXT 2 "register_operand" "r")
		(match_operand:RVP_DWIDTH_EXT 4 "immediate_operand"))) 0)))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && riscv_const_vector_broadcast_val_p (operands[3], <rvp_narrow_umax>)
   && riscv_const_vector_broadcast_val_p (operands[4], <rvp_narrow_umax>)"
  "pnclipup.<rvp_extend_width>\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn_and_split "*rvp_pack_ustrunc_small_load"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
	(truncate:PV4QI
	  (vec_concat:PV4HI
	    (umin:PV2HI (match_operand:PV2HI 1 "memory_operand" "m")
		       (match_operand:PV2HI 3 "immediate_operand"))
	    (umin:PV2HI (match_operand:PV2HI 2 "memory_operand" "m")
		       (match_operand:PV2HI 4 "immediate_operand")))))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && !TARGET_VECTOR
   && can_create_pseudo_p ()
   && riscv_p_small_pack_mems_p (operands[1], operands[2])
   && riscv_const_vector_broadcast_val_p (operands[3], 255)
   && riscv_const_vector_broadcast_val_p (operands[4], 255)"
  "#"
  "&& 1"
  [(const_int 0)]
{
  rtx mem = riscv_p_small_pack_mem (operands[1], operands[2]);
  rtx combined = force_reg (PV4HImode, mem);
  emit_insn (gen_ustruncpv4hipv4qi2 (operands[0], combined));
  DONE;
}
  [(set_attr "type" "load")
   (set_attr "mode" "DI")
   (set (attr "length") (if_then_else (match_test "TARGET_64BIT")
				       (const_int 8) (const_int 12)))])

;; The small-vector pack has two halfword pairs as inputs.  Form the full
;; source before clipping, so either source can overlap the final result.
(define_insn_and_split "*rvp_pack_ustrunc_small"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
	(truncate:PV4QI
	  (vec_concat:PV4HI
	    (umin:PV2HI (match_operand:PV2HI 1 "register_operand" "r")
		       (match_operand:PV2HI 3 "immediate_operand"))
	    (umin:PV2HI (match_operand:PV2HI 2 "register_operand" "r")
		       (match_operand:PV2HI 4 "immediate_operand")))))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && !TARGET_VECTOR
   && can_create_pseudo_p ()
   && riscv_const_vector_broadcast_val_p (operands[3], 255)
   && riscv_const_vector_broadcast_val_p (operands[4], 255)"
  "#"
  "&& 1"
  [(const_int 0)]
{
  rtx combined;
  if (TARGET_64BIT)
    {
      rtx pair = gen_reg_rtx (PV2SImode);
      emit_insn (gen_pack_concatpv2si (pair, gen_lowpart (SImode, operands[1]),
				     gen_lowpart (SImode, operands[2])));
      combined = gen_lowpart (PV4HImode, pair);
    }
  else
    {
      combined = gen_reg_rtx (PV4HImode);
      /* Define the full pseudo with an undefined upper half.  Other
	 register operands cannot always be widened into a register pair.  */
      if (REG_P (operands[1]) && !HARD_REGISTER_P (operands[1]))
	emit_move_insn (combined, gen_rtx_SUBREG (PV4HImode, operands[1], 0));
      else
	emit_move_insn (gen_lowpart (PV2HImode, combined), operands[1]);
      emit_move_insn (gen_highpart (PV2HImode, combined), operands[2]);
    }
  emit_insn (gen_ustruncpv4hipv4qi2 (operands[0], combined));
  DONE;
}
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")
   (set (attr "length") (if_then_else (match_test "TARGET_64BIT")
				       (const_int 8) (const_int 12)))])

;; The RV32 clips hold the shift amount themselves.
(define_insn "*pnclipi_<rvp_extend_width>_rv32"
  [(set (match_operand:<rvp_narrow_mode> 0 "register_operand" "=r")
	(truncate:<rvp_narrow_mode>
	  (smax:RVP_DWIDTH_EXT
	    (smin:RVP_DWIDTH_EXT
	      (ashiftrt:RVP_DWIDTH_EXT
		(match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")
		(match_operand 2 "const_int_operand"))
	      (match_operand:RVP_DWIDTH_EXT 3 "immediate_operand"))
	    (match_operand:RVP_DWIDTH_EXT 4 "immediate_operand"))))]
  "TARGET_RVP && !TARGET_64BIT
   && IN_RANGE (INTVAL (operands[2]), 1, <rvp_narrow_shmax>)
   && riscv_const_vector_broadcast_val_p (operands[3], <rvp_narrow_smax>)
   && riscv_const_vector_broadcast_val_p (operands[4], <rvp_narrow_smin>)"
  "pnclipi.<rvp_extend_width>\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; The RV64 clips have no shift field, so split the shift back out.
(define_insn_and_split "*pnclipp_<rvp_extend_width>_rv64"
  [(set (match_operand:<rvp_narrow_mode> 0 "register_operand" "=r")
	(truncate:<rvp_narrow_mode>
	  (smax:RVP_DWIDTH_EXT
	    (smin:RVP_DWIDTH_EXT
	      (ashiftrt:RVP_DWIDTH_EXT
		(match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")
		(match_operand 2 "const_int_operand"))
	      (match_operand:RVP_DWIDTH_EXT 3 "immediate_operand"))
	    (match_operand:RVP_DWIDTH_EXT 4 "immediate_operand"))))]
  "TARGET_RVP && TARGET_64BIT
   && IN_RANGE (INTVAL (operands[2]), 1, <rvp_narrow_shmax>)
   && riscv_const_vector_broadcast_val_p (operands[3], <rvp_narrow_smax>)
   && riscv_const_vector_broadcast_val_p (operands[4], <rvp_narrow_smin>)
   && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(set (match_dup 5) (ashiftrt:RVP_DWIDTH_EXT (match_dup 1) (match_dup 2)))
   (set (match_dup 0) (ss_truncate:<rvp_narrow_mode> (match_dup 5)))]
  "{ operands[5] = gen_reg_rtx (<MODE>mode); }"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; The unsigned clips compute min (zext (lane) >> shamt, UMAX): the lane is
;; treated as unsigned and shifted logically, so only a logical shift with a
;; bound of exactly UMAX may use them.  An arithmetic shift, or a signed clamp
;; of one, is a different operation -- negatives clamp to 0, not to UMAX -- and
;; must not be matched here.  A logical shift makes every lane non-negative, so
;; a *signed* clamp of one is still the unsigned clip, and is the shape an
;; unsigned narrowing gets when the clamp is written in a signed type.
(define_insn "*pnclipiu_<rvp_extend_width>_lshr_rv32"
  [(set (match_operand:<rvp_narrow_mode> 0 "register_operand" "=r")
	(truncate:<rvp_narrow_mode>
	  (smax:RVP_DWIDTH_EXT
	    (smin:RVP_DWIDTH_EXT
	      (lshiftrt:RVP_DWIDTH_EXT
		(match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")
		(match_operand 2 "const_int_operand"))
	      (match_operand:RVP_DWIDTH_EXT 3 "immediate_operand"))
	    (match_operand:RVP_DWIDTH_EXT 4 "immediate_operand"))))]
  "TARGET_RVP && !TARGET_64BIT
   && IN_RANGE (INTVAL (operands[2]), 1, <rvp_narrow_shmax>)
   && riscv_const_vector_broadcast_val_p (operands[3], <rvp_narrow_umax>)
   && riscv_const_vector_broadcast_val_p (operands[4], 0)"
  "pnclipiu.<rvp_extend_width>\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; An unsigned-typed clamp gives umin rather than smax (smin).
(define_insn "*pnclipiu_<rvp_extend_width>_lshr_umin_rv32"
  [(set (match_operand:<rvp_narrow_mode> 0 "register_operand" "=r")
	(truncate:<rvp_narrow_mode>
	  (umin:RVP_DWIDTH_EXT
	    (lshiftrt:RVP_DWIDTH_EXT
	      (match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")
	      (match_operand 2 "const_int_operand"))
	    (match_operand:RVP_DWIDTH_EXT 3 "immediate_operand"))))]
  "TARGET_RVP && !TARGET_64BIT
   && IN_RANGE (INTVAL (operands[2]), 1, <rvp_narrow_shmax>)
   && riscv_const_vector_broadcast_val_p (operands[3], <rvp_narrow_umax>)"
  "pnclipiu.<rvp_extend_width>\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; Only the signed-clamp shape needs an RV64 pattern: the umin one cannot be
;; fused with the shift either way, so it is already left as a packed shift
;; plus the no-shift clip, which is what this splits into.
(define_insn_and_split "*pnclipup_<rvp_extend_width>_lshr_rv64"
  [(set (match_operand:<rvp_narrow_mode> 0 "register_operand" "=r")
	(truncate:<rvp_narrow_mode>
	  (smax:RVP_DWIDTH_EXT
	    (smin:RVP_DWIDTH_EXT
	      (lshiftrt:RVP_DWIDTH_EXT
		(match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")
		(match_operand 2 "const_int_operand"))
	      (match_operand:RVP_DWIDTH_EXT 3 "immediate_operand"))
	    (match_operand:RVP_DWIDTH_EXT 4 "immediate_operand"))))]
  "TARGET_RVP && TARGET_64BIT
   && IN_RANGE (INTVAL (operands[2]), 1, <rvp_narrow_shmax>)
   && riscv_const_vector_broadcast_val_p (operands[3], <rvp_narrow_umax>)
   && riscv_const_vector_broadcast_val_p (operands[4], 0)
   && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(set (match_dup 5) (lshiftrt:RVP_DWIDTH_EXT (match_dup 1) (match_dup 2)))
   (set (match_dup 0) (us_truncate:<rvp_narrow_mode> (match_dup 5)))]
  "{ operands[5] = gen_reg_rtx (<MODE>mode); }"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; =========================================================================
;; PSATI.H / PSATI.DH / PSATI.W / PSATI.DW - Signed saturation clipping
;; PUSATI.H / PUSATI.DH / PUSATI.W / PUSATI.DW - Unsigned saturation clipping
;;
;; psati.h rd, rs1, W  -- saturate each halfword to [-2^(W-1), 2^(W-1)-1].
;; For an smin bound of 2^N-1, the signed textual width W is N+1.
;; pusati.h rd, rs1, N -- clamp each signed halfword to [0, (1<<N)-1].
;; An unsigned UMIN must use PMINU instead: PUSATI maps negative signed
;; inputs to zero, not to the upper bound.
;; =========================================================================

;; PSATI.H for PV2HI (4-byte, always single register)
(define_insn "*psati_h_pv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
	(smax:PV2HI
	  (smin:PV2HI (match_operand:PV2HI 1 "register_operand" "r")
		      (match_operand:PV2HI 2 "immediate_operand"))
	  (match_operand:PV2HI 3 "immediate_operand")))]
  "TARGET_RVP
   && riscv_psati_bounds_p (operands[2], operands[3], 15)"
  {
    static char buf[32];
    snprintf (buf, sizeof (buf), "psati.h\t%%0, %%1, %d",
	      riscv_psati_imm (operands[2]) + 1);
    return buf;
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; PSATI.H (RV64) / PSATI.DH (RV32) for PV4HI (8-byte)
(define_insn "*psati_h_pv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
	(smax:PV4HI
	  (smin:PV4HI (match_operand:PV4HI 1 "register_operand" "r")
		      (match_operand:PV4HI 2 "immediate_operand"))
	  (match_operand:PV4HI 3 "immediate_operand")))]
  "TARGET_RVP
   && riscv_psati_bounds_p (operands[2], operands[3], 15)"
  {
    static char buf[32];
    const char *insn = TARGET_64BIT ? "psati.h" : "psati.dh";
    snprintf (buf, sizeof (buf), "%s\t%%0, %%1, %d", insn,
	      riscv_psati_imm (operands[2]) + 1);
    return buf;
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; PSATI.W (RV64) / PSATI.DW (RV32) for PV2SI (8-byte words)
(define_insn "*psati_w_pv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(smax:PV2SI
	  (smin:PV2SI (match_operand:PV2SI 1 "register_operand" "r")
		      (match_operand:PV2SI 2 "immediate_operand"))
	  (match_operand:PV2SI 3 "immediate_operand")))]
  "TARGET_RVP
   && riscv_psati_bounds_p (operands[2], operands[3], 31)"
  {
    static char buf[32];
    const char *insn = TARGET_64BIT ? "psati.w" : "psati.dw";
    snprintf (buf, sizeof (buf), "%s\t%%0, %%1, %d", insn,
	      riscv_psati_imm (operands[2]) + 1);
    return buf;
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; PUSATI.H for PV2HI -- signed smax(smin) form: clamp [0, 2^N-1]
(define_insn "*pusati_h_signed_pv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
	(smax:PV2HI
	  (smin:PV2HI (match_operand:PV2HI 1 "register_operand" "r")
		      (match_operand:PV2HI 2 "immediate_operand"))
	  (match_operand:PV2HI 3 "immediate_operand")))]
  "TARGET_RVP
   && riscv_pusati_bounds_p (operands[2], 16)
   && riscv_const_vector_broadcast_val_p (operands[3], 0)"
  {
    static char buf[32];
    snprintf (buf, sizeof (buf), "pusati.h\t%%0, %%1, %d", riscv_psati_imm (operands[2]));
    return buf;
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; PUSATI.H for PV4HI -- signed smax(smin) form: clamp [0, 2^N-1]
(define_insn "*pusati_h_signed_pv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
	(smax:PV4HI
	  (smin:PV4HI (match_operand:PV4HI 1 "register_operand" "r")
		      (match_operand:PV4HI 2 "immediate_operand"))
	  (match_operand:PV4HI 3 "immediate_operand")))]
  "TARGET_RVP
   && riscv_pusati_bounds_p (operands[2], 16)
   && riscv_const_vector_broadcast_val_p (operands[3], 0)"
  {
    static char buf[32];
    const char *insn = TARGET_64BIT ? "pusati.h" : "pusati.dh";
    snprintf (buf, sizeof (buf), "%s\t%%0, %%1, %d", insn, riscv_psati_imm (operands[2]));
    return buf;
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; PUSATI.W for PV2SI -- signed smax(smin) form: clamp [0, 2^N-1]
(define_insn "*pusati_w_signed_pv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(smax:PV2SI
	  (smin:PV2SI (match_operand:PV2SI 1 "register_operand" "r")
		      (match_operand:PV2SI 2 "immediate_operand"))
	  (match_operand:PV2SI 3 "immediate_operand")))]
  "TARGET_RVP
   && riscv_pusati_bounds_p (operands[2], 32)
   && riscv_const_vector_broadcast_val_p (operands[3], 0)"
  {
    static char buf[32];
    const char *insn = TARGET_64BIT ? "pusati.w" : "pusati.dw";
    snprintf (buf, sizeof (buf), "%s\t%%0, %%1, %d", insn, riscv_psati_imm (operands[2]));
    return buf;
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; MVM/MVMN: Move under Mask / Move under Mask Negated
;; MVM:  rd = (~rs2 & rd) | (rs2 & rs1) - select rs1 where mask=1
;; MVMN: rd = (~rs2 & rs1) | (rs2 & rd) - select rs1 where mask=0
(define_insn_and_split "*mvm<mode>"
  [(set (match_operand:PVMVM 0 "register_operand" "=r,r")
	(ior:PVMVM
	  (and:PVMVM (not:PVMVM
		       (match_operand:PVMVM 2 "register_operand" "r,r"))
		     (match_operand:PVMVM 1 "register_operand" "0,r"))
	  (and:PVMVM (match_dup 2)
		     (match_operand:PVMVM 3 "register_operand" "r,0"))))]
  "TARGET_RVP"
{
  if (!TARGET_64BIT && known_eq (GET_MODE_SIZE (<MODE>mode), 8))
    return "#";
  return which_alternative == 0 ? "mvm\t%0,%3,%2" : "mvmn\t%0,%1,%2";
}
  "&& !TARGET_64BIT && known_eq (GET_MODE_SIZE (<MODE>mode), 8)
   && reload_completed"
  [(set (match_dup 4)
	(ior:SI (and:SI (not:SI (match_dup 6)) (match_dup 5))
		(and:SI (match_dup 6) (match_dup 7))))
   (set (match_dup 8)
	(ior:SI (and:SI (not:SI (match_dup 10)) (match_dup 9))
		(and:SI (match_dup 10) (match_dup 11))))]
{
  /* Packed pairs start at even registers, so complete pairs can overlap
     but their low and high halves cannot cross.  */
  for (unsigned int i = 0; i < 4; ++i)
    {
      operands[i + 4] = gen_lowpart (SImode, operands[i]);
      operands[i + 8] = gen_highpart (SImode, operands[i]);
    }
}
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")
   (set (attr "length")
	(if_then_else (match_test "!TARGET_64BIT
				  && known_eq (GET_MODE_SIZE (<MODE>mode), 8)")
		      (const_int 8) (const_int 4)))])

;; Normalize commuted OR-of-ANDs forms to the MVM pattern above.  Combine
;; can use these single-insn splits when a three-insn combination does not
;; match directly.  Keep the destination ties and register-pair splitting
;; in that one pattern.  The first split must not reproduce its own input
;; when the positive-mask value is also the mask.
(define_split
  [(set (match_operand:PVMVM 0 "register_operand")
	(ior:PVMVM
	  (and:PVMVM (not:PVMVM (match_operand:PVMVM 2 "register_operand"))
		     (match_operand:PVMVM 1 "register_operand"))
	  (and:PVMVM (match_operand:PVMVM 3 "register_operand")
		     (match_dup 2))))]
  "TARGET_RVP && can_create_pseudo_p ()
   && !rtx_equal_p (operands[2], operands[3])"
  [(set (match_dup 0)
	(ior:PVMVM (and:PVMVM (not:PVMVM (match_dup 2)) (match_dup 1))
		   (and:PVMVM (match_dup 2) (match_dup 3))))])

(define_split
  [(set (match_operand:PVMVM 0 "register_operand")
	(ior:PVMVM
	  (and:PVMVM (match_operand:PVMVM 2 "register_operand")
		     (match_operand:PVMVM 3 "register_operand"))
	  (and:PVMVM (not:PVMVM (match_dup 2))
		     (match_operand:PVMVM 1 "register_operand"))))]
  "TARGET_RVP && can_create_pseudo_p ()"
  [(set (match_dup 0)
	(ior:PVMVM (and:PVMVM (not:PVMVM (match_dup 2)) (match_dup 1))
		   (and:PVMVM (match_dup 2) (match_dup 3))))])

(define_split
  [(set (match_operand:PVMVM 0 "register_operand")
	(ior:PVMVM
	  (and:PVMVM (match_operand:PVMVM 3 "register_operand")
		     (match_operand:PVMVM 2 "register_operand"))
	  (and:PVMVM (not:PVMVM (match_dup 2))
		     (match_operand:PVMVM 1 "register_operand"))))]
  "TARGET_RVP && can_create_pseudo_p ()"
  [(set (match_dup 0)
	(ior:PVMVM (and:PVMVM (not:PVMVM (match_dup 2)) (match_dup 1))
		   (and:PVMVM (match_dup 2) (match_dup 3))))])

;; MVM/MVMN XOR forms: ((a ^ b) & mask) ^ c
;; This pattern is similar to AArch64's BSL (Bitwise Select) pattern.
;; We can use MVM or MVMN depending on register allocation:
;;   if (op0 == op1) mvm  op0, op3, op2  (selects op3 where mask=1)
;;   if (op0 == op3) mvmn op0, op1, op2  (selects op1 where mask=0)
;;
;; The pattern ((a ^ b) & mask) ^ a is equivalent to (~mask & a) | (mask & b)
;; The pattern ((a ^ b) & mask) ^ b is equivalent to (~mask & b) | (mask & a)
(define_insn_and_split "*mvm<mode>_xor"
  [(set (match_operand:PVMVM 0 "register_operand" "=r,r")
	(xor:PVMVM
	  (and:PVMVM
	    (xor:PVMVM (match_operand:PVMVM 1 "register_operand" "0,r")
		       (match_operand:PVMVM 3 "register_operand" "r,0"))
	    (match_operand:PVMVM 2 "register_operand" "r,r"))
	  (match_dup 1)))]
  "TARGET_RVP"
{
  if (!TARGET_64BIT && known_eq (GET_MODE_SIZE (<MODE>mode), 8))
    return "#";
  return which_alternative == 0 ? "mvm\t%0,%3,%2" : "mvmn\t%0,%1,%2";
}
  "&& !TARGET_64BIT && known_eq (GET_MODE_SIZE (<MODE>mode), 8)
   && reload_completed"
  [(set (match_dup 4)
	(xor:SI (and:SI (xor:SI (match_dup 5) (match_dup 7)) (match_dup 6))
		(match_dup 5)))
   (set (match_dup 8)
	(xor:SI (and:SI (xor:SI (match_dup 9) (match_dup 11)) (match_dup 10))
		(match_dup 9)))]
{
  for (unsigned int i = 0; i < 4; ++i)
    {
      operands[i + 4] = gen_lowpart (SImode, operands[i]);
      operands[i + 8] = gen_highpart (SImode, operands[i]);
    }
}
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")
   (set (attr "length")
	(if_then_else (match_test "!TARGET_64BIT
				  && known_eq (GET_MODE_SIZE (<MODE>mode), 8)")
		      (const_int 8) (const_int 4)))])

;; Alternative form where the outer XOR operand is operands[3] instead
;; of operands[1].  This is needed because combine may produce either form
;; depending on which operand of the inner XOR it chooses to commute.
(define_insn_and_split "*mvm<mode>_xor_alt"
  [(set (match_operand:PVMVM 0 "register_operand" "=r,r")
	(xor:PVMVM
	  (and:PVMVM
	    (xor:PVMVM (match_operand:PVMVM 1 "register_operand" "r,0")
		       (match_operand:PVMVM 3 "register_operand" "0,r"))
	    (match_operand:PVMVM 2 "register_operand" "r,r"))
	  (match_dup 3)))]
  "TARGET_RVP"
{
  if (!TARGET_64BIT && known_eq (GET_MODE_SIZE (<MODE>mode), 8))
    return "#";
  return which_alternative == 0 ? "mvm\t%0,%1,%2" : "mvmn\t%0,%3,%2";
}
  "&& !TARGET_64BIT && known_eq (GET_MODE_SIZE (<MODE>mode), 8)
   && reload_completed"
  [(set (match_dup 4)
	(xor:SI (and:SI (xor:SI (match_dup 5) (match_dup 7)) (match_dup 6))
		(match_dup 7)))
   (set (match_dup 8)
	(xor:SI (and:SI (xor:SI (match_dup 9) (match_dup 11)) (match_dup 10))
		(match_dup 11)))]
{
  for (unsigned int i = 0; i < 4; ++i)
    {
      operands[i + 4] = gen_lowpart (SImode, operands[i]);
      operands[i + 8] = gen_highpart (SImode, operands[i]);
    }
}
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")
   (set (attr "length")
	(if_then_else (match_test "!TARGET_64BIT
				  && known_eq (GET_MODE_SIZE (<MODE>mode), 8)")
		      (const_int 8) (const_int 4)))])

;; PSABS: Saturating absolute value for scalar and packed QI/HI modes
(define_insn "ssabs<mode>2"
  [(set (match_operand:QIHI 0 "register_operand" "=r")
	(ss_abs:QIHI (match_operand:QIHI 1 "register_operand" "r")))]
  "TARGET_RVP"
  "psabs.<rvp_width>\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; Packed absolute value with wrapping semantics (pabs is the pseudo
;; pabd.<w> rs1, x0).  ABS_EXPR on the packed modes must not map to the
;; saturating psabs.  Also covers the scalar QI/HI modes, where a single
;; pabd.<w> rs1, x0 computes the absolute value.  The 8-byte modes are
;; register pairs on RV32.
(define_insn "abs<mode>2"
  [(set (match_operand:QIH_PABD 0 "register_operand" "=r")
	(abs:QIH_PABD (match_operand:QIH_PABD 1 "register_operand" "r")))]
  "TARGET_RVP"
{
  if (!TARGET_64BIT
      && (<MODE>mode == PV8QImode || <MODE>mode == PV4HImode))
    return "pabd.d<rvp_width>\t%0,%1,x0";
  return "pabd.<rvp_width>\t%0,%1,x0";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; Complex addition with the second input rotated by 90 or 270 degrees.
;; PAS subtracts the odd second-input lane from the even first-input lane
;; and adds the even second-input lane to the odd first-input lane.  PSA
;; reverses the add/subtract operations.  Reuse the intrinsic patterns,
;; including their register-pair constraints on RV32.
(define_expand "cadd<rvp_cadd_rot><mode>3"
  [(set (match_operand:RVP_CADD 0 "register_operand")
	(unspec:RVP_CADD
	  [(match_operand:RVP_CADD 1 "register_operand")
	   (match_operand:RVP_CADD 2 "register_operand")]
	  RVP_CADD_OP))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN")

;; SRARI rounds without wrapping the intermediate biased sum.  Do not
;; match an arbitrary PLUS followed by ASHIFTRT: the RTL addition can wrap.
;; Shifting at least once before adding one provides headroom, including
;; at the signed endpoints, so the complete expression below is safe.

;; Preserve bounded-input cases when combine can prove headroom.  Use a
;; split to record that proof in the intrinsic's UNSPEC: register range
;; information is not available to ordinary insn conditions after reload.
(define_split
  [(set (match_operand:X 0 "register_operand")
	(ashiftrt:X
	  (plus:X (match_operand:X 1 "register_operand")
		  (match_operand 2 "const_int_operand"))
	  (match_operand 3 "const_int_operand")))]
  "TARGET_RVP && can_create_pseudo_p ()
   && IN_RANGE (INTVAL (operands[3]), 1, GET_MODE_BITSIZE (<MODE>mode) - 1)
   && INTVAL (operands[2]) == (HOST_WIDE_INT_1 << (INTVAL (operands[3]) - 1))
   && num_sign_bit_copies (operands[1], <MODE>mode) > 1"
  [(const_int 0)]
{
  rtx shift = GEN_INT (-INTVAL (operands[3]));
  emit_insn (TARGET_64BIT
	     ? gen_riscv_shar_i64_insn (operands[0], operands[1], shift)
	     : gen_riscv_sshar_i32_insn (operands[0], operands[1], shift));
  DONE;
})

(define_insn "*rvp_round_ashr<mode>"
  [(set (match_operand:X 0 "register_operand" "=r")
	(ashiftrt:X
	  (plus:X
	    (ashiftrt:X (match_operand:X 1 "register_operand" "r")
		       (match_operand 2 "const_int_operand" "n"))
	    (const_int 1))
	  (const_int 1)))]
  "TARGET_RVP
   && IN_RANGE (INTVAL (operands[2]), 1, GET_MODE_BITSIZE (<MODE>mode) - 2)"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "srari\t%0,%1,%2";
}
  [(set_attr "type" "shift")
   (set_attr "mode" "<MODE>")])

;; On RV64, combine can represent a rounded SI shift using the high word
;; of a shifted DI value.  Only a proven sign-extended SI input allows the
;; word addition to be replaced by XLEN-wide rounding without overflow.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(ashiftrt:DI
	  (plus:DI
	    (and:DI
	      (ashift:DI (match_operand:DI 1 "register_operand")
			 (match_operand 2 "const_int_operand"))
	      (const_int -4294967296))
	    (const_int 4294967296))
	  (const_int 33)))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()
   && IN_RANGE (INTVAL (operands[2]), 2, 31)
   && num_sign_bit_copies (operands[1], DImode) >= 33"
  [(const_int 0)]
{
  emit_insn (gen_riscv_shar_i64_insn
	     (operands[0], operands[1], GEN_INT (INTVAL (operands[2]) - 33)));
  DONE;
})

;; A one-bit rounded shift uses the low bit directly.  Adding it after
;; the shift is safe even when the original value is the largest integer.
;; RV64 word arithmetic can use an extracted word for the quotient.  It
;; agrees with an arithmetic shift only when the DI input is sign-extended
;; from SI.  Record that proof before register allocation loses the range.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(sign_extend:DI
	  (plus:SI
	    (match_operator:SI 4 "subreg_lowpart_operator"
	      [(and:DI (match_operand:DI 1 "register_operand") (const_int 1))])
	    (match_operator:SI 5 "subreg_lowpart_operator"
	      [(zero_extract:DI (match_dup 1)
				(const_int 32) (const_int 1))]))))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()
   && num_sign_bit_copies (operands[1], DImode) >= 33"
  [(const_int 0)]
{
  emit_insn (gen_riscv_shar_i64_insn (operands[0], operands[1], constm1_rtx));
  DONE;
})

;; The commuted word form occurs in scalar loop fallbacks.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(sign_extend:DI
	  (plus:SI
	    (match_operator:SI 4 "subreg_lowpart_operator"
	      [(zero_extract:DI (match_operand:DI 1 "register_operand")
				(const_int 32) (const_int 1))])
	    (match_operator:SI 5 "subreg_lowpart_operator"
	      [(and:DI (match_dup 1) (const_int 1))]))))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()
   && num_sign_bit_copies (operands[1], DImode) >= 33"
  [(const_int 0)]
{
  emit_insn (gen_riscv_shar_i64_insn (operands[0], operands[1], constm1_rtx));
  DONE;
})

;; A genuine SI arithmetic shift also permits unknown upper input bits.
;; Sign-extend the low word before the XLEN-wide rounding operation.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(sign_extend:DI
	  (plus:SI
	    (ashiftrt:SI
	      (match_operator:SI 4 "subreg_lowpart_operator"
		[(match_operand:DI 1 "register_operand")])
	      (const_int 1))
	    (match_operator:SI 5 "subreg_lowpart_operator"
	      [(and:DI (match_dup 1) (const_int 1))]))))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()"
  [(const_int 0)]
{
  rtx input = gen_reg_rtx (DImode);
  emit_insn (gen_extendsidi2 (input, gen_lowpart (SImode, operands[1])));
  emit_insn (gen_riscv_shar_i64_insn (operands[0], input, constm1_rtx));
  DONE;
})

;; After shifting by at least 33, adding the extracted rounding bit still
;; fits in SI.  A 32-bit shift is not enough: rounding INT64_MAX would
;; produce 2^31, whose word truncation must retain its negative SI value.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(sign_extend:DI
	  (plus:SI
	    (match_operator:SI 4 "subreg_lowpart_operator"
	      [(zero_extract:DI (match_operand:DI 1 "register_operand")
				(const_int 1)
				(match_operand 2 "const_int_operand"))])
	    (match_operator:SI 5 "subreg_lowpart_operator"
	      [(ashiftrt:DI (match_dup 1)
			    (match_operand 3 "const_int_operand"))]))))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()
   && IN_RANGE (INTVAL (operands[3]), 33, 63)
   && INTVAL (operands[2]) == INTVAL (operands[3]) - 1"
  [(const_int 0)]
{
  emit_insn (gen_riscv_shar_i64_insn
	     (operands[0], operands[1], GEN_INT (-INTVAL (operands[3]))));
  DONE;
})

;; Combine can put the quotient first when it schedules the two shifts
;; in the opposite order.  Preserve the same word-range restriction.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(sign_extend:DI
	  (plus:SI
	    (match_operator:SI 4 "subreg_lowpart_operator"
	      [(ashiftrt:DI (match_operand:DI 1 "register_operand")
			    (match_operand 3 "const_int_operand"))])
	    (match_operator:SI 5 "subreg_lowpart_operator"
	      [(zero_extract:DI (match_dup 1) (const_int 1)
				(match_operand 2 "const_int_operand"))]))))]
  "TARGET_RVP && TARGET_64BIT && can_create_pseudo_p ()
   && IN_RANGE (INTVAL (operands[3]), 33, 63)
   && INTVAL (operands[2]) == INTVAL (operands[3]) - 1"
  [(const_int 0)]
{
  emit_insn (gen_riscv_shar_i64_insn
	     (operands[0], operands[1], GEN_INT (-INTVAL (operands[3]))));
  DONE;
})

(define_insn "*rvp_round_ashr<mode>_one"
  [(set (match_operand:X 0 "register_operand" "=r")
	(plus:X
	  (and:X (match_operand:X 1 "register_operand" "r") (const_int 1))
	  (ashiftrt:X (match_dup 1) (const_int 1))))]
  "TARGET_RVP"
  "srari\t%0,%1,1"
  [(set_attr "type" "shift")
   (set_attr "mode" "<MODE>")])

;; Packed forms of the same overflow-free identities.  Reuse the intrinsic
;; expanders so that RV32 register-pair constraints remain in one place.
(define_split
  [(set (match_operand:RVP_ROUND 0 "register_operand")
	(ashiftrt:RVP_ROUND
	  (plus:RVP_ROUND
	    (ashiftrt:RVP_ROUND
	      (match_operand:RVP_ROUND 1 "register_operand")
	      (match_operand 2 "const_int_operand"))
	    (match_operand:RVP_ROUND 3 "const_1_operand"))
	  (const_int 1)))]
  "TARGET_RVP && can_create_pseudo_p ()
   && IN_RANGE (INTVAL (operands[2]), 1,
		GET_MODE_UNIT_BITSIZE (<MODE>mode) - 2)"
  [(const_int 0)]
{
  emit_insn (gen_<rvp_round_insn>
	     (operands[0], operands[1], GEN_INT (-INTVAL (operands[2]) - 1)));
  DONE;
})

(define_split
  [(set (match_operand:RVP_ROUND 0 "register_operand")
	(plus:RVP_ROUND
	  (and:RVP_ROUND (match_operand:RVP_ROUND 1 "register_operand")
			(match_operand:RVP_ROUND 2 "const_1_operand"))
	  (ashiftrt:RVP_ROUND (match_dup 1) (const_int 1))))]
  "TARGET_RVP && can_create_pseudo_p ()"
  [(const_int 0)]
{
  emit_insn (gen_<rvp_round_insn> (operands[0], operands[1], constm1_rtx));
  DONE;
})

;; PABD - Packed Absolute Difference
;; pabd.b/h rd, rs1, rs2: rd[i] = |rs1[i] - rs2[i]| (signed)
;; pabdu.b/h rd, rs1, rs2: rd[i] = |rs1[i] - rs2[i]| (unsigned)
;;
;; RTL: (minus (smax a b) (smin a b)) for signed
;;      (minus (umax a b) (umin a b)) for unsigned

(define_insn "<abd_optab><mode>3"
  [(set (match_operand:PV32 0 "register_operand" "=r")
	(minus:PV32
	  (abd_maxop:PV32 (match_operand:PV32 1 "register_operand" "r")
			    (match_operand:PV32 2 "register_operand" "r"))
	  (<abd_minop>:PV32 (match_dup 1) (match_dup 2))))]
  "TARGET_RVP"
  "<abd_insn>.<rvp_width>\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

(define_insn "<abd_optab><mode>3"
  [(set (match_operand:PV64QH 0 "register_operand" "=r")
	(minus:PV64QH
	  (abd_maxop:PV64QH (match_operand:PV64QH 1 "register_operand" "r")
			    (match_operand:PV64QH 2 "register_operand" "r"))
	  (<abd_minop>:PV64QH (match_dup 1) (match_dup 2))))]
  "TARGET_RVP"
  {
    if (TARGET_64BIT)
      return "<abd_insn>.<rvp_width>\t%0,%1,%2";
    else
      return "<abd_insn>.<rvp_dwidth>\t%0,%1,%2";
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;;==========================================================================
;; WMACC(U) - Widening signed(unsigned) multuply-addition
;;==========================================================================
;; rd = rd + <u>signed(X[rs1]) * <u>signed(X[rs2])

(define_expand "<u>maddsidi4"
  [(set (match_operand:DI 0 "register_operand" "=r")
         (plus:DI
          (mult:DI (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
                   (any_extend:DI (match_operand:SI 2 "register_operand" "r")))
          (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && (TARGET_64BIT || !TARGET_BIG_ENDIAN)"
)

(define_insn "*rvp_widen_<u>maddsidi4"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI
          (mult:DI (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
                   (any_extend:DI (match_operand:SI 2 "register_operand" "r")))
          (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "wmacc<u>\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*sumaddsidi4"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI
          (mult:DI (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))
                   (sign_extend:DI (match_operand:SI 1 "register_operand" "r")))
          (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "wmaccsu\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; ABS - Absolute Value for SI/DI modes
;; abs rd, rs1: rd = (rs1 < 0) ? -rs1 : rs1
;;
;; Note: for the most negative representable value, ABS leaves the
;; operand unchanged, matching the usual two's complement expansion
;; (shift + xor + sub) and C's undefined behavior for abs(INT_MIN)
;; and llabs(LLONG_MIN).

(define_insn "abs<GPR:mode>2"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(abs:GPR (match_operand:GPR 1 "register_operand" "r")))]
  "TARGET_RVP"
{
  return TARGET_64BIT && <GPR:MODE>mode == SImode
    ? "absw\t%0,%1" : "abs\t%0,%1";
}
  [(set_attr "type" "arith")
   (set_attr "mode" "<GPR:MODE>")])

;; Inputs have been proven unsigned halfwords.  Keep full-word operands
;; in the UNSPEC so later passes retain the required zero extensions.
;; The scalar result remains visibly zero-extended from a halfword.
(define_insn "riscv_p_scalar_uabdhi<mode>"
  [(set (match_operand:X 0 "register_operand" "=r")
	(zero_extend:X
	  (unspec:HI [(match_operand:X 1 "register_operand" "r")
		      (match_operand:X 2 "register_operand" "r")]
		     UNSPEC_RVP_SCALAR_UABDHI)))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
  "pabdu.h\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; If both native inputs are unsigned bytes, only the low byte contributes
;; to PABDSUMAU.B.  Its XLEN-wide accumulation then implements the scalar
;; addition, including wrapping at the native word width.  Record the
;; range proof before it is lost, and leave the accumulator tie to register
;; allocation rather than requiring identical pseudos here.
(define_split
  [(set (match_operand:X 0 "register_operand")
	(plus:X
	  (zero_extend:X
	    (unspec:HI [(match_operand:X 1 "register_operand")
			(match_operand:X 2 "register_operand")]
		       UNSPEC_RVP_SCALAR_UABDHI))
	  (match_operand:X 3 "register_operand")))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && can_create_pseudo_p ()
   && (nonzero_bits (operands[1], <MODE>mode) & ~HOST_WIDE_INT_UC (255)) == 0
   && (nonzero_bits (operands[2], <MODE>mode) & ~HOST_WIDE_INT_UC (255)) == 0"
  [(const_int 0)]
{
  emit_insn (gen_riscv_p_scalar_uabdaqi<mode> (operands[0], operands[1],
					    operands[2], operands[3]));
  DONE;
})

;; The complete input registers have been proven to contain unsigned bytes.
;; Retain their native modes so later passes preserve the zero upper lanes.
(define_insn "riscv_p_scalar_uabdaqi<mode>"
  [(set (match_operand:X 0 "register_operand" "=r")
	(unspec:X [(match_operand:X 1 "register_operand" "r")
		   (match_operand:X 2 "register_operand" "r")
		   (match_operand:X 3 "register_operand" "0")]
		  UNSPEC_RVP_SCALAR_UABDAQI))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
  "pabdsumau.b\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; A scalar difference of two unsigned halfwords fits in a signed word.
;; Record the range proof in a packed operation while combine still has
;; register bit information.  The other halfword lanes are explicitly zero.
(define_split
  [(set (match_operand:GPR 0 "register_operand")
	(abs:GPR
	  (minus:GPR (match_operand:GPR 1 "register_operand")
		     (match_operand:GPR 2 "register_operand"))))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN && can_create_pseudo_p ()
   && (nonzero_bits (operands[1], <MODE>mode) & ~HOST_WIDE_INT_UC (65535)) == 0
   && (nonzero_bits (operands[2], <MODE>mode) & ~HOST_WIDE_INT_UC (65535)) == 0"
  [(const_int 0)]
{
  riscv_p_expand_scalar_uabd (operands[0], operands[1], operands[2]);
  DONE;
})

;; Include the RV64 word-result extension in the replacement.  A separate
;; word result would hide its range and retain an unnecessary SEXT.W.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(sign_extend:DI
	  (abs:SI
	    (minus:SI (match_operand:SI 1 "register_operand")
		      (match_operand:SI 2 "register_operand")))))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN && can_create_pseudo_p ()
   && (nonzero_bits (operands[1], SImode) & ~HOST_WIDE_INT_UC (65535)) == 0
   && (nonzero_bits (operands[2], SImode) & ~HOST_WIDE_INT_UC (65535)) == 0"
  [(const_int 0)]
{
  riscv_p_expand_scalar_uabd (operands[0], operands[1], operands[2]);
  DONE;
})

;; ABSW - Absolute Value Word (RV64 only)
;; absw rd, rs1: rd = sext.w(abs(rs1[31:0]))
;;
;; For the most negative 32-bit value (0x80000000), the result is
;; also 0x80000000 after abs and sign-extension, as defined by the
;; base P-extension specification.
(define_insn "*absw"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI (abs:SI (match_operand:SI 1 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT"
  "absw\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; Packed sign-extension

;; Widen all consecutive lanes, not just the low part of each wide lane.
(define_expand "<extension><rvp_narrow><rvp_ext_mode>2"
  [(set (match_operand:RVP_DWIDTH_EXT 0 "register_operand")
	(any_extend:RVP_DWIDTH_EXT
	  (match_operand:<HALFMODE> 1 "register_operand")))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_extend (operands[0], operands[1], <CODE> == ZERO_EXTEND);
  DONE;
})

(define_expand "vec_unpack<su>_lo_<mode>"
  [(match_operand:<rvp_unpack_mode> 0 "register_operand")
   (match_operand:RVP_UNPACK 1 "register_operand")
   (any_extend (const_int 0))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_unpack (operands[0], operands[1], <CODE> == ZERO_EXTEND,
			 false);
  DONE;
})

(define_expand "vec_unpack<su>_hi_<mode>"
  [(match_operand:<rvp_unpack_mode> 0 "register_operand")
   (match_operand:RVP_UNPACK 1 "register_operand")
   (any_extend (const_int 0))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_unpack (operands[0], operands[1], <CODE> == ZERO_EXTEND,
			 true);
  DONE;
})

(define_expand "vec_pack_trunc_<mode>"
  [(match_operand:<rvp_pack_mode> 0 "register_operand")
   (match_operand:RVP_DWIDTH_EXT 1 "register_operand")
   (match_operand:RVP_DWIDTH_EXT 2 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_pack (operands[0], operands[1], operands[2]);
  DONE;
})

(define_expand "vec_widen_<su>mult_lo_<mode>"
  [(match_operand:<rvp_unpack_mode> 0 "register_operand")
   (match_operand:RVP_UNPACK 1 "register_operand")
   (match_operand:RVP_UNPACK 2 "register_operand")
   (any_extend (const_int 0))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_widen_mult (operands[0], operands[1], operands[2],
			     <CODE> == ZERO_EXTEND, false);
  DONE;
})

(define_expand "vec_widen_<su>mult_hi_<mode>"
  [(match_operand:<rvp_unpack_mode> 0 "register_operand")
   (match_operand:RVP_UNPACK 1 "register_operand")
   (match_operand:RVP_UNPACK 2 "register_operand")
   (any_extend (const_int 0))]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_widen_mult (operands[0], operands[1], operands[2],
			     <CODE> == ZERO_EXTEND, true);
  DONE;
})

(define_expand "reduc_plus_scal_<mode>"
  [(match_operand:<PVALL_ELT> 0 "register_operand")
   (match_operand:PVMOVE 1 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_reduc_plus (operands[0], operands[1]);
  DONE;
})

;; A dot product with ones sums each group of four bytes or two halfwords
;; into a word accumulator.  Keep the modulo-2^32 accumulator semantics.
(define_expand "widen_ssumpv2si<mode>3"
  [(match_operand:PV2SI 0 "register_operand")
   (match_operand:RVP_DOT 1 "register_operand")
   (match_operand:PV2SI 2 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  rtx ones = force_reg (<MODE>mode, CONST1_RTX (<MODE>mode));
  emit_insn (gen_sdot_prodpv2si<mode> (operands[0], operands[1], ones,
				    operands[2]));
  DONE;
})

(define_expand "widen_usumpv2si<mode>3"
  [(match_operand:PV2SI 0 "register_operand")
   (match_operand:RVP_DOT 1 "register_operand")
   (match_operand:PV2SI 2 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  rtx ones = force_reg (<MODE>mode, CONST1_RTX (<MODE>mode));
  emit_insn (gen_udot_prodpv2si<mode> (operands[0], operands[1], ones,
				    operands[2]));
  DONE;
})

;; Each word accumulator receives four byte products or two halfword
;; products, modulo 2^32.  RV32 uses two single-register instructions.
(define_expand "sdot_prodpv2si<mode>"
  [(match_operand:PV2SI 0 "register_operand")
   (match_operand:RVP_DOT 1 "register_operand")
   (match_operand:RVP_DOT 2 "register_operand")
   (match_operand:PV2SI 3 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  emit_insn (gen_riscv_<rvp_dot_signed> (operands[0], operands[3],
				       operands[1], operands[2]));
  DONE;
})

(define_expand "udot_prodpv2si<mode>"
  [(match_operand:PV2SI 0 "register_operand")
   (match_operand:RVP_DOT 1 "register_operand")
   (match_operand:RVP_DOT 2 "register_operand")
   (match_operand:PV2SI 3 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  emit_insn (gen_riscv_<rvp_dot_unsigned> (operands[0], operands[3],
					 operands[1], operands[2]));
  DONE;
})

(define_expand "usdot_prodpv2si<mode>"
  [(match_operand:PV2SI 0 "register_operand")
   (match_operand:RVP_DOT 1 "register_operand")
   (match_operand:RVP_DOT 2 "register_operand")
   (match_operand:PV2SI 3 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  /* The optab takes the unsigned source first; the instruction takes
     it last.  */
  emit_insn (gen_riscv_<rvp_dot_mixed> (operands[0], operands[3],
				      operands[2], operands[1]));
  DONE;
})

;; Byte and halfword differences feed independent word sums or one
;; doubleword sum.  The absolute differences are unsigned in both cases.
(define_expand "usad<RVP_SAD_ACC:mode><RVP_DOT:mode>"
  [(match_operand:RVP_SAD_ACC 0 "register_operand")
   (match_operand:RVP_DOT 1 "register_operand")
   (match_operand:RVP_DOT 2 "register_operand")
   (match_operand:RVP_SAD_ACC 3 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_sad (operands[0], operands[1], operands[2], operands[3], true);
  DONE;
})

(define_expand "ssad<RVP_SAD_ACC:mode><RVP_DOT:mode>"
  [(match_operand:RVP_SAD_ACC 0 "register_operand")
   (match_operand:RVP_DOT 1 "register_operand")
   (match_operand:RVP_DOT 2 "register_operand")
   (match_operand:RVP_SAD_ACC 3 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_sad (operands[0], operands[1], operands[2], operands[3], false);
  DONE;
})

;; Four full halfword products contribute to a doubleword accumulator.
(define_expand "sdot_prodpv1dipv4hi"
  [(match_operand:PV1DI 0 "register_operand")
   (match_operand:PV4HI 1 "register_operand")
   (match_operand:PV4HI 2 "register_operand")
   (match_operand:PV1DI 3 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_dot_product_64 (operands[0], operands[1], operands[2],
				operands[3], false, false);
  DONE;
})

(define_expand "udot_prodpv1dipv4hi"
  [(match_operand:PV1DI 0 "register_operand")
   (match_operand:PV4HI 1 "register_operand")
   (match_operand:PV4HI 2 "register_operand")
   (match_operand:PV1DI 3 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_dot_product_64 (operands[0], operands[1], operands[2],
				operands[3], true, false);
  DONE;
})

(define_expand "usdot_prodpv1dipv4hi"
  [(match_operand:PV1DI 0 "register_operand")
   (match_operand:PV4HI 1 "register_operand")
   (match_operand:PV4HI 2 "register_operand")
   (match_operand:PV1DI 3 "register_operand")]
  "TARGET_RVP && !TARGET_BIG_ENDIAN"
{
  riscv_p_expand_dot_product_64 (operands[0], operands[1], operands[2],
				operands[3], false, true);
  DONE;
})

;; Intermediate rtl pattern for psext.h.b
(define_insn "*psextqihi_1"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
     (vec_concat:PV2HI
       (sign_extend:HI (subreg:QI (match_operand:PV4QI 1 "register_operand" "r") 0))
       (subreg:HI (ashiftrt:SI (match_operand:SI 2 "register_operand" "r")
                               (const_int 24)) 0)))]
  "TARGET_RVP"
  "psext.h.b\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "psextqihi_2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
     (vec_concat:PV2HI
       (sign_extend:HI (subreg:QI (match_operand:PV4QI 1 "register_operand" "r") 0))
       (subreg:HI (sign_extract:SI (subreg:SI (match_dup 1) 0)
                                   (const_int 8)
                                   (const_int 16)) 0)))]
  "TARGET_RVP"
  "psext.h.b\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")]) 

(define_insn_and_split "*intermediate_for_shr_24"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
     (vec_concat:PV2HI
       (match_operand:HI 1 "register_operand" "r")
       (subreg:HI (ashiftrt:SI (match_operand:SI 2 "register_operand" "r")
                               (const_int 24)) 0)))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  /* This pattern concatenates:
     - Lower element: operand 1 (HI)
     - Upper element: top byte of operand 2, sign-extended to HI

     We use: shift right 24 + ppaireo.h to pack them together.
     ppaireo.h takes the lower HI of first operand and upper HI of second operand.
     After srai 24, the top byte is sign-extended in bits [7:0], so we need
     to shift it left by 16 to position it correctly, then use ppaireo.h.

     Actually, simpler: use srai to get top byte, then use scalar packing. */

  rtx temp = gen_reg_rtx (SImode);
  rtx temp_shifted = gen_reg_rtx (SImode);

  /* Shift right by 24 to get top byte (sign-extended) in lower bits */
  emit_insn (gen_ashrsi3 (temp, operands[2], GEN_INT (24)));

  /* Shift left by 16 to position it in upper halfword */
  emit_insn (gen_ashlsi3 (temp_shifted, temp, GEN_INT (16)));

  /* Mask operand1 into the low halfword before packing.  */
  emit_insn (gen_ppaireo_concatpv2hi (operands[0], operands[1], temp_shifted));

  DONE;
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn_and_split "*shiftrt_8_extend"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (ashiftrt:HI (subreg:HI (match_operand:PV4QI 1 "register_operand" "r") 0)
                     (const_int 8)))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  rtx src_si = gen_lowpart (SImode, operands[1]);
  rtx b1_at_top = gen_reg_rtx (SImode);
  rtx tmp = gen_reg_rtx (SImode);

  /* Extract byte 1 (bits [15:8]) and sign-extend it.  */
  emit_insn (gen_ashlsi3 (b1_at_top, src_si, GEN_INT (16)));
  emit_insn (gen_ashrsi3 (tmp, b1_at_top, GEN_INT (24)));
  emit_move_insn (operands[0], gen_lowpart (HImode, tmp));
  
  DONE;
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; Intermediate rtl pattern for pmul.h.b11
(define_insn_and_split "*psextpv4qipv2hi_odd"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (vec_concat:PV2HI (ashiftrt:HI (subreg:HI (match_operand:PV4QI 1 "register_operand" "r")0)
                                       (const_int 8))
                          (subreg:HI (ashiftrt:SI (subreg:SI (match_dup 1)0)
                                       (const_int 24))0)))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(const_int 0)]
{
  /* PV4QI holds four bytes [b0, b1, b2, b3] packed into a 32-bit word.
     The target packs the "odd" byte of each 16-bit lane (b1, b3),
     sign-extended, into PV2HI as {sign_extend (b1), sign_extend (b3)}.

     ppairo.b op1, op1 (same register on both sides) gathers b1 into byte 0
     and b3 into bytes 2 and 3 of a temporary, so psext.h.b (via the
     match_dup byte-2 form) can then sign-extend bytes 0 and 2 directly.  */

  rtx tmp = gen_reg_rtx (PV4QImode);
  emit_insn (gen_ppairob_mergepv4qi (tmp, operands[1], operands[1]));
  emit_insn (gen_psextqihi_2 (operands[0], tmp));

  DONE;
}
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; Intermediate rtl pattern for psext.w.h
(define_insn "*psexthisi_1"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
     (vec_concat:PV2SI
       (sign_extend:SI (subreg:HI (match_operand:PV4HI 1 "register_operand" "r") 0))
       (subreg:SI (ashiftrt:DI (match_operand:DI 2 "register_operand" "r")
                               (const_int 48)) 0)))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.w.h\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*psexthisi_2"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
     (vec_concat:PV2SI
       (sign_extend:SI (subreg:HI (match_operand:PV4HI 1 "register_operand" "r") 0))
       (subreg:SI (sign_extract:DI (subreg:DI (match_dup 1) 0)
                                   (const_int 16)
                                   (const_int 32)) 0)))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.w.h\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; Intermediate rtl pattern for psext.w.b
;; Currently can't combine due to cost model
 (define_insn "*psextqisi_1"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
     (vec_concat:PV2SI
       (sign_extend:SI (subreg:QI (match_operand:PV8QI 1 "register_operand" "r") 0))
       (subreg:SI (ashiftrt:DI (match_operand:DI 2 "register_operand" "r")
                               (const_int 48)) 0)))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.w.b\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*psextqisi_2"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
     (vec_concat:PV2SI
       (match_operand:SI 1 "register_operand" "r")
       (subreg:SI (sign_extract:DI (subreg:DI (match_operand:PV8QI 2 "register_operand" "r") 0)
                                   (const_int 8)
                                   (const_int 32)) 0)))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.w.b\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*psextqisi_3"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
     (vec_concat:PV2SI
       (sign_extend:SI (subreg:QI (match_operand:PV8QI 1 "register_operand" "r") 0))
       (subreg:SI (sign_extract:DI (subreg:DI (match_operand:PV8QI 2 "register_operand" "r") 0)
                                   (const_int 8)
                                   (const_int 32)) 0)))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.w.b\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; =========================================================================
;; PSH1ADD.H/W/DH/DW: Packed Shift-left-by-1 and Add
;; =========================================================================
;; psh1add.h  rd, rs1, rs2: rd[i] = (rs1[i] << 1) + rs2[i]  (16-bit, PV2HI)
;; psh1add.h  rd, rs1, rs2: rd[i] = (rs1[i] << 1) + rs2[i]  (16-bit, PV4HI, RV64)
;; psh1add.dh rd, rs1, rs2: rd[i] = (rs1[i] << 1) + rs2[i]  (16-bit, PV4HI, RV32)
;; psh1add.w  rd, rs1, rs2: rd[i] = (rs1[i] << 1) + rs2[i]  (32-bit, PV2SI, RV64)
;; psh1add.dw rd, rs1, rs2: rd[i] = (rs1[i] << 1) + rs2[i]  (32-bit, PV2SI, RV32)
;;
;; RTL: (plus (ashift rs1 1) rs2)

;; 4-byte halfword: PV2HI, single register on both RV32 and RV64
(define_insn "*psh1add<mode>3"
  [(set (match_operand:PVHIW 0 "register_operand" "=r")
	(plus:PVHIW
	  (ashift:PVHIW (match_operand:PVHIW 1 "register_operand" "r")
			(const_int 1))
	  (match_operand:PVHIW 2 "register_operand" "r")))]
  "TARGET_RVP"
  "psh1add.<rvp_width>\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; 8-byte halfword/word: PV4HI and PV2SI
;; RV64: single register, uses B/H/W suffix
;; RV32: register pair, uses DH/DW suffix
(define_insn "*psh1add<mode>3"
  [(set (match_operand:PVHW 0 "register_operand" "=r")
	(plus:PVHW
	  (ashift:PVHW (match_operand:PVHW 1 "register_operand" "r")
		       (const_int 1))
	  (match_operand:PVHW 2 "register_operand" "r")))]
  "TARGET_RVP"
  "psh1add.%d0\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; Fold a seeded word reduction modulo 2^32.
;; PREDSUM computes a native sum; truncate only after adding the seed.
(define_split
  [(set (match_operand:DI 0 "register_operand")
	(sign_extend:DI
	  (plus:SI
	    (plus:SI
	      (subreg:SI
		(any_extract:DI (match_operand:DI 1 "register_operand")
				(const_int 32) (const_int 32)) 0)
	      (match_operand:SI 2 "register_operand"))
	    (match_operand:SI 3 "register_operand"))))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN
   && can_create_pseudo_p ()
   && (rtx_equal_p (gen_lowpart (SImode, operands[1]), operands[2])
       || rtx_equal_p (gen_lowpart (SImode, operands[1]), operands[3]))"
  [(set (match_dup 4)
	(unspec:DI [(match_dup 5) (match_dup 6)] UNSPEC_PREDSUM))
   (set (match_dup 0) (sign_extend:DI (subreg:SI (match_dup 4) 0)))]
{
  operands[4] = gen_reg_rtx (DImode);
  operands[5] = gen_lowpart (PV2SImode, operands[1]);
  /* Only the low seed word contributes to the truncated result.  */
  rtx seed = rtx_equal_p (gen_lowpart (SImode, operands[1]), operands[2])
	     ? operands[3] : operands[2];
  operands[6] = gen_lowpart (DImode, seed);
})

;; Combine a widening conversion followed by a horizontal sum.  SLP can
;; introduce this form instead of the scalar lane extractions below.
(define_insn "*rvp_reduc_widen_pv2hi<u>"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI
	  (subreg:SI
	    (any_extend:PV2SI
	      (match_operand:PV2HI 1 "register_operand" "r")) 0)
	  (subreg:SI
	    (any_extend:PV2SI (match_dup 1)) 4)))]
  "TARGET_RVP && !TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "predsum<u>.hs\t%0,%1,zero"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; Reduction sum
(define_insn_and_split "*reduc_sum_inter_rtl"
  [(set (match_operand:SI 0 "register_operand" "=r")
     (plus:SI (ashiftrt:SI (subreg:SI (match_operand:PV2HI 1 "register_operand" "r") 0)
                           (const_int 16))
              (match_operand:SI 2 "register_operand" "r")))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()"
  "#"
  "&& 1"
  [(set (match_dup 3)
        (ashiftrt:SI (subreg:SI (match_dup 1) 0) (const_int 16)))
   (set (match_dup 0)
        (plus:SI (match_dup 3) (match_dup 2)))]
  "operands[3] = gen_reg_rtx (SImode);"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*predsum_h_pv2hi_zero"
  [(set (match_operand:SI 0 "register_operand" "=r")
     (plus:SI (ashiftrt:SI (subreg:SI (match_operand:PV2HI 1 "register_operand" "r") 0)
                           (const_int 16))
              (sign_extend:SI (subreg:HI (match_dup 1) 0))))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsum.hs\t%0, %1, zero"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*predsum_h_pv2hi"
  [(set (match_operand:SI 0 "register_operand" "=r")
     (plus:SI     
       (plus:SI (ashiftrt:SI (subreg:SI (match_operand:PV2HI 1 "register_operand" "r") 0)
                             (const_int 16))
                (sign_extend:SI (subreg:HI (match_dup 1) 0)))
       (match_operand:SI 2 "register_operand" "r")))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsum.hs\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*predsumu_h_pv2hi_zero"
  [(set (match_operand:SI 0 "register_operand" "=r")
     (plus:SI (lshiftrt:SI (subreg:SI (match_operand:PV2HI 1 "register_operand" "r") 0)
                           (const_int 16))
              (zero_extend:SI (subreg:HI (match_dup 1) 0))))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsumu.hs\t%0, %1, zero"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "*predsumu_h_pv2hi"
  [(set (match_operand:SI 0 "register_operand" "=r")
     (plus:SI     
       (plus:SI (lshiftrt:SI (subreg:SI (match_operand:PV2HI 1 "register_operand" "r") 0)
                             (const_int 16))
                (zero_extend:SI (subreg:HI (match_dup 1) 0)))
       (match_operand:SI 2 "register_operand" "r")))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsumu.hs\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; RV32 narrowing shifts pack the low half of each shifted lane without
;; rounding or saturation.  RV64 has no corresponding immediate form.
(define_insn "*rvp_narrow_<optab>_<mode>"
  [(set (match_operand:<rvp_narrow_mode> 0 "register_operand" "=r")
	(truncate:<rvp_narrow_mode>
	  (any_shiftrt:RVP_DWIDTH_EXT
	    (match_operand:RVP_DWIDTH_EXT 1 "register_operand" "r")
	    (match_operand 2 "const_int_operand" "n"))))]
  "TARGET_RVP && !TARGET_64BIT
   && IN_RANGE (INTVAL (operands[2]), 1, <rvp_narrow_shmax>)"
  "pn<insn>i.<rvp_extend_width>\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])
