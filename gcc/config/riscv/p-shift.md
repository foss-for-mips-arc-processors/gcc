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
;; Scalar saturating and rounding shifts.

(define_expand "riscv_ssha_i32"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:SI 1 "register_operand")
		    (match_operand:SI 2 "nonmemory_operand")]
	 UNSPEC_PSSHA))]
  "TARGET_RVP"
{
  if (!CONST_INT_P (operands[2])
      || (!IN_RANGE (INTVAL (operands[2]), 0, 31)
	  && !IN_RANGE (INTVAL (operands[2]), -31, -1)))
    operands[2] = force_reg (SImode, operands[2]);
  emit_insn (gen_riscv_ssha_i32_insn
	     (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_ssha_i32_insn"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r,r,r")
		    (match_operand:SI 2 "arith_operand" "u5,w5,r")]
	 UNSPEC_PSSHA))]
  "TARGET_RVP"
{
  switch (which_alternative)
    {
    case 0:
      return TARGET_64BIT ? "psslai.w\t%0,%1,%2" : "sslai\t%0,%1,%2";
    case 1:
      return TARGET_64BIT ? "psrai.w\t%0,%1,%n2" : "srai\t%0,%1,%n2";
    default:
      return TARGET_64BIT ? "pssha.ws\t%0,%1,%2" : "ssha\t%0,%1,%2";
    }
}
  [(set_attr "type" "simd,simd,simd")
   (set_attr "mode" "SI")])

(define_expand "riscv_sshar_i32"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:SI 1 "register_operand")
		    (match_operand:SI 2 "nonmemory_operand")]
	 UNSPEC_PSSHAR))]
  "TARGET_RVP"
{
  if (!CONST_INT_P (operands[2])
      || (!IN_RANGE (INTVAL (operands[2]), 0, 31)
	  && !IN_RANGE (INTVAL (operands[2]), -31, -1)))
    operands[2] = force_reg (SImode, operands[2]);
  emit_insn (gen_riscv_sshar_i32_insn
	     (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_sshar_i32_insn"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r,r,r")
		    (match_operand:SI 2 "arith_operand" "u5,w5,r")]
	 UNSPEC_PSSHAR))]
  "TARGET_RVP"
{
  switch (which_alternative)
    {
    case 0:
      return TARGET_64BIT ? "psslai.w\t%0,%1,%2" : "sslai\t%0,%1,%2";
    case 1:
      return TARGET_64BIT ? "psrari.w\t%0,%1,%n2" : "srari\t%0,%1,%n2";
    default:
      return TARGET_64BIT ? "psshar.ws\t%0,%1,%2" : "sshar\t%0,%1,%2";
    }
}
  [(set_attr "type" "simd,simd,simd")
   (set_attr "mode" "SI")])

(define_expand "riscv_sshl_u32"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:SI 1 "register_operand")
		    (match_operand:SI 2 "nonmemory_operand")]
	 UNSPEC_PSSHL))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
})

(define_insn "riscv_sshl_u32_insn"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")]
	 UNSPEC_PSSHL))]
  "TARGET_RVP"
{
  return TARGET_64BIT ? "psshl.ws\t%0,%1,%2" : "sshl\t%0,%1,%2";
}
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

(define_expand "riscv_sshlr_u32"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:SI 1 "register_operand")
		    (match_operand:SI 2 "nonmemory_operand")]
	 UNSPEC_PSSHLR))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
})

(define_insn "riscv_sshlr_u32_insn"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")]
	 UNSPEC_PSSHLR))]
  "TARGET_RVP"
{
  return TARGET_64BIT ? "psshlr.ws\t%0,%1,%2" : "sshlr\t%0,%1,%2";
}
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

;; Full-width shifts are available on RV64 only.

(define_expand "riscv_sha_i64"
  [(set (match_operand:DI 0 "register_operand")
	(unspec:DI [(match_operand:DI 1 "register_operand")
		    (match_operand:SI 2 "nonmemory_operand")]
	 UNSPEC_SHA))]
  "TARGET_RVP && TARGET_64BIT"
{
  if (!CONST_INT_P (operands[2])
      || (!IN_RANGE (INTVAL (operands[2]), 0, 63)
	  && !IN_RANGE (INTVAL (operands[2]), -63, -1)))
    operands[2] = force_reg (SImode, operands[2]);
  emit_insn (gen_riscv_sha_i64_insn
	     (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_sha_i64_insn"
  [(set (match_operand:DI 0 "register_operand" "=r,r,r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r,r,r")
		    (match_operand:SI 2 "arith_operand" "u6,w6,r")]
	 UNSPEC_SHA))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   slli\t%0,%1,%2
   srai\t%0,%1,%n2
   sha\t%0,%1,%2"
  [(set_attr "type" "simd,simd,simd")
   (set_attr "mode" "DI")])

(define_expand "riscv_shar_i64"
  [(set (match_operand:DI 0 "register_operand")
	(unspec:DI [(match_operand:DI 1 "register_operand")
		    (match_operand:SI 2 "nonmemory_operand")]
	 UNSPEC_SHAR))]
  "TARGET_RVP && TARGET_64BIT"
{
  if (!CONST_INT_P (operands[2])
      || (!IN_RANGE (INTVAL (operands[2]), 0, 63)
	  && !IN_RANGE (INTVAL (operands[2]), -63, -1)))
    operands[2] = force_reg (SImode, operands[2]);
  emit_insn (gen_riscv_shar_i64_insn
	     (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_shar_i64_insn"
  [(set (match_operand:DI 0 "register_operand" "=r,r,r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r,r,r")
		    (match_operand:SI 2 "arith_operand" "u6,w6,r")]
	 UNSPEC_SHAR))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   slli\t%0,%1,%2
   srari\t%0,%1,%n2
   shar\t%0,%1,%2"
  [(set_attr "type" "simd,simd,simd")
   (set_attr "mode" "DI")])

(define_insn "riscv_shl_u64_insn"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")]
	 UNSPEC_SHL))]
  "TARGET_RVP && TARGET_64BIT"
  "shl\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_expand "riscv_shl_u64"
  [(set (match_operand:DI 0 "register_operand")
	(unspec:DI [(match_operand:DI 1 "register_operand")
		    (match_operand:SI 2 "nonmemory_operand")]
	 UNSPEC_SHL))]
  "TARGET_RVP && TARGET_64BIT"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
})

(define_insn "riscv_shlr_u64_insn"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")]
	 UNSPEC_SHLR))]
  "TARGET_RVP && TARGET_64BIT"
  "shlr\t%0,%1,%2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_expand "riscv_shlr_u64"
  [(set (match_operand:DI 0 "register_operand")
	(unspec:DI [(match_operand:DI 1 "register_operand")
		    (match_operand:SI 2 "nonmemory_operand")]
	 UNSPEC_SHLR))]
  "TARGET_RVP && TARGET_64BIT"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
})

;; Scalar narrowing clips.  The RV32 instructions consume a register pair.
;; RV64 shifts the full-width source first and then clips the low result with
;; PNCLIPP.W or PNCLIPUP.W.

(define_int_iterator RVP_SCALAR_NCLIP
  [UNSPEC_NCLIPU UNSPEC_NCLIPRU UNSPEC_NCLIP UNSPEC_NCLIPR])

(define_int_iterator RVP_SCALAR_NCLIP_NOROUND
  [UNSPEC_NCLIPU UNSPEC_NCLIP])

(define_int_iterator RVP_SCALAR_NCLIP_ROUND
  [UNSPEC_NCLIPRU UNSPEC_NCLIPR])

(define_int_attr rvp_scalar_nclip_builtin
  [(UNSPEC_NCLIPU "nclipu_u32")
   (UNSPEC_NCLIPRU "nclipru_u32")
   (UNSPEC_NCLIP "nclip_i32")
   (UNSPEC_NCLIPR "nclipr_i32")])

(define_int_attr rvp_scalar_nclip_imm
  [(UNSPEC_NCLIPU "nclipiu")
   (UNSPEC_NCLIPRU "nclipriu")
   (UNSPEC_NCLIP "nclipi")
   (UNSPEC_NCLIPR "nclipri")])

(define_int_attr rvp_scalar_nclip_reg
  [(UNSPEC_NCLIPU "nclipu")
   (UNSPEC_NCLIPRU "nclipru")
   (UNSPEC_NCLIP "nclip")
   (UNSPEC_NCLIPR "nclipr")])

(define_int_attr rvp_scalar_nclip_shift
  [(UNSPEC_NCLIPU "srl")
   (UNSPEC_NCLIP "sra")])

(define_int_attr rvp_scalar_nclip_round_shift
  [(UNSPEC_NCLIPRU "shlr")
   (UNSPEC_NCLIPR "shar")])

(define_int_attr rvp_scalar_nclip_pair
  [(UNSPEC_NCLIPU "pnclipup.w")
   (UNSPEC_NCLIPRU "pnclipup.w")
   (UNSPEC_NCLIP "pnclipp.w")
   (UNSPEC_NCLIPR "pnclipp.w")])

(define_expand "riscv_<rvp_scalar_nclip_builtin>"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:DI 1 "register_operand")
		    (match_operand:SI 2 "nonmemory_operand")]
	 RVP_SCALAR_NCLIP))]
  "TARGET_RVP"
{
  if (!CONST_INT_P (operands[2])
      || !IN_RANGE (INTVAL (operands[2]), 0, 63))
    operands[2] = force_reg (SImode, operands[2]);

  if (TARGET_64BIT)
    emit_insn (gen_riscv_<rvp_scalar_nclip_builtin>_rv64
	       (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_<rvp_scalar_nclip_builtin>_rv32
	       (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_<rvp_scalar_nclip_builtin>_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(unspec:SI [(match_operand:DI 1 "register_operand" "R,R")
		    (match_operand:SI 2 "arith_operand" "u6,r")]
	 RVP_SCALAR_NCLIP))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   <rvp_scalar_nclip_imm>\t%0,%1,%2
   <rvp_scalar_nclip_reg>\t%0,%1,%2"
  [(set_attr "type" "simd,simd")
   (set_attr "mode" "SI")])

(define_insn "riscv_<rvp_scalar_nclip_builtin>_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(unspec:SI [(match_operand:DI 1 "register_operand" "r,r")
		    (match_operand:SI 2 "arith_operand" "u6,r")]
	 RVP_SCALAR_NCLIP_NOROUND))
   (clobber (match_scratch:DI 3 "=&r,&r"))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   <rvp_scalar_nclip_shift>i\t%3,%1,%2\;<rvp_scalar_nclip_pair>\t%0,%3,zero
   <rvp_scalar_nclip_shift>\t%3,%1,%2\;<rvp_scalar_nclip_pair>\t%0,%3,zero"
  [(set_attr "type" "simd,simd")
   (set_attr "mode" "DI")])

(define_insn "riscv_<rvp_scalar_nclip_builtin>_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(unspec:SI [(match_operand:DI 1 "register_operand" "r,r")
		    (match_operand:SI 2 "arith_operand" "u6,r")]
	 RVP_SCALAR_NCLIP_ROUND))
   (clobber (match_scratch:DI 3 "=&r,&r"))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   li\t%3,%n2\;<rvp_scalar_nclip_round_shift>\t%3,%1,%3\;<rvp_scalar_nclip_pair>\t%0,%3,zero
   andi\t%3,%2,63\;neg\t%3,%3\;<rvp_scalar_nclip_round_shift>\t%3,%1,%3\;<rvp_scalar_nclip_pair>\t%0,%3,zero"
  [(set_attr "type" "simd,simd")
   (set_attr "mode" "DI")])

;; Rounded arithmetic narrowing without clipping.

(define_expand "riscv_nsrar_i32"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:DI 1 "register_operand")
		    (match_operand:SI 2 "nonmemory_operand")]
	 UNSPEC_NSRAR))]
  "TARGET_RVP"
{
  if (!CONST_INT_P (operands[2])
      || !IN_RANGE (INTVAL (operands[2]), 0, 63))
    operands[2] = force_reg (SImode, operands[2]);

  if (TARGET_64BIT)
    emit_insn (gen_riscv_nsrar_i32_rv64
	       (operands[0], operands[1], operands[2]));
  else
    emit_insn (gen_riscv_nsrar_i32_rv32
	       (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_nsrar_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(unspec:SI [(match_operand:DI 1 "register_operand" "R,R")
		    (match_operand:SI 2 "arith_operand" "u6,r")]
	 UNSPEC_NSRAR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   nsrari\t%0,%1,%2
   nsrar\t%0,%1,%2"
  [(set_attr "type" "simd,simd")
   (set_attr "mode" "SI")])

(define_insn "riscv_nsrar_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(unspec:SI [(match_operand:DI 1 "register_operand" "r,r")
		    (match_operand:SI 2 "arith_operand" "u6,r")]
	 UNSPEC_NSRAR))
   (clobber (match_scratch:DI 3 "=&r,&r"))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   srari\t%0,%1,%2
   andi\t%3,%2,63\;neg\t%3,%3\;shar\t%0,%1,%3"
  [(set_attr "type" "simd,simd")
   (set_attr "mode" "DI")])

;; Packed saturating and rounding shifts.
;;
; pssha/psshar: signed saturating (rounding) arithmetic shift, expanded via
; psslai (immediate) / psrai or psrari (negative immediate) / pssha[r].hs.
; psshl/psshlr: unsigned saturating (rounding) logical shift.

(define_insn "riscv_pssha_s_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r, r, r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
          UNSPEC_PSSHA))]
  "TARGET_RVP"
  "@
   psslai.h\t%0,%1,%2
   psrai.h\t%0,%1,%n2
   pssha.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_psshar_s_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r, r, r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
         UNSPEC_PSSHAR))]
  "TARGET_RVP"
  "@
   psslai.h\t%0,%1,%2
   psrari.h\t%0,%1,%n2
   psshar.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_psshl_s_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHL))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
})

(define_insn "riscv_psshl_s_u16x2_insn"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_PSSHL))]
  "TARGET_RVP"
  "psshl.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psshlr_s_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHLR))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
})

(define_insn "riscv_psshlr_s_u16x2_insn"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_PSSHLR))]
  "TARGET_RVP"
  "psshlr.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pssha_s_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHA))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_pssha_s_i16x4_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_pssha_s_i16x4_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_pssha_s_i16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R, R, R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
          UNSPEC_PSSHA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psslai.dh\t%0,%1,%2
   psrai.dh\t%0,%1,%n2
   pssha.dhs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_pssha_s_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r, r, r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
          UNSPEC_PSSHA))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psslai.h\t%0,%1,%2
   psrai.h\t%0,%1,%n2
   pssha.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_pssha_s_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHA))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_pssha_s_i32x2_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_pssha_s_i32x2_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_pssha_s_i32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R, R, R")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u5, w5, r")]
          UNSPEC_PSSHA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psslai.dw\t%0,%1,%2
   psrai.dw\t%0,%1,%n2
   pssha.dws\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_pssha_s_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r, r, r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u5, w5, r")]
          UNSPEC_PSSHA))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psslai.w\t%0,%1,%2
   psrai.w\t%0,%1,%n2
   pssha.ws\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_psshar_s_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHAR))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshar_s_i16x4_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshar_s_i16x4_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshar_s_i16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R, R, R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
          UNSPEC_PSSHAR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psslai.dh\t%0,%1,%2
   psrari.dh\t%0,%1,%n2
   psshar.dhs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_psshar_s_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r, r, r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u4, w4, r")]
          UNSPEC_PSSHAR))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psslai.h\t%0,%1,%2
   psrari.h\t%0,%1,%n2
   psshar.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_psshar_s_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHAR))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshar_s_i32x2_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshar_s_i32x2_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshar_s_i32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R, R, R")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u5, w5, r")]
          UNSPEC_PSSHAR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   psslai.dw\t%0,%1,%2
   psrari.dw\t%0,%1,%n2
   psshar.dws\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_insn "riscv_psshar_s_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r, r, r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r, r, r")
                    (match_operand:SI 2 "arith_operand" "u5, w5, r")]
          UNSPEC_PSSHAR))]
  "TARGET_RVP && TARGET_64BIT"
  "@
   psslai.w\t%0,%1,%2
   psrari.w\t%0,%1,%n2
   psshar.ws\t%0,%1,%2"
  [(set_attr "type" "simd, simd, simd")])

(define_expand "riscv_psshl_s_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHL))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshl_s_u16x4_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshl_s_u16x4_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshl_s_u16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "R")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHL))]
  "TARGET_RVP && !TARGET_64BIT"
  "psshl.dhs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psshl_s_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHL))]
  "TARGET_RVP && TARGET_64BIT"
  "psshl.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psshl_s_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHL))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshl_s_u32x2_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshl_s_u32x2_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshl_s_u32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHL))]
  "TARGET_RVP && !TARGET_64BIT"
  "psshl.dws\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psshl_s_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHL))]
  "TARGET_RVP && TARGET_64BIT"
  "psshl.ws\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psshlr_s_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHLR))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshlr_s_u16x4_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshlr_s_u16x4_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshlr_s_u16x4_rv32"
  [(set (match_operand:PV4HI 0 "register_operand" "=R")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHLR))]
  "TARGET_RVP && !TARGET_64BIT"
  "psshlr.dhs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psshlr_s_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHLR))]
  "TARGET_RVP && TARGET_64BIT"
  "psshlr.hs\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_psshlr_s_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                    (match_operand:SI 2 "nonmemory_operand")]
         UNSPEC_PSSHLR))]
  "TARGET_RVP"
{
  if (!register_operand (operands[2], SImode))
    operands[2] = force_reg (SImode, operands[2]);
  if (TARGET_64BIT)
    {
      emit_insn (gen_riscv_psshlr_s_u32x2_rv64 (operands[0], operands[1], operands[2]));
    }
  else
    {
      emit_insn (gen_riscv_psshlr_s_u32x2_rv32 (operands[0], operands[1], operands[2]));
    }
  DONE;
})

(define_insn "riscv_psshlr_s_u32x2_rv32"
  [(set (match_operand:PV2SI 0 "register_operand" "=R")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHLR))]
  "TARGET_RVP && !TARGET_64BIT"
  "psshlr.dws\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_psshlr_s_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_PSSHLR))]
  "TARGET_RVP && TARGET_64BIT"
  "psshlr.ws\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Widening Shift
;
;pwsll_s/pwsla_s widen one narrow source (32-bit) into a wide result (64-bit)
;and shift each widened lane left by shamt: PV4QI -> PV4HI, or PV2HI -> PV2SI.
;pwsll = logical left shift (zero-extend widen), pwsla = arithmetic left shift
;(sign-extend widen).  shamt may be an immediate or a register scalar.
;  RV32: immediate form  pwslli.b/h, pwslai.b/h  (constraint Wpd,s,WpH/<)
;        register form    pwsll.bs/hs, pwsla.bs/hs (constraint Wpd,s,t)
;        Wpd is the even-odd result pair, s the narrow source, WpH/< the uimm,
;        t the shamt register.  RV32-only hardware instructions.
;  RV64: no single widening shift instruction; spec gives multi-insn sequences
;        (pwcvtu.wb+pslli.h, etc.).  NOT implemented yet.  TODO.  Builtins are
;        simd32-only.
;The two output templates pick pwslli/pwslai when shamt is a u4/u5 immediate,
;and pwsll.bs/hs/pwsla.bs/hs when it is a register (matches the existing
;riscv_psll_s_* pattern style).
(define_insn "riscv_pwsll_s_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand" "=R, R")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r, r")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PWSLL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pwslli.b\t%0,%1,%2
   pwsll.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pwsll_s_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=R, R")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r, r")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PWSLL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pwslli.h\t%0,%1,%2
   pwsll.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pwsla_s_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand" "=R, R")
        (unspec:PV4HI [(match_operand:PV4QI 1 "register_operand" "r, r")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PWSLA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pwslai.b\t%0,%1,%2
   pwsla.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pwsla_s_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=R, R")
        (unspec:PV2SI [(match_operand:PV2HI 1 "register_operand" "r, r")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PWSLA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pwslai.h\t%0,%1,%2
   pwsla.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

;Packed Narrowing Shift
;
;pnsrl_s/pnsra_s/pnsrar_s narrow one wide source (64-bit) into a narrow result
;(32-bit) by shifting each lane right: PV4HI -> PV4QI, or PV2SI -> PV2HI.
;pnsrl = logical right shift (zero-extend narrow), pnsra = arithmetic right
;shift (sign-extend narrow), pnsrar = rounding arithmetic right shift.
;shamt may be an immediate or a register scalar.
;  RV32: immediate form  pnsrli.b/h, pnsrai.b/h, pnsrari.b/h (constraint d,Wps,WpH/<)
;        register form    pnsrl.bs/hs, pnsra.bs/hs, pnsrar.bs/hs (constraint d,Wps,t)
;        d is the narrow result register, Wps the wide even-odd source pair,
;        WpH/< the uimm, t the shamt register.  RV32-only hardware.
;  RV64: no single narrowing shift instruction; spec gives multi-insn sequences
;        (psrli.h+unzip8p, etc.).  NOT implemented yet.  TODO.  Builtins are
;        simd32-only.
(define_insn "riscv_pnsrl_s_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r, r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNSRL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrli.b\t%0,%1,%2
   pnsrl.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnsrl_s_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r, r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNSRL))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrli.h\t%0,%1,%2
   pnsrl.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnsra_s_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r, r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNSRA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrai.b\t%0,%1,%2
   pnsra.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnsra_s_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r, r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNSRA))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrai.h\t%0,%1,%2
   pnsra.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnsrar_s_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r, r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNSRAR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrari.b\t%0,%1,%2
   pnsrar.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnsrar_s_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r, r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNSRAR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnsrari.h\t%0,%1,%2
   pnsrar.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

;Packed Narrowing Clip
;
;pnclip* narrow one wide source (64-bit) into a narrow result (32-bit) by
;clipping (saturating to the narrow range) after a shift: PV4HI -> PV4QI, or
;PV2SI -> PV2HI.  Four variants:
;  pnclipu  = unsigned clip,            pnclipru = unsigned rounding clip
;  pnclip   = signed clip,              pnclipr  = signed rounding clip
;shamt may be an immediate or a register scalar.
;  RV32: immediate form  pnclipiu.b/h, pnclipriu.b/h, pnclipi.b/h, pnclipri.b/h
;                     (constraint d,Wps,WpH/<)
;        register form    pnclipu.bs/hs, pnclipru.bs/hs, pnclip.bs/hs,
;                         pnclipr.bs/hs  (constraint d,Wps,t)
;        d is the narrow result register, Wps the wide even-odd source pair,
;        WpH/< the uimm, t the shamt register.  RV32-only hardware.
;        Note: the immediate mnemonics carry an extra "i" (pnclipiu/pnclipi)
;        while the register mnemonics drop it (pnclipu.bs/pnclip.bs), matching
;        the binutils opcodes table.
;  RV64: no single narrowing clip instruction; spec gives multi-insn sequences
;        (psrli.h+pnclipup.b, etc.).  NOT implemented yet.  TODO.  Builtins
;        are simd32-only.
(define_insn "riscv_pnclipu_s_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r, r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNCLIPU))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipiu.b\t%0,%1,%2
   pnclipu.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclipu_s_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r, r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNCLIPU))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipiu.h\t%0,%1,%2
   pnclipu.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclipru_s_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r, r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNCLIPRU))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipriu.b\t%0,%1,%2
   pnclipru.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclipru_s_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r, r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNCLIPRU))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipriu.h\t%0,%1,%2
   pnclipru.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclip_s_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r, r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNCLIP))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipi.b\t%0,%1,%2
   pnclip.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclip_s_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r, r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNCLIP))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipi.h\t%0,%1,%2
   pnclip.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclipr_s_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand" "=r, r")
        (unspec:PV4QI [(match_operand:PV4HI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u4, r")]
         UNSPEC_PNCLIPR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipri.b\t%0,%1,%2
   pnclipr.bs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

(define_insn "riscv_pnclipr_s_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r, r")
        (unspec:PV2HI [(match_operand:PV2SI 1 "register_operand" "R, R")
                      (match_operand:SI 2 "arith_operand" "u5, r")]
         UNSPEC_PNCLIPR))]
  "TARGET_RVP && !TARGET_64BIT"
  "@
   pnclipri.h\t%0,%1,%2
   pnclipr.hs\t%0,%1,%2"
  [(set_attr "type" "simd, simd")])

;; Packed narrowing clip pairs.  The 32-bit result forms first concatenate
;; two half-width inputs and then use the existing saturating truncation
;; optabs.  On RV32 this feeds the register-pair PNCLIPI instruction.  RV64
;; needs PACK followed by PNCLIPP with a zero second source because each input
;; contains only half of the lanes consumed by PNCLIPP.

(define_expand "riscv_pnclipp_i8x4"
  [(set (match_operand:PV4QI 0 "register_operand")
	(unspec:PV4QI [(match_operand:PV2HI 1 "register_operand")
		       (match_operand:PV2HI 2 "register_operand")]
	 UNSPEC_PNCLIP))]
  "TARGET_RVP"
{
  rtx combined;
  if (TARGET_64BIT)
    {
      rtx combined_v = gen_reg_rtx (PV2SImode);
      emit_insn (gen_rtx_SET
	(combined_v,
	 gen_rtx_VEC_CONCAT (PV2SImode, gen_lowpart (SImode, operands[1]),
				       gen_lowpart (SImode, operands[2]))));
      combined = gen_lowpart (PV4HImode, combined_v);
    }
  else
    {
      combined = gen_reg_rtx (PV4HImode);
      emit_move_insn (gen_lowpart (PV2HImode, combined), operands[1]);
      emit_move_insn (gen_highpart (PV2HImode, combined), operands[2]);
    }
  emit_insn (gen_sstruncpv4hipv4qi2 (operands[0], combined));
  DONE;
})

(define_expand "riscv_pnclipup_u8x4"
  [(set (match_operand:PV4QI 0 "register_operand")
	(unspec:PV4QI [(match_operand:PV2HI 1 "register_operand")
		       (match_operand:PV2HI 2 "register_operand")]
	 UNSPEC_PNCLIPU))]
  "TARGET_RVP"
{
  rtx combined;
  if (TARGET_64BIT)
    {
      rtx combined_v = gen_reg_rtx (PV2SImode);
      emit_insn (gen_rtx_SET
	(combined_v,
	 gen_rtx_VEC_CONCAT (PV2SImode, gen_lowpart (SImode, operands[1]),
				       gen_lowpart (SImode, operands[2]))));
      combined = gen_lowpart (PV4HImode, combined_v);
    }
  else
    {
      combined = gen_reg_rtx (PV4HImode);
      emit_move_insn (gen_lowpart (PV2HImode, combined), operands[1]);
      emit_move_insn (gen_highpart (PV2HImode, combined), operands[2]);
    }
  emit_insn (gen_ustruncpv4hipv4qi2 (operands[0], combined));
  DONE;
})

(define_expand "riscv_pnclipp_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
	(unspec:PV2HI [(match_operand:SI 1 "register_operand")
		       (match_operand:SI 2 "register_operand")]
	 UNSPEC_PNCLIP))]
  "TARGET_RVP"
{
  rtx combined = gen_reg_rtx (PV2SImode);
  if (TARGET_64BIT)
    emit_insn (gen_rtx_SET
	(combined, gen_rtx_VEC_CONCAT (PV2SImode, operands[1], operands[2])));
  else
    {
      emit_move_insn (gen_lowpart (SImode, combined), operands[1]);
      emit_move_insn (gen_highpart (SImode, combined), operands[2]);
    }
  emit_insn (gen_sstruncpv2sipv2hi2 (operands[0], combined));
  DONE;
})

(define_expand "riscv_pnclipup_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
	(unspec:PV2HI [(match_operand:SI 1 "register_operand")
		       (match_operand:SI 2 "register_operand")]
	 UNSPEC_PNCLIPU))]
  "TARGET_RVP"
{
  rtx combined = gen_reg_rtx (PV2SImode);
  if (TARGET_64BIT)
    emit_insn (gen_rtx_SET
	(combined, gen_rtx_VEC_CONCAT (PV2SImode, operands[1], operands[2])));
  else
    {
      emit_move_insn (gen_lowpart (SImode, combined), operands[1]);
      emit_move_insn (gen_highpart (SImode, combined), operands[2]);
    }
  emit_insn (gen_ustruncpv2sipv2hi2 (operands[0], combined));
  DONE;
})

;; The 64-bit result forms consume two complete XLEN-bit sources on RV64.
;; RV32 clips each register-pair source separately and returns the two narrow
;; results in the corresponding halves of the destination pair.

(define_expand "riscv_pnclipp_i8x8"
  [(set (match_operand:PV8QI 0 "register_operand")
	(unspec:PV8QI [(match_operand:PV4HI 1 "register_operand")
		       (match_operand:PV4HI 2 "reg_or_0_operand")]
	 UNSPEC_PNCLIP))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnclipp_i8x8_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx lo = gen_reg_rtx (PV4QImode);
      rtx hi = gen_reg_rtx (PV4QImode);
      emit_insn (gen_riscv_pnclip_s_i8x4 (lo, operands[1], const0_rtx));
      emit_insn (gen_riscv_pnclip_s_i8x4 (hi, operands[2], const0_rtx));
      emit_move_insn (gen_lowpart (PV4QImode, operands[0]), lo);
      emit_move_insn (gen_highpart (PV4QImode, operands[0]), hi);
    }
  DONE;
})

(define_insn "riscv_pnclipp_i8x8_rv64"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
	(unspec:PV8QI [(match_operand:PV4HI 1 "register_operand" "r")
		       (match_operand:PV4HI 2 "reg_or_0_operand" "rWc0")]
	 UNSPEC_PNCLIP))]
  "TARGET_RVP && TARGET_64BIT"
  "pnclipp.b\t%0,%1,%z2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_expand "riscv_pnclipup_u8x8"
  [(set (match_operand:PV8QI 0 "register_operand")
	(unspec:PV8QI [(match_operand:PV4HI 1 "register_operand")
		       (match_operand:PV4HI 2 "reg_or_0_operand")]
	 UNSPEC_PNCLIPU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnclipup_u8x8_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx lo = gen_reg_rtx (PV4QImode);
      rtx hi = gen_reg_rtx (PV4QImode);
      emit_insn (gen_riscv_pnclipu_s_u8x4 (lo, operands[1], const0_rtx));
      emit_insn (gen_riscv_pnclipu_s_u8x4 (hi, operands[2], const0_rtx));
      emit_move_insn (gen_lowpart (PV4QImode, operands[0]), lo);
      emit_move_insn (gen_highpart (PV4QImode, operands[0]), hi);
    }
  DONE;
})

(define_insn "riscv_pnclipup_u8x8_rv64"
  [(set (match_operand:PV8QI 0 "register_operand" "=r")
	(unspec:PV8QI [(match_operand:PV4HI 1 "register_operand" "r")
		       (match_operand:PV4HI 2 "reg_or_0_operand" "rWc0")]
	 UNSPEC_PNCLIPU))]
  "TARGET_RVP && TARGET_64BIT"
  "pnclipup.b\t%0,%1,%z2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_expand "riscv_pnclipp_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
	(unspec:PV4HI [(match_operand:PV2SI 1 "register_operand")
		       (match_operand:PV2SI 2 "reg_or_0_operand")]
	 UNSPEC_PNCLIP))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnclipp_i16x4_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx lo = gen_reg_rtx (PV2HImode);
      rtx hi = gen_reg_rtx (PV2HImode);
      emit_insn (gen_riscv_pnclip_s_i16x2 (lo, operands[1], const0_rtx));
      emit_insn (gen_riscv_pnclip_s_i16x2 (hi, operands[2], const0_rtx));
      emit_move_insn (gen_lowpart (PV2HImode, operands[0]), lo);
      emit_move_insn (gen_highpart (PV2HImode, operands[0]), hi);
    }
  DONE;
})

(define_insn "riscv_pnclipp_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
	(unspec:PV4HI [(match_operand:PV2SI 1 "register_operand" "r")
		       (match_operand:PV2SI 2 "reg_or_0_operand" "rWc0")]
	 UNSPEC_PNCLIP))]
  "TARGET_RVP && TARGET_64BIT"
  "pnclipp.h\t%0,%1,%z2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_expand "riscv_pnclipup_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
	(unspec:PV4HI [(match_operand:PV2SI 1 "register_operand")
		       (match_operand:PV2SI 2 "reg_or_0_operand")]
	 UNSPEC_PNCLIPU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnclipup_u16x4_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx lo = gen_reg_rtx (PV2HImode);
      rtx hi = gen_reg_rtx (PV2HImode);
      emit_insn (gen_riscv_pnclipu_s_u16x2 (lo, operands[1], const0_rtx));
      emit_insn (gen_riscv_pnclipu_s_u16x2 (hi, operands[2], const0_rtx));
      emit_move_insn (gen_lowpart (PV2HImode, operands[0]), lo);
      emit_move_insn (gen_highpart (PV2HImode, operands[0]), hi);
    }
  DONE;
})

(define_insn "riscv_pnclipup_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
	(unspec:PV4HI [(match_operand:PV2SI 1 "register_operand" "r")
		       (match_operand:PV2SI 2 "reg_or_0_operand" "rWc0")]
	 UNSPEC_PNCLIPU))]
  "TARGET_RVP && TARGET_64BIT"
  "pnclipup.h\t%0,%1,%z2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_expand "riscv_pnclipp_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
	(unspec:PV2SI [(match_operand:DI 1 "register_operand")
		       (match_operand:DI 2 "reg_or_0_operand")]
	 UNSPEC_NCLIP))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnclipp_i32x2_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx lo = gen_reg_rtx (SImode);
      rtx hi = gen_reg_rtx (SImode);
      emit_insn (gen_riscv_nclip_i32 (lo, operands[1], const0_rtx));
      emit_insn (gen_riscv_nclip_i32 (hi, operands[2], const0_rtx));
      emit_move_insn (gen_lowpart (SImode, operands[0]), lo);
      emit_move_insn (gen_highpart (SImode, operands[0]), hi);
    }
  DONE;
})

(define_insn "riscv_pnclipp_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(unspec:PV2SI [(match_operand:DI 1 "register_operand" "r")
		       (match_operand:DI 2 "reg_or_0_operand" "rJ")]
	 UNSPEC_NCLIP))]
  "TARGET_RVP && TARGET_64BIT"
  "pnclipp.w\t%0,%1,%z2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_expand "riscv_pnclipup_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
	(unspec:PV2SI [(match_operand:DI 1 "register_operand")
		       (match_operand:DI 2 "reg_or_0_operand")]
	 UNSPEC_NCLIPU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pnclipup_u32x2_rv64
	       (operands[0], operands[1], operands[2]));
  else
    {
      rtx lo = gen_reg_rtx (SImode);
      rtx hi = gen_reg_rtx (SImode);
      emit_insn (gen_riscv_nclipu_u32 (lo, operands[1], const0_rtx));
      emit_insn (gen_riscv_nclipu_u32 (hi, operands[2], const0_rtx));
      emit_move_insn (gen_lowpart (SImode, operands[0]), lo);
      emit_move_insn (gen_highpart (SImode, operands[0]), hi);
    }
  DONE;
})

(define_insn "riscv_pnclipup_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
	(unspec:PV2SI [(match_operand:DI 1 "register_operand" "r")
		       (match_operand:DI 2 "reg_or_0_operand" "rJ")]
	 UNSPEC_NCLIPU))]
  "TARGET_RVP && TARGET_64BIT"
  "pnclipup.w\t%0,%1,%z2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])
