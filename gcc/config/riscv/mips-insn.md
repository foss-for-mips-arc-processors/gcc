;; Machine description for MIPS custom instructions.
;; Copyright (C) 2025-2026 Free Software Foundation, Inc.

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

(define_insn "*mov<GPR:mode><X:mode>cc_bitmanip"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(if_then_else:GPR (any_eq:X (match_operand:X 1 "register_operand" "r")
				    (match_operand:X 2 "const_0_operand" "J"))
			  (match_operand:GPR 3 "reg_or_0_operand" "rJ")
			  (match_operand:GPR 4 "reg_or_0_operand" "rJ")))]
  "TARGET_XMIPSCMOV"
{
  enum rtx_code code = <CODE>;
  if (code == NE)
    return "mips.ccmov\t%0,%1,%z3,%z4";
  else
    return "mips.ccmov\t%0,%1,%z4,%z3";
}
[(set_attr "type" "condmove")
 (set_attr "mode" "<GPR:MODE>")])

;; flti instruction
(define_insn "riscv_mips_flti"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SI 1 "flti_operand" "zlti")]
		   UNSPEC_FLTI))]
  "TARGET_XMIPSTRIG"
  "mips.flti.s %0,%1"
  [(set_attr "type" "flti")]
)

;; xmipstrig instructions
(define_expand "sinsf2"
  [(match_operand:SF 0 "register_operand")
   (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx scalereg = riscv_get_trig_scale_value (FLTI_CONST_1_BY_2PI);
    emit_insn (gen_mulsf3 (scalereg, operands[1], scalereg));
    emit_insn (gen_riscv_mips_fsin_hz (operands[0], scalereg));
    DONE;
  }
)

(define_expand "asinsf2"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx temp = riscv_output_asinf_hz (operands[0], operands[1]);
    rtx scalereg = riscv_get_trig_scale_value (FLTI_CONST_2PI);
    emit_insn (gen_mulsf3 (operands[0], temp, scalereg));
    DONE;
  }
)

(define_expand "riscv_mips_acosf_hz"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx temp = riscv_output_asinf_hz (operands[0], operands[1]);
    rtx const_0_25 = riscv_get_trig_const (FLI_CONST_0_25_INDEX);
    rtx temp_reg1 = gen_reg_rtx (SFmode);
    emit_move_insn (temp_reg1, const_0_25);
    emit_insn (gen_subsf3 (operands[0], temp_reg1, temp));
    DONE;
  }
)

(define_expand "acossf2"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    emit_insn (gen_riscv_mips_acosf_hz (operands[0], operands[1]));
    rtx scalereg = riscv_get_trig_scale_value (FLTI_CONST_2PI);
    emit_insn (gen_mulsf3 (operands[0], operands[0], scalereg));
    DONE;
  }
)

(define_insn "riscv_mips_fsin_hz"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SF 1 "register_operand" "f")]
		   UNSPEC_SIN))]
  "TARGET_XMIPSTRIG"
  "mips.fsinhz.s %0,%1"
  [(set_attr "type" "ftrig")]
)

(define_expand "cossf2"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx scalereg = riscv_get_trig_scale_value (FLTI_CONST_1_BY_2PI);
    emit_insn (gen_mulsf3 (scalereg, operands[1], scalereg));
    emit_insn (gen_riscv_mips_fcos_hz (operands[0], scalereg));
    DONE;
  }
)

(define_insn "riscv_mips_fcos_hz"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SF 1 "register_operand" "f")]
		   UNSPEC_COS))]
  "TARGET_XMIPSTRIG"
  "mips.fcoshz.s %0,%1"
  [(set_attr "type" "ftrig")]
)

(define_expand "tansf2"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx scalereg = riscv_get_trig_scale_value (FLTI_CONST_1_BY_2PI);
    emit_insn (gen_mulsf3 (scalereg, operands[1], scalereg));
    emit_insn (gen_riscv_mips_ftan_hz (operands[0], scalereg));
    DONE;
  }
)

(define_insn "riscv_mips_ftan_hz"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SF 1 "register_operand" "f")]
		   UNSPEC_TAN))]
  "TARGET_XMIPSTRIG"
  "mips.ftanhz.s %0,%1"
  [(set_attr "type" "ftrig")]
)

(define_expand "atansf2"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx scalereg = riscv_get_trig_scale_value (FLTI_CONST_2PI);
    emit_insn (gen_riscv_mips_fatan_hz (operands[0], operands[1]));
    emit_insn (gen_mulsf3 (operands[0], operands[0], scalereg));
    DONE;
  }
)

(define_insn "riscv_mips_fatan_hz"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SF 1 "register_operand" "f")]
		   UNSPEC_ATAN))]
  "TARGET_XMIPSTRIG"
  "mips.fatanhz.s %0,%1"
  [(set_attr "type" "ftrig")]
)

(define_insn "riscv_mips_fversin_hz"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SF 1 "register_operand" "f")]
		   UNSPEC_VERSIN))]
  "TARGET_XMIPSTRIG"
  "mips.fversinhz.s %0,%1"
  [(set_attr "type" "ftrig")]
)

(define_insn "riscv_mips_ffrecip"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SF 1 "register_operand" "f")]
		   UNSPEC_FRECIP))]
  "TARGET_XMIPSTRIG"
  "mips.ffrecip.s %0,%1"
  [(set_attr "type" "ftrig")]
)

(define_insn "riscv_mips_ffrsqrt"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SF 1 "register_operand" "f")]
		   UNSPEC_FRECIPSQRT))]
  "TARGET_XMIPSTRIG"
  {
      return "mips.ffrsqrt.s %0,%1";
  }
  [(set_attr "type" "ftrig")]
)

(define_expand "tanhsf2"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    emit_insn (gen_riscv_mips_fftanh (operands[0], operands[1]));
    DONE;
  }
)

(define_insn "riscv_mips_fftanh"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SF 1 "register_operand" "f")]
		   UNSPEC_TANH))]
  "TARGET_XMIPSTRIG"
  "mips.fftanh.s %0,%1"
  [(set_attr "type" "ftrig")]
)

(define_expand "log2sf2"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    emit_insn (gen_riscv_mips_fflog2 (operands[0], operands[1]));
    DONE;
  }
)

(define_expand "logsf2"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx scalereg = riscv_get_trig_scale_value (FLTI_CONST_LN_OF_2);
    emit_insn (gen_riscv_mips_fflog2 (operands[0], operands[1]));
    emit_insn (gen_mulsf3 (operands[0], operands[0], scalereg));
    DONE;
  }
)

(define_expand "log10sf2"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx scalereg = riscv_get_trig_scale_value (FLTI_CONST_LOG10_OF_2);
    emit_insn (gen_riscv_mips_fflog2 (operands[0], operands[1]));
    emit_insn (gen_mulsf3 (operands[0], operands[0], scalereg));
    DONE;
  }
)

(define_insn "riscv_mips_fflog2"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SF 1 "register_operand" "f")]
		   UNSPEC_LOG2F))]
  "TARGET_XMIPSTRIG"
  "mips.fflog2.s %0,%1"
  [(set_attr "type" "ftrig")]
)

(define_expand "expsf2"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx scalereg = riscv_get_trig_scale_value (FLTI_CONST_LOG2_OF_E);
    emit_insn (gen_mulsf3 (scalereg, operands[1], scalereg));
    emit_insn (gen_riscv_mips_ffexp2 (operands[0], scalereg));

    DONE;
  }
)

(define_expand "exp10sf2"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx scalereg = riscv_get_trig_scale_value (FLTI_CONST_LOG2_OF_10);
    emit_insn (gen_mulsf3 (scalereg, operands[1], scalereg));
    emit_insn (gen_riscv_mips_ffexp2 (operands[0], scalereg));

    DONE;
  }
)

(define_insn "riscv_mips_ffexp2"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SF 1 "register_operand" "f")]
		   UNSPEC_EXPF))]
  "TARGET_XMIPSTRIG"
  "mips.ffexp2.s %0,%1"
  [(set_attr "type" "ftrig")]
)

(define_insn "riscv_mips_ffsqrt"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(unspec:SF[(match_operand:SF 1 "register_operand" "f")]
		   UNSPEC_FFSQRT))]
  "TARGET_XMIPSTRIG"
  "mips.ffsqrt.s %0,%1"
  [(set_attr "type" "ftrig")]
)

(define_expand "hypotsf3"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")
	 (match_operand:SF 2 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx temp_reg1 = gen_reg_rtx (SFmode);
    rtx temp_reg2 = gen_reg_rtx (SFmode);

    emit_insn (gen_mulsf3 (temp_reg1, operands[1], operands[1]));
    emit_insn (gen_mulsf3 (temp_reg2, operands[2], operands[2]));
    emit_insn (gen_addsf3 (temp_reg2, temp_reg2, temp_reg1));
    emit_insn (gen_riscv_mips_ffsqrt (operands[0], temp_reg2));

    DONE;
  }
)

(define_expand "atan2sf3"
  [(match_operand:SF 0 "register_operand")
	 (match_operand:SF 1 "register_operand")
 	 (match_operand:SF 2 "register_operand")]
  "TARGET_XMIPSTRIG"
  {
    rtx temp_reg1 = gen_reg_rtx (SFmode);

    emit_insn (gen_divsf3 (temp_reg1, operands[1], operands[2]));
    emit_insn (gen_riscv_mips_fatan_hz (operands[0], temp_reg1));

    rtx scalereg = riscv_get_trig_scale_value (FLTI_CONST_2PI);
    emit_insn (gen_mulsf3 (operands[0], operands[0], scalereg));
    DONE;
  }
)
