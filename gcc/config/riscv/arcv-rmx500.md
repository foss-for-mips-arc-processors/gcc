;; DFA scheduling description of the Synopsys RMX-500 cpu
;; for GNU C compiler
;; Copyright (C) 2023 Free Software Foundation, Inc.

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

(define_automaton "arcv_rmx500")

(define_cpu_unit "arcv_rmx500_ALU"    "arcv_rmx500")
;(define_cpu_unit "arcv_rmx500_CSR"    "arcv_rmx500")
(define_cpu_unit "arcv_rmx500_FPU"    "arcv_rmx500")
(define_cpu_unit "arcv_rmx500_MPY"    "arcv_rmx500")
(define_cpu_unit "arcv_rmx500_DIV"    "arcv_rmx500")
(define_cpu_unit "arcv_rmx500_DMP"    "arcv_rmx500")

;; Instruction reservation for arithmetic instructions.
(define_insn_reservation "arcv_rmx500_alu_arith" 3
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "unknown, const, arith, shift, slt, multi, auipc, nop,
                        logical, move, atomic, mvpair, bitmanip, clz, ctz, cpop,
                        zicond, condmove, clmul, min, max, minu, maxu"))
  "arcv_rmx500_ALU, nothing*2")

(define_insn_reservation "arcv_rmx500_jmp_insn" 1
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "branch, jump, call, jalr, ret, trap"))
  "arcv_rmx500_ALU")

(define_insn_reservation "arcv_rmx500_div_insn" 22
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "idiv"))
  "arcv_rmx500_DIV*22")

(define_insn_reservation "arcv_rmx500_mpy32_insn" 10
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "imul"))
  "arcv_rmx500_MPY*10")

(define_insn_reservation "arcv_rmx500_load_insn" 1
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "load,fpload"))
  "arcv_rmx500_DMP")

(define_insn_reservation "arcv_rmx500_store_insn" 1
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "store,fpstore"))
  "arcv_rmx500_DMP")

(define_insn_reservation "arcv_rmx500_farith_insn" 2
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "fadd,fmul,fmadd,fcmp"))
  "arcv_rmx500_FPU*2")

(define_insn_reservation "arcv_rmx500_fdiv_insn" 17
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "fdiv,fsqrt"))
  "arcv_rmx500_FPU*17")

(define_insn_reservation "arcv_rmx500_xfer" 2
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "fmove,mtc,mfc,fcvt,fcvt_f2i,fcvt_i2f"))
   "arcv_rmx500_FPU*2")

;;(define_insn_reservation "core" 1
;;  (eq_attr "type" "block, brk, dmb, flag, lr, sr, sync")
;;  "arcv_rmx500_ALU0 + arcv_rmx500_ALU1 + arcv_rmx500_DMP + arcv_rmx500_MPY + arcv_rmx500_MPY64 + arcv_rmx500_DIV")

;; Bypasses
(define_bypass 9 "arcv_rmx500_mpy32_insn" "arcv_rmx500_mpy32_insn,arcv_rmx500_div_insn")

;;(define_bypass 1 "arcv_rmx500_alu_arith" "arcv_rmx500_mpy32_insn" "!accumulator_bypass_p")
(define_bypass 1 "arcv_rmx500_alu_arith,arcv_rmx500_load_insn"
                 "arcv_rmx500_alu_arith,arcv_rmx500_mpy32_insn,arcv_rmx500_div_insn,arcv_rmx500_load_insn")
(define_bypass 1 "arcv_rmx500_alu_arith,arcv_rmx500_load_insn"
                 "arcv_rmx500_store_insn" "riscv_store_data_bypass_p")
