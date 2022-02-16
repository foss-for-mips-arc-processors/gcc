(define_mode_attr vectab [(V2HI "") (V4HI "d") (V2SI "d")])
(define_mode_attr vmvtab [(V2HI "add") (V4HI "vadd2") (V2SI "vadd2")])

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

(define_insn_and_split "*arc32_mov<mode>"
  [(set (match_operand:VALL 0 "arc64_dest_operand"  "=r,r,Ustor")
	(match_operand:VALL 1 "nonimmediate_operand" "r,m,r"))]
  "!TARGET_64BIT && TARGET_SIMD
   && (register_operand (operands[0], <MODE>mode)
       || register_operand (operands[1], <MODE>mode))"
  "@
  <vmvtab>\\t%0,%1,0
  ld<vectab>%U1\\t%0,%1
  st<vectab>%U0\\t%1,%0"
  "&& reload_completed && arc64_split_double_move_p (operands, <MODE>mode)"
  [(const_int 0)]
  {
   arc64_split_double_move (operands, <MODE>mode);
   DONE;
  }
  [(set_attr "type" "vadd,ld,st")
   (set_attr "length" "4,*,*")])
