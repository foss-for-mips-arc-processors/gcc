;; Machine description for RISC-V 'P' extension multiply operations.
;; Copyright (C) 2025-2026 Free Software Foundation, Inc.
;;
;; This file is part of GCC.
;;
;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.
;;
;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;Scalar Multiply High and Q-format Multiplication
;
;RV32 has scalar instructions.  RV64 uses lane 0 of the corresponding packed
;.w instruction.  Widen the inputs and result to a full GPR on RV64 so that the
;RTL accounts for the packed instruction writing both 32-bit lanes.
(define_int_iterator RVP_SCALAR_MUL
  [UNSPEC_PMULH UNSPEC_PMULHR UNSPEC_PMULHU UNSPEC_PMULHRU
   UNSPEC_PMULHSU UNSPEC_PMULHRSU UNSPEC_PMULQ UNSPEC_PMULQR])

(define_int_attr rvp_scalar_mul_builtin
  [(UNSPEC_PMULH "mulh_i32")
   (UNSPEC_PMULHR "mulhr_i32")
   (UNSPEC_PMULHU "mulhu_u32")
   (UNSPEC_PMULHRU "mulhru_u32")
   (UNSPEC_PMULHSU "mulhsu_i32")
   (UNSPEC_PMULHRSU "mulhrsu_i32")
   (UNSPEC_PMULQ "mulq_i32")
   (UNSPEC_PMULQR "mulqr_i32")])

(define_int_attr rvp_scalar_mul_rv32
  [(UNSPEC_PMULH "mulh")
   (UNSPEC_PMULHR "mulhr")
   (UNSPEC_PMULHU "mulhu")
   (UNSPEC_PMULHRU "mulhru")
   (UNSPEC_PMULHSU "mulhsu")
   (UNSPEC_PMULHRSU "mulhrsu")
   (UNSPEC_PMULQ "mulq")
   (UNSPEC_PMULQR "mulqr")])

(define_int_attr rvp_scalar_mul_packed
  [(UNSPEC_PMULH "pmulh_i32x2")
   (UNSPEC_PMULHR "pmulhr_i32x2")
   (UNSPEC_PMULHU "pmulhu_u32x2")
   (UNSPEC_PMULHRU "pmulhru_u32x2")
   (UNSPEC_PMULHSU "pmulhsu_i32x2")
   (UNSPEC_PMULHRSU "pmulhrsu_i32x2")
   (UNSPEC_PMULQ "pmulq_i32x2")
   (UNSPEC_PMULQR "pmulqr_i32x2")])

(define_expand "riscv_<rvp_scalar_mul_builtin>"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:SI 1 "register_operand")
		    (match_operand:SI 2 "register_operand")]
	 RVP_SCALAR_MUL))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx dest = gen_reg_rtx (DImode);
      rtx r1 = gen_reg_rtx (DImode);
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2 (r1, operands[1]));
      emit_insn (gen_zero_extendsidi2 (r2, operands[2]));
      emit_insn (gen_riscv_<rvp_scalar_mul_packed>
		 (gen_lowpart (PV2SImode, dest),
		  gen_lowpart (PV2SImode, r1),
		  gen_lowpart (PV2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, dest));
    }
  else
    emit_insn (gen_riscv_<rvp_scalar_mul_builtin>_rv32
	       (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_<rvp_scalar_mul_builtin>_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")]
	 RVP_SCALAR_MUL))]
  "TARGET_RVP && !TARGET_64BIT"
  "<rvp_scalar_mul_rv32>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Scalar Multiply High Accumulate
;
;RV32 has scalar read-modify-write instructions.  RV64 uses lane 0 of the
;corresponding packed .w instruction.  Model the complete RV64 GPR operands so
;that the implicit update of the second lane is visible to the RTL data flow.
(define_int_iterator RVP_SCALAR_MUL_ACC
  [UNSPEC_PMHACC UNSPEC_PMHRACC UNSPEC_PMHACCU UNSPEC_PMHRACCU
   UNSPEC_PMHACCSU UNSPEC_PMHRACCSU])

(define_int_attr rvp_scalar_mul_acc_builtin
  [(UNSPEC_PMHACC "mhacc_i32")
   (UNSPEC_PMHRACC "mhracc_i32")
   (UNSPEC_PMHACCU "mhaccu_u32")
   (UNSPEC_PMHRACCU "mhraccu_u32")
   (UNSPEC_PMHACCSU "mhaccsu_i32")
   (UNSPEC_PMHRACCSU "mhraccsu_i32")])

(define_int_attr rvp_scalar_mul_acc_rv32
  [(UNSPEC_PMHACC "mhacc")
   (UNSPEC_PMHRACC "mhracc")
   (UNSPEC_PMHACCU "mhaccu")
   (UNSPEC_PMHRACCU "mhraccu")
   (UNSPEC_PMHACCSU "mhaccsu")
   (UNSPEC_PMHRACCSU "mhraccsu")])

(define_int_attr rvp_scalar_mul_acc_packed
  [(UNSPEC_PMHACC "pmhacc_i32x2_rmw")
   (UNSPEC_PMHRACC "pmhracc_i32x2_rmw")
   (UNSPEC_PMHACCU "pmhaccu_u32x2_rmw")
   (UNSPEC_PMHRACCU "pmhraccu_u32x2_rmw")
   (UNSPEC_PMHACCSU "pmhaccsu_i32x2_rmw")
   (UNSPEC_PMHRACCSU "pmhraccsu_i32x2_rmw")])

(define_expand "riscv_<rvp_scalar_mul_acc_builtin>"
  [(set (match_operand:SI 0 "register_operand")
	(unspec:SI [(match_operand:SI 1 "register_operand")
		    (match_operand:SI 2 "register_operand")
		    (match_operand:SI 3 "register_operand")]
	 RVP_SCALAR_MUL_ACC))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
      rtx dest = gen_reg_rtx (DImode);
      rtx acc = gen_reg_rtx (DImode);
      rtx r1 = gen_reg_rtx (DImode);
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2 (acc, operands[1]));
      emit_insn (gen_zero_extendsidi2 (r1, operands[2]));
      emit_insn (gen_zero_extendsidi2 (r2, operands[3]));
      emit_move_insn (dest, acc);
      emit_insn (gen_riscv_<rvp_scalar_mul_acc_packed>
		 (gen_lowpart (PV2SImode, dest),
		  gen_lowpart (PV2SImode, r1),
		  gen_lowpart (PV2SImode, r2)));
      emit_move_insn (operands[0], gen_lowpart (SImode, dest));
    }
  else
    {
      emit_move_insn (operands[0], operands[1]);
      emit_insn (gen_riscv_<rvp_scalar_mul_acc_builtin>_rv32_rmw
		 (operands[0], operands[2], operands[3]));
    }
  DONE;
})

(define_insn "riscv_<rvp_scalar_mul_acc_builtin>_rv32_rmw"
  [(set (match_operand:SI 0 "register_operand" "+r")
	(unspec:SI [(match_dup 0)
		    (match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")]
	 RVP_SCALAR_MUL_ACC))]
  "TARGET_RVP && !TARGET_64BIT"
  "<rvp_scalar_mul_acc_rv32>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Scalar Q-format Multiply with Widening Accumulate
;
;RV32 uses an even-odd GPR pair for the 64-bit accumulator.  RV64 selects the
;low word from each source with mqacc.w00/mqracc.w00.
(define_int_iterator RVP_SCALAR_QACC
  [UNSPEC_PMQACC_W00 UNSPEC_PMQRACC_W00])

(define_int_attr rvp_scalar_qacc_builtin
  [(UNSPEC_PMQACC_W00 "mqwacc_i64")
   (UNSPEC_PMQRACC_W00 "mqrwacc_i64")])

(define_int_attr rvp_scalar_qacc_rv32
  [(UNSPEC_PMQACC_W00 "mqwacc")
   (UNSPEC_PMQRACC_W00 "mqrwacc")])

(define_int_attr rvp_scalar_qacc_rv64
  [(UNSPEC_PMQACC_W00 "mqacc_w00_i64_rv64")
   (UNSPEC_PMQRACC_W00 "mqracc_w00_i64_rv64")])

(define_expand "riscv_<rvp_scalar_qacc_builtin>"
  [(set (match_operand:DI 0 "register_operand")
	(unspec:DI [(match_operand:DI 1 "register_operand")
		    (match_operand:SI 2 "register_operand")
		    (match_operand:SI 3 "register_operand")]
	 RVP_SCALAR_QACC))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
      rtx r1 = gen_reg_rtx (DImode);
      rtx r2 = gen_reg_rtx (DImode);
      emit_insn (gen_zero_extendsidi2 (r1, operands[2]));
      emit_insn (gen_zero_extendsidi2 (r2, operands[3]));
      emit_insn (gen_riscv_<rvp_scalar_qacc_rv64>
		 (operands[0], gen_lowpart (PV2SImode, r1),
		  gen_lowpart (PV2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_<rvp_scalar_qacc_builtin>_rv32_rmw
	       (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_<rvp_scalar_qacc_builtin>_rv32_rmw"
  [(set (match_operand:DI 0 "register_operand" "+R")
	(unspec:DI [(match_dup 0)
		    (match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")]
	 RVP_SCALAR_QACC))]
  "TARGET_RVP && !TARGET_64BIT"
  "<rvp_scalar_qacc_rv32>\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Multiply High
;
;pmulh* compute the high half of the product of corresponding lanes:
;  pmulh    = signed * signed,        pmulhr   = signed * signed (rounding)
;  pmulhu   = unsigned * unsigned,    pmulhru  = unsigned * unsigned (rounding)
;  pmulhsu  = signed * unsigned,      pmulhrsu = signed * unsigned (rounding)
;32-bit forms (PV2HI lanes) use a single instruction on both ISAs
;(constraint d,s,t).  64-bit forms (PV4HI/PV2SI lanes) use a single RV64
;instruction (pmulh.h/w etc., 64-bit-only in binutils).  RV32 PV4HI forms use
;two pmulh.h instructions on the low and high halves; PV2SI forms remain
;unimplemented.
;  32-bit (both ISAs): pmulh.h, pmulhr.h, pmulhu.h, pmulhru.h, pmulhsu.h,
;                       pmulhrsu.h  (constraint d,s,t)
;  64-bit RV64:        pmulh.w, pmulhr.w, pmulhu.w, pmulhru.w, pmulhsu.w,
;                       pmulhrsu.w (constraint d,s,t)
;  64-bit RV32 PV4HI:   2x pmulh.h / pmulhr.h / etc.
;  64-bit RV32 PV2SI:   2x mulh / etc.  Not implemented yet.
;pmulhsu/pmulhrsu take a signed rs1 and unsigned rs2, so their ftypes mix
;PV2HI and UV2HI.
(define_insn "riscv_pmulh_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULH))]
  "TARGET_RVP"
  "pmulh.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhr_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULHR))]
  "TARGET_RVP"
  "pmulhr.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhu_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULHU))]
  "TARGET_RVP"
  "pmulhu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhru_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULHRU))]
  "TARGET_RVP"
  "pmulhru.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhsu_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULHSU))]
  "TARGET_RVP"
  "pmulhsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhrsu_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULHRSU))]
  "TARGET_RVP"
  "pmulhrsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Multiply High Accumulate -- 32-bit i16x2 (both ISAs, single pmhacc.h)
;rd is RMW accumulator.  define_expand copies rd into output, then RMW insn.
(define_expand "riscv_pmhacc_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")
                      (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMHACC))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhacc_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhacc_i16x2_rmw"
  [(set (match_operand:PV2HI 0 "register_operand" "+r")
        (unspec:PV2HI [(match_dup 0)
                      (match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMHACC))]
  "TARGET_RVP"
  "pmhacc.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhracc_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")
                      (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMHRACC))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhracc_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhracc_i16x2_rmw"
  [(set (match_operand:PV2HI 0 "register_operand" "+r")
        (unspec:PV2HI [(match_dup 0)
                      (match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMHRACC))]
  "TARGET_RVP"
  "pmhracc.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccu_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")
                      (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMHACCU))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhaccu_u16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhaccu_u16x2_rmw"
  [(set (match_operand:PV2HI 0 "register_operand" "+r")
        (unspec:PV2HI [(match_dup 0)
                      (match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMHACCU))]
  "TARGET_RVP"
  "pmhaccu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhraccu_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")
                      (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMHRACCU))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhraccu_u16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhraccu_u16x2_rmw"
  [(set (match_operand:PV2HI 0 "register_operand" "+r")
        (unspec:PV2HI [(match_dup 0)
                      (match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMHRACCU))]
  "TARGET_RVP"
  "pmhraccu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccsu_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")
                      (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMHACCSU))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhaccsu_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhaccsu_i16x2_rmw"
  [(set (match_operand:PV2HI 0 "register_operand" "+r")
        (unspec:PV2HI [(match_dup 0)
                      (match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMHACCSU))]
  "TARGET_RVP"
  "pmhaccsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhraccsu_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand")
                      (match_operand:PV2HI 2 "register_operand")
                      (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMHRACCSU))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhraccsu_i16x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhraccsu_i16x2_rmw"
  [(set (match_operand:PV2HI 0 "register_operand" "+r")
        (unspec:PV2HI [(match_dup 0)
                      (match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMHRACCSU))]
  "TARGET_RVP"
  "pmhraccsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Multiply High -- 64-bit forms (PV4HI lanes)
;
;RV64: single instruction pmulh.h (constraint d,s,t, PV4HI in one 64-bit reg).
;RV32: pmulh.h is a 32-bit instruction (2 lanes), so a 64-bit PV4HI source
;(4 lanes, in an even-odd register pair) needs two pmulh.h on the low/high
;halves.  We split each PV4HI operand into its low/high PV2HI subregs and emit
;two pmulh.h.  The .w 32x2 forms (pmulh.w etc.) are RV64-only in binutils and
;have no RV32 single instruction -- their RV32 form would be 2x mulh (scalar),
;left as TODO.


; ---- 64-bit i16x4: RV64 single insn, RV32 2x on high/low PV2HI halves.
; pmulh series (2 sources, output only).  RV32 uses force_reg before
; simplify_gen_subreg to avoid ICE on inlined non-REG operands.
(define_expand "riscv_pmulh_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULH))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulh_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r0 = force_reg (PV4HImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_pmulh_i16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulh_i16x2 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmulh_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULH))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulh.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulhr_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULHR))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulhr_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r0 = force_reg (PV4HImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_pmulhr_i16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulhr_i16x2 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmulhr_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULHR))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhr.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulhu_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULHU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulhu_u16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r0 = force_reg (PV4HImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_pmulhu_u16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulhu_u16x2 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmulhu_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULHU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulhru_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULHRU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulhru_u16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r0 = force_reg (PV4HImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_pmulhru_u16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulhru_u16x2 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmulhru_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULHRU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhru.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulhsu_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULHSU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulhsu_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r0 = force_reg (PV4HImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_pmulhsu_i16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulhsu_i16x2 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmulhsu_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULHSU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulhrsu_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULHRSU))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulhrsu_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r0 = force_reg (PV4HImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_pmulhrsu_i16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulhrsu_i16x2 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmulhrsu_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULHRSU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhrsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

; pmhacc series (3 sources: rd accumulator + rs1 + rs2, RMW).  RV64-only:
; define_expand copies rd into the output reg, then runs the RMW insn.
(define_expand "riscv_pmhacc_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMHACC))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhacc_i16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhacc_i16x4_rmw"
  [(set (match_operand:PV4HI 0 "register_operand" "+r")
        (unspec:PV4HI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMHACC))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhacc.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhracc_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMHRACC))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhracc_i16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhracc_i16x4_rmw"
  [(set (match_operand:PV4HI 0 "register_operand" "+r")
        (unspec:PV4HI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMHRACC))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhracc.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccu_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMHACCU))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhaccu_u16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhaccu_u16x4_rmw"
  [(set (match_operand:PV4HI 0 "register_operand" "+r")
        (unspec:PV4HI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMHACCU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhaccu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhraccu_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMHRACCU))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhraccu_u16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhraccu_u16x4_rmw"
  [(set (match_operand:PV4HI 0 "register_operand" "+r")
        (unspec:PV4HI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMHRACCU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhraccu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccsu_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMHACCSU))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhaccsu_i16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhaccsu_i16x4_rmw"
  [(set (match_operand:PV4HI 0 "register_operand" "+r")
        (unspec:PV4HI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMHACCSU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhaccsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhraccsu_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMHRACCSU))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhraccsu_i16x4_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhraccsu_i16x4_rmw"
  [(set (match_operand:PV4HI 0 "register_operand" "+r")
        (unspec:PV4HI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMHRACCSU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhraccsu.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

; ---- 64-bit i32x2: RV64 single pmulh.w / pmhacc.w (RV32 2x scalar TODO)
(define_insn "riscv_pmulh_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULH))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulh.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhr_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULHR))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhr.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhu_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULHU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhu.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhru_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULHRU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhru.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhsu_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULHSU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhsu.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulhrsu_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULHRSU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulhrsu.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

; pmhacc i32x2 (RV64 single, RV32 2x mhacc TODO)
(define_expand "riscv_pmhacc_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")
                      (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMHACC))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhacc_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhacc_i32x2_rmw"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMHACC))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhacc.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhracc_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")
                      (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMHRACC))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhracc_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhracc_i32x2_rmw"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMHRACC))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhracc.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccu_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")
                      (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMHACCU))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhaccu_u32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhaccu_u32x2_rmw"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMHACCU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhaccu.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhraccu_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")
                      (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMHRACCU))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhraccu_u32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhraccu_u32x2_rmw"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMHRACCU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhraccu.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhaccsu_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")
                      (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMHACCSU))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhaccsu_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhaccsu_i32x2_rmw"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMHACCSU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhaccsu.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmhraccsu_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV2SI 2 "register_operand")
                      (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMHRACCSU))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_pmhraccsu_i32x2_rmw (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_pmhraccsu_i32x2_rmw"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMHRACCSU))]
  "TARGET_RVP && TARGET_64BIT"
  "pmhraccsu.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed "Q-format" Multiplication
;
;pmulq* compute the Q-format product (scaled fixed-point multiply) of
;corresponding lanes: pmulq = plain Q-format, pmulqr = rounding Q-format.
;  i16x2 (both ISAs): pmulq.h, pmulqr.h  (constraint d,s,t)
;  i16x4 RV64: pmulq.h, pmulqr.h (single insn on PV4HI).
;  i16x4 RV32: two pmulq.h or pmulqr.h instructions.
;  i32x2 RV64: pmulq.w, pmulqr.w (64-bit-only insn).
;  i32x2 RV32: two mulq/mulqr instructions.  Not implemented yet.
(define_insn "riscv_pmulq_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULQ))]
  "TARGET_RVP"
  "pmulq.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulqr_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV2HI 1 "register_operand" "r")
                      (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULQR))]
  "TARGET_RVP"
  "pmulqr.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulq_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULQ))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulq_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        /* RV32: pmulq.h is a 32-bit (2-lane) instruction; a 64-bit PV4HI pair
           (4 lanes) needs two pmulq.h on the low/high PV2HI halves.  force_reg
           each operand first so simplify_gen_subreg never sees a non-REG rtx
           (which would ICE during expand on inlined subregs/mems).  */
        rtx r0 = force_reg (PV4HImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_pmulq_i16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulq_i16x2 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmulq_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULQ))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulq.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulqr_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULQR))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulqr_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r0 = force_reg (PV4HImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, r0, PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_pmulqr_i16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulqr_i16x2 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmulqr_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULQR))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulqr.h\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulq_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULQ))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulq.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulqr_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULQR))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulqr.w\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed "Q-format" Multiply Parts Accumulate
;
;mqacc.*/mqracc.* (RV32) and pmqacc.w.*/pmqracc.w.* (RV64): Q-format multiply
;of a selected pair of halfwords (h00/h01/h11) or words (w00/w01/w11), with the
;product's middle bits accumulated RMW into rd.  mqracc.* adds a rounding bias
;before extraction.
;  h-series i32  (scalar):   RV32 mqacc.h{00,01,11}/mqracc.h{00,01,11};
;                            RV64 pmqacc.w.h{00,01,11}/pmqracc.w.h{00,01,11}.
;  h-series i32x2 (packed):  RV64 pmqacc.w.h{00,01,11}/pmqracc.w.h{00,01,11};
;                            RV32 2x mqacc.h{00,01,11}/mqracc.h{00,01,11}.
;  w-series i64  (scalar):   RV64 mqacc.w{00,01,11}/mqracc.w{00,01,11};
;                            RV32 mqwacc/mqrwacc (register pair) -- TODO.
;All variants are RMW (the instruction reads and writes rd).

;-------------------- h-series i32 (scalar SI, RMW) --------------------
;rd is the accumulator (operands[1]); it is copied to the output first, then
;the RMW insn accumulates rs1*rs2 into it.  h00 = low*low, h01 = low*high
;(rs1 low * rs2 high), h11 = high*high.
(define_expand "riscv_mqacc_h00_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:PV2HI 2 "register_operand")
                    (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMQACC_H00))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
        /* RV64: pmqacc.w.h00 is a packed PV2SI instruction operating on both
           32-bit lanes.  The scalar int32_t/int16x2_t values live in lane 0
           (the low 32 bits of a GPR).  Widen rs1/rs2/rd (32-bit PV2HI/SI) to
           64-bit PV2SI via zero-extend so the full register is owned by the
           insn; lane 1 carries junk but the int32_t result only consumes
           lane 0.  Mirrors riscv_predsum_i8x4_i32 (simd.md:1907).  */
        rtx acc = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2 (acc, operands[0]));
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[3]))));
        emit_insn (gen_riscv_mqacc_h00_i32_rv64
                   (gen_lowpart (PV2SImode, acc),
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
        emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_mqacc_h00_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqacc_h00_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMQACC_H00))]
  "TARGET_RVP && !TARGET_64BIT"
  "mqacc.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mqacc_h00_i32_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQACC_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqacc.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mqacc_h01_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:PV2HI 2 "register_operand")
                    (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMQACC_H01))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
        rtx acc = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2 (acc, operands[0]));
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[3]))));
        emit_insn (gen_riscv_mqacc_h01_i32_rv64
                   (gen_lowpart (PV2SImode, acc),
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
        emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_mqacc_h01_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqacc_h01_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMQACC_H01))]
  "TARGET_RVP && !TARGET_64BIT"
  "mqacc.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mqacc_h01_i32_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQACC_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqacc.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mqacc_h11_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:PV2HI 2 "register_operand")
                    (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMQACC_H11))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
        rtx acc = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2 (acc, operands[0]));
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[3]))));
        emit_insn (gen_riscv_mqacc_h11_i32_rv64
                   (gen_lowpart (PV2SImode, acc),
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
        emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_mqacc_h11_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqacc_h11_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMQACC_H11))]
  "TARGET_RVP && !TARGET_64BIT"
  "mqacc.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mqacc_h11_i32_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQACC_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqacc.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- mqracc (rounding) h-series i32, same structure ---
(define_expand "riscv_mqracc_h00_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:PV2HI 2 "register_operand")
                    (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMQRACC_H00))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
        rtx acc = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2 (acc, operands[0]));
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[3]))));
        emit_insn (gen_riscv_mqracc_h00_i32_rv64
                   (gen_lowpart (PV2SImode, acc),
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
        emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_mqracc_h00_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqracc_h00_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_H00))]
  "TARGET_RVP && !TARGET_64BIT"
  "mqracc.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mqracc_h00_i32_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqracc.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mqracc_h01_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:PV2HI 2 "register_operand")
                    (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMQRACC_H01))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
        rtx acc = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2 (acc, operands[0]));
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[3]))));
        emit_insn (gen_riscv_mqracc_h01_i32_rv64
                   (gen_lowpart (PV2SImode, acc),
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
        emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_mqracc_h01_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqracc_h01_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_H01))]
  "TARGET_RVP && !TARGET_64BIT"
  "mqracc.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mqracc_h01_i32_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqracc.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mqracc_h11_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:SI 1 "register_operand")
                    (match_operand:PV2HI 2 "register_operand")
                    (match_operand:PV2HI 3 "register_operand")]
         UNSPEC_PMQRACC_H11))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    {
        rtx acc = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2 (acc, operands[0]));
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[3]))));
        emit_insn (gen_riscv_mqracc_h11_i32_rv64
                   (gen_lowpart (PV2SImode, acc),
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
        emit_move_insn (operands[0], gen_lowpart (SImode, acc));
    }
  else
    emit_insn (gen_riscv_mqracc_h11_i32_rv32 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqracc_h11_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "+r")
        (unspec:SI [(match_dup 0)
                    (match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_H11))]
  "TARGET_RVP && !TARGET_64BIT"
  "mqracc.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mqracc_h11_i32_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV2SI 1 "register_operand" "r")
                      (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqracc.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------------------- h-series i32x2 (packed PV2SI, RMW) --------------------
;RV64: single pmqacc.w.h*/pmqracc.w.h* on PV2SI (operands are int32x2_t/int16x4_t).
;RV32: pmqacc.w.* is RV64-only; split the 64-bit pair into low/high SI/PV2HI
;halves and run the scalar mqacc.h*/mqracc.h* on each half.
(define_expand "riscv_pmqacc_h00_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMQACC_H00))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmqacc_h00_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
        rtx r0 = force_reg (PV2SImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[2]);
        rtx r2 = force_reg (PV4HImode, operands[3]);
        rtx d_lo = simplify_gen_subreg (SImode, r0, PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, r0, PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mqacc_h00_i32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mqacc_h00_i32_rv32 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmqacc_h00_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMQACC_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqacc.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmqacc_h01_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMQACC_H01))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmqacc_h01_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
        rtx r0 = force_reg (PV2SImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[2]);
        rtx r2 = force_reg (PV4HImode, operands[3]);
        rtx d_lo = simplify_gen_subreg (SImode, r0, PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, r0, PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mqacc_h01_i32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mqacc_h01_i32_rv32 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmqacc_h01_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMQACC_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqacc.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmqacc_h11_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMQACC_H11))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmqacc_h11_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
        rtx r0 = force_reg (PV2SImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[2]);
        rtx r2 = force_reg (PV4HImode, operands[3]);
        rtx d_lo = simplify_gen_subreg (SImode, r0, PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, r0, PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mqacc_h11_i32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mqacc_h11_i32_rv32 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmqacc_h11_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMQACC_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqacc.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmqracc_h00_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMQRACC_H00))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmqracc_h00_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
        rtx r0 = force_reg (PV2SImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[2]);
        rtx r2 = force_reg (PV4HImode, operands[3]);
        rtx d_lo = simplify_gen_subreg (SImode, r0, PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, r0, PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mqracc_h00_i32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mqracc_h00_i32_rv32 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmqracc_h00_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqracc.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmqracc_h01_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMQRACC_H01))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmqracc_h01_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
        rtx r0 = force_reg (PV2SImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[2]);
        rtx r2 = force_reg (PV4HImode, operands[3]);
        rtx d_lo = simplify_gen_subreg (SImode, r0, PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, r0, PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mqracc_h01_i32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mqracc_h01_i32_rv32 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmqracc_h01_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqracc.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmqracc_h11_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV2SI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")
                      (match_operand:PV4HI 3 "register_operand")]
         UNSPEC_PMQRACC_H11))]
  "TARGET_RVP"
{
  emit_move_insn (operands[0], operands[1]);
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmqracc_h11_i32x2_rv64 (operands[0], operands[2], operands[3]));
  else
    {
        rtx r0 = force_reg (PV2SImode, operands[0]);
        rtx r1 = force_reg (PV4HImode, operands[2]);
        rtx r2 = force_reg (PV4HImode, operands[3]);
        rtx d_lo = simplify_gen_subreg (SImode, r0, PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, r0, PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mqracc_h11_i32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mqracc_h11_i32_rv32 (d_hi, s1_hi, s2_hi));
        emit_move_insn (operands[0], r0);
    }
  DONE;
})

(define_insn "riscv_pmqracc_h11_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "+r")
        (unspec:PV2SI [(match_dup 0)
                      (match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmqracc.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------------------- w-series i64 (scalar DI, RMW; RV64-only) --------------------
;mqacc.w{00,01,11}/mqracc.w{00,01,11} multiply a selected pair of 32-bit words
;(w00=low*low, w01=low*high, w11=high*high), extract bits [94:31] of the product,
;and accumulate RMW into the 64-bit rd.  RV32 uses the register-pair mqwacc/
;mqrwacc instructions -- TODO (needs even-GPR pair allocation + int32x2_t
;low-half extraction), left RV64-only like predsum_*_i64 (simd.md:2155).
(define_expand "riscv_mqacc_w00_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")
                    (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMQACC_W00))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_mqacc_w00_i64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqacc_w00_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQACC_W00))]
  "TARGET_RVP && TARGET_64BIT"
  "mqacc.w00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mqacc_w01_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")
                    (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMQACC_W01))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_mqacc_w01_i64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqacc_w01_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQACC_W01))]
  "TARGET_RVP && TARGET_64BIT"
  "mqacc.w01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mqacc_w11_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")
                    (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMQACC_W11))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_mqacc_w11_i64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqacc_w11_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQACC_W11))]
  "TARGET_RVP && TARGET_64BIT"
  "mqacc.w11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mqracc_w00_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")
                    (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMQRACC_W00))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_mqracc_w00_i64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqracc_w00_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_W00))]
  "TARGET_RVP && TARGET_64BIT"
  "mqracc.w00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mqracc_w01_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")
                    (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMQRACC_W01))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_mqracc_w01_i64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqracc_w01_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_W01))]
  "TARGET_RVP && TARGET_64BIT"
  "mqracc.w01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mqracc_w11_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:DI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")
                    (match_operand:PV2SI 3 "register_operand")]
         UNSPEC_PMQRACC_W11))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_move_insn (operands[0], operands[1]);
  emit_insn (gen_riscv_mqracc_w11_i64_rv64 (operands[0], operands[2], operands[3]));
  DONE;
})

(define_insn "riscv_mqracc_w11_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "+r")
        (unspec:DI [(match_dup 0)
                    (match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMQRACC_W11))]
  "TARGET_RVP && TARGET_64BIT"
  "mqracc.w11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;Packed Multiply Parts
;
;pmul.h.b*/pmulu.h.b*/pmulsu.h.b* multiply a selected byte pair (b00/b01/b11)
;of each 16-bit lane and produce packed 16-bit products.  mul.h*/mulu.h*/mulsu.h*
;(RV32) and pmul.w.h*/pmulu.w.h*/pmulsu.w.h* (RV64) multiply a selected halfword
;pair and produce a 32-bit product per lane.  mul.w*/mulu.w*/mulsu.w* (RV64) multiply
;a selected word pair and produce a 64-bit product.  All non-RMW (write-only rd).
;  b-series i16x2 (both ISAs): pmul.h.bNN/pmulu.h.bNN/pmulsu.h.bNN (single insn;
;    RV64 operates on 4 lanes but the PV2HI result consumes the low 2 lanes).
;  b-series i16x4 (packed): RV64 single pmul.h.bNN; RV32 2x pmul.h.bNN.
;  h-series i32 (scalar): RV32 mul.hNN; RV64 pmul.w.hNN (lane 0 = result).
;  h-series i32x2 (packed): RV64 pmul.w.hNN; RV32 2x mul.hNN.
;  w-series i64 (scalar): RV64 mul.wNN; RV32 wmul/wmulu/wmulsu (register pair)
;    -- TODO.

;-------------------- b-series i16x2 (PV4QI -> PV2HI, single insn, both ISAs) ----
;Signed: pmul.h.bNN; unsigned: pmulu.h.bNN; signed x unsigned: pmulsu.h.bNN.
(define_insn "riscv_pmul_b00_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PMUL_B00))]
  "TARGET_RVP"
  "pmul.h.b00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmul_b01_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PMUL_B01))]
  "TARGET_RVP"
  "pmul.h.b01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmul_b11_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PMUL_B11))]
  "TARGET_RVP"
  "pmul.h.b11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulu_b00_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")
                       (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PMULU_B00))]
  "TARGET_RVP"
  "pmulu.h.b00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulu_b01_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")
                       (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PMULU_B01))]
  "TARGET_RVP"
  "pmulu.h.b01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulu_b11_u16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")
                       (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PMULU_B11))]
  "TARGET_RVP"
  "pmulu.h.b11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulsu_b00_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PMULSU_B00))]
  "TARGET_RVP"
  "pmulsu.h.b00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_pmulsu_b11_i16x2"
  [(set (match_operand:PV2HI 0 "register_operand" "=r")
        (unspec:PV2HI [(match_operand:PV4QI 1 "register_operand" "r")
                      (match_operand:PV4QI 2 "register_operand" "r")]
         UNSPEC_PMULSU_B11))]
  "TARGET_RVP"
  "pmulsu.h.b11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------------------- h-series i32 (PV2HI -> SI scalar; RV32 mul.hNN, RV64 pmul.w.hNN) ----
;RV64: pmul.w.hNN is a packed PV2SI insn; the scalar PV2HI/SI values live in lane 0.
;Widen rs1/rs2 (PV2HI, 32-bit) via zero-extend to DI so the full 64-bit reg is owned
;by the insn; lane 1 product is discarded.  rd (SI) takes the low 32 bits directly.
;Mirrors riscv_predsum_i8x4_i32 (simd.md:1907), non-RMW form.
(define_expand "riscv_mul_h00_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand")
                    (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PMUL_H00))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        emit_insn (gen_riscv_mul_h00_i32_rv64
                   (operands[0],
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mul_h00_i32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mul_h00_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMUL_H00))]
  "TARGET_RVP && !TARGET_64BIT"
  "mul.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mul_h00_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMUL_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmul.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mul_h01_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand")
                    (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PMUL_H01))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        emit_insn (gen_riscv_mul_h01_i32_rv64
                   (operands[0],
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mul_h01_i32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mul_h01_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMUL_H01))]
  "TARGET_RVP && !TARGET_64BIT"
  "mul.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mul_h01_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMUL_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmul.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mul_h11_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand")
                    (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PMUL_H11))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        emit_insn (gen_riscv_mul_h11_i32_rv64
                   (operands[0],
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mul_h11_i32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mul_h11_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMUL_H11))]
  "TARGET_RVP && !TARGET_64BIT"
  "mul.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mul_h11_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMUL_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmul.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- mulu_h* (unsigned) ---
(define_expand "riscv_mulu_h00_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand")
                     (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PMULU_H00))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        emit_insn (gen_riscv_mulu_h00_u32_rv64
                   (operands[0],
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mulu_h00_u32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulu_h00_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand" "r")
                     (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULU_H00))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulu.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mulu_h00_u32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2SI 1 "register_operand" "r")
                     (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULU_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulu.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mulu_h01_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand")
                     (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PMULU_H01))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        emit_insn (gen_riscv_mulu_h01_u32_rv64
                   (operands[0],
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mulu_h01_u32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulu_h01_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand" "r")
                     (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULU_H01))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulu.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mulu_h01_u32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2SI 1 "register_operand" "r")
                     (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULU_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulu.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mulu_h11_u32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand")
                     (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PMULU_H11))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        emit_insn (gen_riscv_mulu_h11_u32_rv64
                   (operands[0],
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mulu_h11_u32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulu_h11_u32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand" "r")
                     (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULU_H11))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulu.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mulu_h11_u32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2SI 1 "register_operand" "r")
                     (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULU_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulu.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;--- mulsu_h* (signed x unsigned) ---
(define_expand "riscv_mulsu_h00_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand")
                    (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PMULSU_H00))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        emit_insn (gen_riscv_mulsu_h00_i32_rv64
                   (operands[0],
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mulsu_h00_i32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulsu_h00_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULSU_H00))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulsu.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mulsu_h00_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULSU_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulsu.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mulsu_h11_i32"
  [(set (match_operand:SI 0 "register_operand")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand")
                    (match_operand:PV2HI 2 "register_operand")]
         UNSPEC_PMULSU_H11))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    {
        rtx r1 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r1, force_reg (SImode, gen_lowpart (SImode, operands[1]))));
        rtx r2 = gen_reg_rtx (DImode);
        emit_insn (gen_zero_extendsidi2
                   (r2, force_reg (SImode, gen_lowpart (SImode, operands[2]))));
        emit_insn (gen_riscv_mulsu_h11_i32_rv64
                   (operands[0],
                    gen_lowpart (PV2SImode, r1),
                    gen_lowpart (PV2SImode, r2)));
    }
  else
    emit_insn (gen_riscv_mulsu_h11_i32_rv32 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulsu_h11_i32_rv32"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2HI 1 "register_operand" "r")
                    (match_operand:PV2HI 2 "register_operand" "r")]
         UNSPEC_PMULSU_H11))]
  "TARGET_RVP && !TARGET_64BIT"
  "mulsu.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_insn "riscv_mulsu_h11_i32_rv64"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULSU_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulsu.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------------------- b-series i16x4 (PV8QI -> PV4HI; RV64 single, RV32 2x) ----
;RV32 splits the 64-bit pair into low/high PV4QI/PV2HI halves and runs the i16x2
;single insn on each (operands[0] PV4HI subregs are valid write-only outputs).
(define_expand "riscv_pmul_b00_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")
                      (match_operand:PV8QI 2 "register_operand")]
         UNSPEC_PMUL_B00))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmul_b00_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV8QImode, operands[1]);
        rtx r2 = force_reg (PV8QImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 4);
        emit_insn (gen_riscv_pmul_b00_i16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmul_b00_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmul_b00_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")
                      (match_operand:PV8QI 2 "register_operand" "r")]
         UNSPEC_PMUL_B00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmul.h.b00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmul_b01_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")
                      (match_operand:PV8QI 2 "register_operand")]
         UNSPEC_PMUL_B01))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmul_b01_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV8QImode, operands[1]);
        rtx r2 = force_reg (PV8QImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 4);
        emit_insn (gen_riscv_pmul_b01_i16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmul_b01_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmul_b01_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")
                      (match_operand:PV8QI 2 "register_operand" "r")]
         UNSPEC_PMUL_B01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmul.h.b01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmul_b11_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")
                      (match_operand:PV8QI 2 "register_operand")]
         UNSPEC_PMUL_B11))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmul_b11_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV8QImode, operands[1]);
        rtx r2 = force_reg (PV8QImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 4);
        emit_insn (gen_riscv_pmul_b11_i16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmul_b11_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmul_b11_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")
                      (match_operand:PV8QI 2 "register_operand" "r")]
         UNSPEC_PMUL_B11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmul.h.b11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulu_b00_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")
                       (match_operand:PV8QI 2 "register_operand")]
         UNSPEC_PMULU_B00))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulu_b00_u16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV8QImode, operands[1]);
        rtx r2 = force_reg (PV8QImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 4);
        emit_insn (gen_riscv_pmulu_b00_u16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulu_b00_u16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulu_b00_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")
                       (match_operand:PV8QI 2 "register_operand" "r")]
         UNSPEC_PMULU_B00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulu.h.b00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulu_b01_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")
                       (match_operand:PV8QI 2 "register_operand")]
         UNSPEC_PMULU_B01))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulu_b01_u16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV8QImode, operands[1]);
        rtx r2 = force_reg (PV8QImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 4);
        emit_insn (gen_riscv_pmulu_b01_u16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulu_b01_u16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulu_b01_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")
                       (match_operand:PV8QI 2 "register_operand" "r")]
         UNSPEC_PMULU_B01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulu.h.b01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulu_b11_u16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")
                       (match_operand:PV8QI 2 "register_operand")]
         UNSPEC_PMULU_B11))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulu_b11_u16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV8QImode, operands[1]);
        rtx r2 = force_reg (PV8QImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 4);
        emit_insn (gen_riscv_pmulu_b11_u16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulu_b11_u16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulu_b11_u16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")
                       (match_operand:PV8QI 2 "register_operand" "r")]
         UNSPEC_PMULU_B11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulu.h.b11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulsu_b00_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")
                      (match_operand:PV8QI 2 "register_operand")]
         UNSPEC_PMULSU_B00))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulsu_b00_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV8QImode, operands[1]);
        rtx r2 = force_reg (PV8QImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 4);
        emit_insn (gen_riscv_pmulsu_b00_i16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulsu_b00_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulsu_b00_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")
                      (match_operand:PV8QI 2 "register_operand" "r")]
         UNSPEC_PMULSU_B00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulsu.h.b00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulsu_b11_i16x4"
  [(set (match_operand:PV4HI 0 "register_operand")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand")
                      (match_operand:PV8QI 2 "register_operand")]
         UNSPEC_PMULSU_B11))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulsu_b11_i16x4_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV8QImode, operands[1]);
        rtx r2 = force_reg (PV8QImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 0);
        rtx d_hi = simplify_gen_subreg (PV2HImode, operands[0], PV4HImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV4QImode, r1, PV8QImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV4QImode, r2, PV8QImode, 4);
        emit_insn (gen_riscv_pmulsu_b11_i16x2 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_pmulsu_b11_i16x2 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulsu_b11_i16x4_rv64"
  [(set (match_operand:PV4HI 0 "register_operand" "=r")
        (unspec:PV4HI [(match_operand:PV8QI 1 "register_operand" "r")
                      (match_operand:PV8QI 2 "register_operand" "r")]
         UNSPEC_PMULSU_B11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulsu.h.b11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------------------- h-series i32x2 (PV4HI -> PV2SI; RV64 single pmul.w.hNN, RV32 2x mul.hNN) ----
;RV32 splits the 64-bit pair into low/high SI/PV2HI halves and runs the scalar
;h-series _rv32 insn on each.
(define_expand "riscv_pmul_h00_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMUL_H00))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmul_h00_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (SImode, operands[0], PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, operands[0], PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mul_h00_i32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mul_h00_i32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmul_h00_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMUL_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmul.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmul_h01_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMUL_H01))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmul_h01_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (SImode, operands[0], PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, operands[0], PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mul_h01_i32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mul_h01_i32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmul_h01_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMUL_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmul.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmul_h11_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMUL_H11))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmul_h11_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (SImode, operands[0], PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, operands[0], PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mul_h11_i32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mul_h11_i32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmul_h11_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMUL_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmul.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulu_h00_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")
                       (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULU_H00))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulu_h00_u32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (SImode, operands[0], PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, operands[0], PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mulu_h00_u32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mulu_h00_u32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulu_h00_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")
                       (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULU_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulu.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulu_h01_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")
                       (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULU_H01))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulu_h01_u32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (SImode, operands[0], PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, operands[0], PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mulu_h01_u32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mulu_h01_u32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulu_h01_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")
                       (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULU_H01))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulu.w.h01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulu_h11_u32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")
                       (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULU_H11))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulu_h11_u32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (SImode, operands[0], PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, operands[0], PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mulu_h11_u32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mulu_h11_u32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulu_h11_u32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")
                       (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULU_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulu.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulsu_h00_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULSU_H00))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulsu_h00_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (SImode, operands[0], PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, operands[0], PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mulsu_h00_i32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mulsu_h00_i32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulsu_h00_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULSU_H00))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulsu.w.h00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_pmulsu_h11_i32x2"
  [(set (match_operand:PV2SI 0 "register_operand")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand")
                      (match_operand:PV4HI 2 "register_operand")]
         UNSPEC_PMULSU_H11))]
  "TARGET_RVP"
{
  if (TARGET_64BIT)
    emit_insn (gen_riscv_pmulsu_h11_i32x2_rv64 (operands[0], operands[1], operands[2]));
  else
    {
        rtx r1 = force_reg (PV4HImode, operands[1]);
        rtx r2 = force_reg (PV4HImode, operands[2]);
        rtx d_lo = simplify_gen_subreg (SImode, operands[0], PV2SImode, 0);
        rtx d_hi = simplify_gen_subreg (SImode, operands[0], PV2SImode, 4);
        rtx s1_lo = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 0);
        rtx s1_hi = simplify_gen_subreg (PV2HImode, r1, PV4HImode, 4);
        rtx s2_lo = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 0);
        rtx s2_hi = simplify_gen_subreg (PV2HImode, r2, PV4HImode, 4);
        emit_insn (gen_riscv_mulsu_h11_i32_rv32 (d_lo, s1_lo, s2_lo));
        emit_insn (gen_riscv_mulsu_h11_i32_rv32 (d_hi, s1_hi, s2_hi));
    }
  DONE;
})

(define_insn "riscv_pmulsu_h11_i32x2_rv64"
  [(set (match_operand:PV2SI 0 "register_operand" "=r")
        (unspec:PV2SI [(match_operand:PV4HI 1 "register_operand" "r")
                      (match_operand:PV4HI 2 "register_operand" "r")]
         UNSPEC_PMULSU_H11))]
  "TARGET_RVP && TARGET_64BIT"
  "pmulsu.w.h11\t%0,%1,%2"
  [(set_attr "type" "simd")])

;-------------------- w-series i64 (PV2SI -> DI scalar; RV64-only) ----
;mul.wNN/mulu.wNN/mulsu.wNN multiply a selected word pair (w00/w01/w11) and
;produce a 64-bit product.  RV32 uses wmul/wmulu/wmulsu (register pair) -- TODO
;(needs even-GPR pair allocation), left RV64-only like mqacc_w*_i64.
(define_expand "riscv_mul_w00_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PMUL_W00))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_mul_w00_i64_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})
; TODO(RV32): wmul uses a register-pair destination (even GPR); needs register-pair
; allocation.  Left RV64-only, matching mqacc_w*_i64 / predsum_*_i64.

(define_insn "riscv_mul_w00_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMUL_W00))]
  "TARGET_RVP && TARGET_64BIT"
  "mul.w00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mul_w01_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PMUL_W01))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_mul_w01_i64_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mul_w01_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMUL_W01))]
  "TARGET_RVP && TARGET_64BIT"
  "mul.w01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mul_w11_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PMUL_W11))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_mul_w11_i64_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mul_w11_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMUL_W11))]
  "TARGET_RVP && TARGET_64BIT"
  "mul.w11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mulu_w00_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand")
                     (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PMULU_W00))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_mulu_w00_u64_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulu_w00_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand" "r")
                     (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULU_W00))]
  "TARGET_RVP && TARGET_64BIT"
  "mulu.w00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mulu_w01_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand")
                     (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PMULU_W01))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_mulu_w01_u64_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulu_w01_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand" "r")
                     (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULU_W01))]
  "TARGET_RVP && TARGET_64BIT"
  "mulu.w01\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mulu_w11_u64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand")
                     (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PMULU_W11))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_mulu_w11_u64_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulu_w11_u64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand" "r")
                     (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULU_W11))]
  "TARGET_RVP && TARGET_64BIT"
  "mulu.w11\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mulsu_w00_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PMULSU_W00))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_mulsu_w00_i64_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulsu_w00_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULSU_W00))]
  "TARGET_RVP && TARGET_64BIT"
  "mulsu.w00\t%0,%1,%2"
  [(set_attr "type" "simd")])

(define_expand "riscv_mulsu_w11_i64"
  [(set (match_operand:DI 0 "register_operand")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand")
                    (match_operand:PV2SI 2 "register_operand")]
         UNSPEC_PMULSU_W11))]
  "TARGET_RVP && TARGET_64BIT"
{
  emit_insn (gen_riscv_mulsu_w11_i64_rv64 (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "riscv_mulsu_w11_i64_rv64"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:PV2SI 1 "register_operand" "r")
                    (match_operand:PV2SI 2 "register_operand" "r")]
         UNSPEC_PMULSU_W11))]
  "TARGET_RVP && TARGET_64BIT"
  "mulsu.w11\t%0,%1,%2"
  [(set_attr "type" "simd")])
