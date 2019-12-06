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
	    (match_operand 0 "memory_operand")
	    (match_code "unspec")
	    (and (match_code "const_int")
		 (ior (match_test "UNSIGNED_INT32 (INTVAL (op))")
		      (match_test "SIGNED_INT32 (INTVAL (op))"))))))

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

; to be used for br{eq/ne}_s instructions.
(define_predicate "equality_comparison_operator"
  (match_code "eq, ne"))

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
