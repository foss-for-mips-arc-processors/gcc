;; Place holder for mov operand predicate
(define_predicate "arc64_mov_operand"
  (and (match_code "reg, subreg, mem, const, const_int, symbol_ref, label_ref")
       (ior (match_operand 0 "register_operand")
	    (match_operand 0 "memory_operand"))))
