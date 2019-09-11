; HEADER FOR THE FILE


; TODO: addsi3: add1, add2, add3 were not included.
; START:addsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (plus:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "add"
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
;       { "_comment": "add_s c:R3, b:R3, u3:uimm3 (67)", "assembly": "add_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q", "op2": "U03S0" } },
;       { "_comment": "add_s b:R3, b:R3, u7:uimm7 (66)", "assembly": "add_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q", "op2": "U07S0" } },
;       { "_comment": "add_s a:R3, b:R3, c:R3 (60)", "assembly": "add_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q", "op2": "q" } },
;       { "_comment": "add_s b:R3, b:R3, limm:limm (64)", "assembly": "add_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "6" }, "constraints":   { "op0": "q", "op1": "q", "op2": "ULIMM" } },
;       { "_comment": "add.cc.f b:R6, b:R6, c:R6 (54)", "assembly": "add %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } },
;       { "_comment": "add.cc.f b:R6, b:R6, limm:limm (55)", "assembly": "add %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "add.cc.f b:R6, b:R6, u6:uimm6 (58)", "assembly": "add %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "add.f a:R6, b:R6, u6:uimm6 (48)", "assembly": "add %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "add.f b:R6, b:R6, s12:simm12 (52)", "assembly": "add %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "S12S0" } },
;       { "_comment": "add.f a:R6, b:R6, c:R6 (40)", "assembly": "add %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } },
;       { "_comment": "add.f a:R6, limm:limm, c:R6 (41)", "assembly": "add %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "add.f a:R6, limm:limm, limm:limm (43)", "assembly": "add %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "ULIMM" } },
;       { "_comment": "add.f a:R6, limm:limm, u6:uimm6 (49)", "assembly": "add %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "U06S0" } },
;       { "_comment": "add.f a:R6, b:R6, limm:limm (42)", "assembly": "add %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "add %0,%1,%2",
;       "add_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "not included": [
;         { "_comment": "add_s R0:r0, b:R3, u6:uimm6 (70)", "assembly": "add_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "TODO:R0", "op1": "q", "op2": "U06S0" } },
;         { "_comment": "add_s R1:r1, b:R3, u6:uimm6 (71)", "assembly": "add_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "TODO:R1", "op1": "q", "op2": "U06S0" } },
;         { "_comment": "add_s b:R3, b:R3, h:h (61)", "assembly": "add_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q", "op2": "TODO:h" } },
;         { "_comment": "add_s h:h, h:h, s3:simm3 (62)", "assembly": "add_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "TODO:h", "op1": "TODO:h", "op2": "S03S0" } }
;     ]
;     }
;   }
; OUTPUT:addsi3
(define_insn "addsi3" [
    (set 
      (match_operand:SI 0 "register_operand" "=q,q,q,q,r,r,r,r,r,r,r,r,r,r") 
      (plus:SI 
        (match_operand:SI 1 "nonmemory_operand" "q,q,q,q,r,r,r,r,r,r,ULIMM,ULIMM,ULIMM,r") 
        (match_operand:SI 2 "nonmemory_operand" "U03S0,U07S0,q,ULIMM,r,ULIMM,U06S0,U06S0,S12S0,r,r,ULIMM,U06S0,ULIMM")))]
 "true" "@
  add_s %0,%1,%2
  add_s %0,%1,%2
  add_s %0,%1,%2
  add_s %0,%1,%2
  add %0,%1,%2
  add %0,%1,%2
  add %0,%1,%2
  add %0,%1,%2
  add %0,%1,%2
  add %0,%1,%2
  add %0,%1,%2
  add %0,%1,%2
  add %0,%1,%2
  add %0,%1,%2" [
    (set_attr "predicable" "no,no,no,no,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "2,2,2,6,4,8,4,4,4,4,8,8,8,8")
    (set_attr "type" "add,add,add,add,add,add,add,add,add,add,add,add,add,add")]
)
; END:addsi3

; START:adddi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (minus:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "addl"
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
;       { "_comment": "addl_s R0:r0, GP:gp, s11:simm11 (6584)", "assembly": "addl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "SR_R0", "op1": "SR_GP", "op2": "S11S0" } },
;       { "_comment": "addl_s SP:sp, SP:sp, u9:uimm9 (6575)", "assembly": "addl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "SR_SP", "op1": "0", "op2": "U09S0" } },
;       { "_comment": "addl_s b:R3, SP:sp, u7:uimm7 (6574)", "assembly": "addl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "SR_SP", "op2": "U07S0" } },
;       { "_comment": "addl_s b:R3, b:R3, c:R3 (6585)", "assembly": "addl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "q" } },
;       { "_comment": "addl.cc.f RB:rb, RB:rb, u6:uimm6 (4968)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "addl.cc.f RB:rb, RB:rb, limm:limm (4975)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "addl.cc.f RB:rb, RB:rb, ximm:ximm (4988)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "addl.cc.f RB:rb, RB:rb, RC:rc (4965)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "addl.f RA:ra, RB:rb, u6:uimm6 (4966)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "addl.f RB:rb, RB:rb, s12:simm12 (4969)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "S12S0" } },
;       { "_comment": "addl.f RA:ra, limm:limm, u6:uimm6 (4976)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "U06S0" } },
;       { "_comment": "addl.f RA:ra, ximm:ximm, u6:uimm6 (4989)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "U06S0" } },
;       { "_comment": "addl.f RA:ra, limm:limm, RC:rc (4970)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "addl.f RA:ra, ximm:ximm, RC:rc (4983)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "addl.f RA:ra, RB:rb, limm:limm (4971)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "addl.f RA:ra, RB:rb, ximm:ximm (4984)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "addl.f RA:ra, RB:rb, RC:rc (4963)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "addl %0,%1,%2",
;       "addl_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "not included": [
;         { "_comment": "addl_s h:h, PCL:pcl, ximm:ximm (6595)", "assembly": "addl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "TODO:h", "op1": "SRPCL", "op2": "UXIMM" } },
;         { "_comment": "addl_s h:h, h:h, ximm:ximm (6594)", "assembly": "addl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "TODO:h", "op1": "TODO:h", "op2": "UXIMM" } },
;         { "_comment": "addl.f RA:ra, limm:limm, limm:limm (4980)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "ULIMM" } },
;         { "_comment": "addl.f RA:ra, ximm:ximm, ximm:ximm (4993)", "assembly": "addl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "UXIMM" } }
;     ]
;     }
;   }
; OUTPUT:adddi3
(define_insn "adddi3" [
    (set 
      (match_operand:DI 0 "register_operand" "=SR_R0,SR_SP,q,q,r,r,r,r,r,r,r,r,r,r,r,r,r") 
      (minus:DI 
        (match_operand:DI 1 "nonmemory_operand" "SR_GP,0,SR_SP,0,0,0,0,0,r,r,ULIMM,UXIMM,ULIMM,UXIMM,r,r,r") 
        (match_operand:DI 2 "nonmemory_operand" "S11S0,U09S0,U07S0,q,U06S0,ULIMM,UXIMM,r,U06S0,S12S0,U06S0,U06S0,r,r,ULIMM,UXIMM,r")))]
 "true" "@
  addl_s %0,%1,%2
  addl_s %0,%1,%2
  addl_s %0,%1,%2
  addl_s %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2
  addl %0,%1,%2" [
    (set_attr "predicable" "no,no,no,no,yes,yes,yes,yes,no,no,no,no,no,no,no,no,no")
    (set_attr "length" "2,2,2,2,4,8,4,4,4,4,8,4,8,4,8,4,4")
    (set_attr "type" "addl,addl,addl,addl,addl,addl,addl,addl,addl,addl,addl,addl,addl,addl,addl,addl,addl")]
)
; END:adddi3

; START:subsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (minus:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "sub"
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
;       { "_comment": "sub_s b:R3, b:R3, c:R3 (3279)", "assembly": "sub_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "q" } },
;       { "_comment": "sub_s c:R3, b:R3, u3:uimm3 (3277)", "assembly": "sub_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q", "op2": "U03S0" } },
;       { "_comment": "sub_s b:R3, b:R3, u5:uimm5 (3280)", "assembly": "sub_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "U05S0" } },
;       { "_comment": "sub_s a:R3, b:R3, c:R3 (3282)", "assembly": "sub_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q", "op2": "q" } },
;       { "_comment": "sub.cc.f b:R6, b:R6, u6:uimm6 (3275)", "assembly": "sub %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "sub.cc.f b:R6, b:R6, limm:limm (3272)", "assembly": "sub %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "sub.cc.f b:R6, b:R6, c:R6 (3271)", "assembly": "sub %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "sub.f a:R6, b:R6, limm:limm (3259)", "assembly": "sub %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "sub.f a:R6, b:R6, u6:uimm6 (3265)", "assembly": "sub %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "sub.f b:R6, b:R6, s12:simm12 (3269)", "assembly": "sub %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "sub.f a:R6, limm:limm, c:R6 (3258)", "assembly": "sub %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "sub.f a:R6, limm:limm, u6:uimm6 (3266)", "assembly": "sub %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "U06S0" } },
;       { "_comment": "sub.f a:R6, b:R6, c:R6 (3257)", "assembly": "sub %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "sub %0,%1,%2",
;       "sub_s %0,%1,%2",
;       "sub1 %0,%1,%2",
;       "sub2 %0,%1,%2",
;       "sub3 %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "not included": [
;         { "_comment": "sub_s.NE b:R3, b:R3, b:R3 (3278)", "assembly": "sub_s %0,%1,%2", "attributes":   { "predicable": "yes", "length": "2" }, "constraints":   { "op0": "q", "op1": "q", "op2": "q" } },
;         { "_comment": "sub.f a:R6, limm:limm, limm:limm (3260)", "assembly": "sub %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "ULIMM" } }
;     ]
;     }
;   }
; END:subsi3

; START:subdi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (minus:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "sub"
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
;       { "_comment": "subl_s SP:sp, SP:sp, u9:uimm9 (6576)", "assembly": "subl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "SR_SP", "op1": "0", "op2": "U09S0" } },
;       { "_comment": "subl_s b:R3, b:R3, c:R3 (6586)", "assembly": "subl_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "q" } },
;       { "_comment": "subl.cc.f RB:rb, RB:rb, RC:rc (5031)", "assembly": "subl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "subl.cc.f RB:rb, RB:rb, limm:limm (5041)", "assembly": "subl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "subl.cc.f RB:rb, RB:rb, u6:uimm6 (5034)", "assembly": "subl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "subl.cc.f RB:rb, RB:rb, ximm:ximm (5054)", "assembly": "subl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "subl.f RA:ra, RB:rb, u6:uimm6 (5032)", "assembly": "subl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "subl.f RB:rb, RB:rb, s12:simm12 (5035)", "assembly": "subl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "subl.f RA:ra, RB:rb, limm:limm (5037)", "assembly": "subl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "subl.f RA:ra, RB:rb, ximm:ximm (5050)", "assembly": "subl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "subl.f RA:ra, limm:limm, RC:rc (5036)", "assembly": "subl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "subl.f RA:ra, ximm:ximm, RC:rc (5049)", "assembly": "subl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "subl.f RA:ra, RB:rb, RC:rc (5029)", "assembly": "subl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "subl %0,%1,%2",
;       "subl_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:subdi3
(define_insn "subdi3" [
    (set 
      (match_operand:DI 0 "register_operand" "=SR_SP,q,r,r,r,r,r,r,r,r,r,r,r") 
      (minus:DI 
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,0,0,r,0,r,r,ULIMM,UXIMM,r") 
        (match_operand:DI 2 "nonmemory_operand" "U09S0,q,r,ULIMM,U06S0,UXIMM,U06S0,S12S0,ULIMM,UXIMM,r,r,r")))]
 "true" "@
  subl_s %0,%1,%2
  subl_s %0,%1,%2
  subl %0,%1,%2
  subl %0,%1,%2
  subl %0,%1,%2
  subl %0,%1,%2
  subl %0,%1,%2
  subl %0,%1,%2
  subl %0,%1,%2
  subl %0,%1,%2
  subl %0,%1,%2
  subl %0,%1,%2
  subl %0,%1,%2" [
    (set_attr "predicable" "no,no,yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "2,2,4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "sub,sub,sub,sub,sub,sub,sub,sub,sub,sub,sub,sub,sub")]
)
; END:subdi3

; START:abssi2
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (abs:SI @op1{mode=SI}))]",
;   "general_attributes":   {
;     "type": "abs"
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
;       { "_comment": "abs_s b:R3, c:R3 (7)", "assembly": "abs_s %0,%1", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q" } },
;       { "_comment": "abs.f b:R6, u6:uimm6 (5)", "assembly": "abs %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "abs.f b:R6, limm:limm (2)", "assembly": "abs %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "abs.f b:R6, c:R6 (1)", "assembly": "abs %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "abs %0,%1",
;       "abs_s %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:abssi2
(define_insn "abssi2" [
    (set 
      (match_operand:SI 0 "register_operand" "=q,r,r,r") 
      (abs:SI 
        (match_operand:SI 1 "nonmemory_operand" "q,U06S0,ULIMM,r")))]
 "true" "@
  abs_s %0,%1
  abs %0,%1
  abs %0,%1
  abs %0,%1" [
    (set_attr "predicable" "no,no,no,no")
    (set_attr "length" "2,4,8,4")
    (set_attr "type" "abs,abs,abs,abs")]
)
; END:abssi2


; START:absdi2
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (abs:DI @op1{mode=DI}))]",
;   "general_attributes":   {
;     "type": "abs"
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
;       { "_comment": "absl.f RB:rb, u6:uimm6 (6300)", "assembly": "absl %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "U06S0" } },
;       { "_comment": "absl.f RB:rb, limm:limm (6302)", "assembly": "absl %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "absl.f RB:rb, ximm:ximm (6304)", "assembly": "absl %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM" } },
;       { "_comment": "absl.f RB:rb, RC:rc (6298)", "assembly": "absl %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "absl %0,%1",
;       "absl_s %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:absdi2
(define_insn "absdi2" [
    (set 
      (match_operand:DI 0 "register_operand" "=r,r,r,r") 
      (abs:DI 
        (match_operand:DI 1 "nonmemory_operand" "U06S0,ULIMM,UXIMM,r")))]
 "true" "@
  absl %0,%1
  absl %0,%1
  absl %0,%1
  absl %0,%1" [
    (set_attr "predicable" "no,no,no,no")
    (set_attr "length" "4,8,4,4")
    (set_attr "type" "abs,abs,abs,abs")]
)
; END:absdi2


; START:negsi2
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (neg:SI @op1{mode=SI}))]",
;   "general_attributes":   {
;     "type": "neg"
;     },
;   "operand_predicates":   {
;     "op0": "register_operand",
;     "op1": "nonmemory_operand"
;     },
;   "constraint_predecessor":   {
;     "op0": "="
;     },
;   "pattern_predicate": "true",
;   "to_become_pattern_predicate": "register_operand (operands[1], SImode)",
;   "ordered_constraints": [
;       { "_comment": "neg_s b:R3, c:R3 (2495)", "assembly": "neg_s %0,%1", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "q" } },
;       { "_comment": "neg.cc.f b:R6, b:R6 (2493)", "assembly": "neg %0,%1", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0" } },
;       { "_comment": "neg.f a:R6, limm:limm (2492)", "assembly": "neg %0,%1", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM" } },
;       { "_comment": "neg.f a:R6, b:R6 (2491)", "assembly": "neg %0,%1", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "neg %0,%1",
;       "neg_s %0,%1"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:negsi2
(define_insn "negsi2" [
    (set 
      (match_operand:SI 0 "register_operand" "=q,r,r,r") 
      (neg:SI 
        (match_operand:SI 1 "nonmemory_operand" "q,0,ULIMM,r")))]
 "true" "@
  neg_s %0,%1
  neg %0,%1
  neg %0,%1
  neg %0,%1" [
    (set_attr "predicable" "no,yes,no,no")
    (set_attr "length" "2,4,8,4")
    (set_attr "type" "neg,neg,neg,neg")]
)
; END:negsi2

; START:divsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (div:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "div"
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
;       { "_comment": "div.cc.f b:R6, b:R6, c:R6 (780)", "assembly": "div %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "div.cc.f b:R6, b:R6, u6:uimm6 (784)", "assembly": "div %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "div.cc.f b:R6, b:R6, limm:limm (781)", "assembly": "div %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "div.f b:R6, b:R6, s12:simm12 (778)", "assembly": "div %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "div.f a:R6, b:R6, u6:uimm6 (774)", "assembly": "div %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "div.f a:R6, b:R6, limm:limm (768)", "assembly": "div %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "div.f a:R6, limm:limm, c:R6 (767)", "assembly": "div %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "div.f a:R6, b:R6, c:R6 (766)", "assembly": "div %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "div %0,%1,%2",
;       "div_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:divsi3
(define_insn "divsi3" [
    (set 
      (match_operand:SI 0 "register_operand" "=r,r,r,r,r,r,r,r") 
      (div:SI 
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,0,r,r,ULIMM,r") 
        (match_operand:SI 2 "nonmemory_operand" "r,U06S0,ULIMM,S12S0,U06S0,ULIMM,r,r")))]
 "true" "@
  div %0,%1,%2
  div %0,%1,%2
  div %0,%1,%2
  div %0,%1,%2
  div %0,%1,%2
  div %0,%1,%2
  div %0,%1,%2
  div %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "4,4,8,4,4,8,8,4")
    (set_attr "type" "div,div,div,div,div,div,div,div")]
)
; END:divsi3

; START:divdi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (div:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "div"
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
;       { "_comment": "divl.cc.f RB:rb, RB:rb, u6:uimm6 (5760)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "divl.cc.f RB:rb, RB:rb, limm:limm (5767)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "divl.cc.f RB:rb, RB:rb, ximm:ximm (5780)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "divl.cc.f RB:rb, RB:rb, RC:rc (5757)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "divl.f RA:ra, RB:rb, u6:uimm6 (5758)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "divl.f RB:rb, RB:rb, s12:simm12 (5761)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "divl.f RA:ra, RB:rb, limm:limm (5763)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "divl.f RA:ra, RB:rb, ximm:ximm (5776)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "divl.f RA:ra, limm:limm, RC:rc (5762)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "divl.f RA:ra, ximm:ximm, RC:rc (5775)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "divl.f RA:ra, RB:rb, RC:rc (5755)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "divl %0,%1,%2",
;       "divl_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:divdi3
(define_insn "divdi3" [
    (set 
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r") 
      (div:DI 
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM,UXIMM,r") 
        (match_operand:DI 2 "nonmemory_operand" "U06S0,ULIMM,UXIMM,r,U06S0,S12S0,ULIMM,UXIMM,r,r,r")))]
 "true" "@
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "div,div,div,div,div,div,div,div,div,div,div")]
)
; END:divdi3

; START:udivsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (udiv:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "udiv"
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
;       { "_comment": "divu.cc.f b:R6, b:R6, u6:uimm6 (804)", "assembly": "divu %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "divu.cc.f b:R6, b:R6, limm:limm (801)", "assembly": "divu %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "divu.cc.f b:R6, b:R6, c:R6 (800)", "assembly": "divu %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "divu.f a:R6, b:R6, u6:uimm6 (794)", "assembly": "divu %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "divu.f b:R6, b:R6, s12:simm12 (798)", "assembly": "divu %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "divu.f a:R6, b:R6, limm:limm (788)", "assembly": "divu %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "divu.f a:R6, limm:limm, c:R6 (787)", "assembly": "divu %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "divu.f a:R6, limm:limm, limm:limm (789)", "assembly": "divu %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "ULIMM" } },
;       { "_comment": "divu.f a:R6, limm:limm, u6:uimm6 (795)", "assembly": "divu %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "U06S0" } },
;       { "_comment": "divu.f a:R6, b:R6, c:R6 (786)", "assembly": "divu %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "divu %0,%1,%2",
;       "divu_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:udivsi3
(define_insn "udivsi3" [
    (set 
      (match_operand:SI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r") 
      (udiv:SI 
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,r,0,r,ULIMM,ULIMM,ULIMM,r") 
        (match_operand:SI 2 "nonmemory_operand" "U06S0,ULIMM,r,U06S0,S12S0,ULIMM,r,ULIMM,U06S0,r")))]
 "true" "@
  divu %0,%1,%2
  divu %0,%1,%2
  divu %0,%1,%2
  divu %0,%1,%2
  divu %0,%1,%2
  divu %0,%1,%2
  divu %0,%1,%2
  divu %0,%1,%2
  divu %0,%1,%2
  divu %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,8,8,8,8,4")
    (set_attr "type" "udiv,udiv,udiv,udiv,udiv,udiv,udiv,udiv,udiv,udiv")]
)
; END:udivsi3

; START:udivdi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (udiv:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "udivl"
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
;       { "_comment": "divl.cc.f RB:rb, RB:rb, u6:uimm6 (5760)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "divl.cc.f RB:rb, RB:rb, limm:limm (5767)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "divl.cc.f RB:rb, RB:rb, ximm:ximm (5780)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "divl.cc.f RB:rb, RB:rb, RC:rc (5757)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "divl.f RA:ra, RB:rb, u6:uimm6 (5758)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "divl.f RB:rb, RB:rb, s12:simm12 (5761)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "divl.f RA:ra, RB:rb, limm:limm (5763)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "divl.f RA:ra, RB:rb, ximm:ximm (5776)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "divl.f RA:ra, limm:limm, RC:rc (5762)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "divl.f RA:ra, ximm:ximm, RC:rc (5775)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "divl.f RA:ra, RB:rb, RC:rc (5755)", "assembly": "divl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "divul %0,%1,%2",
;       "divul_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:udivdi3
(define_insn "udivdi3" [
    (set 
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r") 
      (udiv:DI 
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM,UXIMM,r") 
        (match_operand:DI 2 "nonmemory_operand" "U06S0,ULIMM,UXIMM,r,U06S0,S12S0,ULIMM,UXIMM,r,r,r")))]
 "true" "@
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2
  divl %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "udivl,udivl,udivl,udivl,udivl,udivl,udivl,udivl,udivl,udivl,udivl")]
)
; END:udivdi3

; START:smaxsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (smax:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "max"
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
;       { "_comment": "max.cc.f b:R6, b:R6, u6:uimm6 (2043)", "assembly": "max %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "max.cc.f b:R6, b:R6, limm:limm (2040)", "assembly": "max %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "max.cc.f b:R6, b:R6, c:R6 (2039)", "assembly": "max %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "max.f a:R6, b:R6, u6:uimm6 (2033)", "assembly": "max %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "max.f b:R6, b:R6, s12:simm12 (2037)", "assembly": "max %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "max.f a:R6, b:R6, limm:limm (2027)", "assembly": "max %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "max.f a:R6, limm:limm, c:R6 (2026)", "assembly": "max %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "max.f a:R6, b:R6, c:R6 (2025)", "assembly": "max %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "max %0,%1,%2",
;       "max_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:smaxsi3
(define_insn "smaxsi3" [
    (set 
      (match_operand:SI 0 "register_operand" "=r,r,r,r,r,r,r,r") 
      (smax:SI 
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,r,0,r,ULIMM,r") 
        (match_operand:SI 2 "nonmemory_operand" "U06S0,ULIMM,r,U06S0,S12S0,ULIMM,r,r")))]
 "true" "@
  max %0,%1,%2
  max %0,%1,%2
  max %0,%1,%2
  max %0,%1,%2
  max %0,%1,%2
  max %0,%1,%2
  max %0,%1,%2
  max %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,8,8,4")
    (set_attr "type" "max,max,max,max,max,max,max,max")]
)
; END:smaxsi3

; START:smaxdi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (smax:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "maxl"
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
;       { "_comment": "maxl.cc.f RB:rb, RB:rb, u6:uimm6 (5232)", "assembly": "maxl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "maxl.cc.f RB:rb, RB:rb, limm:limm (5239)", "assembly": "maxl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "maxl.cc.f RB:rb, RB:rb, ximm:ximm (5252)", "assembly": "maxl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "maxl.cc.f RB:rb, RB:rb, RC:rc (5229)", "assembly": "maxl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "maxl.f RA:ra, RB:rb, u6:uimm6 (5230)", "assembly": "maxl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "maxl.f RB:rb, RB:rb, s12:simm12 (5233)", "assembly": "maxl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "maxl.f RA:ra, RB:rb, limm:limm (5235)", "assembly": "maxl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "maxl.f RA:ra, RB:rb, ximm:ximm (5248)", "assembly": "maxl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "maxl.f RA:ra, limm:limm, RC:rc (5234)", "assembly": "maxl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "maxl.f RA:ra, ximm:ximm, RC:rc (5247)", "assembly": "maxl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "maxl.f RA:ra, RB:rb, RC:rc (5227)", "assembly": "maxl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "maxl %0,%1,%2",
;       "maxl_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ],
;     "failed_for_operands": [
;         { "_comment": "maxl.aq RB:rb, RC:rc (6426)" },
;         { "_comment": "maxl.aq 0:0, RC:rc (6427)" },
;         { "_comment": "maxl.aq RB:rb, u6:uimm6 (6428)" },
;         { "_comment": "maxl.aq 0:0, u6:uimm6 (6429)" },
;         { "_comment": "maxl.aq RB:rb, limm:limm (6430)" },
;         { "_comment": "maxl.aq 0:0, limm:limm (6431)" },
;         { "_comment": "maxl.aq RB:rb, ximm:ximm (6432)" },
;         { "_comment": "maxl.aq 0:0, ximm:ximm (6433)" }
;     ]
;     }
;   }
; OUTPUT:smaxdi3
(define_insn "smaxdi3" [
    (set 
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r") 
      (smax:DI 
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM,UXIMM,r") 
        (match_operand:DI 2 "nonmemory_operand" "U06S0,ULIMM,UXIMM,r,U06S0,S12S0,ULIMM,UXIMM,r,r,r")))]
 "true" "@
  maxl %0,%1,%2
  maxl %0,%1,%2
  maxl %0,%1,%2
  maxl %0,%1,%2
  maxl %0,%1,%2
  maxl %0,%1,%2
  maxl %0,%1,%2
  maxl %0,%1,%2
  maxl %0,%1,%2
  maxl %0,%1,%2
  maxl %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "maxl,maxl,maxl,maxl,maxl,maxl,maxl,maxl,maxl,maxl,maxl")]
)
; END:smaxdi3


; START:sminsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (smin:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "min"
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
;       { "_comment": "min.cc.f b:R6, b:R6, c:R6 (2059)", "assembly": "min %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "min.cc.f b:R6, b:R6, limm:limm (2060)", "assembly": "min %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "min.cc.f b:R6, b:R6, u6:uimm6 (2063)", "assembly": "min %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "min.f a:R6, b:R6, u6:uimm6 (2053)", "assembly": "min %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "min.f b:R6, b:R6, s12:simm12 (2057)", "assembly": "min %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "min.f a:R6, b:R6, limm:limm (2047)", "assembly": "min %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "min.f a:R6, limm:limm, c:R6 (2046)", "assembly": "min %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "min.f a:R6, b:R6, c:R6 (2045)", "assembly": "min %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "min %0,%1,%2",
;       "min_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:sminsi3
(define_insn "sminsi3" [
    (set 
      (match_operand:SI 0 "register_operand" "=r,r,r,r,r,r,r,r") 
      (smin:SI 
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,r,0,r,ULIMM,r") 
        (match_operand:SI 2 "nonmemory_operand" "r,ULIMM,U06S0,U06S0,S12S0,ULIMM,r,r")))]
 "true" "@
  min %0,%1,%2
  min %0,%1,%2
  min %0,%1,%2
  min %0,%1,%2
  min %0,%1,%2
  min %0,%1,%2
  min %0,%1,%2
  min %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,8,8,4")
    (set_attr "type" "min,min,min,min,min,min,min,min")]
)
; END:sminsi3


; START:smindi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (smin:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "minl"
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
;       { "_comment": "minl.cc.f RB:rb, RB:rb, RC:rc (5262)", "assembly": "minl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "minl.cc.f RB:rb, RB:rb, limm:limm (5272)", "assembly": "minl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "minl.cc.f RB:rb, RB:rb, u6:uimm6 (5265)", "assembly": "minl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "minl.cc.f RB:rb, RB:rb, ximm:ximm (5285)", "assembly": "minl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "minl.f RA:ra, RB:rb, u6:uimm6 (5263)", "assembly": "minl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "minl.f RB:rb, RB:rb, s12:simm12 (5266)", "assembly": "minl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "minl.f RA:ra, RB:rb, limm:limm (5268)", "assembly": "minl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "minl.f RA:ra, RB:rb, ximm:ximm (5281)", "assembly": "minl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "minl.f RA:ra, limm:limm, RC:rc (5267)", "assembly": "minl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "minl.f RA:ra, ximm:ximm, RC:rc (5280)", "assembly": "minl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "minl.f RA:ra, RB:rb, RC:rc (5260)", "assembly": "minl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "minl %0,%1,%2",
;       "minl_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ],
;     "failed_for_operands": [
;         { "_comment": "minl.aq RB:rb, RC:rc (6410)" },
;         { "_comment": "minl.aq 0:0, RC:rc (6411)" },
;         { "_comment": "minl.aq RB:rb, u6:uimm6 (6412)" },
;         { "_comment": "minl.aq 0:0, u6:uimm6 (6413)" },
;         { "_comment": "minl.aq RB:rb, limm:limm (6414)" },
;         { "_comment": "minl.aq 0:0, limm:limm (6415)" },
;         { "_comment": "minl.aq RB:rb, ximm:ximm (6416)" },
;         { "_comment": "minl.aq 0:0, ximm:ximm (6417)" }
;     ]
;     }
;   }
; OUTPUT:smindi3
(define_insn "smindi3" [
    (set 
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r") 
      (smin:DI 
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM,UXIMM,r") 
        (match_operand:DI 2 "nonmemory_operand" "r,ULIMM,U06S0,UXIMM,U06S0,S12S0,ULIMM,UXIMM,r,r,r")))]
 "true" "@
  minl %0,%1,%2
  minl %0,%1,%2
  minl %0,%1,%2
  minl %0,%1,%2
  minl %0,%1,%2
  minl %0,%1,%2
  minl %0,%1,%2
  minl %0,%1,%2
  minl %0,%1,%2
  minl %0,%1,%2
  minl %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "minl,minl,minl,minl,minl,minl,minl,minl,minl,minl,minl")]
)
; END:smindi3

; START:modsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (mod:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "rem"
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
;       { "_comment": "rem.cc.f b:R6, b:R6, c:R6 (2882)", "assembly": "rem %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "rem.cc.f b:R6, b:R6, limm:limm (2883)", "assembly": "rem %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "rem.cc.f b:R6, b:R6, u6:uimm6 (2886)", "assembly": "rem %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "rem.f a:R6, b:R6, u6:uimm6 (2876)", "assembly": "rem %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "rem.f b:R6, b:R6, s12:simm12 (2880)", "assembly": "rem %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "rem.f a:R6, b:R6, limm:limm (2870)", "assembly": "rem %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "rem.f a:R6, limm:limm, c:R6 (2869)", "assembly": "rem %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "rem.f a:R6, b:R6, c:R6 (2868)", "assembly": "rem %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "rem %0,%1,%2",
;       "rem_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:modsi3
(define_insn "modsi3" [
    (set 
      (match_operand:SI 0 "register_operand" "=r,r,r,r,r,r,r,r") 
      (mod:SI 
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,r,0,r,ULIMM,r") 
        (match_operand:SI 2 "nonmemory_operand" "r,ULIMM,U06S0,U06S0,S12S0,ULIMM,r,r")))]
 "true" "@
  rem %0,%1,%2
  rem %0,%1,%2
  rem %0,%1,%2
  rem %0,%1,%2
  rem %0,%1,%2
  rem %0,%1,%2
  rem %0,%1,%2
  rem %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,8,8,4")
    (set_attr "type" "rem,rem,rem,rem,rem,rem,rem,rem")]
)
; END:modsi3

; START:moddi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (mod:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "reml"
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
;       { "_comment": "reml.cc.f RB:rb, RB:rb, u6:uimm6 (5826)", "assembly": "reml %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "reml.cc.f RB:rb, RB:rb, RC:rc (5823)", "assembly": "reml %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "reml.cc.f RB:rb, RB:rb, limm:limm (5833)", "assembly": "reml %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "reml.cc.f RB:rb, RB:rb, ximm:ximm (5846)", "assembly": "reml %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "reml.f RA:ra, RB:rb, u6:uimm6 (5824)", "assembly": "reml %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "reml.f RB:rb, RB:rb, s12:simm12 (5827)", "assembly": "reml %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "reml.f RA:ra, RB:rb, limm:limm (5829)", "assembly": "reml %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "reml.f RA:ra, RB:rb, ximm:ximm (5842)", "assembly": "reml %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "reml.f RA:ra, limm:limm, RC:rc (5828)", "assembly": "reml %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "reml.f RA:ra, ximm:ximm, RC:rc (5841)", "assembly": "reml %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "reml.f RA:ra, RB:rb, RC:rc (5821)", "assembly": "reml %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "reml %0,%1,%2",
;       "reml_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:moddi3
(define_insn "moddi3" [
    (set 
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r") 
      (mod:DI 
        (match_operand:DI 1 "nonmemory_operand" "r,0,0,0,r,0,r,r,ULIMM,UXIMM,r") 
        (match_operand:DI 2 "nonmemory_operand" "U06S0,r,ULIMM,UXIMM,U06S0,S12S0,ULIMM,UXIMM,r,r,r")))]
 "true" "@
  reml %0,%1,%2
  reml %0,%1,%2
  reml %0,%1,%2
  reml %0,%1,%2
  reml %0,%1,%2
  reml %0,%1,%2
  reml %0,%1,%2
  reml %0,%1,%2
  reml %0,%1,%2
  reml %0,%1,%2
  reml %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,4,8,4,4,4,8,4,8,4,4")
    (set_attr "type" "reml,reml,reml,reml,reml,reml,reml,reml,reml,reml,reml")]
)
; END:moddi3

; START:umodsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (umod:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "remu"
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
;       { "_comment": "remu.cc.f b:R6, b:R6, c:R6 (2902)", "assembly": "remu %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "remu.cc.f b:R6, b:R6, limm:limm (2903)", "assembly": "remu %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "remu.cc.f b:R6, b:R6, u6:uimm6 (2906)", "assembly": "remu %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "remu.f a:R6, b:R6, u6:uimm6 (2896)", "assembly": "remu %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "remu.f b:R6, b:R6, s12:simm12 (2900)", "assembly": "remu %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "remu.f a:R6, b:R6, limm:limm (2890)", "assembly": "remu %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "remu.f a:R6, limm:limm, c:R6 (2889)", "assembly": "remu %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "remu.f a:R6, b:R6, c:R6 (2888)", "assembly": "remu %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "remu %0,%1,%2",
;       "remu_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:umodsi3
(define_insn "umodsi3" [
    (set 
      (match_operand:SI 0 "register_operand" "=r,r,r,r,r,r,r,r") 
      (umod:SI 
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,r,0,r,ULIMM,r") 
        (match_operand:SI 2 "nonmemory_operand" "r,ULIMM,U06S0,U06S0,S12S0,ULIMM,r,r")))]
 "true" "@
  remu %0,%1,%2
  remu %0,%1,%2
  remu %0,%1,%2
  remu %0,%1,%2
  remu %0,%1,%2
  remu %0,%1,%2
  remu %0,%1,%2
  remu %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,8,8,4")
    (set_attr "type" "remu,remu,remu,remu,remu,remu,remu,remu")]
)
; END:umodsi3

; START:umoddi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (umod:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "remul"
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
;       { "_comment": "remul.cc.f RB:rb, RB:rb, RC:rc (5856)", "assembly": "remul %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "remul.cc.f RB:rb, RB:rb, limm:limm (5866)", "assembly": "remul %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "remul.cc.f RB:rb, RB:rb, u6:uimm6 (5859)", "assembly": "remul %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "remul.cc.f RB:rb, RB:rb, ximm:ximm (5879)", "assembly": "remul %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "remul.f RB:rb, RB:rb, s12:simm12 (5860)", "assembly": "remul %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "S12S0" } },
;       { "_comment": "remul.f RA:ra, RB:rb, u6:uimm6 (5857)", "assembly": "remul %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "remul.f RA:ra, RB:rb, limm:limm (5862)", "assembly": "remul %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "remul.f RA:ra, RB:rb, ximm:ximm (5875)", "assembly": "remul %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "remul.f RA:ra, limm:limm, RC:rc (5861)", "assembly": "remul %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "remul.f RA:ra, ximm:ximm, RC:rc (5874)", "assembly": "remul %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "remul.f RA:ra, RB:rb, RC:rc (5854)", "assembly": "remul %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "remul %0,%1,%2",
;       "remul_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:umoddi3
(define_insn "umoddi3" [
    (set 
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r") 
      (umod:DI 
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM,UXIMM,r") 
        (match_operand:DI 2 "nonmemory_operand" "r,ULIMM,U06S0,UXIMM,S12S0,U06S0,ULIMM,UXIMM,r,r,r")))]
 "true" "@
  remul %0,%1,%2
  remul %0,%1,%2
  remul %0,%1,%2
  remul %0,%1,%2
  remul %0,%1,%2
  remul %0,%1,%2
  remul %0,%1,%2
  remul %0,%1,%2
  remul %0,%1,%2
  remul %0,%1,%2
  remul %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "remul,remul,remul,remul,remul,remul,remul,remul,remul,remul,remul")]
)
; END:umoddi3


; START:xorsi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=SI} (xor:SI @op1{mode=SI} @op2{mode=SI}))]",
;   "general_attributes":   {
;     "type": "xor"
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
;       { "_comment": "xor.cc.f b:R6, b:R6, c:R6 (4502)", "assembly": "xor %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "xor.cc.f b:R6, b:R6, limm:limm (4504)", "assembly": "xor %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "xor.cc.f b:R6, b:R6, u6:uimm6 (4506)", "assembly": "xor %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "xor.f b:R6, b:R6, s12:simm12 (4500)", "assembly": "xor %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "xor.f a:R6, b:R6, limm:limm (4490)", "assembly": "xor %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "xor.f a:R6, b:R6, u6:uimm6 (4496)", "assembly": "xor %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "xor.f a:R6, limm:limm, c:R6 (4489)", "assembly": "xor %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "xor_s b:R3, b:R3, c:R3 (4508)", "assembly": "xor_s %0,%1,%2", "attributes":   { "predicable": "no", "length": "2" }, "constraints":   { "op0": "q", "op1": "0", "op2": "q" } },
;       { "_comment": "xor.f a:R6, b:R6, c:R6 (4488)", "assembly": "xor %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "xor %0,%1,%2",
;       "xor_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ]
;     }
;   }
; OUTPUT:xorsi3
(define_insn "xorsi3" [
    (set 
      (match_operand:SI 0 "register_operand" "=r,r,r,r,r,r,r,q,r") 
      (xor:SI 
        (match_operand:SI 1 "nonmemory_operand" "0,0,0,0,r,r,ULIMM,0,r") 
        (match_operand:SI 2 "nonmemory_operand" "r,ULIMM,U06S0,S12S0,ULIMM,U06S0,r,q,r")))]
 "true" "@
  xor %0,%1,%2
  xor %0,%1,%2
  xor %0,%1,%2
  xor %0,%1,%2
  xor %0,%1,%2
  xor %0,%1,%2
  xor %0,%1,%2
  xor_s %0,%1,%2
  xor %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,8,4,8,2,4")
    (set_attr "type" "xor,xor,xor,xor,xor,xor,xor,xor,xor")]
)
; END:xorsi3

; START:xordi3
;   {
;   "valid_actions": "generate/db_constraints",
;   "type": "define_insn",
;   "match_rule": "[(set @op0{mode=DI} (xor:DI @op1{mode=DI} @op2{mode=DI}))]",
;   "general_attributes":   {
;     "type": "xorl"
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
;       { "_comment": "xorl.cc.f RB:rb, RB:rb, RC:rc (5196)", "assembly": "xorl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "r" } },
;       { "_comment": "xorl.cc.f RB:rb, RB:rb, limm:limm (5206)", "assembly": "xorl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "8" }, "constraints":   { "op0": "r", "op1": "0", "op2": "ULIMM" } },
;       { "_comment": "xorl.cc.f RB:rb, RB:rb, u6:uimm6 (5199)", "assembly": "xorl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "U06S0" } },
;       { "_comment": "xorl.cc.f RB:rb, RB:rb, ximm:ximm (5219)", "assembly": "xorl %0,%1,%2", "attributes":   { "predicable": "yes", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "UXIMM" } },
;       { "_comment": "xorl.f RA:ra, RB:rb, u6:uimm6 (5197)", "assembly": "xorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "U06S0" } },
;       { "_comment": "xorl.f RB:rb, RB:rb, s12:simm12 (5200)", "assembly": "xorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "0", "op2": "S12S0" } },
;       { "_comment": "xorl.f RA:ra, RB:rb, limm:limm (5202)", "assembly": "xorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "r", "op2": "ULIMM" } },
;       { "_comment": "xorl.f RA:ra, RB:rb, ximm:ximm (5215)", "assembly": "xorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "UXIMM" } },
;       { "_comment": "xorl.f RA:ra, limm:limm, RC:rc (5201)", "assembly": "xorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "8" }, "constraints":   { "op0": "r", "op1": "ULIMM", "op2": "r" } },
;       { "_comment": "xorl.f RA:ra, ximm:ximm, RC:rc (5214)", "assembly": "xorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "UXIMM", "op2": "r" } },
;       { "_comment": "xorl.f RA:ra, RB:rb, RC:rc (5194)", "assembly": "xorl %0,%1,%2", "attributes":   { "predicable": "no", "length": "4" }, "constraints":   { "op0": "r", "op1": "r", "op2": "r" } }
;   ],
;   "DB_match_information":   {
;     "instructions_to_match": [
;       "xorl %0,%1,%2",
;       "xorl_s %0,%1,%2"
;     ]
;     },
;   "DB_generated":   {
;     "found_matches": [
;     
;     ],
;     "failed_for_operands": [
;         { "_comment": "xorl.aq RB:rb, RC:rc (6394)" },
;         { "_comment": "xorl.aq 0:0, RC:rc (6395)" },
;         { "_comment": "xorl.aq RB:rb, u6:uimm6 (6396)" },
;         { "_comment": "xorl.aq 0:0, u6:uimm6 (6397)" },
;         { "_comment": "xorl.aq RB:rb, limm:limm (6398)" },
;         { "_comment": "xorl.aq 0:0, limm:limm (6399)" },
;         { "_comment": "xorl.aq RB:rb, ximm:ximm (6400)" },
;         { "_comment": "xorl.aq 0:0, ximm:ximm (6401)" }
;     ]
;     }
;   }
; OUTPUT:xordi3
(define_insn "xordi3" [
    (set 
      (match_operand:DI 0 "register_operand" "=r,r,r,r,r,r,r,r,r,r,r") 
      (xor:DI 
        (match_operand:DI 1 "nonmemory_operand" "0,0,0,0,r,0,r,r,ULIMM,UXIMM,r") 
        (match_operand:DI 2 "nonmemory_operand" "r,ULIMM,U06S0,UXIMM,U06S0,S12S0,ULIMM,UXIMM,r,r,r")))]
 "true" "@
  xorl %0,%1,%2
  xorl %0,%1,%2
  xorl %0,%1,%2
  xorl %0,%1,%2
  xorl %0,%1,%2
  xorl %0,%1,%2
  xorl %0,%1,%2
  xorl %0,%1,%2
  xorl %0,%1,%2
  xorl %0,%1,%2
  xorl %0,%1,%2" [
    (set_attr "predicable" "yes,yes,yes,yes,no,no,no,no,no,no,no")
    (set_attr "length" "4,8,4,4,4,4,8,4,8,4,4")
    (set_attr "type" "xorl,xorl,xorl,xorl,xorl,xorl,xorl,xorl,xorl,xorl,xorl")]
)
; END:xordi3


