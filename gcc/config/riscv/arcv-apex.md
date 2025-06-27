;; Machine description for the APEX instructions
;; Copyright (C) 2025 Free Software Foundation, Inc.

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

;; Used by "XD" insn. format: `insn` volatile
(define_insn "riscv_arcv_apex_void_ftype_v"
  [(unspec_volatile:SI [(match_operand:SI 0 "const_int_operand" "xAVpXD")]
	UNSPEC_ARCV_APEX_VOID_V)]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[0]);
  return xasprintf ("%s # 'XD' `insn` volatile", str);
}
  [(set_attr "type" "arith")]
)

;; Used by "XI","XD" insn. format: `insn src0` volatile
(define_insn "riscv_arcv_apex_void_ftype_src0_v"
  [(unspec_volatile:SI [(match_operand:SI 0 "const_int_operand" "xAVpXI,xAVpXD")
			(match_operand:SI 1 "nonmemory_operand" "I,r")]
	UNSPEC_ARCV_APEX_VOID_SRC0_V)]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[0]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%si\t%d # 'XI' `insn src0` volatile",
			str,
			(int) INTVAL (operands[1]));
    case 1:
      return xasprintf ("%s\t%s # 'XD' `insn src0` volatile",
			str,
			reg_names[REGNO (operands[1])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith")]
)

;; Used by "XS","XD" insn. format: `insn src0, src1` volatile
(define_insn "riscv_arcv_apex_void_ftype_src0_src1_v"
  [(unspec_volatile:SI [(match_operand:SI 0 "const_int_operand" "xAVpXS,xAVpXD")
			(match_operand:SI 1 "register_operand" "r,r")
			(match_operand:SI 2 "nonmemory_operand" "B8,r")]
	UNSPEC_ARCV_APEX_VOID_SRC0_SRC1_V)]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[0]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%si\t%s,%d # 'XS' `insn src0, src1` volatile",
			str,
			reg_names[REGNO (operands[1])],
			(int) INTVAL (operands[2]));
    case 1:
      return xasprintf ("%s\t%s,%s # 'XD' `insn src0, src1` volatile",
			str,
			reg_names[REGNO (operands[1])],
			reg_names[REGNO (operands[2])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith")]
)

;; Used by "XD" insn. format: `insn dest` volatile
(define_insn "riscv_arcv_apex_dest_ftype_v"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec_volatile:SI [(match_operand:SI 1 "const_int_operand" "xAVpXD")]
	UNSPEC_ARCV_APEX_DEST_V))]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[1]);
  return xasprintf ("%s\t%s # 'XD' `insn dest` volatile",
		    str,
		    reg_names[REGNO (operands[0])]);
}
  [(set_attr "type" "arith")]
)

;; Used by "XD" insn. format: `insn dest`
(define_insn "riscv_arcv_apex_dest_ftype"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "const_int_operand" "xAVpXD")]
	UNSPEC_ARCV_APEX_DEST))]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[1]);
  return xasprintf ("%s\t%s # 'XD' `insn dest`",
		    str,
		    reg_names[REGNO (operands[0])]);
}
  [(set_attr "type" "arith")]
)

;; Used by "XI","XD" insn. format: `insn dest, src0` volatile
(define_insn "riscv_arcv_apex_dest_ftype_src0_v"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(unspec_volatile:SI [(match_operand:SI 1 "const_int_operand" "xAVpXI,xAVpXD")
		    (match_operand:SI 2 "nonmemory_operand" "I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0_V))]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[1]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%si\t%s,%d # 'XI' `insn des, src0` volatile",
			str,
			reg_names[REGNO (operands[0])],
			(int) INTVAL (operands[2]));
    case 1:
      return xasprintf ("%s\t%s,%s # 'XD' `insn des, src0` volatile",
			str,
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith")]
)

;; Used by "XI","XD" insn. format: `insn dest, src0`
(define_insn "riscv_arcv_apex_dest_ftype_src0"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(unspec:SI [(match_operand:SI 1 "const_int_operand" "xAVpXI,xAVpXD")
		    (match_operand:SI 2 "nonmemory_operand" "I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0))]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[1]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%si\t%s,%d # 'XI' `insn des, src0`",
			str,
			reg_names[REGNO (operands[0])],
			(int) INTVAL (operands[2]));
    case 1:
      return xasprintf ("%s\t%s,%s # 'XD' `insn des, src0`",
			str,
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith")]
)

;; Used by "XS","XC","XD" insn. format: `insn dest, src0, imm/src1` volatile
(define_insn "riscv_arcv_apex_dest_ftype_src0_src1_v"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r")
	(unspec_volatile:SI [(match_operand:SI 1 "const_int_operand" "xAVpXS,xAVpXC,xAVpXD")
		    (match_operand:SI 2 "register_operand" "r,0,r")
		    (match_operand:SI 3 "nonmemory_operand" "B8,I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0_SRC1_V))]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[1]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%si\t%s,%s,%d # 'XS' `insn dest, src0, imm/src1` volatile",
			str,
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			(int) INTVAL (operands[3]));
    case 1:
      return xasprintf ("%si\t%s,%s,%d # 'XC' `insn dest/src0, imm` volatile",
			str,
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			(int) INTVAL (operands[3]));
    case 2:
      return xasprintf ("%s\t%s,%s,%s # 'XD' `insn dest, src0, imm/src1` volatile",
			str,
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			reg_names[REGNO (operands[3])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith,arith")]
)

;; Used by "XS","XC","XD" insn. format: `insn dest, src0, imm/src1`
(define_insn "riscv_arcv_apex_dest_ftype_src0_src1"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r")
	(unspec:SI [(match_operand:SI 1 "const_int_operand" "xAVpXS,xAVpXC,xAVpXD")
		    (match_operand:SI 2 "register_operand" "r,0,r")
		    (match_operand:SI 3 "nonmemory_operand" "B8,I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0_SRC1))]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[1]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%si\t%s,%s,%d # 'XS' `insn dest, src0, imm/src1`",
			str,
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			(int) INTVAL (operands[3]));
    case 1:
      return xasprintf ("%si\t%s,%s,%d # 'XC' `insn dest/src0, imm`",
			str,
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			(int) INTVAL (operands[3]));
    case 2:
      return xasprintf ("%s\t%s,%s,%s # 'XD' `insn dest, src0, imm/src1`",
			str,
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			reg_names[REGNO (operands[3])]);
    default:
      gcc_unreachable ();
  }
}
  [(set_attr "type" "arith,arith,arith")]
)

