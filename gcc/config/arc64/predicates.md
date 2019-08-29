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
(define_predicate "arc64_mov_operand"
  (and (match_code "reg, subreg, mem, const, const_int, symbol_ref, label_ref")
       (ior (match_operand 0 "register_operand")
	    (match_operand 0 "memory_operand"))))

;; Acceptable arguments for the call insn.
(define_predicate "arc64_call_insn_operand"
  (ior (match_code "symbol_ref")
       (match_operand 0 "register_operand")))
