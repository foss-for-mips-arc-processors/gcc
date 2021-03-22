;; Machine description for arc64 architecture.
;; Copyright (C) 2019 Free Software Foundation, Inc.
;; Contributed by Claudiu Zissulescu
;;
;; This file is part of GCC.
;;
;; GCC is free software; you can redistribute it and/or modify it
;; under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.
;;
;; GCC is distributed in the hope that it will be useful, but
;; WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
;; General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;; Place holder for mov operand predicate
(define_predicate "arc64_movl_operand"
  (and (match_code "unspec,reg, subreg, mem, const, const_int, symbol_ref, label_ref")
       (ior (match_operand 0 "register_operand")
	    (and (ior (match_code "label_ref")
		      (match_code "symbol_ref"))
		 (match_test "arc64_allow_direct_access_p (op)"))
	    (match_operand 0 "memory_operand")
	    (and (match_code "unspec")
		 (ior (match_test "XINT (op,1) == ARC64_UNSPEC_PCREL")
		      (match_test "XINT (op,1) == ARC64_UNSPEC_TLS_GD")))
	    (and (match_code "const_int")
		 (ior (match_test "UNSIGNED_INT32 (INTVAL (op))")
		      (match_test "SIGNED_INT32 (INTVAL (op))"))))))

(define_predicate "arc64_movf_operand"
  (and (match_code "reg, subreg, mem, const, const_double")
       (ior (match_operand 0 "register_operand")
	    (match_operand 0 "memory_operand")
	    (and (match_code "const_double")
		 (ior (match_test "GET_MODE_SIZE (GET_MODE (op)) <= 4")
		      (match_test "op == CONST0_RTX (DFmode)"))))))

;; A restricted version of the above, still accepting symbols and label refs.
(define_predicate "arc64_regsym_operand"
  (ior (match_operand 0 "register_operand")
       (and (ior (match_code "label_ref")
		 (match_code "symbol_ref"))
	    (match_test "arc64_allow_direct_access_p (op)"))
       (and (match_code "const_int")
	    (ior (match_test "UNSIGNED_INT32 (INTVAL (op))")
		 (match_test "SIGNED_INT32 (INTVAL (op))")))))

(define_predicate "arc64_nonmem_operand"
  (ior (match_operand 0 "register_operand")
       (and (match_code "const_int")
	    (ior (match_test "UNSIGNED_INT32 (INTVAL (op))")
		 (match_test "SIGNED_INT32 (INTVAL (op))")))))

;; Used for HIGH or LO_SUM patterns
(define_predicate "arc64_immediate_or_pic"
  (ior (match_operand 0 "immediate_operand")
       (match_code "unspec")))

;; Acceptable arguments for the call insn.
(define_predicate "arc64_call_insn_operand"
  (ior (and (match_code "symbol_ref")
	    (match_test "!arc64_is_long_call_p (op)"))
       (match_operand 0 "register_operand")))

; to be used for b{eq/ne}_s instructions.
(define_predicate "equality_comparison_operator"
  (match_code "eq, ne"))

; to be used for b{eq/ne/...}_s instructions.
(define_predicate "ccmode_comparison_operator"
  (match_code "eq, ne, gt, ge, lt, le, gtu, geu, ltu, leu,
	       unlt, unle, unge, ungt")
  {
   enum rtx_code code = GET_CODE (op);

   switch (GET_MODE (XEXP (op, 0)))
   {
     case E_CC_FPUmode:
     case E_CC_FPUEmode:
     case E_CCmode:
       return 1;

     case E_CC_ZNmode:
       return (code == EQ || code == NE);

     default:
       return 0;
     }
  })


;; True for integer comparisons and for FP comparisons other then LTGT or UNEQ
(define_special_predicate "arc64_comparison_operator"
  (match_code "eq, ne, le, lt, ge, gt, geu, gtu, leu, ltu, unordered,
	       ordered, unlt, unle, unge, ungt"))

(define_special_predicate "cc_register"
  (match_code "reg")
{
  if (mode == VOIDmode)
    {
      mode = GET_MODE (op);
      if (GET_MODE_CLASS (mode) != MODE_CC)
	return FALSE;
    }

  if (mode == GET_MODE (op) && GET_CODE (op) == REG && REGNO (op) == CC_REGNUM)
    return TRUE;

  return FALSE;
})

;; Return TRUE if OP is a shimm 6bit value
(define_predicate "S06S0_immediate_operand"
  (and (match_code "const_int")
       (match_test "SIGNED_INT6 (INTVAL (op))"))
)

;; Return true if OP is a MEM that when used as a load or store address will
;; require an 8 byte insn.
;; Load and store instructions don't allow the same possibilities but they're
;; similar enough that this one function will do.
;; This is currently only used when calculating length attributes.  */
(define_predicate "limm_ldst_operand"
  (and (match_code "mem")
       (match_test "arc64_limm_addr_p (op)")))

;; Allows only 1,2,3 values.  It is used with add/sub shifted operations.
(define_predicate "_1_2_3_operand"
  (and (match_code "const_int")
       (match_test "INTVAL (op) == 1 || INTVAL (op) == 2 || INTVAL (op) == 3"))
)

;; Allows only 1,2,3 values.  It is used with add/sub shifted operations.
(define_predicate "_2_4_8_operand"
  (and (match_code "const_int")
       (match_test "INTVAL (op) == 2 || INTVAL (op) == 4 || INTVAL (op) == 8"))
)

;; Return TRUE if OP can be used as a destination for any move
;; (mov,st,ld) instruction.
(define_predicate "arc64_dest_operand"
  (match_code "reg, subreg, mem")
  {
   if (MEM_P (op))
      return arc64_legitimate_store_address_p (mode, XEXP (op, 0));
   return nonimmediate_operand (op, mode);
  })

(define_predicate "mem_noofs_operand"
  (and (match_code "mem")
       (match_code "reg" "0")))

