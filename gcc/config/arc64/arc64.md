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

    (AP_REGNUM		64)
    (SFP_REGNUM		65)
    (CC_REGNUM		66)
  ]
  )

(define_c_enum "unspec"
  [
   VUNSPEC_ARC_BLOCKAGE
   ])

(include "constraints.md")
(include "predicates.md")

;; -------------------------------------------------------------------
;; Mode Iterators
;; -------------------------------------------------------------------

;; Iterator for General Purpose Integer registers (32- and 64-bit modes)
(define_mode_iterator GPI [SI DI])

;; Iterator for QI and HI modes
(define_mode_iterator SHORT [QI HI])

;; Iterator for QI HI and SI modes
(define_mode_iterator EXT [QI HI SI])

;; Iterator for all integer modes (up to 64-bit)
(define_mode_iterator ALLI [QI HI SI DI])

;; -------------------------------------------------------------------
;; Code Iterators
;; -------------------------------------------------------------------

;; Code iterator for sign/zero extension
(define_code_iterator ANY_EXTEND [sign_extend zero_extend])

;; This code iterator allows the shifts supported in arithmetic instructions
(define_code_iterator ASHIFT [ashift ashiftrt lshiftrt])

;; Iterates over the SETcc instructions
(define_code_iterator SETCC [eq ne gt lt ge le ltu geu])

;; Three operand arithmetic operations
(define_code_iterator ARITH [plus minus])

;; Three operand logic operations
(define_code_iterator LOGIC [and ior xor smin smax])

;; Two operand logic operations
(define_code_iterator LOGIC2 [not abs])
;; -------------------------------------------------------------------
;; Mode Attributes
;; -------------------------------------------------------------------

;; Map rtl mode to ARC mnemonic suffixes used in sign extend
;; instructions.
(define_mode_attr exttab [(QI "b") (HI "h") (SI "w")])

;; Map rtl mode to ARC mnemonic suffixes
(define_mode_attr sfxtab [(QI "b") (HI "h") (SI "") (DI "l")])

;; -------------------------------------------------------------------
;; Code Attributes
;; -------------------------------------------------------------------
;; Map rtl objects to optab names
(define_code_attr optab [(ashift "ashl")
			 (ashiftrt "ashr")
			 (lshiftrt "lshr")
			 (rotatert "rotr")
			 (sign_extend "extend")
			 (zero_extend "zero_extend")
			 (sign_extract "extv")
			 (zero_extract "extzv")
			 (fix "fix")
			 (unsigned_fix "fixuns")
			 (float "float")
			 (unsigned_float "floatuns")
			 (popcount "popcount")
			 (and "and")
			 (ior "ior")
			 (xor "xor")
			 (not "one_cmpl")
			 (neg "neg")
			 (plus "add")
			 (minus "sub")
			 (mult "mul")
			 (div "div")
			 (udiv "udiv")
			 (ss_plus "qadd")
			 (us_plus "qadd")
			 (ss_minus "qsub")
			 (us_minus "qsub")
			 (ss_neg "qneg")
			 (ss_abs "qabs")
			 (smin "smin")
			 (smax "smax")
			 (umin "umin")
			 (umax "umax")
			 (eq "eq")
			 (ne "ne")
			 (lt "lt")
			 (ge "ge")
			 (le "le")
			 (gt "gt")
			 (ltu "ltu")
			 (leu "leu")
			 (geu "geu")
			 (gtu "gtu")
			 (abs "abs")
			 (sqrt "sqrt")])

;; map rtl to ARC mnemonic names, slightly different than above.
(define_code_attr cctab [(abs "abs")
			 (not "not")
			 (eq "eq")
			 (ne "ne")
			 (lt "lt")
			 (ge "ge")
			 (le "le")
			 (gt "gt")
			 (ltu "lo")
			 (leu "NA")
			 (geu "hs")
			 (gtu "NA")])
;; -------------------------------------------------------------------
;; Instruction types and attributes
;; -------------------------------------------------------------------

(define_attr "type" "abs, add, addl, and, andl, asl, asll, asr, asrl,
bl, block, bmsk, branch, branchcc, bset, bsetl, bxor, bxorl, compare,
div, jl, jump, ld, lsr, lsrl, max, maxl, min, minl, move, neg, nop,
norm, normh, norml, not, notl, or, orl, rem, reml, remu, remul,
return, ror, setcc, sex, st, sub, subl, swape, swapel, udiv, udivl,
unknown, xor, xorl"
  (const_string "unknown"))

(define_attr "iscompact" "yes,no,maybe" (const_string "no"))

(define_attr "predicable" "yes,no" (const_string "no"))

(define_attr "length" ""
  (cond
   [
    (eq_attr "type" "ld")
    (if_then_else
     (match_operand 1 "limm_ldst_operand" "")
     (const_int 8) (const_int 4))

    (eq_attr "type" "st")
    (if_then_else
     (ior (match_operand 0 "limm_ldst_operand" "")
	  (and (not (match_operand 1 "S06S0_immediate_operand" ""))
	       (match_operand 1 "immediate_operand" "")))
     (const_int 8) (const_int 4))
    ]
   (const_int 8)))

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
  if (arc64_prepare_move_operands (operands[0], operands[1], <MODE>mode))
    DONE;
  "
  )

;; We use movsf for soft and hard floats.
(define_expand "movsf"
  [(set (match_operand:SF 0 "nonimmediate_operand" "")
	(match_operand:SF 1 "general_operand"))]
  ""
  {
   if (arc64_prepare_move_operands (operands[0], operands[1], SFmode))
      DONE;
   })

;(define_insn_and_split "*movsi_arc64"             ;  3     4   5  12  13  14  15 16   17   18  22  23 26 27  28
;  [(set (match_operand:SI 0 "nonimmediate_operand" "=q,   qh,  r,  q,  h,  r,  q, S  Us<,qRck,!*Rcd,r,m,  m,VMcnst")
;	(match_operand:SI 1 "arc64_mov_operand"    " P,qhCm1,rLI,Cax,Cal,Cal,Uts, q,qRck  Us>,  Ucd,m,r,Cm3,   i"))]
;  "register_operand (operands[0], SImode)
;   || register_operand (operands[1], SImode)
;   || (CONSTANT_P (operands[1])
;       && satisfies_constraint_Usc (operands[0]))
;   || (satisfies_constraint_Cm3 (operands[1])
;      && memory_operand (operands[0], SImode))"
;  "@
;   mov%?\\t%0,%1	;3
;   mov%?\\t%0,%1	;4
;   mov%?\\t%0,%1	;5
;   #
;   mov%?\\t%0,%j1	;13
;   mov%?\\t%0,%j1	;14
;   ld%?\\t%0,%1		;15
;   st%?\\t%1,%0		;16
;   push%?\\t%1          ;17
;   pop%?\\t%0           ;18
;   ld%?\\t%0,%1		;22
;   ld%U1%V1\\t%0,%1	;23
;   st%U0%V0\\t%1,%0	;26
;   st%U0%V0\\t%1,%0	;27
;   st%U0%V0\\t%1,%0	;28"
;  "reload_completed && satisfies_constraint_Cax (operands[1])
;   && register_operand (operands[0], SImode)"
;  [(const_int 0)]
;  "
;   arc64_split_mov_const (operands);
;   DONE;
;  "
;   ;                          3    4     5    12   13    14   15    16    17   18   22   23    26    27   28
;  [(set_attr "type"       "move,move, move,multi,move, move,load,store,store,load,load,load,store,store,store")
;   (set_attr "iscompact"  "true,true,false,false,true,false,true, true, true,true,true,true,false,false,false")
;   (set_attr "length"        "*,   *,    4,    *,   6,    *,   *,    *,    *,   *,   4,   *,    *,   *,   8")
;   (set_attr "predicable"   "no,  no,  yes,   no, yes,  yes,  no,   no,   no,  no,  no,  no,   no,  no,  no")])


;; mov<.f>        b, c
;; mov<.f>        b, s12
;; mov_s          b, u8
;; mov_s          g, h
;;
;; ld             a, [b, s9]
;; ld             a, [b,  c]
;; ld             a, [limm ]
;;
;; st<zz>         c   , [b , s9]
;; st<zz>         limm, [b , s9]
;; stb_s          b   , [sp, u7]
;; stb_s          c   , [b , u5]
(define_insn "*arc64_movqi"
   [(set (match_operand:QI 0 "nonimmediate_operand" "=qh, r,     q, r,     m, m, r, m")
	 (match_operand:QI 1 "general_operand"      " qh, r, U08S0, i, S06S0, i, m, r"))
   ]
   ; in general, at least one of the operands must be a register
   "register_operand (operands[0], QImode)
   || register_operand (operands[1], QImode)
   /* this is to match 'stb w6, [limm]' (S06S0 is the w6).  */
   || (satisfies_constraint_S06S0 (operands[1])
       && memory_operand (operands[0], QImode))
   /* writing a byte into memory using limm variant.  */
   || (immediate_operand (operands[1], QImode)
       && memory_operand (operands[0], QImode))"
   "@
    mov_s\\t%0,%1
    mov\\t%0,%1
    mov_s\\t%0,%1
    mov\\t%0,%1
    stb%U0\\t%1,[%0]
    stb%U0\\t%1,[%0]
    ldb%U1\\t%0,[%1]
    stb%U0\\t%1,[%0]"
   [(set_attr "type" "move,move,move,move,st,st,ld,st")
    (set_attr "length" "2,4,2,4,*,8,*,*")]
)

(define_insn "*arc64_movhi"
  [(set (match_operand:HI 0 "nonimmediate_operand" "=qh, r,     q, r,     m, m, r, m")
	(match_operand:HI 1 "general_operand"      " qh, r, U08S0, i, S06S0, i, m, r"))
   ]
  "register_operand (operands[0], HImode)
   || register_operand (operands[1], HImode)
   || (satisfies_constraint_S06S0 (operands[1])
       && memory_operand (operands[0], HImode))"
   "@
    mov_s\\t%0,%1
    mov\\t%0,%1
    mov_s\\t%0,%1
    mov\\t%0,%1
    sth%U0\\t%1,[%0]
    sth%U0\\t%1,[%0]
    ldh%U1\\t%0,[%1]
    sth%U0\\t%1,[%0]"
   [(set_attr "type" "move,move,move,move,st,st,ld,st")
    (set_attr "length" "2,4,2,8,*,8,*,*")]
)

(define_insn "*arc64_movsi"
   [(set (match_operand:SI 0 "nonimmediate_operand" "=r, r, r, m,    m")
	 (match_operand:SI 1 "general_operand"      " r, i, m, r,S06S0"))
   ]
   "register_operand (operands[0], SImode)
   || register_operand (operands[1], SImode)
   || (satisfies_constraint_S06S0 (operands[1])
       && memory_operand (operands[0], SImode))"
   "@
    mov\\t%0,%1
    mov\\t%0,%1
    ld%U1\\t%0,[%1]
    st%U0\\t%1,[%0]
    st%U0\\t%1,[%0]"
)

;; Softcore float move.
(define_insn "*arc64_movsf"
   [(set (match_operand:SF 0 "nonimmediate_operand" "=r, r, r, m")
	 (match_operand:SF 1 "general_operand"      " r, E, m, r"))
   ]
   "register_operand (operands[0], SFmode)
   || register_operand (operands[1], SFmode)"
   "@
    mov\\t%0,%1
    mov\\t%0,%1
    ld%U1\\t%0,[%1]
    st%U0\\t%1,[%0]"
   )

(define_insn "*arc64_push"
  [(set (mem:DI (pre_dec (reg:DI SP_REGNUM)))
	(                 match_operand:DI 0 "register_operand" "qr"))]
   ""
   "pushl_s\\t%0"
   [(set_attr "type" "st")
    (set_attr "length" "2")])

(define_insn "*arc64_pop"
  [(set (                  match_operand:DI 0 "register_operand" "=qr")
	(mem:DI (post_inc (reg:DI SP_REGNUM))))]
  ""
  "popl_s\\t%0"
  [(set_attr "type" "ld")
   (set_attr "length" "2")])

;;
;; Short insns: movl_s g,h; movl_s b,u8
;; Long insns: movl, stl, ldl
;;
(define_insn "*arc64_movdi"
   [(set (match_operand:DI 0 "nonimmediate_operand" "=qh,    q,r,    r,    r,r, m")
	 (match_operand:DI 1 "arc64_movl_operand"    "qh,U08S0,r,S12S0,S32S0,m, r"))]
   "register_operand (operands[0], DImode)
    || register_operand (operands[1], DImode)"
   "@
    movl_s\\t%0,%1
    movl_s\\t%0,%1
    movl\\t%0,%1
    movl\\t%0,%1
    movl\\t%0,%1
    ldl%U1\\t%0,[%1]
    stl%U0\\t%1,[%0]"
   [(set_attr "type" "move,move,move,move,move,ld,st")
    (set_attr "length" "2,2,4,4,8,*,*")]
)

;; Hi/Low moves for constant and symbol loading.

(define_insn "*movdi_high"
  [(set (match_operand:DI 0 "register_operand"   "=   r,   qh,    r")
	(high:DI
	 (match_operand:DI 1 "immediate_operand" "S12S0,S32S0,S32S0")))]
  ""
  "@
   movhl\\t%0,%h1
   movhl_s\\t%0,%h1
   movhl\\t%0,%h1"
  [(set_attr "type" "move")
   (set_attr "length" "4,6,8")])

(define_insn "*movdi_lo_sum_iori"
  [(set (match_operand:DI 0 "register_operand"                "=q,    r,   qh,    r")
	(lo_sum:DI (match_operand:DI 1 "register_operand"      "0,    r,    0,    r")
		   (match_operand:DI 2 "immediate_operand" "U08S0,S12S0,S32S0,S32S0")))]
  ""
  "@
   movl_s\\t%0,%L2
   orl\\t%0,%1,%L2
   movl_s\\t%0,%L2
   orl\\t%0,%1,%L2"
  [(set_attr "type" "move,or,move,or")
   (set_attr "length" "2,4,6,8")])

;(define_insn "*arc64_movqi"
;  [(set (match_operand:QI 0 "nonimmediate_operand" "=q,   qh,  r,h,w,q,  r,r,   m,Usc")
;	(match_operand:QI 1 "arc64_mov_operand"     " P,qhCm1,rLI,i,i,T,Ucm,m,rCm3,i"))]
;  "register_operand (operands[0], QImode)
;   || register_operand (operands[1], QImode)
;   || (satisfies_constraint_Cm3 (operands[1])
;       && memory_operand (operands[0], QImode))"
;  "@
;   mov%?\\t%0,%1
;   mov%?\\t%0,%1
;   mov%?\\t%0,%1
;   mov%?\\t%0,%1
;   mov%?\\t%0,%1
;   ldb%?\\t%0,%1
;   ldb%U1%V1\\t%0,%1
;   stb%U0%V0\\t%1,%0
;   stb%U0%V0\\t%1,%0"
;  [(set_attr "type"       "move,move, move, move,      move,load, load,store,store")
;   (set_attr "iscompact"  "true,true,false,false,maybe_limm,true,false,false,false")])
;

;(define_insn "*movhi_arc64"
;  [(set (match_operand:HI 0 "move_dest_operand" "=q,   qh,  r,q,h, r,  q,r,   m,VUsc")
;	(match_operand:HI 1 "move_src_operand" "  P,qhCm1,rLI,i,i, i,  T,m,rCm3,i"))]
;  "register_operand (operands[0], HImode)
;   || register_operand (operands[1], HImode)
;   || (satisfies_constraint_Cm3 (operands[1])
;       && memory_operand (operands[0], HImode))"
;  "@
;   mov%?\\t%0,%1
;   mov%?\\t%0,%1
;   mov%?\\t%0,%1
;   mov%?\\t%0,%1
;   mov%?\\t%0,%1
;   mov%?\\t%0,%1
;   ldh%?\\t%0,%1%&
;   ldh%U1%V1\\t%0,%1
;   sth%U0%V0\\t%1,%0
;   sth%U0%V0\\t%1,%0"
;  [(set_attr "type"      "move,move, move,      move,      move, move,load, load,store,store")
;   (set_attr "iscompact" "true,true,false,maybe_limm,maybe_limm,false,true,false,false,false")])


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
  [(call (mem:DI (match_operand:DI 0 "arc64_call_insn_operand" "q,r,BLsym"))
	 (match_operand 1 "" ""))
   (clobber (reg:DI BLINK_REGNUM))]
  ""
  "@
   jl_s\\t[%0]
   jl\\t[%0]
   bl\\t%c0"
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
	(call (mem:DI (match_operand:DI 1 "arc64_call_insn_operand"
					"q,r,BLsym"))
	      (match_operand 2 "" "")))
   (clobber (reg:DI BLINK_REGNUM))]
  ""
  "@
   jl_s\\t[%1]
   jl\\t[%1]
   bl\\t%c1"
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
  )

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
 [(call (mem:DI (match_operand:DI 0 "arc64_call_insn_operand" "Sbreg,BLsym"))
	(match_operand 1 "" ""))
  (return)]
  "SIBLING_CALL_P (insn)"
  "@
   j\\t[%0]
   b\\t%c0"
  [(set_attr "type" "jump,branch")
   (set_attr "predicable" "yes,yes")
   (set_attr "iscompact" "maybe,no")]
)

(define_insn "*sibcall_value_insn"
 [(set (match_operand 0 "" "")
       (call (mem:DI (match_operand:DI 1 "arc64_call_insn_operand" "Sbreg,BLsym"))
	     (match_operand 2 "" "")))
  (return)]
  "SIBLING_CALL_P (insn)"
  "@
   j\\t[%1]
   b\\t%c1"
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
  "j%?\\t[%0]"
  [(set_attr "type" "jump")
   (set_attr "length" "2,4")]
)

(define_insn "jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  ""
  "b%?\\t%l0"
  [(set_attr "type" "branch")
   (set (attr "length")
	(if_then_else
	 (and (ge (minus (match_dup 0) (pc)) (const_int -512))
	      (le (minus (match_dup 0) (pc)) (const_int 506)))
	 (const_int 2)
	 (const_int 4)))]
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
  "b%m0%?\\t%l2"
  [(set_attr "type" "branchcc")
   (set_attr "iscompact" "maybe")
   (set (attr "length")
	(cond
	  [(and (match_operand 1 "equality_comparison_operator" "")
		(and (ge (minus (match_dup 2) (pc)) (const_int -512))
		     (le (minus (match_dup 2) (pc)) (const_int 506))))
	   (const_int 2)

	   (and (ge (minus (match_dup 2) (pc)) (const_int -62))
		(le (minus (match_dup 2) (pc)) (const_int 60)))
	   (const_int 2)]
	  (const_int 4)))])

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
  "arc64_can_use_return_insn_p ()"
  "")

(define_insn "simple_return"
  [(simple_return)]
  ""
  "j_s\\t[blink]"
  [(set_attr "type" "return")
   (set_attr "iscompact" "maybe")
   (set_attr "length" "*")])

(define_insn "nop"
  [(const_int 0)]
  ""
  "nop_s"
  [(set_attr "type" "nop")
   (set_attr "length" "2")])

(define_insn "blockage"
  [(unspec_volatile [(const_int 0)] VUNSPEC_ARC_BLOCKAGE)]
  ""
  ""
  [(set_attr "length" "0")
   (set_attr "type" "block")]
)
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

(define_insn "*arc64_zero_extend_<mode>_to_si"
   [(set (match_operand:SI 0 "register_operand"      "=q,r,r")
	 (zero_extend:SI
	  (match_operand:SHORT 1 "nonimmediate_operand"  "q,r,m")))]
   ""
   "@
   ext<exttab>_s\\t%0,%1
   ext<exttab>\\t%0,%1
   ld<sfxtab>%U1\\t%0,[%1]"
  [(set_attr "type" "sex,sex,ld")
   (set_attr "length" "2,4,*")])

(define_insn "*arc64_zero_extend_si_to_di"
   [(set (match_operand:DI 0 "register_operand"       "=r,r")
	 (zero_extend:DI
	  (match_operand:SI 1 "nonimmediate_operand"   "r,m")))
   ]
   ""
   "@
   bmskl\\t%0,%1,31
   ld%U1\\t%0,[%1]"
  [(set_attr "type" "and,ld")
   (set_attr "length" "4,*")]
)

(define_insn "*arc64_zero_extend_qi_to_di"
   [(set (match_operand:DI 0 "register_operand"       "=r,r")
	 (zero_extend:DI
	  (match_operand:QI 1 "nonimmediate_operand"   "r,m")))
   ]
   ""
   "@
   bmskl\\t%0,%1,7
   ldb%U1\\t%0,[%1]"
  [(set_attr "type" "and,ld")
   (set_attr "length" "4,*")]
)

(define_insn "*arc64_zero_extend_hi_to_di"
   [(set (match_operand:DI 0 "register_operand"       "=r,r")
	 (zero_extend:DI
	  (match_operand:HI 1 "nonimmediate_operand"   "r,m")))
   ]
   ""
   "@
   bmskl\\t%0,%1,15
   ldh%U1\\t%0,[%1]"
  [(set_attr "type" "and,ld")
   (set_attr "length" "4,*")]
)

(define_insn "*arc64_sign_extend_<mode>_to_di"
  [(set (match_operand:DI 0 "register_operand"       "=r,r")
	(sign_extend:DI
	 (match_operand:EXT 1 "nonimmediate_operand"  "r,m")))
   ]
   ""
   "@
   sex<exttab>l\\t%1,%0
   ld<sfxtab>.x%U1\\t%0,[%1]"
  [(set_attr "type" "sex,ld")
   (set_attr "length" "4,*")]
)

(define_insn "*sign_extend<mode>si2"
  [(set (match_operand:SI 0 "register_operand" "=q,r,r")
	(sign_extend:SI
	 (match_operand:SHORT 1 "nonimmediate_operand" "q,r,m")))]
  ""
  "@
  sex<exttab>_s\\t%0,%1
  sex<exttab>\\t%0,%1
  ld<sfxtab>.x%U1\\t%0,[%1]"
  [(set_attr "type" "sex,sex,ld")
   (set_attr "length" "2,4,8")])

;; -------------------------------------------------------------------
;; Simple arithmetic
;; -------------------------------------------------------------------

(define_expand "<optab><mode>3"
  [(set (match_operand:GPI 0 "register_operand")
	(ARITH:GPI (match_operand:GPI 1 "register_operand")
		   (match_operand:GPI 2 "nonmemory_operand")))]
  ""
  )

;;(define_expand "addv<mode>4"
;;  [(match_operand:GPI 0 "register_operand")
;;   (match_operand:GPI 1 "register_operand")
;;   (match_operand:GPI 2 "nonmemory_operand")
;;   (label_ref (match_operand 3 "" ""))]
;;  ""
;;  )
;;
;;(define_expand "uaddv<mode>4"
;;  [(match_operand:GPI 0 "register_operand")
;;   (match_operand:GPI 1 "register_operand")
;;   (match_operand:GPI 2 "register_operand")
;;   (label_ref (match_operand 3 "" ""))]
;;  ""
;;)
;;
;;(define_expand "subv<GPI:mode>4"
;;  [(match_operand:GPI 0 "register_operand")
;;   (match_operand:GPI 1 "register_operand")
;;   (match_operand:GPI 2 "nonmemory_operand")
;;   (label_ref (match_operand 3 "" ""))]
;;  ""
;;  )
;;
;;(define_expand "negv<GPI:mode>3"
;;  [(match_operand:GPI 0 "register_operand")
;;   (match_operand:GPI 1 "register_operand")
;;   (label_ref (match_operand 2 "" ""))]
;;  ""
;;  )
;;
;;(define_expand "usubv<mode>4"
;;  [(match_operand:GPI 0 "register_operand")
;;   (match_operand:GPI 1 "nonmemory_operand")
;;   (match_operand:GPI 2 "nonmemory_operand")
;;   (label_ref (match_operand 3 "" ""))]
;;  ""
;;  )

;; -------------------------------------------------------------------
;; Comparison insns
;; -------------------------------------------------------------------

(define_insn "cmp<mode>"
  [(set (reg:CC CC_REGNUM)
	(compare:CC (match_operand:GPI 0 "nonmemory_operand" "r,    r,    r,U06S0,S12S0,i,r")
		    (match_operand:GPI 1 "nonmemory_operand" "r,U06S0,S12S0,    r,    r,r,i")))]
  "register_operand (operands[0], <MODE>mode)
   || register_operand (operands[1], <MODE>mode)"
  "@
   cmp<sfxtab>%?\\t%0,%1
   cmp<sfxtab>%?\\t%0,%1
   cmp<sfxtab>%?\\t%0,%1
   rcmp<sfxtab>%?\\t%1,%0
   rcmp<sfxtab>%?\\t%1,%0
   rcmp<sfxtab>%?\\t%1,%0
   cmp<sfxtab>%?\\t%0,%1"
  [(set_attr "type" "compare")
   (set_attr "iscompact" "no")
   (set_attr "predicable" "yes,yes,no,yes,no,no,no")
   (set_attr "length" "*,*,*,*,*,8,8")])


;; -------------------------------------------------------------------
;; Store-flag and conditional select insns
;; -------------------------------------------------------------------

(define_expand "cstore<mode>4"
  [(set (match_operand:SI 0 "register_operand")
	(match_operator:SI 1 "comparison_operator"
	 [(match_operand:GPI 2 "nonmemory_operand")
	  (match_operand:GPI 3 "nonmemory_operand")]))]
  ""
  {
   if (!register_operand (operands[2], <MODE>mode))
      operands[2] = force_reg (<MODE>mode, operands[2]);
   })

;; SETcc instructions
(define_insn "set<cctab><mode>"
  [(set (match_operand:SI 0 "register_operand"            "=r,r,    r,    r,    r,r,r")
	(SETCC:SI (match_operand:GPI 1 "register_operand"  "0,r,    0,    r,    0,0,r")
		  (match_operand:GPI 2 "nonmemory_operand" "r,r,U06S0,U06S0,S12S0,n,n")))]
  ""
  "set<cctab><sfxtab>%?\\t%0,%1,%2"
  [(set_attr "length" "4,4,4,4,4,8,8")
   (set_attr "type" "setcc")
   (set_attr "predicable" "yes,no,yes,no,no,yes,no")])

;; Special cases of SETCC
(define_insn_and_split "*sethi<mode>"
  [(set (match_operand:SI 0 "register_operand"          "=r,r,    r,r")
	(gtu:SI (match_operand:GPI 1 "register_operand"  "r,r,    r,r")
		(match_operand:GPI 2 "nonmemory_operand" "0,r,U06M1,n")))]
  ""
  "setlo<sfxtab>%?\\t%0,%2,%1"
  "reload_completed
   && CONST_INT_P (operands[2])
   && satisfies_constraint_U06M1 (operands[2])"
  [(const_int 0)]
  "{
    /* sethi a,b,u6 => seths a,b,u6 + 1.  */
    operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
    emit_insn (gen_seths<mode> (operands[0], operands[1], operands[2]));
    DONE;
   }"
 [(set_attr "length" "4,4,4,8")
   (set_attr "type" "setcc")
   (set_attr "predicable" "yes,no,no,no")])

(define_insn_and_split "*setls<mode>"
  [(set (match_operand:SI 0 "register_operand"          "=r,r,    r,r")
	(leu:SI (match_operand:GPI 1 "register_operand"  "r,r,    r,r")
		(match_operand:GPI 2 "nonmemory_operand" "0,r,U06M1,n")))]
  ""
  "seths<sfxtab>%?\\t%0,%2,%1"
  "reload_completed
   && satisfies_constraint_U06M1 (operands[2])"
  [(const_int 0)]
  "{
    /* setls a,b,u6 => setlo a,b,u6 + 1.  */
    operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
    emit_insn (gen_setlo<mode> (operands[0], operands[1], operands[2]));
    DONE;
   }"
  [(set_attr "length" "4,4,4,8")
   (set_attr "type" "setcc")
   (set_attr "predicable" "yes,no,no,no")])


;;(define_expand "mov<mode>cc"
;;  [(set (match_operand:ALLI 0 "register_operand")
;;	(if_then_else:ALLI (match_operator 1 "comparison_operator")
;;			   (match_operand:ALLI 2 "register_operand")
;;			   (match_operand:ALLI 3 "register_operand")))]
;;  ""
;;  )

;; -------------------------------------------------------------------
;; Logical operations
;; -------------------------------------------------------------------

(define_expand "<optab><mode>3"
  [(set (match_operand:GPI 0 "register_operand")
	(LOGIC:GPI (match_operand:GPI 1 "register_operand")
		   (match_operand:GPI 2 "nonmemory_operand")))]
  ""
  )

(define_expand "<optab><mode>2"
  [(set (match_operand:GPI 0 "register_operand")
	(LOGIC2:GPI (match_operand:GPI 1 "register_operand")))]
  ""
  )

(define_insn "negsi2"
  [(set (match_operand:SI 0 "register_operand"        "=q,q,r,r")
	(neg:SI (match_operand:SI 1 "register_operand" "0,q,0,r")))]
  ""
  "neg%?\\t%0,%1"
  [(set_attr "type" "neg")
   (set_attr "iscompact" "maybe,yes,no,no")
   (set_attr "predicable" "no,no,yes,no")])

;FIXME;(define_insn "*<optab>2_short"
;FIXME;  [(set (match_operand:SI 0 "compact_register_operand" "=q")
;FIXME;	(LOGIC2:SI (match_operand:SI 1 "compact_register_operand" "q")))]
;FIXME;  ""
;FIXME;  "<cctab>_s\\t%0,%1"
;FIXME;  [(set_attr "type" "<cctab>")
;FIXME;   (set_attr "length" "2")])

(define_insn "*<optab><mode>2"
  [(set (match_operand:GPI 0 "register_operand" "=r")
	(LOGIC2:GPI (match_operand:GPI 1 "register_operand" "r")))]
  ""
  "<cctab><sfxtab>%?\\t%0,%1"
  [(set_attr "type" "<cctab>")
   (set_attr "length" "4")])

(define_insn "*smax<mode>3"
   [(set (match_operand:GPI 0 "register_operand"                "=r,     r,r")
	 (smax:GPI (match_operand:GPI 1 "register_operand"      "%0,     r,r")
		   (match_operand:GPI 2 "nonmemory_operand" "rU06S0,rU06S0,i")))]
  ""
  "max<sfxtab>%?\\t%0,%1,%2"
  [(set_attr "type" "max")
   (set_attr "length" "4,4,8")
   (set_attr "predicable" "yes,no,no")]
)

(define_insn "*smin<mode>3"
   [(set (match_operand:GPI 0 "register_operand"                "=r,     r,r")
	 (smin:GPI (match_operand:GPI 1 "register_operand"      "%0,     r,r")
		   (match_operand:GPI 2 "nonmemory_operand" "rU06S0,rU06S0,i")))]
  ""
  "min<sfxtab>%?\\t%0,%1,%2"
  [(set_attr "type" "min")
   (set_attr "length" "4,4,8")
   (set_attr "predicable" "yes,no,no")]
)

;; -------------------------------------------------------------------
;; Shifts
;; -------------------------------------------------------------------

;; FIXME! check if we get better code if we use QI for op 2.
(define_expand "<optab><mode>3"
  [(set (match_operand:GPI 0 "register_operand")
	(ASHIFT:GPI (match_operand:GPI 1 "register_operand")
		    (match_operand:GPI 2 "nonmemory_operand")))]
  ""
)

;(define_expand "ashl<mode>3"
;  [(set (match_operand:SHORT 0 "register_operand")
;	(ashift:SHORT (match_operand:SHORT 1 "register_operand")
;		      (match_operand:QI 2 "const_int_operand")))]
;  ""
;)

(define_expand "rotrsi3"
  [(set (match_operand:SI 0 "register_operand")
	(rotatert:SI (match_operand:SI 1 "nonmemory_operand")
		     (match_operand:SI 2 "nonmemory_operand")))]
  ""
)

(define_insn "*rotrsi3"
  [(set (match_operand:SI 0 "register_operand"                   "=r,     r,r")
	(rotatert:SI (match_operand:SI 1 "nonmemory_operand"      "0,     r,i")
		     (match_operand:SI 2 "nonmemory_operand" "rU06S0,rU06S0,r")))]
  ;; FIXME! this needs BARREL_SHIFTER option
  "register_operand (operands[0], SImode)
   || register_operand (operands[1], SImode)"
  "ror%?\\t%0,%1,%2"
  [(set_attr "type" "ror")
   (set_attr "predicable" "yes,no,no")
   (set_attr "length" "4,4,8")])

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


(include "arith.md")
;;(include "generate/logic.md")

;; mode:emacs-lisp
;; comment-start: ";; "
;; eval: (set-syntax-table (copy-sequence (syntax-table)))
;; eval: (modify-syntax-entry ?[ "(]")
;; eval: (modify-syntax-entry ?] ")[")
;; eval: (modify-syntax-entry ?{ "(}")
;; eval: (modify-syntax-entry ?} "){")
;; eval: (setq indent-tabs-mode t)
;; End:
