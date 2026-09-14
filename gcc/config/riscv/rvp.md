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

;; Binary Arithmetic Operations

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
  "TARGET_RVP && !TARGET_64BIT"
  "#"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

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

;; Split PV4HI multiplication into element-wise multiplications using mul.h00/mul.h11
;; when the pattern cannot be combined into more efficient forms (like PWMUL).
;; On RV32, PV4HI uses register pairs where each 32-bit word contains TWO packed
;; 16-bit elements. We use mul.h00 and mul.h11 to multiply individual elements,
;; then pack the results using shift and OR.
(define_split
  [(set (match_operand:PV4HI 0 "register_operand")
        (mult:PV4HI (match_operand:PV4HI 1 "register_operand")
                    (match_operand:PV4HI 2 "register_operand")))]
  "TARGET_RVP && !TARGET_64BIT && can_create_pseudo_p ()"
  [(const_int 0)]
{
  rtx dest_lo = riscv_subword (operands[0], false);
  rtx dest_hi = riscv_subword (operands[0], true);
  rtx src1_lo = riscv_subword (operands[1], false);
  rtx src1_hi = riscv_subword (operands[1], true);
  rtx src2_lo = riscv_subword (operands[2], false);
  rtx src2_hi = riscv_subword (operands[2], true);

  /* Each 32-bit word contains two 16-bit elements [e0, e1] or [e2, e3].
     mul.h00 multiplies lower 16-bit elements: result in lower 16 bits
     mul.h11 multiplies upper 16-bit elements: result in lower 16 bits
     We pack them: (mul.h11 << 16) | (mul.h00 & 0xFFFF) */

  /* Process lower word: elements [0] and [1] */
  rtx temp_e0 = gen_reg_rtx (SImode);  /* element 0 result */
  rtx temp_e1 = gen_reg_rtx (SImode);  /* element 1 result */
  rtx temp_e1_shifted = gen_reg_rtx (SImode);
  rtx temp_e0_masked = gen_reg_rtx (SImode);

  /* mul_h00 expects HImode operands: extract lower 16 bits as HImode */
  rtx src1_lo_hi = gen_lowpart (HImode, src1_lo);
  rtx src2_lo_hi = gen_lowpart (HImode, src2_lo);

  emit_insn (gen_mulhisi3 (temp_e0, src1_lo_hi, src2_lo_hi));
  emit_insn (gen_mul_h11 (temp_e1, src1_lo, src2_lo));
  emit_insn (gen_ashlsi3 (temp_e1_shifted, temp_e1, GEN_INT (16)));
  emit_insn (gen_andsi3 (temp_e0_masked, temp_e0, GEN_INT (0xFFFF)));
  emit_insn (gen_iorsi3 (dest_lo, temp_e1_shifted, temp_e0_masked));

  /* Process upper word: elements [2] and [3] */
  rtx temp_e2 = gen_reg_rtx (SImode);  /* element 2 result */
  rtx temp_e3 = gen_reg_rtx (SImode);  /* element 3 result */
  rtx temp_e3_shifted = gen_reg_rtx (SImode);
  rtx temp_e2_masked = gen_reg_rtx (SImode);

  /* mul_h00 expects HImode operands: extract lower 16 bits as HImode */
  rtx src1_hi_hi = gen_lowpart (HImode, src1_hi);
  rtx src2_hi_hi = gen_lowpart (HImode, src2_hi);

  emit_insn (gen_mulhisi3 (temp_e2, src1_hi_hi, src2_hi_hi));
  emit_insn (gen_mul_h11 (temp_e3, src1_hi, src2_hi));
  emit_insn (gen_ashlsi3 (temp_e3_shifted, temp_e3, GEN_INT (16)));
  emit_insn (gen_andsi3 (temp_e2_masked, temp_e2, GEN_INT (0xFFFF)));
  emit_insn (gen_iorsi3 (dest_hi, temp_e3_shifted, temp_e2_masked));

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

(define_insn "*pwmulsu<rvp_narrow>3"
  [(set (match_operand:PVHW 0 "register_operand" "=r")
        (mult:PVHW (zero_extend:PVHW (match_operand:<HALFMODE> 1 "register_operand" "r"))
                   (sign_extend:PVHW (match_operand:<HALFMODE> 2 "register_operand" "r"))))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmulsu.<rvp_extend_width>\t%0, %2, %1"
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

(define_insn "*pwmaccsupv2hi3"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (plus:PV2SI (mult:PV2SI (zero_extend:PV2SI (match_operand:PV2HI 1 "register_operand" "r"))
                                (sign_extend:PV2SI (match_operand:PV2HI 2 "register_operand" "r")))
                    (match_operand:PV2SI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmaccsu.h\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

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

;; 4-byte packed vector shift (PV4QI/PV2HI, RV32 and RV64)
(define_insn "v<rvp_shift_optab><mode>3"
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
(define_insn "v<rvp_shift_optab><mode>3"
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
  "TARGET_RVP && !TARGET_64BIT"
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
  "TARGET_RVP && !TARGET_64BIT"
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
  "TARGET_RVP && !TARGET_64BIT"
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
  "TARGET_RVP && !TARGET_64BIT"
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
  "TARGET_RVP && !TARGET_64BIT"
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
  "TARGET_RVP && !TARGET_64BIT"
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
  "TARGET_RVP && !TARGET_64BIT"
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
  "TARGET_RVP && !TARGET_64BIT"
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
  "TARGET_RVP && !TARGET_64BIT"
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
  "TARGET_RVP && !TARGET_64BIT"
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
  "TARGET_RVP && !TARGET_64BIT"
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

;; Averaging arithmetic operations with standard optab names.
;;
;; GCC's tree-vect-patterns.cc recognizes widening average patterns like:
;;   (int8_t)(((int16_t)a + (int16_t)b) >> 1)
;; and lowers them to IFN_AVG_FLOOR/IFN_AVG_SUB_FLOOR, which map to
;; avg<mode>3_floor/avg_sub<mode>3_floor optabs.
;;
;; P-extension averaging instructions:
;;   paadd/paaddu: signed/unsigned averaging add: (a + b) >> 1
;;   pasub/pasubu: signed/unsigned averaging subtract: (a - b) >> 1
;;
;; These instructions perform overflow-free averaging in hardware by
;; widening operands internally before the add/subtract.
;;
;; Note: The RTL pattern uses (plus:PVALL ...) which has wraparound
;; semantics at element boundaries. However, this correctly models the
;; hardware behavior because paadd/paaddu internally widen operands
;; before addition, avoiding overflow.

;; Signed averaging: avg<mode>3_floor -> paadd, avg_sub<mode>3_floor -> pasub
(define_insn "<savg_optab><mode>3_floor"
  [(set (match_operand:PVALL 0 "register_operand" "=r")
	(ashiftrt:PVALL
	  (avg_op:PVALL (match_operand:PVALL 1 "register_operand" "r")
			(match_operand:PVALL 2 "register_operand" "r"))
	  (const_int 1)))]
  "TARGET_RVP"
  "<avg_insn>.<rvp_width>\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; Unsigned averaging: uavg<mode>3_floor -> paaddu, uavg_sub<mode>3_floor -> pasubu
(define_insn "<uavg_optab><mode>3_floor"
  [(set (match_operand:PVALL 0 "register_operand" "=r")
	(lshiftrt:PVALL
	  (avg_op:PVALL (match_operand:PVALL 1 "register_operand" "r")
			(match_operand:PVALL 2 "register_operand" "r"))
	  (const_int 1)))]
  "TARGET_RVP"
  "<avg_insn>u.<rvp_width>\t%0,%1,%2"
  [(set_attr "type" "arith")
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

;; Bitwise operations for 4-byte vector modes (always single register)
(define_insn "<optab><mode>3"
  [(set (match_operand:PV32 0 "register_operand" "=r")
	(any_bitwise:PV32 (match_operand:PV32 1 "register_operand" "r")
			  (match_operand:PV32 2 "register_operand" "r")))]
  "TARGET_RVP"
  "<insn>\t%0,%1,%2"
  [(set_attr "type" "logical")
   (set_attr "mode" "<MODE>")])

;; Bitwise operations for 8-byte vectors on RV64 (single register instruction).
(define_insn "<optab><mode>3"
  [(set (match_operand:PV64 0 "register_operand" "=r")
	(any_bitwise:PV64 (match_operand:PV64 1 "register_operand" "r")
			  (match_operand:PV64 2 "register_operand" "r")))]
  "TARGET_RVP && TARGET_64BIT"
  "<insn>\t%0,%1,%2"
  [(set_attr "type" "logical")
   (set_attr "mode" "<MODE>")])

;; Bitwise operations for 8-byte vectors on RV32 (register pair).
;; Use early-clobber (=&r) to prevent the RA from assigning the destination
;; pair to overlap with either source pair in a crossed fashion, which would
;; cause wrong-code when the split fires after reload.
(define_insn_and_split "<optab><mode>3_rv32"
  [(set (match_operand:PV64 0 "register_operand" "=&r")
	(any_bitwise:PV64 (match_operand:PV64 1 "register_operand" "r")
			  (match_operand:PV64 2 "register_operand" "r")))]
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

;; Pack operations for scalar mode
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
  "@
   ppaireo.h\t%0, %1, %2
   ppaire.h\t%0, %2, %1"
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
  "@
   ppaireo.w\t%0, %1, %2
   pack\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Concatenate two halfwords into a PV2HI vector.  PPAIRE.H packs the low
;; halfword of each operand into a 32-bit word, which is what is needed for
;; both RV32 and RV64; on RV64 a plain PACK would instead concatenate the
;; full 32-bit halves and produce a wrong result.  On RV32 PPAIRE.H is an
;; alias of PACK, so this is also correct there.
(define_insn "ppaire_concatpv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (vec_concat:PV2HI
          (match_operand:HI 1 "register_operand" "r") 
          (match_operand:HI 2 "register_operand" "r")))]
  "TARGET_RVP"
  "ppaire.h\t%0, %1, %2"
  [(set_attr "type"  "arith")
   (set_attr "mode"  "SI")])

(define_insn "*pack_concatpv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (vec_concat:PV2SI
          (match_operand:SI 1 "register_operand" "r") 
          (match_operand:SI 2 "register_operand" "r")))]
  "TARGET_RVP && TARGET_64BIT"
  "pack\t%0, %1, %2"
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
  "ppaire.h\t%0, %1, %2"
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
  "ppaireo.h\t%0, %1, %2"
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
  "ppairoe.h\t%0, %1, %2"
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
  "ppairo.h\t%0, %1, %2"
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
  "pack\t%0, %1, %2"
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
  "ppaireo.w\t%0, %1, %2"
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
  "ppairoe.w\t%0, %1, %2"
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
  "ppairo.w\t%0, %1, %2"
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
  "ppaire.b\t%0, %1, %2"
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
  "ppaire.%d0\t%0, %1, %2"
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
  "ppaireo.b\t%0, %1, %2"
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
  "ppaireo.%d0\t%0, %1, %2"
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
  "ppairoe.b\t%0, %1, %2"
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
  "ppairoe.%d0\t%0, %1, %2"
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
  "ppairo.b\t%0, %1, %2"
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
  "ppairo.%d0\t%0, %1, %2"
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
  "ppaire.%d0\t%0, %1, %2"
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
  "ppaireo.%d0\t%0, %1, %2"
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
  "ppairoe.%d0\t%0, %1, %2"
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
  "ppairo.%d0\t%0, %1, %2"
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
  "zip8p\t%0, %1, %2"
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
  "zip8hp\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Byte-granularity zip of two 32-bit vectors into a 64-bit one.  zip8p and
;; wzip8p are the same operation -- both read only the low 32 bits of each
;; source -- and differ only in whether the 64-bit result is one register or an
;; even-odd pair, which the PV8QI mode already expresses.  The PV4QI zip
;; permutes take the low or high half of this result.
(define_insn "riscv_zip8p_pv4qi"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
	(vec_select:PV8QI
	  (vec_concat:PV8QI (match_operand:PV4QI 1 "register_operand" "r")
			    (match_operand:PV4QI 2 "register_operand" "r"))
	  (parallel [(const_int 0) (const_int 4)
		     (const_int 1) (const_int 5)
		     (const_int 2) (const_int 6)
		     (const_int 3) (const_int 7)])))]
  "TARGET_RVP"
  {
    if (TARGET_64BIT)
      return "zip8p\t%0, %1, %2";
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
  "zip16p\t%0, %1, %2"
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
  "zip16hp\t%0, %1, %2"
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
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "unzip8p\t%0, %1, %2"
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
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "unzip8hp\t%0, %1, %2"
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
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "unzip16p\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*unziph_concatpv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (vec_concat:PV4HI
          (vec_select:PV2HI (match_operand:PV4HI 1 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 3)]))
          (vec_select:PV2HI (match_operand:PV4HI 2 "register_operand" "r")
                            (parallel [(const_int 1) (const_int 3)]))))]
  "TARGET_RVP && TARGET_64BIT && !TARGET_BIG_ENDIAN"
  "unzip16hp\t%0, %1, %2"
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
  "!TARGET_64BIT && TARGET_RVP"
  "wadd\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Signed widening sub (WSUB)
;; This pattern matches: (long long)a - (long long)b
(define_insn "*wsubsi3"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (minus:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                  (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP"
  "wsub\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Unsigned widening add (WADDU)
;; This pattern matches: (unsigned long long)a + (unsigned long long)b
(define_insn "*waddusi3"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP"
  "waddu\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Unsigned widening sub (WSUBU)
;; This pattern matches: (unsigned long long)a - (unsigned long long)b
(define_insn "*wsubusi3"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (minus:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                  (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP"
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
  "!TARGET_64BIT && TARGET_RVP"
  "wadda<u>\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; Rtl pattern for wadda(u) when the operand has x0 register.
(define_insn "*<su>extend_add"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (match_operand:DI 2 "register_operand" "0")))]
  "!TARGET_64BIT && TARGET_RVP"
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
  "!TARGET_64BIT && TARGET_RVP"
  "wsuba<u>\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; DI-mode addition for RV32 with RVP
;; Uses ADDD instruction; operands must be register pairs (R constraint)
(define_insn "*adddi3_rvp32"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI (match_operand:DI 1 "register_operand" "R")
                 (match_operand:DI 2 "register_operand" "R")))]
  "!TARGET_64BIT && TARGET_RVP"
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
  "!TARGET_64BIT && TARGET_RVP"
  "subd\t%0, %z1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*negdi2_rvp32_neg"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (neg:DI (match_operand:DI 1 "register_operand" "R")))]
  "!TARGET_64BIT && TARGET_RVP"
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
  "mulsu.h00\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; MULSU.W00
(define_insn "*rvp_mulsu_w00"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT"
  "mulsu.w00\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; widen-multiply for RV32 with RVP
(define_insn "*smulsidi3_rvp"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP"
  "wmul\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*umulsidi3_rvp"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP"
  "wmulu\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*sumulsidi3_rvp"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "!TARGET_64BIT && TARGET_RVP"
  "wmulsu\t%0, %2, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

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
  "pncvt.<rvp_extend_width>\t%0, %1"
  [(set_attr "type" "arith")
   (set (attr "mode") (if_then_else (match_test "TARGET_64BIT")
				     (const_string "DI") (const_string "SI")))])

;; The odd-byte counterpart of PNCVT.B: pnsrli.b rd, rs1_p, 8 on RV32 and
;; unzip8hp rd, rs1, x0 on RV64.  Used by the PV4QI odd unzip permute.
(define_insn "riscv_pncvth_b"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
	(truncate:PV4QI
	  (lshiftrt:PV4HI (match_operand:PV4HI 1 "register_operand" "r")
			  (const_int 8))))]
  "TARGET_RVP"
  "pncvth.b\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; Routes __builtin_convertvector (PV4HI->PV4QI) through truncpv4hipv4qi2 so
;; combine can match the compound clip patterns before the fallback byte-pack
;; split fires.
(define_expand "vec_pack_trunc_pv2hi"
  [(match_operand:PV4QI 0 "register_operand" "")
   (match_operand:PV2HI 1 "register_operand" "")	; lo half
   (match_operand:PV2HI 2 "register_operand" "")]	; hi half
  "TARGET_RVP"
{
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
;; psati.h rd, rs1, N  -- saturate each halfword to [-(1<<N), (1<<N)-1]
;;   N is the immediate; the smin bound is max = 2^N - 1.
;; pusati.h rd, rs1, N -- saturate each halfword to [0, (1<<N)-1]
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
    snprintf (buf, sizeof (buf), "psati.h\t%%0, %%1, %d", riscv_psati_imm (operands[2]));
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
    snprintf (buf, sizeof (buf), "%s\t%%0, %%1, %d", insn, riscv_psati_imm (operands[2]));
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
    snprintf (buf, sizeof (buf), "%s\t%%0, %%1, %d", insn, riscv_psati_imm (operands[2]));
    return buf;
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; PUSATI.H for PV2HI -- unsigned umin form (uint16 input)
(define_insn "*pusati_h_umin_pv2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
	(umin:PV2HI (match_operand:PV2HI 1 "register_operand" "r")
		    (match_operand:PV2HI 2 "immediate_operand")))]
  "TARGET_RVP
   && riscv_pusati_bounds_p (operands[2], 16)"
  {
    static char buf[32];
    snprintf (buf, sizeof (buf), "pusati.h\t%%0, %%1, %d", riscv_psati_imm (operands[2]));
    return buf;
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; PUSATI.H for PV4HI -- unsigned umin form (uint16 input)
(define_insn "*pusati_h_umin_pv4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
	(umin:PV4HI (match_operand:PV4HI 1 "register_operand" "r")
		    (match_operand:PV4HI 2 "immediate_operand")))]
  "TARGET_RVP
   && riscv_pusati_bounds_p (operands[2], 16)"
  {
    static char buf[32];
    const char *insn = TARGET_64BIT ? "pusati.h" : "pusati.dh";
    snprintf (buf, sizeof (buf), "%s\t%%0, %%1, %d", insn, riscv_psati_imm (operands[2]));
    return buf;
  }
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; PUSATI.W for PV2SI -- unsigned umin form (uint32 input)
(define_insn "*pusati_w_umin_pv2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(umin:PV2SI (match_operand:PV2SI 1 "register_operand" "r")
		    (match_operand:PV2SI 2 "immediate_operand")))]
  "TARGET_RVP
   && riscv_pusati_bounds_p (operands[2], 32)"
  {
    static char buf[32];
    const char *insn = TARGET_64BIT ? "pusati.w" : "pusati.dw";
    snprintf (buf, sizeof (buf), "%s\t%%0, %%1, %d", insn, riscv_psati_imm (operands[2]));
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
(define_insn "*mvm<X:mode>"
  [(set (match_operand:X 0 "register_operand" "=r,r")
	(ior:X (and:X (not:X (match_operand:X 2 "register_operand" "r,r"))
		      (match_operand:X 1 "register_operand" "0,r"))
	       (and:X (match_dup 2)
		      (match_operand:X 3 "register_operand" "r,0"))))]
  "TARGET_RVP"
  "@
   mvm\t%0,%3,%2
   mvmn\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<X:MODE>")])

;; MVM/MVMN XOR forms: ((a ^ b) & mask) ^ c
;; This pattern is similar to AArch64's BSL (Bitwise Select) pattern.
;; We can use MVM or MVMN depending on register allocation:
;;   if (op0 == op1) mvm  op0, op3, op2  (selects op3 where mask=1)
;;   if (op0 == op3) mvmn op0, op1, op2  (selects op1 where mask=0)
;;
;; The pattern ((a ^ b) & mask) ^ a is equivalent to (~mask & a) | (mask & b)
;; The pattern ((a ^ b) & mask) ^ b is equivalent to (~mask & b) | (mask & a)
(define_insn "*mvm<X:mode>_xor"
  [(set (match_operand:X 0 "register_operand" "=r,r")
	(xor:X (and:X (xor:X (match_operand:X 1 "register_operand" "0,r")
			     (match_operand:X 3 "register_operand" "r,0"))
		      (match_operand:X 2 "register_operand" "r,r"))
	       (match_dup 1)))]
  "TARGET_RVP"
  "@
   mvm\t%0,%3,%2
   mvmn\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<X:MODE>")])

;; Alternative form where the outer XOR operand is operands[3] instead
;; of operands[1].  This is needed because combine may produce either form
;; depending on which operand of the inner XOR it chooses to commute.
(define_insn "*mvm<X:mode>_xor_alt"
  [(set (match_operand:X 0 "register_operand" "=r,r")
	(xor:X (and:X (xor:X (match_operand:X 1 "register_operand" "r,0")
			     (match_operand:X 3 "register_operand" "0,r"))
		      (match_operand:X 2 "register_operand" "r,r"))
	       (match_dup 3)))]
  "TARGET_RVP"
  "@
   mvm\t%0,%1,%2
   mvmn\t%0,%3,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "<X:MODE>")])

;; PSABS: Saturating absolute value for scalar and packed QI/HI modes
(define_insn "ssabs<mode>2"
  [(set (match_operand:QIHI 0 "register_operand" "=r")
	(ss_abs:QIHI (match_operand:QIHI 1 "register_operand" "r")))]
  "TARGET_RVP"
  "psabs.<rvp_width>\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

(define_insn "abs<mode>2"
  [(set (match_operand:QIHI 0 "register_operand" "=r")
	(abs:QIHI (match_operand:QIHI 1 "register_operand" "r")))]
  "TARGET_RVP"
  "psabs.<rvp_width>\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

;; PAS/PSA - Packed Add-Subtract (alternating operations)
;; pas.hx: rd[even] = rs1[even] + rs2[even], rd[odd] = rs1[odd] - rs2[odd]
;; psa.hx: rd[even] = rs1[even] - rs2[even], rd[odd] = rs1[odd] + rs2[odd]
;;
;; GCC vectorizes and combines this as:
;;   (vec_merge (vec_select (op1 a b) [even indices])
;;              (vec_select (op2 a b) [odd indices]) mask)
;; Uses iterators: pas_even_op, pas_odd_op, pas_insn

;; pas/psa.hx for PV2HI (RV32/RV64)
;; Even: pas_even_op(rs1, rs2), Odd: pas_odd_op(rs1, rs2) - canonical form.
(define_insn "*rvp_<pas_insn>_hx_v2hi"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
	(vec_merge:PV2HI
	  (vec_select:PV2HI
	    (pas_even_op:PV2HI
	      (match_operand:PV2HI 1 "register_operand" "r")
	      (match_operand:PV2HI 2 "register_operand" "r"))
	    (parallel [(const_int 0) (const_int 0)]))
	  (vec_select:PV2HI
	    (<pas_odd_op>:PV2HI (match_dup 1) (match_dup 2))
	    (parallel [(const_int 1) (const_int 1)]))
	  (const_int 1)))]
  "TARGET_RVP"
  "<pas_insn>.hx\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "PV2HI")])

;; Commuted-plus variant: GCC's SLP may canonicalize plus(rs2, rs1) when the
;; non-commutative odd op remains minus(rs1, rs2).  This matches pas.hx only
;; (pas_even_op == plus swapped; psa already has minus in even which is fine).
(define_insn "*rvp_pas_hx_v2hi_comm"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
	(vec_merge:PV2HI
	  (vec_select:PV2HI
	    (plus:PV2HI
	      (match_operand:PV2HI 2 "register_operand" "r")
	      (match_operand:PV2HI 1 "register_operand" "r"))
	    (parallel [(const_int 0) (const_int 0)]))
	  (vec_select:PV2HI
	    (minus:PV2HI (match_dup 1) (match_dup 2))
	    (parallel [(const_int 1) (const_int 1)]))
	  (const_int 1)))]
  "TARGET_RVP"
  "pas.hx\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "PV2HI")])

;; Commuted-plus variant for psa.hx: GCC may canonicalize plus(rs2, rs1) in
;; the odd position while minus(rs1, rs2) remains in the even position.
(define_insn "*rvp_psa_hx_v2hi_comm"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
	(vec_merge:PV2HI
	  (vec_select:PV2HI
	    (minus:PV2HI
	      (match_operand:PV2HI 1 "register_operand" "r")
	      (match_operand:PV2HI 2 "register_operand" "r"))
	    (parallel [(const_int 0) (const_int 0)]))
	  (vec_select:PV2HI
	    (plus:PV2HI (match_dup 2) (match_dup 1))
	    (parallel [(const_int 1) (const_int 1)]))
	  (const_int 1)))]
  "TARGET_RVP"
  "psa.hx\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "PV2HI")])

;; pas/psa.hx for PV4HI (RV32: pas.dhx, RV64: pas.hx)
(define_insn "*rvp_<pas_insn>_hx_v4hi"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
	(vec_merge:PV4HI
	  (vec_select:PV4HI
	    (pas_even_op:PV4HI
	      (match_operand:PV4HI 1 "register_operand" "r")
	      (match_operand:PV4HI 2 "register_operand" "r"))
	    (parallel [(const_int 0) (const_int 0) (const_int 2) (const_int 2)]))
	  (vec_select:PV4HI
	    (<pas_odd_op>:PV4HI (match_dup 1) (match_dup 2))
	    (parallel [(const_int 1) (const_int 1) (const_int 3) (const_int 3)]))
	  (const_int 5)))]
  "TARGET_RVP"
  "<pas_insn>.%d0x\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "PV4HI")])

;; Commuted-plus variant for pas.hx on PV4HI.
(define_insn "*rvp_pas_hx_v4hi_comm"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
	(vec_merge:PV4HI
	  (vec_select:PV4HI
	    (plus:PV4HI
	      (match_operand:PV4HI 2 "register_operand" "r")
	      (match_operand:PV4HI 1 "register_operand" "r"))
	    (parallel [(const_int 0) (const_int 0) (const_int 2) (const_int 2)]))
	  (vec_select:PV4HI
	    (minus:PV4HI (match_dup 1) (match_dup 2))
	    (parallel [(const_int 1) (const_int 1) (const_int 3) (const_int 3)]))
	  (const_int 5)))]
  "TARGET_RVP"
  "pas.%d0x\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "PV4HI")])

;; Commuted-plus variant for psa.hx on PV4HI.
(define_insn "*rvp_psa_hx_v4hi_comm"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
	(vec_merge:PV4HI
	  (vec_select:PV4HI
	    (minus:PV4HI
	      (match_operand:PV4HI 1 "register_operand" "r")
	      (match_operand:PV4HI 2 "register_operand" "r"))
	    (parallel [(const_int 0) (const_int 0) (const_int 2) (const_int 2)]))
	  (vec_select:PV4HI
	    (plus:PV4HI (match_dup 2) (match_dup 1))
	    (parallel [(const_int 1) (const_int 1) (const_int 3) (const_int 3)]))
	  (const_int 5)))]
  "TARGET_RVP"
  "psa.%d0x\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "PV4HI")])

;; pas/psa.wx for PV2SI (RV64 only)
(define_insn "*rvp_<pas_insn>_wx_v2si"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(vec_merge:PV2SI
	  (vec_select:PV2SI
	    (pas_even_op:PV2SI
	      (match_operand:PV2SI 1 "register_operand" "r")
	      (match_operand:PV2SI 2 "register_operand" "r"))
	    (parallel [(const_int 0) (const_int 0)]))
	  (vec_select:PV2SI
	    (<pas_odd_op>:PV2SI (match_dup 1) (match_dup 2))
	    (parallel [(const_int 1) (const_int 1)]))
	  (const_int 1)))]
  "TARGET_RVP && TARGET_64BIT"
  "<pas_insn>.wx\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "PV2SI")])

;; Rounding arithmetic shift right immediate - scalar
;; SRARI: rd = (rs1 + (1 << (shamt-1))) >> shamt (with rounding)
;; Pattern matches: (a + (1 << (n-1))) >> n
;; Shift amount must be in range [1, mode_bitsize-1] to avoid UB.
(define_insn "*srari<X:mode>"
  [(set (match_operand:X 0 "register_operand" "=r")
	(ashiftrt:X
	  (plus:X (match_operand:X 1 "register_operand" "r")
		  (match_operand:X 2 "const_int_operand" "n"))
	  (match_operand:X 3 "const_int_operand" "n")))]
  "TARGET_RVP
   && IN_RANGE (INTVAL (operands[3]), 1, GET_MODE_BITSIZE (<X:MODE>mode) - 1)
   && INTVAL (operands[2]) == ((HOST_WIDE_INT)1 << (INTVAL (operands[3]) - 1))"
  "srari\t%0,%1,%3"
  [(set_attr "type" "shift")
   (set_attr "mode" "<X:MODE>")])

;; SRARI for SI mode on RV64: matches (ashiftrt:DI (sign_extend:DI (plus:SI ...)) shamt)
;; This is the RTL form GCC generates when combining: addiw + srai -> srari
;; Shift amount must be in range [1, 31] for SI mode.
(define_insn "*srari_sidi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ashiftrt:DI
	  (sign_extend:DI
	    (plus:SI (match_operand:SI 1 "register_operand" "r")
		     (match_operand:SI 2 "const_int_operand" "n")))
	  (match_operand:DI 3 "const_int_operand" "n")))]
  "TARGET_64BIT && TARGET_RVP
   && IN_RANGE (INTVAL (operands[3]), 1, 31)
   && INTVAL (operands[2]) == ((HOST_WIDE_INT)1 << (INTVAL (operands[3]) - 1))"
  "srari\t%0,%1,%3"
  [(set_attr "type" "shift")
   (set_attr "mode" "SI")])

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
      return "<abd_insn>.<rvp_width>\t%0, %1, %2";
    else
      return "<abd_insn>.<rvp_dwidth>\t%0, %1, %2";
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
  "TARGET_RVP"
)

(define_insn "*rvp_widen_<u>maddsidi4"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI
          (mult:DI (any_extend:DI (match_operand:SI 1 "register_operand" "r"))
                   (any_extend:DI (match_operand:SI 2 "register_operand" "r")))
          (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
  "wmacc<u>\t%0, %1, %2"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "*sumaddsidi4"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (plus:DI
          (mult:DI (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))
                   (sign_extend:DI (match_operand:SI 1 "register_operand" "r")))
          (match_operand:DI 3 "register_operand" "0")))]
  "TARGET_RVP && !TARGET_64BIT"
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
  "abs\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<GPR:MODE>")])

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

;; Match sign_extend(subreg(abs(di))) pattern from GCC RTL expansion,
;; e.g. an ABS followed by SEXT.W on RV64.
(define_insn "*absw_di_subreg"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI
	  (subreg:SI (abs:DI (match_operand:DI 1 "register_operand" "r")) 0)))]
  "TARGET_RVP && TARGET_64BIT"
  "absw\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

;; Packed sign-extension

;; Pattern for RV32 register-pair sign extendtions (ps/zext.dh/dw.b/h)
(define_insn "<extension><rvp_narrow><rvp_ext_mode>2"
  [(set (match_operand:RVP_DWIDTH_EXT 0 "register_operand" "=R")
        (any_extend:RVP_DWIDTH_EXT (match_operand:<HALFMODE> 1 "register_operand" "r")))]
  "TARGET_RVP && !TARGET_64BIT"
  "<rvp_extend_insn>.<rvp_dwidth>.<rvp_extend_width>\t%0, %1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<MODE>")])

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
