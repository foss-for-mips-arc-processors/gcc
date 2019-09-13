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

(define_insn "*<arc64_code_map>_insn"
    [(set (                   match_operand:SI 0 "register_operand"  "=q,r,    r,    r,    r,r,    r,    r")
          (arith_pattern1:SI (match_operand:SI 1 "nonmemory_operand" "%0,0,    0,    0,    r,r,ULIMM,    r")
                             (match_operand:SI 2 "nonmemory_operand" " q,r,U06S0,S12S0,U06S0,r,    r,ULIMM")))]
    "register_operand (operands[1], SImode) || register_operand (operands[2], SImode)"
    "<arc64_code_map>%?\\t%0,%1,%2"
    [(set_attr "predicable" "no,yes,yes,no,no,no,no,no")
     (set_attr "length"     "2,4,4,4,4,4,8,8")
     (set_attr "type"       "<arc64_code_map>")]
)
