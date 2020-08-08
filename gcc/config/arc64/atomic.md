;; GCC machine description for ARC atomic instructions.
;; Copyright (C) 2015-2020 Free Software Foundation, Inc.
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

(define_mode_iterator QHSDI [QI HI SI DI])
(define_mode_iterator SDI [SI DI])

(define_code_iterator atomicop [plus minus ior xor and])
(define_code_attr atomic_optab
  [(ior "or") (xor "xor") (and "and") (plus "add") (minus "sub")])

(define_expand "memory_barrier"
  [(set (match_dup 0)
	(unspec:BLK [(match_dup 0)] ARC64_UNSPEC_MEMBAR))]
  ""
{
  operands[0] = gen_rtx_MEM (BLKmode, gen_rtx_SCRATCH (Pmode));
  MEM_VOLATILE_P (operands[0]) = 1;
})

;; A compiler-only memory barrier for ARC700.  Generic code, when
;; checking for the existence of various named patterns, uses
;; asm("":::"memory") when we don't need an actual instruction.  For
;; ARCHS, we use a hardware data memory barrier that waits for
;; completion of current data memory operations before initiating
;; similar data memory operations.
(define_insn "*memory_barrier"
  [(set (match_operand:BLK 0 "" "")
	(unspec:BLK [(match_dup 0)] ARC64_UNSPEC_MEMBAR))]
  ""
  {
       return "dmb\\t3";
  }
  [(set_attr "type" "dmb")
   (set_attr "length" "4")])

(define_expand "atomic_compare_and_swap<mode>"
  [(match_operand:SI 0 "register_operand" "")		;; bool out
   (match_operand:QHSDI 1 "register_operand" "")	;; val out
   (match_operand:QHSDI 2 "mem_noofs_operand" "")	;; memory
   (match_operand:QHSDI 3 "register_operand" "")	;; expected
   (match_operand:QHSDI 4 "register_operand" "")	;; desired
   (match_operand:SI 5 "const_int_operand")		;; is_weak
   (match_operand:SI 6 "const_int_operand")		;; mod_s
   (match_operand:SI 7 "const_int_operand")]		;; mod_f
  ""
{
  arc64_expand_compare_and_swap (operands);
  DONE;
})

(define_insn_and_split "atomic_compare_and_swap<mode>_1"
  [(set (reg:CC_Z CC_REGNUM)					;; bool out
	(unspec_volatile:CC_Z [(const_int 0)] ARC64_VUNSPEC_CAS))
   (set (match_operand:SDI 0 "register_operand"      "=&r")		;; val out
	(match_operand:SDI 1 "mem_noofs_operand"      "+ATOMC"))	;; memory
   (set (match_dup 1)
	(unspec_volatile
	  [(match_operand:SDI 2 "register_operand"     "r") ;; expect
	   (match_operand:SDI 3 "register_operand"     "r") ;; desired
	   (match_operand:SI 4 "const_int_operand")	;; is_weak
	   (match_operand:SI 5 "const_int_operand")	;; mod_s
	   (match_operand:SI 6 "const_int_operand")]	;; mod_f
	  ARC64_VUNSPEC_CAS))]
  ""
  "#"
  "&& reload_completed"
  [(const_int 0)]
  {
    arc64_split_compare_and_swap (operands);
    DONE;
  })

(define_insn "arc_load_exclusive<mode>"
  [(set (match_operand:SDI 0 "register_operand" "=r")
	(unspec_volatile:SDI
	  [(match_operand:SDI 1 "mem_noofs_operand" "ATOMC")]
	  ARC64_VUNSPEC_LL))]
  ""
  "llock<mcctab> %0,%1"
  [(set_attr "type" "llock")
   (set_attr "iscompact" "no")
   (set_attr "predicable" "no")
   (set_attr "length" "*")])

(define_insn "arc_store_exclusive<mode>"
  [(set (match_operand:SDI 0 "mem_noofs_operand"     "=ATOMC")
	(unspec_volatile:SDI[(match_operand:SDI 1 "register_operand" "r")]
			   ARC64_VUNSPEC_SC))
   (clobber (reg:CC_Z CC_REGNUM))]
  ""
  "scond<mcctab> %1,%0"
  [(set_attr "type" "scond")
   (set_attr "iscompact" "no")
   (set_attr "predicable" "no")
   (set_attr "length" "*")])

(define_expand "atomic_exchangesi"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "mem_noofs_operand" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:SI 3 "const_int_operand" "")]
  ""
{
  enum memmodel model = (enum memmodel) INTVAL (operands[3]);

  if (model == MEMMODEL_SEQ_CST)
    emit_insn (gen_sync ());
  emit_insn (gen_exchangesi (operands[0], operands[1], operands[2]));
  DONE;
})

(define_insn "exchange<mode>"
  [(set (match_operand:SDI 0 "register_operand" "=r")
	(unspec_volatile:SDI [(match_operand:SDI 1 "mem_noofs_operand" "+ATOMC")]
			    ARC64_VUNSPEC_EX))
   (set (match_dup 1)
	(match_operand:SDI 2 "register_operand" "0"))]
  ""
  "ex<mcctab> %0,%1"
  [(set_attr "type" "ex")
   (set_attr "iscompact" "no")
   (set_attr "predicable" "no")
   (set_attr "length" "*")])

(define_expand "atomic_<atomic_optab>si"
  [(match_operand:SI 0 "mem_noofs_operand" "")  ;; memory
   (atomicop:SI (match_dup 0)
		(match_operand:SI 1 "register_operand" "")) ;; operand
   (match_operand:SI 2 "const_int_operand" "")] ;; model
  ""
{
  arc64_expand_atomic_op (<CODE>, operands[0], operands[1],
				NULL_RTX, NULL_RTX, operands[2]);
  DONE;
})

(define_expand "atomic_nandsi"
  [(match_operand:SI 0 "mem_noofs_operand" "")	;; memory
   (match_operand:SI 1 "register_operand" "")	;; operand
   (match_operand:SI 2 "const_int_operand" "")]	;; model
  ""
{
 arc64_expand_atomic_op (NOT, operands[0], operands[1],
			    NULL_RTX, NULL_RTX, operands[2]);
 DONE;
})

(define_expand "atomic_fetch_<atomic_optab><mode>"
  [(match_operand:SDI 0 "register_operand" "")	;; output
   (match_operand:SDI 1 "mem_noofs_operand" "")	;; memory
   (atomicop:SI (match_dup 1)
		(match_operand:SDI 2 "register_operand" "")) ;; operand
   (match_operand:SI 3 "const_int_operand" "")]	;; model
  ""
{
  arc64_expand_atomic_op (<CODE>, operands[1], operands[2],
				operands[0], NULL_RTX, operands[3]);
  DONE;
})

(define_expand "atomic_fetch_nand<mode>"
  [(match_operand:SDI 0 "register_operand" "")	;; output
   (match_operand:SDI 1 "mem_noofs_operand" "")	;; memory
   (match_operand:SDI 2 "register_operand" "")	;; operand
   (match_operand:SDI 3 "const_int_operand" "")]	;; model
  ""
{
  arc64_expand_atomic_op (NOT, operands[1], operands[2],
			     operands[0], NULL_RTX, operands[3]);
  DONE;
})

(define_expand "atomic_<atomic_optab>_fetch<mode>"
  [(match_operand:SDI 0 "register_operand" "")	;; output
   (match_operand:SDI 1 "mem_noofs_operand" "")	;; memory
   (atomicop:SDI (match_dup 1)
		(match_operand:SDI 2 "register_operand" "")) ;; operand
   (match_operand:SDI 3 "const_int_operand" "")]	;; model
  ""
{
  arc64_expand_atomic_op (<CODE>, operands[1], operands[2],
				NULL_RTX, operands[0], operands[3]);
  DONE;
})

(define_expand "atomic_nand_fetch<mode>"
  [(match_operand:SDI 0 "register_operand" "")		;; output
   (match_operand:SDI 1 "mem_noofs_operand" "")		;; memory
   (match_operand:SDI 2 "register_operand" "")		;; operand
   (match_operand:SDI 3 "const_int_operand" "")]	;; model
  ""
{
  arc64_expand_atomic_op (NOT, operands[1], operands[2],
			     NULL_RTX, operands[0], operands[3]);
  DONE;
})

