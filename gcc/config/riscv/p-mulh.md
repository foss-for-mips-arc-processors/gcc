;; Machine description for RISC-V 'P' extension multiply operations.
;; Copyright (C) 2025-2026 Free Software Foundation, Inc.
;;
;; This file is part of GCC.
;;
;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.
;;
;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;-------------------- Packed Multiply High Parts -------------------------
;Two-operand high-half multiply.  Structurally identical to the Packed
;Multiply Parts family (simd.md:8847+): .b selects byte 0/1, .h selects
;halfword 0/1; the product's high half is taken (vs. Packed Multiply Parts
;which uses the full product via bNN/hNN word-pair selection).
;  b-series i16x2 (both ISAs, single insn): pmulh.h.bN/pmulhsu.h.bN.
;  h-series i32 (scalar): RV32 mulh.hN/mulhsu.hN, RV64 pmulh.w.hN/etc.
;  b-series i16x4 (packed): RV64 single, RV32 2x.
;  h-series i32x2 (packed): RV64 pmulh.w.hN, RV32 2x mulh.hN.

;--- b-series i16x2 (V2HI, V4QI -> V2HI; single insn, both ISAs) ---
(define_insn "riscv_pmulh_b0_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PMULH_B0))]
  "TARGET_RVP"
  "pmulh.h.b0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulh_b1_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PMULH_B1))]
  "TARGET_RVP"
  "pmulh.h.b1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhsu_b0_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PMULHSU_B0))]
  "TARGET_RVP"
  "pmulhsu.h.b0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhsu_b1_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PMULHSU_B1))]
  "TARGET_RVP"
  "pmulhsu.h.b1\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- h-series i32 (scalar SI; RV32 mulh.hN, RV64 pmulh.w.hN) ---
;RV64: pmulh.w.hN is a packed V2SI insn; the scalar SI/int16x2_t values live
;in lane 0.  Widen rs1/rs2 (32-bit SI/V2HI) to 64-bit V2SI via zero-extend so
;the full register is owned by the insn; lane 1 product is discarded.  rd (SI)
;takes the low 32 bits.  Mirrors riscv_mul_h00_i32 (simd.md:8924).
(define_expand "riscv_mulh_h0_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")]
         UNSPEC_MULH_H0))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx r1 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
      emit_insn (gen_riscv_mulh_h0_i32_rv64
		   (operands[0],
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mulh_h0_i32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulh_h0_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MULH_H0))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulh.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mulh_h0_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MULH_H0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulh.w.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mulh_h1_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")]
         UNSPEC_MULH_H1))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx r1 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
      emit_insn (gen_riscv_mulh_h1_i32_rv64
		   (operands[0],
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mulh_h1_i32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulh_h1_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MULH_H1))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulh.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mulh_h1_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MULH_H1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulh.w.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mulhsu_h0_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")]
         UNSPEC_MULHSU_H0))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx r1 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
      emit_insn (gen_riscv_mulhsu_h0_i32_rv64
		   (operands[0],
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mulhsu_h0_i32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulhsu_h0_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MULHSU_H0))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulhsu.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mulhsu_h0_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MULHSU_H0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhsu.w.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mulhsu_h1_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")]
         UNSPEC_MULHSU_H1))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx r1 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
      emit_insn (gen_riscv_mulhsu_h1_i32_rv64
		   (operands[0],
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mulhsu_h1_i32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulhsu_h1_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MULHSU_H1))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulhsu.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mulhsu_h1_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MULHSU_H1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhsu.w.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- b-series i16x4 (packed V8QI -> V4HI; RV64 single, RV32 2x) ---
;RV64: single pmulh.h.bN/pmulhsu.h.bN on the full 64-bit vector.  RV32: split
;the 64-bit pair into low/high V4QI/V2HI halves and run the i16x2 insn on each
;(mirrors riscv_pmul_b00_i16x4, simd.md:9273).
(define_expand "riscv_pmulh_b0_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V8QI 2 "register_operand")]
         UNSPEC_PMULH_B0))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulh_b0_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V8QImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (V2HImode, operands[0], V4HImode, 0);
      rtx d_hi = simplify_gen_subreg (V2HImode, operands[0], V4HImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pmulh_b0_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmulh_b0_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulh_b0_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PMULH_B0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulh.h.b0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulh_b1_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V8QI 2 "register_operand")]
         UNSPEC_PMULH_B1))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulh_b1_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V8QImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (V2HImode, operands[0], V4HImode, 0);
      rtx d_hi = simplify_gen_subreg (V2HImode, operands[0], V4HImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pmulh_b1_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmulh_b1_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulh_b1_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PMULH_B1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulh.h.b1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulhsu_b0_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V8QI 2 "register_operand")]
         UNSPEC_PMULHSU_B0))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulhsu_b0_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V8QImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (V2HImode, operands[0], V4HImode, 0);
      rtx d_hi = simplify_gen_subreg (V2HImode, operands[0], V4HImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pmulhsu_b0_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmulhsu_b0_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulhsu_b0_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PMULHSU_B0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhsu.h.b0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulhsu_b1_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V8QI 2 "register_operand")]
         UNSPEC_PMULHSU_B1))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulhsu_b1_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V8QImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (V2HImode, operands[0], V4HImode, 0);
      rtx d_hi = simplify_gen_subreg (V2HImode, operands[0], V4HImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pmulhsu_b1_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmulhsu_b1_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulhsu_b1_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PMULHSU_B1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhsu.h.b1\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- h-series i32x2 (packed V4HI -> V2SI; RV64 pmulh.w.hN, RV32 2x mulh.hN) ---
(define_expand "riscv_pmulh_h0_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_MULH_H0))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulh_h0_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V2SImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (SImode, r1, V2SImode, 0);
      rtx s1_hi = simplify_gen_subreg (SImode, r1, V2SImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_mulh_h0_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_mulh_h0_i32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulh_h0_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_MULH_H0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulh.w.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulh_h1_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_MULH_H1))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulh_h1_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V2SImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (SImode, r1, V2SImode, 0);
      rtx s1_hi = simplify_gen_subreg (SImode, r1, V2SImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_mulh_h1_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_mulh_h1_i32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulh_h1_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_MULH_H1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulh.w.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulhsu_h0_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_MULHSU_H0))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulhsu_h0_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V2SImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (SImode, r1, V2SImode, 0);
      rtx s1_hi = simplify_gen_subreg (SImode, r1, V2SImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_mulhsu_h0_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_mulhsu_h0_i32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulhsu_h0_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_MULHSU_H0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhsu.w.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulhsu_h1_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_MULHSU_H1))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulhsu_h1_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V2SImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (SImode, r1, V2SImode, 0);
      rtx s1_hi = simplify_gen_subreg (SImode, r1, V2SImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_mulhsu_h1_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_mulhsu_h1_i32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulhsu_h1_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_MULHSU_H1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhsu.w.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------- Packed Multiply High Parts Accumulate ---------------------------
;Three-operand RMW: rd += (high-half product of selected byte/halfword pair).
;Mirrors the Packed Multiply High Parts family above (simd.md:12760) plus an
;RMW accumulator, structurally identical to the Packed Multiply High
;Accumulate pmhacc series (simd.md:7404) and the mqacc_* RMW accumulators.
;  b-series i16x2 (both ISAs, single RMW insn): pmhacc.h.bN/pmhaccsu.h.bN.
;  h-series i32 (scalar, RMW): RV32 mhacc.hN/mhaccsu.hN, RV64 pmhacc.w.hN/etc.
;  b-series i16x4 (packed, RMW): RV64 single, RV32 2x.
;  h-series i32x2 (packed, RMW): RV64 pmhacc.w.hN, RV32 2x mhacc.hN.

;--- b-series i16x2 (V2HI rd accumulator; single RMW insn, both ISAs) ---
(define_expand "riscv_pmhacc_b0_i16x2"
  [(set (match_operand:V2HI 0 "register_operand")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V4QI 3 "register_operand")]
         UNSPEC_PMHACC_B0))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhacc_b0_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhacc_b0_i16x2_rmw"
  [(set (match_operand:V2HI 0 "register_operand" "+r")
        (unspec:V2HI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PMHACC_B0))]
  "TARGET_RVP"
  "pmhacc.h.b0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhacc_b1_i16x2"
  [(set (match_operand:V2HI 0 "register_operand")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V4QI 3 "register_operand")]
         UNSPEC_PMHACC_B1))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhacc_b1_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhacc_b1_i16x2_rmw"
  [(set (match_operand:V2HI 0 "register_operand" "+r")
        (unspec:V2HI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PMHACC_B1))]
  "TARGET_RVP"
  "pmhacc.h.b1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccsu_b0_i16x2"
  [(set (match_operand:V2HI 0 "register_operand")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V4QI 3 "register_operand")]
         UNSPEC_PMHACCSU_B0))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhaccsu_b0_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhaccsu_b0_i16x2_rmw"
  [(set (match_operand:V2HI 0 "register_operand" "+r")
        (unspec:V2HI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PMHACCSU_B0))]
  "TARGET_RVP"
  "pmhaccsu.h.b0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccsu_b1_i16x2"
  [(set (match_operand:V2HI 0 "register_operand")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V4QI 3 "register_operand")]
         UNSPEC_PMHACCSU_B1))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhaccsu_b1_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhaccsu_b1_i16x2_rmw"
  [(set (match_operand:V2HI 0 "register_operand" "+r")
        (unspec:V2HI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PMHACCSU_B1))]
  "TARGET_RVP"
  "pmhaccsu.h.b1\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- h-series i32 (scalar SI RMW; RV32 mhacc.hN, RV64 pmhacc.w.hN) ---
;RV64: pmhacc.w.hN is a packed V2SI insn; the scalar SI values live in lane 0.
;Widen rs1/rs2 (32-bit SI/V2HI) to 64-bit V2SI via zero-extend so the full
;register is owned by the insn; lane 1 product is discarded.  Mirrors
;riscv_mqacc_h00_i32 (simd.md:8141).
(define_expand "riscv_mhacc_h0_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:SI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MHACC_H0))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
      rtx acc = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2 (acc, operands[0]));
      rtx r1 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r1, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r2, force_reg (SImode, gen_lowpart (SImode, operands[3]))));
      emit_insn (gen_riscv_mhacc_h0_i32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_mhacc_h0_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mhacc_h0_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:SI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MHACC_H0))]
  "TARGET_RVP && !TARGET_64BIT"
  "mhacc.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mhacc_h0_i32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MHACC_H0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhacc.w.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mhacc_h1_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:SI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MHACC_H1))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
      rtx acc = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2 (acc, operands[0]));
      rtx r1 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r1, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r2, force_reg (SImode, gen_lowpart (SImode, operands[3]))));
      emit_insn (gen_riscv_mhacc_h1_i32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_mhacc_h1_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mhacc_h1_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:SI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MHACC_H1))]
  "TARGET_RVP && !TARGET_64BIT"
  "mhacc.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mhacc_h1_i32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MHACC_H1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhacc.w.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mhaccsu_h0_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:SI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MHACCSU_H0))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
      rtx acc = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2 (acc, operands[0]));
      rtx r1 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r1, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r2, force_reg (SImode, gen_lowpart (SImode, operands[3]))));
      emit_insn (gen_riscv_mhaccsu_h0_i32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_mhaccsu_h0_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mhaccsu_h0_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:SI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MHACCSU_H0))]
  "TARGET_RVP && !TARGET_64BIT"
  "mhaccsu.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mhaccsu_h0_i32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MHACCSU_H0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhaccsu.w.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mhaccsu_h1_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:SI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MHACCSU_H1))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
      rtx acc = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2 (acc, operands[0]));
      rtx r1 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r1, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		   (r2, force_reg (SImode, gen_lowpart (SImode, operands[3]))));
      emit_insn (gen_riscv_mhaccsu_h1_i32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_mhaccsu_h1_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mhaccsu_h1_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:SI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MHACCSU_H1))]
  "TARGET_RVP && !TARGET_64BIT"
  "mhaccsu.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mhaccsu_h1_i32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MHACCSU_H1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhaccsu.w.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- b-series i16x4 (packed V4HI rd RMW; RV64 single, RV32 2x) ---
;RV64: single pmhacc.h.bN/pmhaccsu.h.bN on the full 64-bit vector.  RV32: split
;the 64-bit pair into low/high V2HI/V4QI halves and run the i16x2 RMW insn on
;each (mirrors riscv_pmqacc_h00_i32x2, simd.md:8452).
(define_expand "riscv_pmhacc_b0_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V8QI 3 "register_operand")]
         UNSPEC_PMHACC_B0))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmhacc_b0_i16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V4HImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V8QImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (V2HImode, r0, V4HImode, 0);
      rtx d_hi = simplify_gen_subreg (V2HImode, r0, V4HImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pmhacc_b0_i16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmhacc_b0_i16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmhacc_b0_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "+r")
        (unspec:V4HI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PMHACC_B0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhacc.h.b0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhacc_b1_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V8QI 3 "register_operand")]
         UNSPEC_PMHACC_B1))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmhacc_b1_i16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V4HImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V8QImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (V2HImode, r0, V4HImode, 0);
      rtx d_hi = simplify_gen_subreg (V2HImode, r0, V4HImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pmhacc_b1_i16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmhacc_b1_i16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmhacc_b1_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "+r")
        (unspec:V4HI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PMHACC_B1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhacc.h.b1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccsu_b0_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V8QI 3 "register_operand")]
         UNSPEC_PMHACCSU_B0))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmhaccsu_b0_i16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V4HImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V8QImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (V2HImode, r0, V4HImode, 0);
      rtx d_hi = simplify_gen_subreg (V2HImode, r0, V4HImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pmhaccsu_b0_i16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmhaccsu_b0_i16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmhaccsu_b0_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "+r")
        (unspec:V4HI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PMHACCSU_B0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhaccsu.h.b0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccsu_b1_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V8QI 3 "register_operand")]
         UNSPEC_PMHACCSU_B1))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmhaccsu_b1_i16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V4HImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V8QImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (V2HImode, r0, V4HImode, 0);
      rtx d_hi = simplify_gen_subreg (V2HImode, r0, V4HImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pmhaccsu_b1_i16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmhaccsu_b1_i16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmhaccsu_b1_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "+r")
        (unspec:V4HI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PMHACCSU_B1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhaccsu.h.b1\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- h-series i32x2 (packed V2SI rd RMW; RV64 pmhacc.w.hN, RV32 2x mhacc.hN) ---
(define_expand "riscv_pmhacc_h0_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2SI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_MHACC_H0))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmhacc_h0_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V2SImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (SImode, r1, V2SImode, 0);
      rtx s1_hi = simplify_gen_subreg (SImode, r1, V2SImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_mhacc_h0_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_mhacc_h0_i32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmhacc_h0_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_MHACC_H0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhacc.w.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhacc_h1_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2SI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_MHACC_H1))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmhacc_h1_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V2SImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (SImode, r1, V2SImode, 0);
      rtx s1_hi = simplify_gen_subreg (SImode, r1, V2SImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_mhacc_h1_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_mhacc_h1_i32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmhacc_h1_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_MHACC_H1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhacc.w.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccsu_h0_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2SI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_MHACCSU_H0))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmhaccsu_h0_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V2SImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (SImode, r1, V2SImode, 0);
      rtx s1_hi = simplify_gen_subreg (SImode, r1, V2SImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_mhaccsu_h0_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_mhaccsu_h0_i32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmhaccsu_h0_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_MHACCSU_H0))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhaccsu.w.h0\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccsu_h1_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2SI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_MHACCSU_H1))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmhaccsu_h1_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V2SImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (SImode, r1, V2SImode, 0);
      rtx s1_hi = simplify_gen_subreg (SImode, r1, V2SImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_mhaccsu_h1_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_mhaccsu_h1_i32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmhaccsu_h1_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_MHACCSU_H1))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhaccsu.w.h1\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------------------- Packed Widening Multiply ----------------------------
;Two-operand widening multiply: V4QI->V4HI / V2HI->V2SI.  RV32 has single
;insns (pwmul.b/pwmul.h/pwmulu.*/pwmulsu.*) producing a 64-bit result in a
;register pair (=R).  RV64 has no single widening-mul insn; the spec sequences
;(zip8p+pmul.h.b01 / zip16p+pmul.w.h01 / pwcvtu+pmulsu.h.b00) are not yet
;wired here -- builtins are simd32-only (see simd.def), so RV64 calls error
;out, matching the existing pwadd/pwsub family (simd.md:6758+).

(define_insn "riscv_pwmul_i16x4"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4QI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PWMUL_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmul.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwmul_i32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWMUL_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmul.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwmulu_u16x4"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4QI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PWMULU_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmulu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwmulu_u32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWMULU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmulu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwmulsu_i16x4"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4QI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PWMULSU_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmulsu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwmulsu_i32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWMULSU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmulsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------------------- Packed Widening Multiply Accumulate ------------------
;Three-operand RMW widening accumulate: rd (V2SI/UV2SI) += (rs1 * rs2) where
;rs1/rs2 are V2HI/UV2HI (the product widens to 32-bit).  RV32 has single RMW
;insns (pwmacc.h/pwmaccu.h/pwmaccsu.h) using a register pair (=R).  RV64 has
;no single widening-mul-accumulate insn; the spec sequences (zip16p+pmacc.w.h01
; / pwcvtu+pmaccsu.w.h00) are not yet wired -- builtins are simd32-only, so RV64
;calls error out, matching the existing pwadda/pwsuba family (simd.md:6854+).

(define_expand "riscv_pwmacc_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PWMACC_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwmacc_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwmacc_i32x2_rmw"
  [(set (match_operand:V2SI 0 "register_operand" "+R")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWMACC_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmacc.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwmaccu_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PWMACCU_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwmaccu_u32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwmaccu_u32x2_rmw"
  [(set (match_operand:V2SI 0 "register_operand" "+R")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWMACCU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmaccu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwmaccsu_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PWMACCSU_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwmaccsu_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwmaccsu_i32x2_rmw"
  [(set (match_operand:V2SI 0 "register_operand" "+R")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWMACCSU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwmaccsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------- Packed "Q-format" Multiply with Widening Accumulate -------------
;Three-operand RMW widening Q-format accumulate: rd (V2SI) += Q(rs1*rs2) where
;rs1/rs2 are V2HI (product widens to 32-bit).  RV32 single RMW insns
;(pmqwacc.h/pmqrwacc.h) using a register pair (=R).  RV64 sequences
;(zip16p+pmqacc.w.h01 / zip16p+pmqracc.w.h01) not wired -- simd32-only, RV64
;errors out, matching pwmacc / pwadda.

(define_expand "riscv_pmqwacc_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PMQWACC_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmqwacc_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmqwacc_i32x2_rmw"
  [(set (match_operand:V2SI 0 "register_operand" "+R")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PMQWACC_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmqwacc.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmqrwacc_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PMQRWACC_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmqrwacc_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmqrwacc_i32x2_rmw"
  [(set (match_operand:V2SI 0 "register_operand" "+R")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PMQRWACC_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmqrwacc.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------- Packed Multiplication with Widening Horizontal Addition ----------
;Two-operand widening mul+horizontal-add: V2HI -> DI.  RV32 has single
;register-pair instructions.  RV64 clears the unused upper word of one source
;before using PM4ADD, or sign-extends the scalar PM2SUB result.

(define_expand "riscv_pm2wadd_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2HI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")]
         UNSPEC_PM2WADD_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx lhs_di = gen_reg_rtx (DImode);
      rtx lhs_si = gen_lowpart (SImode, operands[1]);
      rtx rhs = lowpart_subreg (V4HImode, operands[2], V2HImode);
      emit_insn (gen_rtx_SET
	(lhs_di, gen_rtx_ZERO_EXTEND (DImode, lhs_si)));
      emit_insn (gen_riscv_pm4add_i16x4
	(operands[0], gen_lowpart (V4HImode, lhs_di), rhs));
    }
  else
    emit_insn (gen_riscv_pm2wadd_i64_rv32
	       (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2wadd_i64_rv32"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (unspec:DI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WADD_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2wadd.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2wadd_x_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2HI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")]
         UNSPEC_PM2WADD_HX))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx lhs_di = gen_reg_rtx (DImode);
      rtx lhs_si = gen_lowpart (SImode, operands[1]);
      rtx rhs = gen_lowpart (PV2HImode, operands[2]);
      rtx exchanged = gen_reg_rtx (PV2HImode);
      emit_insn (gen_rtx_SET
	(lhs_di, gen_rtx_ZERO_EXTEND (DImode, lhs_si)));
      emit_insn (gen_riscv_ppairoe_i16x2 (exchanged, rhs, rhs));
      emit_insn (gen_riscv_pm4add_i16x4
	(operands[0], gen_lowpart (V4HImode, lhs_di),
	 lowpart_subreg (V4HImode, exchanged, PV2HImode)));
    }
  else
    emit_insn (gen_riscv_pm2wadd_x_i64_rv32
	       (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2wadd_x_i64_rv32"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (unspec:DI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WADD_HX))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2wadd.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2waddu_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2HI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")]
         UNSPEC_PM2WADDU_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx lhs_di = gen_reg_rtx (DImode);
      rtx lhs_si = gen_lowpart (SImode, operands[1]);
      rtx rhs = lowpart_subreg (V4HImode, operands[2], V2HImode);
      emit_insn (gen_rtx_SET
	(lhs_di, gen_rtx_ZERO_EXTEND (DImode, lhs_si)));
      emit_insn (gen_riscv_pm4addu_u16x4
	(operands[0], gen_lowpart (V4HImode, lhs_di), rhs));
    }
  else
    emit_insn (gen_riscv_pm2waddu_u64_rv32
	       (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2waddu_u64_rv32"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (unspec:DI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WADDU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2waddu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2wsub_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2HI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")]
         UNSPEC_PM2WSUB_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx difference = gen_reg_rtx (SImode);
      emit_insn (gen_riscv_pm2sub_i16x2
	(difference, operands[1], operands[2]));
      emit_insn (gen_rtx_SET
	(operands[0], gen_rtx_SIGN_EXTEND (DImode, difference)));
    }
  else
    emit_insn (gen_riscv_pm2wsub_i64_rv32
	       (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2wsub_i64_rv32"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (unspec:DI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WSUB_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2wsub.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2wsub_x_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2HI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")]
         UNSPEC_PM2WSUB_HX))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx difference = gen_reg_rtx (SImode);
      emit_insn (gen_riscv_pm2sub_x_i16x2
	(difference, operands[1], operands[2]));
      emit_insn (gen_rtx_SET
	(operands[0], gen_rtx_SIGN_EXTEND (DImode, difference)));
    }
  else
    emit_insn (gen_riscv_pm2wsub_x_i64_rv32
	       (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2wsub_x_i64_rv32"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (unspec:DI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WSUB_HX))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2wsub.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2waddsu_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2HI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")]
         UNSPEC_PM2WADDSU_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx lhs_di = gen_reg_rtx (DImode);
      rtx lhs_si = gen_lowpart (SImode, operands[1]);
      rtx rhs = lowpart_subreg (V4HImode, operands[2], V2HImode);
      emit_insn (gen_rtx_SET
	(lhs_di, gen_rtx_ZERO_EXTEND (DImode, lhs_si)));
      emit_insn (gen_riscv_pm4addsu_i16x4
	(operands[0], gen_lowpart (V4HImode, lhs_di), rhs));
    }
  else
    emit_insn (gen_riscv_pm2waddsu_u64_rv32
	       (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2waddsu_u64_rv32"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (unspec:DI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WADDSU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2waddsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------- Packed Multiplication with Widening Horizontal Addition and Accumulate
;Three-operand RMW widening mul+horizontal-add accumulate: rd (DI/UDI) +=
;(rs1 * rs2) widened where rs1/rs2 are V2HI/UV2HI.  RV32 uses single
;register-pair instructions.  RV64 uses PM4ADDA for addition and a PM2SUB,
;zero-extension, and PREDSUM sequence for subtraction.

(define_expand "riscv_pm2wadda_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2WADDA_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx lhs_di = gen_reg_rtx (DImode);
      rtx lhs_si = gen_lowpart (SImode, operands[2]);
      rtx rhs = lowpart_subreg (V4HImode, operands[3], V2HImode);
      emit_insn (gen_rtx_SET
	(lhs_di, gen_rtx_ZERO_EXTEND (DImode, lhs_si)));
      emit_insn (gen_riscv_pm4adda_i16x4
	(operands[0], operands[1], gen_lowpart (V4HImode, lhs_di), rhs));
    }
  else
    {
      emit_move_insn (operands[0], operands[1]);
      emit_insn (gen_riscv_pm2wadda_i64_rmw
	(operands[0], operands[2], operands[3]));
    }
  DONE;
})

(define_insn "riscv_pm2wadda_i64_rmw"
  [(set (match_operand:DI 0 "register_operand" "+R")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WADDA_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2wadda.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2wadda_x_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2WADDA_HX))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx lhs_di = gen_reg_rtx (DImode);
      rtx lhs_si = gen_lowpart (SImode, operands[2]);
      rtx rhs = gen_lowpart (PV2HImode, operands[3]);
      rtx exchanged = gen_reg_rtx (PV2HImode);
      emit_insn (gen_rtx_SET
	(lhs_di, gen_rtx_ZERO_EXTEND (DImode, lhs_si)));
      emit_insn (gen_riscv_ppairoe_i16x2 (exchanged, rhs, rhs));
      emit_insn (gen_riscv_pm4adda_i16x4
	(operands[0], operands[1], gen_lowpart (V4HImode, lhs_di),
	 lowpart_subreg (V4HImode, exchanged, PV2HImode)));
    }
  else
    {
      emit_move_insn (operands[0], operands[1]);
      emit_insn (gen_riscv_pm2wadda_x_i64_rmw
	(operands[0], operands[2], operands[3]));
    }
  DONE;
})

(define_insn "riscv_pm2wadda_x_i64_rmw"
  [(set (match_operand:DI 0 "register_operand" "+R")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WADDA_HX))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2wadda.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2waddau_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2WADDAU_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx lhs_di = gen_reg_rtx (DImode);
      rtx lhs_si = gen_lowpart (SImode, operands[2]);
      rtx rhs = lowpart_subreg (V4HImode, operands[3], V2HImode);
      emit_insn (gen_rtx_SET
	(lhs_di, gen_rtx_ZERO_EXTEND (DImode, lhs_si)));
      emit_insn (gen_riscv_pm4addau_u16x4
	(operands[0], operands[1], gen_lowpart (V4HImode, lhs_di), rhs));
    }
  else
    {
      emit_move_insn (operands[0], operands[1]);
      emit_insn (gen_riscv_pm2waddau_u64_rmw
	(operands[0], operands[2], operands[3]));
    }
  DONE;
})

(define_insn "riscv_pm2waddau_u64_rmw"
  [(set (match_operand:DI 0 "register_operand" "+R")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WADDAU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2waddau.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2wsuba_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2WSUBA_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx difference = gen_reg_rtx (SImode);
      rtx widened = gen_reg_rtx (DImode);
      emit_insn (gen_riscv_pm2sub_i16x2
	(difference, operands[2], operands[3]));
      emit_insn (gen_rtx_SET
	(widened, gen_rtx_ZERO_EXTEND (DImode, difference)));
      emit_insn (gen_riscv_predsum_i32x2_i64
	(operands[0], gen_lowpart (PV2SImode, widened), operands[1]));
    }
  else
    {
      emit_move_insn (operands[0], operands[1]);
      emit_insn (gen_riscv_pm2wsuba_i64_rmw
	(operands[0], operands[2], operands[3]));
    }
  DONE;
})

(define_insn "riscv_pm2wsuba_i64_rmw"
  [(set (match_operand:DI 0 "register_operand" "+R")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WSUBA_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2wsuba.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2wsuba_x_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2WSUBA_HX))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx difference = gen_reg_rtx (SImode);
      rtx widened = gen_reg_rtx (DImode);
      emit_insn (gen_riscv_pm2sub_x_i16x2
	(difference, operands[2], operands[3]));
      emit_insn (gen_rtx_SET
	(widened, gen_rtx_ZERO_EXTEND (DImode, difference)));
      emit_insn (gen_riscv_predsum_i32x2_i64
	(operands[0], gen_lowpart (PV2SImode, widened), operands[1]));
    }
  else
    {
      emit_move_insn (operands[0], operands[1]);
      emit_insn (gen_riscv_pm2wsuba_x_i64_rmw
	(operands[0], operands[2], operands[3]));
    }
  DONE;
})

(define_insn "riscv_pm2wsuba_x_i64_rmw"
  [(set (match_operand:DI 0 "register_operand" "+R")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WSUBA_HX))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2wsuba.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2waddasu_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2WADDASU_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx lhs_di = gen_reg_rtx (DImode);
      rtx lhs_si = gen_lowpart (SImode, operands[2]);
      rtx rhs = lowpart_subreg (V4HImode, operands[3], V2HImode);
      emit_insn (gen_rtx_SET
	(lhs_di, gen_rtx_ZERO_EXTEND (DImode, lhs_si)));
      emit_insn (gen_riscv_pm4addasu_i16x4
	(operands[0], operands[1], gen_lowpart (V4HImode, lhs_di), rhs));
    }
  else
    {
      emit_move_insn (operands[0], operands[1]);
      emit_insn (gen_riscv_pm2waddasu_u64_rmw
	(operands[0], operands[2], operands[3]));
    }
  DONE;
})

(define_insn "riscv_pm2waddasu_u64_rmw"
  [(set (match_operand:DI 0 "register_operand" "+R")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2WADDASU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pm2waddasu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])
