;; DFA-based pipeline description for m8500.
;;
;; Copyright (C) 2018-2024 Free Software Foundation, Inc.
;;
;; This file is part of GCC.
;;
;; GCC is free software; you can redistribute it and/or modify it
;; under the terms of the GNU General Public License as published
;; by the Free Software Foundation; either version 3, or (at your
;; option) any later version.

;; GCC is distributed in the hope that it will be useful, but WITHOUT
;; ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
;; or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
;; License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;; MIPS RISC-V m8500 has 6 pipelines
;; ALU0 pipe   - ALU, Branch
;; ALU1 pipe   - ALU, Branch, Integer Mul, Integer Div
;; FPU0 pipe   - FDIV, FSQRT and other FPU ops
;; FPU1 pipe   - Trig and other FPU ops
;; LD pipe     - Load instructions
;; ST pipe     - Store instructions

(define_automaton "mips_m8500_alu_pipe, mips_m8500_lsu_pipe,
     mips_m8500_fpu_pipe")

(define_cpu_unit "mips_m8500_alu0, mips_m8500_alu1"
		 "mips_m8500_alu_pipe")

(define_cpu_unit "mips_m8500_ld, mips_m8500_st" "mips_m8500_lsu_pipe")

(define_cpu_unit "mips_m8500_fpu0, mips_m8500_fpu1" "mips_m8500_fpu_pipe")

;; ALU, Branch instructions can use ALU0 and ALU1 pipe.
(define_reservation "mips_m8500_int_pipe" "(mips_m8500_alu0 | mips_m8500_alu1)")

;; FPU instructions can use FPU0 and FPU1 pipe.
(define_reservation "mips_m8500_float_pipe"
     "(mips_m8500_fpu0 | mips_m8500_fpu1)")

;;
;; FPU pipe
;;

(define_insn_reservation "mips_m8500_fpu_fadd" 6
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "fadd"))
  "mips_m8500_float_pipe")

(define_insn_reservation "mips_m8500_fpu_move" 3
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "fmove"))
  "mips_m8500_float_pipe")

(define_insn_reservation "mips_m8500_fpu_fabs" 3
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "fcmp"))
  "mips_m8500_float_pipe")

(define_insn_reservation "mips_m8500_fpu_fmadd" 6
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "fmadd"))
  "mips_m8500_float_pipe")

(define_insn_reservation "mips_m8500_fpu_fmul" 6
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "fmul"))
  "mips_m8500_float_pipe")

(define_insn_reservation "mips_m8500_fpu_fdiv_s" 13
  (and (eq_attr "tune" "mips_m8500")
       (and (eq_attr "type" "fdiv,fsqrt")
	    (eq_attr "mode" "SF")))
  "mips_m8500_fpu0*7")

(define_insn_reservation "mips_m8500_fpu_fdiv_d" 20
  (and (eq_attr "tune" "mips_m8500")
       (and (eq_attr "type" "fdiv,fsqrt")
	    (eq_attr "mode" "DF")))
  "mips_m8500_fpu0*7")

(define_insn_reservation "mips_m8500_fpu_fcvt" 5
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "fcvt,fcvt_i2f,fcvt_f2i,mtc,mfc"))
  "mips_m8500_float_pipe")

;;
;; Load/Store pipe
;;

(define_insn_reservation "mips_m8500_load" 4
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "load, fpload"))
  "mips_m8500_ld")

(define_insn_reservation "mips_m8500_store" 1
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "store, fpstore"))
  "mips_m8500_st")

;;
;; Integer pipe
;;

(define_insn_reservation "mips_m8500_int_arith" 1
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "unknown,const,arith,shift,slt,multi,auipc,logical,
	move,bitmanip,min,max,minu,maxu,clz,ctz,rotate,atomic,condmove,
	crypto,mvpair,zicond,branch,jump,jalr,cpop,clmul"))
  "mips_m8500_int_pipe")

(define_insn_reservation "mips_m8500_int_nop" 0
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "nop"))
  "mips_m8500_int_pipe")

(define_insn_reservation "mips_m8500_dsp_mult" 1
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "imul"))
  "mips_m8500_alu1")

(define_insn_reservation "mips_m8500_int_div" 16
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "idiv"))
  "mips_m8500_alu1*7")

(define_insn_reservation "mips_m8500_int_branch" 1
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "ret,sfb_alu,trap"))
  "mips_m8500_alu0")

(define_insn_reservation "mips_m8500_int_call" 2
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "call"))
  "mips_m8500_alu0")

;;
;; forwarding/bypass
;;
(define_bypass 3 "mips_m8500_load" "mips_m8500_load,mips_m8500_store")
(define_bypass 1 "mips_m8500_store" "mips_m8500_load")

;; Even if a specific type attribute is not implemented by a processor
;; tune variant, the pipeline description must still provide a valid
;; reservation to prevent scheduling errors.

(define_insn_reservation "mips_m8500_unknown" 1
  (and (eq_attr "tune" "mips_m8500")
       (eq_attr "type" "vfmovvf,vssegte,vmov,vfmuladd,rdfrm,vslideup,vfncvtftof,
  vfmov,vfncvtbf16,vimov,vaesdf,vislide1up,vsm3c,vfredu,vfslide1up,vlsegde,
  vcompress,vfwcvtftof,vector,rdvl,vlsegdox,vgather,vrev8,vfmul,vsm4k,vimovxv,
  vfwmul,vfwcvtbf16,vsha2cl,vfsqrt,vlde,vldox,viwmuladd,vaesef,vctz,viwalu,
  vmpop,alu_fused,wrfrm,vmiota,vext,vmidx,vfcmp,rdvlenb,vsshift,vfwalu,
  vislide1down,vsm4r,vldux,vfsgnj,vfmovfv,vfwmuladd,vsmul,vimuladd,vidiv,
  vfwredo,vfcvtftoi,vrol,vlsegdux,vicalu,vaeskf2,vshift,wrvxrm,vaesz,vbrev,
  sf_vc,vfdiv,vimul,vfrecp,vste,vssegts,imul_fused,vstm,vfwcvtitof,vialu,vandn,
  viminmax,vnshift, vaesdm,vstr,vsalu,vfmerge,vsetvl,sf_vqmacc,vfwmaccbf16,
  viwred,vsts,vldff,vstox,vfclass,vssegtux,vaalu,vmalu,vfredo,vlsegdff,vimovvx,
  arcv_dsp_vector,vsetvl_pre,vfminmax,vmsfs,vcpop,vclz,vfwredu,vldr,vfncvtitof,
  sf_vc_se,vlds,viwmul,vror,vwsll,vsm3me,vclmul,vlsegds,vsha2ms,vaesem,
  vfncvtftoi,vghsh,vfalu,ghost,vimerge,vfwcvtftoi,vsha2ch,vaeskf1,vssegtox,
  vfslide1down,vfcvtitof,vldm,sf_vfnrclip,vgmul,vbrev8,vclmulh,vmffs,vnclip,
  vstux,vicmp,vired,vslidedown"))
  "mips_m8500_int_pipe")
