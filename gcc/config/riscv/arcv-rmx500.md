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

(define_cpu_unit "arcv_rmx500_ALU_fuse0_early"	"arcv_rmx500")
(define_cpu_unit "arcv_rmx500_ALU_fuse1_early"	"arcv_rmx500")
(define_cpu_unit "arcv_rmx500_MPY32"	"arcv_rmx500")
(define_cpu_unit "arcv_rmx500_DIV"	"arcv_rmx500")
(define_cpu_unit "arcv_rmx500_DMP_fuse0"	"arcv_rmx500")
(define_cpu_unit "arcv_rmx500_DMP_fuse1"	"arcv_rmx500")
(define_cpu_unit "arcv_rmx500_fdivsqrt"	"arcv_rmx500")
(define_cpu_unit "arcv_rmx500_issue_fuse0" "arcv_rmx500")
(define_cpu_unit "arcv_rmx500_issue_fuse1" "arcv_rmx500")

;; Instruction reservation for arithmetic instructions (single pipe).
;; instructions can be issued back to back - after 1 cycle the result is available
(define_insn_reservation "arcv_rmx500_alu_early_arith" 1
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "unknown,move,const,arith,shift,slt,multi,auipc,nop,logical,\
		bitmanip,min,max,minu,maxu,clz,ctz,atomic,\
		condmove,mvpair,zicond,cpop,clmul"))
  "(arcv_rmx500_issue_fuse0 + arcv_rmx500_ALU_fuse0_early) | (arcv_rmx500_issue_fuse1 + arcv_rmx500_ALU_fuse1_early)")

(define_insn_reservation "arcv_rmx500_imul_fused" 3
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "imul_fused"))
  "(arcv_rmx500_issue_fuse0 + arcv_rmx500_issue_fuse1 + arcv_rmx500_ALU_fuse0_early + arcv_rmx500_ALU_fuse1_early + arcv_rmx500_MPY32), nothing*2")

(define_insn_reservation "arcv_rmx500_alu_fused" 1
   (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "alu_fused"))
  "(arcv_rmx500_issue_fuse0 + arcv_rmx500_issue_fuse1 + arcv_rmx500_ALU_fuse0_early + arcv_rmx500_ALU_fuse1_early)")

(define_insn_reservation "arcv_rmx500_jmp_insn" 1
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "branch,jump,call,jalr,ret,trap"))
  "arcv_rmx500_issue_fuse0 | arcv_rmx500_issue_fuse1")

(define_insn_reservation "arcv_rmx500_div_insn" 21
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "idiv"))
  "arcv_rmx500_issue_fuse0 + arcv_rmx500_DIV, nothing*20")

(define_insn_reservation "arcv_rmx500_mpy32_insn" 3
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "imul"))
  "arcv_rmx500_issue_fuse0 + arcv_rmx500_MPY32, nothing*2")

(define_insn_reservation "arcv_rmx500_load_insn" 2
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "load,fpload"))
  "(arcv_rmx500_issue_fuse0 + arcv_rmx500_DMP_fuse0) | (arcv_rmx500_issue_fuse1 + arcv_rmx500_DMP_fuse1), nothing")

(define_insn_reservation "arcv_rmx500_store_insn" 1
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "store,fpstore"))
  "(arcv_rmx500_issue_fuse0 + arcv_rmx500_DMP_fuse0) | (arcv_rmx500_issue_fuse1 + arcv_rmx500_DMP_fuse1)")
;; (soft) floating points
(define_insn_reservation "arcv_rmx500_xfer" 3
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "mfc,mtc,fcvt,fcvt_i2f,fcvt_f2i,fmove,fcmp"))
  "(arcv_rmx500_ALU_fuse0_early | arcv_rmx500_ALU_fuse1_early), nothing*2")

(define_insn_reservation "arcv_rmx500_fmul" 3
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "fadd,fmul,fmadd"))
  "(arcv_rmx500_ALU_fuse0_early | arcv_rmx500_ALU_fuse1_early), nothing*2")

(define_insn_reservation "arcv_rmx500_fdiv" 21
  (and (eq_attr "tune" "arcv_rmx500")
       (eq_attr "type" "fdiv,fsqrt"))
  "arcv_rmx500_fdivsqrt*21")

;; Bypasses
(define_bypass 1 "arcv_rmx500_alu_early_arith" "arcv_rmx500_store_insn" "riscv_store_data_bypass_p")
(define_bypass 1 "arcv_rmx500_mpy32_insn" "arcv_rmx500_store_insn" "riscv_store_data_bypass_p")
;; (define_bypass 5 "arcv_rmx500_mpy32_insn" "arcv_rmx500_store_insn" "!riscv_store_data_bypass_p")
;; (define_bypass 5 "arcv_rmx500_mpy32_insn" "arcv_rmx500_load_insn" "!riscv_store_data_bypass_p")
(define_bypass 1 "arcv_rmx500_load_insn" "arcv_rmx500_store_insn" "riscv_store_data_bypass_p")
(define_bypass 1 "arcv_rmx500_load_insn" "arcv_rmx500_alu_early_arith")
(define_bypass 1 "arcv_rmx500_load_insn" "arcv_rmx500_mpy*_insn")
(define_bypass 1 "arcv_rmx500_load_insn" "arcv_rmx500_load_insn")
(define_bypass 1 "arcv_rmx500_load_insn" "arcv_rmx500_div_insn")
(define_bypass 9 "arcv_rmx500_mpy32_insn" "arcv_rmx500_mpy*_insn")
(define_bypass 9 "arcv_rmx500_mpy32_insn" "arcv_rmx500_div_insn")
