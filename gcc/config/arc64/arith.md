;; -------------------------------------------------------------------
;; Code Attributes
;; -------------------------------------------------------------------
;; Map rtl objects to arc instuction names
(define_code_attr arc64_code_map [(ashift   "asl")
                                  (ashiftrt "asr")
                                  (lshiftrt "lsr")
                                  (and      "and")
                                  (ior      "or")
                                  (xor      "xor")
                                  (plus     "add")
                                  (minus    "sub")])

(define_code_iterator arith_pattern1 [and plus ior xor minus ashift ashiftrt lshiftrt] )

(define_code_attr arc64_carry_map [(plus   "adc")
                                   (minus  "sbc")])

(define_code_iterator arith_pattern2 [plus minus] )

(define_insn "*<optab>si_insn"
    [(set (                   match_operand:SI 0 "register_operand"  "=q,r,    r,    r,    r,r,r,r")
          (arith_pattern1:SI (match_operand:SI 1 "nonmemory_operand" " 0,0,    0,    0,    r,r,i,r")
                             (match_operand:SI 2 "nonmemory_operand" " q,r,U06S0,S12S0,U06S0,r,r,i")))]
    "register_operand (operands[1], SImode) || register_operand (operands[2], SImode)"
    "<arc64_code_map>%?\\t%0,%1,%2"
    [(set_attr "predicable" "no,yes,yes,no,no,no,no,no")
     (set_attr "length"     "2,4,4,4,4,4,8,8")
     (set_attr "type"       "<arc64_code_map>")]
)

(define_insn "*<optab>di_insn"
    [(set (                   match_operand:DI 0 "register_operand"     "=r,    r,    r,    r,r,    r,    r")
          (arith_pattern1:DI (match_operand:DI 1 "arc64_nonmem_operand" " 0,    0,    0,    r,r,S32S0,    r")
                             (match_operand:DI 2 "arc64_nonmem_operand" " r,U06S0,S12S0,U06S0,r,    r,S32S0")))]
    "register_operand (operands[1], DImode) || register_operand (operands[2], DImode)"
    "<arc64_code_map>l\\t%0,%1,%2"
    [(set_attr "predicable" "yes,yes,no,no,no,no,no")
     (set_attr "length"     "4,4,4,4,4,8,8")
     (set_attr "type"       "<arc64_code_map>")]
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
          (arith_pattern2:DI (match_operand:DI 1 "arc64_nonmem_operand" " 0,    0,    0,    r,r,S32S0,    r")
                   (match_operand:DI 2 "arc64_nonmem_operand" " r,U06S0,S12S0,U06S0,r,    r,S32S0")))
     (set (reg:CC_C CC_REGNUM)
	(compare:CC_C (arith_pattern2:DI (match_dup 1)
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
	(arith_pattern2:DI
	 (arith_pattern2:DI (match_operand:DI 1 "register_operand" "r")
		  (match_operand:DI 2 "register_operand" "r"))
	 (ltu:DI (reg:CC_C CC_REGNUM) (const_int 0))))]
  ""
  "<arc64_carry_map>l\\t%0,%1,%2"
  [(set_attr "type" "<arc64_carry_map>l")
   (set_attr "length" "4")]
)

(define_expand "<optab>ti3"
  [(set (match_operand:TI 0 "register_operand")
        (arith_pattern2:TI (match_operand:TI 1 "register_operand")
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

