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

(define_code_attr GPIsuffix [(SI "") (DI "l")])

;; Iterator for QI and HI modes
(define_mode_iterator SHORT [QI HI])

;; Iterator for all integer modes (up to 64-bit)
(define_mode_iterator ALLI [QI HI SI DI])


;; -------------------------------------------------------------------
;; Instruction types and attributes
;; -------------------------------------------------------------------

;; -------------------------------------------------------------------
;; Pipeline descriptions and scheduling
;; -------------------------------------------------------------------

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
	      (use (match_operand 2 "" ""))
	     (clobber (reg:DI BLINK_REGNUM))])]
  ""
  {
   arc64_expand_call (NULL_RTX, operands[0], false);
   DONE;
  }
)

(define_insn "*call_insn"
  [(call (mem:DI (match_operand:DI 0 "arc64_call_address_operand" "q,r,BLsym"))
	 (match_operand 1 "" ""))
   (clobber (reg:DI BLINK_REGNUM))]
  ""
  "@
   jl_s\\t[%0]
   jl%!%*\\t[%0]
   bl%!%*\\t%c0"
  [(set_attr "type" "jl,jl,bl")
   (set_attr "predicable" "no,yes,yes")
   (set_attr "length" "2,4,4")])

(define_expand "call_value"
  [(parallel [(set (match_operand 0 "" "")
		   (call (match_operand 1 "memory_operand")
			 (match_operand 2 "general_operand")))
	      (use (match_operand 3 "" ""))
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
	(call (mem:DI (match_operand:DI 1 "arc64_call_address_operand"
					"q,r,BLsym"))
	      (match_operand 2 "" "")))
   (clobber (reg:DI BLINK_REGNUM))]
  ""
  "@
   jl_s\\t[%1]
   jl%!\\t[%1]
   bl%!\\t%c1"
  [(set_attr "type" "jl,jl,bl")
   (set_attr "predicable" "no,yes,yes")
   (set_attr "length" "2,4,4")])

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
 [(call (mem:DI (match_operand:DI 0 "arc64_call_address_operand" "Sbreg,BLsym"))
	(match_operand 1 "" ""))
  (return)]
  "SIBLIG_CALL_P (insn)"
  "@
   j%!\\t[%0]
   b%!\\t%c0"
  [(set_attr "type" "jump,branch")
   (set_attr "predicable" "yes,yes")
   (set_attr "iscompact" "maybe,no")]
)

(define_insn "*sibcall_value_insn"
 [(set (match_operand 0 "" "")
       (call (mem:DI (match_operand:DI 1 "call_address_operand" "Sbreg,BLsym"))
	     (match_operand 2 "" "")))
  (return)]
  "SIBLING_CALL_P (insn)"
  "@
   j%!\\t[%1]
   b%!\\t%c1"
  [(set_attr "type" "jump,branch")
   (set_attr "predicable" "yes,yes")
   (set_attr "iscompact" "maybe,no")]
)

;; -------------------------------------------------------------------
;; Jumps and other miscellaneous insns
;; -------------------------------------------------------------------

(define_insn "indirect_jump"
  [(set (pc) (match_operand:DI 0 "register_operand" "q,r"))]
  ""
  "@
   j%!\\t[%0]
   j%!\\t[%0]"
  [(set_attr "type" "jump")
   (set_attr "predicable" "no,yes")
   (set_attr "iscompact" "yes,no")]
)

(define_insn "jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  ""
  "b%!\\t%l0"
  [(set_attr "type" "branch")
   (set (attr "length")
	(if_then_else
	 (and (ge (minus (match_dup 0) (pc)) (const_int -512))
	      (le (minus (match_dup 0) (pc)) (const_int 506)))
	 (const_int 4)
	 (const_int 2)))]
)

(define_expand "cbranch<mode>4"
  [(set (pc) (if_then_else
	      (match_operator 0 "ordered_comparison_operator"
			      [(match_operand:GPI 1 "nonmemory_operand")
			       (match_operand:GPI 2 "nonmemory_operand")])
	      (label_ref (match_operand 3 "" ""))
	      (pc)))]
  ""
  "
  operands[1] = arc64_gen_compare_reg (GET_CODE (operands[0]), operands[1],
					 operands[2]);
  operands[2] = const0_rtx;
  "
  )

(define_insn "condjump"
  [(set (pc) (if_then_else
	      (match_operator 0 "ordered_comparison_operator"
			      [(match_operand 1 "cc_register" "")
			       (const_int 0)])
	      (label_ref (match_operand 2 "" ""))
	      (pc)))]
  ""
  "b%m0%!\\t%l2"
  [(set_attr "type" "branchcc")
   (set_attr "compact" "maybe")
   (set (attr "length")
	[(cond
	  [(and (match_operand 1 "equality_comparison_operator" "")
		(and (ge (minus (match_dup 2) (pc)) (const_int -512))
		     (le (minus (match_dup 2) (pc)) (const_int 506))))
	   (const_int 2)

	   (and (ge (minus (match_dup 2) (pc)) (const_int -62))
		(le (minus (match_dup 2) (pc)) (const_int 60)))
	   (const_int 2)]
	  (const_int 4))])]
  )

(define_expand "prologue"
  [(clobber (const_int 0))]
  ""
  "
  arc64_expand_prologue ();
  DONE;
  "
)

(define_expand "epilogue"
  [(clobber (const_int 0))]
  ""
  "
  arc64_expand_epilogue (false);
  DONE;
  "
)

(define_expand "sibcall_epilogue"
  [(clobber (const_int 0))]
  ""
  "
  arc64_expand_epilogue (true);
  DONE;
  "
)

(define_expand "return"
  [(return)]
  "arc64_can_use_return_insn ()"
  "")

(define_insn "simple_return"
  [(simple_return)]
  "arc64_use_simple_return_insn_p ()"
  "j%!%*\\t[blink]"
  [(set_attr "type" "return")
   (set_attr "cond" "canuse")
   (set_attr "iscompact" "maybe")
   (set_attr "length" "*")])

;; -------------------------------------------------------------------
;; Sign/Zero extension
;; -------------------------------------------------------------------

(define_expand "<optab>sidi2"
  [(set (match_operand:DI 0 "register_operand")
	(ANY_EXTEND:DI (match_operand:SI 1 "nonimmediate_operand")))]
  ""
)

(define_expand "<ANY_EXTEND:optab><SHORT:mode><GPI:mode>2"
  [(set (match_operand:GPI 0 "register_operand")
        (ANY_EXTEND:GPI (match_operand:SHORT 1 "nonimmediate_operand")))]
  ""
)

(define_expand "<optab>qihi2"
  [(set (match_operand:HI 0 "register_operand")
        (ANY_EXTEND:HI (match_operand:QI 1 "nonimmediate_operand")))]
  ""
)

;; -------------------------------------------------------------------
;; Simple arithmetic
;; -------------------------------------------------------------------

(define_expand "add<mode>3"
  [(set
    (match_operand:GPI 0 "register_operand")
    (plus:GPI (match_operand:GPI 1 "register_operand")
	      (match_operand:GPI 2 "arc64_pluslong_or_int_operand")))]
  ""
  )

(define_expand "addv<mode>4"
  [(match_operand:GPI 0 "register_operand")
   (match_operand:GPI 1 "register_operand")
   (match_operand:GPI 2 "arc64_plus_operand")
   (label_ref (match_operand 3 "" ""))]
  ""
  )

(define_expand "uaddv<mode>4"
  [(match_operand:GPI 0 "register_operand")
   (match_operand:GPI 1 "register_operand")
   (match_operand:GPI 2 "register_operand")
   (label_ref (match_operand 3 "" ""))]
  ""
)

(define_expand "subv<GPI:mode>4"
  [(match_operand:GPI 0 "register_operand")
   (match_operand:GPI 1 "register_operand")
   (match_operand:GPI 2 "arc64_plus_operand")
   (label_ref (match_operand 3 "" ""))]
  ""
  )

(define_expand "negv<GPI:mode>3"
  [(match_operand:GPI 0 "register_operand")
   (match_operand:GPI 1 "register_operand")
   (label_ref (match_operand 2 "" ""))]
  ""
  )

(define_expand "usubv<mode>4"
  [(match_operand:GPI 0 "register_operand")
   (match_operand:GPI 1 "arc64_reg_or_zero")
   (match_operand:GPI 2 "arc64_reg_or_zero")
   (label_ref (match_operand 3 "" ""))]
  ""
  )

(define_expand "abs<mode>2"
  [(match_operand:GPI 0 "register_operand")
   (match_operand:GPI 1 "register_operand")]
  ""
  )

;; -------------------------------------------------------------------
;; Comparison insns
;; -------------------------------------------------------------------

(define_insn "cmp<mode>"
  [(set (reg:CC CC_REGNUM)
	(compare:CC (match_operand:GPI 0 "nonmemory_operand" "r,    r,    r,U06S0,S12S0,i,r")
		    (match_operand:GPI 1 "nonmemory_operand" "r,U06S0,S12S0,    r,    r,r,i")))]
  "register_operand (operands[0])
   || reister_operand (operands[1])"
  "@
   cmp<GPIsuffix>%?\\t%0,%1
   cmp<GPIsuffix>%?\\t%0,%1
   cmp<GPIsuffix>%?\\t%0,%1
   rcmp<GPIsuffix>%?\\t%1,%0
   rcmp<GPIsuffix>%?\\t%1,%0
   rcmp<GPIsuffix>%?\\t%1,%0
   cmp<GPIsuffix>%?\\t%0,%1"
  [(set_attr "type" "compare")
   (set_attr "iscompact" "false")
   (set_attr "predicable" "yes,yes,no,yes,no,no,no")
   (set_attr "length" "*,*,*,*,*,8,8")])


;; -------------------------------------------------------------------
;; Store-flag and conditional select insns
;; -------------------------------------------------------------------

(define_expand "cstore<mode>4"
  [(set (match_operand:SI 0 "register_operand")
	(match_operator:SI 1 "arc64_comparison_operator"
	 [(match_operand:GPI 2 "register_operand")
	  (match_operand:GPI 3 "arc64_plus_operand")]))]
  ""
  )

(define_expand "mov<mode>cc"
  [(set (match_operand:ALLI 0 "register_operand")
	(if_then_else:ALLI (match_operand 1 "arc64_comparison_operator")
			   (match_operand:ALLI 2 "register_operand")
			   (match_operand:ALLI 3 "register_operand")))]
  ""
  )

;; -------------------------------------------------------------------
;; Logical operations
;; -------------------------------------------------------------------


;; -------------------------------------------------------------------
;; Shifts
;; -------------------------------------------------------------------

(define_expand "<optab><mode>3"
  [(set (match_operand:GPI 0 "register_operand")
	(ASHIFT:GPI (match_operand:GPI 1 "register_operand")
		    (match_operand:QI 2 "arc64_reg_or_imm")))]
  ""
)

(define_expand "ashl<mode>3"
  [(set (match_operand:SHORT 0 "register_operand")
	(ashift:SHORT (match_operand:SHORT 1 "register_operand")
		      (match_operand:QI 2 "const_int_operand")))]
  ""
)

(define_expand "rotr<mode>3"
  [(set (match_operand:GPI 0 "register_operand")
	(rotatert:GPI (match_operand:GPI 1 "register_operand")
		      (match_operand:QI 2 "arc64_reg_or_imm")))]
  ""
)

;; -------------------------------------------------------------------
;; Bitfields
;; -------------------------------------------------------------------

;; -------------------------------------------------------------------
;; Floating-point intrinsics
;; -------------------------------------------------------------------

;; -------------------------------------------------------------------
;; Floating-point conversions
;; -------------------------------------------------------------------

;; -------------------------------------------------------------------
;; Floating-point arithmetic
;; -------------------------------------------------------------------
