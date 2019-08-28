;; Register numbers
(define_constants
  [
    (R0_REGNUM		0)
    (R1_REGNUM		1)
    (R2_REGNUM		2)
    (R3_REGNUM		3)
    (R4_REGNUM		4)
    (R5_REGNUM		5)
    (R6_REGNUM		6)
    (R7_REGNUM		7)
    (R8_REGNUM		8)
    (R9_REGNUM		9)
    (R10_REGNUM		10)
    (R11_REGNUM		11)
    (R12_REGNUM		12)
    (R13_REGNUM		13)
    (R14_REGNUM		14)
    (R15_REGNUM		15)
    (R16_REGNUM		16)
    (R17_REGNUM		17)
    (R18_REGNUM		18)
    (R19_REGNUM		19)
    (R20_REGNUM		20)
    (R21_REGNUM		21)
    (R22_REGNUM		22)
    (R23_REGNUM		23)
    (R24_REGNUM		24)
    (R25_REGNUM		25)
    (R26_REGNUM		26)
    (R27_REGNUM		27)
    (SP_REGNUM		28)
    (ILINK_REGNUM	29)
    (R30_REGNUM		30)
    (BLINK_REGNUM	31)
    (R32_REGNUM		32)
    (R33_REGNUM		33)
    (R34_REGNUM		34)
    (R35_REGNUM		35)
    (R36_REGNUM		36)
    (R37_REGNUM		37)
    (R38_REGNUM		38)
    (R39_REGNUM		39)
    (R40_REGNUM		40)
    (R41_REGNUM		41)
    (R42_REGNUM		42)
    (R43_REGNUM		43)
    (R44_REGNUM		44)
    (R45_REGNUM		45)
    (R46_REGNUM		46)
    (R47_REGNUM		47)
    (R48_REGNUM		48)
    (R49_REGNUM		49)
    (R50_REGNUM		50)
    (R51_REGNUM		51)
    (R52_REGNUM		52)
    (R53_REGNUM		53)
    (R54_REGNUM		54)
    (R55_REGNUM		55)
    (R56_REGNUM		56)
    (R57_REGNUM		57)
    (R58_REGNUM		58)
    (R59_REGNUM		59)
    (R60_REGNUM		60)
    (AP_REGNUM		64)
    (SFP_REGNUM		65)
    (CC_REGNUM		66)
  ]
)

;; -------------------------------------------------------------------
;; Mode Iterators
;; -------------------------------------------------------------------


;; Iterator for General Purpose Integer registers (32- and 64-bit modes)
(define_mode_iterator GPI [SI DI])

;; Iterator for all integer modes.
(define_mode_iterator ALLI [QI HI SI DI])

;; -------------------------------------------------------------------
;; Moves
;; -------------------------------------------------------------------

(define_expand "mov<mode>"
  [(set (match_operand:ALLI 0 "nonimmediate_operand")
	(match_operand:ALLI 1 "general_operand"))]
  ""
  "
  if (arc64_prepare_move_operands (opernads[0], operands[1], <MODE>mode))
    DONE;
  "
  )

(define_insn_and_split "*movsi_arc64"             ;  3     4   5  12  13  14  15 16   17   18  22  23 26 27  28
  [(set (match_operand:SI 0 "nonimmediate_operand" "=q,   qh,  r,  q,  h,  r,  q, S  Us<,qRck,!*Rcd,r,m,  m,VUsc")
	(match_operand:SI 1 "arc64_mov_operand"    " P,qhCm1,rLI,Cax,Cal,Cal,Uts, q,qRck  Us>,  Ucd,m,r,Cm3, C32"))]
  "register_operand (operands[0], SImode)
   || register_operand (operands[1], SImode)
   || (CONSTANT_P (operands[1])
       && satisfies_constraint_Usc (operands[0]))
   || (satisfies_constraint_Cm3 (operands[1])
      && memory_operand (operands[0], SImode))"
  "@
   mov%?\\t%0,%1	;3
   mov%?\\t%0,%1	;4
   mov%?\\t%0,%1	;5
   #
   mov%?\\t%0,%j1	;13
   mov%?\\t%0,%j1	;14
   ld%?\\t%0,%1		;15
   st%?\\t%1,%0		;16
   push%?\\t%1          ;17
   pop%?\\t%0           ;18
   ld%?\\t%0,%1		;22
   ld%U1%V1\\t%0,%1	;23
   st%U0%V0\\t%1,%0	;26
   st%U0%V0\\t%1,%0	;27
   st%U0%V0\\t%1,%0	;28"
  "reload_completed && satisfies_constraint_Cax (operands[1])
   && register_operand (operands[0], SImode)"
  [(const_int 0)]
  "
   arc64_split_mov_const (operands);
   DONE;
  "
   ;                          3    4     5    12   13    14   15    16    17   18   22   23    26    27   28
  [(set_attr "type"       "move,move, move,multi,move, move,load,store,store,load,load,load,store,store,store")
   (set_attr "iscompact"  "true,true,false,false,true,false,true, true, true,true,true,true,false,false,false")
   (set_attr "length"        "*,   *,    4,    *,   6,    *,   *,    *,    *,   *,   4,   *,    *,   *,   8")
   (set_attr "predicable"   "no,  no,  yes,   no, yes,  yes,  no,   no,   no,  no,  no,  no,   no,  no,  no")])

(define_insn "*movdi_arc64"
  [(set (match_operand:DI 0 "nonimmediate_operand" "=qh,  r,  r,r,m")
	(match_operand:DI 1 "arc64_mov_operand"    " qh,rLI,X32,m,r"))]
  ""
  "register_operand (operands[0], DImode)
   || register_operand (operands[1], DImode)"
  "@
   movl%?\\t%0,%1
   movl%?\\t%0,%1
   movl%?\\t%0,%1
   ldl%U1%V1\\t%0,%1
   stl%U0%V0\\t%1,%0"
  [(set_attr "type" "move,move,move,load,store")
   (set_attr "length" "2,4,8,8,8")])


(define_insn "*movqi_arc64"
  [(set (match_operand:QI 0 "nonimmediate_operand" "=q,   qh,  r,h,w,q,  r,r,   m,Usc")
	(match_operand:QI 1 "arc64_mov_operand"    " P,qhCm1,rLI,i,i,T,Ucm,m,rCm3,i"))]
  "register_operand (operands[0], QImode)
   || register_operand (operands[1], QImode)
   || (satisfies_constraint_Cm3 (operands[1])
       && memory_operand (operands[0], QImode))"
  "@
   mov%?\\t%0,%1
   mov%?\\t%0,%1
   mov%?\\t%0,%1
   mov%?\\t%0,%1
   mov%?\\t%0,%1
   ldb%?\\t%0,%1
   ldb%U1%V1\\t%0,%1
   stb%U0%V0\\t%1,%0
   stb%U0%V0\\t%1,%0"
  [(set_attr "type"       "move,move, move, move,      move,load, load,store,store")
   (set_attr "iscompact"  "true,true,false,false,maybe_limm,true,false,false,false")])

(define_insn "*movhi_arc64"
  [(set (match_operand:HI 0 "move_dest_operand" "=q,   qh,  r,q,h, r,  q,r,   m,VUsc")
	(match_operand:HI 1 "move_src_operand" "  P,qhCm1,rLI,i,i, i,  T,m,rCm3,i"))]
  "register_operand (operands[0], HImode)
   || register_operand (operands[1], HImode)
   || (satisfies_constraint_Cm3 (operands[1])
       && memory_operand (operands[0], HImode))"
  "@
   mov%?\\t%0,%1
   mov%?\\t%0,%1
   mov%?\\t%0,%1
   mov%?\\t%0,%1
   mov%?\\t%0,%1
   mov%?\\t%0,%1
   ldh%?\\t%0,%1%&
   ldh%U1%V1\\t%0,%1
   sth%U0%V0\\t%1,%0
   sth%U0%V0\\t%1,%0"
  [(set_attr "type"      "move,move, move,      move,      move, move,load, load,store,store")
   (set_attr "iscompact" "true,true,false,maybe_limm,maybe_limm,false,true,false,false,false")])


;; -------------------------------------------------------------------
;; Subroutine calls and sibcalls
;; -------------------------------------------------------------------

(define_expand "call"
  [(parallel [(call (match_operand 0 "memory_operand")
		    (match_operand 1 "general_operand"))
	     (clobber (reg:DI BLINK_REGNUM))])]
  ""
  {
   arc64_expand_call (NULL_RTX, operands[0], false);
   DONE;
  }
)

(define_insn "*call_insn"
  [(call (mem:DI (match_operand:DI 0 "arc64_call_address_operand" "q,r,Cbp,Cbr,L,I,Cal"))
	 (match_operand 1 "" ""))
   (clobber (reg:DI BLINK_REGNUM))]
  ""
  "@
   jl%!%*\\t[%0]
   jl%!%*\\t[%0]
   bl%!%*\\t%P0
   bl%!%*\\t%P0
   jl%!%*\\t%0
   jl%*\\t%0
   jl%!\\t%0"
  [(set_attr "type" "call,call,call,call,call,call,call_no_delay_slot")
   (set_attr "length" "*,4,2,4,4,4,8")])

(define_expand "call_value"
  [(parallel [(set (match_operand 0 "" "")
		   (call (match_operand 1 "memory_operand")
			 (match_operand 2 "general_operand")))
	      (clobber (reg:DI BLINK_REGNUM))])]
  ""
  "
  {
    arc64_expand_call (operands[0], operands[1], false);
    DONE;
  }"
)

(define_insn "*call_value_insn"
  [(set (match_operand 0 "" "")
	(call (mem:DI (match_operand:DI 1 "arc64_call_address_operand" "q,c,Cbp,Cbr,L,I,Cal"))
	      (match_operand 2 "" "")))
   (clobber (reg:DI BLINK_REGNUM))]
  ""
  "@
   jl%!%*\\t[%1]
   jl%!%*\\t[%1]
   bl%!%*\\t%P1
   bl%!%*\\t%P1
   jl%!%*\\t%1
   jl%*\\t%1
   jl%!\\t%1"
  [(set_attr "type" "call,call,call,call,call,call,call_no_delay_slot")
   (set_attr "length" "*,4,2,4,4,4,8")])

(define_expand "sibcall"
  [(parallel [(call (match_operand 0 "memory_operand")
		    (match_operand 1 "general_operand"))
	      (return)
	      (use (match_operand 2 "" ""))])]
  ""
  {
    arc64_expand_call (NULL_RTX, operands[0], true);
    DONE;
  }

(define_expand "sibcall_value"
  [(parallel [(set (match_operand 0 "" "")
		   (call (match_operand 1 "memory_operand")
			 (match_operand 2 "general_operand")))
	      (return)
	      (use (match_operand 3 "" ""))])]
  ""
  {
    arc64_expand_call (operands[0], operands[1], true);
    DONE;
  }
)

(define_insn "*sibcall_insn"
 [(call (mem:DI (match_operand:DI 0 "arc64_call_address_operand"
				  "Cbp,Cbr,!Rcd,Rsc,Cal"))
	(match_operand 1 "" ""))
  (return)
  (use (match_operand 2 "" ""))]
  "SIBLIG_CALL_P (insn)"
  "@
   b%!%*\\t%P0
   b%!%*\\t%P0
   j%!%*\\t[%0]
   j%!%*\\t[%0]
   j%!\\t%P0"
  [(set_attr "type" "call,call,call,call,call_no_delay_slot")
   (set_attr "predicable" "yes,no,no,yes,yes")
   (set_attr "iscompact" "false,false,maybe,false,false")]
)

(define_insn "*sibcall_value_insn"
 [(set (match_operand 0 "" "")
       (call (mem:DI (match_operand:DI 1 "call_address_operand"
				       "Cbp,Cbr,!Rcd,Rsc,Cal"))
	     (match_operand 2 "" "")))
  (return)
  (use (match_operand 3 "" ""))]
  "SIBLING_CALL_P (insn)"
  "@
   b%!%*\\t%P1
   b%!%*\\t%P1
   j%!%*\\t[%1]
   j%!%*\\t[%1]
   j%!\\t%P1"
  [(set_attr "type" "call,call,call,call,call_no_delay_slot")
   (set_attr "predicable" "yes,no,no,yes,yes")
   (set_attr "iscompact" "false,false,maybe,false,false")]
)

;; Call subroutine returning any type.

;FIXME!;(define_expand "untyped_call"
;FIXME!;  [(parallel [(call (match_operand 0 "")
;FIXME!;		    (const_int 0))
;FIXME!;	      (match_operand 1 "")
;FIXME!;	      (match_operand 2 "")])]
