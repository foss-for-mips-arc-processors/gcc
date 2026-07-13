;); Machine description for RISC-V Bit Manipulation operations.
;; Copyright (C) 2025-2026 Free Software Foundation, Inc.
;; Contributed by Jiawei Chen (jiawei@iscas.ac.cn), PLCT ISCAS.

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

;; Packed-SIMD extension.
; Packed Shifts
(define_insn "riscv_psll_s_u8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:V4QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
         UNSPEC_PSLL))]
  "TARGET_RVP"
  "@
   pslli.b\t%0,%1,%2
   psll.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psll_s_i8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:V4QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSLL))]
  "TARGET_RVP"
  "@
   pslli.b\t%0,%1,%2
   psll.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psll_s_u16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u4, r")]
          UNSPEC_PSLL))]
  "TARGET_RVP"
  "@
   pslli.h\t%0,%1,%2
   psll.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psll_s_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u4, r")]
          UNSPEC_PSLL))]
  "TARGET_RVP"
  "@
   pslli.h\t%0,%1,%2
   psll.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psrl_s_u8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:V4QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
         UNSPEC_PSRL))]
  "TARGET_RVP"
  "@
   psrli.b\t%0,%1,%2
   psrl.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psrl_s_u16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PSRL))]
  "TARGET_RVP"
  "@
   psrli.h\t%0,%1,%2
   psrl.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psra_s_i8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:V4QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
         UNSPEC_PSRA))]
  "TARGET_RVP"
  "@
   psrai.b\t%0,%1,%2
   psra.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psra_s_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PSRA))]
  "TARGET_RVP"
  "@
   psrai.h\t%0,%1,%2
   psra.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psll_s_u8x8"
  [(set (match_operand:V8QI 0 "register_operand")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSLL))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psll_s_u8x8_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psll_s_u8x8_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})


(define_insn "riscv_psll_s_u8x8_rv32"
  [(set (match_operand:V8QI 0 "register_operand" "=R, R")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
         UNSPEC_PSLL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pslli.db\t%0,%1,%2
   psll.dbs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psll_s_u8x8_rv64"
  [(set (match_operand:V8QI 0 "register_operand" "=r, r")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
         UNSPEC_PSLL))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pslli.b\t%0,%1,%2
   psll.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psll_s_i8x8"
  [(set (match_operand:V8QI 0 "register_operand")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSLL))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psll_s_i8x8_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psll_s_i8x8_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psll_s_i8x8_rv64"
  [(set (match_operand:V8QI 0 "register_operand" "=r, r")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
         UNSPEC_PSLL))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pslli.b\t%0,%1,%2
   psll.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psll_s_i8x8_rv32"
  [(set (match_operand:V8QI 0 "register_operand" "=R, R")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
         UNSPEC_PSLL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pslli.db\t%0,%1,%2
   psll.dbs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psll_s_u16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSLL))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psll_s_u16x4_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psll_s_u16x4_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psll_s_u16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R, R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u4, r")]
          UNSPEC_PSLL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pslli.dh\t%0,%1,%2
   psll.dhs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psll_s_u16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r, r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u4, r")]
          UNSPEC_PSLL))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pslli.h\t%0,%1,%2
   psll.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psll_s_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSLL))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psll_s_i16x4_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psll_s_i16x4_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psll_s_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R, R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u4, r")]
          UNSPEC_PSLL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pslli.dh\t%0,%1,%2
   psll.dhs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psll_s_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r, r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u4, r")]
          UNSPEC_PSLL))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pslli.h\t%0,%1,%2
   psll.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psll_s_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSLL))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psll_s_u32x2_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psll_s_u32x2_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psll_s_u32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R, R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u5, r")]
          UNSPEC_PSLL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pslli.dw\t%0,%1,%2
   psll.dws\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psll_s_u32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r, r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u5, r")]
          UNSPEC_PSLL))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pslli.w\t%0,%1,%2
   psll.ws\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psll_s_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSLL))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psll_s_i32x2_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psll_s_i32x2_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psll_s_i32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R, R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u5, r")]
          UNSPEC_PSLL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pslli.dw\t%0,%1,%2
   psll.dws\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psll_s_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r, r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u5, r")]
          UNSPEC_PSLL))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pslli.w\t%0,%1,%2
   psll.ws\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psrl_s_u8x8"
  [(set (match_operand:V8QI 0 "register_operand")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSRL))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psrl_s_u8x8_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psrl_s_u8x8_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psrl_s_u8x8_rv32"
  [(set (match_operand:V8QI 0 "register_operand" "=R, R")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psrli.db\t%0,%1,%2
   psrl.dbs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psrl_s_u8x8_rv64"
  [(set (match_operand:V8QI 0 "register_operand" "=r, r")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRL))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psrli.b\t%0,%1,%2
   psrl.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psrl_s_u16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSRL))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psrl_s_u16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psrl_s_u16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psrl_s_u16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R, R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psrli.dh\t%0,%1,%2
   psrl.dhs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psrl_s_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSRL))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psrl_s_u32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psrl_s_u32x2_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psrl_s_u32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R, R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psrli.dw\t%0,%1,%2
   psrl.dws\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psra_s_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r, r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRA))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psrai.w\t%0,%1,%2
   psra.ws\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psra_s_i8x8"
  [(set (match_operand:V8QI 0 "register_operand")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSRA))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psra_s_i8x8_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psra_s_i8x8_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psra_s_i8x8_rv32"
  [(set (match_operand:V8QI 0 "register_operand" "=R, R")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psrai.db\t%0,%1,%2
   psra.dbs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psra_s_i8x8_rv64"
  [(set (match_operand:V8QI 0 "register_operand" "=r, r")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRA))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psrai.b\t%0,%1,%2
   psra.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psra_s_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSRA))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psra_s_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psra_s_i16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psra_s_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R, R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psrai.dh\t%0,%1,%2
   psra.dhs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psra_s_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r, r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRA))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psrai.h\t%0,%1,%2
   psra.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psrl_s_u16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r, r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRL))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psrli.h\t%0,%1,%2
   psrl.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_psra_s_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSRA))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psra_s_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psra_s_i32x2_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psra_s_i32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R, R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psrai.dw\t%0,%1,%2
   psra.dws\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_psrl_s_u32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r, r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r")
                    (match_operand:SI 2 "arith_operand" "u3, r")]
          UNSPEC_PSRL))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psrli.w\t%0,%1,%2
   psrl.ws\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

;Packed Saturating and Rounding Shifts
;
; pssha/psshar: signed saturating (rounding) arithmetic shift, expanded via
; psslai (immediate) / psrai or psrari (negative immediate) / pssha[r].hs.
; psshl/psshlr: unsigned saturating (rounding) logical shift.

(define_insn "riscv_pssha_s_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r, r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
          UNSPEC_PSSHA))]
  "TARGET_RVP"
  "@
   psslai.h\t%0,%1,%2
   psrai.h\t%0,%1,%n2
   pssha.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_psshar_s_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r, r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
         UNSPEC_PSSHAR))]
  "TARGET_RVP"
  "@
   psslai.h\t%0,%1,%2
   psrari.h\t%0,%1,%n2
   psshar.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_psshl_s_u16x2"
  [(set (match_operand:V2HI 0 "register_operand")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHL))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
})

(define_insn "riscv_psshl_s_u16x2_insn"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_PSSHL))]
  "TARGET_RVP"
  "psshl.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psshlr_s_u16x2"
  [(set (match_operand:V2HI 0 "register_operand")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHLR))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
})

(define_insn "riscv_psshlr_s_u16x2_insn"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_PSSHLR))]
  "TARGET_RVP"
  "psshlr.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pssha_s_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHA))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_pssha_s_i16x4_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_pssha_s_i16x4_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_pssha_s_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R, R, R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
          UNSPEC_PSSHA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psslai.dh\t%0,%1,%2
   psrai.dh\t%0,%1,%n2
   pssha.dhs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_pssha_s_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r, r, r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
          UNSPEC_PSSHA))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psslai.h\t%0,%1,%2
   psrai.h\t%0,%1,%n2
   pssha.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_pssha_s_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHA))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_pssha_s_i32x2_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_pssha_s_i32x2_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_pssha_s_i32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R, R, R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u5, w5, r")]
          UNSPEC_PSSHA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psslai.dw\t%0,%1,%2
   psrai.dw\t%0,%1,%n2
   pssha.dws\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_pssha_s_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r, r, r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u5, w5, r")]
          UNSPEC_PSSHA))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psslai.w\t%0,%1,%2
   psrai.w\t%0,%1,%n2
   pssha.ws\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_psshar_s_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHAR))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshar_s_i16x4_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshar_s_i16x4_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshar_s_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R, R, R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
          UNSPEC_PSSHAR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psslai.dh\t%0,%1,%2
   psrari.dh\t%0,%1,%n2
   psshar.dhs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_psshar_s_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r, r, r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
          UNSPEC_PSSHAR))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psslai.h\t%0,%1,%2
   psrari.h\t%0,%1,%n2
   psshar.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_psshar_s_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHAR))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshar_s_i32x2_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshar_s_i32x2_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshar_s_i32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R, R, R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u5, w5, r")]
          UNSPEC_PSSHAR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psslai.dw\t%0,%1,%2
   psrari.dw\t%0,%1,%n2
   psshar.dws\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_psshar_s_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r, r, r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u5, w5, r")]
          UNSPEC_PSSHAR))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psslai.w\t%0,%1,%2
   psrari.w\t%0,%1,%n2
   psshar.ws\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_psshl_s_u16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHL))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshl_s_u16x4_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshl_s_u16x4_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshl_s_u16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "R")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHL))]
  "TARGET_RVP && !TARGET_64BIT"
  "psshl.dhs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psshl_s_u16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHL))]
  "TARGET_RVP && TARGET_64BIT"
  "psshl.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psshl_s_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHL))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshl_s_u32x2_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshl_s_u32x2_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshl_s_u32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHL))]
  "TARGET_RVP && !TARGET_64BIT"
  "psshl.dws\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psshl_s_u32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHL))]
  "TARGET_RVP && TARGET_64BIT"
  "psshl.ws\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psshlr_s_u16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHLR))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshlr_s_u16x4_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshlr_s_u16x4_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshlr_s_u16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHLR))]
  "TARGET_RVP && !TARGET_64BIT"
  "psshlr.dhs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psshlr_s_u16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHLR))]
  "TARGET_RVP && TARGET_64BIT"
  "psshlr.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psshlr_s_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHLR))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshlr_s_u32x2_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshlr_s_u32x2_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshlr_s_u32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHLR))]
  "TARGET_RVP && !TARGET_64BIT"
  "psshlr.dws\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psshlr_s_u32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHLR))]
  "TARGET_RVP && TARGET_64BIT"
  "psshlr.ws\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Widening Shift
;
;pwsll_s/pwsla_s widen one narrow source (32-bit) into a wide result (64-bit)
;and shift each widened lane left by shamt: V4QI -> V4HI, or V2HI -> V2SI.
;pwsll = logical left shift (zero-extend widen), pwsla = arithmetic left shift
;(sign-extend widen).  shamt may be an immediate or a register scalar.
;  RV32: immediate form  pwslli.b/h, pwslai.b/h  (constraint Wpd,s,WpH/<)
;        register form    pwsll.bs/hs, pwsla.bs/hs (constraint Wpd,s,t)
;        Wpd is the even-odd result pair, s the narrow source, WpH/< the uimm,
;        t the shamt register.  RV32-only hardware instructions.
;  RV64: no single widening shift instruction; spec gives multi-insn sequences
;        (pwcvtu.wb+pslli.h, etc.).  NOT implemented yet.  TODO.  Builtins are
;        simd32-only.
;The two output templates pick pwslli/pwslai when shamt is a u4/u5 immediate,
;and pwsll.bs/hs/pwsla.bs/hs when it is a register (matches the existing
;riscv_psll_s_* pattern style).
(define_insn "riscv_pwsll_s_u16x4"
  [(set (match_operand:V4HI 0 "register_operand" "=R, R")
        (unspec:V4HI [(match_operand:V4QI 1 "register_operand" "r, r")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PWSLL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pwslli.b\t%0,%1,%2
   pwsll.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pwsll_s_u32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=R, R")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand" "r, r")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PWSLL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pwslli.h\t%0,%1,%2
   pwsll.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pwsla_s_i16x4"
  [(set (match_operand:V4HI 0 "register_operand" "=R, R")
        (unspec:V4HI [(match_operand:V4QI 1 "register_operand" "r, r")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PWSLA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pwslai.b\t%0,%1,%2
   pwsla.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pwsla_s_i32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=R, R")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand" "r, r")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PWSLA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pwslai.h\t%0,%1,%2
   pwsla.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

;Packed Narrowing Shift
;
;pnsrl_s/pnsra_s/pnsrar_s narrow one wide source (64-bit) into a narrow result
;(32-bit) by shifting each lane right: V4HI -> V4QI, or V2SI -> V2HI.
;pnsrl = logical right shift (zero-extend narrow), pnsra = arithmetic right
;shift (sign-extend narrow), pnsrar = rounding arithmetic right shift.
;shamt may be an immediate or a register scalar.
;  RV32: immediate form  pnsrli.b/h, pnsrai.b/h, pnsrari.b/h (constraint d,Wps,WpH/<)
;        register form    pnsrl.bs/hs, pnsra.bs/hs, pnsrar.bs/hs (constraint d,Wps,t)
;        d is the narrow result register, Wps the wide even-odd source pair,
;        WpH/< the uimm, t the shamt register.  RV32-only hardware.
;  RV64: no single narrowing shift instruction; spec gives multi-insn sequences
;        (psrli.h+unzip8p, etc.).  NOT implemented yet.  TODO.  Builtins are
;        simd32-only.
(define_insn "riscv_pnsrl_s_u8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:V4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNSRL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrli.b\t%0,%1,%2
   pnsrl.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnsrl_s_u16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r")
        (unspec:V2HI [(match_operand:V2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNSRL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrli.h\t%0,%1,%2
   pnsrl.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnsra_s_i8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:V4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNSRA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrai.b\t%0,%1,%2
   pnsra.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnsra_s_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r")
        (unspec:V2HI [(match_operand:V2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNSRA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrai.h\t%0,%1,%2
   pnsra.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnsrar_s_i8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:V4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNSRAR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrari.b\t%0,%1,%2
   pnsrar.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnsrar_s_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r")
        (unspec:V2HI [(match_operand:V2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNSRAR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrari.h\t%0,%1,%2
   pnsrar.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

;Packed Narrowing Clip
;
;pnclip* narrow one wide source (64-bit) into a narrow result (32-bit) by
;clipping (saturating to the narrow range) after a shift: V4HI -> V4QI, or
;V2SI -> V2HI.  Four variants:
;  pnclipu  = unsigned clip,            pnclipru = unsigned rounding clip
;  pnclip   = signed clip,              pnclipr  = signed rounding clip
;shamt may be an immediate or a register scalar.
;  RV32: immediate form  pnclipiu.b/h, pnclipriu.b/h, pnclipi.b/h, pnclipri.b/h
;                     (constraint d,Wps,WpH/<)
;        register form    pnclipu.bs/hs, pnclipru.bs/hs, pnclip.bs/hs,
;                         pnclipr.bs/hs  (constraint d,Wps,t)
;        d is the narrow result register, Wps the wide even-odd source pair,
;        WpH/< the uimm, t the shamt register.  RV32-only hardware.
;        Note: the immediate mnemonics carry an extra "i" (pnclipiu/pnclipi)
;        while the register mnemonics drop it (pnclipu.bs/pnclip.bs), matching
;        the binutils opcodes table.
;  RV64: no single narrowing clip instruction; spec gives multi-insn sequences
;        (psrli.h+pnclipup.b, etc.).  NOT implemented yet.  TODO.  Builtins
;        are simd32-only.
(define_insn "riscv_pnclipu_s_u8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:V4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNCLIPU))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipiu.b\t%0,%1,%2
   pnclipu.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclipu_s_u16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r")
        (unspec:V2HI [(match_operand:V2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNCLIPU))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipiu.h\t%0,%1,%2
   pnclipu.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclipru_s_u8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:V4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNCLIPRU))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipriu.b\t%0,%1,%2
   pnclipru.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclipru_s_u16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r")
        (unspec:V2HI [(match_operand:V2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNCLIPRU))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipriu.h\t%0,%1,%2
   pnclipru.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclip_s_i8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:V4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNCLIP))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipi.b\t%0,%1,%2
   pnclip.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclip_s_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r")
        (unspec:V2HI [(match_operand:V2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNCLIP))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipi.h\t%0,%1,%2
   pnclip.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclipr_s_i8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:V4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNCLIPR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipri.b\t%0,%1,%2
   pnclipr.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclipr_s_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r")
        (unspec:V2HI [(match_operand:V2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNCLIPR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipri.h\t%0,%1,%2
   pnclipr.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])
