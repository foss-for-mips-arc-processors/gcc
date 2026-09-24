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

;; Scalar comparison.

(define_int_iterator RVP_SCALAR_COMPARE
  [UNSPEC_PMSEQ UNSPEC_PMSLT UNSPEC_PMSGT UNSPEC_PMSLTU UNSPEC_PMSGTU])

(define_int_attr rvp_scalar_compare_builtin
  [(UNSPEC_PMSEQ "mseq_i32_u32")
   (UNSPEC_PMSLT "mslt_u32")
   (UNSPEC_PMSGT "msgt_u32")
   (UNSPEC_PMSLTU "msltu_u32")
   (UNSPEC_PMSGTU "msgtu_u32")])

(define_int_attr rvp_scalar_compare_insn
  [(UNSPEC_PMSEQ "mseq")
   (UNSPEC_PMSLT "mslt")
   (UNSPEC_PMSGT "msgt")
   (UNSPEC_PMSLTU "msltu")
   (UNSPEC_PMSGTU "msgtu")])

(define_int_attr rvp_scalar_inverse_compare_builtin
  [(UNSPEC_PMSEQ "msne_i32_u32")
   (UNSPEC_PMSLT "msge_u32")
   (UNSPEC_PMSGT "msle_u32")
   (UNSPEC_PMSLTU "msgeu_u32")
   (UNSPEC_PMSGTU "msleu_u32")])

(define_insn "riscv_<rvp_scalar_compare_builtin>"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")]
	 RVP_SCALAR_COMPARE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    return "p<rvp_scalar_compare_insn>.w\t%0,%1,%2";
  return "<rvp_scalar_compare_insn>\t%0,%1,%2";
}
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

;; Derived scalar comparisons are the inverse of the corresponding base
;; comparison.

(define_expand "riscv_<rvp_scalar_inverse_compare_builtin>"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:SI 1 "register_operand")
		    (match_operand:SI 2 "register_operand")]
	 RVP_SCALAR_COMPARE))]
  "TARGET_RVP"
{
  rtx tmp = gen_reg_rtx (SImode);
  emit_insn (gen_riscv_<rvp_scalar_compare_builtin>
	       (tmp, operands[1], operands[2]));
  riscv_emit_packed_not (operands[0], tmp, SImode);
  DONE;
})

;; Scalar 64-bit merge.  RV32 performs the operation on both halves of the
;; register pair.

(define_expand "riscv_merge_di"
  [(set (match_operand:DI 0 "register_operand")
	(unspec:DI [(match_operand:DI 1 "register_operand")
		    (match_operand:DI 2 "register_operand")
		    (match_operand:DI 3 "register_operand")]
	 UNSPEC_PMERGE))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_merge_di_rv64
	       (operands[0], operands[1], operands[2], operands[3]));
  else
    {
      rtx out0 = operand_subword (operands[0], 0, 1, DImode);
      rtx out1 = operand_subword (operands[0], 1, 1, DImode);
      rtx rs10 = operand_subword_force (operands[1], 0, DImode);
      rtx rs11 = operand_subword_force (operands[1], 1, DImode);
      rtx rs20 = operand_subword_force (operands[2], 0, DImode);
      rtx rs21 = operand_subword_force (operands[2], 1, DImode);
      rtx mask0 = operand_subword_force (operands[3], 0, DImode);
      rtx mask1 = operand_subword_force (operands[3], 1, DImode);

      emit_insn (gen_riscv_pmerge_si (out0, rs10, rs20, mask0));
      emit_insn (gen_riscv_pmerge_si (out1, rs11, rs21, mask1));
    }
  DONE;
})

(define_insn "riscv_merge_di_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r,r,r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r,0,r")
		    (match_operand:DI 2 "register_operand" "r,r,0")
		    (match_operand:DI 3 "register_operand" "0,r,r")]
	 UNSPEC_PMERGE))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   merge\t%0,%1,%2
   mvm\t%0,%2,%3
   mvmn\t%0,%1,%3"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

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
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP"
  "psext.h.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_pzext_b_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")]
         UNSPEC_PZEXT))]
  "TARGET_RVP"
  "ppaire.b\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_psext_b_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")]
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "psext.dh.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psext_b_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.h.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_psext_b_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")]
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
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP && !TARGET_64BIT"
  "psext.dw.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psext_b_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")]
         UNSPEC_PSEXT_B))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.w.b\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_psext_h_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")]
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
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")]
         UNSPEC_PSEXT_H))]
  "TARGET_RVP && !TARGET_64BIT"
  "psext.dw.h\t%0,%1"
  [(set_attr "type" "simd")])

(define_insn "riscv_psext_h_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")]
         UNSPEC_PSEXT_H))]
  "TARGET_RVP && TARGET_64BIT"
  "psext.w.h\t%0,%1"
  [(set_attr "type" "simd")])

(define_expand "riscv_pzext_b_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")]
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PZEXT))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.db\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pzext_b_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")]
         UNSPEC_PZEXT))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.b\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_expand "riscv_pzext_h_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")]
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
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")]
         UNSPEC_PZEXT))]
  "TARGET_RVP && !TARGET_64BIT"
  "ppaire.dh\t%0,%1,x0"
  [(set_attr "type" "simd")])

(define_insn "riscv_pzext_h_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")]
         UNSPEC_PZEXT))]
  "TARGET_RVP && TARGET_64BIT"
  "ppaire.h\t%0,%1,x0"
  [(set_attr "type" "simd")])

;; Scalar saturation.

(define_insn "riscv_sati_i32"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "sati_width5_operand" "Ws5")]
	 UNSPEC_SATI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    return "psati.w\t%0,%1,%2";
  return "sati\t%0,%1,%2";
}
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

(define_insn "riscv_usati_u32"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "const_int5_operand" "u5")]
	 UNSPEC_USATI))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    return "pusati.w\t%0,%1,%2";
  return "usati\t%0,%1,%2";
}
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

(define_insn "riscv_sati_i64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r")
		    (match_operand:SI 2 "sati_width6_operand" "Ws6")]
	 UNSPEC_SATI))]
  "TARGET_RVP && TARGET_64BIT"
  "sati\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_insn "riscv_usati_u64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r")
		    (match_operand:SI 2 "const_int6_operand" "u6")]
	 UNSPEC_USATI))]
  "TARGET_RVP && TARGET_64BIT"
  "usati\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

;; Packed saturation.

(define_insn "riscv_pusati_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int4_operand" "u4")]
         UNSPEC_PUSATI))]
  "TARGET_RVP"
  "pusati.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psati_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:SI 2 "sati_width4_operand" "Ws4")]
         UNSPEC_PSATI))]
  "TARGET_RVP"
  "psati.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pusati_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:SI 2 "const_int4_operand")]
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int4_operand" "u4")]
         UNSPEC_PUSATI))]
  "TARGET_RVP && !TARGET_64BIT"
  "pusati.dh\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pusati_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int4_operand" "u4")]
         UNSPEC_PUSATI))]
  "TARGET_RVP && TARGET_64BIT"
  "pusati.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pusati_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:SI 2 "const_int5_operand")]
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
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int5_operand" "u5")]
         UNSPEC_PUSATI))]
  "TARGET_RVP && !TARGET_64BIT"
  "pusati.dw\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pusati_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "const_int5_operand" "u5")]
         UNSPEC_PUSATI))]
  "TARGET_RVP && TARGET_64BIT"
  "pusati.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psati_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:SI 2 "sati_width4_operand")]
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
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "sati_width4_operand" "Ws4")]
         UNSPEC_PSATI))]
  "TARGET_RVP && !TARGET_64BIT"
  "psati.dh\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psati_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "sati_width4_operand" "Ws4")]
         UNSPEC_PSATI))]
  "TARGET_RVP && TARGET_64BIT"
  "psati.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psati_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:SI 2 "sati_width5_operand")]
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
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "sati_width5_operand" "Ws5")]
         UNSPEC_PSATI))]
  "TARGET_RVP && !TARGET_64BIT"
  "psati.dw\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psati_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "sati_width5_operand" "Ws5")]
         UNSPEC_PSATI))]
  "TARGET_RVP && TARGET_64BIT"
  "psati.w\t%0,%1,%2"
  [(set_attr "type" "simd")])
