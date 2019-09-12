
; START:andsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (and:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "and"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], SImode) || register_operand (operands[2], SImode)",
;   "ordered_constraints": [
;       { "_comment": "and_s b:R3, b:R3, c:R3 (189)", "assembly": "and_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "q" } },
;       { "_comment": "and.cc.f b:R6, b:R6, u6:uimm6 (187)", "assembly": "and %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "and.cc.f b:R6, b:R6, limm:limm (184)", "assembly": "and %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "and.cc.f b:R6, b:R6, c:R6 (183)", "assembly": "and %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "and.f a:R6, b:R6, u6:uimm6 (177)", "assembly": "and %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "and.f b:R6, b:R6, s12:simm12 (181)", "assembly": "and %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "and.f a:R6, b:R6, c:R6 (169)", "assembly": "and %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } },
;       { "_comment": "and.f a:R6, b:R6, limm:limm (171)", "assembly": "and %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "and.f a:R6, limm:limm, c:R6 (170)", "assembly": "and %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "and %0,%1,%2",
;       "and_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:andsi3
(define_insn "andsi3" [
    (set
      (match_operand:SI 0 "register_operand" "=q,r,r,r,r,r,r,r,r")
      (and:SI
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM")
        (match_operand:SI 2 "nonmemory_operand" "q,U06S0,ULIMM,r,U06S0,S12S0,r,ULIMM,r")))]
 "true" "@
  and_s %0,%1,%2
  and %0,%1,%2
  and %0,%1,%2
  and %0,%1,%2
  and %0,%1,%2
  and %0,%1,%2
  and %0,%1,%2
  and %0,%1,%2
  and %0,%1,%2" [
    (set_attr "predicable" "no,yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "2,4,8,4,4,4,4,8,8")
    (set_attr "type" "and,and,and,and,and,and,and,and,and")]
)
; END:andsi3

; START:anddi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (and:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "andl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], DImode) || register_operand (operands[2], DImode)",
;   "ordered_constraints": [
;       { "_comment": "andl_s b:R3, b:R3, c:R3 (6587)", "assembly": "andl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "q" } },
;       { "_comment": "andl.cc.f RB:rb, RB:rb, u6:uimm6 (5100)", "assembly": "andl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "andl.cc.f RB:rb, RB:rb, limm:limm (5107)", "assembly": "andl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "andl.cc.f RB:rb, RB:rb, ximm:ximm (5120)", "assembly": "andl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "andl.cc.f RB:rb, RB:rb, RC:rc (5097)", "assembly": "andl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "andl.f RA:ra, RB:rb, u6:uimm6 (5098)", "assembly": "andl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "andl.f RB:rb, RB:rb, s12:simm12 (5101)", "assembly": "andl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "andl.f RA:ra, RB:rb, limm:limm (5103)", "assembly": "andl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "andl.f RA:ra, RB:rb, ximm:ximm (5116)", "assembly": "andl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "andl.f RA:ra, limm:limm, RC:rc (5102)", "assembly": "andl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "andl.f RA:ra, ximm:ximm, RC:rc (5115)", "assembly": "andl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "andl.f RA:ra, RB:rb, RC:rc (5095)", "assembly": "andl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "andl %0,%1,%2",
;       "andl_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;         { "_comment": "andl.aq RB:rb, RC:rc (6402)" },
;         { "_comment": "andl.aq 0:0, RC:rc (6403)" },
;         { "_comment": "andl.aq RB:rb, u6:uimm6 (6404)" },
;         { "_comment": "andl.aq 0:0, u6:uimm6 (6405)" },
;         { "_comment": "andl.aq RB:rb, limm:limm (6406)" },
;         { "_comment": "andl.aq 0:0, limm:limm (6407)" },
;         { "_comment": "andl.aq RB:rb, ximm:ximm (6408)" },
;         { "_comment": "andl.aq 0:0, ximm:ximm (6409)" }
;     ]
;     }
;   }
; OUTPUT:anddi3
(define_insn "anddi3" [
    (set
      (match_operand:DI 0 "register_operand" "=q,r,r,r,r,r,r,r,r,r,r,r")
      (and:DI
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,0,r,0,r,r,ULIMM,UXIMM,r")
        (match_operand:DI 2 "nonmemory_operand" "q,U06S0,ULIMM,UXIMM,r,U06S0,S12S0,ULIMM,UXIMM,r,r,r")))]
 "true" "@
  andl_s %0,%1,%2
  andl %0,%1,%2
  andl %0,%1,%2
  andl %0,%1,%2
  andl %0,%1,%2
  andl %0,%1,%2
  andl %0,%1,%2
  andl %0,%1,%2
  andl %0,%1,%2
  andl %0,%1,%2
  andl %0,%1,%2
  andl %0,%1,%2" [
    (set_attr "predicable" "no,yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "2,4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "andl,andl,andl,andl,andl,andl,andl,andl,andl,andl,andl,andl")]
)
; END:anddi3


; START:ashlsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (ashift:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "asl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], SImode) || register_operand (operands[2], SImode)",
;   "ordered_constraints": [
;       { "_comment": "asl_s c:R3, b:R3, u3:uimm3 (217)", "assembly": "asl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "U03S0" } },
;       { "_comment": "asl_s b:R3, b:R3, u5:uimm5 (219)", "assembly": "asl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "U05S0" } },
;       { "_comment": "asl_s b:R3, b:R3, c:R3 (218)", "assembly": "asl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "q" } },
;       { "_comment": "asl.cc.f b:R6, b:R6, u6:uimm6 (215)", "assembly": "asl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "asl.cc.f b:R6, b:R6, limm:limm (212)", "assembly": "asl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "asl.cc.f b:R6, b:R6, c:R6 (211)", "assembly": "asl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "asl.f a:R6, b:R6, u6:uimm6 (205)", "assembly": "asl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "asl.f b:R6, b:R6, s12:simm12 (209)", "assembly": "asl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "asl.f a:R6, b:R6, limm:limm (199)", "assembly": "asl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "asl.f a:R6, limm:limm, c:R6 (198)", "assembly": "asl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "asl.f a:R6, b:R6, c:R6 (197)", "assembly": "asl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "asl %0,%1,%2",
;       "asl_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;         { "_comment": "asl.f b:R6, c:R6 (190)" },
;         { "_comment": "asl.f b:R6, limm:limm (191)" },
;         { "_comment": "asl.f 0:0, c:R6 (192)" },
;         { "_comment": "asl.f 0:0, limm:limm (193)" },
;         { "_comment": "asl.f b:R6, u6:uimm6 (194)" },
;         { "_comment": "asl.f 0:0, u6:uimm6 (195)" },
;         { "_comment": "asl_s b:R3, c:R3 (196)" }
;     ]
;     }
;   }
; OUTPUT:ashlsi3
(define_insn "ashlsi3" [
    (set
      (match_operand:SI 0 "register_operand" "=q,q,q,r,r,r,r,r,r,r,r")
      (ashift:SI
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,0,0,0,r,0,r,ULIMM,r")
        (match_operand:SI 2 "nonmemory_operand" "U03S0,U05S0,q,U06S0,ULIMM,r,U06S0,S12S0,ULIMM,r,r")))]
 "true" "@
  asl_s %0,%1,%2
  asl_s %0,%1,%2
  asl_s %0,%1,%2
  asl %0,%1,%2
  asl %0,%1,%2
  asl %0,%1,%2
  asl %0,%1,%2
  asl %0,%1,%2
  asl %0,%1,%2
  asl %0,%1,%2
  asl %0,%1,%2" [
    (set_attr "predicable" "no,no,no,yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "2,2,2,4,8,4,4,4,8,8,4")
    (set_attr "type" "asl,asl,asl,asl,asl,asl,asl,asl,asl,asl,asl")]
)
; END:ashlsi3


; START:ashldi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (ashift:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "asll"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], DImode) || register_operand (operands[2], DImode)",
;   "ordered_constraints": [
;       { "_comment": "asll.cc.f RB:rb, RB:rb, RC:rc (5658)", "assembly": "asll %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "asll.cc.f RB:rb, RB:rb, limm:limm (5668)", "assembly": "asll %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "asll.cc.f RB:rb, RB:rb, u6:uimm6 (5661)", "assembly": "asll %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "asll.cc.f RB:rb, RB:rb, ximm:ximm (5681)", "assembly": "asll %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "asll.f RA:ra, RB:rb, u6:uimm6 (5659)", "assembly": "asll %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "asll.f RB:rb, RB:rb, s12:simm12 (5662)", "assembly": "asll %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "asll.f RA:ra, RB:rb, limm:limm (5664)", "assembly": "asll %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "asll.f RA:ra, RB:rb, ximm:ximm (5677)", "assembly": "asll %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "asll.f RA:ra, limm:limm, RC:rc (5663)", "assembly": "asll %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "asll.f RA:ra, ximm:ximm, RC:rc (5676)", "assembly": "asll %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "asll.f RA:ra, RB:rb, RC:rc (5656)", "assembly": "asll %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "asll %0,%1,%2",
;       "asll_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;         { "_comment": "asll.f RB:rb, RC:rc (6250)" },
;         { "_comment": "asll.f 0:0, RC:rc (6251)" },
;         { "_comment": "asll.f RB:rb, u6:uimm6 (6252)" },
;         { "_comment": "asll.f 0:0, u6:uimm6 (6253)" },
;         { "_comment": "asll.f RB:rb, limm:limm (6254)" },
;         { "_comment": "asll.f 0:0, limm:limm (6255)" },
;         { "_comment": "asll.f RB:rb, ximm:ximm (6256)" },
;         { "_comment": "asll.f 0:0, ximm:ximm (6257)" }
;     ]
;     }
;   }
; OUTPUT:ashldi3
(define_insn "ashldi3" [
    (set
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r")
      (ashift:DI
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM,UXIMM,r")
        (match_operand:DI 2 "nonmemory_operand" "r,ULIMM,U06S0,UXIMM,U06S0,S12S0,ULIMM,UXIMM,r,r,r")))]
 "true" "@
  asll %0,%1,%2
  asll %0,%1,%2
  asll %0,%1,%2
  asll %0,%1,%2
  asll %0,%1,%2
  asll %0,%1,%2
  asll %0,%1,%2
  asll %0,%1,%2
  asll %0,%1,%2
  asll %0,%1,%2
  asll %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "asll,asll,asll,asll,asll,asll,asll,asll,asll,asll,asll")]
)
; END:ashldi3


; START:ashlsi2_cnt1
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (ashift:SI @op1{mode=SI} (const_int 1)))]",
;   "general_attributes":   {
;     "type": "asl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "",
;   "ordered_constraints": [
;       { "_comment": "asl_s b:R3, c:R3 (196)", "assembly": "asl_s %0,%1", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q" } },
;       { "_comment": "asl.f b:R6, u6:uimm6 (194)", "assembly": "asl %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "asl.f b:R6, limm:limm (191)", "assembly": "asl %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "asl.f b:R6, c:R6 (190)", "assembly": "asl %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "asl %0,%1",
;       "asl_s %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:ashlsi2_cnt1
(define_insn "ashlsi2_cnt1" [
    (set
      (match_operand:SI 0 "register_operand" "=q,r,r,r")
      (ashift:SI
        (match_operand:SI 1 "nonmemory_operand" "q,U06S0,ULIMM,r")
        (const_int 1)))]
 "true" "@
  asl_s %0,%1
  asl %0,%1
  asl %0,%1
  asl %0,%1" [
    (set_attr "predicable" "no,no,no,no")
    (set_attr "length" "2,4,8,4")
    (set_attr "type" "asl,asl,asl,asl")]
)
; END:ashlsi2_cnt1

; START:ashlsi2_cnt8
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (ashift:SI @op1{mode=SI} (const_int 8)))]",
;   "general_attributes":   {
;     "type": "asl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "",
;   "ordered_constraints": [
;       { "_comment": "lsl8.f b:R6, u6:uimm6 (1762)", "assembly": "lsl8 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "lsl8.f b:R6, c:R6 (1758)", "assembly": "lsl8 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } },
;       { "_comment": "lsl8.f b:R6, limm:limm (1759)", "assembly": "lsl8 %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "lsl8_s %0,%1",
;       "lsl8 %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:ashlsi2_cnt8
(define_insn "ashlsi2_cnt8" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r")
      (ashift:SI
        (match_operand:SI 1 "nonmemory_operand" "U06S0,r,ULIMM")
        (const_int 8)))]
 "true" "@
  lsl8 %0,%1
  lsl8 %0,%1
  lsl8 %0,%1" [
    (set_attr "predicable" "no,no,no")
    (set_attr "length" "4,4,8")
    (set_attr "type" "asl,asl,asl")]
)
; END:ashlsi2_cnt8

; START:ashlsi2_cnt16
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (ashift:SI @op1{mode=SI} (const_int 16)))]",
;   "general_attributes":   {
;     "type": "asl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "",
;   "ordered_constraints": [
;       { "_comment": "lsl16.f b:R6, u6:uimm6 (1756)", "assembly": "lsl16 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "lsl16.f b:R6, limm:limm (1753)", "assembly": "lsl16 %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "lsl16.f b:R6, c:R6 (1752)", "assembly": "lsl16 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "lsl16_s %0,%1",
;       "lsl16 %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:ashlsi2_cnt16
(define_insn "ashlsi2_cnt16" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r")
      (ashift:SI
        (match_operand:SI 1 "nonmemory_operand" "U06S0,ULIMM,r")
        (const_int 16)))]
 "true" "@
  lsl16 %0,%1
  lsl16 %0,%1
  lsl16 %0,%1" [
    (set_attr "predicable" "no,no,no")
    (set_attr "length" "4,8,4")
    (set_attr "type" "asl,asl,asl")]
)
; END:ashlsi2_cnt16

; START:ashrsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (ashiftrt:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "asr"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], SImode) || register_operand (operands[2], SImode)",
;   "ordered_constraints": [
;       { "_comment": "asr_s c:R3, b:R3, u3:uimm3 (271)", "assembly": "asr_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q", "op2": "U03S0" } },
;       { "_comment": "asr_s b:R3, b:R3, u5:uimm5 (273)", "assembly": "asr_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "U05S0" } },
;       { "_comment": "asr_s b:R3, b:R3, c:R3 (272)", "assembly": "asr_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "q" } },
;       { "_comment": "asr.cc.f b:R6, b:R6, c:R6 (265)", "assembly": "asr %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "asr.cc.f b:R6, b:R6, limm:limm (266)", "assembly": "asr %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "asr.cc.f b:R6, b:R6, u6:uimm6 (269)", "assembly": "asr %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "asr.f a:R6, b:R6, u6:uimm6 (259)", "assembly": "asr %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "asr.f b:R6, b:R6, s12:simm12 (263)", "assembly": "asr %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "asr.f a:R6, b:R6, limm:limm (253)", "assembly": "asr %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "asr.f a:R6, limm:limm, c:R6 (252)", "assembly": "asr %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "asr.f a:R6, b:R6, c:R6 (251)", "assembly": "asr %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "asr_s %0,%1,%2",
;       "asr %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:ashrsi3
(define_insn "ashrsi3" [
    (set
      (match_operand:SI 0 "register_operand" "=q,q,q,r,r,r,r,r,r,r,r")
      (ashiftrt:SI
        (match_operand:SI 1 "nonmemory_operand" "q,0,0,0,0,0,r,0,r,ULIMM,r")
        (match_operand:SI 2 "nonmemory_operand" "U03S0,U05S0,q,r,ULIMM,U06S0,U06S0,S12S0,ULIMM,r,r")))]
 "true" "@
  asr_s %0,%1,%2
  asr_s %0,%1,%2
  asr_s %0,%1,%2
  asr %0,%1,%2
  asr %0,%1,%2
  asr %0,%1,%2
  asr %0,%1,%2
  asr %0,%1,%2
  asr %0,%1,%2
  asr %0,%1,%2
  asr %0,%1,%2" [
    (set_attr "predicable" "no,no,no,yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "2,2,2,4,8,4,4,4,8,8,4")
    (set_attr "type" "asr,asr,asr,asr,asr,asr,asr,asr,asr,asr,asr")]
)
; END:ashrsi3

; START:ashrsi2_cnt1
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (ashiftrt:SI @op1{mode=SI} (const_int 1)))]",
;   "general_attributes":   {
;     "type": "asr"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "",
;   "ordered_constraints": [
;       { "_comment": "asr_s b:R3, c:R3 (250)", "assembly": "asr_s %0,%1", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q" } },
;       { "_comment": "asr.f b:R6, u6:uimm6 (248)", "assembly": "asr %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "asr.f b:R6, limm:limm (245)", "assembly": "asr %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "asr.f b:R6, c:R6 (244)", "assembly": "asr %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "asr_s %0,%1",
;       "asr %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:ashrsi2_cnt1
(define_insn "ashrsi2_cnt1" [
    (set
      (match_operand:SI 0 "register_operand" "=q,r,r,r")
      (ashiftrt:SI
        (match_operand:SI 1 "nonmemory_operand" "q,U06S0,ULIMM,r")
        (const_int 1)))]
 "true" "@
  asr_s %0,%1
  asr %0,%1
  asr %0,%1
  asr %0,%1" [
    (set_attr "predicable" "no,no,no,no")
    (set_attr "length" "2,4,8,4")
    (set_attr "type" "asr,asr,asr,asr")]
)
; END:ashrsi2_cnt1

; START:ashrsi2_cnt8
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (ashiftrt:SI @op1{mode=SI} (const_int 8)))]",
;   "general_attributes":   {
;     "type": "asr"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "",
;   "ordered_constraints": [
;       { "_comment": "asr8.f b:R6, u6:uimm6 (281)", "assembly": "asr8 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "asr8.f b:R6, limm:limm (282)", "assembly": "asr8 %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "asr8.f b:R6, c:R6 (280)", "assembly": "asr8 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "asr8_s %0,%1",
;       "asr8 %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:ashrsi2_cnt8
(define_insn "ashrsi2_cnt8" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r")
      (ashiftrt:SI
        (match_operand:SI 1 "nonmemory_operand" "U06S0,ULIMM,r")
        (const_int 8)))]
 "true" "@
  asr8 %0,%1
  asr8 %0,%1
  asr8 %0,%1" [
    (set_attr "predicable" "no,no,no")
    (set_attr "length" "4,8,4")
    (set_attr "type" "asr,asr,asr")]
)
; END:ashrsi2_cnt8

; START:ashrsi2_cnt16
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (ashiftrt:SI @op1{mode=SI} (const_int 16)))]",
;   "general_attributes":   {
;     "type": "asr"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "",
;   "ordered_constraints": [
;       { "_comment": "asr16.f b:R6, c:R6 (274)", "assembly": "asr16 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } },
;       { "_comment": "asr16.f b:R6, limm:limm (276)", "assembly": "asr16 %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "asr16.f b:R6, u6:uimm6 (275)", "assembly": "asr16 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "asr16_s %0,%1",
;       "asr16 %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:ashrsi2_cnt16
(define_insn "ashrsi2_cnt16" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r")
      (ashiftrt:SI
        (match_operand:SI 1 "nonmemory_operand" "r,ULIMM,U06S0")
        (const_int 16)))]
 "true" "@
  asr16 %0,%1
  asr16 %0,%1
  asr16 %0,%1" [
    (set_attr "predicable" "no,no,no")
    (set_attr "length" "4,8,4")
    (set_attr "type" "asr,asr,asr")]
)
; END:ashrsi2_cnt16


; START:ashrdi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (ashiftrt:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "asrl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], DImode) || register_operand (operands[2], DImode)",
;   "ordered_constraints": [
;       { "_comment": "asrl.cc.f RB:rb, RB:rb, RC:rc (5724)", "assembly": "asrl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "asrl.cc.f RB:rb, RB:rb, limm:limm (5734)", "assembly": "asrl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "asrl.cc.f RB:rb, RB:rb, u6:uimm6 (5727)", "assembly": "asrl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "asrl.cc.f RB:rb, RB:rb, ximm:ximm (5747)", "assembly": "asrl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "asrl.f RA:ra, RB:rb, u6:uimm6 (5725)", "assembly": "asrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "asrl.f RB:rb, RB:rb, s12:simm12 (5728)", "assembly": "asrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "asrl.f RA:ra, RB:rb, RC:rc (5722)", "assembly": "asrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } },
;       { "_comment": "asrl.f RA:ra, RB:rb, limm:limm (5730)", "assembly": "asrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "asrl.f RA:ra, RB:rb, ximm:ximm (5743)", "assembly": "asrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "asrl.f RA:ra, limm:limm, RC:rc (5729)", "assembly": "asrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "asrl.f RA:ra, ximm:ximm, RC:rc (5742)", "assembly": "asrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "asrl_s %0,%1,%2",
;       "asrl %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:ashrdi3
(define_insn "ashrdi3" [
    (set
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r")
      (ashiftrt:DI
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,r,ULIMM,UXIMM")
        (match_operand:DI 2 "nonmemory_operand" "r,ULIMM,U06S0,UXIMM,U06S0,S12S0,r,ULIMM,UXIMM,r,r")))]
 "true" "@
  asrl %0,%1,%2
  asrl %0,%1,%2
  asrl %0,%1,%2
  asrl %0,%1,%2
  asrl %0,%1,%2
  asrl %0,%1,%2
  asrl %0,%1,%2
  asrl %0,%1,%2
  asrl %0,%1,%2
  asrl %0,%1,%2
  asrl %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,4,8,4,8,4")
    (set_attr "type" "asrl,asrl,asrl,asrl,asrl,asrl,asrl,asrl,asrl,asrl,asrl")]
)
; END:ashrdi3

; START:ashrdi2_cnt1
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (ashiftrt:DI @op1{mode=DI} (const_int 1)))]",
;   "general_attributes":   {
;     "type": "asrl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], DImode)",
;   "ordered_constraints": [
;       { "_comment": "asrl.f RB:rb, u6:uimm6 (6260)", "assembly": "asrl %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "asrl.f RB:rb, limm:limm (6262)", "assembly": "asrl %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "asrl.f RB:rb, ximm:ximm (6264)", "assembly": "asrl %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM" } },
;       { "_comment": "asrl.f RB:rb, RC:rc (6258)", "assembly": "asrl %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "asrl_s %0,%1",
;       "asrl %0,%1"
;     ]
;     },
;   "DB_generated":   {
;
;     }
;   }
; OUTPUT:ashrdi2_cnt1
(define_insn "ashrdi2_cnt1" [
    (set
      (match_operand:DI 0 "register_operand" "=r,r,r,r")
      (ashiftrt:DI
        (match_operand:DI 1 "nonmemory_operand" "U06S0,ULIMM,UXIMM,r")
        (const_int 1)))]
 "true" "@
  asrl %0,%1
  asrl %0,%1
  asrl %0,%1
  asrl %0,%1" [
    (set_attr "predicable" "no,no,no,no")
    (set_attr "length" "4,8,4,4")
    (set_attr "type" "asrl,asrl,asrl,asrl")]
)
; END:ashrdi2_cnt1

; START:lshrsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (lshiftrt:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "lsr"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], SImode) || register_operand (operands[2], SImode)",
;   "ordered_constraints": [
;       { "_comment": "lsr_s b:R3, b:R3, c:R3 (1791)", "assembly": "lsr_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "q" } },
;       { "_comment": "lsr.cc.f b:R6, b:R6, u6:uimm6 (1789)", "assembly": "lsr %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "lsr.cc.f b:R6, b:R6, limm:limm (1786)", "assembly": "lsr %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "lsr.cc.f b:R6, b:R6, c:R6 (1785)", "assembly": "lsr %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "lsr_s b:R3, b:R3, u5:uimm5 (1792)", "assembly": "lsr_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "U05S0" } },
;       { "_comment": "lsr.f b:R6, b:R6, s12:simm12 (1783)", "assembly": "lsr %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "lsr.f a:R6, b:R6, limm:limm (1773)", "assembly": "lsr %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "lsr.f a:R6, b:R6, u6:uimm6 (1779)", "assembly": "lsr %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "lsr.f a:R6, limm:limm, c:R6 (1772)", "assembly": "lsr %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "lsr.f a:R6, b:R6, c:R6 (1771)", "assembly": "lsr %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "lsr_s %0,%1,%2",
;       "lsr %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:lshrsi3
(define_insn "lshrsi3" [
    (set
      (match_operand:SI 0 "register_operand" "=q,r,r,r,q,r,r,r,r,r")
      (lshiftrt:SI
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,0,0,0,r,r,ULIMM,r")
        (match_operand:SI 2 "nonmemory_operand" "q,U06S0,ULIMM,r,U05S0,S12S0,ULIMM,U06S0,r,r")))]
 "true" "@
  lsr_s %0,%1,%2
  lsr %0,%1,%2
  lsr %0,%1,%2
  lsr %0,%1,%2
  lsr_s %0,%1,%2
  lsr %0,%1,%2
  lsr %0,%1,%2
  lsr %0,%1,%2
  lsr %0,%1,%2
  lsr %0,%1,%2" [
    (set_attr "predicable" "no,yes,yes,yes,no,no,no,no,no,no")
    (set_attr "length" "2,4,8,4,2,4,8,4,8,4")
    (set_attr "type" "lsr,lsr,lsr,lsr,lsr,lsr,lsr,lsr,lsr,lsr")]
)
; END:lshrsi3

; START:lshrsi2_cnt1
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (lshiftrt:SI @op1{mode=SI} (const_int 1)))]",
;   "general_attributes":   {
;     "type": "lsr"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "lsr_s b:R3, c:R3 (1770)", "assembly": "lsr_s %0,%1", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q" } },
;       { "_comment": "lsr.f b:R6, u6:uimm6 (1768)", "assembly": "lsr %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "lsr.f b:R6, limm:limm (1765)", "assembly": "lsr %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "lsr.f b:R6, c:R6 (1764)", "assembly": "lsr %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "lsr_s %0,%1",
;       "lsr %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:lshrsi2_cnt1
(define_insn "lshrsi2_cnt1" [
    (set
      (match_operand:SI 0 "register_operand" "=q,r,r,r")
      (lshiftrt:SI
        (match_operand:SI 1 "nonmemory_operand" "q,U06S0,ULIMM,r")
        (const_int 1)))]
 "true" "@
  lsr_s %0,%1
  lsr %0,%1
  lsr %0,%1
  lsr %0,%1" [
    (set_attr "predicable" "no,no,no,no")
    (set_attr "length" "2,4,8,4")
    (set_attr "type" "lsr,lsr,lsr,lsr")]
)
; END:lshrsi2_cnt1

; START:lshrsi2_cnt8
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (lshiftrt:SI @op1{mode=SI} (const_int 8)))]",
;   "general_attributes":   {
;     "type": "lsr"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "lsr8.f b:R6, u6:uimm6 (1803)", "assembly": "lsr8 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "lsr8.f b:R6, limm:limm (1800)", "assembly": "lsr8 %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "lsr8.f b:R6, c:R6 (1799)", "assembly": "lsr8 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "lsr8_s %0,%1",
;       "lsr8 %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:lshrsi2_cnt8
(define_insn "lshrsi2_cnt8" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r")
      (lshiftrt:SI
        (match_operand:SI 1 "nonmemory_operand" "U06S0,ULIMM,r")
        (const_int 8)))]
 "true" "@
  lsr8 %0,%1
  lsr8 %0,%1
  lsr8 %0,%1" [
    (set_attr "predicable" "no,no,no")
    (set_attr "length" "4,8,4")
    (set_attr "type" "lsr,lsr,lsr")]
)
; END:lshrsi2_cnt8

; START:lshrsi2_cnt16
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (lshiftrt:SI @op1{mode=SI} (const_int 16)))]",
;   "general_attributes":   {
;     "type": "lsr"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "lsr16.f b:R6, u6:uimm6 (1797)", "assembly": "lsr16 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "lsr16.f b:R6, limm:limm (1794)", "assembly": "lsr16 %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "lsr16.f b:R6, c:R6 (1793)", "assembly": "lsr16 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "lsr16_s %0,%1",
;       "lsr16 %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:lshrsi2_cnt16
(define_insn "lshrsi2_cnt16" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r")
      (lshiftrt:SI
        (match_operand:SI 1 "nonmemory_operand" "U06S0,ULIMM,r")
        (const_int 16)))]
 "true" "@
  lsr16 %0,%1
  lsr16 %0,%1
  lsr16 %0,%1" [
    (set_attr "predicable" "no,no,no")
    (set_attr "length" "4,8,4")
    (set_attr "type" "lsr,lsr,lsr")]
)
; END:lshrsi2_cnt16

; START:lshrdi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (lshiftrt:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "lsrl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], DImode) || register_operand (operands[2], DImode)",
;   "ordered_constraints": [
;       { "_comment": "lsrl.cc.f RB:rb, RB:rb, RC:rc (5691)", "assembly": "lsrl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "lsrl.cc.f RB:rb, RB:rb, limm:limm (5701)", "assembly": "lsrl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "lsrl.cc.f RB:rb, RB:rb, u6:uimm6 (5694)", "assembly": "lsrl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "lsrl.cc.f RB:rb, RB:rb, ximm:ximm (5714)", "assembly": "lsrl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "lsrl.f RA:ra, RB:rb, u6:uimm6 (5692)", "assembly": "lsrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "lsrl.f RB:rb, RB:rb, s12:simm12 (5695)", "assembly": "lsrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "lsrl.f RA:ra, RB:rb, limm:limm (5697)", "assembly": "lsrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "lsrl.f RA:ra, RB:rb, ximm:ximm (5710)", "assembly": "lsrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "lsrl.f RA:ra, limm:limm, RC:rc (5696)", "assembly": "lsrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "lsrl.f RA:ra, ximm:ximm, RC:rc (5709)", "assembly": "lsrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "lsrl.f RA:ra, RB:rb, RC:rc (5689)", "assembly": "lsrl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "lsrl_s %0,%1,%2",
;       "lsrl %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:lshrdi3
(define_insn "lshrdi3" [
    (set
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r")
      (lshiftrt:DI
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM,UXIMM,r")
        (match_operand:DI 2 "nonmemory_operand" "r,ULIMM,U06S0,UXIMM,U06S0,S12S0,ULIMM,UXIMM,r,r,r")))]
 "true" "@
  lsrl %0,%1,%2
  lsrl %0,%1,%2
  lsrl %0,%1,%2
  lsrl %0,%1,%2
  lsrl %0,%1,%2
  lsrl %0,%1,%2
  lsrl %0,%1,%2
  lsrl %0,%1,%2
  lsrl %0,%1,%2
  lsrl %0,%1,%2
  lsrl %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "lsrl,lsrl,lsrl,lsrl,lsrl,lsrl,lsrl,lsrl,lsrl,lsrl,lsrl")]
)
; END:lshrdi3

; START:one_cmplsi2
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (not:SI @op1{mode=SI}))]",
;   "general_attributes":   {
;     "type": "not"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "not_s b:R3, c:R3 (2534)", "assembly": "not_s %0,%1", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0" } },
;       { "_comment": "not.f b:R6, u6:uimm6 (2532)", "assembly": "not %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "not.f b:R6, limm:limm (2529)", "assembly": "not %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "not.f b:R6, c:R6 (2528)", "assembly": "not %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "not_s %0,%1",
;       "not %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:one_cmplsi2
(define_insn "one_cmplsi2" [
    (set
      (match_operand:SI 0 "register_operand" "=q,r,r,r")
      (not:SI
        (match_operand:SI 1 "nonmemory_operand" "0,U06S0,ULIMM,r")))]
 "true" "@
  not_s %0,%1
  not %0,%1
  not %0,%1
  not %0,%1" [
    (set_attr "predicable" "no,no,no,no")
    (set_attr "length" "2,4,8,4")
    (set_attr "type" "not,not,not,not")]
)
; END:one_cmplsi2


; START:one_cmpldi2
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (not:DI @op1{mode=DI}))]",
;   "general_attributes":   {
;     "type": "notl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "notl.f RB:rb, u6:uimm6 (6308)", "assembly": "notl %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "notl.f RB:rb, limm:limm (6310)", "assembly": "notl %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "notl.f RB:rb, ximm:ximm (6312)", "assembly": "notl %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM" } },
;       { "_comment": "notl.f RB:rb, RC:rc (6306)", "assembly": "notl %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "notl_s %0,%1",
;       "notl %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:one_cmpldi2
(define_insn "one_cmpldi2" [
    (set
      (match_operand:DI 0 "register_operand" "=r,r,r,r")
      (not:DI
        (match_operand:DI 1 "nonmemory_operand" "U06S0,ULIMM,UXIMM,r")))]
 "true" "@
  notl %0,%1
  notl %0,%1
  notl %0,%1
  notl %0,%1" [
    (set_attr "predicable" "no,no,no,no")
    (set_attr "length" "4,8,4,4")
    (set_attr "type" "notl,notl,notl,notl")]
)
; END:one_cmpldi2

; START:rotrsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (rotatert:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "ror"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "ror.cc.f b:R6, b:R6, u6:uimm6 (2956)", "assembly": "ror %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "ror.cc.f b:R6, b:R6, limm:limm (2953)", "assembly": "ror %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "ror.cc.f b:R6, b:R6, c:R6 (2952)", "assembly": "ror %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "ror.f a:R6, b:R6, u6:uimm6 (2946)", "assembly": "ror %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "ror.f b:R6, b:R6, s12:simm12 (2950)", "assembly": "ror %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "ror.f a:R6, b:R6, limm:limm (2940)", "assembly": "ror %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "ror.f a:R6, limm:limm, c:R6 (2939)", "assembly": "ror %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "ror.f a:R6, b:R6, c:R6 (2938)", "assembly": "ror %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "ror_s %0,%1,%2",
;       "ror %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:rotrsi3
(define_insn "rotrsi3" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r,r,r,r,r,r")
      (rotatert:SI
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,r,0,r,ULIMM,r")
        (match_operand:SI 2 "nonmemory_operand" "U06S0,ULIMM,r,U06S0,S12S0,ULIMM,r,r")))]
 "true" "@
  ror %0,%1,%2
  ror %0,%1,%2
  ror %0,%1,%2
  ror %0,%1,%2
  ror %0,%1,%2
  ror %0,%1,%2
  ror %0,%1,%2
  ror %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,8,8,4")
    (set_attr "type" "ror,ror,ror,ror,ror,ror,ror,ror")]
)
; END:rotrsi3

; START:rotrsi2_cnt1
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (rotatert:SI @op1{mode=SI} (const_int 1)))]",
;   "general_attributes":   {
;     "type": "ror"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "ror.f b:R6, u6:uimm6 (2936)", "assembly": "ror %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "ror.f b:R6, limm:limm (2933)", "assembly": "ror %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "ror.f b:R6, c:R6 (2932)", "assembly": "ror %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "ror_s %0,%1",
;       "ror %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:rotrsi2_cnt1
(define_insn "rotrsi2_cnt1" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r")
      (rotatert:SI
        (match_operand:SI 1 "nonmemory_operand" "U06S0,ULIMM,r")
        (const_int 1)))]
 "true" "@
  ror %0,%1
  ror %0,%1
  ror %0,%1" [
    (set_attr "predicable" "no,no,no")
    (set_attr "length" "4,8,4")
    (set_attr "type" "ror,ror,ror")]
)
; END:rotrsi2_cnt1

; START:rotrsi2_cnt8
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (rotatert:SI @op1{mode=SI} (const_int 8)))]",
;   "general_attributes":   {
;     "type": "ror"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "ror8.f b:R6, u6:uimm6 (2962)", "assembly": "ror8 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "ror8.f b:R6, limm:limm (2959)", "assembly": "ror8 %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "ror8.f b:R6, c:R6 (2958)", "assembly": "ror8 %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "ror8_s %0,%1",
;       "ror8 %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:rotrsi2_cnt8
(define_insn "rotrsi2_cnt8" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r")
      (rotatert:SI
        (match_operand:SI 1 "nonmemory_operand" "U06S0,ULIMM,r")
        (const_int 8)))]
 "true" "@
  ror8 %0,%1
  ror8 %0,%1
  ror8 %0,%1" [
    (set_attr "predicable" "no,no,no")
    (set_attr "length" "4,8,4")
    (set_attr "type" "ror,ror,ror")]
)
; END:rotrsi2_cnt8

; START:clrsbsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (clrsb:SI @op1{mode=SI}))]",
;   "general_attributes":   {
;     "type": "norm"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "norm.f b:R6, u6:uimm6 (2514)", "assembly": "norm %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "norm.f b:R6, limm:limm (2511)", "assembly": "norm %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "norm.f b:R6, c:R6 (2510)", "assembly": "norm %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "norm_s %0,%1",
;       "norm %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:clrsbsi3
(define_insn "clrsbsi3" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r")
      (clrsb:SI
        (match_operand:SI 1 "nonmemory_operand" "U06S0,ULIMM,r")))]
 "true" "@
  norm %0,%1
  norm %0,%1
  norm %0,%1" [
    (set_attr "predicable" "no,no,no")
    (set_attr "length" "4,8,4")
    (set_attr "type" "norm,norm,norm")]
)
; END:clrsbsi3

; START:clrsbdi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (clrsb:DI @op1{mode=DI}))]",
;   "general_attributes":   {
;     "type": "norml"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "norml.f RB:rb, u6:uimm6 (6364)", "assembly": "norml %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "norml.f RB:rb, limm:limm (6366)", "assembly": "norml %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "norml.f RB:rb, ximm:ximm (6368)", "assembly": "norml %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM" } },
;       { "_comment": "norml.f RB:rb, RC:rc (6362)", "assembly": "norml %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "norml_s %0,%1",
;       "norml %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:clrsbdi3
(define_insn "clrsbdi3" [
    (set
      (match_operand:DI 0 "register_operand" "=r,r,r,r")
      (clrsb:DI
        (match_operand:DI 1 "nonmemory_operand" "U06S0,ULIMM,UXIMM,r")))]
 "true" "@
  norml %0,%1
  norml %0,%1
  norml %0,%1
  norml %0,%1" [
    (set_attr "predicable" "no,no,no,no")
    (set_attr "length" "4,8,4,4")
    (set_attr "type" "norml,norml,norml,norml")]
)
; END:clrsbdi3

; START:clrsbhi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=HI} (clrsb:HI @op1{mode=HI}))]",
;   "general_attributes":   {
;     "type": "normh"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "normh.f b:R6, u6:uimm6 (2526)", "assembly": "normh %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "normh.f b:R6, limm:limm (2523)", "assembly": "normh %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "normh.f b:R6, c:R6 (2522)", "assembly": "normh %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "normh_s %0,%1",
;       "normh %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:clrsbhi3
(define_insn "clrsbhi3" [
    (set
      (match_operand:HI 0 "register_operand" "=r,r,r")
      (clrsb:HI
        (match_operand:HI 1 "nonmemory_operand" "U06S0,ULIMM,r")))]
 "true" "@
  normh %0,%1
  normh %0,%1
  normh %0,%1" [
    (set_attr "predicable" "no,no,no")
    (set_attr "length" "4,8,4")
    (set_attr "type" "normh,normh,normh")]
)
; END:clrsbhi3



; START:orsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (ior:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "or"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], SImode) || register_operand (operands[2], SImode)",
;   "ordered_constraints": [
;       { "_comment": "or_s b:R3, b:R3, c:R3 (2555)", "assembly": "or_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "q" } },
;       { "_comment": "or.cc.f b:R6, b:R6, c:R6 (2549)", "assembly": "or %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "or.cc.f b:R6, b:R6, limm:limm (2550)", "assembly": "or %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "or.cc.f b:R6, b:R6, u6:uimm6 (2553)", "assembly": "or %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "or.f a:R6, b:R6, u6:uimm6 (2543)", "assembly": "or %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "or.f b:R6, b:R6, s12:simm12 (2547)", "assembly": "or %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "or.f a:R6, b:R6, limm:limm (2537)", "assembly": "or %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "or.f a:R6, limm:limm, c:R6 (2536)", "assembly": "or %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "or.f a:R6, b:R6, c:R6 (2535)", "assembly": "or %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "or_s %0,%1,%2",
;       "or %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:orsi3
(define_insn "orsi3" [
    (set
      (match_operand:SI 0 "register_operand" "=q,r,r,r,r,r,r,r,r")
      (ior:SI
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,0,r,0,r,ULIMM,r")
        (match_operand:SI 2 "nonmemory_operand" "q,r,ULIMM,U06S0,U06S0,S12S0,ULIMM,r,r")))]
 "true" "@
  or_s %0,%1,%2
  or %0,%1,%2
  or %0,%1,%2
  or %0,%1,%2
  or %0,%1,%2
  or %0,%1,%2
  or %0,%1,%2
  or %0,%1,%2
  or %0,%1,%2" [
    (set_attr "predicable" "no,yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "2,4,8,4,4,4,8,8,4")
    (set_attr "type" "or,or,or,or,or,or,or,or,or")]
)
; END:orsi3

; START:ordi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (ior:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "orl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], DImode) || register_operand (operands[2], DImode)",
;   "ordered_constraints": [
;       { "_comment": "orl_s b:R3, b:R3, c:R3 (6588)", "assembly": "orl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "q" } },
;       { "_comment": "orl.cc.f RB:rb, RB:rb, RC:rc (5130)", "assembly": "orl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "orl.cc.f RB:rb, RB:rb, limm:limm (5140)", "assembly": "orl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "orl.cc.f RB:rb, RB:rb, u6:uimm6 (5133)", "assembly": "orl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "orl.cc.f RB:rb, RB:rb, ximm:ximm (5153)", "assembly": "orl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "orl.f RA:ra, RB:rb, u6:uimm6 (5131)", "assembly": "orl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "orl.f RB:rb, RB:rb, s12:simm12 (5134)", "assembly": "orl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "orl.f RA:ra, RB:rb, RC:rc (5128)", "assembly": "orl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } },
;       { "_comment": "orl.f RA:ra, RB:rb, limm:limm (5136)", "assembly": "orl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "orl.f RA:ra, RB:rb, ximm:ximm (5149)", "assembly": "orl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "orl.f RA:ra, limm:limm, RC:rc (5135)", "assembly": "orl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "orl.f RA:ra, ximm:ximm, RC:rc (5148)", "assembly": "orl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "orl_s %0,%1,%2",
;       "orl %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "not included": [
;         { "_comment": "orl_s h:h, PCL:pcl, ximm:ximm (6591)", "assembly": "orl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "TODO:h", "op1": "FIPCL", "op2": "UXIMM" } },
;         { "_comment": "orl_s h:h, h:h, ximm:ximm (6590)", "assembly": "orl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "TODO:h", "op1": "TODO:h", "op2": "UXIMM" } }
;     ],
;     "found_matches": [
;
;     ],
;     "failed_for_operands": [
;
;     ]
;     }
;   }
; OUTPUT:ordi3
(define_insn "ordi3" [
    (set
      (match_operand:DI 0 "register_operand" "=q,r,r,r,r,r,r,r,r,r,r,r")
      (ior:DI
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,0,r,0,r,r,r,ULIMM,UXIMM")
        (match_operand:DI 2 "nonmemory_operand" "q,r,ULIMM,U06S0,UXIMM,U06S0,S12S0,r,ULIMM,UXIMM,r,r")))]
 "true" "@
  orl_s %0,%1,%2
  orl %0,%1,%2
  orl %0,%1,%2
  orl %0,%1,%2
  orl %0,%1,%2
  orl %0,%1,%2
  orl %0,%1,%2
  orl %0,%1,%2
  orl %0,%1,%2
  orl %0,%1,%2
  orl %0,%1,%2
  orl %0,%1,%2" [
    (set_attr "predicable" "no,yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "2,4,8,4,4,4,4,4,8,4,8,4")
    (set_attr "type" "orl,orl,orl,orl,orl,orl,orl,orl,orl,orl,orl,orl")]
)
; END:ordi3

; START:bswapsi2
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (bswap:SI @op1{mode=SI}))]",
;   "general_attributes":   {
;     "type": "swape"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "swape.f b:R6, u6:uimm6 (3372)", "assembly": "swape %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "swape.f b:R6, limm:limm (3371)", "assembly": "swape %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "swape.f b:R6, c:R6 (3370)", "assembly": "swape %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "swape_s %0,%1",
;       "swape %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:bswapsi2
(define_insn "bswapsi2" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r")
      (bswap:SI
        (match_operand:SI 1 "nonmemory_operand" "U06S0,ULIMM,r")))]
 "true" "@
  swape %0,%1
  swape %0,%1
  swape %0,%1" [
    (set_attr "predicable" "no,no,no")
    (set_attr "length" "4,8,4")
    (set_attr "type" "swape,swape,swape")]
)
; END:bswapsi2

; START:bswapdi2
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (bswap:DI @op1{mode=DI}))]",
;   "general_attributes":   {
;     "type": "swapel"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "ordered_constraints": [
;       { "_comment": "swapel.f RB:rb, u6:uimm6 (6372)", "assembly": "swapel %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "swapel.f RB:rb, limm:limm (6374)", "assembly": "swapel %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "swapel.f RB:rb, ximm:ximm (6376)", "assembly": "swapel %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM" } },
;       { "_comment": "swapel.f RB:rb, RC:rc (6370)", "assembly": "swapel %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "swapel_s %0,%1",
;       "swapel %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:bswapdi2
(define_insn "bswapdi2" [
    (set
      (match_operand:DI 0 "register_operand" "=r,r,r,r")
      (bswap:DI
        (match_operand:DI 1 "nonmemory_operand" "U06S0,ULIMM,UXIMM,r")))]
 "true" "@
  swapel %0,%1
  swapel %0,%1
  swapel %0,%1
  swapel %0,%1" [
    (set_attr "predicable" "no,no,no,no")
    (set_attr "length" "4,8,4,4")
    (set_attr "type" "swapel,swapel,swapel,swapel")]
)
; END:bswapdi2

; START:bsetsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (ior:SI @op1{mode=SI} (ashift:SI (const_int 1) @op2{mode=SI})))]",
;   "general_attributes":   {
;     "type": "bset"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], SImode) || register_operand (operands[2], SImode)",
;   "ordered_constraints": [
;       { "_comment": "bset_s b:R3, b:R3, u5:uimm5 (501)", "assembly": "bset_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "U05S0" } },
;       { "_comment": "bset.cc.f b:R6, b:R6, c:R6 (495)", "assembly": "bset %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "bset.cc.f b:R6, b:R6, limm:limm (496)", "assembly": "bset %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "bset.cc.f b:R6, b:R6, u6:uimm6 (499)", "assembly": "bset %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "bset.f a:R6, b:R6, u6:uimm6 (489)", "assembly": "bset %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "bset.f b:R6, b:R6, s12:simm12 (493)", "assembly": "bset %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "bset.f a:R6, b:R6, limm:limm (483)", "assembly": "bset %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "bset.f a:R6, limm:limm, c:R6 (482)", "assembly": "bset %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "bset.f a:R6, b:R6, c:R6 (481)", "assembly": "bset %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "bset_s %0,%1,%2",
;       "bset %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:bsetsi3
(define_insn "bsetsi3" [
    (set
      (match_operand:SI 0 "register_operand" "=q,r,r,r,r,r,r,r,r")
      (ior:SI
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,0,r,0,r,ULIMM,r")
        (ashift:SI
          (const_int 1)
          (match_operand:SI 2 "nonmemory_operand" "U05S0,r,ULIMM,U06S0,U06S0,S12S0,ULIMM,r,r"))))]
 "true" "@
  bset_s %0,%1,%2
  bset %0,%1,%2
  bset %0,%1,%2
  bset %0,%1,%2
  bset %0,%1,%2
  bset %0,%1,%2
  bset %0,%1,%2
  bset %0,%1,%2
  bset %0,%1,%2" [
    (set_attr "predicable" "no,yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "2,4,8,4,4,4,8,8,4")
    (set_attr "type" "bset,bset,bset,bset,bset,bset,bset,bset,bset")]
)
; END:bsetsi3

; START:bsetdi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (ior:DI @op1{mode=DI} (ashift:DI (const_int 1) @op2{mode=DI})))]",
;   "general_attributes":   {
;     "type": "bsetl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], DImode) || register_operand (operands[2], DImode)",
;   "ordered_constraints": [
;       { "_comment": "bsetl.cc.f RB:rb, RB:rb, RC:rc (5328)", "assembly": "bsetl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "bsetl.cc.f RB:rb, RB:rb, limm:limm (5338)", "assembly": "bsetl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "bsetl.cc.f RB:rb, RB:rb, u6:uimm6 (5331)", "assembly": "bsetl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "bsetl.cc.f RB:rb, RB:rb, ximm:ximm (5351)", "assembly": "bsetl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "bsetl.f RA:ra, RB:rb, u6:uimm6 (5329)", "assembly": "bsetl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "bsetl.f RB:rb, RB:rb, s12:simm12 (5332)", "assembly": "bsetl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "bsetl.f RA:ra, RB:rb, limm:limm (5334)", "assembly": "bsetl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "bsetl.f RA:ra, RB:rb, ximm:ximm (5347)", "assembly": "bsetl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "bsetl.f RA:ra, limm:limm, RC:rc (5333)", "assembly": "bsetl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "bsetl.f RA:ra, ximm:ximm, RC:rc (5346)", "assembly": "bsetl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "bsetl.f RA:ra, RB:rb, RC:rc (5326)", "assembly": "bsetl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "bsetl_s %0,%1,%2",
;       "bsetl %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:bsetdi3
(define_insn "bsetdi3" [
    (set
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r")
      (ior:DI
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM,UXIMM,r")
        (ashift:DI
          (const_int 1)
          (match_operand:DI 2 "nonmemory_operand" "r,ULIMM,U06S0,UXIMM,U06S0,S12S0,ULIMM,UXIMM,r,r,r"))))]
 "true" "@
  bsetl %0,%1,%2
  bsetl %0,%1,%2
  bsetl %0,%1,%2
  bsetl %0,%1,%2
  bsetl %0,%1,%2
  bsetl %0,%1,%2
  bsetl %0,%1,%2
  bsetl %0,%1,%2
  bsetl %0,%1,%2
  bsetl %0,%1,%2
  bsetl %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "bsetl,bsetl,bsetl,bsetl,bsetl,bsetl,bsetl,bsetl,bsetl,bsetl,bsetl")]
)
; END:bsetdi3

; START:bxorsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (xor:SI @op1{mode=SI} (ashift:SI (const_int 1) @op2{mode=SI})))]",
;   "general_attributes":   {
;     "type": "bxor"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], SImode) || register_operand (operands[2], SImode)",
;   "ordered_constraints": [
;       { "_comment": "bxor.cc.f b:R6, b:R6, c:R6 (531)", "assembly": "bxor %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "bxor.cc.f b:R6, b:R6, limm:limm (532)", "assembly": "bxor %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "bxor.cc.f b:R6, b:R6, u6:uimm6 (535)", "assembly": "bxor %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "bxor.f a:R6, b:R6, u6:uimm6 (525)", "assembly": "bxor %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "bxor.f b:R6, b:R6, s12:simm12 (529)", "assembly": "bxor %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "bxor.f a:R6, b:R6, limm:limm (519)", "assembly": "bxor %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "bxor.f a:R6, limm:limm, c:R6 (518)", "assembly": "bxor %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "bxor.f a:R6, b:R6, c:R6 (517)", "assembly": "bxor %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "bxor_s %0,%1,%2",
;       "bxor %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:bxorsi3
(define_insn "bxorsi3" [
    (set
      (match_operand:SI 0 "register_operand" "=r,r,r,r,r,r,r,r")
      (xor:SI
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,r,0,r,ULIMM,r")
        (ashift:SI
          (const_int 1)
          (match_operand:SI 2 "nonmemory_operand" "r,ULIMM,U06S0,U06S0,S12S0,ULIMM,r,r"))))]
 "true" "@
  bxor %0,%1,%2
  bxor %0,%1,%2
  bxor %0,%1,%2
  bxor %0,%1,%2
  bxor %0,%1,%2
  bxor %0,%1,%2
  bxor %0,%1,%2
  bxor %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,8,8,4")
    (set_attr "type" "bxor,bxor,bxor,bxor,bxor,bxor,bxor,bxor")]
)
; END:bxorsi3

; START:bxordi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (xor:DI @op1{mode=DI} (ashift:DI (const_int 1) @op2{mode=DI})))]",
;   "general_attributes":   {
;     "type": "bxorl"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], DImode) || register_operand (operands[2], DImode)",
;   "ordered_constraints": [
;       { "_comment": "bxorl.cc.f RB:rb, RB:rb, RC:rc (5394)", "assembly": "bxorl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "bxorl.cc.f RB:rb, RB:rb, limm:limm (5404)", "assembly": "bxorl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "bxorl.cc.f RB:rb, RB:rb, u6:uimm6 (5397)", "assembly": "bxorl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "bxorl.cc.f RB:rb, RB:rb, ximm:ximm (5417)", "assembly": "bxorl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "bxorl.f RA:ra, RB:rb, u6:uimm6 (5395)", "assembly": "bxorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "bxorl.f RB:rb, RB:rb, s12:simm12 (5398)", "assembly": "bxorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "bxorl.f RA:ra, RB:rb, limm:limm (5400)", "assembly": "bxorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "bxorl.f RA:ra, RB:rb, ximm:ximm (5413)", "assembly": "bxorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "bxorl.f RA:ra, limm:limm, RC:rc (5399)", "assembly": "bxorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "bxorl.f RA:ra, ximm:ximm, RC:rc (5412)", "assembly": "bxorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "bxorl.f RA:ra, RB:rb, RC:rc (5392)", "assembly": "bxorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "bxorl_s %0,%1,%2",
;       "bxorl %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:bxordi3
(define_insn "bxordi3" [
    (set
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r")
      (xor:DI
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM,UXIMM,r")
        (ashift:DI
          (const_int 1)
          (match_operand:DI 2 "nonmemory_operand" "r,ULIMM,U06S0,UXIMM,U06S0,S12S0,ULIMM,UXIMM,r,r,r"))))]
 "true" "@
  bxorl %0,%1,%2
  bxorl %0,%1,%2
  bxorl %0,%1,%2
  bxorl %0,%1,%2
  bxorl %0,%1,%2
  bxorl %0,%1,%2
  bxorl %0,%1,%2
  bxorl %0,%1,%2
  bxorl %0,%1,%2
  bxorl %0,%1,%2
  bxorl %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "bxorl,bxorl,bxorl,bxorl,bxorl,bxorl,bxorl,bxorl,bxorl,bxorl,bxorl")]
)
; END:bxordi3

; START:bmsksi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (and:SI @op1{mode=SI} (plus:SI (ashift:SI (const_int 1) (plus:SI @op2{mode=SI} (const_int 1))) (const_int -1))))]",
;   "general_attributes":   {
;     "type": "bmsk"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], SImode) || register_operand (operands[2], SImode)",
;   "ordered_constraints": [
;       { "_comment": "bmsk_s b:R3, b:R3, u5:uimm5 (420)", "assembly": "bmsk_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "U05S0" } },
;       { "_comment": "bmsk.cc.f b:R6, b:R6, c:R6 (414)", "assembly": "bmsk %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "bmsk.cc.f b:R6, b:R6, limm:limm (415)", "assembly": "bmsk %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "bmsk.cc.f b:R6, b:R6, u6:uimm6 (418)", "assembly": "bmsk %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "bmsk.f a:R6, b:R6, u6:uimm6 (408)", "assembly": "bmsk %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "bmsk.f b:R6, b:R6, s12:simm12 (412)", "assembly": "bmsk %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "bmsk.f a:R6, b:R6, limm:limm (402)", "assembly": "bmsk %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "bmsk.f a:R6, limm:limm, c:R6 (401)", "assembly": "bmsk %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "bmsk.f a:R6, b:R6, c:R6 (400)", "assembly": "bmsk %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "bmsk_s %0,%1,%2",
;       "bmsk %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:bmsksi3
(define_insn "bmsksi3" [
    (set
      (match_operand:SI 0 "register_operand" "=q,r,r,r,r,r,r,r,r")
      (and:SI
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,0,r,0,r,ULIMM,r")
        (plus:SI
          (ashift:SI
            (const_int 1)
            (plus:SI
              (match_operand:SI 2 "nonmemory_operand" "U05S0,r,ULIMM,U06S0,U06S0,S12S0,ULIMM,r,r")
              (const_int 1)))
          (const_int -1))))]
 "true" "@
  bmsk_s %0,%1,%2
  bmsk %0,%1,%2
  bmsk %0,%1,%2
  bmsk %0,%1,%2
  bmsk %0,%1,%2
  bmsk %0,%1,%2
  bmsk %0,%1,%2
  bmsk %0,%1,%2
  bmsk %0,%1,%2" [
    (set_attr "predicable" "no,yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "2,4,8,4,4,4,8,8,4")
    (set_attr "type" "bmsk,bmsk,bmsk,bmsk,bmsk,bmsk,bmsk,bmsk,bmsk")]
)
; END:bmsksi3

; START:bmskdi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (and:DI @op1{mode=DI} (plus:DI (ashift:DI (const_int 1) (plus:DI @op2{mode=DI} (const_int 1))) (const_int -1))))]",
;   "general_attributes":   {
;     "type": "bmsk"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand",
;     "op2": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], DImode) || register_operand (operands[2], DImode)",
;   "ordered_constraints": [
;       { "_comment": "bmskl.cc.f RB:rb, RB:rb, u6:uimm6 (5430)", "assembly": "bmskl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "bmskl.cc.f RB:rb, RB:rb, limm:limm (5437)", "assembly": "bmskl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "bmskl.cc.f RB:rb, RB:rb, ximm:ximm (5450)", "assembly": "bmskl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "bmskl.cc.f RB:rb, RB:rb, RC:rc (5427)", "assembly": "bmskl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "bmskl.f RA:ra, RB:rb, u6:uimm6 (5428)", "assembly": "bmskl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "bmskl.f RB:rb, RB:rb, s12:simm12 (5431)", "assembly": "bmskl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "bmskl.f RA:ra, RB:rb, limm:limm (5433)", "assembly": "bmskl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "bmskl.f RA:ra, RB:rb, ximm:ximm (5446)", "assembly": "bmskl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "bmskl.f RA:ra, limm:limm, RC:rc (5432)", "assembly": "bmskl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "bmskl.f RA:ra, ximm:ximm, RC:rc (5445)", "assembly": "bmskl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "bmskl.f RA:ra, RB:rb, RC:rc (5425)", "assembly": "bmskl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "bmskl_s %0,%1,%2",
;       "bmskl %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;
;     ]
;     }
;   }
; OUTPUT:bmskdi3
(define_insn "bmskdi3" [
    (set
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r")
      (and:DI
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM,UXIMM,r")
        (plus:DI
          (ashift:DI
            (const_int 1)
            (plus:DI
              (match_operand:DI 2 "nonmemory_operand" "U06S0,ULIMM,UXIMM,r,U06S0,S12S0,ULIMM,UXIMM,r,r,r")
              (const_int 1)))
          (const_int -1))))]
 "true" "@
  bmskl %0,%1,%2
  bmskl %0,%1,%2
  bmskl %0,%1,%2
  bmskl %0,%1,%2
  bmskl %0,%1,%2
  bmskl %0,%1,%2
  bmskl %0,%1,%2
  bmskl %0,%1,%2
  bmskl %0,%1,%2
  bmskl %0,%1,%2
  bmskl %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "bmsk,bmsk,bmsk,bmsk,bmsk,bmsk,bmsk,bmsk,bmsk,bmsk,bmsk")]
)
; END:bmskdi3
