;; Machine description for RISC-V Bit Manipulation operations.
;; Copyright (C) 2025-2026 Free Software Foundation, Inc.
;; Contributed by Jiawei Chen (jiawei@iscas.ac.cn) and 
;; Dongyan Chen (chendongyan@isrc.iscas.ac.cn), PLCT ISCAS.

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

;; Scalar Intrinsics

;; -----------------------------------------------------------------
;; Bitmanip scalar intrinsics (manual "Bitmanip" section).
;; Suffixed names: cls_32/cls_64, rev_32/rev_64, rev16_64, slx_32/slx_64,
;; srx_32/srx_64, wzip8p_64/wzip16p_64, zip/unzip {8,16}{,h}p_64.
;; -----------------------------------------------------------------

; cls_32: RV32 -> cls (32-bit CLS); RV64 -> clsw (32-bit CLS on low half).
(define_expand "riscv_cls_32_p"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")] UNSPEC_CLS))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx tmp = gen_reg_rtx (DImode);
      emit_insn (gen_riscv_clsw_32_p (tmp, operands[1]));
      emit_move_insn (operands[0], gen_lowpart (SImode, tmp));
    }
  else
    emit_insn (gen_riscv_cls_32_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_cls_32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")] UNSPEC_CLS))]
  "TARGET_RVP && !TARGET_64BIT"
  "cls\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

; On RV64 clsw writes an XLEN (64-bit) result; truncate to the SI result the
; prototype promises.
(define_insn "riscv_clsw_32_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (sign_extend:DI
          (unspec:SI [(match_operand:SI 1 "register_operand" "r")] UNSPEC_CLS)))]
  "TARGET_RVP && TARGET_64BIT"
  "clsw\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

; cls_64 (RV64 only): full 64-bit CLS, result is a small unsigned count;
; the prototype returns `unsigned`, but exposing it as DI matches the
; existing riscv_cls<mode>_p form and the count fits in 32 bits.
(define_insn "riscv_cls_64_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")] UNSPEC_CLS))]
  "TARGET_RVP && TARGET_64BIT"
  "cls\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

; rev_32: RV32 -> rev (bit-reverse 32 bits in a 32-bit reg);
; RV64 -> rev (reverse all 64 bits) then srai 32 to bring the 32-bit
; reversed result (which lands in bits 63..32) back to the low half.
(define_expand "riscv_rev_32_p"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")] UNSPEC_REV))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx tmp = gen_reg_rtx (DImode);
      emit_insn (gen_riscv_rev_32_rv64 (tmp, operands[1]));
      emit_move_insn (operands[0], gen_lowpart (SImode, tmp));
    }
  else
    emit_insn (gen_riscv_rev_32_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_rev_32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")] UNSPEC_REV))]
  "TARGET_RVP && !TARGET_64BIT"
  "rev\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

(define_insn "riscv_rev_32_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:SI 1 "register_operand" "r")] UNSPEC_REV))]
  "TARGET_RVP && TARGET_64BIT"
  "rev\t%0,%1\;srai\t%0,%0,32"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

; rev_64 / rev16_64 (RV64 only): single instruction on a 64-bit value.
(define_insn "riscv_rev_64_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")] UNSPEC_REV))]
  "TARGET_RVP && TARGET_64BIT"
  "rev\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_insn "riscv_rev16_64_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")] UNSPEC_REV16))]
  "TARGET_RVP && TARGET_64BIT"
  "rev16\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

; slx/srx are read-modify-write on rd (the first user argument): rd's prior
; value participates in the 2*XLEN concatenation.  Emit_move copies the user's
; rd into the target first, then the insn reuses that register via match_dup 0.

; slx_32: RV32 -> slx (32-bit); RV64 -> andi+slli+slx sequence.
; Mask the shift amount to the five bits used by RV32 and place rs1 in the
; high half of a 64-bit register.  The low 32 bits of the RV64 slx result are
; then the RV32 result.
;   andi  shamt, shamt, 31
;   slli  rs1, rs1, 32
;   slx   rd, rs1, shamt
(define_expand "riscv_slx_32_p"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:SI 2 "register_operand")
                    (match_operand:SI 3 "register_operand")] UNSPEC_SLX))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
      rtx rd = gen_reg_rtx (DImode);
      rtx rs1 = gen_reg_rtx (DImode);
      rtx shamt = gen_reg_rtx (DImode);
      emit_move_insn (rd, gen_lowpart (DImode, operands[0]));
      emit_insn (gen_ashldi3 (rs1, gen_lowpart (DImode, operands[2]),
			      GEN_INT (32)));
      emit_insn (gen_anddi3 (shamt, gen_lowpart (DImode, operands[3]),
			     GEN_INT (31)));
      emit_insn (gen_riscv_slx_64_raw (rd, rs1, shamt));
      emit_move_insn (operands[0], gen_lowpart (SImode, rd));
    }
  else
    emit_insn (gen_riscv_slx_32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_slx_32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:SI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")] UNSPEC_SLX))]
  "TARGET_RVP && !TARGET_64BIT"
  "slx\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

; slx_64 (RV64 only): single 64-bit RMW insn.
(define_expand "riscv_slx_64_p"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:DI 2 "register_operand")
                    (match_operand:SI 3 "register_operand")] UNSPEC_SLX))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_slx_64_raw (operands[0], operands[2],
				   gen_lowpart (DImode, operands[3])));
  DONE;
})

(define_insn "riscv_slx_64_raw"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")] UNSPEC_SLX))]
  "TARGET_RVP && TARGET_64BIT"
  "slx\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

; srx_32: RV32 -> srx (32-bit); RV64 -> ori+slli+srx sequence.
; Set bit 5 of the shift amount so that RV64 shifts by 32 plus the RV32
; five-bit shift amount, and place rd in the high half of a 64-bit register.
; The low 32 bits of the RV64 srx result are then the RV32 result.
;   ori   shamt, shamt, 32
;   slli  rd, rd, 32
;   srx   rd, rs1, shamt
(define_expand "riscv_srx_32_p"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:SI 2 "register_operand")
                    (match_operand:SI 3 "register_operand")] UNSPEC_SRX))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
      rtx rd = gen_reg_rtx (DImode);
      rtx shamt = gen_reg_rtx (DImode);
      emit_insn (gen_ashldi3 (rd, gen_lowpart (DImode, operands[0]),
			      GEN_INT (32)));
      emit_insn (gen_iordi3 (shamt, gen_lowpart (DImode, operands[3]),
			     GEN_INT (32)));
      emit_insn (gen_riscv_srx_64_raw
		   (rd, gen_lowpart (DImode, operands[2]), shamt));
      emit_move_insn (operands[0], gen_lowpart (SImode, rd));
    }
  else
    emit_insn (gen_riscv_srx_32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_srx_32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:SI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")] UNSPEC_SRX))]
  "TARGET_RVP && !TARGET_64BIT"
  "srx\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

; srx_64 (RV64 only): single 64-bit RMW insn.
(define_expand "riscv_srx_64_p"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:DI 2 "register_operand")
                    (match_operand:SI 3 "register_operand")] UNSPEC_SRX))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_srx_64_raw (operands[0], operands[2],
				   gen_lowpart (DImode, operands[3])));
  DONE;
})

(define_insn "riscv_srx_64_raw"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")] UNSPEC_SRX))]
  "TARGET_RVP && TARGET_64BIT"
  "srx\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

; wzip8p_64 / wzip16p_64: take two 32-bit sources, produce a 64-bit result.
; RV32 -> wzip8p/wzip16p into an even-odd register pair (=R);
; RV64 -> zip8p/zip16p into a single 64-bit register.
(define_expand "riscv_wzip8p_64_p"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:SI 1 "register_operand")
                    (match_operand:SI 2 "register_operand")] UNSPEC_WZIP8P))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_wzip8p_64_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_wzip8p_64_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_wzip8p_64_rv32"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (unspec:DI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")] UNSPEC_WZIP8P))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip8p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_wzip8p_64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")] UNSPEC_WZIP8P))]
  "TARGET_RVP && TARGET_64BIT"
  "zip8p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_wzip16p_64_p"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:SI 1 "register_operand")
                    (match_operand:SI 2 "register_operand")] UNSPEC_WZIP16P))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_wzip16p_64_rv64 (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_wzip16p_64_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_wzip16p_64_rv32"
  [(set (match_operand:DI 0 "register_operand" "=R")
        (unspec:DI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")] UNSPEC_WZIP16P))]
  "TARGET_RVP && !TARGET_64BIT"
  "wzip16p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_wzip16p_64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")] UNSPEC_WZIP16P))]
  "TARGET_RVP && TARGET_64BIT"
  "zip16p\t%0,%1,%2"
  [(set_attr "type" "simd")])

; zip/unzip {8,16}{,h}p_64 (RV64 only): single 64-bit insns, two 64-bit sources.
(define_insn "riscv_zip8p_64_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")] UNSPEC_ZIP8P))]
  "TARGET_RVP && TARGET_64BIT"
  "zip8p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_zip16p_64_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")] UNSPEC_ZIP16P))]
  "TARGET_RVP && TARGET_64BIT"
  "zip16p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_zip8hp_64_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")] UNSPEC_ZIP8HP))]
  "TARGET_RVP && TARGET_64BIT"
  "zip8hp\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_zip16hp_64_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")] UNSPEC_ZIP16HP))]
  "TARGET_RVP && TARGET_64BIT"
  "zip16hp\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_unzip8p_64_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")] UNSPEC_UNZIP8P))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip8p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_unzip16p_64_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")] UNSPEC_UNZIP16P))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip16p\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_unzip8hp_64_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")] UNSPEC_UNZIP8HP))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip8hp\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_unzip16hp_64_p"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "register_operand" "r")] UNSPEC_UNZIP16HP))]
  "TARGET_RVP && TARGET_64BIT"
  "unzip16hp\t%0,%1,%2"
  [(set_attr "type" "simd")])

;; Scalar saturating and averaging arithmetic.  RV64 uses the low word of
;; the corresponding packed instruction.  Describing the result in SImode
;; leaves the upper word unspecified until normal ABI extension is needed.

(define_int_iterator RVP_SCALAR_BINARY
  [UNSPEC_PSADD UNSPEC_PSADDU UNSPEC_PSSUB UNSPEC_PSSUBU
   UNSPEC_PAADD UNSPEC_PAADDU UNSPEC_PASUB UNSPEC_PASUBU
   UNSPEC_PSSH1SADD])

(define_int_attr rvp_scalar_builtin
  [(UNSPEC_PSADD "sadd_i32")
   (UNSPEC_PSADDU "saddu_u32")
   (UNSPEC_PSSUB "ssub_i32")
   (UNSPEC_PSSUBU "ssubu_u32")
   (UNSPEC_PAADD "aadd_i32")
   (UNSPEC_PAADDU "aaddu_u32")
   (UNSPEC_PASUB "asub_i32")
   (UNSPEC_PASUBU "asubu_u32")
   (UNSPEC_PSSH1SADD "ssh1sadd_i32")])

(define_int_attr rvp_scalar_insn
  [(UNSPEC_PSADD "sadd")
   (UNSPEC_PSADDU "saddu")
   (UNSPEC_PSSUB "ssub")
   (UNSPEC_PSSUBU "ssubu")
   (UNSPEC_PAADD "aadd")
   (UNSPEC_PAADDU "aaddu")
   (UNSPEC_PASUB "asub")
   (UNSPEC_PASUBU "asubu")
   (UNSPEC_PSSH1SADD "ssh1sadd")])

(define_insn "riscv_<rvp_scalar_builtin>"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")]
	 RVP_SCALAR_BINARY))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    return "p<rvp_scalar_insn>.w\t%0,%1,%2";
  return "<rvp_scalar_insn>\t%0,%1,%2";
}
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

;; Scalar absolute value.

(define_expand "riscv_abs_u32"
  [(set (match_operand:SI 0 "register_operand")
	(abs:SI (match_operand:SI 1 "register_operand")))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx tmp = gen_reg_rtx (DImode);
      emit_insn (gen_riscv_abs_u32_rv64 (tmp, operands[1]));
      emit_move_insn (operands[0], gen_lowpart (SImode, tmp));
    }
  else
    emit_insn (gen_riscv_abs_u32_rv32 (operands[0], operands[1]));
  DONE;
})

(define_insn "riscv_abs_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(abs:SI (match_operand:SI 1 "register_operand" "r")))]
  "TARGET_RVP && !TARGET_64BIT"
  "abs\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

(define_insn "riscv_abs_u32_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI
	  (abs:SI (match_operand:SI 1 "register_operand" "r"))))]
  "TARGET_RVP && TARGET_64BIT"
  "absw\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

(define_insn "riscv_abs_u64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(abs:DI (match_operand:DI 1 "register_operand" "r")))]
  "TARGET_RVP && TARGET_64BIT"
  "abs\t%0,%1"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])
