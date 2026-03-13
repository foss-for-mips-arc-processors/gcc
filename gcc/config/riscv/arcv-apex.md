;; Machine description for the APEX instructions
;; Copyright (C) 2026 Free Software Foundation, Inc.

;; This file is part of GCC.

;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.

;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

(define_c_enum "unspec" [

;; ARC-V APEX
  UNSPEC_ARCV_APEX_VOID_V
  UNSPEC_ARCV_APEX_VOID_SRC0_V
  UNSPEC_ARCV_APEX_VOID_SRC0_SRC1_V
  UNSPEC_ARCV_APEX_DEST
  UNSPEC_ARCV_APEX_DEST_V
  UNSPEC_ARCV_APEX_DEST_SRC0
  UNSPEC_ARCV_APEX_DEST_SRC0_V
  UNSPEC_ARCV_APEX_DEST_SRC0_SRC1
  UNSPEC_ARCV_APEX_DEST_SRC0_SRC1_V
])

;; Used by XD (volatile): insn
(define_insn "riscv_arcv_apex_void_ftype_v"
  [(unspec_volatile:SI [(match_operand:SI 0 "const_int_operand" "xAVpXD")]
	UNSPEC_ARCV_APEX_VOID_V)]
  ""
{
  return xasprintf ("%s",
		    arcv_apex_asm_mnemonic (operands[0], false));
}
  [(set_attr "type" "arith")]
)

;; Used by XI and XD (volatile): insn src0
(define_insn "riscv_arcv_apex_void_ftype_<APEX_SRC0:mode>_v"
  [(unspec_volatile [(match_operand:SI 0 "const_int_operand" "xAVpXI,xAVpXD")
			(match_operand:APEX_SRC0 1 "nonmemory_operand" "I,r")]
	UNSPEC_ARCV_APEX_VOID_SRC0_V)]
  ""
{
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s\t%d",
			arcv_apex_asm_mnemonic (operands[0], true),
			(int) INTVAL (operands[1]));
    case 1:
      return xasprintf ("%s\t%s",
			arcv_apex_asm_mnemonic (operands[0], false),
			reg_names[REGNO (operands[1])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith")]
)

(define_expand "riscv_arcv_apex_void_ftype_src0_v"
  [(unspec_volatile [(match_operand:SI 0 "const_int_operand")
    (match_operand 1 "nonmemory_operand")]
	UNSPEC_ARCV_APEX_VOID_SRC0_V)]
  ""
{
  emit_insn (gen_rtx_UNSPEC_VOLATILE (VOIDmode,
				 gen_rtvec (2, operands[0],
					       operands[1]),
				 UNSPEC_ARCV_APEX_VOID_SRC0_V));
  DONE;
})

;; Used by XS and XD (volatile): insn src0, src1
(define_insn "riscv_arcv_apex_void_ftype_<APEX_SRC0:mode>_<APEX_SRC1:mode>_v"
  [(unspec_volatile [(match_operand:SI 0 "const_int_operand" "xAVpXS,xAVpXD")
			(match_operand:APEX_SRC0 1 "register_operand" "r,r")
			(match_operand:APEX_SRC1 2 "nonmemory_operand" "Os08,r")]
	UNSPEC_ARCV_APEX_VOID_SRC0_SRC1_V)]
  ""
{
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s\t%s,%d",
			arcv_apex_asm_mnemonic (operands[0], true),
			reg_names[REGNO (operands[1])],
			(int) INTVAL (operands[2]));
    case 1:
      return xasprintf ("%s\t%s,%s",
			arcv_apex_asm_mnemonic (operands[0], false),
			reg_names[REGNO (operands[1])],
			reg_names[REGNO (operands[2])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith")]
)

(define_expand "riscv_arcv_apex_void_ftype_src0_src1_v"
  [(unspec_volatile [(match_operand:SI 0 "const_int_operand")
    (match_operand 1 "register_operand")
    (match_operand 2 "nonmemory_operand")]
	UNSPEC_ARCV_APEX_VOID_SRC0_SRC1_V)]
  ""
{
  emit_insn (gen_rtx_UNSPEC_VOLATILE (VOIDmode,
				 gen_rtvec (3, operands[0],
					       operands[1],
					       operands[2]),
				 UNSPEC_ARCV_APEX_VOID_SRC0_SRC1_V));
  DONE;
})

;; Used by XD (volatile): insn rd
(define_insn "riscv_arcv_apex_<APEX_DEST:mode>_ftype_v"
  [(set (match_operand:APEX_DEST 0 "register_operand" "=r")
	(unspec_volatile:APEX_DEST [(match_operand:SI 1 "const_int_operand" "xAVpXD")]
	UNSPEC_ARCV_APEX_DEST_V))]
  ""
{
  return xasprintf ("%s\t%s",
		    arcv_apex_asm_mnemonic (operands[1], false),
		    reg_names[REGNO (operands[0])]);
}
  [(set_attr "type" "arith")]
)

(define_expand "riscv_arcv_apex_dest_ftype_v"
  [(set (match_operand 0 "register_operand")
	(unspec_volatile [(match_operand:SI 1 "const_int_operand")]
	UNSPEC_ARCV_APEX_DEST_V))]
  ""
{
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC_VOLATILE (GET_MODE (operands[0]),
				 gen_rtvec (1, operands[1]),
				 UNSPEC_ARCV_APEX_DEST_V)));
  DONE;
})

;; Used by XD: insn rd
(define_insn "riscv_arcv_apex_<APEX_DEST:mode>_ftype"
  [(set (match_operand:APEX_DEST 0 "register_operand" "=r")
	(unspec:APEX_DEST [(match_operand:SI 1 "const_int_operand" "xAVpXD")]
	UNSPEC_ARCV_APEX_DEST))]
  ""
{
  return xasprintf ("%s\t%s",
		    arcv_apex_asm_mnemonic (operands[1], false),
		    reg_names[REGNO (operands[0])]);
}
  [(set_attr "type" "arith")]
)

(define_expand "riscv_arcv_apex_dest_ftype"
  [(set (match_operand 0 "register_operand")
	(unspec [(match_operand:SI 1 "const_int_operand")]
	UNSPEC_ARCV_APEX_DEST))]
  ""
{
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC (GET_MODE (operands[0]),
				 gen_rtvec (1, operands[1]),
				 UNSPEC_ARCV_APEX_DEST)));
  DONE;
})

;; Used by XI and XD (volatile): insn rd, src0
(define_insn "riscv_arcv_apex_<APEX_DEST:mode>_ftype_<APEX_SRC0:mode>_v"
  [(set (match_operand:APEX_DEST 0 "register_operand" "=r,r")
	(unspec_volatile:APEX_DEST [(match_operand:SI 1 "const_int_operand" "xAVpXI,xAVpXD")
		    (match_operand:APEX_SRC0 2 "nonmemory_operand" "I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0_V))]
  ""
{
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s\t%s,%d",
			arcv_apex_asm_mnemonic (operands[1], true),
			reg_names[REGNO (operands[0])],
			(int) INTVAL (operands[2]));
    case 1:
      return xasprintf ("%s\t%s,%s",
			arcv_apex_asm_mnemonic (operands[1], false),
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith")]
)

(define_expand "riscv_arcv_apex_dest_ftype_src0_v"
  [(set (match_operand 0 "register_operand")
	(unspec_volatile [(match_operand:SI 1 "const_int_operand")
		    (match_operand 2 "nonmemory_operand")]
	UNSPEC_ARCV_APEX_DEST_SRC0_V))]
  ""
{
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC_VOLATILE (GET_MODE (operands[0]),
				 gen_rtvec (2, operands[1],
					       operands[2]),
				 UNSPEC_ARCV_APEX_DEST_SRC0_V)));
  DONE;
})

;; Used by XI and XD: insn rd, src0
(define_insn "riscv_arcv_apex_<APEX_DEST:mode>_ftype_<APEX_SRC0:mode>"
  [(set (match_operand:APEX_DEST 0 "register_operand" "=r,r")
	(unspec:APEX_DEST [(match_operand:SI 1 "const_int_operand" "xAVpXI,xAVpXD")
		    (match_operand:APEX_SRC0 2 "nonmemory_operand" "I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0))]
  ""
{
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s\t%s,%d",
			arcv_apex_asm_mnemonic (operands[1], true),
			reg_names[REGNO (operands[0])],
			(int) INTVAL (operands[2]));
    case 1:
      return xasprintf ("%s\t%s,%s",
			arcv_apex_asm_mnemonic (operands[1], false),
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith")]
)

(define_expand "riscv_arcv_apex_dest_ftype_src0"
  [(set (match_operand 0 "register_operand")
	(unspec [(match_operand:SI 1 "const_int_operand")
		 (match_operand 2 "nonmemory_operand")]
		UNSPEC_ARCV_APEX_DEST_SRC0))]
  ""
{
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC (GET_MODE (operands[0]),
				 gen_rtvec (2, operands[1],
					       operands[2]),
				 UNSPEC_ARCV_APEX_DEST_SRC0)));
  DONE;
})

;; Used by XS, XC and XD (volatile): insn rd, src0, imm/src1
(define_insn "riscv_arcv_apex_<APEX_DEST:mode>_ftype_<APEX_SRC0:mode>_<APEX_SRC1:mode>_v"
  [(set (match_operand:APEX_DEST 0 "register_operand" "=r,r,r")
	(unspec_volatile:APEX_DEST [(match_operand:SI 1 "const_int_operand" "xAVpXS,xAVpXC,xAVpXD")
		    (match_operand:APEX_SRC0 2 "register_operand" "r,0,r")
		    (match_operand:APEX_SRC1 3 "nonmemory_operand" "Os08,I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0_SRC1_V))]
  ""
{
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s\t%s,%s,%d",
			arcv_apex_asm_mnemonic (operands[1], true),
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			(int) INTVAL (operands[3]));
    case 1:
      return xasprintf ("%s\t%s,%s,%d",
			arcv_apex_asm_mnemonic (operands[1], true),
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			(int) INTVAL (operands[3]));
    case 2:
      return xasprintf ("%s\t%s,%s,%s",
			arcv_apex_asm_mnemonic (operands[1], false),
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			reg_names[REGNO (operands[3])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith,arith")]
)

(define_expand "riscv_arcv_apex_dest_ftype_src0_src1_v"
  [(set (match_operand 0 "register_operand")
	(unspec_volatile [(match_operand:SI 1 "const_int_operand")
		 (match_operand 2 "register_operand")
		 (match_operand 3 "nonmemory_operand")]
		UNSPEC_ARCV_APEX_DEST_SRC0_SRC1_V))]
  ""
{
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC_VOLATILE (GET_MODE (operands[0]),
				 gen_rtvec (3, operands[1],
					       operands[2],
					       operands[3]),
				 UNSPEC_ARCV_APEX_DEST_SRC0_SRC1_V)));
  DONE;
})

;; Used by XS, XC and XD: insn rd, src0, imm/src1
(define_insn "riscv_arcv_apex_<APEX_DEST:mode>_ftype_<APEX_SRC0:mode>_<APEX_SRC1:mode>"
  [(set (match_operand:APEX_DEST 0 "register_operand" "=r,r,r")
	(unspec:APEX_DEST [(match_operand:SI 1 "const_int_operand" "xAVpXS,xAVpXC,xAVpXD")
		    (match_operand:APEX_SRC0 2 "register_operand" "r,0,r")
		    (match_operand:APEX_SRC1 3 "nonmemory_operand" "Os08,I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0_SRC1))]
  ""
{
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s\t%s,%s,%d",
			arcv_apex_asm_mnemonic (operands[1], true),
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			(int) INTVAL (operands[3]));
    case 1:
      return xasprintf ("%s\t%s,%s,%d",
			arcv_apex_asm_mnemonic (operands[1], true),
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			(int) INTVAL (operands[3]));
    case 2:
      return xasprintf ("%s\t%s,%s,%s",
			arcv_apex_asm_mnemonic (operands[1], false),
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			reg_names[REGNO (operands[3])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith,arith")]
)

(define_expand "riscv_arcv_apex_dest_ftype_src0_src1"
  [(set (match_operand 0 "register_operand")
	(unspec [(match_operand:SI 1 "const_int_operand")
		 (match_operand 2 "register_operand")
		 (match_operand 3 "nonmemory_operand")]
		UNSPEC_ARCV_APEX_DEST_SRC0_SRC1))]
  ""
{
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC (GET_MODE (operands[0]),
				 gen_rtvec (3, operands[1],
					       operands[2],
					       operands[3]),
				 UNSPEC_ARCV_APEX_DEST_SRC0_SRC1)));
  DONE;
})
