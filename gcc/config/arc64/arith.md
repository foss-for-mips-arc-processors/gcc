;; -------------------------------------------------------------------
;; Code Attributes
;; -------------------------------------------------------------------
;; Map rtl objects to arc instuction names
(define_code_attr arc64_code_map [(ashift   "asl")
				  (ashiftrt "asr")
				  (sign_extend "sex")
				  (zero_extend "ext")
				  (div      "div")
				  (udiv     "divu")
				  (mod      "rem")
				  (umod     "remu")
				  (lshiftrt "lsr")
				  (and      "and")
				  (ior      "or")
				  (xor      "xor")
				  (plus     "add")
				  (minus    "sub")])

(define_code_iterator COMMUTATIVE [and ior xor] )

(define_code_iterator BIT [ior xor] )

(define_code_iterator DIVREM [div udiv mod umod] )

(define_code_attr bit_optab [(plus   "adc")
			     (minus  "sbc")
			     (ior    "bset")
			     (xor    "bxor")
			     ])

(define_code_iterator ADDSUB [plus minus] )

;; SI instructions having short instruction variant
(define_insn "*<optab><mode>_insn"
  [(set (                match_operand:GPI 0 "register_operand"  "=q,q,     r,    r,     r,    r,    r,    r,r")
	(COMMUTATIVE:GPI (match_operand:GPI 1 "nonmemory_operand" "%0,q,     0,    0,     r,U06S0,S12S0,S32S0,r")
			 (match_operand:GPI 2 "nonmemory_operand" " q,0,rU06S0,S12S0,rU06S0,    r,    0,    r,S32S0")))]
  "register_operand (operands[1], <MODE>mode)
   || register_operand (operands[2], <MODE>mode)"
  "@
   <arc64_code_map><sfxtab>%?\\t%0,%1,%2
   <arc64_code_map><sfxtab>%?\\t%0,%2,%1
   <arc64_code_map><sfxtab>%?\\t%0,%1,%2
   <arc64_code_map><sfxtab>%?\\t%0,%1,%2
   <arc64_code_map><sfxtab>%?\\t%0,%1,%2
   <arc64_code_map><sfxtab>%?\\t%0,%2,%1
   <arc64_code_map><sfxtab>%?\\t%0,%2,%1
   <arc64_code_map><sfxtab>%?\\t%0,%1,%2
   <arc64_code_map><sfxtab>%?\\t%0,%1,%2"
  [(set_attr "iscompact" "maybe,maybe,no,no,no,no,no,no,no")
   (set_attr "predicable" "no,no,yes,no,no,no,no,no,no")
   (set_attr "length"     "*,*,4,4,4,4,4,8,8")
   (set_attr "type"       "<arc64_code_map>")]
  )

(define_insn "*<optab><mode>_insn"
  [(set (            match_operand:GPI 0 "register_operand"  "=q,     r,    r,    r,    r,r")
	(ASHIFT:GPI (match_operand:GPI 1 "nonmemory_operand" " 0,     0,    0,    r,S32S0,r")
		    (match_operand:GPI 2 "nonmemory_operand" " q,rU06S0,S12S0,rU06S0,   r,S32S0")))]
  "register_operand (operands[1], <MODE>mode)
   || register_operand (operands[2], <MODE>mode)"
  "<arc64_code_map><sfxtab>%?\\t%0,%1,%2"
  [(set_attr "iscompact" "maybe,no,no,no,no,no")
   (set_attr "predicable" "no,yes,no,no,no,no")
   (set_attr "length"     "*,4,4,4,8,8")
   (set_attr "type"       "<arc64_code_map>")]
  )

(define_insn "*sub<mode>_insn"
  [(set (           match_operand:GPI 0 "register_operand"  "=q,    q,    q,     r,     r,    r,     r,    r,    r,    r,r")
	(minus:GPI (match_operand:GPI 1 "nonmemory_operand" " 0,    0,    q,     0,rU06S0,    0,     r,U06S0,S12S0,S32S0,r")
		   (match_operand:GPI 2 "nonmemory_operand" " q,U05S0,U03S0,rU06S0,     0,S12S0,rU06S0,    r,    0,    r,S32S0")))]
  "register_operand (operands[1], <MODE>mode)
   || register_operand (operands[2], <MODE>mode)"
  "@
   sub<sfxtab>%?\\t%0,%1,%2
   sub<sfxtab>%?\\t%0,%1,%2
   sub<sfxtab>%?\\t%0,%1,%2
   sub<sfxtab>%?\\t%0,%1,%2
   rsub<sfxtab>%?\\t%0,%2,%1
   sub<sfxtab>%?\\t%0,%1,%2
   sub<sfxtab>%?\\t%0,%1,%2
   rsub<sfxtab>%?\\t%0,%2,%1
   rsub<sfxtab>%?\\t%0,%2,%1
   sub<sfxtab>%?\\t%0,%1,%2
   sub<sfxtab>%?\\t%0,%1,%2"
  [(set_attr "iscompact"  "yes,maybe,maybe,no,no,no,no,no,no,no,no")
   (set_attr "predicable" "no,yes,no,yes,yes,no,no,no,no,no,no")
   (set_attr "length"     "2,*,*,4,4,4,4,4,4,8,8")
   (set_attr "type"       "sub")]
  )

(define_insn "*add<mode>_insn"
  [(set (          match_operand:GPI 0 "register_operand"  "=q, q,q,    q,    q,     r,    r,     r,r")
	(plus:GPI (match_operand:GPI 1 "register_operand"  "%0, 0,q,    0,    q,     0,    0,     r,r")
		  (match_operand:GPI 2 "nonmemory_operand" " q,qh,q,U07S0,U03S0,rU06S0,S12S0,rU06S0,S32S0")))]
  "register_operand (operands[1], <MODE>mode)
   || register_operand (operands[2], <MODE>mode)"
  "add<sfxtab>%?\\t%0,%1,%2"
  [(set_attr "iscompact"  "yes,maybe,maybe,maybe,maybe,no,no,no,no")
   (set_attr "predicable" "no,no,no,no,no,yes,no,no,no")
   (set_attr "length"     "2,*,*,*,*,4,4,4,8")
   (set_attr "type"       "add")]
  )

;; Arithmetic patterns used by the combiner.
(define_insn "*bic<mode>3"
  [(set (                  match_operand:GPI 0 "register_operand"  "=q,r,r,    r")
	(and:GPI (not:GPI (match_operand:GPI 1 "register_operand"   "q,r,r,    r"))
		 (         match_operand:GPI 2 "nonmemory_operand"  "0,0,r,S32S0")))]
  ""
  "bic<sfxtab>%?\\t%0,%2,%1"
  [(set_attr "iscompact" "maybe,no,no,no")
   (set_attr "predicable" "no,yes,no,no")
   (set_attr "length"     "*,4,4,8")
   (set_attr "type"       "bic")])

(define_insn "*bic<mode>3_cmp0"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (and:GPI
	  (not:GPI (match_operand:GPI 1 "register_operand"   "r,r,    r"))
	  (match_operand:GPI 2 "nonmemory_operand"  "0,r,S32S0"))
	 (const_int 0)))
   (set (match_operand:GPI 0 "register_operand"  "=r,r,r")
	(and:GPI (not:GPI (match_dup 1)) (match_dup 2)))]
  ""
  "bic<sfxtab>%?.f\\t%0,%2,%1"
  [(set_attr "iscompact" "no,no,no")
   (set_attr "predicable" "yes,no,no")
   (set_attr "length"     "4,4,8")
   (set_attr "type"       "bic")])

(define_insn "*bic<mode>3_cmp0_noout"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (and:GPI
	  (not:GPI (match_operand:GPI 0 "register_operand"   "r,r"))
	  (match_operand:GPI 1 "nonmemory_operand"  "r,S32S0"))
	 (const_int 0)))]
  ""
  "bic<sfxtab>.f\\t0,%1,%0"
  [(set_attr "iscompact"  "no,no")
   (set_attr "predicable" "no,no")
   (set_attr "length"     "4,8")
   (set_attr "type"       "bic")])

(define_insn "*<bit_optab><mode>3"
  [(set (match_operand:GPI 0 "register_operand" "=r,r,r")
	(BIT:GPI
	 (ashift:GPI
	  (const_int 1)
	  (match_operand:GPI 1 "register_operand" "r,r,r"))
	 (match_operand:GPI 2 "nonmemory_operand" "0,r,S32S0")))]
  ""
  "<bit_optab><sfxtab>%?\\t%0,%2,%1"
  [(set_attr "type" "<bit_optab>")
   (set_attr "iscompact" "no")
   (set_attr "length" "4,4,8")
   (set_attr "predicable" "yes,no,no")])

(define_insn "*bset<mode>3_cmp0"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (BIT:GPI
	  (ashift:GPI
	   (const_int 1)
	   (match_operand:GPI 1 "register_operand" "r,r,r"))
	  (match_operand:GPI 2 "nonmemory_operand" "0,r,S32S0"))
	 (const_int 0)))
   (set (match_operand:GPI 0 "register_operand" "=r,r,r")
	(BIT:GPI
	 (ashift:GPI
	  (const_int 1)
	  (match_dup 1))
	 (match_dup 2)))]
  ""
  "<bit_optab><sfxtab>%?.f\\t%0,%2,%1"
  [(set_attr "type" "<bit_optab>")
   (set_attr "iscompact" "no")
   (set_attr "length" "4,4,8")
   (set_attr "predicable" "yes,no,no")])

(define_insn "*bset<mode>3_cmp0_noout"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (BIT:GPI
	  (ashift:GPI
	   (const_int 1)
	   (match_operand:GPI 0 "register_operand" "r,r"))
	  (match_operand:GPI 1 "nonmemory_operand" "r,S32S0"))
	 (const_int 0)))]
  ""
  "<bit_optab><sfxtab>.f\\t0,%1,%0"
  [(set_attr "type" "<bit_optab>")
   (set_attr "iscompact" "no")
   (set_attr "length" "4,8")
   (set_attr "predicable" "no,no")])

(define_insn "*<optab><mode>_cmp0"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (COMMUTATIVE:GPI
	  (match_operand:GPI 1 "nonmemory_operand" "%     0,    0,     r,U06S0,S12S0,S32S0,r")
	  (match_operand:GPI 2 "nonmemory_operand" " rU06S0,S12S0,rU06S0,    r,    0,    r,S32S0"))
	 (const_int 0)))
   (set (match_operand:GPI 0 "register_operand"  "=     r,    r,     r,    r,    r,    r,r")
	(COMMUTATIVE:GPI (match_dup 1) (match_dup 2)))]
  "register_operand (operands[1], <MODE>mode)
   || register_operand (operands[2], <MODE>mode)"
  "@
   <arc64_code_map><sfxtab>%?.f\\t%0,%1,%2
   <arc64_code_map><sfxtab>%?.f\\t%0,%1,%2
   <arc64_code_map><sfxtab>%?.f\\t%0,%1,%2
   <arc64_code_map><sfxtab>%?.f\\t%0,%2,%1
   <arc64_code_map><sfxtab>%?.f\\t%0,%2,%1
   <arc64_code_map><sfxtab>%?.f\\t%0,%1,%2
   <arc64_code_map><sfxtab>%?.f\\t%0,%1,%2"
  [(set_attr "iscompact"  "no,no,no,no,no,no,no")
   (set_attr "predicable" "yes,no,no,no,no,no,no")
   (set_attr "length"     "4,4,4,4,4,8,8")
   (set_attr "type"       "<arc64_code_map>")]
  )

(define_insn "*<optab><mode>_cmp0_noout"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (COMMUTATIVE:GPI
	  (match_operand:GPI 0 "nonmemory_operand" "%     r,U06S0,S32S0,r")
	  (match_operand:GPI 1 "nonmemory_operand" " rU06S0,    r,    r,S32S0"))
	 (const_int 0)))]
  "register_operand (operands[0], <MODE>mode)
   || register_operand (operands[1], <MODE>mode)"
  "@
   <arc64_code_map><sfxtab>.f\\t0,%0,%1
   <arc64_code_map><sfxtab>.f\\t0,%1,%0
   <arc64_code_map><sfxtab>.f\\t0,%0,%1
   <arc64_code_map><sfxtab>.f\\t0,%0,%1"
  [(set_attr "iscompact"  "no")
   (set_attr "predicable" "no")
   (set_attr "length"     "4,4,8,8")
   (set_attr "type"       "<arc64_code_map>")]
  )

(define_insn "*<ANY_EXTEND:optab><SHORT:mode>si2_cmp0_noout"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (ANY_EXTEND:SI (match_operand:SHORT 0 "register_operand" "r"))
	 (const_int 0)))]
  ""
  "<ANY_EXTEND:arc64_code_map><SHORT:exttab>.f\\t0,%0"
  [(set_attr "type" "<ANY_EXTEND:arc64_code_map>")
   (set_attr "length" "4")])

(define_insn "*extend<EXT:mode>di2_cmp0_noout"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (sign_extend:DI (match_operand:EXT 0 "register_operand" "r"))
	 (const_int 0)))]
  ""
  "sex<EXT:exttab>l.f\\t0,%0"
  [(set_attr "type" "sex")
   (set_attr "length" "4")])

(define_insn "*<ANY_EXTEND:optab><SHORT:mode>si_cmp0"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (ANY_EXTEND:SI (match_operand:SHORT 1 "register_operand" "r"))
	 (const_int 0)))
   (set (match_operand:SI 0 "register_operand" "=r")
	(ANY_EXTEND:SI (match_dup 1)))]
  ""
  "<ANY_EXTEND:arc64_code_map><SHORT:exttab>.f\\t%0,%1"
  [(set_attr "type" "<ANY_EXTEND:arc64_code_map>")
   (set_attr "length" "4")])

(define_insn "*extend<EXT:mode>di_cmp0"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (sign_extend:DI (match_operand:EXT 1 "register_operand" "r"))
	 (const_int 0)))
   (set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI (match_dup 1)))]
  ""
  "sex<EXT:exttab>l.f\\t%0,%1"
  [(set_attr "type" "sex")
   (set_attr "length" "4")])

;; SI/DI DIV/REM instructions.
(define_expand "<optab><mode>3"
  [(set (match_operand:GPI 0 "register_operand")
	(DIVREM:GPI (match_operand:GPI 1 "nonmemory_operand")
		    (match_operand:GPI 2 "nonmemory_operand")))]
  "TARGET_ARC64_DIVREM"
  ""
  )

(define_insn "*<optab><mode>3"
  [(set (match_operand:GPI 0 "register_operand"                 "=r,    r,    r,    r,r,    r,    r")
	(DIVREM:GPI (match_operand:GPI 1 "arc64_nonmem_operand" " 0,    0,    0,    r,r,S32S0,    r")
		    (match_operand:GPI 2 "arc64_nonmem_operand" " r,U06S0,S12S0,U06S0,r,    r,S32S0")))]
  "TARGET_ARC64_DIVREM
   && (register_operand (operands[1], <MODE>mode)
       || register_operand (operands[2], <MODE>mode))"
  "<arc64_code_map><sfxtab>%?\\t%0,%1,%2"
  [(set_attr "predicable" "yes,yes,no,no,no,no,no")
   (set_attr "length"     "4,4,4,4,4,8,8")
   (set_attr "type"       "<optab><sfxtab>")]
  )

;; To be merged into adddi3
(define_insn "*add_tls_off"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(plus:DI (match_operand:DI 1 "register_operand" "r")
		 (unspec:DI [(match_operand 2 "" "")]
			    ARC64_UNSPEC_TLS_OFF)))]
  ""
  "addl\\t%0,%1,%2@tpoff"
  [(set_attr "type" "addl")
   (set_attr "length" "8")]
  )

(define_insn "<optab>di3_cmp"
  [(set (match_operand:DI 0 "register_operand"     "=r,    r,    r,    r,r,    r,    r")
	(ADDSUB:DI (match_operand:DI 1 "arc64_nonmem_operand" " 0,    0,    0,    r,r,S32S0,    r")
		   (match_operand:DI 2 "arc64_nonmem_operand" " r,U06S0,S12S0,U06S0,r,    r,S32S0")))
   (set (reg:CC_C CC_REGNUM)
	(compare:CC_C (ADDSUB:DI (match_dup 1)
				 (match_dup 2))
		      (match_dup 2)))]

  "register_operand (operands[1], DImode) || register_operand (operands[2], DImode)"
  "<optab>l.f\\t%0,%1,%2"
  [(set_attr "predicable" "yes,yes,no,no,no,no,no")
   (set_attr "length"     "4,4,4,4,4,8,8")
   (set_attr "type"       "<optab>l")]
  )

(define_insn "<optab>di3_carry"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(ADDSUB:DI
	 (ADDSUB:DI (match_operand:DI 1 "register_operand" "r")
		    (match_operand:DI 2 "register_operand" "r"))
	 (ltu:DI (reg:CC_C CC_REGNUM) (const_int 0))))]
  ""
  "<bit_optab>l\\t%0,%1,%2"
  [(set_attr "type" "<bit_optab>l")
   (set_attr "length" "4")]
)

(define_expand "<optab>ti3"
  [(set (match_operand:TI 0 "register_operand")
        (ADDSUB:TI (match_operand:TI 1 "register_operand")
		   (match_operand:TI 2 "nonmemory_operand")))]
  ""
{
  rtx low_dest, op1_low, op2_low, high_dest, op1_high, op2_high;

  high_dest = gen_highpart (DImode, operands[0]);
  low_dest = gen_lowpart (DImode, operands[0]);
  op1_high = gen_highpart (DImode, operands[1]);
  op1_low = gen_lowpart (DImode, operands[1]);
  op2_high = gen_highpart_mode (DImode, TImode, operands[2]);
  op2_low = gen_lowpart (DImode, operands[2]);

  emit_insn (gen_<optab>di3_cmp (low_dest, op1_low,
                                 force_reg (DImode, op2_low)));
  emit_insn (gen_<optab>di3_carry (high_dest, op1_high,
                                   force_reg (DImode, op2_high)));

  DONE;
})

;; Shifted adds and subs
(define_insn "*addsi_shift"
  [(set (match_operand:SI 0 "register_operand" "=q,r,r,r")
	(plus:SI (ashift:SI (match_operand:SI 1 "register_operand" "q,r,r,r")
			    (match_operand:SI 2 "_1_2_3_operand" ""))
		 (match_operand:SI 3 "arc64_nonmem_operand"  "0,0,r,S32S0")))]
  ""
  "add%2%?\\t%0,%3,%1"
  [(set_attr "type" "add")
   (set_attr "length" "*,4,4,8")
   (set_attr "predicable" "yes,yes,no,no")
   (set_attr "iscompact" "maybe,no,no,no")])

(define_insn "*adddi_shift"
  [(set (match_operand:DI 0 "register_operand" "=r,r,r")
	(plus:DI (ashift:DI (match_operand:DI 1 "register_operand" "r,r,r")
			    (match_operand:DI 2 "_1_2_3_operand" ""))
		 (match_operand:DI 3 "arc64_nonmem_operand"  "0,r,S32S0")))]
  ""
  "add%2l%?\\t%0,%3,%1"
  [(set_attr "type" "add")
   (set_attr "length" "4,4,8")
   (set_attr "predicable" "yes,no,no")])

(define_insn "*add<mode>_cmp0"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (plus:GPI (ashift:GPI (match_operand:GPI 1 "register_operand" "r,r,r")
			       (match_operand:GPI 2 "_1_2_3_operand" ""))
		  (match_operand:GPI 3 "arc64_nonmem_operand"  "0,r,S32S0"))
	 (const_int 0)))
   (set (match_operand:GPI 0 "register_operand" "=r,r,r")
	(plus:GPI (ashift:GPI (match_dup 1) (match_dup 2))
		  (match_dup 3)))]
  ""
  "add%2<sfxtab>%?.f\\t%0,%3,%1"
  [(set_attr "type" "add<sfxtab>")
   (set_attr "length" "4,4,8")
   (set_attr "predicable" "yes,no,no")])

(define_insn "*add<mode>_cmp0_noout"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (plus:GPI (ashift:GPI (match_operand:GPI 0 "register_operand" "r,r,r")
			       (match_operand:GPI 1 "_1_2_3_operand" ""))
		  (match_operand:GPI 2 "arc64_nonmem_operand"  "0,r,S32S0"))
	 (const_int 0)))]
  ""
  "add%1<sfxtab>%?.f\\t0,%2,%1"
  [(set_attr "type" "add<sfxtab>")
   (set_attr "length" "4,4,8")
   (set_attr "predicable" "yes,no,no")])

(define_insn "*sub<mode>_shift"
  [(set (match_operand:GPI 0 "register_operand" "=r,r,r")
	(minus:GPI (match_operand:GPI 1 "arc64_nonmem_operand" "0,r,S32S0")
		   (ashift:GPI (match_operand:GPI 2 "register_operand" "r,r,r")
			       (match_operand:GPI 3 "_1_2_3_operand" ""))))]
  ""
  "sub%3<sfxtab>\\t%0,%1,%2"
  [(set_attr "type" "sub<sfxtab>")
   (set_attr "length" "4,4,8")
   (set_attr "predicable" "yes,no,no")])

;; Multiplications

(define_expand "<ANY_EXTEND:su_optab>mulhisi3"
  [(set (match_operand:SI 0 "register_operand")
	(mult:SI (ANY_EXTEND:SI (match_operand:HI 1 "register_operand"))
		 (ANY_EXTEND:SI (match_operand:HI 2 "nonmemory_operand"))))]
   ""
   "
    if (CONSTANT_P (operands[2]))
    {
      emit_insn (gen_<ANY_EXTEND:su_optab>mulhisi3i (operands[0], operands[1], operands[2]));
      DONE;
    }
   "
  )

(define_insn "*<ANY_EXTEND:su_optab>mulhisi3r"
  [(set (match_operand:SI 0 "register_operand"                         "=q,r,r")
	(mult:SI (ANY_EXTEND:SI (match_operand:HI 1 "register_operand" "%0,0,r"))
		 (ANY_EXTEND:SI (match_operand:HI 2 "register_operand"  "q,r,r"))))]
  ""
  "mpy<ANY_EXTEND:su_optab>w%?\\t%0,%1,%2"
  [(set_attr "length" "*,4,4")
   (set_attr "iscompact" "maybe,no,no")
   (set_attr "type" "mpy")
   (set_attr "predicable" "yes,yes,no")
   ])

(define_insn "<ANY_EXTEND:su_optab>mulhisi3i"
  [(set (match_operand:SI 0 "register_operand"              "=r,    r,    r,r,r")
	(mult:SI (ANY_EXTEND:SI
		  (match_operand:HI 1 "register_operand"    "%0,    r,    0,0,r"))
		 (match_operand:HI 2 "immediate_operand" "U06S0,U06S0,S12S0,i,i")))]
  ""
  "mpy<ANY_EXTEND:su_optab>w%?\\t%0,%1,%2"
  [(set_attr "length" "4,4,4,8,8")
   (set_attr "type" "mpy")
   (set_attr "predicable" "yes,no,no,yes,no")])


(define_insn "*mul<mode>3"
 [(set (match_operand:GPIM 0 "register_operand"             "=q,q,     r,     r,    r,    r,    r")
       (mult:GPIM (match_operand:GPIM 1 "register_operand"  "%0,q,     0,     r,    0,    0,    r")
		  (match_operand:GPIM 2 "nonmemory_operand"  "q,0,rU06S0,rU06S0,S12S0,S32S0,S32S0")))]
 ""
 "@
  mpy<sfxtab>%?\\t%0,%1,%2
  mpy<sfxtab>%?\\t%0,%2,%1
  mpy<sfxtab>%?\\t%0,%1,%2
  mpy<sfxtab>%?\\t%0,%1,%2
  mpy<sfxtab>%?\\t%0,%1,%2
  mpy<sfxtab>%?\\t%0,%1,%2
  mpy<sfxtab>%?\\t%0,%1,%2"
 [(set_attr "length" "*,*,4,4,4,8,8")
  (set_attr "iscompact" "maybe,maybe,no,no,no,no,no")
  (set_attr "type" "mpy<sfxtab>")
  (set_attr "predicable" "no,no,yes,no,no,yes,no")])

(define_insn "*mul<mode>3_cmp0"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (mult:GPIM
	  (match_operand:GPIM 1 "register_operand"  "%     0,     r,    0,    0,    r")
	  (match_operand:GPIM 2 "nonmemory_operand"  "rU06S0,rU06S0,S12S0,S32S0,S32S0"))
	 (const_int 0)))
   (set (match_operand:GPIM 0 "register_operand"   "=     r,     r,    r,    r,    r")
	(mult:GPIM (match_dup 1) (match_dup 2)))]
 ""
 "mpy<sfxtab>%?.f\\t%0,%1,%2"
 [(set_attr "length" "4,4,4,8,8")
  (set_attr "iscompact" "no,no,no,no,no")
  (set_attr "type" "mpy<sfxtab>")
  (set_attr "predicable" "yes,no,no,yes,no")])

(define_insn "*mul<mode>3_cmp0_noout"
  [(set (reg:CC_ZN CC_REGNUM)
	(compare:CC_ZN
	 (mult:GPIM
	  (match_operand:GPIM 0 "register_operand"  "%     r,    r,    r")
	  (match_operand:GPIM 1 "nonmemory_operand"  "rU06S0,S12S0,S32S0"))
	 (const_int 0)))]
 ""
 "mpy<sfxtab>%?.f\\t0,%0,%1"
 [(set_attr "length" "4,4,8")
  (set_attr "iscompact" "no,no,no")
  (set_attr "type" "mpy<sfxtab>")
  (set_attr "predicable" "no,no,no")])

(define_insn "<su>mulsi3_highpart"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(truncate:SI
	 (lshiftrt:DI
	  (mult:DI
	   (ANY_EXTEND:DI (match_operand:SI 1 "register_operand" "%0,r"))
	   (ANY_EXTEND:DI (match_operand:SI 2 "register_operand"  "r,r")))
	  (const_int 32))))]
  ""
  "mpym<su_optab>%?\\t%0,%1,%2"
  [(set_attr "length" "4")
   (set_attr "type" "mpy")
   (set_attr "predicable" "yes,no")])

(define_insn "<su>muldi3_highpart"
  [(set (match_operand:DI 0 "register_operand" "=r,r")
	(truncate:DI
	 (lshiftrt:TI
	  (mult:TI
	   (ANY_EXTEND:TI (match_operand:DI 1 "register_operand" "%0,r"))
	   (ANY_EXTEND:TI (match_operand:DI 2 "register_operand" "r,r")))
	  (const_int 64))))]
  "TARGET_ARC64_MPY64"
  "mpym<su_optab>l%?\\t%0,%1,%2"
  [(set_attr "type" "mpyl")
   (set_attr "length" "4")
   (set_attr "predicable" "yes,no")])

(define_expand "<su_optab>mulditi3"
  [(set (match_operand:TI 0 "register_operand")
	(mult:TI (ANY_EXTEND:TI (match_operand:DI 1 "register_operand"))
		 (ANY_EXTEND:TI (match_operand:DI 2 "register_operand"))))]
  "TARGET_ARC64_MPY64"
{
  rtx low = gen_reg_rtx (DImode);
  emit_insn (gen_muldi3 (low, operands[1], operands[2]));

  rtx high = gen_reg_rtx (DImode);
  emit_insn (gen_<su>muldi3_highpart (high, operands[1], operands[2]));

  emit_move_insn (gen_lowpart (DImode, operands[0]), low);
  emit_move_insn (gen_highpart (DImode, operands[0]), high);
  DONE;
})

(define_expand "usmulditi3"
  [(set (match_operand:TI                          0 "register_operand")
	(mult:TI (zero_extend:TI (match_operand:DI 1 "register_operand"))
		 (sign_extend:TI (match_operand:DI 2 "register_operand"))))]
  "TARGET_ARC64_MPY64"
{
  rtx low = gen_reg_rtx (DImode);
  emit_insn (gen_muldi3 (low, operands[1], operands[2]));

  rtx high = gen_reg_rtx (DImode);
  emit_insn (gen_usmuldi3_highpart (high, operands[1], operands[2]));

  emit_move_insn (gen_lowpart (DImode, operands[0]), low);
  emit_move_insn (gen_highpart (DImode, operands[0]), high);
  DONE;
})

(define_insn "usmuldi3_highpart"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(truncate:DI
	 (lshiftrt:TI
	  (mult:TI (zero_extend:TI
		    (match_operand:DI 1 "register_operand"  "r"))
		   (sign_extend:TI
		    (match_operand:DI 2 "register_operand" " r")))
	  (const_int 64))))]
  "TARGET_ARC64_MPY64"
  "mpymsul\t%0,%2,%1"
  [(set_attr "type" "mpyl")
   (set_attr "length" "4")])
