;; DFA scheduling description of the Synopsys RHX-100 cpu
;; for GNU C compiler
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

(define_automaton "arcv_rhx100")

(define_cpu_unit "arcv_rhx100_ALU_A_fuse0_early"	"arcv_rhx100")
(define_cpu_unit "arcv_rhx100_ALU_A_fuse1_early"	"arcv_rhx100")
(define_cpu_unit "arcv_rhx100_ALU_B_fuse0_early"	"arcv_rhx100")
(define_cpu_unit "arcv_rhx100_ALU_B_fuse1_early"	"arcv_rhx100")
(define_cpu_unit "arcv_rhx100_MPY32"	"arcv_rhx100")
(define_cpu_unit "arcv_rhx100_DIV"	"arcv_rhx100")
(define_cpu_unit "arcv_rhx100_DMP_fuse0"	"arcv_rhx100")
(define_cpu_unit "arcv_rhx100_DMP_fuse1"	"arcv_rhx100")
(define_cpu_unit "arcv_rhx100_DMP_FPU"	"arcv_rhx100")
(define_cpu_unit "arcv_rhx100_FPU"	"arcv_rhx100")
(define_cpu_unit "arcv_rhx100_fdivsqrt"	"arcv_rhx100")
(define_cpu_unit "arcv_rhx100_issueA_fuse0" "arcv_rhx100")
(define_cpu_unit "arcv_rhx100_issueA_fuse1" "arcv_rhx100")
(define_cpu_unit "arcv_rhx100_issueB_fuse0" "arcv_rhx100")
(define_cpu_unit "arcv_rhx100_issueB_fuse1" "arcv_rhx100")

;; Instruction reservation for arithmetic instructions (pipe A, pipe B).
(define_insn_reservation "arcv_rhx100_alu_early_arith" 1
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "unknown,move,const,arith,shift,slt,multi,auipc,nop,logical,\
		bitmanip,min,max,minu,maxu,clz,ctz,atomic,\
		condmove,mvpair,zicond,cpop,clmul"))
  "((arcv_rhx100_issueA_fuse0 + arcv_rhx100_ALU_A_fuse0_early) | (arcv_rhx100_issueA_fuse1 + arcv_rhx100_ALU_A_fuse1_early)) | ((arcv_rhx100_issueB_fuse0 + arcv_rhx100_ALU_B_fuse0_early) | (arcv_rhx100_issueB_fuse1 + arcv_rhx100_ALU_B_fuse1_early))")

(define_insn_reservation "arcv_rhx100_imul_fused" 4
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "imul_fused"))
  "(arcv_rhx100_issueA_fuse0 + arcv_rhx100_issueA_fuse1 + arcv_rhx100_ALU_A_fuse0_early + arcv_rhx100_ALU_A_fuse1_early + arcv_rhx100_MPY32), nothing*3")

(define_insn_reservation "arcv_rhx100_alu_fused" 1
   (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "alu_fused"))
  "(arcv_rhx100_issueA_fuse0 + arcv_rhx100_issueA_fuse1 + arcv_rhx100_ALU_A_fuse0_early + arcv_rhx100_ALU_A_fuse1_early) | (arcv_rhx100_issueB_fuse0 + arcv_rhx100_issueB_fuse1 + arcv_rhx100_ALU_B_fuse0_early + arcv_rhx100_ALU_B_fuse1_early)")

(define_insn_reservation "arcv_rhx100_jmp_insn" 1
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "branch,jump,call,jalr,ret,trap"))
  "arcv_rhx100_issueA_fuse0 | arcv_rhx100_issueA_fuse1")

(define_insn_reservation "arcv_rhx100_div_insn" 12
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "idiv"))
  "arcv_rhx100_issueA_fuse0 + arcv_rhx100_DIV, nothing*11")

(define_insn_reservation "arcv_rhx100_mpy32_insn" 4
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "imul"))
  "arcv_rhx100_issueA_fuse0 + arcv_rhx100_MPY32, nothing*3")

(define_insn_reservation "arcv_rhx100_load_insn" 3
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "load"))
  "(arcv_rhx100_issueB_fuse0 + arcv_rhx100_DMP_fuse0) | (arcv_rhx100_issueB_fuse1 + arcv_rhx100_DMP_fuse1)")

(define_insn_reservation "arcv_rhx100_store_insn" 1
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "store"))
  "(arcv_rhx100_issueB_fuse0 + arcv_rhx100_DMP_fuse0) | (arcv_rhx100_issueB_fuse1 + arcv_rhx100_DMP_fuse1)")

(define_insn_reservation "arcv_rhx100_fpload_insn" 1
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "fpload"))
  "arcv_rhx100_issueB_fuse0 + arcv_rhx100_issueB_fuse1 + arcv_rhx100_DMP_FPU")

(define_insn_reservation "arcv_rhx100_fpstore_insn" 1
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "fpstore"))
  "arcv_rhx100_issueB_fuse0 + arcv_rhx100_issueB_fuse1 + arcv_rhx100_DMP_FPU")

(define_insn_reservation "arcv_rhx100_fmove" 2
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "mtc,fmove"))
  "(arcv_rhx100_issueA_fuse0 | arcv_rhx100_issueA_fuse1) + arcv_rhx100_FPU")

(define_insn_reservation "arcv_rhx100_fcvt" 3
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "fcvt,fcvt_i2f"))
  "(arcv_rhx100_issueA_fuse0 | arcv_rhx100_issueA_fuse1) + arcv_rhx100_FPU")

(define_insn_reservation "arcv_rhx100_fmv_x" 5
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "mfc"))
  "(arcv_rhx100_issueA_fuse0 | arcv_rhx100_issueA_fuse1) + arcv_rhx100_FPU")

(define_insn_reservation "arcv_rhx100_fcmp" 5
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "fcmp"))
  "(arcv_rhx100_issueA_fuse0 | arcv_rhx100_issueA_fuse1) + arcv_rhx100_FPU")

(define_insn_reservation "arcv_rhx100_fcvt_f2i" 6
  (and (eq_attr "tune" "arcv_rhx100")
       (eq_attr "type" "fcvt_f2i"))
  "(arcv_rhx100_issueA_fuse0 | arcv_rhx100_issueA_fuse1) + arcv_rhx100_FPU")

(define_insn_reservation "arcv_rhx100_fmul_dp" 5
  (and (eq_attr "tune" "arcv_rhx100")
       (and (eq_attr "type" "fadd,fmul,fmadd")
	    (eq_attr "mode" "DF")))
  "(arcv_rhx100_issueA_fuse0 | arcv_rhx100_issueA_fuse1) + arcv_rhx100_FPU")

(define_insn_reservation "arcv_rhx100_fmul" 4
  (and (eq_attr "tune" "arcv_rhx100")
       (and (eq_attr "type" "fadd,fmul,fmadd")
	    (not (eq_attr "mode" "DF"))))
  "(arcv_rhx100_issueA_fuse0 | arcv_rhx100_issueA_fuse1) + arcv_rhx100_FPU")

(define_insn_reservation "arcv_rhx100_fdiv_dp" 26
  (and (eq_attr "tune" "arcv_rhx100")
       (and (eq_attr "type" "fdiv,fsqrt")
	    (eq_attr "mode" "DF")))
  "(arcv_rhx100_issueA_fuse0 | arcv_rhx100_issueA_fuse1) + arcv_rhx100_FPU + arcv_rhx100_fdivsqrt, arcv_rhx100_fdivsqrt*6")

(define_insn_reservation "arcv_rhx100_fdiv" 14
  (and (eq_attr "tune" "arcv_rhx100")
       (and (eq_attr "type" "fdiv,fsqrt")
	    (not (eq_attr "mode" "DF"))))
  "(arcv_rhx100_issueA_fuse0 | arcv_rhx100_issueA_fuse1) + arcv_rhx100_FPU + arcv_rhx100_fdivsqrt, arcv_rhx100_fdivsqrt*6")

;; Bypasses
(define_bypass 1 "arcv_rhx100_alu_early_arith" "arcv_rhx100_store_insn" "riscv_store_data_bypass_p")

(define_bypass 1 "arcv_rhx100_load_insn" "arcv_rhx100_store_insn" "riscv_store_data_bypass_p")
(define_bypass 1 "arcv_rhx100_load_insn" "arcv_rhx100_alu_early_arith")
(define_bypass 1 "arcv_rhx100_load_insn" "arcv_rhx100_mpy*_insn")
(define_bypass 2 "arcv_rhx100_load_insn" "arcv_rhx100_load_insn")
(define_bypass 1 "arcv_rhx100_load_insn" "arcv_rhx100_div_insn")

(define_bypass 3 "arcv_rhx100_mpy32_insn" "arcv_rhx100_mpy*_insn")
(define_bypass 3 "arcv_rhx100_mpy32_insn" "arcv_rhx100_div_insn")
(define_bypass 1 "arcv_rhx100_mpy32_insn" "arcv_rhx100_store_insn" "riscv_store_data_bypass_p")
(define_bypass 7 "arcv_rhx100_mpy32_insn" "arcv_rhx100_store_insn")
(define_bypass 7 "arcv_rhx100_mpy32_insn" "arcv_rhx100_load_insn")

(define_bypass 3 "arcv_rhx100_fmul"    "arcv_rhx100_fmul*")
(define_bypass 4 "arcv_rhx100_fmul_dp" "arcv_rhx100_fmul*")
(define_bypass 2 "arcv_rhx100_fmul*"  "arcv_rhx100_fmul*" "arcv_fmadd_acc_bypass_p")
