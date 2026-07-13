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


(define_c_enum "unspec" [
  UNSPEC_CLS
  UNSPEC_REV
  UNSPEC_REV16
  UNSPEC_SHA
  UNSPEC_SHAR
  UNSPEC_SHL
  UNSPEC_SHLR
  UNSPEC_UNZIP8P
  UNSPEC_PSLLI
  UNSPEC_PSSLAI
  UNSPEC_SSLAI
  UNSPEC_PLI
  UNSPEC_PSEXT_B
  UNSPEC_PSEXT_H
  UNSPEC_PZEXT
  UNSPEC_PLUI
  UNSPEC_PSLL
  UNSPEC_PADD
  UNSPEC_PSUB
  UNSPEC_PMIN
  UNSPEC_PMAX
  UNSPEC_PMINU
  UNSPEC_PMAXU
  UNSPEC_PMSEQ
  UNSPEC_PMSLT
  UNSPEC_PMSGT
  UNSPEC_PMSLTU
  UNSPEC_PMSGTU
  UNSPEC_PREDSUM
  UNSPEC_PREDSUMU
  UNSPEC_PMERGE
  UNSPEC_PSSHA
  UNSPEC_PSSHAR
  UNSPEC_PSSHL
  UNSPEC_PSSHLR
  UNSPEC_PSRL
  UNSPEC_PSRLI
  UNSPEC_PUSATI
  UNSPEC_PSABS
  UNSPEC_PABD
  UNSPEC_PABDU
  UNSPEC_PSRAI
  UNSPEC_PSATI
  UNSPEC_SATI
  UNSPEC_PSRA
  UNSPEC_PDIFSUMU
  UNSPEC_PDIFSUMAU
  UNSPEC_PMUL
  UNSPEC_PPACK
  UNSPEC_PPAIRE
  UNSPEC_PPAIREO
  UNSPEC_PPAIROE
  UNSPEC_PPAIRO
  UNSPEC_PM2ADD
  UNSPEC_PMULH
  UNSPEC_PMULHR
  UNSPEC_PMULHU
  UNSPEC_PMULHRU
  UNSPEC_PMULHSU
  UNSPEC_PMULHRSU
  UNSPEC_PMHACC
  UNSPEC_PMHRACC
  UNSPEC_PMHACCU
  UNSPEC_PMHRACCU
  UNSPEC_PMHACCSU
  UNSPEC_PMHRACCSU
  UNSPEC_PMULQ
  UNSPEC_PMULQR
  UNSPEC_PMQACC_H00
  UNSPEC_PMQACC_H01
  UNSPEC_PMQACC_H11
  UNSPEC_PMQRACC_H00
  UNSPEC_PMQRACC_H01
  UNSPEC_PMQRACC_H11
  UNSPEC_PMQACC_W00
  UNSPEC_PMQACC_W01
  UNSPEC_PMQACC_W11
  UNSPEC_PMQRACC_W00
  UNSPEC_PMQRACC_W01
  UNSPEC_PMQRACC_W11
  UNSPEC_PMUL_B00
  UNSPEC_PMUL_B01
  UNSPEC_PMUL_B11
  UNSPEC_PMULU_B00
  UNSPEC_PMULU_B01
  UNSPEC_PMULU_B11
  UNSPEC_PMULSU_B00
  UNSPEC_PMULSU_B11
  UNSPEC_PMUL_H00
  UNSPEC_PMUL_H01
  UNSPEC_PMUL_H11
  UNSPEC_PMULU_H00
  UNSPEC_PMULU_H01
  UNSPEC_PMULU_H11
  UNSPEC_PMULSU_H00
  UNSPEC_PMULSU_H11
  UNSPEC_PMUL_W00
  UNSPEC_PMUL_W01
  UNSPEC_PMUL_W11
  UNSPEC_PMULU_W00
  UNSPEC_PMULU_W01
  UNSPEC_PMULU_W11
  UNSPEC_PMULSU_W00
  UNSPEC_PMULSU_W11
  UNSPEC_PSA
  UNSPEC_PAS
  UNSPEC_PSAS
  UNSPEC_PSSA
  UNSPEC_PAAS
  UNSPEC_PASA
  UNSPEC_PSADD
  UNSPEC_PSSUB
  UNSPEC_PSADDU
  UNSPEC_PSSUBU
  UNSPEC_PAADD
  UNSPEC_PASUB
  UNSPEC_PAADDU
  UNSPEC_PASUBU
  UNSPEC_PSH1ADD
  UNSPEC_PSSH1SADD
  UNSPEC_PWCVT_B
  UNSPEC_PWCVT_H
  UNSPEC_PWCVTU_B
  UNSPEC_PWCVTU_H
  UNSPEC_PWCVTH_B
  UNSPEC_PWCVTH_H
  UNSPEC_PNCVT_B
  UNSPEC_PNCVT_H
  UNSPEC_PNCVTH_B
  UNSPEC_PNCVTH_H
  UNSPEC_PZIP_B
  UNSPEC_PZIP_H
  UNSPEC_PUNZIPE_B
  UNSPEC_PUNZIPE_H
  UNSPEC_PUNZIPO_B
  UNSPEC_PUNZIPO_H
  UNSPEC_PNZIP_B
  UNSPEC_PNZIP_H
  UNSPEC_PNZIPH_B
  UNSPEC_PNZIPH_H
  UNSPEC_PWUNZIPE
  UNSPEC_PWUNZIPO
  UNSPEC_PWUNZIPUE
  UNSPEC_PWUNZIPUO
  UNSPEC_PWUNZIPHE
  UNSPEC_PWUNZIPHO
  UNSPEC_PWADD_B
  UNSPEC_PWADD_H
  UNSPEC_PWADDU_B
  UNSPEC_PWADDU_H
  UNSPEC_PWSUB_B
  UNSPEC_PWSUB_H
  UNSPEC_PWSUBU_B
  UNSPEC_PWSUBU_H
  UNSPEC_PWADDA_B
  UNSPEC_PWADDA_H
  UNSPEC_PWADDAU_B
  UNSPEC_PWADDAU_H
  UNSPEC_PWSUBA_B
  UNSPEC_PWSUBA_H
  UNSPEC_PWSUBAU_B
  UNSPEC_PWSUBAU_H
  UNSPEC_PWSLL
  UNSPEC_PWSLA
  UNSPEC_PNSRL
  UNSPEC_PNSRA
  UNSPEC_PNSRAR
  UNSPEC_PNCLIPU
  UNSPEC_PNCLIPRU
  UNSPEC_PNCLIP
  UNSPEC_PNCLIPR
])


(define_mode_iterator VQI [(V4QI "!TARGET_64BIT") (V8QI "TARGET_64BIT")])
(define_mode_iterator VHI [(V2HI "!TARGET_64BIT") (V4HI "TARGET_64BIT")])
(define_mode_iterator V_SI [(SI "!TARGET_64BIT") (V2SI "TARGET_64BIT")])
(define_mode_iterator SI_DI [(SI "!TARGET_64BIT") (DI "TARGET_64BIT")])
(define_mode_iterator VPSI [(SI "!TARGET_64BIT") (V2SI "TARGET_64BIT")])
(define_mode_attr PSEXT [(V2HI "V4QI") (V4HI "V8QI")])
(define_mode_iterator VD_SI [(SI "!TARGET_64BIT") (V2SI "TARGET_64BIT")])


(define_mode_iterator VQIHISI [(V4QI "!TARGET_64BIT") (V8QI "TARGET_64BIT")
                            (V2HI "!TARGET_64BIT") (V4HI "TARGET_64BIT")
                            (V2SI "TARGET_64BIT")])

(define_mode_attr SUFFIX [(V4QI "b") (V8QI "b") (V2HI "h") (V4HI "h") (V2SI "w")])
(define_mode_attr PMUL [(V2HI "V4QI") (V4HI "V8QI")])
(define_mode_iterator SAT32 [(V4QI "true") (V2HI "true")])
(define_mode_iterator SAT64 [(V8QI "true") (V4HI "true") (V2SI "true")])
(define_mode_iterator SHADD32 [(V2HI "true")])
(define_mode_iterator SHADD64 [(V4HI "true") (V2SI "true")])
(define_mode_attr SAT_NAME [(V4QI "i8x4") (V2HI "i16x2")
                            (V8QI "i8x8") (V4HI "i16x4")
                            (V2SI "i32x2")])
(define_mode_attr USAT_NAME [(V4QI "u8x4") (V2HI "u16x2")
                             (V8QI "u8x8") (V4HI "u16x4")
                             (V2SI "u32x2")])
(define_mode_attr SAT_SUFFIX [(V4QI "b") (V2HI "h")
                              (V8QI "b") (V4HI "h") (V2SI "w")])
(define_mode_attr DSAT_SUFFIX [(V8QI "db") (V4HI "dh") (V2SI "dw")])
(define_mode_attr SSUFFIX [(V4QI "bs") (V2HI "hs")
                            (V8QI "bs") (V4HI "hs") (V2SI "ws")])
(define_mode_attr DSSUFFIX [(V8QI "dbs") (V4HI "dhs") (V2SI "dws")])
(define_mode_attr SCALAR_MODE [(V4QI "QI") (V2HI "HI")
                                (V8QI "QI") (V4HI "HI") (V2SI "SI")])
(define_mode_iterator ABD32 [(V4QI "true") (V2HI "true")])
(define_mode_iterator ABD64 [(V8QI "true") (V4HI "true")])
; 64-bit packed modes excluding V2SI (used by Packed Pair 8x8/16x4, where the
; 32x2 case is handled separately because its RV64 mnemonic is "pack"/ppaireo.w
; rather than ppaire.w, and its RV32 form is intentionally unsupported).
(define_mode_iterator PAIR64 [(V8QI "true") (V4HI "true")])
(define_mode_iterator PMERGE32 [(V4QI "true") (V2HI "true")])
(define_mode_iterator PMERGE64 [(V8QI "true") (V4HI "true") (V2SI "true")])
(define_mode_attr PMERGE_NAME [(V4QI "i8x4") (V2HI "i16x2")
                               (V8QI "i8x8") (V4HI "i16x4")
                               (V2SI "i32x2")])
(define_mode_attr UPMERGE_NAME [(V4QI "u8x4") (V2HI "u16x2")
                                (V8QI "u8x8") (V4HI "u16x4")
                                (V2SI "u32x2")])
; Packed Comparison: result is always unsigned.  Input signedness varies:
; pmseq/pmsne accept both (two intrinsic variants, same instruction);
; pmslt/pmsgt/pmsge/pmsle take signed inputs; pmsltu/pmsgtu/pmsgeu/pmsleu
; take unsigned inputs.  V4QI and UV4QI share the same machine mode, so the
; insns operate on the V*/UV* mode interchangeably; the builtin ftype carries
; the signedness of the inputs.
; Builtin/intrinsic naming: a suffix is added only to disambiguate.
; pmseq/pmsne are sign-agnostic, so the input signedness must be encoded
; explicitly (pmseq_i8x4_u8x4 signed in, pmseq_u8x4_u8x4 unsigned in).
; pmslt/pmsgt/pmsge/pmsle carry signedness in the opcode name (s = signed),
; and pmsltu/pmsgtu/pmsgeu/pmsleu in the opcode (u = unsigned), so the input
; signedness is unambiguous and only the (unsigned) result width is named,
; e.g. pmslt_u8x4 (signed in) and pmsltu_u8x4 (unsigned in).
(define_mode_attr PCMP_SNAME [(V4QI "i8x4_u8x4") (V2HI "i16x2_u16x2")
                              (V8QI "i8x8_u8x8") (V4HI "i16x4_u16x4")
                              (V2SI "i32x2_u32x2")])
(define_mode_attr PCMP_UNAME [(V4QI "u8x4_u8x4") (V2HI "u16x2_u16x2")
                              (V8QI "u8x8_u8x8") (V4HI "u16x4_u16x4")
                              (V2SI "u32x2_u32x2")])
(define_mode_attr PCMP_ONAME [(V4QI "u8x4") (V2HI "u16x2")
                              (V8QI "u8x8") (V4HI "u16x4")
                              (V2SI "u32x2")])

;Scalar Intrinsics Common to RV32 and RV64
(define_insn "riscv_abs<mode>_p"
  [(set (match_operand:X 0 "register_operand" "=r")
        (abs:X (match_operand:X 1 "register_operand" "r")))]
  "TARGET_RVP"
  "abs\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "riscv_cls<mode>_p"
  [(set (match_operand:X 0 "register_operand" "=r")
        (unspec:X [(match_operand:X 1 "register_operand" "r")]
         UNSPEC_CLS))]
  "TARGET_RVP"
  "cls\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "riscv_rev<mode>_p"
  [(set (match_operand:X 0 "register_operand" "=r")
        (unspec:X [(match_operand:X 1 "register_operand" "r")]
         UNSPEC_REV))]
  "TARGET_RVP"
  "rev\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;RV64 Only Scalar Intrinsics
(define_insn "riscv_absw_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (sign_extend:DI
          (abs:SI (match_operand:SI 1 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT"
  "absw\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

(define_insn "riscv_clsw_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (sign_extend:DI
          (unspec:SI [(match_operand:SI 1 "register_operand" "r")] UNSPEC_CLS)))]
  "TARGET_RVP && TARGET_64BIT"
  "clsw\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

(define_insn "riscv_rev16_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")]
         UNSPEC_REV16))]
  "TARGET_RVP && TARGET_64BIT"
  "rev16\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_insn "riscv_sha_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")]
         UNSPEC_SHA))]
  "TARGET_RVP && TARGET_64BIT"
  "sha\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_insn "riscv_shar_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")]
	 UNSPEC_SHAR))]
  "TARGET_RVP && TARGET_64BIT"
  "shar\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_insn "riscv_shl_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")]
         UNSPEC_SHL))]
  "TARGET_RVP && TARGET_64BIT"
  "shl\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_insn "riscv_shlr_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")]
	 UNSPEC_SHLR))]
  "TARGET_RVP && TARGET_64BIT"
  "shlr\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

;Packed Splat
(define_insn "riscv_pmv_s_u8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:QI 1 "nonmemory_operand" "r, Wpb")]
         UNSPEC_PLI))]
  "TARGET_RVP"
  "@
   pmv.bs\t%0,%1
   pli.b\t%0,%1"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pmv_s_i8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r, r")
        (unspec:V4QI [(match_operand:QI 1 "nonmemory_operand" "r, Wpb")]
         UNSPEC_PLI))]
  "TARGET_RVP"
  "@
   pmv.bs\t%0,%1
   pli.b\t%0,%1"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pmv_s_u16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r, r")
        (unspec:V2HI [(match_operand:HI 1 "nonmemory_operand" "r, Wpi, Wpu")]
         UNSPEC_PLI))]
  "TARGET_RVP"
  "@
   pmv.hs\t%0,%1
   pli.h\t%0,%1
   plui.h\t%0,%1"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_pmv_s_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r, r, r")
        (unspec:V2HI [(match_operand:HI 1 "nonmemory_operand" "r, Wpi, Wpu")]
         UNSPEC_PLI))]
  "TARGET_RVP"
  "@
   pmv.hs\t%0,%1
   pli.h\t%0,%1
   plui.h\t%0,%1"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_pmv_s_u8x8"
  [(set (match_operand:V8QI 0 "register_operand")
        (unspec:V8QI [(match_operand:QI 1 "nonmemory_operand")]
         UNSPEC_PLI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_pmv_s_u8x8_rv64 (operands[0], operands[1]));
    }
  else
    {
      emit_insn (gen_riscv_pmv_s_u8x8_rv32 (operands[0], operands[1]));
    }
  DONE;
})

(define_insn "riscv_pmv_s_u8x8_rv32"
  [(set (match_operand:V8QI 0 "register_operand" "=R, R")
        (unspec:V8QI [(match_operand:QI 1 "nonmemory_operand" "r, Wpb")]
         UNSPEC_PLI))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pmv.dbs\t%0,%1
   pli.db\t%0,%1"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pmv_s_u8x8_rv64"
  [(set (match_operand:V8QI 0 "register_operand" "=r, r")
        (unspec:V8QI [(match_operand:QI 1 "nonmemory_operand" "r, Wpb")]
         UNSPEC_PLI))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pmv.bs\t%0,%1
   pli.b\t%0,%1"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_pmv_s_i8x8"
  [(set (match_operand:V8QI 0 "register_operand")
        (unspec:V8QI [(match_operand:QI 1 "nonmemory_operand")]
         UNSPEC_PLI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_pmv_s_i8x8_rv64 (operands[0], operands[1]));
    }
  else
    {
      emit_insn (gen_riscv_pmv_s_i8x8_rv32 (operands[0], operands[1]));
    }
  DONE;
})

(define_insn "riscv_pmv_s_i8x8_rv32"
  [(set (match_operand:V8QI 0 "register_operand" "=R, R")
        (unspec:V8QI [(match_operand:QI 1 "nonmemory_operand" "r, Wpb")]
         UNSPEC_PLI))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pmv.dbs\t%0,%1
   pli.db\t%0,%1"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pmv_s_i8x8_rv64"
  [(set (match_operand:V8QI 0 "register_operand" "=r, r")
        (unspec:V8QI [(match_operand:QI 1 "nonmemory_operand" "r, Wpb")]
         UNSPEC_PLI))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pmv.bs\t%0,%1
   pli.b\t%0,%1"
  [(set_attr "type" "simd, simd")])

(define_expand "riscv_pmv_s_u16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:HI 1 "nonmemory_operand")]
         UNSPEC_PLI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_pmv_s_u16x4_rv64 (operands[0], operands[1]));
    }
  else
    {
      emit_insn (gen_riscv_pmv_s_u16x4_rv32 (operands[0], operands[1]));
    }
  DONE;
})

(define_insn "riscv_pmv_s_u16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R, R, R")
        (unspec:V4HI [(match_operand:HI 1 "nonmemory_operand" "r, Wpi, Wpu")]
         UNSPEC_PLI))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pmv.dhs\t%0,%1
   pli.dh\t%0,%1
   plui.dh\t%0,%1"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_pmv_s_u16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r, r, r")
        (unspec:V4HI [(match_operand:HI 1 "nonmemory_operand" "r, Wpi, Wpu")]
         UNSPEC_PLI))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pmv.hs\t%0,%1
   pli.h\t%0,%1
   plui.h\t%0,%1"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_pmv_s_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:HI 1 "nonmemory_operand")]
         UNSPEC_PLI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_pmv_s_i16x4_rv64 (operands[0], operands[1]));
    }
  else
    {
      emit_insn (gen_riscv_pmv_s_i16x4_rv32 (operands[0], operands[1]));
    }
  DONE;
})

(define_insn "riscv_pmv_s_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R, R, R")
        (unspec:V4HI [(match_operand:HI 1 "nonmemory_operand" "r, Wpi, Wpu")]
         UNSPEC_PLI))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pmv.dhs\t%0,%1
   pli.dh\t%0,%1
   plui.dh\t%0,%1"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_pmv_s_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r, r, r")
        (unspec:V4HI [(match_operand:HI 1 "nonmemory_operand" "r, Wpi, Wpu")]
         UNSPEC_PLI))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pmv.hs\t%0,%1
   pli.h\t%0,%1
   plui.h\t%0,%1"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_pmv_s_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:SI 1 "nonmemory_operand")]
         UNSPEC_PLI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_pmv_s_u32x2_rv64 (operands[0], operands[1]));
    }
  else
    {
      if (!register_operand (operands[1], SImode))
        operands[1] = force_reg (SImode, operands[1]);
      emit_insn (gen_riscv_pmv_s_u32x2_rv32 (operands[0], operands[1]));
    }
  DONE;
})

(define_insn "riscv_pmv_s_u32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:SI 1 "register_operand" "r")]
         UNSPEC_PLI))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmv.dws\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmv_s_u32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r, r, r")
        (unspec:V2SI [(match_operand:SI 1 "nonmemory_operand" "r, Wpi, Wpw")]
         UNSPEC_PLI))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pmv.ws\t%0,%1
   pli.w\t%0,%1
   plui.w\t%0,%1"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_pmv_s_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:SI 1 "nonmemory_operand")]
         UNSPEC_PLI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_pmv_s_i32x2_rv64 (operands[0], operands[1]));
    }
  else
    {
      if (!register_operand (operands[1], SImode))
        operands[1] = force_reg (SImode, operands[1]);
      emit_insn (gen_riscv_pmv_s_i32x2_rv32 (operands[0], operands[1]));
    }
  DONE;
})

(define_insn "riscv_pmv_s_i32x2_rv32"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:SI 1 "register_operand" "r")]
         UNSPEC_PLI))]
  "TARGET_RVP && !TARGET_64BIT"
  "pmv.dws\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmv_s_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r, r, r")
        (unspec:V2SI [(match_operand:SI 1 "nonmemory_operand" "r, Wpi, Wpw")]
         UNSPEC_PLI))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   pmv.ws\t%0,%1
   pli.w\t%0,%1
   plui.w\t%0,%1"
  [(set_attr "type" "simd, simd, simd")])

;Packed Addition and Subtraction (32-bit)
(define_insn "riscv_padd_<SAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP"
  "padd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_padd_<USAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP"
  "padd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Addition and Subtraction (64-bit)
(define_expand "riscv_padd_<SAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PADD))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_padd_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_padd_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_padd_<SAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP && !TARGET_64BIT"
  "padd.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_padd_<SAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP && TARGET_64BIT"
  "padd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_padd_<USAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PADD))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_padd_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_padd_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_padd_<USAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP && !TARGET_64BIT"
  "padd.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_padd_<USAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP && TARGET_64BIT"
  "padd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psub_<SAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PSUB))]
  "TARGET_RVP"
  "psub.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psub_<USAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PSUB))]
  "TARGET_RVP"
  "psub.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

; Packed Subtraction (64-bit)
(define_expand "riscv_psub_<SAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PSUB))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psub_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psub_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psub_<SAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSUB))]
  "TARGET_RVP && !TARGET_64BIT"
  "psub.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psub_<SAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSUB))]
  "TARGET_RVP && TARGET_64BIT"
  "psub.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psub_<USAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PSUB))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psub_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psub_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psub_<USAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSUB))]
  "TARGET_RVP && !TARGET_64BIT"
  "psub.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psub_<USAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSUB))]
  "TARGET_RVP && TARGET_64BIT"
  "psub.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pneg_<SAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")]
         UNSPEC_PSUB))]
  "TARGET_RVP"
  "pneg.<SAT_SUFFIX>\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_pneg_<SAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")]
         UNSPEC_PSUB))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pneg_<SAT_NAME>_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pneg_<SAT_NAME>_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pneg_<SAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")]
         UNSPEC_PSUB))]
  "TARGET_RVP && !TARGET_64BIT"
  "pneg.<DSAT_SUFFIX>\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pneg_<SAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")]
         UNSPEC_PSUB))]
  "TARGET_RVP && TARGET_64BIT"
  "pneg.<SAT_SUFFIX>\t%0,%1"
  [(set_attr "type" "simd")])

; Packed Addition with Scalar (32-bit)
(define_insn "riscv_padd_s_<SAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:<SCALAR_MODE> 2 "nonmemory_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP"
  "padd.<SSUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_padd_s_<USAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:<SCALAR_MODE> 2 "nonmemory_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP"
  "padd.<SSUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

; Packed Addition with Scalar (64-bit)
(define_expand "riscv_padd_s_<SAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:<SCALAR_MODE> 2 "nonmemory_operand")]
         UNSPEC_PADD))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_padd_s_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_padd_s_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_padd_s_<SAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:<SCALAR_MODE> 2 "nonmemory_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP && !TARGET_64BIT"
  "padd.<DSSUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_padd_s_<SAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:<SCALAR_MODE> 2 "nonmemory_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP && TARGET_64BIT"
  "padd.<SSUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_padd_s_<USAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:<SCALAR_MODE> 2 "nonmemory_operand")]
         UNSPEC_PADD))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_padd_s_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_padd_s_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_padd_s_<USAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:<SCALAR_MODE> 2 "nonmemory_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP && !TARGET_64BIT"
  "padd.<DSSUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_padd_s_<USAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:<SCALAR_MODE> 2 "nonmemory_operand" "r")]
         UNSPEC_PADD))]
  "TARGET_RVP && TARGET_64BIT"
  "padd.<SSUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Saturating Addition and Subtraction

(define_insn "riscv_psadd_<SAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PSADD))]
  "TARGET_RVP"
  "psadd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psaddu_<USAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PSADDU))]
  "TARGET_RVP"
  "psaddu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pssub_<SAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PSSUB))]
  "TARGET_RVP"
  "pssub.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pssubu_<USAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PSSUBU))]
  "TARGET_RVP"
  "pssubu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psadd_<SAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PSADD))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psadd_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psadd_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psadd_<SAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSADD))]
  "TARGET_RVP && !TARGET_64BIT"
  "psadd.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psadd_<SAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSADD))]
  "TARGET_RVP && TARGET_64BIT"
  "psadd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psaddu_<USAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PSADDU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psaddu_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psaddu_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psaddu_<USAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSADDU))]
  "TARGET_RVP && !TARGET_64BIT"
  "psaddu.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psaddu_<USAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSADDU))]
  "TARGET_RVP && TARGET_64BIT"
  "psaddu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pssub_<SAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PSSUB))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pssub_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pssub_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pssub_<SAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSSUB))]
  "TARGET_RVP && !TARGET_64BIT"
  "pssub.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pssub_<SAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSSUB))]
  "TARGET_RVP && TARGET_64BIT"
  "pssub.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pssubu_<USAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PSSUBU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pssubu_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pssubu_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pssubu_<USAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSSUBU))]
  "TARGET_RVP && !TARGET_64BIT"
  "pssubu.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pssubu_<USAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PSSUBU))]
  "TARGET_RVP && TARGET_64BIT"
  "pssubu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Averaging Addition and Subtraction

(define_insn "riscv_paadd_<SAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PAADD))]
  "TARGET_RVP"
  "paadd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_paaddu_<USAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PAADDU))]
  "TARGET_RVP"
  "paaddu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pasub_<SAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PASUB))]
  "TARGET_RVP"
  "pasub.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pasubu_<USAT_NAME>"
  [(set (match_operand:SAT32 0 "register_operand" "=r")
        (unspec:SAT32 [(match_operand:SAT32 1 "register_operand" "r")
                       (match_operand:SAT32 2 "register_operand" "r")]
         UNSPEC_PASUBU))]
  "TARGET_RVP"
  "pasubu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_paadd_<SAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PAADD))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_paadd_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_paadd_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_paadd_<SAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PAADD))]
  "TARGET_RVP && !TARGET_64BIT"
  "paadd.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_paadd_<SAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PAADD))]
  "TARGET_RVP && TARGET_64BIT"
  "paadd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_paaddu_<USAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PAADDU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_paaddu_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_paaddu_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_paaddu_<USAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PAADDU))]
  "TARGET_RVP && !TARGET_64BIT"
  "paaddu.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_paaddu_<USAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PAADDU))]
  "TARGET_RVP && TARGET_64BIT"
  "paaddu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pasub_<SAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PASUB))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pasub_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pasub_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pasub_<SAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PASUB))]
  "TARGET_RVP && !TARGET_64BIT"
  "pasub.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pasub_<SAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PASUB))]
  "TARGET_RVP && TARGET_64BIT"
  "pasub.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pasubu_<USAT_NAME>"
  [(set (match_operand:SAT64 0 "register_operand")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand")
                       (match_operand:SAT64 2 "register_operand")]
         UNSPEC_PASUBU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pasubu_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pasubu_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pasubu_<USAT_NAME>_rv32"
  [(set (match_operand:SAT64 0 "register_operand" "=R")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PASUBU))]
  "TARGET_RVP && !TARGET_64BIT"
  "pasubu.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pasubu_<USAT_NAME>_rv64"
  [(set (match_operand:SAT64 0 "register_operand" "=r")
        (unspec:SAT64 [(match_operand:SAT64 1 "register_operand" "r")
                       (match_operand:SAT64 2 "register_operand" "r")]
         UNSPEC_PASUBU))]
  "TARGET_RVP && TARGET_64BIT"
  "pasubu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Shift-Add

(define_insn "riscv_psh1add_<SAT_NAME>"
  [(set (match_operand:SHADD32 0 "register_operand" "=r")
        (unspec:SHADD32 [(match_operand:SHADD32 1 "register_operand" "r")
                         (match_operand:SHADD32 2 "register_operand" "r")]
         UNSPEC_PSH1ADD))]
  "TARGET_RVP"
  "psh1add.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psh1add_<USAT_NAME>"
  [(set (match_operand:SHADD32 0 "register_operand" "=r")
        (unspec:SHADD32 [(match_operand:SHADD32 1 "register_operand" "r")
                         (match_operand:SHADD32 2 "register_operand" "r")]
         UNSPEC_PSH1ADD))]
  "TARGET_RVP"
  "psh1add.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pssh1sadd_<SAT_NAME>"
  [(set (match_operand:SHADD32 0 "register_operand" "=r")
        (unspec:SHADD32 [(match_operand:SHADD32 1 "register_operand" "r")
                         (match_operand:SHADD32 2 "register_operand" "r")]
         UNSPEC_PSSH1SADD))]
  "TARGET_RVP"
  "pssh1sadd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psh1add_<SAT_NAME>"
  [(set (match_operand:SHADD64 0 "register_operand")
        (unspec:SHADD64 [(match_operand:SHADD64 1 "register_operand")
                         (match_operand:SHADD64 2 "register_operand")]
         UNSPEC_PSH1ADD))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psh1add_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psh1add_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psh1add_<SAT_NAME>_rv32"
  [(set (match_operand:SHADD64 0 "register_operand" "=R")
        (unspec:SHADD64 [(match_operand:SHADD64 1 "register_operand" "r")
                         (match_operand:SHADD64 2 "register_operand" "r")]
         UNSPEC_PSH1ADD))]
  "TARGET_RVP && !TARGET_64BIT"
  "psh1add.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psh1add_<SAT_NAME>_rv64"
  [(set (match_operand:SHADD64 0 "register_operand" "=r")
        (unspec:SHADD64 [(match_operand:SHADD64 1 "register_operand" "r")
                         (match_operand:SHADD64 2 "register_operand" "r")]
         UNSPEC_PSH1ADD))]
  "TARGET_RVP && TARGET_64BIT"
  "psh1add.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psh1add_<USAT_NAME>"
  [(set (match_operand:SHADD64 0 "register_operand")
        (unspec:SHADD64 [(match_operand:SHADD64 1 "register_operand")
                         (match_operand:SHADD64 2 "register_operand")]
         UNSPEC_PSH1ADD))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psh1add_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psh1add_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psh1add_<USAT_NAME>_rv32"
  [(set (match_operand:SHADD64 0 "register_operand" "=R")
        (unspec:SHADD64 [(match_operand:SHADD64 1 "register_operand" "r")
                         (match_operand:SHADD64 2 "register_operand" "r")]
         UNSPEC_PSH1ADD))]
  "TARGET_RVP && !TARGET_64BIT"
  "psh1add.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psh1add_<USAT_NAME>_rv64"
  [(set (match_operand:SHADD64 0 "register_operand" "=r")
        (unspec:SHADD64 [(match_operand:SHADD64 1 "register_operand" "r")
                         (match_operand:SHADD64 2 "register_operand" "r")]
         UNSPEC_PSH1ADD))]
  "TARGET_RVP && TARGET_64BIT"
  "psh1add.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pssh1sadd_<SAT_NAME>"
  [(set (match_operand:SHADD64 0 "register_operand")
        (unspec:SHADD64 [(match_operand:SHADD64 1 "register_operand")
                         (match_operand:SHADD64 2 "register_operand")]
         UNSPEC_PSSH1SADD))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pssh1sadd_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pssh1sadd_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pssh1sadd_<SAT_NAME>_rv32"
  [(set (match_operand:SHADD64 0 "register_operand" "=R")
        (unspec:SHADD64 [(match_operand:SHADD64 1 "register_operand" "r")
                         (match_operand:SHADD64 2 "register_operand" "r")]
         UNSPEC_PSSH1SADD))]
  "TARGET_RVP && !TARGET_64BIT"
  "pssh1sadd.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pssh1sadd_<SAT_NAME>_rv64"
  [(set (match_operand:SHADD64 0 "register_operand" "=r")
        (unspec:SHADD64 [(match_operand:SHADD64 1 "register_operand" "r")
                         (match_operand:SHADD64 2 "register_operand" "r")]
         UNSPEC_PSSH1SADD))]
  "TARGET_RVP && TARGET_64BIT"
  "pssh1sadd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Exchanged Addition and Subtraction
;
; Each instruction performs a cross add/subtract on packed halfword or word
; pairs: within each 32-bit word, the even (lower) element of rs1 is combined
; with the odd (upper) element of rs2 and vice versa.  The six variants are:
;   pas  : even=sub, odd=add        (wrap)
;   psa  : even=add, odd=sub        (wrap)
;   psas : even=sat(sub), odd=sat(add)
;   pssa : even=sat(add), odd=sat(sub)
;   paas : even=(sub)>>1, odd=(add)>>1   (averaging)
;   pasa : even=(add)>>1, odd=(sub)>>1   (averaging)
;
; Suffixes: i16x2/i16x4(RV64) use .hx, i16x4(RV32) uses .dhx, i32x2(RV64) uses
; .wx.  On RV32 the i32x2 pas/psa variants have no cross-word instruction and
; are expanded to a pair of scalar add/sub instructions.

(define_insn "riscv_pas_x_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PAS))]
  "TARGET_RVP"
  "pas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psa_x_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PSA))]
  "TARGET_RVP"
  "psa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psas_x_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PSAS))]
  "TARGET_RVP"
  "psas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pssa_x_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PSSA))]
  "TARGET_RVP"
  "pssa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_paas_x_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PAAS))]
  "TARGET_RVP"
  "paas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pasa_x_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PASA))]
  "TARGET_RVP"
  "pasa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pas_x_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PAS))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pas_x_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pas_x_i16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pas_x_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PAS))]
  "TARGET_RVP && !TARGET_64BIT"
  "pas.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pas_x_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PAS))]
  "TARGET_RVP && TARGET_64BIT"
  "pas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psa_x_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PSA))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psa_x_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psa_x_i16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psa_x_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PSA))]
  "TARGET_RVP && !TARGET_64BIT"
  "psa.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psa_x_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PSA))]
  "TARGET_RVP && TARGET_64BIT"
  "psa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psas_x_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PSAS))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psas_x_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_psas_x_i16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_psas_x_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PSAS))]
  "TARGET_RVP && !TARGET_64BIT"
  "psas.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psas_x_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PSAS))]
  "TARGET_RVP && TARGET_64BIT"
  "psas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pssa_x_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PSSA))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pssa_x_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pssa_x_i16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pssa_x_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PSSA))]
  "TARGET_RVP && !TARGET_64BIT"
  "pssa.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pssa_x_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PSSA))]
  "TARGET_RVP && TARGET_64BIT"
  "pssa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_paas_x_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PAAS))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_paas_x_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_paas_x_i16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_paas_x_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PAAS))]
  "TARGET_RVP && !TARGET_64BIT"
  "paas.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_paas_x_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PAAS))]
  "TARGET_RVP && TARGET_64BIT"
  "paas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pasa_x_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4HI 2 "register_operand")]
         UNSPEC_PASA))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pasa_x_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pasa_x_i16x4_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pasa_x_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PASA))]
  "TARGET_RVP && !TARGET_64BIT"
  "pasa.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pasa_x_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")
                      (match_operand:V4HI 2 "register_operand" "r")]
         UNSPEC_PASA))]
  "TARGET_RVP && TARGET_64BIT"
  "pasa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pas_x_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2SI 2 "register_operand")]
         UNSPEC_PAS))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pas_x_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        /* even = a_even - b_odd ; odd = a_odd + b_even  */
        machine_mode mode = GET_MODE (operands[0]);
        rtx out_lo = operand_subword (operands[0], 0, 1, mode);
        rtx out_hi = operand_subword (operands[0], 1, 1, mode);
        rtx a_lo = operand_subword_force (operands[1], 0, mode);
        rtx a_hi = operand_subword_force (operands[1], 1, mode);
        rtx b_lo = operand_subword_force (operands[2], 0, mode);
        rtx b_hi = operand_subword_force (operands[2], 1, mode);
        emit_insn (gen_subsi3 (out_lo, a_lo, b_hi));
        emit_insn (gen_addsi3 (out_hi, a_hi, b_lo));
    }
  DONE;
})

(define_insn "riscv_pas_x_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PAS))]
  "TARGET_RVP && TARGET_64BIT"
  "pas.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psa_x_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2SI 2 "register_operand")]
         UNSPEC_PSA))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psa_x_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        /* even = a_even + b_odd ; odd = a_odd - b_even  */
        machine_mode mode = GET_MODE (operands[0]);
        rtx out_lo = operand_subword (operands[0], 0, 1, mode);
        rtx out_hi = operand_subword (operands[0], 1, 1, mode);
        rtx a_lo = operand_subword_force (operands[1], 0, mode);
        rtx a_hi = operand_subword_force (operands[1], 1, mode);
        rtx b_lo = operand_subword_force (operands[2], 0, mode);
        rtx b_hi = operand_subword_force (operands[2], 1, mode);
        emit_insn (gen_addsi3 (out_lo, a_lo, b_hi));
        emit_insn (gen_subsi3 (out_hi, a_hi, b_lo));
    }
  DONE;
})

(define_insn "riscv_psa_x_i32x2_rv64"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PSA))]
  "TARGET_RVP && TARGET_64BIT"
  "psa.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

; TODO: Implement the RV32 i32x2 psas, pssa, paas and pasa operations using
; the scalar sadd, ssub, aadd and asub operations.
(define_insn "riscv_psas_x_i32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PSAS))]
  "TARGET_RVP && TARGET_64BIT"
  "psas.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pssa_x_i32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PSSA))]
  "TARGET_RVP && TARGET_64BIT"
  "pssa.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_paas_x_i32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PAAS))]
  "TARGET_RVP && TARGET_64BIT"
  "paas.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pasa_x_i32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand" "r")
                      (match_operand:V2SI 2 "register_operand" "r")]
         UNSPEC_PASA))]
  "TARGET_RVP && TARGET_64BIT"
  "pasa.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Absolute Value and Absolute Difference
;
; pabs is a pseudo-operation: pabs(rs1) = pabd(rs1, x0), so it is emitted as
; "pabd.<suffix> %0,%1,x0" per the P-ext proposal.
(define_insn "riscv_pabs_<SAT_NAME>"
  [(set (match_operand:ABD32 0 "register_operand" "=r")
        (unspec:ABD32 [(match_operand:ABD32 1 "register_operand" "r")]
         UNSPEC_PABD))]
  "TARGET_RVP"
  "pabd.<SAT_SUFFIX>\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pabd_<SAT_NAME>"
  [(set (match_operand:ABD32 0 "register_operand" "=r")
        (unspec:ABD32 [(match_operand:ABD32 1 "register_operand" "r")
                       (match_operand:ABD32 2 "register_operand" "r")]
         UNSPEC_PABD))]
  "TARGET_RVP"
  "pabd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pabdu_<USAT_NAME>"
  [(set (match_operand:ABD32 0 "register_operand" "=r")
        (unspec:ABD32 [(match_operand:ABD32 1 "register_operand" "r")
                       (match_operand:ABD32 2 "register_operand" "r")]
         UNSPEC_PABDU))]
  "TARGET_RVP"
  "pabdu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pabs_<SAT_NAME>"
  [(set (match_operand:ABD64 0 "register_operand")
        (unspec:ABD64 [(match_operand:ABD64 1 "register_operand")]
         UNSPEC_PABD))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pabs_<SAT_NAME>_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_pabs_<SAT_NAME>_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_pabs_<SAT_NAME>_rv32"
  [(set (match_operand:ABD64 0 "register_operand" "=R")
        (unspec:ABD64 [(match_operand:ABD64 1 "register_operand" "r")]
         UNSPEC_PABD))]
  "TARGET_RVP && !TARGET_64BIT"
  "pabd.<DSAT_SUFFIX>\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pabs_<SAT_NAME>_rv64"
  [(set (match_operand:ABD64 0 "register_operand" "=r")
        (unspec:ABD64 [(match_operand:ABD64 1 "register_operand" "r")]
         UNSPEC_PABD))]
  "TARGET_RVP && TARGET_64BIT"
  "pabd.<SAT_SUFFIX>\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_pabd_<SAT_NAME>"
  [(set (match_operand:ABD64 0 "register_operand")
        (unspec:ABD64 [(match_operand:ABD64 1 "register_operand")
                       (match_operand:ABD64 2 "register_operand")]
         UNSPEC_PABD))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pabd_<SAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pabd_<SAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pabd_<SAT_NAME>_rv32"
  [(set (match_operand:ABD64 0 "register_operand" "=R")
        (unspec:ABD64 [(match_operand:ABD64 1 "register_operand" "r")
                       (match_operand:ABD64 2 "register_operand" "r")]
         UNSPEC_PABD))]
  "TARGET_RVP && !TARGET_64BIT"
  "pabd.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pabd_<SAT_NAME>_rv64"
  [(set (match_operand:ABD64 0 "register_operand" "=r")
        (unspec:ABD64 [(match_operand:ABD64 1 "register_operand" "r")
                       (match_operand:ABD64 2 "register_operand" "r")]
         UNSPEC_PABD))]
  "TARGET_RVP && TARGET_64BIT"
  "pabd.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pabdu_<USAT_NAME>"
  [(set (match_operand:ABD64 0 "register_operand")
        (unspec:ABD64 [(match_operand:ABD64 1 "register_operand")
                       (match_operand:ABD64 2 "register_operand")]
         UNSPEC_PABDU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pabdu_<USAT_NAME>_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_pabdu_<USAT_NAME>_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_pabdu_<USAT_NAME>_rv32"
  [(set (match_operand:ABD64 0 "register_operand" "=R")
        (unspec:ABD64 [(match_operand:ABD64 1 "register_operand" "r")
                       (match_operand:ABD64 2 "register_operand" "r")]
         UNSPEC_PABDU))]
  "TARGET_RVP && !TARGET_64BIT"
  "pabdu.<DSAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pabdu_<USAT_NAME>_rv64"
  [(set (match_operand:ABD64 0 "register_operand" "=r")
        (unspec:ABD64 [(match_operand:ABD64 1 "register_operand" "r")
                       (match_operand:ABD64 2 "register_operand" "r")]
         UNSPEC_PABDU))]
  "TARGET_RVP && TARGET_64BIT"
  "pabdu.<SAT_SUFFIX>\t%0,%1,%2"
  [(set_attr "type" "simd")])

; TODO(difficult): Packed Absolute Difference Sum

;Packed Saturating Absolute Value

(define_insn "riscv_psabs_i8x4"
  [(set (match_operand:V4QI 0 "register_operand" "=r")
        (unspec:V4QI [(match_operand:V4QI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP"
  "psabs.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psabs_i16x2"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP"
  "psabs.h\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_psabs_i8x8"
  [(set (match_operand:V8QI 0 "register_operand")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand")]
         UNSPEC_PSABS))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psabs_i8x8_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_psabs_i8x8_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_psabs_i8x8_rv32"
  [(set (match_operand:V8QI 0 "register_operand" "=R")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP && !TARGET_64BIT"
  "psabs.db\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psabs_i8x8_rv64"
  [(set (match_operand:V8QI 0 "register_operand" "=r")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP && TARGET_64BIT"
  "psabs.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_psabs_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")]
         UNSPEC_PSABS))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_psabs_i16x4_rv64 (operands[0], operands[1]));
  else
    emit_insn (gen_riscv_psabs_i16x4_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_psabs_i16x4_rv32"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP && !TARGET_64BIT"
  "psabs.dh\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psabs_i16x4_rv64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP && TARGET_64BIT"
  "psabs.h\t%0,%1"
  [(set_attr "type" "simd")])

;Packed Reduction Sum

(define_expand "riscv_predsum_i8x4_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:V4QI 1 "register_operand")
                            (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx wide = gen_reg_rtx (DImode);
      rtx low = gen_lowpart (SImode, operands[1]);

      emit_insn (gen_zero_extendsidi2 (wide, low));
      emit_insn (gen_riscv_predsum_i8x8_i32_rv64
		 (operands[0], gen_lowpart (V8QImode, wide), operands[2]));
    }
  else
    emit_insn (gen_riscv_predsum_i8x4_i32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsum_i8x4_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4QI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsum.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u8x4_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:V4QI 1 "register_operand")
                            (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx wide = gen_reg_rtx (DImode);
      rtx low = gen_lowpart (SImode, operands[1]);

      emit_insn (gen_zero_extendsidi2 (wide, low));
      emit_insn (gen_riscv_predsumu_u8x8_u32_rv64
		 (operands[0], gen_lowpart (V8QImode, wide), operands[2]));
    }
  else
    emit_insn (gen_riscv_predsumu_u8x4_u32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsumu_u8x4_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4QI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsumu.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsum_i16x2_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:V2HI 1 "register_operand")
                            (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx wide = gen_reg_rtx (DImode);
      rtx low = gen_lowpart (SImode, operands[1]);

      emit_insn (gen_zero_extendsidi2 (wide, low));
      emit_insn (gen_riscv_predsum_i16x4_i32_rv64
		 (operands[0], gen_lowpart (V4HImode, wide), operands[2]));
    }
  else
    emit_insn (gen_riscv_predsum_i16x2_i32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsum_i16x2_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsum.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u16x2_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:V2HI 1 "register_operand")
                            (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx wide = gen_reg_rtx (DImode);
      rtx low = gen_lowpart (SImode, operands[1]);

      emit_insn (gen_zero_extendsidi2 (wide, low));
      emit_insn (gen_riscv_predsumu_u16x4_u32_rv64
		 (operands[0], gen_lowpart (V4HImode, wide), operands[2]));
    }
  else
    emit_insn (gen_riscv_predsumu_u16x2_u32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsumu_u16x2_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsumu.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsum_i8x8_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:V8QI 1 "register_operand")
                            (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_predsum_i8x8_i32_rv64
		 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_predsum_i8x8_i32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsum_i8x8_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V8QI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsum.dbs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u8x8_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:V8QI 1 "register_operand")
                            (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_predsumu_u8x8_u32_rv64
		 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_predsumu_u8x8_u32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsumu_u8x8_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V8QI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsumu.dbs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsum_i16x4_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:V4HI 1 "register_operand")
                            (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_predsum_i16x4_i32_rv64
		 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_predsum_i16x4_i32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsum_i16x4_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4HI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsum.dhs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u16x4_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:V4HI 1 "register_operand")
                            (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_predsumu_u16x4_u32_rv64
		 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_predsumu_u16x4_u32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsumu_u16x4_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4HI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsumu.dhs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_predsum_i8x8_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V8QI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
  "predsum.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_predsumu_u8x8_u32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V8QI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
  "predsumu.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_predsum_i16x4_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4HI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
  "predsum.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_predsumu_u16x4_u32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4HI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
  "predsumu.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

; TODO(difficult): RV32 i64 accumulate variants need wadda/waddau (unimplemented).
; These six i64 intrinsics are RV64-only for now.
(define_expand "riscv_predsum_i8x8_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V8QI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_predsum_i8x8_i64_rv64
	     (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsum_i8x8_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V8QI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
  "predsum.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u8x8_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V8QI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_predsumu_u8x8_u64_rv64
	     (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsumu_u8x8_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V8QI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
  "predsumu.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsum_i16x4_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V4HI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_predsum_i16x4_i64_rv64
	     (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsum_i16x4_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V4HI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
  "predsum.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u16x4_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V4HI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_predsumu_u16x4_u64_rv64
	     (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsumu_u16x4_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V4HI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
  "predsumu.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsum_i32x2_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2SI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_predsum_i32x2_i64_rv64
	     (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsum_i32x2_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V2SI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
  "predsum.ws\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u32x2_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:V2SI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_predsumu_u32x2_u64_rv64
	     (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsumu_u32x2_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V2SI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
  "predsumu.ws\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Widening Addition and Subtraction
;
;pwadd/pwsub widen two narrow sources (32-bit each) into one wide result
;(64-bit): two V4QI -> V4HI, or two V2HI -> V2SI.  Each lane is sign/zero
;extended then added/subtracted.
;  RV32: single real instruction pwadd.b/h, pwaddu.b/h, pwsub.b/h, pwsubu.b/h
;        (constraint Wpd,s,t: result in even-odd register pair, two scalar
;         source registers).  These are RV32-only hardware instructions.
;  RV64: no single widening add/sub instruction exists.  The spec gives
;        multi-instruction sequences (e.g. zip8p+psrai.h+psext.h.b+padd.h for
;        pwadd_i16x4, pli.h+zip16p+pm2add.h for pwadd_i32x2) that rely on
;        pm2add.h/pm2sub.h (multiply-parts-accumulate) to emulate widening
;        add/sub.  These sequences are intricate and their semantics via
;        pm2add is non-obvious, so RV64 is NOT implemented yet.
;        TODO: implement the RV64 sequences (or wait for a future RV64
;        register-pair widening extension, per proposal note).  For now the
;        builtins are simd32-only (see simd.def), so RV64 calls error out.
(define_insn "riscv_pwadd_i16x4"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4QI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PWADD_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwadd.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwadd_i32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWADD_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwadd.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwaddu_u16x4"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4QI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PWADDU_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwaddu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwaddu_u32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWADDU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwaddu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwsub_i16x4"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4QI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PWSUB_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsub.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwsub_i32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWSUB_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsub.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwsubu_u16x4"
  [(set (match_operand:V4HI 0 "register_operand" "=R")
        (unspec:V4HI [(match_operand:V4QI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PWSUBU_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsubu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwsubu_u32x2"
  [(set (match_operand:V2SI 0 "register_operand" "=R")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWSUBU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsubu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Widening Addition and Subtraction Accumulate
;
;pwadda/pwsuba are the accumulating forms of pwadd/pwsub: they widen rs1/rs2
;(two narrow 32-bit sources) and add/sub the wide result into the corresponding
;lanes of rd (a wide 64-bit accumulator): rd += widen(rs1) +/- widen(rs2).
;  RV32: single real instruction pwadda.b/h, pwaddau.b/h, pwsuba.b/h, pwsubau.h
;        (constraint Wpd,s,t: rd_p is a read-modify-write even-odd register
;         pair, s/t are the two narrow scalar sources).  RV32-only hardware.
;  RV64: no single widening accumulate instruction; spec gives multi-insn
;        sequences (zip8p+psrai.h+psext.h.b+padd.h+padd.h, pli.h+zip16p+
;        pm2adda.h, etc.) relying on pm2adda.h (multiply-parts-accumulate).
;        NOT implemented yet.  TODO.  Builtins are simd32-only.
;
;The C prototype is pwadda_i16x4(rd, rs1, rs2) -> rd': rd is a value input
;(the accumulator base) and the function returns the updated accumulator, so
;we model it as: copy rd into the output pair, then run the RMW accumulate
;instruction on that pair.  define_expand emits the copy (emit_move_insn)
;then the RMW insn (operand 0 is "+R", read-write).
(define_expand "riscv_pwadda_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4QI 2 "register_operand")
                      (match_operand:V4QI 3 "register_operand")]
         UNSPEC_PWADDA_B))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwadda_i16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwadda_i16x4_rmw"
  [(set (match_operand:V4HI 0 "register_operand" "+R")
        (unspec:V4HI [(match_dup 0)
                      (match_operand:V4QI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PWADDA_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwadda.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwadda_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PWADDA_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwadda_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwadda_i32x2_rmw"
  [(set (match_operand:V2SI 0 "register_operand" "+R")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWADDA_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwadda.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwaddau_u16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4QI 2 "register_operand")
                      (match_operand:V4QI 3 "register_operand")]
         UNSPEC_PWADDAU_B))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwaddau_u16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwaddau_u16x4_rmw"
  [(set (match_operand:V4HI 0 "register_operand" "+R")
        (unspec:V4HI [(match_dup 0)
                      (match_operand:V4QI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PWADDAU_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwaddau.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwaddau_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PWADDAU_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwaddau_u32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwaddau_u32x2_rmw"
  [(set (match_operand:V2SI 0 "register_operand" "+R")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWADDAU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwaddau.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwsuba_i16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4QI 2 "register_operand")
                      (match_operand:V4QI 3 "register_operand")]
         UNSPEC_PWSUBA_B))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwsuba_i16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwsuba_i16x4_rmw"
  [(set (match_operand:V4HI 0 "register_operand" "+R")
        (unspec:V4HI [(match_dup 0)
                      (match_operand:V4QI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PWSUBA_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsuba.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwsuba_i32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PWSUBA_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwsuba_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwsuba_i32x2_rmw"
  [(set (match_operand:V2SI 0 "register_operand" "+R")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWSUBA_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsuba.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwsubau_u16x4"
  [(set (match_operand:V4HI 0 "register_operand")
        (unspec:V4HI [(match_operand:V4HI 1 "register_operand")
                      (match_operand:V4QI 2 "register_operand")
                      (match_operand:V4QI 3 "register_operand")]
         UNSPEC_PWSUBAU_B))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwsubau_u16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwsubau_u16x4_rmw"
  [(set (match_operand:V4HI 0 "register_operand" "+R")
        (unspec:V4HI [(match_dup 0)
                      (match_operand:V4QI 1 "register_operand" "r")
                      (match_operand:V4QI 2 "register_operand" "r")]
         UNSPEC_PWSUBAU_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsubau.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwsubau_u32x2"
  [(set (match_operand:V2SI 0 "register_operand")
        (unspec:V2SI [(match_operand:V2SI 1 "register_operand")
                      (match_operand:V2HI 2 "register_operand")
                      (match_operand:V2HI 3 "register_operand")]
         UNSPEC_PWSUBAU_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwsubau_u32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwsubau_u32x2_rmw"
  [(set (match_operand:V2SI 0 "register_operand" "+R")
        (unspec:V2SI [(match_dup 0)
                      (match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
         UNSPEC_PWSUBAU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsubau.h\t%0,%1,%2"
  [(set_attr "type" "simd")])
