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

;; Packed-SIMD extension.
;Packed Multiply Parts Accumulate
;Three-operand RMW: rd += (selected halfword/word pair product).
;hNN selects the halfword pair (h00=low*low, h01=low*high, h11=high*high);
;wNN selects the word pair likewise.  Structurally identical to the
;q-format mqacc/mqracc family above (simd.md:8141+); the only difference is
;no Q-format product-window extraction -- the full low 32/64-bit product is
;accumulated.  That semantic difference is carried by the hardware mnemonic;
;GCC models both as opaque unspec RMW.
;  h-series i32 (scalar): RV32 macc.hNN/maccu.hNN/maccsu.hNN;
;    RV64 pmacc.w.hNN/etc (lane 0 = result).
;  h-series i32x2 (packed): RV64 pmacc.w.hNN/etc; RV32 2x macc.hNN.
;  w-series i64 (scalar, RV64-only): macc.wNN/maccu.wNN/maccsu.wNN.
;    RV32 uses wmacc/wmaccu/wmaccsu (register pair) -- TODO, like mqacc_w.

;--- macc_h* (signed) ---
(define_expand "riscv_macc_h00_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MACC_H00))]
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
      emit_insn (gen_riscv_macc_h00_i32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_macc_h00_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_macc_h00_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MACC_H00))]
  "TARGET_RVP && !TARGET_64BIT"
  "macc.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_macc_h00_i32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACC_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmacc.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_macc_h01_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MACC_H01))]
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
      emit_insn (gen_riscv_macc_h01_i32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_macc_h01_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_macc_h01_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MACC_H01))]
  "TARGET_RVP && !TARGET_64BIT"
  "macc.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_macc_h01_i32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACC_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmacc.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_macc_h11_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MACC_H11))]
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
      emit_insn (gen_riscv_macc_h11_i32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_macc_h11_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_macc_h11_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MACC_H11))]
  "TARGET_RVP && !TARGET_64BIT"
  "macc.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_macc_h11_i32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACC_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmacc.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- maccu_h* (unsigned) ---
(define_expand "riscv_maccu_h00_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MACCU_H00))]
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
      emit_insn (gen_riscv_maccu_h00_u32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_maccu_h00_u32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_maccu_h00_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MACCU_H00))]
  "TARGET_RVP && !TARGET_64BIT"
  "maccu.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_maccu_h00_u32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACCU_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmaccu.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_maccu_h01_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MACCU_H01))]
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
      emit_insn (gen_riscv_maccu_h01_u32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_maccu_h01_u32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_maccu_h01_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MACCU_H01))]
  "TARGET_RVP && !TARGET_64BIT"
  "maccu.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_maccu_h01_u32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACCU_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmaccu.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_maccu_h11_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MACCU_H11))]
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
      emit_insn (gen_riscv_maccu_h11_u32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_maccu_h11_u32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_maccu_h11_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MACCU_H11))]
  "TARGET_RVP && !TARGET_64BIT"
  "maccu.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_maccu_h11_u32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACCU_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmaccu.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- maccsu_h* (signed x unsigned) ---
(define_expand "riscv_maccsu_h00_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MACCSU_H00))]
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
      emit_insn (gen_riscv_maccsu_h00_i32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_maccsu_h00_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_maccsu_h00_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MACCSU_H00))]
  "TARGET_RVP && !TARGET_64BIT"
  "maccsu.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_maccsu_h00_i32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACCSU_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmaccsu.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_maccsu_h11_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_MACCSU_H11))]
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
      emit_insn (gen_riscv_maccsu_h11_i32_rv64
		   (gen_lowpart (V2SImode, acc),
		    gen_lowpart (V2SImode, r1),
		    gen_lowpart (V2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_maccsu_h11_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_maccsu_h11_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_MACCSU_H11))]
  "TARGET_RVP && !TARGET_64BIT"
  "maccsu.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_maccsu_h11_i32_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACCSU_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmaccsu.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- h-series i32x2 (packed V2SI, RMW) ---
;RV64: single pmacc.w.h*/etc on V2SI.  RV32: split the 64-bit pair into
;low/high SI/V2HI halves and run the scalar macc.h*/etc on each half.
(define_expand "riscv_pmacc_h00_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PMACC_H00))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmacc_h00_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_macc_h00_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_macc_h00_i32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmacc_h00_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMACC_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmacc.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmacc_h01_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PMACC_H01))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmacc_h01_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_macc_h01_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_macc_h01_i32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmacc_h01_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMACC_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmacc.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmacc_h11_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PMACC_H11))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmacc_h11_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_macc_h11_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_macc_h11_i32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmacc_h11_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMACC_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmacc.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmaccu_h00_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PMACCU_H00))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmaccu_h00_u32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_maccu_h00_u32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_maccu_h00_u32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmaccu_h00_u32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMACCU_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmaccu.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmaccu_h01_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PMACCU_H01))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmaccu_h01_u32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_maccu_h01_u32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_maccu_h01_u32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmaccu_h01_u32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMACCU_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmaccu.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmaccu_h11_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PMACCU_H11))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmaccu_h11_u32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_maccu_h11_u32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_maccu_h11_u32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmaccu_h11_u32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMACCU_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmaccu.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmaccsu_h00_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PMACCSU_H00))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmaccsu_h00_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_maccsu_h00_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_maccsu_h00_i32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmaccsu_h00_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMACCSU_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmaccsu.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmaccsu_h11_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PMACCSU_H11))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmaccsu_h11_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_maccsu_h11_i32_rv32 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_maccsu_h11_i32_rv32 (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmaccsu_h11_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMACCSU_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmaccsu.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- w-series i64 (scalar DI, RMW; RV64-only) ---
;macc.wNN/maccu.wNN/maccsu.wNN multiply a selected pair of 32-bit words
;(w00=low*low, w01=low*high, w11=high*high) and accumulate into the 64-bit rd.
;RV32 uses wmacc/wmaccu/wmaccsu (register pair) -- TODO (needs even-GPR pair
;allocation), left RV64-only like mqacc_w*_i64 (simd.md:8692) / mul_w*_i64.
(define_expand "riscv_macc_w00_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_MACC_W00))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_macc_w00_i64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_macc_w00_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACC_W00))]
  "TARGET_RVP && TARGET_64BIT"
  "macc.w00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_macc_w01_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_MACC_W01))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_macc_w01_i64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_macc_w01_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACC_W01))]
  "TARGET_RVP && TARGET_64BIT"
  "macc.w01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_macc_w11_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_MACC_W11))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_macc_w11_i64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_macc_w11_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACC_W11))]
  "TARGET_RVP && TARGET_64BIT"
  "macc.w11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_maccu_w00_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_MACCU_W00))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_maccu_w00_u64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_maccu_w00_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACCU_W00))]
  "TARGET_RVP && TARGET_64BIT"
  "maccu.w00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_maccu_w01_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_MACCU_W01))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_maccu_w01_u64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_maccu_w01_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACCU_W01))]
  "TARGET_RVP && TARGET_64BIT"
  "maccu.w01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_maccu_w11_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_MACCU_W11))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_maccu_w11_u64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_maccu_w11_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACCU_W11))]
  "TARGET_RVP && TARGET_64BIT"
  "maccu.w11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_maccsu_w00_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_MACCSU_W00))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_maccsu_w00_i64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_maccsu_w00_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACCSU_W00))]
  "TARGET_RVP && TARGET_64BIT"
  "maccsu.w00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_maccsu_w11_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_MACCSU_W11))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_maccsu_w11_i64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_maccsu_w11_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_MACCSU_W11))]
  "TARGET_RVP && TARGET_64BIT"
  "maccsu.w11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------------------- Packed Multiplication with Horizontal Addition --------
;Two-operand: rs1*rs2 horizontal-add to a scalar/packed result.  Mirrors the
;Packed Q-format Multiply (pmulq_*, simd.md:8035) structure: the .b/.h/.hx
;mnemonics are single instructions on both ISAs for the 32-bit (V4QI/V2HI->SI)
;forms; the i32x2 packed forms are RV64 single / RV32 2x; the i64 forms are
;RV64 single (RV32 uses wmul+wmacc / pm2wadd sequences -- TODO, like mqacc_w).

;--- 32-bit (both ISAs, single insn): V4QI/V2HI -> SI/USI scalar ---
(define_insn "riscv_pm4add_i8x4"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4QI 1 "register_operand" "r")
                    (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PM4ADD_B))]
  "TARGET_RVP"
  "pm4add.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pm2add_i16x2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2ADD_H))]
  "TARGET_RVP"
  "pm2add.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pm2add_x_i16x2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2ADD_HX))]
  "TARGET_RVP"
  "pm2add.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pm4addu_u8x4"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4QI 1 "register_operand" "r")
                    (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PM4ADDU_B))]
  "TARGET_RVP"
  "pm4addu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pm2addu_u16x2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDU_H))]
  "TARGET_RVP"
  "pm2addu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmq2add_i16x2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PMQ2ADD_H))]
  "TARGET_RVP"
  "pmq2add.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmqr2add_i16x2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PMQR2ADD_H))]
  "TARGET_RVP"
  "pmqr2add.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pm2sadd_i16x2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2SADD_H))]
  "TARGET_RVP"
  "pm2sadd.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pm2sadd_x_i16x2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2SADD_HX))]
  "TARGET_RVP"
  "pm2sadd.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pm2sub_i16x2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2SUB_H))]
  "TARGET_RVP"
  "pm2sub.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pm2sub_x_i16x2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2SUB_HX))]
  "TARGET_RVP"
  "pm2sub.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pm4addsu_i8x4"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4QI 1 "register_operand" "r")
                    (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PM4ADDSU_B))]
  "TARGET_RVP"
  "pm4addsu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pm2addsu_i16x2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDSU_H))]
  "TARGET_RVP"
  "pm2addsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- 64-bit i32x2 (packed): RV64 single insn; RV32 2x split into low/high ---
;RV64: single pm4add.b/pm2add.h/etc on the full 64-bit vector.  RV32: split
;the 64-bit pair into low/high V4QI/V2HI halves and run the scalar 32-bit
;insn on each (mirrors riscv_pmulq_i16x4, simd.md:8053).
(define_expand "riscv_pm4add_i8x8"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V8QI 1 "register_operand")
                      (match_operand:V8QI 2 "register_operand")]
         UNSPEC_PM4ADD_I8X8))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm4add_i8x8_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V8QImode, operands[1]);
      rtx r2 = force_reg (V8QImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V4QImode, r1, V8QImode, 0);
      rtx s1_hi = simplify_gen_subreg (V4QImode, r1, V8QImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pm4add_i8x4 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm4add_i8x4 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pm4add_i8x8_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V8QI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PM4ADD_I8X8))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4add.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2add_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PM2ADD_I16X4))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2add_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2add_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2add_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pm2add_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2ADD_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2add.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2add_x_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PM2ADD_X_I16X4))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2add_x_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2add_x_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2add_x_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pm2add_x_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2ADD_X_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2add.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4addu_u8x8"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V8QI 1 "register_operand")
                      (match_operand:V8QI 2 "register_operand")]
         UNSPEC_PM4ADDU_U8X8))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm4addu_u8x8_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V8QImode, operands[1]);
      rtx r2 = force_reg (V8QImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V4QImode, r1, V8QImode, 0);
      rtx s1_hi = simplify_gen_subreg (V4QImode, r1, V8QImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pm4addu_u8x4 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm4addu_u8x4 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pm4addu_u8x8_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V8QI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PM4ADDU_U8X8))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4addu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2addu_u16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PM2ADDU_U16X4))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2addu_u16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2addu_u16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2addu_u16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pm2addu_u16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDU_U16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2addu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmq2add_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PMQ2ADD_I16X4))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmq2add_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pmq2add_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmq2add_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmq2add_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMQ2ADD_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pmq2add.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmqr2add_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PMQR2ADD_I16X4))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmqr2add_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pmqr2add_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmqr2add_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmqr2add_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMQR2ADD_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqr2add.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2sadd_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PM2SADD_I16X4))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2sadd_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2sadd_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2sadd_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pm2sadd_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2SADD_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2sadd.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2sadd_x_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PM2SADD_X_I16X4))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2sadd_x_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2sadd_x_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2sadd_x_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pm2sadd_x_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2SADD_X_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2sadd.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2sub_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PM2SUB_I16X4))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2sub_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2sub_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2sub_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pm2sub_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2SUB_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2sub.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2sub_x_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PM2SUB_X_I16X4))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2sub_x_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2sub_x_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2sub_x_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pm2sub_x_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2SUB_X_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2sub.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4addsu_i8x8"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V8QI 1 "register_operand")
                      (match_operand:V8QI 2 "register_operand")]
         UNSPEC_PM4ADDSU_I8X8))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm4addsu_i8x8_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V8QImode, operands[1]);
      rtx r2 = force_reg (V8QImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V4QImode, r1, V8QImode, 0);
      rtx s1_hi = simplify_gen_subreg (V4QImode, r1, V8QImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pm4addsu_i8x4 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm4addsu_i8x4 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pm4addsu_i8x8_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V8QI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PM4ADDSU_I8X8))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4addsu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2addsu_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PM2ADDSU_I16X4))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2addsu_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
      rtx r1 = force_reg (V4HImode, operands[1]);
      rtx r2 = force_reg (V4HImode, operands[2]);
      rtx d_lo = simplify_gen_subreg (SImode, operands[0], V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, operands[0], V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2addsu_i16x2 (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2addsu_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pm2addsu_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDSU_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2addsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- 64-bit i64 (scalar DI/UDI; RV64-only) ---
;pm2add.w/pm2add.wx/pm2addu.w/pmq2add.w/pm2sub.w/pm2sub.wx/pm2addsu.w/pmqr2add.w
;take a V2SI pair, horizontally multiply+add the two words, produce a 64-bit
;result.  pm4add.h/pm4addu.h/pm4addsu.h take a V4HI pair -> 64-bit.  RV32 uses
;wmul+wmacc / pm2wadd sequences -- TODO (needs even-GPR pair allocation / the
;pm2wadd insn family), left RV64-only like mqacc_w / macc_w (simd.md:8692).
(define_expand "riscv_pm2add_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")]
         UNSPEC_PM2ADD_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_pm2add_i32x2_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2add_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2ADD_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2add.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2add_x_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")]
         UNSPEC_PM2ADD_WX))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_pm2add_x_i32x2_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2add_x_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2ADD_WX))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2add.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2addu_u32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")]
         UNSPEC_PM2ADDU_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_pm2addu_u32x2_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2addu_u32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2ADDU_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2addu.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmq2add_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")]
         UNSPEC_PMQ2ADD_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_pmq2add_i32x2_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pmq2add_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PMQ2ADD_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pmq2add.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2sub_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")]
         UNSPEC_PM2SUB_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_pm2sub_i32x2_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2sub_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2SUB_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2sub.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2sub_x_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")]
         UNSPEC_PM2SUB_WX))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_pm2sub_x_i32x2_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2sub_x_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2SUB_WX))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2sub.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2addsu_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")]
         UNSPEC_PM2ADDSU_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_pm2addsu_i32x2_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm2addsu_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2ADDSU_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2addsu.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmqr2add_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")]
         UNSPEC_PMQR2ADD_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_pmqr2add_i32x2_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pmqr2add_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PMQR2ADD_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqr2add.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4add_i16x4"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V4HI 1 "register_operand")
                    (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PM4ADD_H))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_pm4add_i16x4_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm4add_i16x4_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V4HI 1 "register_operand" "r")
                    (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM4ADD_H))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4add.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4addu_u16x4"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V4HI 1 "register_operand")
                    (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PM4ADDU_H))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_pm4addu_u16x4_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm4addu_u16x4_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V4HI 1 "register_operand" "r")
                    (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM4ADDU_H))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4addu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4addsu_i16x4"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V4HI 1 "register_operand")
                    (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PM4ADDSU_H))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_pm4addsu_i16x4_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pm4addsu_i16x4_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V4HI 1 "register_operand" "r")
                    (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM4ADDSU_H))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4addsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------- Packed Multiplication with Horizontal Addition and Accumulate ---
;Three-operand RMW: rd += (rs1 op rs2) horizontal.  Mirrors the pm2add/pm4add
;family above (simd.md:10967) plus an RMW accumulator, structurally identical
;to the Packed Multiply High Accumulate pmhacc series (simd.md:7363).
;  32-bit (both ISAs, single insn): pm4adda.b/pm2adda.h/etc, RMW into SI/USI.
;  64-bit i32x2 (packed, RMW): RV64 single pm2adda.h/etc; RV32 2x.
;  64-bit i64 (RV64-only, RMW): pm2adda.w/etc, pm4adda.h/etc.
;    RV32 uses wmacc/pm2wadda sequences -- TODO, like mqacc_w / macc_w.

;--- 32-bit (both ISAs, single insn, RMW): V4QI/V2HI -> SI/USI ---
(define_expand "riscv_pm4adda_i8x4"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V4QI 2 "register_operand")
                    (match_operand:V4QI 3 "register_operand")]
         UNSPEC_PM4ADDA_B))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm4adda_i8x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm4adda_i8x4_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V4QI 1 "register_operand" "r")
                    (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PM4ADDA_B))]
  "TARGET_RVP"
  "pm4adda.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2adda_i16x2"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2ADDA_H))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2adda_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2adda_i16x2_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDA_H))]
  "TARGET_RVP"
  "pm2adda.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2adda_x_i16x2"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2ADDA_HX))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2adda_x_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2adda_x_i16x2_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDA_HX))]
  "TARGET_RVP"
  "pm2adda.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4addau_u8x4"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V4QI 2 "register_operand")
                    (match_operand:V4QI 3 "register_operand")]
         UNSPEC_PM4ADDAU_B))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm4addau_u8x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm4addau_u8x4_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V4QI 1 "register_operand" "r")
                    (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PM4ADDAU_B))]
  "TARGET_RVP"
  "pm4addau.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2addau_u16x2"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2ADDAU_H))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2addau_u16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2addau_u16x2_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDAU_H))]
  "TARGET_RVP"
  "pm2addau.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmq2adda_i16x2"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PMQ2ADDA_H))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmq2adda_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmq2adda_i16x2_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PMQ2ADDA_H))]
  "TARGET_RVP"
  "pmq2adda.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmqr2adda_i16x2"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PMQR2ADDA_H))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmqr2adda_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmqr2adda_i16x2_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PMQR2ADDA_H))]
  "TARGET_RVP"
  "pmqr2adda.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2suba_i16x2"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2SUBA_H))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2suba_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2suba_i16x2_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2SUBA_H))]
  "TARGET_RVP"
  "pm2suba.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2suba_x_i16x2"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2SUBA_HX))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2suba_x_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2suba_x_i16x2_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2SUBA_HX))]
  "TARGET_RVP"
  "pm2suba.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4addasu_i8x4"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V4QI 2 "register_operand")
                    (match_operand:V4QI 3 "register_operand")]
         UNSPEC_PM4ADDASU_B))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm4addasu_i8x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm4addasu_i8x4_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V4QI 1 "register_operand" "r")
                    (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PM4ADDASU_B))]
  "TARGET_RVP"
  "pm4addasu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2addasu_i16x2"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:V2HI 2 "register_operand")
                    (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PM2ADDASU_H))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2addasu_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2addasu_i16x2_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDASU_H))]
  "TARGET_RVP"
  "pm2addasu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- 64-bit i32x2 (packed, RMW): RV64 single; RV32 2x split low/high ---
;RV64: single pm4adda.b/pm2adda.h/etc on V2SI accumulator.  RV32: split the
;64-bit pair into low/high V4QI/V2HI halves and run the scalar RMW insn on
;each (mirrors riscv_pmqacc_h00_i32x2, simd.md:8452).
(define_expand "riscv_pm4adda_i8x8"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V8QI 2 "register_operand")
                      (match_operand:V8QI 3 "register_operand")]
         UNSPEC_PM4ADDA_I8X8))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm4adda_i8x8_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V8QImode, operands[2]);
      rtx r2 = force_reg (V8QImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V4QImode, r1, V8QImode, 0);
      rtx s1_hi = simplify_gen_subreg (V4QImode, r1, V8QImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pm4adda_i8x4_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm4adda_i8x4_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pm4adda_i8x8_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V8QI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PM4ADDA_I8X8))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4adda.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2adda_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PM2ADDA_I16X4))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2adda_i16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2adda_i16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2adda_i16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pm2adda_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDA_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2adda.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2adda_x_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PM2ADDA_X_I16X4))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2adda_x_i16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2adda_x_i16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2adda_x_i16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pm2adda_x_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDA_X_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2adda.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4addau_u8x8"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V8QI 2 "register_operand")
                      (match_operand:V8QI 3 "register_operand")]
         UNSPEC_PM4ADDAU_U8X8))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm4addau_u8x8_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V8QImode, operands[2]);
      rtx r2 = force_reg (V8QImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V4QImode, r1, V8QImode, 0);
      rtx s1_hi = simplify_gen_subreg (V4QImode, r1, V8QImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pm4addau_u8x4_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm4addau_u8x4_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pm4addau_u8x8_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V8QI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PM4ADDAU_U8X8))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4addau.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2addau_u16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PM2ADDAU_U16X4))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2addau_u16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2addau_u16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2addau_u16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pm2addau_u16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDAU_U16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2addau.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmq2adda_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PMQ2ADDA_I16X4))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmq2adda_i16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pmq2adda_i16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmq2adda_i16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmq2adda_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMQ2ADDA_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pmq2adda.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmqr2adda_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PMQR2ADDA_I16X4))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmqr2adda_i16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pmqr2adda_i16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pmqr2adda_i16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmqr2adda_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PMQR2ADDA_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqr2adda.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2suba_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PM2SUBA_I16X4))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2suba_i16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2suba_i16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2suba_i16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pm2suba_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2SUBA_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2suba.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2suba_x_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PM2SUBA_X_I16X4))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2suba_x_i16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2suba_x_i16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2suba_x_i16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pm2suba_x_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2SUBA_X_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2suba.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4addasu_i8x8"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V8QI 2 "register_operand")
                      (match_operand:V8QI 3 "register_operand")]
         UNSPEC_PM4ADDASU_I8X8))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm4addasu_i8x8_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V8QImode, operands[2]);
      rtx r2 = force_reg (V8QImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V4QImode, r1, V8QImode, 0);
      rtx s1_hi = simplify_gen_subreg (V4QImode, r1, V8QImode, 4);
      rtx s2_lo = simplify_gen_subreg (V4QImode, r2, V8QImode, 0);
      rtx s2_hi = simplify_gen_subreg (V4QImode, r2, V8QImode, 4);
      emit_insn (gen_riscv_pm4addasu_i8x4_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm4addasu_i8x4_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pm4addasu_i8x8_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V8QI 1 "register_operand" "r")
                      (match_operand:V8QI 2 "register_operand" "r")]
         UNSPEC_PM4ADDASU_I8X8))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4addasu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2addasu_i16x4"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")
                      (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PM2ADDASU_I16X4))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pm2addasu_i16x4_rv64 (operands[0], operands[2], operands[3]));
  else
    {
      rtx r0 = force_reg (V2SImode, operands[0]);
      rtx r1 = force_reg (V4HImode, operands[2]);
      rtx r2 = force_reg (V4HImode, operands[3]);
      rtx d_lo = simplify_gen_subreg (SImode, r0, V2SImode, 0);
      rtx d_hi = simplify_gen_subreg (SImode, r0, V2SImode, 4);
      rtx s1_lo = simplify_gen_subreg (V2HImode, r1, V4HImode, 0);
      rtx s1_hi = simplify_gen_subreg (V2HImode, r1, V4HImode, 4);
      rtx s2_lo = simplify_gen_subreg (V2HImode, r2, V4HImode, 0);
      rtx s2_hi = simplify_gen_subreg (V2HImode, r2, V4HImode, 4);
      emit_insn (gen_riscv_pm2addasu_i16x2_rmw (d_lo, s1_lo, s2_lo));
      emit_insn (gen_riscv_pm2addasu_i16x2_rmw (d_hi, s1_hi, s2_hi));
      emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pm2addasu_i16x4_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "+r")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM2ADDASU_I16X4))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2addasu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- 64-bit i64 (scalar DI/UDI, RMW; RV64-only) ---
;pm2adda.w/pm2adda.wx/pm2addau.w/pmq2adda.w/pm2suba.w/pm2suba.wx/pm2addasu.w/
;pmqr2adda.w accumulate into a 64-bit rd from a V2SI pair; pm4adda.h/pm4addau.h/
;pm4addasu.h from a V4HI pair.  RV32 uses wmacc/pm2wadda sequences -- TODO
;(needs even-GPR pair allocation / the pm2wadda insn family), left RV64-only
;like mqacc_w / macc_w / pm2add_w (simd.md:11540).
(define_expand "riscv_pm2adda_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_PM2ADDA_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2adda_i32x2_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2adda_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2ADDA_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2adda.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2adda_x_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_PM2ADDA_WX))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2adda_x_i32x2_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2adda_x_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2ADDA_WX))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2adda.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2addau_u32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_PM2ADDAU_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2addau_u32x2_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2addau_u32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2ADDAU_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2addau.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmq2adda_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_PMQ2ADDA_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmq2adda_i32x2_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmq2adda_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PMQ2ADDA_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pmq2adda.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2suba_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_PM2SUBA_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2suba_i32x2_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2suba_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2SUBA_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2suba.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2suba_x_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_PM2SUBA_WX))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2suba_x_i32x2_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2suba_x_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2SUBA_WX))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2suba.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm2addasu_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_PM2ADDASU_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm2addasu_i32x2_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm2addasu_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PM2ADDASU_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pm2addasu.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmqr2adda_i32x2"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V2SI 2 "register_operand")
                    (match_operand:V2SI 3 "register_operand")]
         UNSPEC_PMQR2ADDA_W))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmqr2adda_i32x2_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmqr2adda_i32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V2SI 1 "register_operand" "r")
                    (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PMQR2ADDA_W))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqr2adda.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4adda_i16x4"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V4HI 2 "register_operand")
                    (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PM4ADDA_H))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm4adda_i16x4_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm4adda_i16x4_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V4HI 1 "register_operand" "r")
                    (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM4ADDA_H))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4adda.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4addau_u16x4"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V4HI 2 "register_operand")
                    (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PM4ADDAU_H))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm4addau_u16x4_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm4addau_u16x4_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V4HI 1 "register_operand" "r")
                    (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM4ADDAU_H))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4addau.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pm4addasu_i16x4"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:V4HI 2 "register_operand")
                    (match_operand:V4HI 3 "register_operand")]
         UNSPEC_PM4ADDASU_H))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pm4addasu_i16x4_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pm4addasu_i16x4_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:V4HI 1 "register_operand" "r")
                    (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PM4ADDASU_H))]
  "TARGET_RVP && TARGET_64BIT"
  "pm4addasu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

