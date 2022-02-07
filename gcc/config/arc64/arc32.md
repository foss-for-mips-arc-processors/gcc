;; ARCv3:32 specific instructions.

(define_insn_and_split "*arc32_movdi"
  [(set (match_operand:DI 0 "arc64_dest_operand"  "=r,r,Ustor")
	(match_operand:DI 1 "nonimmediate_operand" "r,m,r"))]
  "!TARGET_64BIT
   && (register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode))"
  "@
  vadd2\\t%0,%1,0
  ldd%U1\\t%0,%1
  std%U0\\t%1,%0"
  "&& reload_completed && arc64_split_double_move_p (operands, DImode)"
  [(const_int 0)]
  {
   arc64_split_double_move (operands, DImode);
   DONE;
  }
  [(set_attr "type" "vadd,ld,st")
   (set_attr "length" "4,*,*")])
