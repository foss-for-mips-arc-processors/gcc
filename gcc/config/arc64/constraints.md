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
(define_register_constraint "Rsc" "SIBCALL_REGS"
  "@internal
   Sibling call register")

;; Register suited for mov_s g,h instructions like.
;; FIXME! check if we get better code when it is register_constraint.
(define_constraint "h"
  "@internal
   Register usable in short move instructions: @code{r0}-@code{r31}"
  (and (match_code "reg")
       (match_test "REGNO (op) < R32_REGNO")))

; Usc constant is only used for storing long constants, hence we can
; have only [b,s9], and [b] types of addresses.
(define_memory_constraint "Usc"
  "@internal
   A valid memory operand for storing constants"
  (and (match_code "mem")
       (match_test "!CONSTANT_P (XEXP (op,0))")))

(define_constraint "Us<"
  "@internal
   Stack pre-decrement"
  (and (match_code "mem")
       (match_test "GET_CODE (XEXP (op, 0)) == PRE_DEC")
       (match_test "REG_P (XEXP (XEXP (op, 0), 0))")
       (match_test "REGNO (XEXP (XEXP (op, 0), 0)) == SP_REG")))

(define_constraint "Us>"
  "@internal
   Stack post-increment"
  (and (match_code "mem")
       (match_test "GET_CODE (XEXP (op, 0)) == POST_INC")
       (match_test "REG_P (XEXP (XEXP (op, 0), 0))")
       (match_test "REGNO (XEXP (XEXP (op, 0), 0)) == SP_REG")))

(define_constraint "Ucm"
  "@internal
  cmem access"
  (and (match_code "mem")
       (match_test "TARGET_NPS_CMEM && cmem_address (XEXP (op, 0), VOIDmode)")))

;; Internal immediate constraint used to split move instructions.
(define_constraint "Cax"
  "@internal
  special const_int pattern used to split move insns"
  (and (match_code "const_int")
       (match_test "optimize_size")
       (match_test "arc_check_mov_const (ival)")))
