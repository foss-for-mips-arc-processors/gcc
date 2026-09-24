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
;Packed Pair
;
; ppaire  : pack pair even   (RV32 16x2 & RV64 32x2 -> "pack"; RV64 -> ppaire.h/w;
;           RV32 double-wide -> ppaire.db/dh)
; ppaireo : pack pair even-odd
; ppairoe : pack pair odd-even
; ppairo  : pack pair odd
; Each variant has its own UNSPEC (UNSPEC_PPAIRE/PPAIREO/PPAIROE/PPAIRO); the
; mnemonic and (where relevant) the pack/mv alias carry the distinction.
; Signed and unsigned variants of the same width use the same machine
; instruction, so they are separate patterns only because the builtin names differ.
;
; 32x2 (PV2SI) uses pack and the .w instructions on RV64.  On RV32 each
; operation selects one word from each source register pair and is expanded
; to a pair of moves.

(define_int_iterator RVP_PAIR_I32X2
  [UNSPEC_PPAIRE UNSPEC_PPAIREO UNSPEC_PPAIROE UNSPEC_PPAIRO])
(define_int_attr rvp_pair_name
  [(UNSPEC_PPAIRE "ppaire")
   (UNSPEC_PPAIREO "ppaireo")
   (UNSPEC_PPAIROE "ppairoe")
   (UNSPEC_PPAIRO "ppairo")])
(define_int_attr rvp_pair_low
  [(UNSPEC_PPAIRE "0")
   (UNSPEC_PPAIREO "0")
   (UNSPEC_PPAIROE "1")
   (UNSPEC_PPAIRO "1")])
(define_int_attr rvp_pair_high
  [(UNSPEC_PPAIRE "0")
   (UNSPEC_PPAIREO "1")
   (UNSPEC_PPAIROE "0")
   (UNSPEC_PPAIRO "1")])
(define_int_attr rvp_pair_rv64_insn
  [(UNSPEC_PPAIRE "pack")
   (UNSPEC_PPAIREO "ppaireo.w")
   (UNSPEC_PPAIROE "ppairoe.w")
   (UNSPEC_PPAIRO "ppairo.w")])

; ---- 8x4 (PV4QI), 32-bit, single form ----
(define_insn "riscv_ppaire_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP"
  "ppaire.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppaire_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP"
  "ppaire.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppaireo_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PPAIREO))]
  "TARGET_RVP"
  "ppaireo.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppaireo_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PPAIREO))]
  "TARGET_RVP"
  "ppaireo.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairoe_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PPAIROE))]
  "TARGET_RVP"
  "ppairoe.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairoe_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PPAIROE))]
  "TARGET_RVP"
  "ppairoe.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairo_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PPAIRO))]
  "TARGET_RVP"
  "ppairo.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairo_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PPAIRO))]
  "TARGET_RVP"
  "ppairo.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

; ---- 16x2 (PV2HI), 32-bit ----
; ppaire: RV32 -> "pack" (alias), RV64 -> ppaire.h
(define_expand "riscv_ppaire_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_ppaire_u16x2_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_ppaire_u16x2_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_ppaire_u16x2_rv32"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP && !TARGET_64BIT"
  "pack\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppaire_u16x2_rv64"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_ppaire_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_ppaire_i16x2_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_ppaire_i16x2_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_ppaire_i16x2_rv32"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP && !TARGET_64BIT"
  "pack\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppaire_i16x2_rv64"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

; ppaireo/ppairoe/ppairo 16x2: single form (no RV32/RV64 mnemonic split)
(define_insn "riscv_ppaireo_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PPAIREO))]
  "TARGET_RVP"
  "ppaireo.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppaireo_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PPAIREO))]
  "TARGET_RVP"
  "ppaireo.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairoe_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PPAIROE))]
  "TARGET_RVP"
  "ppairoe.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairoe_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PPAIROE))]
  "TARGET_RVP"
  "ppairoe.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairo_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PPAIRO))]
  "TARGET_RVP"
  "ppairo.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairo_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PPAIRO))]
  "TARGET_RVP"
  "ppairo.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

; ---- 8x8 (PV8QI) and 16x4 (PV4HI), 64-bit: RV32 double-wide / RV64 single ----
; ppaire: RV64 -> ppaire.b/h, RV32 -> ppaire.db/dh
(define_expand "riscv_ppaire_<USAT_NAME>"
  [(set (match_operand:PAIR64 0 "register_operand")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand")
                        (match_operand:PAIR64 2 "register_operand")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_ppaire_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_ppaire_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_ppaire_<USAT_NAME>_rv32"
  [(set (match_operand:PAIR64 0 "register_operand" "=R")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppaire_<USAT_NAME>_rv64"
  [(set (match_operand:PAIR64 0 "register_operand" "=r")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

; ppaireo: RV64 -> ppaireo.b/h, RV32 -> ppaireo.db/dh
(define_expand "riscv_ppaireo_<USAT_NAME>"
  [(set (match_operand:PAIR64 0 "register_operand")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand")
                        (match_operand:PAIR64 2 "register_operand")]
         UNSPEC_PPAIREO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_ppaireo_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_ppaireo_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_ppaireo_<USAT_NAME>_rv32"
  [(set (match_operand:PAIR64 0 "register_operand" "=R")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIREO))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaireo.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppaireo_<USAT_NAME>_rv64"
  [(set (match_operand:PAIR64 0 "register_operand" "=r")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIREO))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaireo.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

; ppairoe: RV64 -> ppairoe.b/h, RV32 -> ppairoe.db/dh
(define_expand "riscv_ppairoe_<USAT_NAME>"
  [(set (match_operand:PAIR64 0 "register_operand")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand")
                        (match_operand:PAIR64 2 "register_operand")]
         UNSPEC_PPAIROE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_ppairoe_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_ppairoe_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_ppairoe_<USAT_NAME>_rv32"
  [(set (match_operand:PAIR64 0 "register_operand" "=R")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIROE))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairoe.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairoe_<USAT_NAME>_rv64"
  [(set (match_operand:PAIR64 0 "register_operand" "=r")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIROE))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairoe.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

; ppairo: RV64 -> ppairo.b/h, RV32 -> ppairo.db/dh
(define_expand "riscv_ppairo_<USAT_NAME>"
  [(set (match_operand:PAIR64 0 "register_operand")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand")
                        (match_operand:PAIR64 2 "register_operand")]
         UNSPEC_PPAIRO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_ppairo_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_ppairo_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_ppairo_<USAT_NAME>_rv32"
  [(set (match_operand:PAIR64 0 "register_operand" "=R")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIRO))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairo_<USAT_NAME>_rv64"
  [(set (match_operand:PAIR64 0 "register_operand" "=r")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIRO))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

; Signed 8x8/16x4 variants (same instructions, distinct builtin names).
(define_expand "riscv_ppaire_<SAT_NAME>"
  [(set (match_operand:PAIR64 0 "register_operand")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand")
                        (match_operand:PAIR64 2 "register_operand")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_ppaire_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_ppaire_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_ppaire_<SAT_NAME>_rv32"
  [(set (match_operand:PAIR64 0 "register_operand" "=R")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppaire_<SAT_NAME>_rv64"
  [(set (match_operand:PAIR64 0 "register_operand" "=r")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIRE))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_ppaireo_<SAT_NAME>"
  [(set (match_operand:PAIR64 0 "register_operand")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand")
                        (match_operand:PAIR64 2 "register_operand")]
         UNSPEC_PPAIREO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_ppaireo_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_ppaireo_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_ppaireo_<SAT_NAME>_rv32"
  [(set (match_operand:PAIR64 0 "register_operand" "=R")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIREO))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaireo.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppaireo_<SAT_NAME>_rv64"
  [(set (match_operand:PAIR64 0 "register_operand" "=r")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIREO))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaireo.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_ppairoe_<SAT_NAME>"
  [(set (match_operand:PAIR64 0 "register_operand")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand")
                        (match_operand:PAIR64 2 "register_operand")]
         UNSPEC_PPAIROE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_ppairoe_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_ppairoe_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_ppairoe_<SAT_NAME>_rv32"
  [(set (match_operand:PAIR64 0 "register_operand" "=R")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIROE))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairoe.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairoe_<SAT_NAME>_rv64"
  [(set (match_operand:PAIR64 0 "register_operand" "=r")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIROE))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairoe.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_ppairo_<SAT_NAME>"
  [(set (match_operand:PAIR64 0 "register_operand")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand")
                        (match_operand:PAIR64 2 "register_operand")]
         UNSPEC_PPAIRO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_ppairo_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_ppairo_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_ppairo_<SAT_NAME>_rv32"
  [(set (match_operand:PAIR64 0 "register_operand" "=R")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIRO))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_ppairo_<SAT_NAME>_rv64"
  [(set (match_operand:PAIR64 0 "register_operand" "=r")
        (unspec:PAIR64 [(match_operand:PAIR64 1 "register_operand" "r")
                        (match_operand:PAIR64 2 "register_operand" "r")]
         UNSPEC_PPAIRO))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

; ---- 32x2 (PV2SI), RV32 move expansion / RV64 native instruction ----
(define_expand "riscv_<rvp_pair_name>_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                       (match_operand:PV2SI 2 "register_operand")]
         RVP_PAIR_I32X2))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_<rvp_pair_name>_32x2_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      machine_mode mode = GET_MODE (operands[0]);
      rtx out_lo = operand_subword (operands[0], 0, 1, mode);
      rtx out_hi = operand_subword (operands[0], 1, 1, mode);
      rtx in_lo = operand_subword_force (operands[1], <rvp_pair_low>, mode);
      rtx in_hi = operand_subword_force (operands[2], <rvp_pair_high>, mode);
      emit_move_insn (out_lo, in_lo);
      emit_move_insn (out_hi, in_hi);
    }
  DONE;
})

(define_expand "riscv_<rvp_pair_name>_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                       (match_operand:PV2SI 2 "register_operand")]
         RVP_PAIR_I32X2))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_<rvp_pair_name>_32x2_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      machine_mode mode = GET_MODE (operands[0]);
      rtx out_lo = operand_subword (operands[0], 0, 1, mode);
      rtx out_hi = operand_subword (operands[0], 1, 1, mode);
      rtx in_lo = operand_subword_force (operands[1], <rvp_pair_low>, mode);
      rtx in_hi = operand_subword_force (operands[2], <rvp_pair_high>, mode);
      emit_move_insn (out_lo, in_lo);
      emit_move_insn (out_hi, in_hi);
    }
  DONE;
})

(define_insn "riscv_<rvp_pair_name>_32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                       (match_operand:PV2SI 2 "register_operand" "r")]
         RVP_PAIR_I32X2))]
  "TARGET_RVP && TARGET_64BIT"
  "<rvp_pair_rv64_insn>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Reverse
;
;RV32 stores a 64-bit packed vector in a register pair.  Reversing the full
;vector therefore also exchanges the two registers, in addition to reversing
;the elements within each register.

(define_mode_iterator RVP_PREV
  [PV4QI PV2HI PV8QI PV4HI PV2SI])
(define_mode_attr rvp_prev_suffix
  [(PV4QI "8x4")
   (PV2HI "16x2")
   (PV8QI "8x8")
   (PV4HI "16x4")
   (PV2SI "32x2")])
(define_mode_attr rvp_prev_unspec
  [(PV4QI "UNSPEC_PREV8")
   (PV2HI "UNSPEC_PREV16")
   (PV8QI "UNSPEC_PREV8")
   (PV4HI "UNSPEC_PREV16")
   (PV2SI "UNSPEC_PREV32")])

(define_expand "riscv_prev_i<rvp_prev_suffix>"
  [(set (match_operand:RVP_PREV 0 "register_operand")
	(unspec:RVP_PREV
	  [(match_operand:RVP_PREV 1 "register_operand")]
	  <rvp_prev_unspec>))]
  "TARGET_RVP"
{
  emit_insn (gen_riscv_prev_<rvp_prev_suffix> (operands[0], operands[1]));
  DONE;
})

(define_expand "riscv_prev_u<rvp_prev_suffix>"
  [(set (match_operand:RVP_PREV 0 "register_operand")
	(unspec:RVP_PREV
	  [(match_operand:RVP_PREV 1 "register_operand")]
	  <rvp_prev_unspec>))]
  "TARGET_RVP"
{
  emit_insn (gen_riscv_prev_<rvp_prev_suffix> (operands[0], operands[1]));
  DONE;
})

(define_expand "riscv_prev_8x4"
  [(set (match_operand:PV4QI 0 "register_operand")
	(unspec:PV4QI
	  [(match_operand:PV4QI 1 "register_operand")] UNSPEC_PREV8))]
  "TARGET_RVP"
{
  rtx out = gen_lowpart (SImode, operands[0]);
  rtx in = gen_lowpart (SImode, operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_prev_8x4_rv64 (out, in));
  else
    emit_insn (gen_riscv_prev_8x4_rv32 (out, in));
  DONE;
})

(define_insn "riscv_prev_8x4_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")]
	 UNSPEC_PREV8))]
  "TARGET_RVP && !TARGET_64BIT"
  "rev8\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_prev_8x4_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")]
	 UNSPEC_PREV8))]
  "TARGET_RVP && TARGET_64BIT"
  "rev8\t%0,%1\;srli\t%0,%0,32"
  [(set_attr "type" "simd")
   (set_attr "length" "8")])

(define_expand "riscv_prev_16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
	(unspec:PV2HI
	  [(match_operand:PV2HI 1 "register_operand")] UNSPEC_PREV16))]
  "TARGET_RVP"
{
  emit_insn (gen_riscv_prev_16x2_insn
	     (gen_lowpart (SImode, operands[0]),
	      gen_lowpart (SImode, operands[1])));
  DONE;
})

(define_insn "riscv_prev_16x2_insn"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")]
	 UNSPEC_PREV16))]
  "TARGET_RVP"
  "ppairoe.h\t%0,%1,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_prev_8x8"
  [(set (match_operand:PV8QI 0 "register_operand")
	(unspec:PV8QI
	  [(match_operand:PV8QI 1 "register_operand")] UNSPEC_PREV8))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_prev_8x8_rv64
	       (gen_lowpart (DImode, operands[0]),
		gen_lowpart (DImode, operands[1])));
  else
    {
      machine_mode mode = GET_MODE (operands[0]);
      rtx out_lo = operand_subword (operands[0], 0, 1, mode);
      rtx out_hi = operand_subword (operands[0], 1, 1, mode);
      rtx in_lo = operand_subword_force (operands[1], 0, mode);
      rtx in_hi = operand_subword_force (operands[1], 1, mode);
      emit_insn (gen_riscv_prev_8x4_rv32 (out_lo, in_hi));
      emit_insn (gen_riscv_prev_8x4_rv32 (out_hi, in_lo));
    }
  DONE;
})

(define_insn "riscv_prev_8x8_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r")]
	 UNSPEC_PREV8))]
  "TARGET_RVP && TARGET_64BIT"
  "rev8\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_prev_16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
	(unspec:PV4HI
	  [(match_operand:PV4HI 1 "register_operand")] UNSPEC_PREV16))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_prev_16x4_rv64
	       (gen_lowpart (DImode, operands[0]),
		gen_lowpart (DImode, operands[1])));
  else
    {
      machine_mode mode = GET_MODE (operands[0]);
      rtx out_lo = operand_subword (operands[0], 0, 1, mode);
      rtx out_hi = operand_subword (operands[0], 1, 1, mode);
      rtx in_lo = operand_subword_force (operands[1], 0, mode);
      rtx in_hi = operand_subword_force (operands[1], 1, mode);
      emit_insn (gen_riscv_prev_16x2_insn (out_lo, in_hi));
      emit_insn (gen_riscv_prev_16x2_insn (out_hi, in_lo));
    }
  DONE;
})

(define_insn "riscv_prev_16x4_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r")]
	 UNSPEC_PREV16))]
  "TARGET_RVP && TARGET_64BIT"
  "rev16\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_prev_32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
	(unspec:PV2SI
	  [(match_operand:PV2SI 1 "register_operand")] UNSPEC_PREV32))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_prev_32x2_rv64
	       (gen_lowpart (DImode, operands[0]),
		gen_lowpart (DImode, operands[1])));
  else
    {
      machine_mode mode = GET_MODE (operands[0]);
      rtx out_lo = operand_subword (operands[0], 0, 1, mode);
      rtx out_hi = operand_subword (operands[0], 1, 1, mode);
      rtx in_lo = operand_subword_force (operands[1], 0, mode);
      rtx in_hi = operand_subword_force (operands[1], 1, mode);
      emit_move_insn (out_lo, in_hi);
      emit_move_insn (out_hi, in_lo);
    }
  DONE;
})

(define_insn "riscv_prev_32x2_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r")]
	 UNSPEC_PREV32))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairoe.w\t%0,%1,%1"
  [(set_attr "type" "simd")])

;Packed Widening Convert
;
;pwcvt.* / pwcvtu.* / pwcvth.* are NOT real instructions; per the P-ext spec
;they are pseudoinstructions of the underlying widening instructions:
;  RV32:
;    pwcvt.b   rd_p, rs1 -> pwadd.b   rd_p, rs1, x0   (sign-extend widen)
;    pwcvt.h   rd_p, rs1 -> pwadd.h   rd_p, rs1, x0
;    pwcvtu.b  rd_p, rs1 -> wzip8p    rd_p, rs1, x0   (zero-extend widen)
;    pwcvtu.h  rd_p, rs1 -> wzip16p   rd_p, rs1, x0
;    pwcvth.b  rd_p, rs1 -> wzip8p    rd_p, x0, rs1   (high-half widen)
;    pwcvth.h  rd_p, rs1 -> wzip16p   rd_p, x0, rs1
;  RV64:
;    pwcvt.b   rd, rs1 -> zip8p  rd, rs1, x0  +  psext.h.b rd, rd
;    pwcvt.h   rd, rs1 -> zip16p rd, rs1, x0  +  psext.w.h rd, rd
;    pwcvtu.b  rd, rs1 -> zip8p  rd, rs1, x0
;    pwcvtu.h  rd, rs1 -> zip16p rd, rs1, x0
;    pwcvth.b  rd, rs1 -> zip8p  rd, x0, rs1
;    pwcvth.h  rd, rs1 -> zip16p rd, x0, rs1
;Hence the templates emit the underlying pwadd.b/wzip8p/zip8p/... forms rather
;than a (non-existent) pwcvt mnemonic.  The signed RV64 forms need two insns
;(zip for zero-extend widen, then psext for sign-extend), emitted via
;define_expand reusing the existing riscv_psext_*_rv64 patterns.

; pwcvt_i16x4 (signed b -> h, RV32 pwadd.b / RV64 zip8p + psext.h.b)
(define_expand "riscv_pwcvt_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand")]
         UNSPEC_PWCVT_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
        emit_insn (gen_riscv_pwcvt_i16x4_zip_rv64 (operands[0], operands[1]));
        emit_insn (gen_riscv_psext_b_i16x4_rv64 (operands[0], operands[0]));
    }
  else
    emit_insn (gen_riscv_pwcvt_i16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwcvt_i16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWCVT_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwadd.b\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwcvt_i16x4_zip_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWCVT_B))]
  "TARGET_RVP && TARGET_64BIT"
  "zip8p\t%0,%1,x0"
  [(set_attr "type" "simd")])

; pwcvt_i32x2 (signed h -> w, RV32 pwadd.h / RV64 zip16p + psext.w.h)
(define_expand "riscv_pwcvt_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand")]
         UNSPEC_PWCVT_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
        emit_insn (gen_riscv_pwcvt_i32x2_zip_rv64 (operands[0], operands[1]));
        emit_insn (gen_riscv_psext_h_i32x2_rv64 (operands[0], operands[0]));
    }
  else
    emit_insn (gen_riscv_pwcvt_i32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwcvt_i32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")]
         UNSPEC_PWCVT_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwadd.h\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwcvt_i32x2_zip_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")]
         UNSPEC_PWCVT_H))]
  "TARGET_RVP && TARGET_64BIT"
  "zip16p\t%0,%1,x0"
  [(set_attr "type" "simd")])

; pwcvtu_u16x4 (unsigned b -> h, RV32 wzip8p / RV64 zip8p)
(define_expand "riscv_pwcvtu_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand")]
         UNSPEC_PWCVTU_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwcvtu_u16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwcvtu_u16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwcvtu_u16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWCVTU_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip8p\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwcvtu_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWCVTU_B))]
  "TARGET_RVP && TARGET_64BIT"
  "zip8p\t%0,%1,x0"
  [(set_attr "type" "simd")])

; pwcvtu_u32x2 (unsigned h -> w, RV32 wzip16p / RV64 zip16p)
(define_expand "riscv_pwcvtu_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand")]
         UNSPEC_PWCVTU_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwcvtu_u32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwcvtu_u32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwcvtu_u32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")]
         UNSPEC_PWCVTU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip16p\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwcvtu_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")]
         UNSPEC_PWCVTU_H))]
  "TARGET_RVP && TARGET_64BIT"
  "zip16p\t%0,%1,x0"
  [(set_attr "type" "simd")])

; pwcvth_i16x4 / pwcvth_u16x4 (high-half b -> h, RV32 wzip8p / RV64 zip8p).
; Signed and unsigned share the same machine instruction (zero-extend widen of
; the high half); they differ only in the C-level element type, so both map to
; UNSPEC_PWCVTH_B but get distinct pattern names for their distinct builtins.
(define_expand "riscv_pwcvth_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand")]
         UNSPEC_PWCVTH_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwcvth_i16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwcvth_i16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwcvth_i16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWCVTH_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip8p\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwcvth_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWCVTH_B))]
  "TARGET_RVP && TARGET_64BIT"
  "zip8p\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwcvth_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand")]
         UNSPEC_PWCVTH_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwcvth_u16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwcvth_u16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwcvth_u16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWCVTH_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip8p\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwcvth_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWCVTH_B))]
  "TARGET_RVP && TARGET_64BIT"
  "zip8p\t%0,x0,%1"
  [(set_attr "type" "simd")])

; pwcvth_i32x2 / pwcvth_u32x2 (high-half h -> w, RV32 wzip16p / RV64 zip16p)
(define_expand "riscv_pwcvth_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand")]
         UNSPEC_PWCVTH_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwcvth_i32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwcvth_i32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwcvth_i32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")]
         UNSPEC_PWCVTH_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip16p\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwcvth_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")]
         UNSPEC_PWCVTH_H))]
  "TARGET_RVP && TARGET_64BIT"
  "zip16p\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwcvth_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand")]
         UNSPEC_PWCVTH_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwcvth_u32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwcvth_u32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwcvth_u32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")]
         UNSPEC_PWCVTH_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip16p\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwcvth_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")]
         UNSPEC_PWCVTH_H))]
  "TARGET_RVP && TARGET_64BIT"
  "zip16p\t%0,x0,%1"
  [(set_attr "type" "simd")])

;Packed Narrowing Convert
;
;pncvt.* / pncvth.* are NOT real instructions; per the P-ext spec they are
;pseudoinstructions of the underlying narrowing instructions:
;  RV32:
;    pncvt.b   rd, rs1_p -> pnsrli.b  rd, rs1_p, 0    (low half)
;    pncvt.h   rd, rs1_p -> pnsrli.h  rd, rs1_p, 0
;    pncvth.b  rd, rs1_p -> pnsrli.b  rd, rs1_p, 8    (high half)
;    pncvth.h  rd, rs1_p -> pnsrli.h  rd, rs1_p, 16
;  RV64:
;    pncvt.wb  rd, rs1 -> unzip8p   rd, rs1, x0
;    pncvt.wh  rd, rs1 -> unzip16p  rd, rs1, x0
;    pncvth.wb rd, rs1 -> unzip8hp  rd, rs1, x0
;    pncvth.wh rd, rs1 -> unzip16hp rd, rs1, x0
;Hence the templates emit the underlying pnsrli.b/unzip8p/... forms rather than
;a (non-existent) pncvt mnemonic.  This is the mirror of Packed Widening Convert
;(wide-in/narrow-out vs narrow-in/wide-out); each form is a single instruction,
;so no two-insn expand is needed.  Signed and unsigned variants share the same
;machine instruction and UNSPEC, differing only in the C-level element type;
;they get distinct pattern names for their distinct builtins.

; pncvt_i8x4 / pncvt_u8x4 (narrow h -> b, RV32 pnsrli.b,0 / RV64 unzip8p)
(define_expand "riscv_pncvt_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PNCVT_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pncvt_i8x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pncvt_i8x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pncvt_i8x4_rv32"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "R")]
         UNSPEC_PNCVT_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.b\t%0,%1,0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pncvt_i8x4_rv64"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PNCVT_B))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip8p\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_pncvt_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PNCVT_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pncvt_u8x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pncvt_u8x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pncvt_u8x4_rv32"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "R")]
         UNSPEC_PNCVT_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.b\t%0,%1,0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pncvt_u8x4_rv64"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PNCVT_B))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip8p\t%0,%1,x0"
  [(set_attr "type" "simd")])

; pncvt_i16x2 / pncvt_u16x2 (narrow w -> h, RV32 pnsrli.h,0 / RV64 unzip16p)
(define_expand "riscv_pncvt_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand")]
         UNSPEC_PNCVT_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pncvt_i16x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pncvt_i16x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pncvt_i16x2_rv32"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "R")]
         UNSPEC_PNCVT_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.h\t%0,%1,0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pncvt_i16x2_rv64"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "r")]
         UNSPEC_PNCVT_H))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip16p\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_pncvt_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand")]
         UNSPEC_PNCVT_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pncvt_u16x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pncvt_u16x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pncvt_u16x2_rv32"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "R")]
         UNSPEC_PNCVT_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.h\t%0,%1,0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pncvt_u16x2_rv64"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "r")]
         UNSPEC_PNCVT_H))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip16p\t%0,%1,x0"
  [(set_attr "type" "simd")])

; pncvth_i8x4 / pncvth_u8x4 (high-half h -> b, RV32 pnsrli.b,8 / RV64 unzip8hp)
(define_expand "riscv_pncvth_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PNCVTH_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pncvth_i8x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pncvth_i8x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pncvth_i8x4_rv32"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "R")]
         UNSPEC_PNCVTH_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.b\t%0,%1,8"
  [(set_attr "type" "simd")])

(define_insn "riscv_pncvth_i8x4_rv64"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PNCVTH_B))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip8hp\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_pncvth_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PNCVTH_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pncvth_u8x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pncvth_u8x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pncvth_u8x4_rv32"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "R")]
         UNSPEC_PNCVTH_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.b\t%0,%1,8"
  [(set_attr "type" "simd")])

(define_insn "riscv_pncvth_u8x4_rv64"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PNCVTH_B))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip8hp\t%0,%1,x0"
  [(set_attr "type" "simd")])

; pncvth_i16x2 / pncvth_u16x2 (high-half w -> h, RV32 pnsrli.h,16 / RV64 unzip16hp)
(define_expand "riscv_pncvth_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand")]
         UNSPEC_PNCVTH_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pncvth_i16x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pncvth_i16x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pncvth_i16x2_rv32"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "R")]
         UNSPEC_PNCVTH_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.h\t%0,%1,16"
  [(set_attr "type" "simd")])

(define_insn "riscv_pncvth_i16x2_rv64"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "r")]
         UNSPEC_PNCVTH_H))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip16hp\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_pncvth_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand")]
         UNSPEC_PNCVTH_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pncvth_u16x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pncvth_u16x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pncvth_u16x2_rv32"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "R")]
         UNSPEC_PNCVTH_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.h\t%0,%1,16"
  [(set_attr "type" "simd")])

(define_insn "riscv_pncvth_u16x2_rv64"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "r")]
         UNSPEC_PNCVTH_H))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip16hp\t%0,%1,x0"
  [(set_attr "type" "simd")])

;Packed Zip
;
;pzip interleaves two narrow sources (32-bit each) into one wide result
;(64-bit): two PV4QI -> PV8QI, or two PV2HI -> PV4HI.
;  RV32: wzip8p/wzip16p rd_p, rs1, rs2  (result in even-odd register pair)
;  RV64: zip8p/zip16p   rd,   rs1, rs2  (result in a single register)
;Signed and unsigned variants share the same machine instruction and UNSPEC,
;differing only in the C-level element type; they get distinct pattern names.

; pzip_i8x8 / pzip_u8x8 (two PV4QI -> PV8QI)
(define_expand "riscv_pzip_i8x8"
  [(set (match_operand:PV8QI 0 "register_operand")
        (unspec:PV8QI [(match_operand:PV4QI 1 "register_operand")
                      (match_operand:PV4QI 2 "register_operand")]
         UNSPEC_PZIP_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pzip_i8x8_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pzip_i8x8_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pzip_i8x8_rv32"
  [(set (match_operand:PV8QI 0 "register_operand" "=R")
        (unspec:PV8QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PZIP_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip8p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pzip_i8x8_rv64"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (unspec:PV8QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PZIP_B))]
  "TARGET_RVP && TARGET_64BIT"
  "zip8p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pzip_u8x8"
  [(set (match_operand:PV8QI 0 "register_operand")
        (unspec:PV8QI [(match_operand:PV4QI 1 "register_operand")
                      (match_operand:PV4QI 2 "register_operand")]
         UNSPEC_PZIP_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pzip_u8x8_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pzip_u8x8_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pzip_u8x8_rv32"
  [(set (match_operand:PV8QI 0 "register_operand" "=R")
        (unspec:PV8QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PZIP_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip8p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pzip_u8x8_rv64"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (unspec:PV8QI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PZIP_B))]
  "TARGET_RVP && TARGET_64BIT"
  "zip8p\t%0,%1,%2"
  [(set_attr "type" "simd")])

; pzip_i16x4 / pzip_u16x4 (two PV2HI -> PV4HI)
(define_expand "riscv_pzip_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV2HI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PZIP_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pzip_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pzip_i16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pzip_i16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PZIP_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip16p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pzip_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PZIP_H))]
  "TARGET_RVP && TARGET_64BIT"
  "zip16p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pzip_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV2HI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PZIP_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pzip_u16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pzip_u16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pzip_u16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PZIP_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip16p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pzip_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PZIP_H))]
  "TARGET_RVP && TARGET_64BIT"
  "zip16p\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Unzip
;
;punzipe/punzipo de-interleave one wide source (64-bit) into one narrow result
;(32-bit): PV8QI -> PV4QI, or PV4HI -> PV2HI.  They share the underlying machine
;instructions with pncvt/pncvth (narrowing convert), but take a different input
;mode (the 8x8/16x4 wide form rather than 16x4/32x2), so they need their own
;patterns.  Mapping (same as pncvt/pncvth):
;  RV32:
;    punzipe.b  rd, rs1_p -> pnsrli.b  rd, rs1_p, 0   (even half)
;    punzipo.b  rd, rs1_p -> pnsrli.b  rd, rs1_p, 8   (odd half)
;    punzipe.h  rd, rs1_p -> pnsrli.h  rd, rs1_p, 0
;    punzipo.h  rd, rs1_p -> pnsrli.h  rd, rs1_p, 16
;  RV64:
;    punzipe.wb rd, rs1 -> unzip8p   rd, rs1, x0
;    punzipo.wb rd, rs1 -> unzip8hp  rd, rs1, x0
;    punzipe.wh rd, rs1 -> unzip16p  rd, rs1, x0
;    punzipo.wh rd, rs1 -> unzip16hp rd, rs1, x0
;Signed and unsigned variants share the same machine instruction and UNSPEC,
;differing only in the C-level element type; they get distinct pattern names.

; punzipe_i8x4 / punzipe_u8x4 (PV8QI -> PV4QI, even half)
(define_expand "riscv_punzipe_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PUNZIPE_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_punzipe_i8x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_punzipe_i8x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_punzipe_i8x4_rv32"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand" "R")]
         UNSPEC_PUNZIPE_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.b\t%0,%1,0"
  [(set_attr "type" "simd")])

(define_insn "riscv_punzipe_i8x4_rv64"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PUNZIPE_B))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip8p\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_punzipe_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PUNZIPE_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_punzipe_u8x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_punzipe_u8x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_punzipe_u8x4_rv32"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand" "R")]
         UNSPEC_PUNZIPE_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.b\t%0,%1,0"
  [(set_attr "type" "simd")])

(define_insn "riscv_punzipe_u8x4_rv64"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PUNZIPE_B))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip8p\t%0,%1,x0"
  [(set_attr "type" "simd")])

; punzipo_i8x4 / punzipo_u8x4 (PV8QI -> PV4QI, odd half)
(define_expand "riscv_punzipo_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PUNZIPO_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_punzipo_i8x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_punzipo_i8x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_punzipo_i8x4_rv32"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand" "R")]
         UNSPEC_PUNZIPO_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.b\t%0,%1,8"
  [(set_attr "type" "simd")])

(define_insn "riscv_punzipo_i8x4_rv64"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PUNZIPO_B))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip8hp\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_punzipo_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PUNZIPO_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_punzipo_u8x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_punzipo_u8x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_punzipo_u8x4_rv32"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand" "R")]
         UNSPEC_PUNZIPO_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.b\t%0,%1,8"
  [(set_attr "type" "simd")])

(define_insn "riscv_punzipo_u8x4_rv64"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PUNZIPO_B))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip8hp\t%0,%1,x0"
  [(set_attr "type" "simd")])

; punzipe_i16x2 / punzipe_u16x2 (PV4HI -> PV2HI, even half)
(define_expand "riscv_punzipe_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PUNZIPE_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_punzipe_i16x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_punzipe_i16x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_punzipe_i16x2_rv32"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand" "R")]
         UNSPEC_PUNZIPE_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.h\t%0,%1,0"
  [(set_attr "type" "simd")])

(define_insn "riscv_punzipe_i16x2_rv64"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PUNZIPE_H))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip16p\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_punzipe_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PUNZIPE_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_punzipe_u16x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_punzipe_u16x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_punzipe_u16x2_rv32"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand" "R")]
         UNSPEC_PUNZIPE_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.h\t%0,%1,0"
  [(set_attr "type" "simd")])

(define_insn "riscv_punzipe_u16x2_rv64"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PUNZIPE_H))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip16p\t%0,%1,x0"
  [(set_attr "type" "simd")])

; punzipo_i16x2 / punzipo_u16x2 (PV4HI -> PV2HI, odd half)
(define_expand "riscv_punzipo_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PUNZIPO_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_punzipo_i16x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_punzipo_i16x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_punzipo_i16x2_rv32"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand" "R")]
         UNSPEC_PUNZIPO_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.h\t%0,%1,16"
  [(set_attr "type" "simd")])

(define_insn "riscv_punzipo_i16x2_rv64"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PUNZIPO_H))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip16hp\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_punzipo_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PUNZIPO_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_punzipo_u16x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_punzipo_u16x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_punzipo_u16x2_rv32"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand" "R")]
         UNSPEC_PUNZIPO_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pnsrli.h\t%0,%1,16"
  [(set_attr "type" "simd")])

(define_insn "riscv_punzipo_u16x2_rv64"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PUNZIPO_H))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip16hp\t%0,%1,x0"
  [(set_attr "type" "simd")])

;Packed Narrowing Zip
;
;pnzip/pnziph narrow two wide sources into one narrow result by pairing the low
;byte/halfword of corresponding elements: two PV2HI -> PV4QI (32-bit), or two
;PV4HI/PV2SI -> PV8QI/PV4HI (64-bit).  They share the ppaire/ppairo machine
;instructions with Packed Pair, but take wider input modes (the 16x2/16x4/32x2
;form rather than 8x4/8x8/16x4), so they need their own patterns.
;  pnzip  (even-pair) -> ppaire.b/h/db/dh
;  pnziph (odd-pair)  -> ppairo.b/h/db/dh
;Mapping:
;  32-bit (PV2HI -> PV4QI, single register, both ISAs): ppaire.b / ppairo.b
;  64-bit RV32 (PV4HI->PV8QI, PV2SI->PV4HI, register pairs): ppaire.db/dh, ppairo.db/dh
;  64-bit RV64 (PV4HI->PV8QI, PV2SI->PV4HI, single register): ppaire.b/h, ppairo.b/h
;Signed and unsigned variants share the same machine instruction and UNSPEC,
;differing only in the C-level element type; they get distinct pattern names.

; ---- 32-bit (PV2HI + PV2HI -> PV4QI), single form, both ISAs ----
(define_insn "riscv_pnzip_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PNZIP_B))]
  "TARGET_RVP"
  "ppaire.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pnzip_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PNZIP_B))]
  "TARGET_RVP"
  "ppaire.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pnziph_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PNZIPH_B))]
  "TARGET_RVP"
  "ppairo.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pnziph_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PNZIPH_B))]
  "TARGET_RVP"
  "ppairo.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

; ---- 64-bit (PV4HI + PV4HI -> PV8QI), RV32 ppaire.db / RV64 ppaire.b ----
(define_expand "riscv_pnzip_i8x8"
  [(set (match_operand:PV8QI 0 "register_operand")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PNZIP_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnzip_i8x8_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pnzip_i8x8_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pnzip_i8x8_rv32"
  [(set (match_operand:PV8QI 0 "register_operand" "=R")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PNZIP_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.db\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pnzip_i8x8_rv64"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PNZIP_B))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pnzip_u8x8"
  [(set (match_operand:PV8QI 0 "register_operand")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PNZIP_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnzip_u8x8_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pnzip_u8x8_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pnzip_u8x8_rv32"
  [(set (match_operand:PV8QI 0 "register_operand" "=R")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PNZIP_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.db\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pnzip_u8x8_rv64"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PNZIP_B))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pnziph_i8x8"
  [(set (match_operand:PV8QI 0 "register_operand")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PNZIPH_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnziph_i8x8_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pnziph_i8x8_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pnziph_i8x8_rv32"
  [(set (match_operand:PV8QI 0 "register_operand" "=R")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PNZIPH_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.db\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pnziph_i8x8_rv64"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PNZIPH_B))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pnziph_u8x8"
  [(set (match_operand:PV8QI 0 "register_operand")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PNZIPH_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnziph_u8x8_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pnziph_u8x8_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pnziph_u8x8_rv32"
  [(set (match_operand:PV8QI 0 "register_operand" "=R")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PNZIPH_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.db\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pnziph_u8x8_rv64"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (unspec:PV8QI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PNZIPH_B))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

; ---- 64-bit (PV2SI + PV2SI -> PV4HI), RV32 ppaire.dh / RV64 ppaire.h ----
(define_expand "riscv_pnzip_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PNZIP_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnzip_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pnzip_i16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pnzip_i16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PNZIP_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.dh\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pnzip_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PNZIP_H))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pnzip_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PNZIP_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnzip_u16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pnzip_u16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pnzip_u16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PNZIP_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.dh\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pnzip_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PNZIP_H))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pnziph_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PNZIPH_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnziph_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pnziph_i16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pnziph_i16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PNZIPH_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.dh\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pnziph_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PNZIPH_H))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pnziph_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PNZIPH_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnziph_u16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pnziph_u16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pnziph_u16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PNZIPH_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.dh\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pnziph_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PNZIPH_H))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Widening Unzip
;
;pwunzip* widen one narrow source (32-bit) into one wide result (64-bit) by
;de-interleaving: PV4QI -> PV2HI (32-bit), PV8QI -> PV4HI / PV4HI -> PV2SI (64-bit).
;Six variants, each maps to a different underlying instruction:
;  pwunzipe  (even, signed)   -> psext.h.b / psext.w.h / psext.dh.b / psext.dw.h
;  pwunzipo  (odd,  signed)   -> psrai.h,8 / psrai.w,16 / psrai.dh,8 / psrai.dw,16
;  pwunzipue (even, unsigned) -> ppaire.b %0,%1,x0  / ppaire.h %0,%1,x0  (rs2=0)
;  pwunzipuo (odd,  unsigned) -> ppairo.b %0,%1,x0 / ppairo.h %0,%1,x0 (rs2=0)
;  pwunziphe (high-even)      -> pslli.h,8 / pslli.w,16 / pslli.dh,8 / pslli.dw,16
;  pwunzipho (high-odd)       -> ppairo.b %0,x0,%1 / ppairo.h %0,x0,%1 (rs1=0)
;Signed and unsigned variants share the same machine instruction and UNSPEC
;for e/o (psext/psrai are inherently sign-aware, ue/uo use ppaire/ppairo which
;are sign-agnostic), differing only in the C-level element type; they get
;distinct pattern names.  Immediates (8/16) are written literally into the
;template, not passed as operands.

; ---- 32-bit (PV4QI -> PV2HI), single form, both ISAs (constraint d,s) ----
(define_insn "riscv_pwunzipe_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPE))]
  "TARGET_RVP"
  "psext.h.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipo_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPO))]
  "TARGET_RVP"
  "psrai.h\t%0,%1,8"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipue_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPUE))]
  "TARGET_RVP"
  "ppaire.b\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipuo_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPUO))]
  "TARGET_RVP"
  "ppairo.b\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunziphe_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP"
  "pslli.h\t%0,%1,8"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunziphe_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP"
  "pslli.h\t%0,%1,8"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipho_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP"
  "ppairo.b\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipho_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP"
  "ppairo.b\t%0,x0,%1"
  [(set_attr "type" "simd")])

; ---- 64-bit (PV8QI -> PV4HI), RV32 psext.dh.b etc / RV64 psext.h.b etc ----
; pwunzipe_i16x4 (signed even -> psext)
(define_expand "riscv_pwunzipe_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PWUNZIPE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipe_i16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipe_i16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipe_i16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPE))]
  "TARGET_RVP && !TARGET_64BIT"
  "psext.dh.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipe_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPE))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.h.b\t%0,%1"
  [(set_attr "type" "simd")])

; pwunzipo_i16x4 (signed odd -> psrai.h,8 / psrai.dh,8)
(define_expand "riscv_pwunzipo_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PWUNZIPO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipo_i16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipo_i16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipo_i16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPO))]
  "TARGET_RVP && !TARGET_64BIT"
  "psrai.dh\t%0,%1,8"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipo_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPO))]
  "TARGET_RVP && TARGET_64BIT"
  "psrai.h\t%0,%1,8"
  [(set_attr "type" "simd")])

; pwunzipue_u16x4 (unsigned even -> ppaire.b,rs2=0 / ppaire.db,rs2_p=0)
(define_expand "riscv_pwunzipue_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PWUNZIPUE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipue_u16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipue_u16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipue_u16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPUE))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.db\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipue_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPUE))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.b\t%0,%1,x0"
  [(set_attr "type" "simd")])

; pwunzipuo_u16x4 (unsigned odd -> ppairo.b,rs2=0 / ppairo.db,rs2_p=0)
(define_expand "riscv_pwunzipuo_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PWUNZIPUO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipuo_u16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipuo_u16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipuo_u16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPUO))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.db\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipuo_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPUO))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.b\t%0,%1,x0"
  [(set_attr "type" "simd")])

; pwunziphe_i16x4 (signed/unsigned high-even -> pslli.h,8 / pslli.dh,8)
(define_expand "riscv_pwunziphe_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunziphe_i16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunziphe_i16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunziphe_i16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP && !TARGET_64BIT"
  "pslli.dh\t%0,%1,8"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunziphe_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP && TARGET_64BIT"
  "pslli.h\t%0,%1,8"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwunziphe_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunziphe_u16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunziphe_u16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunziphe_u16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP && !TARGET_64BIT"
  "pslli.dh\t%0,%1,8"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunziphe_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP && TARGET_64BIT"
  "pslli.h\t%0,%1,8"
  [(set_attr "type" "simd")])

; pwunzipho_i16x4 (signed/unsigned high-odd -> ppairo.b,rs1=0 / ppairo.db,rs1_p=0)
(define_expand "riscv_pwunzipho_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipho_i16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipho_i16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipho_i16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.db\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipho_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.b\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwunzipho_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipho_u16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipho_u16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipho_u16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.db\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipho_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.b\t%0,x0,%1"
  [(set_attr "type" "simd")])

; ---- 64-bit (PV4HI -> PV2SI), RV32 psext.dw.h etc / RV64 psext.w.h etc ----
; pwunzipe_i32x2 (signed even -> psext.w.h / psext.dw.h)
(define_expand "riscv_pwunzipe_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PWUNZIPE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipe_i32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipe_i32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipe_i32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPE))]
  "TARGET_RVP && !TARGET_64BIT"
  "psext.dw.h\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipe_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPE))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.w.h\t%0,%1"
  [(set_attr "type" "simd")])

; pwunzipo_i32x2 (signed odd -> psrai.w,16 / psrai.dw,16)
(define_expand "riscv_pwunzipo_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PWUNZIPO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipo_i32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipo_i32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipo_i32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPO))]
  "TARGET_RVP && !TARGET_64BIT"
  "psrai.dw\t%0,%1,16"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipo_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPO))]
  "TARGET_RVP && TARGET_64BIT"
  "psrai.w\t%0,%1,16"
  [(set_attr "type" "simd")])

; pwunzipue_u32x2 (unsigned even -> ppaire.h,rs2=0 / ppaire.dh,rs2_p=0)
(define_expand "riscv_pwunzipue_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PWUNZIPUE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipue_u32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipue_u32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipue_u32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPUE))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.dh\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipue_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPUE))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0,%1,x0"
  [(set_attr "type" "simd")])

; pwunzipuo_u32x2 (unsigned odd -> ppairo.h,rs2=0 / ppairo.dh,rs2_p=0)
(define_expand "riscv_pwunzipuo_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PWUNZIPUO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipuo_u32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipuo_u32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipuo_u32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPUO))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.dh\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipuo_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPUO))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.h\t%0,%1,x0"
  [(set_attr "type" "simd")])

; pwunziphe_i32x2 (signed/unsigned high-even -> pslli.w,16 / pslli.dw,16)
(define_expand "riscv_pwunziphe_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunziphe_i32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunziphe_i32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunziphe_i32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP && !TARGET_64BIT"
  "pslli.dw\t%0,%1,16"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunziphe_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP && TARGET_64BIT"
  "pslli.w\t%0,%1,16"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwunziphe_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunziphe_u32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunziphe_u32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunziphe_u32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP && !TARGET_64BIT"
  "pslli.dw\t%0,%1,16"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunziphe_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHE))]
  "TARGET_RVP && TARGET_64BIT"
  "pslli.w\t%0,%1,16"
  [(set_attr "type" "simd")])

; pwunzipho_i32x2 (signed/unsigned high-odd -> ppairo.h,rs1=0 / ppairo.dh,rs1_p=0)
(define_expand "riscv_pwunzipho_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipho_i32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipho_i32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipho_i32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.dh\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipho_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.h\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwunzipho_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pwunzipho_u32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pwunzipho_u32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pwunzipho_u32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppairo.dh\t%0,x0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwunzipho_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PWUNZIPHO))]
  "TARGET_RVP && TARGET_64BIT"
  "ppairo.h\t%0,x0,%1"
  [(set_attr "type" "simd")])
