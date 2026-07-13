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
;Packed Minimum and Maximum
;
; pmin/pmax perform signed element-wise min/max; pminu/pmaxu the unsigned
; variants.  Suffixes follow the same scheme as padd: 32-bit types use
; .b/.h, 64-bit types use .b/.h/.w on RV64 and .db/.dh/.dw on RV32.

;--- PMIN (signed minimum) ---

(define_insn "riscv_pmin_<SAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PMIN))]
  "TARGET_RVP"
  "pmin.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmin_<SAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMIN))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmin_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmin_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pmin_<SAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMIN))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmin.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmin_<SAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMIN))]
  "TARGET_RVP && TARGET_64BIT"
  "pmin.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- PMAX (signed maximum) ---

(define_insn "riscv_pmax_<SAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PMAX))]
  "TARGET_RVP"
  "pmax.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmax_<SAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMAX))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmax_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmax_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pmax_<SAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMAX))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmax.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmax_<SAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMAX))]
  "TARGET_RVP && TARGET_64BIT"
  "pmax.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- PMINU (unsigned minimum) ---

(define_insn "riscv_pminu_<USAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PMINU))]
  "TARGET_RVP"
  "pminu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pminu_<USAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMINU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pminu_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pminu_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pminu_<USAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMINU))]
  "TARGET_RVP && !TARGET_64BIT"
  "pminu.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pminu_<USAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMINU))]
  "TARGET_RVP && TARGET_64BIT"
  "pminu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- PMAXU (unsigned maximum) ---

(define_insn "riscv_pmaxu_<USAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PMAXU))]
  "TARGET_RVP"
  "pmaxu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmaxu_<USAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMAXU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmaxu_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmaxu_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pmaxu_<USAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMAXU))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmaxu.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmaxu_<USAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMAXU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmaxu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Comparison
;
; All comparisons yield an unsigned result.  pmseq is sign-agnostic so the
; signed/unsigned input variants share the pmseq instruction; pmslt/pmsgt take
; signed inputs, pmsltu/pmsgtu take unsigned inputs.  Derived predicates
; (pmsne/pmsge/pmsle/pmsgeu/pmsleu) are expanded as the base comparison
; followed by bitwise NOT (xori -1).  On RV32, 64-bit results live in a
; register pair so the NOT is applied to both halves (two not instructions).

;--- PMSEQ (==), signed input variant ---

(define_insn "riscv_pmseq_<PCMP_SNAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP"
  "pmseq.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmseq_<PCMP_SNAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmseq_<PCMP_SNAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmseq_<PCMP_SNAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pmseq_<PCMP_SNAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmseq.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmseq_<PCMP_SNAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP && TARGET_64BIT"
  "pmseq.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- PMSEQ (==), unsigned input variant (same instruction) ---

(define_insn "riscv_pmseq_<PCMP_UNAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP"
  "pmseq.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmseq_<PCMP_UNAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmseq_<PCMP_UNAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmseq_<PCMP_UNAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pmseq_<PCMP_UNAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmseq.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmseq_<PCMP_UNAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP && TARGET_64BIT"
  "pmseq.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- PMSLT (<, signed) ---

(define_insn "riscv_pmslt_<PCMP_ONAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PMSLT))]
  "TARGET_RVP"
  "pmslt.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmslt_<PCMP_ONAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSLT))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmslt_<PCMP_ONAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmslt_<PCMP_ONAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pmslt_<PCMP_ONAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSLT))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmslt.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmslt_<PCMP_ONAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSLT))]
  "TARGET_RVP && TARGET_64BIT"
  "pmslt.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- PMSGT (>, signed) ---

(define_insn "riscv_pmsgt_<PCMP_ONAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PMSGT))]
  "TARGET_RVP"
  "pmsgt.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmsgt_<PCMP_ONAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSGT))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmsgt_<PCMP_ONAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmsgt_<PCMP_ONAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pmsgt_<PCMP_ONAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSGT))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmsgt.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmsgt_<PCMP_ONAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSGT))]
  "TARGET_RVP && TARGET_64BIT"
  "pmsgt.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- PMSLTU (<, unsigned) ---

(define_insn "riscv_pmsltu_<PCMP_ONAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PMSLTU))]
  "TARGET_RVP"
  "pmsltu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmsltu_<PCMP_ONAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSLTU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmsltu_<PCMP_ONAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmsltu_<PCMP_ONAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pmsltu_<PCMP_ONAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSLTU))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmsltu.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmsltu_<PCMP_ONAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSLTU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmsltu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- PMSGTU (>, unsigned) ---

(define_insn "riscv_pmsgtu_<PCMP_ONAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PMSGTU))]
  "TARGET_RVP"
  "pmsgtu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmsgtu_<PCMP_ONAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSGTU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmsgtu_<PCMP_ONAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmsgtu_<PCMP_ONAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pmsgtu_<PCMP_ONAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSGTU))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmsgtu.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmsgtu_<PCMP_ONAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PMSGTU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmsgtu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- PMSNE (!=, = pmseq + not), signed input variant ---

(define_expand "riscv_pmsne_<PCMP_SNAME>"
  [(set (match_operand:SAT32 0 "register_operand")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand")
                       (match_operand:SAT32 2 "register_operand")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  emit_insn (gen_riscv_pmseq_<PCMP_SNAME> (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

(define_expand "riscv_pmsne_<PCMP_SNAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmseq_<PCMP_SNAME>_rv64 (tmp, operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmseq_<PCMP_SNAME>_rv32 (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

;--- PMSNE (!=, = pmseq + not), unsigned input variant ---

(define_expand "riscv_pmsne_<PCMP_UNAME>"
  [(set (match_operand:SAT32 0 "register_operand")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand")
                       (match_operand:SAT32 2 "register_operand")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  emit_insn (gen_riscv_pmseq_<PCMP_UNAME> (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

(define_expand "riscv_pmsne_<PCMP_UNAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSEQ))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmseq_<PCMP_UNAME>_rv64 (tmp, operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmseq_<PCMP_UNAME>_rv32 (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

;--- PMSGE (>=, = pmslt + not), signed ---

(define_expand "riscv_pmsge_<PCMP_ONAME>"
  [(set (match_operand:SAT32 0 "register_operand")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand")
                       (match_operand:SAT32 2 "register_operand")]
         UNSPEC_PMSLT))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  emit_insn (gen_riscv_pmslt_<PCMP_ONAME> (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

(define_expand "riscv_pmsge_<PCMP_ONAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSLT))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmslt_<PCMP_ONAME>_rv64 (tmp, operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmslt_<PCMP_ONAME>_rv32 (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

;--- PMSLE (<=, = pmsgt + not), signed ---

(define_expand "riscv_pmsle_<PCMP_ONAME>"
  [(set (match_operand:SAT32 0 "register_operand")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand")
                       (match_operand:SAT32 2 "register_operand")]
         UNSPEC_PMSGT))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  emit_insn (gen_riscv_pmsgt_<PCMP_ONAME> (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

(define_expand "riscv_pmsle_<PCMP_ONAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSGT))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmsgt_<PCMP_ONAME>_rv64 (tmp, operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmsgt_<PCMP_ONAME>_rv32 (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

;--- PMSGEU (>=, = pmsltu + not), unsigned ---

(define_expand "riscv_pmsgeu_<PCMP_ONAME>"
  [(set (match_operand:SAT32 0 "register_operand")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand")
                       (match_operand:SAT32 2 "register_operand")]
         UNSPEC_PMSLTU))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  emit_insn (gen_riscv_pmsltu_<PCMP_ONAME> (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

(define_expand "riscv_pmsgeu_<PCMP_ONAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSLTU))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmsltu_<PCMP_ONAME>_rv64 (tmp, operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmsltu_<PCMP_ONAME>_rv32 (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

;--- PMSLEU (<=, = pmsgtu + not), unsigned ---

(define_expand "riscv_pmsleu_<PCMP_ONAME>"
  [(set (match_operand:SAT32 0 "register_operand")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand")
                       (match_operand:SAT32 2 "register_operand")]
         UNSPEC_PMSGTU))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  emit_insn (gen_riscv_pmsgtu_<PCMP_ONAME> (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

(define_expand "riscv_pmsleu_<PCMP_ONAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PMSGTU))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (<MODE>mode);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmsgtu_<PCMP_ONAME>_rv64 (tmp, operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pmsgtu_<PCMP_ONAME>_rv32 (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, <MODE>mode);
  DONE;
})

;Packed Merge

(define_insn "riscv_pmerge_si"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r,0,r")
                    (match_operand:SI 2 "register_operand" "r,r,0")
                    (match_operand:SI 3 "register_operand" "0,r,r")]
         UNSPEC_PMERGE))]
  "TARGET_RVP"
  "@
   merge\t%0,%1,%2
   mvm\t%0,%2,%3
   mvmn\t%0,%1,%3"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmerge_<UPMERGE_NAME>"
  [(set (match_operand:PMERGE32 0 "register_operand" "=r,r,r")
        (unspec:PMERGE32 [(match_operand:PMERGE32 1 "register_operand" "r,0,r")
                          (match_operand:PMERGE32 2 "register_operand" "r,r,0")
                          (match_operand:PMERGE32 3 "register_operand" "0,r,r")]
         UNSPEC_PMERGE))]
  "TARGET_RVP"
  "@
   merge\t%0,%1,%2
   mvm\t%0,%2,%3
   mvmn\t%0,%1,%3"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmerge_<PMERGE_NAME>"
  [(set (match_operand:PMERGE32 0 "register_operand" "=r,r,r")
        (unspec:PMERGE32 [(match_operand:PMERGE32 1 "register_operand" "r,0,r")
                          (match_operand:PMERGE32 2 "register_operand" "r,r,0")
                          (match_operand:PMERGE32 3 "register_operand" "0,r,r")]
         UNSPEC_PMERGE))]
  "TARGET_RVP"
  "@
   merge\t%0,%1,%2
   mvm\t%0,%2,%3
   mvmn\t%0,%1,%3"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmerge_<UPMERGE_NAME>"
  [(set (match_operand:PMERGE64 0 "register_operand")
        (unspec:PMERGE64 [(match_operand:PMERGE64 1 "register_operand")
                          (match_operand:PMERGE64 2 "register_operand")
                          (match_operand:PMERGE64 3 "register_operand")]
         UNSPEC_PMERGE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmerge_<UPMERGE_NAME>_rv64
		 (operands[0], operands[1], operands[2], operands[3]));
  else
    {
      machine_mode mode = GET_MODE (operands[0]);
      rtx out0 = operand_subword (operands[0], 0, 1, mode);
      rtx out1 = operand_subword (operands[0], 1, 1, mode);
      rtx rs10 = operand_subword_force (operands[1], 0, mode);
      rtx rs11 = operand_subword_force (operands[1], 1, mode);
      rtx rs20 = operand_subword_force (operands[2], 0, mode);
      rtx rs21 = operand_subword_force (operands[2], 1, mode);
      rtx mask0 = operand_subword_force (operands[3], 0, mode);
      rtx mask1 = operand_subword_force (operands[3], 1, mode);

      emit_insn (gen_riscv_pmerge_si (out0, rs10, rs20, mask0));
      emit_insn (gen_riscv_pmerge_si (out1, rs11, rs21, mask1));
    }
  DONE;
})

(define_insn "riscv_pmerge_<UPMERGE_NAME>_rv64"
  [(set (match_operand:PMERGE64 0 "register_operand" "=r,r,r")
        (unspec:PMERGE64 [(match_operand:PMERGE64 1 "register_operand" "r,0,r")
                          (match_operand:PMERGE64 2 "register_operand" "r,r,0")
                          (match_operand:PMERGE64 3 "register_operand" "0,r,r")]
         UNSPEC_PMERGE))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   merge\t%0,%1,%2
   mvm\t%0,%2,%3
   mvmn\t%0,%1,%3"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmerge_<PMERGE_NAME>"
  [(set (match_operand:PMERGE64 0 "register_operand")
        (unspec:PMERGE64 [(match_operand:PMERGE64 1 "register_operand")
                          (match_operand:PMERGE64 2 "register_operand")
                          (match_operand:PMERGE64 3 "register_operand")]
         UNSPEC_PMERGE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmerge_<PMERGE_NAME>_rv64
		 (operands[0], operands[1], operands[2], operands[3]));
  else
    {
      machine_mode mode = GET_MODE (operands[0]);
      rtx out0 = operand_subword (operands[0], 0, 1, mode);
      rtx out1 = operand_subword (operands[0], 1, 1, mode);
      rtx rs10 = operand_subword_force (operands[1], 0, mode);
      rtx rs11 = operand_subword_force (operands[1], 1, mode);
      rtx rs20 = operand_subword_force (operands[2], 0, mode);
      rtx rs21 = operand_subword_force (operands[2], 1, mode);
      rtx mask0 = operand_subword_force (operands[3], 0, mode);
      rtx mask1 = operand_subword_force (operands[3], 1, mode);

      emit_insn (gen_riscv_pmerge_si (out0, rs10, rs20, mask0));
      emit_insn (gen_riscv_pmerge_si (out1, rs11, rs21, mask1));
    }
  DONE;
})

(define_insn "riscv_pmerge_<PMERGE_NAME>_rv64"
  [(set (match_operand:PMERGE64 0 "register_operand" "=r,r,r")
        (unspec:PMERGE64 [(match_operand:PMERGE64 1 "register_operand" "r,0,r")
                          (match_operand:PMERGE64 2 "register_operand" "r,r,0")
                          (match_operand:PMERGE64 3 "register_operand" "0,r,r")]
         UNSPEC_PMERGE))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   merge\t%0,%1,%2
   mvm\t%0,%2,%3
   mvmn\t%0,%1,%3"
  [(set_attr "type" "simd")])

;Packed Sign and Zero Extend
;
;psext.* are real hardware instructions with their own encodings (one-operand
;unary form: rd, rs1), so the templates emit the psext mnemonic directly.
;
;pzext.* are NOT real instructions; per the P-ext spec they are only
;pseudoinstructions of ppaire.* with rs2 == x0, e.g.
;  pzext.h.b  rd, rs1  -> ppaire.b   rd, rs1, x0
;  pzext.w.h  rd, rs1  -> ppaire.h   rd, rs1, x0
;  pzext.dh.b rd, rs1  -> ppaire.db  rd, rs1, x0
;  pzext.dw.h rd, rs1  -> ppaire.dh  rd, rs1, x0
;Hence the pzext templates emit the underlying ppaire.* form with x0 instead
;of a (non-existent) pzext mnemonic.
(define_insn "riscv_psext_b_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP"
  "psext.h.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pzext_b_u16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")]
         UNSPEC_PZEXT))]
  "TARGET_RVP"
  "ppaire.b\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_psext_b_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psext_b_i16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_psext_b_i16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_psext_b_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "psext.dh.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psext_b_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.h.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_psext_b_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psext_b_i32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_psext_b_i32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_psext_b_i32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "psext.dw.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psext_b_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.w.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_psext_h_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")]
         UNSPEC_PSEXT_H))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psext_h_i32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_psext_h_i32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_psext_h_i32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")]
         UNSPEC_PSEXT_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "psext.dw.h\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psext_h_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")]
         UNSPEC_PSEXT_H))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.w.h\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_pzext_b_u16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")]
         UNSPEC_PZEXT))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pzext_b_u16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pzext_b_u16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pzext_b_u16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")]
         UNSPEC_PZEXT))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.db\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pzext_b_u16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")]
         UNSPEC_PZEXT))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.b\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_pzext_h_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")]
         UNSPEC_PZEXT))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pzext_h_u32x2_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pzext_h_u32x2_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pzext_h_u32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")]
         UNSPEC_PZEXT))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.dh\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pzext_h_u32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")]
         UNSPEC_PZEXT))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0,%1,x0"
  [(set_attr "type" "simd")])

;Packed Saturation
(define_insn "riscv_pusati_u16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int_operand" "u4")]
         UNSPEC_PUSATI))]
  "TARGET_RVP"
  "pusati.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psati_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int_operand" "u4")]
         UNSPEC_PSATI))]
  "TARGET_RVP"
  "psati.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pusati_u16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:SI 2 "const_int_operand")]
         UNSPEC_PUSATI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pusati_u16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pusati_u16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pusati_u16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int_operand" "u4")]
         UNSPEC_PUSATI))]
  "TARGET_RVP && !TARGET_64BIT"
  "pusati.dh\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pusati_u16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int_operand" "u4")]
         UNSPEC_PUSATI))]
  "TARGET_RVP && TARGET_64BIT"
  "pusati.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pusati_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:SI 2 "const_int_operand")]
         UNSPEC_PUSATI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pusati_u32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pusati_u32x2_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pusati_u32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int_operand" "u5")]
         UNSPEC_PUSATI))]
  "TARGET_RVP && !TARGET_64BIT"
  "pusati.dw\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pusati_u32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int_operand" "u5")]
         UNSPEC_PUSATI))]
  "TARGET_RVP && TARGET_64BIT"
  "pusati.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psati_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:SI 2 "const_int_operand")]
         UNSPEC_PSATI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psati_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psati_i16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psati_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int_operand" "u4")]
         UNSPEC_PSATI))]
  "TARGET_RVP && !TARGET_64BIT"
  "psati.dh\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psati_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int_operand" "u4")]
         UNSPEC_PSATI))]
  "TARGET_RVP && TARGET_64BIT"
  "psati.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psati_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:SI 2 "const_int_operand")]
         UNSPEC_PSATI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psati_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psati_i32x2_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psati_i32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int_operand" "u5")]
         UNSPEC_PSATI))]
  "TARGET_RVP && !TARGET_64BIT"
  "psati.dw\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psati_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int_operand" "u5")]
         UNSPEC_PSATI))]
  "TARGET_RVP && TARGET_64BIT"
  "psati.w\t%0,%1,%2"
  [(set_attr "type" "simd")])
