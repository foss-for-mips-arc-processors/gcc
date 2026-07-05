;; DFA scheduling description of the Synopsys RMX-100 cpu
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

(define_automaton "arcv_rmx100")

(define_cpu_unit "arcv_rmx100_ALU"    "arcv_rmx100")
(define_cpu_unit "arcv_rmx100_FPU"    "arcv_rmx100")
(define_cpu_unit "arcv_rmx100_MPY"    "arcv_rmx100")
(define_cpu_unit "arcv_rmx100_DIV"    "arcv_rmx100")
(define_cpu_unit "arcv_rmx100_DMP"    "arcv_rmx100")

;; Instruction reservation for arithmetic instructions.
(define_insn_reservation "arcv_rmx100_alu_arith" 1
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "unknown, const, arith, shift, slt, multi, auipc, nop,
			logical, move, atomic, mvpair, bitmanip, clz, ctz, cpop,
			zicond, condmove, clmul, min, max, minu, maxu, rotate"))
  "arcv_rmx100_ALU")

(define_insn_reservation "arcv_rmx100_jmp_insn" 1
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "branch, jump, call, jalr, ret, trap"))
  "arcv_rmx100_ALU")

; DIV insn: latency may be overridden by a define_bypass
(define_insn_reservation "arcv_rmx100_div_insn" 35
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "idiv"))
  "arcv_rmx100_DIV*35")

; MPY insn: latency may be overridden by a define_bypass
(define_insn_reservation "arcv_rmx100_mpy32_insn" 9
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "imul"))
  "arcv_rmx100_MPY")

(define_insn_reservation "arcv_rmx100_load_insn" 3
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "load"))
  "arcv_rmx100_DMP,nothing*2")

(define_insn_reservation "arcv_rmx100_store_insn" 1
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "store,fpstore"))
  "arcv_rmx100_DMP")

;; FPU scheduling.  FIXME: This is based on the "fast" unit for now, the "slow"
;; option remains to be implemented later (together with the -mfpu flag).

(define_insn_reservation "arcv_rmx100_fpload_insn" 3
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "fpload"))
  "arcv_rmx100_DMP,nothing*2")

(define_insn_reservation "arcv_rmx100_farith_insn" 2
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "fadd,fcmp"))
  "arcv_rmx100_FPU,nothing")

(define_insn_reservation "arcv_rmx100_xfer" 1
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "fmove,mtc,mfc,fcvt,fcvt_f2i,fcvt_i2f"))
   "arcv_rmx100_FPU")

(define_insn_reservation "arcv_rmx100_fmul_insn" 2
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "fmul"))
  "arcv_rmx100_FPU,nothing")

(define_insn_reservation "arcv_rmx100_fmac_insn" 2
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "fmadd"))
  "arcv_rmx100_FPU,nothing")

(define_insn_reservation "arcv_rmx100_fdiv_insn" 10
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "fdiv,fsqrt"))
  "arcv_rmx100_FPU")


(define_bypass 1 "arcv_rmx100_mpy32_insn"
  "arcv_rmx100_*" "arcv_mpy_1c_bypass_p")
(define_bypass 2 "arcv_rmx100_mpy32_insn"
  "arcv_rmx100_*" "arcv_mpy_2c_bypass_p")

(define_bypass 9 "arcv_rmx100_div_insn" "arcv_rmx100_*" "arcv_mpy_1c_bypass_p")
(define_bypass 9 "arcv_rmx100_div_insn" "arcv_rmx100_*" "arcv_mpy_2c_bypass_p")

(define_insn_reservation "arcv_rmx100_unknown" 1
  (and (eq_attr "tune" "arcv_rmx100")
       (eq_attr "type" "vfrecp,vclmul,vldm,vmffs,vclmulh,vlsegde,vfcvtitof,vsm4k,vfcvtftoi,vfdiv,vsm3c,vsm4r,viwmuladd,vfwredu,vcpop,vfwmuladd,vstux,vsshift,vfwcvtftof,vfncvtftof,vfwmaccbf16,vext,vssegte,rdvl,vaeskf1,vfslide1up,vmov,vimovvx,vaesef,vfsqrt,viminmax,vfwcvtftoi,vssegtox,vfclass,viwmul,vector,vgmul,vsm3me,vfcmp,vstm,vfredo,vfwmul,vaeskf2,vstox,vfncvtbf16,vislide1up,vgather,vldox,viwred,vctz,vghsh,vsts,vslidedown,vfmerge,vicmp,vsmul,vlsegdff,vfalu,vfmov,vislide1down,vfminmax,vcompress,vldr,vldff,vlsegdux,vimuladd,vsalu,vidiv,sf_vqmacc,vfslide1down,vaesem,vimerge,vfncvtftoi,vfwcvtitof,vicalu,vaesz,sf_vc_se,vsha2cl,vmsfs,vldux,vmidx,vslideup,vired,vlde,vfwredo,vfmovfv,vbrev,vfncvtitof,rdfrm,vsetvl,vssegts,vimul,vialu,vbrev8,vfwalu,rdvlenb,sf_vfnrclip,vclz,vnclip,sf_vc,vimov,vste,vfmuladd,vfmovvf,vwsll,vsetvl_pre,vlds,vlsegds,vmiota,vmalu,wrvxrm,wrfrm,viwalu,vaesdm,vssegtux,vaesdf,vimovxv,vror,vnshift,vstr,vaalu,vsha2ms,crypto,vfwcvtbf16,vlsegdox,vrol,vandn,vfsgnj,vmpop,vfredu,vsha2ch,vshift,vrev8,vfmul"))
  "arcv_rmx100_ALU")

