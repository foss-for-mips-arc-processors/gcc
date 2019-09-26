;; Constraint definitions for Synopsys DesignWare ARC.
;; Copyright (C) 2019 Free Software Foundation, Inc.
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

;; Register constraints

;; Register suited for short instructions.
(define_register_constraint "q" "AC16_REGS"
  "Registers usable in short 16-bit like instructions: @code{r0}-@code{r3},
@code{r12}-@code{r15}")

;; Register suited for sibling calls.
(define_register_constraint "Sbreg" "SIBCALL_REGS"
  "@internal
   Sibling call register")

;; Register suited for mov_s g,h instructions like.
;; FIXME! check if we get better code when it is register_constraint.
(define_constraint "h"
  "@internal
   Register usable in short move instructions: @code{r0}-@code{r31}"
  (and (match_code "reg")
       (match_test "REGNO (op) < R32_REGNUM")))

; Usc constant is only used for storing long constants, hence we can
; have only [b,s9], and [b] types of addresses.
(define_memory_constraint "Ucnst"
  "@internal
   A valid memory operand for storing constants"
  (and (match_code "mem")
       (match_test "!CONSTANT_P (XEXP (op,0))")))

;(define_constraint "Us<"
;  "@internal
;   Stack pre-decrement"
;  (and (match_code "mem")
;       (match_test "GET_CODE (XEXP (op, 0)) == PRE_DEC")
;       (match_test "REG_P (XEXP (XEXP (op, 0), 0))")
;       (match_test "REGNO (XEXP (XEXP (op, 0), 0)) == SP_REG")))
;
;(define_constraint "Us>"
;  "@internal
;   Stack post-increment"
;  (and (match_code "mem")
;       (match_test "GET_CODE (XEXP (op, 0)) == POST_INC")
;       (match_test "REG_P (XEXP (XEXP (op, 0), 0))")
;       (match_test "REGNO (XEXP (XEXP (op, 0), 0)) == SP_REG")))
;
;;; Internal immediate constraint used to split move instructions.
;(define_constraint "Cax"
;  "@internal
;  special const_int pattern used to split move insns"
;  (and (match_code "const_int")
;       (match_test "optimize_size")
;       (match_test "arc_check_mov_const (ival)")))

(define_constraint "BLsym"
  "@internal
  is a symbol reference allowed by the BL instruction"
  (match_code "symbol_ref"))

(define_constraint "U06M1"
  "@internal
   An unsigned 6-bit integer constant, up to 62."
  (and (match_code "const_int")
       (match_test "UNSIGNED_INT6 (ival - 1)")))

(define_constraint "S32S0"
  "@internal
   Special constant/symbol which fits in limm field."
  (match_code "const_int, symbol_ref, label_ref"))

(define_constraint "S06S0" "@internal
  A 6-bit signed integer constant"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT6 (ival)")))

;---------------------------------------------------------

(define_constraint "U06S0" "@internal
  A 6-bit unsigned integer constant"
  (and
    (match_code "const_int")
    (match_test "UNSIGNED_INT6 (ival)")))

(define_constraint "U06S1" "@internal
  A 6-bit unsigned integer constant shifted by 1-bit(s)"
  (and
    (match_code "const_int")
    (match_test "UNSIGNED_INT7_SHIFTED (ival,1)")))

(define_constraint "U06S2" "@internal
  A 6-bit unsigned integer constant shifted by 2-bit(s)"
  (and
    (match_code "const_int")
    (match_test "UNSIGNED_INT8_SHIFTED (ival,2)")))

(define_constraint "U06S3" "@internal
  A 6-bit unsigned integer constant shifted by 3-bit(s)"
  (and
    (match_code "const_int")
    (match_test "UNSIGNED_INT9_SHIFTED (ival,3)")))

(define_constraint "S12S0" "@internal
  A 12-bit signed integer constant"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT12 (ival)")))

(define_constraint "S12S1" "@internal
  A 12-bit signed integer constant shifted by 1-bit(s)"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT13_SHIFTED (ival,1)")))

(define_constraint "S12S2" "@internal
  A 12-bit signed integer constant shifted by 2-bit(s)"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT14_SHIFTED (ival,2)")))

(define_constraint "S12S3" "@internal
  A 12-bit signed integer constant shifted by 3-bit(s)"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT15_SHIFTED (ival,3)")))

(define_constraint "S03S0" "@internal
  A 3-bit signed integer constant"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT3 (ival)")))

(define_constraint "U07S0" "@internal
  A 7-bit unsigned integer constant"
  (and
    (match_code "const_int")
    (match_test "UNSIGNED_INT7 (ival)")))

(define_constraint "U03S0" "@internal
  A 3-bit unsigned integer constant"
  (and
    (match_code "const_int")
    (match_test "UNSIGNED_INT3 (ival)")))

(define_constraint "S11S0" "@internal
  A 11-bit signed integer constant"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT11 (ival)")))

(define_constraint "U05S0" "@internal
  A 5-bit unsigned integer constant"
  (and
    (match_code "const_int")
    (match_test "UNSIGNED_INT5 (ival)")))

(define_constraint "S09S0" "@internal
  A 9-bit signed integer constant"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT9 (ival)")))

(define_constraint "S21S0" "@internal
  A 21-bit signed integer constant"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT21 (ival)")))

(define_constraint "S25S0" "@internal
  A 25-bit signed integer constant"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT25 (ival)")))

(define_constraint "S10S0" "@internal
  A 10-bit signed integer constant"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT10 (ival)")))

(define_constraint "S07S0" "@internal
  A 7-bit signed integer constant"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT7 (ival)")))

(define_constraint "S13S0" "@internal
  A 13-bit signed integer constant"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT13 (ival)")))

(define_constraint "S08S0" "@internal
  A 8-bit signed integer constant"
  (and
    (match_code "const_int")
    (match_test "SIGNED_INT8 (ival)")))

(define_constraint "U10S0" "@internal
  A 10-bit unsigned integer constant"
  (and
    (match_code "const_int")
    (match_test "UNSIGNED_INT10 (ival)")))

(define_constraint "U08S0" "@internal
  A 8-bit unsigned integer constant"
  (and
    (match_code "const_int")
    (match_test "UNSIGNED_INT8 (ival)")))

(define_constraint "U09S0" "@internal
  A 9-bit unsigned integer constant"
  (and
    (match_code "const_int")
    (match_test "UNSIGNED_INT9 (ival)")))

(define_constraint "ULIMM" "@internal
  A 32-bit unsigned integer constant"
  (match_code "const_int"))

(define_constraint "UXIMM" "@internal
  A 32-bit signed extended integer constant"
  (match_code "const_int"))


; TODO: Below this line definition should be corrected
(define_constraint "SR_R0"
  "@internal
   @code{R0} register."
  (and (match_code "reg")
       (match_test "REGNO (op) == R0_REGNUM")))

(define_constraint "SR_R1"
  "@internal
   @code{R1} register."
  (and (match_code "reg")
       (match_test "REGNO (op) == R1_REGNUM")))

(define_constraint "SR_SP"
  "@internal
   @code{SP} register."
  (and (match_code "reg")
       (match_test "REGNO (op) == SP_REGNUM")))

; TODO: FIX THIS
(define_constraint "SR_GP"
  "@internal
   @code{GP} register."
  (and (match_code "reg")
       (match_test "REGNO (op) == R0_REGNUM")))

; TODO: FIX THIS
(define_constraint "SRPCL"
  "@internal
   @code{PCL} register."
  (and (match_code "reg")
       (match_test "REGNO (op) == R0_REGNUM")))
