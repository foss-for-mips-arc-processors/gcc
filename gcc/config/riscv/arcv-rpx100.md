;; DFA scheduling description of the Synopsys RPX-100 cpu
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

(define_automaton "arcv_rpx100")

(define_cpu_unit "arcv_rpx100_ALU_A_fuse0_early"	"arcv_rpx100")
(define_cpu_unit "arcv_rpx100_ALU_A_fuse1_early"	"arcv_rpx100")
(define_cpu_unit "arcv_rpx100_ALU_B_fuse0_early"	"arcv_rpx100")
(define_cpu_unit "arcv_rpx100_ALU_B_fuse1_early"	"arcv_rpx100")
(define_cpu_unit "arcv_rpx100_MPY"	"arcv_rpx100")
(define_cpu_unit "arcv_rpx100_DIV"	"arcv_rpx100")
(define_cpu_unit "arcv_rpx100_DMP_fuse0"	"arcv_rpx100")
(define_cpu_unit "arcv_rpx100_DMP_fuse1"	"arcv_rpx100")
(define_cpu_unit "arcv_rpx100_fdivsqrt"	"arcv_rpx100")
(define_cpu_unit "arcv_rpx100_issueA_fuse0" "arcv_rpx100")
(define_cpu_unit "arcv_rpx100_issueA_fuse1" "arcv_rpx100")
(define_cpu_unit "arcv_rpx100_issueB_fuse0" "arcv_rpx100")
(define_cpu_unit "arcv_rpx100_issueB_fuse1" "arcv_rpx100")

;; Instruction reservation for arithmetic instructions (pipe A, pipe B).
(define_insn_reservation "arcv_rpx100_alu_early_arith" 1
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "unknown,move,const,arith,shift,slt,multi,auipc,nop,logical,\
		bitmanip,min,max,minu,maxu,clz,ctz,atomic,\
		condmove,mvpair,zicond,cpop,clmul"))
  "((arcv_rpx100_issueA_fuse0 + arcv_rpx100_ALU_A_fuse0_early) | (arcv_rpx100_issueA_fuse1 + arcv_rpx100_ALU_A_fuse1_early)) | ((arcv_rpx100_issueB_fuse0 + arcv_rpx100_ALU_B_fuse0_early) | (arcv_rpx100_issueB_fuse1 + arcv_rpx100_ALU_B_fuse1_early))")

(define_insn_reservation "arcv_rpx100_mpy32_fused" 4
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "imul_fused"))
  "(arcv_rpx100_issueA_fuse0 + arcv_rpx100_issueA_fuse1 + arcv_rpx100_ALU_A_fuse0_early + arcv_rpx100_ALU_A_fuse1_early + arcv_rpx100_MPY), nothing*3")

(define_insn_reservation "arcv_rpx100_alu_fused" 1
   (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "alu_fused"))
  "(arcv_rpx100_issueA_fuse0 + arcv_rpx100_issueA_fuse1 + arcv_rpx100_ALU_A_fuse0_early + arcv_rpx100_ALU_A_fuse1_early) | (arcv_rpx100_issueB_fuse0 + arcv_rpx100_issueB_fuse1 + arcv_rpx100_ALU_B_fuse0_early + arcv_rpx100_ALU_B_fuse1_early)")

(define_insn_reservation "arcv_rpx100_jmp_insn" 1
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "branch,jump,call,jalr,ret,trap"))
  "arcv_rpx100_issueA_fuse0 | arcv_rpx100_issueA_fuse1")

(define_insn_reservation "arcv_rpx100_div_insn" 12
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "idiv"))
  "arcv_rpx100_issueA_fuse0 + arcv_rpx100_DIV, nothing*11")

(define_insn_reservation "arcv_rpx100_mpy32_insn" 4
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "imul")
       (eq_attr "mode" "SI"))
  "arcv_rpx100_issueA_fuse0 + arcv_rpx100_MPY, nothing*3")

(define_insn_reservation "arcv_rpx100_mpy64l_insn" 6
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "imul")
       (eq_attr "mode" "DI")
       (eq_attr "mul_part" "low"))
  "arcv_rpx100_issueA_fuse0 + arcv_rpx100_MPY, arcv_rpx100_MPY*2, nothing * 3")

;; The 1 cycle reservation of the multiplier is only correct for the bonded mul case.
;; Mul high part is usually generated together with the low part.
;; Otherwise, this is 3 cycles too optimistic about multiplier reservation.
(define_insn_reservation "arcv_rpx100_mpy64h_insn" 7
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "imul")
       (eq_attr "mode" "DI")
       (eq_attr "mul_part" "high"))
  "arcv_rpx100_issueA_fuse0 + arcv_rpx100_MPY, nothing*6")

(define_insn_reservation "arcv_rpx100_load_insn" 3
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "load,fpload"))
  "(arcv_rpx100_issueB_fuse0 + arcv_rpx100_DMP_fuse0) | (arcv_rpx100_issueB_fuse1 + arcv_rpx100_DMP_fuse1)")

(define_insn_reservation "arcv_rpx100_store_insn" 1
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "store,fpstore"))
  "(arcv_rpx100_issueB_fuse0 + arcv_rpx100_DMP_fuse0) | (arcv_rpx100_issueB_fuse1 + arcv_rpx100_DMP_fuse1)")

;; (soft) floating points
(define_insn_reservation "arcv_rpx100_xfer" 3
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "mfc,mtc,fcvt,fcvt_i2f,fcvt_f2i,fmove,fcmp"))
  "(arcv_rpx100_ALU_A_fuse0_early | arcv_rpx100_ALU_B_fuse0_early), nothing*2")

(define_insn_reservation "arcv_rpx100_fmul" 5
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "fadd,fmul,fmadd"))
  "(arcv_rpx100_ALU_A_fuse0_early | arcv_rpx100_ALU_B_fuse0_early)")

(define_insn_reservation "arcv_rpx100_fdiv" 20
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "fdiv,fsqrt"))
  "arcv_rpx100_fdivsqrt*20")

;(final_presence_set "arcv_rpx100_issueA_fuse1" "arcv_rpx100_issueA_fuse0")
;(final_presence_set "arcv_rpx100_issueB_fuse1" "arcv_rpx100_issueB_fuse0")
;(final_presence_set "arcv_rpx100_ALU_A_fuse1_early" "arcv_rpx100_ALU_A_fuse0_early")
;(final_presence_set "arcv_rpx100_ALU_B_fuse1_early" "arcv_rpx100_ALU_B_fuse0_early")

;; Bypasses
;(define_bypass 0 "arcv_rpx100_alu_early_arith" "arcv_rpx100_store_insn" "riscv_store_data_bypass_p")
(define_bypass 1 "arcv_rpx100_alu_early_arith" "arcv_rpx100_store_insn" "riscv_store_data_bypass_p")

;(define_bypass 0 "arcv_rpx100_load_insn" "arcv_rpx100_store_insn" "riscv_store_data_bypass_p")
(define_bypass 1 "arcv_rpx100_load_insn" "arcv_rpx100_store_insn" "riscv_store_data_bypass_p")
(define_bypass 1 "arcv_rpx100_load_insn" "arcv_rpx100_alu_early_arith")
(define_bypass 1 "arcv_rpx100_load_insn" "arcv_rpx100_mpy*_insn")
(define_bypass 2 "arcv_rpx100_load_insn" "arcv_rpx100_load_insn")
(define_bypass 1 "arcv_rpx100_load_insn" "arcv_rpx100_div_insn")

(define_bypass 3 "arcv_rpx100_mpy32*" "arcv_rpx100_mpy*_insn")
(define_bypass 3 "arcv_rpx100_mpy32*" "arcv_rpx100_div_insn")
(define_bypass 1 "arcv_rpx100_mpy*_insn" "arcv_rpx100_store_insn" "riscv_store_data_bypass_p")
(define_bypass 7 "arcv_rpx100_mpy32*" "arcv_rpx100_load_insn")
(define_bypass 7 "arcv_rpx100_mpy32*" "arcv_rpx100_store_insn")
(define_bypass 9 "arcv_rpx100_mpy64l_insn" "arcv_rpx100_load_insn")
(define_bypass 9 "arcv_rpx100_mpy64l_insn" "arcv_rpx100_store_insn")
(define_bypass 10 "arcv_rpx100_mpy64h_insn" "arcv_rpx100_load_insn")
(define_bypass 10 "arcv_rpx100_mpy64h_insn" "arcv_rpx100_store_insn")

;; Even if a specific type attribute is not implemented by a processor
;; tune variant, the pipeline description must still provide a valid
;; reservation to prevent compiler scheduling errors.

(define_insn_reservation "arcv_rpx100_unknown" 1
  (and (eq_attr "tune" "arcv_rpx100")
       (eq_attr "type" "vfrecp,vclmul,vldm,vmffs,vclmulh,vlsegde,vfcvtitof,vsm4k,vfcvtftoi,vfdiv,vsm3c,vsm4r,viwmuladd,vfwredu,vcpop,vfwmuladd,vstux,vsshift,vfwcvtftof,vfncvtftof,vfwmaccbf16,vext,vssegte,rdvl,vaeskf1,vfslide1up,vmov,vimovvx,vaesef,vfsqrt,viminmax,vfwcvtftoi,vssegtox,vfclass,viwmul,vector,vgmul,vsm3me,vfcmp,vstm,vfredo,vfwmul,vaeskf2,vstox,vfncvtbf16,vislide1up,vgather,vldox,viwred,vctz,vghsh,vsts,vslidedown,vfmerge,vicmp,vsmul,vlsegdff,vfalu,vfmov,vislide1down,vfminmax,vcompress,vldr,vldff,vlsegdux,vimuladd,vsalu,vidiv,sf_vqmacc,vfslide1down,vaesem,vimerge,vfncvtftoi,vfwcvtitof,vicalu,vaesz,sf_vc_se,vsha2cl,vmsfs,vldux,vmidx,vslideup,vired,vlde,vfwredo,vfmovfv,vbrev,vfncvtitof,rdfrm,vsetvl,vssegts,vimul,vialu,vbrev8,vfwalu,rdvlenb,sf_vfnrclip,vclz,vnclip,sf_vc,vimov,vste,vfmuladd,vfmovvf,vwsll,vsetvl_pre,vlds,vlsegds,vmiota,vmalu,wrvxrm,wrfrm,viwalu,vaesdm,vssegtux,vaesdf,vimovxv,vror,vnshift,vstr,vaalu,vsha2ms,crypto,vfwcvtbf16,vlsegdox,vrol,vandn,vfsgnj,vmpop,vfredu,vsha2ch,vshift,vrev8,vfmul,sfb_alu,rotate,arcv_dsp_vector"))
  "arcv_rpx100_ALU_A_fuse0_early")
