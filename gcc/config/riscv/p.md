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
  UNSPEC_NCLIPU
  UNSPEC_NCLIPRU
  UNSPEC_NSRAR
  UNSPEC_NCLIP
  UNSPEC_NCLIPR
  UNSPEC_UNZIP8P
  UNSPEC_SLX
  UNSPEC_SRX
  UNSPEC_ZIP8P
  UNSPEC_ZIP16P
  UNSPEC_ZIP8HP
  UNSPEC_ZIP16HP
  UNSPEC_UNZIP16P
  UNSPEC_UNZIP8HP
  UNSPEC_UNZIP16HP
  UNSPEC_WZIP8P
  UNSPEC_WZIP16P
  UNSPEC_PSSLAI
  UNSPEC_SSLAI
  UNSPEC_PSEXT_B
  UNSPEC_PSEXT_H
  UNSPEC_PZEXT
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
  UNSPEC_PUSATI
  UNSPEC_PSABS
  UNSPEC_PABD
  UNSPEC_PABDU
  UNSPEC_PSATI
  UNSPEC_SATI
  UNSPEC_USATI
  UNSPEC_PABDSUMU
  UNSPEC_PABDSUMAU
  UNSPEC_PMUL
  UNSPEC_PPACK
  UNSPEC_PPAIRE
  UNSPEC_PPAIREO
  UNSPEC_PPAIROE
  UNSPEC_PPAIRO
  UNSPEC_PREV8
  UNSPEC_PREV16
  UNSPEC_PREV32
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
  UNSPEC_MACC_H00
  UNSPEC_MACC_H01
  UNSPEC_MACC_H11
  UNSPEC_MACCU_H00
  UNSPEC_MACCU_H01
  UNSPEC_MACCU_H11
  UNSPEC_MACCSU_H00
  UNSPEC_MACCSU_H11
  UNSPEC_PMACC_H00
  UNSPEC_PMACC_H01
  UNSPEC_PMACC_H11
  UNSPEC_PMACCU_H00
  UNSPEC_PMACCU_H01
  UNSPEC_PMACCU_H11
  UNSPEC_PMACCSU_H00
  UNSPEC_PMACCSU_H11
  UNSPEC_MACC_W00
  UNSPEC_MACC_W01
  UNSPEC_MACC_W11
  UNSPEC_MACCU_W00
  UNSPEC_MACCU_W01
  UNSPEC_MACCU_W11
  UNSPEC_MACCSU_W00
  UNSPEC_MACCSU_W11
  UNSPEC_PM4ADD_B
  UNSPEC_PM2ADD_H
  UNSPEC_PM2ADD_HX
  UNSPEC_PM4ADDU_B
  UNSPEC_PM2ADDU_H
  UNSPEC_PMQ2ADD_H
  UNSPEC_PMQR2ADD_H
  UNSPEC_PM2SADD_H
  UNSPEC_PM2SADD_HX
  UNSPEC_PM2SUB_H
  UNSPEC_PM2SUB_HX
  UNSPEC_PM4ADDSU_B
  UNSPEC_PM2ADDSU_H
  UNSPEC_PM4ADD_I8X8
  UNSPEC_PM2ADD_I16X4
  UNSPEC_PM2ADD_X_I16X4
  UNSPEC_PM4ADDU_U8X8
  UNSPEC_PM2ADDU_U16X4
  UNSPEC_PMQ2ADD_I16X4
  UNSPEC_PMQR2ADD_I16X4
  UNSPEC_PM2SADD_I16X4
  UNSPEC_PM2SADD_X_I16X4
  UNSPEC_PM2SUB_I16X4
  UNSPEC_PM2SUB_X_I16X4
  UNSPEC_PM4ADDSU_I8X8
  UNSPEC_PM2ADDSU_I16X4
  UNSPEC_PM2ADD_W
  UNSPEC_PM2ADD_WX
  UNSPEC_PM2ADDU_W
  UNSPEC_PMQ2ADD_W
  UNSPEC_PM2SUB_W
  UNSPEC_PM2SUB_WX
  UNSPEC_PM2ADDSU_W
  UNSPEC_PMQR2ADD_W
  UNSPEC_PM4ADD_H
  UNSPEC_PM4ADDU_H
  UNSPEC_PM4ADDSU_H
  UNSPEC_PM4ADDA_B
  UNSPEC_PM2ADDA_H
  UNSPEC_PM2ADDA_HX
  UNSPEC_PM4ADDAU_B
  UNSPEC_PM2ADDAU_H
  UNSPEC_PMQ2ADDA_H
  UNSPEC_PMQR2ADDA_H
  UNSPEC_PM2SUBA_H
  UNSPEC_PM2SUBA_HX
  UNSPEC_PM4ADDASU_B
  UNSPEC_PM2ADDASU_H
  UNSPEC_PM4ADDA_I8X8
  UNSPEC_PM2ADDA_I16X4
  UNSPEC_PM2ADDA_X_I16X4
  UNSPEC_PM4ADDAU_U8X8
  UNSPEC_PM2ADDAU_U16X4
  UNSPEC_PMQ2ADDA_I16X4
  UNSPEC_PMQR2ADDA_I16X4
  UNSPEC_PM2SUBA_I16X4
  UNSPEC_PM2SUBA_X_I16X4
  UNSPEC_PM4ADDASU_I8X8
  UNSPEC_PM2ADDASU_I16X4
  UNSPEC_PM2ADDA_W
  UNSPEC_PM2ADDA_WX
  UNSPEC_PM2ADDAU_W
  UNSPEC_PMQ2ADDA_W
  UNSPEC_PM2SUBA_W
  UNSPEC_PM2SUBA_WX
  UNSPEC_PM2ADDASU_W
  UNSPEC_PMQR2ADDA_W
  UNSPEC_PM4ADDA_H
  UNSPEC_PM4ADDAU_H
  UNSPEC_PM4ADDASU_H
  UNSPEC_PMULH_B0
  UNSPEC_PMULH_B1
  UNSPEC_PMULHSU_B0
  UNSPEC_PMULHSU_B1
  UNSPEC_MULH_H0
  UNSPEC_MULH_H1
  UNSPEC_MULHSU_H0
  UNSPEC_MULHSU_H1
  UNSPEC_PMHACC_B0
  UNSPEC_PMHACC_B1
  UNSPEC_PMHACCSU_B0
  UNSPEC_PMHACCSU_B1
  UNSPEC_MHACC_H0
  UNSPEC_MHACC_H1
  UNSPEC_MHACCSU_H0
  UNSPEC_MHACCSU_H1
  UNSPEC_PWMUL_B
  UNSPEC_PWMUL_H
  UNSPEC_PWMULU_B
  UNSPEC_PWMULU_H
  UNSPEC_PWMULSU_B
  UNSPEC_PWMULSU_H
  UNSPEC_PWMACC_H
  UNSPEC_PWMACCU_H
  UNSPEC_PWMACCSU_H
  UNSPEC_PMQWACC_H
  UNSPEC_PMQRWACC_H
  UNSPEC_PM2WADD_H
  UNSPEC_PM2WADD_HX
  UNSPEC_PM2WADDU_H
  UNSPEC_PM2WSUB_H
  UNSPEC_PM2WSUB_HX
  UNSPEC_PM2WADDSU_H
  UNSPEC_PM2WADDA_H
  UNSPEC_PM2WADDA_HX
  UNSPEC_PM2WADDAU_H
  UNSPEC_PM2WSUBA_H
  UNSPEC_PM2WSUBA_HX
  UNSPEC_PM2WADDASU_H
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


(define_mode_iterator VQI [(PV4QI "!TARGET_64BIT") (PV8QI "TARGET_64BIT")])
(define_mode_iterator VHI [(PV2HI "!TARGET_64BIT") (PV4HI "TARGET_64BIT")])
(define_mode_iterator V_SI [(SI "!TARGET_64BIT") (PV2SI "TARGET_64BIT")])
(define_mode_iterator SI_DI [(SI "!TARGET_64BIT") (DI "TARGET_64BIT")])
(define_mode_iterator VPSI [(SI "!TARGET_64BIT") (PV2SI "TARGET_64BIT")])
(define_mode_attr PSEXT [(PV2HI "PV4QI") (PV4HI "PV8QI")])
(define_mode_iterator VD_SI [(SI "!TARGET_64BIT") (PV2SI "TARGET_64BIT")])


(define_mode_iterator VQIHISI [(PV4QI "!TARGET_64BIT") (PV8QI "TARGET_64BIT")
                            (PV2HI "!TARGET_64BIT") (PV4HI "TARGET_64BIT")
                            (PV2SI "TARGET_64BIT")])

(define_mode_attr SUFFIX [(PV4QI "b") (PV8QI "b") (PV2HI "h") (PV4HI "h") (PV2SI "w")])
(define_mode_attr PMUL [(PV2HI "PV4QI") (PV4HI "PV8QI")])
(define_mode_iterator SAT32 [(PV4QI "true") (PV2HI "true")])
(define_mode_iterator SAT64 [(PV8QI "true") (PV4HI "true") (PV2SI "true")])
(define_mode_iterator SHADD32 [(PV2HI "true")])
(define_mode_iterator SHADD64 [(PV4HI "true") (PV2SI "true")])
(define_mode_attr SAT_NAME [(PV4QI "i8x4") (PV2HI "i16x2")
                            (PV8QI "i8x8") (PV4HI "i16x4")
                            (PV2SI "i32x2")])
(define_mode_attr USAT_NAME [(PV4QI "u8x4") (PV2HI "u16x2")
                             (PV8QI "u8x8") (PV4HI "u16x4")
                             (PV2SI "u32x2")])
(define_int_iterator RVP_EXCHANGE_I32X2
  [UNSPEC_PSAS UNSPEC_PSSA UNSPEC_PAAS UNSPEC_PASA])
(define_int_attr rvp_exchange_name
  [(UNSPEC_PSAS "psas_x_i32x2")
   (UNSPEC_PSSA "pssa_x_i32x2")
   (UNSPEC_PAAS "paas_x_i32x2")
   (UNSPEC_PASA "pasa_x_i32x2")])
(define_int_attr rvp_exchange_low
  [(UNSPEC_PSAS "ssub")
   (UNSPEC_PSSA "sadd")
   (UNSPEC_PAAS "asub")
   (UNSPEC_PASA "aadd")])
(define_int_attr rvp_exchange_high
  [(UNSPEC_PSAS "sadd")
   (UNSPEC_PSSA "ssub")
   (UNSPEC_PAAS "aadd")
   (UNSPEC_PASA "asub")])
(define_int_attr rvp_exchange_insn
  [(UNSPEC_PSAS "psas")
   (UNSPEC_PSSA "pssa")
   (UNSPEC_PAAS "paas")
   (UNSPEC_PASA "pasa")])
(define_mode_attr SAT_SUFFIX [(PV4QI "b") (PV2HI "h")
                              (PV8QI "b") (PV4HI "h") (PV2SI "w")])
(define_mode_attr DSAT_SUFFIX [(PV8QI "db") (PV4HI "dh") (PV2SI "dw")])
(define_mode_attr SSUFFIX [(PV4QI "bs") (PV2HI "hs")
                            (PV8QI "bs") (PV4HI "hs") (PV2SI "ws")])
(define_mode_attr DSSUFFIX [(PV8QI "dbs") (PV4HI "dhs") (PV2SI "dws")])
(define_mode_attr SCALAR_MODE [(PV4QI "QI") (PV2HI "HI")
                                (PV8QI "QI") (PV4HI "HI") (PV2SI "SI")])
(define_mode_iterator ABD32 [(PV4QI "true") (PV2HI "true")])
(define_mode_iterator ABD64 [(PV8QI "true") (PV4HI "true")])
; 64-bit packed modes excluding PV2SI (used by Packed Pair 8x8/16x4, where the
; 32x2 case is handled separately because its RV64 mnemonic is "pack"/ppaireo.w
; and its RV32 form is expanded to register moves).
(define_mode_iterator PAIR64 [(PV8QI "true") (PV4HI "true")])
(define_mode_iterator PMERGE32 [(PV4QI "true") (PV2HI "true")])
(define_mode_iterator PMERGE64 [(PV8QI "true") (PV4HI "true") (PV2SI "true")])
(define_mode_attr PMERGE_NAME [(PV4QI "i8x4") (PV2HI "i16x2")
                               (PV8QI "i8x8") (PV4HI "i16x4")
                               (PV2SI "i32x2")])
(define_mode_attr UPMERGE_NAME [(PV4QI "u8x4") (PV2HI "u16x2")
                                (PV8QI "u8x8") (PV4HI "u16x4")
                                (PV2SI "u32x2")])

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
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PAS))]
  "TARGET_RVP"
  "pas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psa_x_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PSA))]
  "TARGET_RVP"
  "psa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psas_x_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PSAS))]
  "TARGET_RVP"
  "psas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pssa_x_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PSSA))]
  "TARGET_RVP"
  "pssa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_paas_x_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PAAS))]
  "TARGET_RVP"
  "paas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pasa_x_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PASA))]
  "TARGET_RVP"
  "pasa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pas_x_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PAS))]
  "TARGET_RVP && !TARGET_64BIT"
  "pas.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pas_x_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PAS))]
  "TARGET_RVP && TARGET_64BIT"
  "pas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psa_x_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PSA))]
  "TARGET_RVP && !TARGET_64BIT"
  "psa.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psa_x_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PSA))]
  "TARGET_RVP && TARGET_64BIT"
  "psa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psas_x_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PSAS))]
  "TARGET_RVP && !TARGET_64BIT"
  "psas.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psas_x_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PSAS))]
  "TARGET_RVP && TARGET_64BIT"
  "psas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pssa_x_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PSSA))]
  "TARGET_RVP && !TARGET_64BIT"
  "pssa.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pssa_x_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PSSA))]
  "TARGET_RVP && TARGET_64BIT"
  "pssa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_paas_x_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PAAS))]
  "TARGET_RVP && !TARGET_64BIT"
  "paas.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_paas_x_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PAAS))]
  "TARGET_RVP && TARGET_64BIT"
  "paas.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pasa_x_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PASA))]
  "TARGET_RVP && !TARGET_64BIT"
  "pasa.dhx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pasa_x_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PASA))]
  "TARGET_RVP && TARGET_64BIT"
  "pasa.hx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pas_x_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")]
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
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PAS))]
  "TARGET_RVP && TARGET_64BIT"
  "pas.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psa_x_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")]
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
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PSA))]
  "TARGET_RVP && TARGET_64BIT"
  "psa.wx\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_<rvp_exchange_name>"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                       (match_operand:PV2SI 2 "register_operand")]
         RVP_EXCHANGE_I32X2))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_<rvp_exchange_name>_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      machine_mode mode = GET_MODE (operands[0]);
      rtx out_lo = operand_subword (operands[0], 0, 1, mode);
      rtx out_hi = operand_subword (operands[0], 1, 1, mode);
      rtx a_lo = operand_subword_force (operands[1], 0, mode);
      rtx a_hi = operand_subword_force (operands[1], 1, mode);
      rtx b_lo = operand_subword_force (operands[2], 0, mode);
      rtx b_hi = operand_subword_force (operands[2], 1, mode);
      emit_insn (gen_riscv_<rvp_exchange_low>_i32
		 (out_lo, a_lo, b_hi));
      emit_insn (gen_riscv_<rvp_exchange_high>_i32
		 (out_hi, a_hi, b_lo));
    }
  DONE;
})

(define_insn "riscv_<rvp_exchange_name>_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                       (match_operand:PV2SI 2 "register_operand" "r")]
         RVP_EXCHANGE_I32X2))]
  "TARGET_RVP && TARGET_64BIT"
  "<rvp_exchange_insn>.wx\t%0,%1,%2"
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

;Packed Absolute Difference Sum
;
;The hardware reduction covers all byte lanes in an XLEN-wide GPR.  The
;u8x4 RV64 expanders therefore clear the unused upper word before using the
;native instruction.  Conversely, the u8x8 RV32 expanders reduce the two
;words separately and combine the partial sums as required by the intrinsic
;specification.
(define_insn "riscv_pabdsumu_si_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")]
	 UNSPEC_PABDSUMU))]
  "TARGET_RVP && !TARGET_64BIT"
  "pabdsumu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pabdsumau_si_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
	(unspec:SI [(match_dup 0)
		    (match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")]
	 UNSPEC_PABDSUMAU))]
  "TARGET_RVP && !TARGET_64BIT"
  "pabdsumau.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pabdsumu_di_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r")
		    (match_operand:DI 2 "register_operand" "r")]
	 UNSPEC_PABDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
  "pabdsumu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pabdsumau_di_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
	(unspec:DI [(match_dup 0)
		    (match_operand:DI 1 "register_operand" "r")
		    (match_operand:DI 2 "register_operand" "r")]
	 UNSPEC_PABDSUMAU))]
  "TARGET_RVP && TARGET_64BIT"
  "pabdsumau.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pabdsumu_u8x4_u32"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:PV4QI 1 "register_operand")
		    (match_operand:PV4QI 2 "register_operand")]
	 UNSPEC_PABDSUMU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx dest = gen_reg_rtx (DImode);
      rtx r1 = gen_reg_rtx (DImode);
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2
		 (r1, gen_lowpart (SImode, operands[1])));
      emit_insn (gen_zero_extendsidi2
		 (r2, gen_lowpart (SImode, operands[2])));
      emit_insn (gen_riscv_pabdsumu_di_rv64 (dest, r1, r2));
      emit_move_insn (operands[0], gen_lowpart (SImode, dest));
    }
  else
    emit_insn (gen_riscv_pabdsumu_si_rv32
	       (operands[0], gen_lowpart (SImode, operands[1]),
		gen_lowpart (SImode, operands[2])));
  DONE;
})

(define_expand "riscv_pabdsumau_u8x4_u32"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:SI 1 "register_operand")
		    (match_operand:PV4QI 2 "register_operand")
		    (match_operand:PV4QI 3 "register_operand")]
	 UNSPEC_PABDSUMAU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx dest = gen_reg_rtx (DImode);
      rtx r1 = gen_reg_rtx (DImode);
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2 (dest, operands[1]));
      emit_insn (gen_zero_extendsidi2
		 (r1, gen_lowpart (SImode, operands[2])));
      emit_insn (gen_zero_extendsidi2
		 (r2, gen_lowpart (SImode, operands[3])));
      emit_insn (gen_riscv_pabdsumau_di_rv64 (dest, r1, r2));
      emit_move_insn (operands[0], gen_lowpart (SImode, dest));
    }
  else
    {
      emit_move_insn (operands[0], operands[1]);
      emit_insn (gen_riscv_pabdsumau_si_rv32
		 (operands[0], gen_lowpart (SImode, operands[2]),
		  gen_lowpart (SImode, operands[3])));
    }
  DONE;
})

(define_expand "riscv_pabdsumu_u8x8_u32"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:PV8QI 1 "register_operand")
		    (match_operand:PV8QI 2 "register_operand")]
	 UNSPEC_PABDSUMU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx dest = gen_reg_rtx (DImode);
      emit_insn (gen_riscv_pabdsumu_di_rv64
		 (dest, gen_lowpart (DImode, operands[1]),
		  gen_lowpart (DImode, operands[2])));
      emit_move_insn (operands[0], gen_lowpart (SImode, dest));
    }
  else
    {
      emit_insn (gen_riscv_pabdsumu_si_rv32
		 (operands[0], riscv_subword (operands[1], false),
		  riscv_subword (operands[2], false)));
      emit_insn (gen_riscv_pabdsumau_si_rv32
		 (operands[0], riscv_subword (operands[1], true),
		  riscv_subword (operands[2], true)));
    }
  DONE;
})

(define_expand "riscv_pabdsumu_u8x8_u64"
  [(set (match_operand:DI 0 "register_operand")
	(unspec:DI [(match_operand:PV8QI 1 "register_operand")
		    (match_operand:PV8QI 2 "register_operand")]
	 UNSPEC_PABDSUMU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pabdsumu_di_rv64
	       (operands[0], gen_lowpart (DImode, operands[1]),
		gen_lowpart (DImode, operands[2])));
  else
    {
      rtx sum1 = gen_reg_rtx (SImode);
      rtx sum2 = gen_reg_rtx (SImode);
      emit_insn (gen_riscv_pabdsumu_si_rv32
		 (sum1, riscv_subword (operands[1], false),
		  riscv_subword (operands[2], false)));
      emit_insn (gen_riscv_pabdsumu_si_rv32
		 (sum2, riscv_subword (operands[1], true),
		  riscv_subword (operands[2], true)));
      emit_insn (gen_rtx_SET
		 (operands[0],
		  gen_rtx_PLUS (DImode, gen_rtx_ZERO_EXTEND (DImode, sum1),
				gen_rtx_ZERO_EXTEND (DImode, sum2))));
    }
  DONE;
})

(define_expand "riscv_pabdsumau_u8x8_u32"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:SI 1 "register_operand")
		    (match_operand:PV8QI 2 "register_operand")
		    (match_operand:PV8QI 3 "register_operand")]
	 UNSPEC_PABDSUMAU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx dest = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2 (dest, operands[1]));
      emit_insn (gen_riscv_pabdsumau_di_rv64
		 (dest, gen_lowpart (DImode, operands[2]),
		  gen_lowpart (DImode, operands[3])));
      emit_move_insn (operands[0], gen_lowpart (SImode, dest));
    }
  else
    {
      emit_move_insn (operands[0], operands[1]);
      emit_insn (gen_riscv_pabdsumau_si_rv32
		 (operands[0], riscv_subword (operands[2], false),
		  riscv_subword (operands[3], false)));
      emit_insn (gen_riscv_pabdsumau_si_rv32
		 (operands[0], riscv_subword (operands[2], true),
		  riscv_subword (operands[3], true)));
    }
  DONE;
})

(define_expand "riscv_pabdsumau_u8x8_u64"
  [(set (match_operand:DI 0 "register_operand")
	(unspec:DI [(match_operand:DI 1 "register_operand")
		    (match_operand:PV8QI 2 "register_operand")
		    (match_operand:PV8QI 3 "register_operand")]
	 UNSPEC_PABDSUMAU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_move_insn (operands[0], operands[1]);
      emit_insn (gen_riscv_pabdsumau_di_rv64
		 (operands[0], gen_lowpart (DImode, operands[2]),
		  gen_lowpart (DImode, operands[3])));
    }
  else
    {
      rtx sum1 = gen_reg_rtx (SImode);
      rtx sum2 = gen_reg_rtx (SImode);
      emit_insn (gen_riscv_pabdsumu_si_rv32
		 (sum1, riscv_subword (operands[2], false),
		  riscv_subword (operands[3], false)));
      emit_insn (gen_riscv_pabdsumu_si_rv32
		 (sum2, riscv_subword (operands[2], true),
		  riscv_subword (operands[3], true)));
      emit_insn (gen_rtx_SET
		 (operands[0],
		  gen_rtx_PLUS
		   (DImode,
		    gen_rtx_PLUS (DImode,
				  gen_rtx_ZERO_EXTEND (DImode, sum1),
				  gen_rtx_ZERO_EXTEND (DImode, sum2)),
		    operands[1])));
    }
  DONE;
})

;Packed Saturating Absolute Value

(define_insn "riscv_psabs_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r")
        (unspec:PV4QI [(match_operand:PV4QI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP"
  "psabs.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psabs_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP"
  "psabs.h\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_psabs_i8x8"
  [(set (match_operand:PV8QI 0 "register_operand")
        (unspec:PV8QI [(match_operand:PV8QI 1 "register_operand")]
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
  [(set (match_operand:PV8QI 0 "register_operand" "=R")
        (unspec:PV8QI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP && !TARGET_64BIT"
  "psabs.db\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psabs_i8x8_rv64"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
        (unspec:PV8QI [(match_operand:PV8QI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP && TARGET_64BIT"
  "psabs.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_psabs_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")]
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP && !TARGET_64BIT"
  "psabs.dh\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psabs_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PSABS))]
  "TARGET_RVP && TARGET_64BIT"
  "psabs.h\t%0,%1"
  [(set_attr "type" "simd")])

;Packed Reduction Sum

(define_expand "riscv_predsum_i8x4_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV4QI 1 "register_operand")
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
		 (operands[0], gen_lowpart (PV8QImode, wide), operands[2]));
    }
  else
    emit_insn (gen_riscv_predsum_i8x4_i32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsum_i8x4_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV4QI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsum.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u8x4_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV4QI 1 "register_operand")
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
		 (operands[0], gen_lowpart (PV8QImode, wide), operands[2]));
    }
  else
    emit_insn (gen_riscv_predsumu_u8x4_u32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsumu_u8x4_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV4QI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsumu.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsum_i16x2_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand")
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
		 (operands[0], gen_lowpart (PV4HImode, wide), operands[2]));
    }
  else
    emit_insn (gen_riscv_predsum_i16x2_i32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsum_i16x2_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsum.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u16x2_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand")
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
		 (operands[0], gen_lowpart (PV4HImode, wide), operands[2]));
    }
  else
    emit_insn (gen_riscv_predsumu_u16x2_u32_rv32
		 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_predsumu_u16x2_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsumu.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsum_i8x8_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV8QI 1 "register_operand")
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
        (unspec:SI [(match_operand:PV8QI 1 "register_operand" "r")
                    (match_operand:SI 2 "reg_or_0_operand" "rJ")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsum.dbs\t%0,%1,%z2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u8x8_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV8QI 1 "register_operand")
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
        (unspec:SI [(match_operand:PV8QI 1 "register_operand" "r")
                    (match_operand:SI 2 "reg_or_0_operand" "rJ")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsumu.dbs\t%0,%1,%z2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsum_i16x4_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV4HI 1 "register_operand")
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
        (unspec:SI [(match_operand:PV4HI 1 "register_operand" "r")
                    (match_operand:SI 2 "reg_or_0_operand" "rJ")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsum.dhs\t%0,%1,%z2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u16x4_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV4HI 1 "register_operand")
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
        (unspec:SI [(match_operand:PV4HI 1 "register_operand" "r")
                    (match_operand:SI 2 "reg_or_0_operand" "rJ")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && !TARGET_64BIT"
  "predsumu.dhs\t%0,%1,%z2"
  [(set_attr "type" "simd")])

(define_insn "riscv_predsum_i8x8_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV8QI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
  "predsum.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_predsumu_u8x8_u32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV8QI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
  "predsumu.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_predsum_i16x4_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV4HI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
  "predsum.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_predsumu_u16x4_u32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV4HI 1 "register_operand" "r")
                            (match_operand:SI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
  "predsumu.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

;; The i64 RV32 expanders first reduce packed byte or halfword sources into a
;; 32-bit partial sum, then use wadda/waddau to update the 64-bit accumulator.
;; A two-word source can be accumulated directly by wadda/waddau.
(define_expand "riscv_predsum_i8x8_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV8QI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_predsum_i8x8_i64_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx sum = gen_reg_rtx (SImode);
      emit_insn (gen_riscv_predsum_i8x8_i32_rv32
		 (sum, operands[1], const0_rtx));
      emit_move_insn (operands[0], operands[2]);
      emit_insn (gen_rtx_SET
		 (operands[0],
		  gen_rtx_PLUS (DImode, gen_rtx_SIGN_EXTEND (DImode, sum),
				operands[0])));
    }
  DONE;
})

(define_insn "riscv_predsum_i8x8_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV8QI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
  "predsum.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u8x8_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV8QI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_predsumu_u8x8_u64_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx sum = gen_reg_rtx (SImode);
      emit_insn (gen_riscv_predsumu_u8x8_u32_rv32
		 (sum, operands[1], const0_rtx));
      emit_move_insn (operands[0], operands[2]);
      emit_insn (gen_rtx_SET
		 (operands[0],
		  gen_rtx_PLUS (DImode, gen_rtx_ZERO_EXTEND (DImode, sum),
				operands[0])));
    }
  DONE;
})

(define_insn "riscv_predsumu_u8x8_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV8QI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
  "predsumu.bs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsum_i16x4_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV4HI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_predsum_i16x4_i64_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx sum = gen_reg_rtx (SImode);
      emit_insn (gen_riscv_predsum_i16x4_i32_rv32
		 (sum, operands[1], const0_rtx));
      emit_move_insn (operands[0], operands[2]);
      emit_insn (gen_rtx_SET
		 (operands[0],
		  gen_rtx_PLUS (DImode, gen_rtx_SIGN_EXTEND (DImode, sum),
				operands[0])));
    }
  DONE;
})

(define_insn "riscv_predsum_i16x4_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV4HI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
  "predsum.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u16x4_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV4HI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_predsumu_u16x4_u64_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx sum = gen_reg_rtx (SImode);
      emit_insn (gen_riscv_predsumu_u16x4_u32_rv32
		 (sum, operands[1], const0_rtx));
      emit_move_insn (operands[0], operands[2]);
      emit_insn (gen_rtx_SET
		 (operands[0],
		  gen_rtx_PLUS (DImode, gen_rtx_ZERO_EXTEND (DImode, sum),
				operands[0])));
    }
  DONE;
})

(define_insn "riscv_predsumu_u16x4_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV4HI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
  "predsumu.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsum_i32x2_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_predsum_i32x2_i64_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx lo = riscv_subword (operands[1], false);
      rtx hi = riscv_subword (operands[1], true);
      emit_move_insn (operands[0], operands[2]);
      emit_insn (gen_rtx_SET
		 (operands[0],
		  gen_rtx_PLUS
		   (DImode,
		    gen_rtx_PLUS (DImode, gen_rtx_SIGN_EXTEND (DImode, lo),
				  gen_rtx_SIGN_EXTEND (DImode, hi)),
		    operands[0])));
    }
  DONE;
})

(define_insn "riscv_predsum_i32x2_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUM))]
  "TARGET_RVP && TARGET_64BIT"
  "predsum.ws\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_predsumu_u32x2_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand")
                            (match_operand:DI 2 "nonmemory_operand")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_predsumu_u32x2_u64_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx lo = riscv_subword (operands[1], false);
      rtx hi = riscv_subword (operands[1], true);
      emit_move_insn (operands[0], operands[2]);
      emit_insn (gen_rtx_SET
		 (operands[0],
		  gen_rtx_PLUS
		   (DImode,
		    gen_rtx_PLUS (DImode, gen_rtx_ZERO_EXTEND (DImode, lo),
				  gen_rtx_ZERO_EXTEND (DImode, hi)),
		    operands[0])));
    }
  DONE;
})

(define_insn "riscv_predsumu_u32x2_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand" "r")
                            (match_operand:DI 2 "nonmemory_operand" "r")]
         UNSPEC_PREDSUMU))]
  "TARGET_RVP && TARGET_64BIT"
  "predsumu.ws\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Widening Addition and Subtraction
;
;pwadd/pwsub widen two narrow sources (32-bit each) into one wide result
;(64-bit): two PV4QI -> PV4HI, or two PV2HI -> PV2SI.  Each lane is sign/zero
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PWADD_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwadd.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwadd_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PWADD_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwadd.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwaddu_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PWADDU_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwaddu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwaddu_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PWADDU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwaddu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwsub_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PWSUB_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsub.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwsub_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PWSUB_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsub.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwsubu_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PWSUBU_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsubu.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pwsubu_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
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
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4QI 2 "register_operand")
                      (match_operand:PV4QI 3 "register_operand")]
         UNSPEC_PWADDA_B))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwadda_i16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwadda_i16x4_rmw"
  [(set (match_operand:PV4HI 0 "register_operand" "+R")
        (unspec:PV4HI [(match_dup 0)
                      (match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PWADDA_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwadda.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwadda_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")
                      (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PWADDA_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwadda_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwadda_i32x2_rmw"
  [(set (match_operand:PV2SI 0 "register_operand" "+R")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PWADDA_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwadda.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwaddau_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4QI 2 "register_operand")
                      (match_operand:PV4QI 3 "register_operand")]
         UNSPEC_PWADDAU_B))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwaddau_u16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwaddau_u16x4_rmw"
  [(set (match_operand:PV4HI 0 "register_operand" "+R")
        (unspec:PV4HI [(match_dup 0)
                      (match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PWADDAU_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwaddau.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwaddau_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")
                      (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PWADDAU_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwaddau_u32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwaddau_u32x2_rmw"
  [(set (match_operand:PV2SI 0 "register_operand" "+R")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PWADDAU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwaddau.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwsuba_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4QI 2 "register_operand")
                      (match_operand:PV4QI 3 "register_operand")]
         UNSPEC_PWSUBA_B))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwsuba_i16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwsuba_i16x4_rmw"
  [(set (match_operand:PV4HI 0 "register_operand" "+R")
        (unspec:PV4HI [(match_dup 0)
                      (match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PWSUBA_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsuba.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwsuba_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")
                      (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PWSUBA_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwsuba_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwsuba_i32x2_rmw"
  [(set (match_operand:PV2SI 0 "register_operand" "+R")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PWSUBA_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsuba.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwsubau_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4QI 2 "register_operand")
                      (match_operand:PV4QI 3 "register_operand")]
         UNSPEC_PWSUBAU_B))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwsubau_u16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwsubau_u16x4_rmw"
  [(set (match_operand:PV4HI 0 "register_operand" "+R")
        (unspec:PV4HI [(match_dup 0)
                      (match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PWSUBAU_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsubau.b\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pwsubau_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")
                      (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PWSUBAU_H))]
  "TARGET_RVP && !TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pwsubau_u32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pwsubau_u32x2_rmw"
  [(set (match_operand:PV2SI 0 "register_operand" "+R")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PWSUBAU_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "pwsubau.h\t%0,%1,%2"
  [(set_attr "type" "simd")])
