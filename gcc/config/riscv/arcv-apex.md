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
(define_insn "riscv_arcv_apex_void_ftype_<S0M:mode>_v"
  [(unspec_volatile [(match_operand:SI 0 "const_int_operand" "xAVpXI,xAVpXD")
			(match_operand:S0M 1 "nonmemory_operand" "I,r")]
	UNSPEC_ARCV_APEX_VOID_SRC0_V)]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[0]);
  const char *suffix = arcv_apex_get_insn_suffix (operands[0]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s%s\t%d # 'XI' `insn src0` volatile",
			str,
			suffix,
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

(define_expand "riscv_arcv_apex_void_ftype_src0_v"
  [(unspec_volatile [(match_operand:SI 0 "const_int_operand")
    (match_operand 1 "nonmemory_operand")]
	UNSPEC_ARCV_APEX_VOID_SRC0_V)]
  ""
{
  /* Build the SET exactly as it appears above, but with the
     real RTX objects.  Every operand already carries its mode,
     so nothing needs to be guessed.  The UNSPEC code is
     essential as it tags this RTL with a unique ID, so the
     recognizer can match it to the correct mode-specific
     define_insn.  */
  emit_insn (gen_rtx_UNSPEC_VOLATILE (VOIDmode,
				 gen_rtvec (2, operands[0],
					       operands[1]),
				 UNSPEC_ARCV_APEX_VOID_SRC0_V));
  DONE;
})

;; Used by "XS","XD" insn. format: `insn src0, src1` volatile
(define_insn "riscv_arcv_apex_void_ftype_<S0M:mode>_<S1M:mode>_v"
  [(unspec_volatile [(match_operand:SI 0 "const_int_operand" "xAVpXS,xAVpXD")
			(match_operand:S0M 1 "register_operand" "r,r")
			(match_operand:S1M 2 "nonmemory_operand" "B8,r")]
	UNSPEC_ARCV_APEX_VOID_SRC0_SRC1_V)]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[0]);
  const char *suffix = arcv_apex_get_insn_suffix (operands[0]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s%s\t%s,%d # 'XS' `insn src0, src1` volatile",
			str,
			suffix,
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

(define_expand "riscv_arcv_apex_void_ftype_src0_src1_v"
  [(unspec_volatile [(match_operand:SI 0 "const_int_operand")
    (match_operand 1 "register_operand")
    (match_operand 2 "nonmemory_operand")]
	UNSPEC_ARCV_APEX_VOID_SRC0_SRC1_V)]
  ""
{
  /* Build the SET exactly as it appears above, but with the
     real RTX objects.  Every operand already carries its mode,
     so nothing needs to be guessed.  The UNSPEC code is
     essential as it tags this RTL with a unique ID, so the
     recognizer can match it to the correct mode-specific
     define_insn.  */
  emit_insn (gen_rtx_UNSPEC_VOLATILE (VOIDmode,
				 gen_rtvec (3, operands[0],
					       operands[1],
					       operands[2]),
				 UNSPEC_ARCV_APEX_VOID_SRC0_SRC1_V));
  DONE;
})

;; Used by "XD" insn. format: `insn dest` volatile
(define_insn "riscv_arcv_apex_<DM:mode>_ftype_v"
  [(set (match_operand:DM 0 "register_operand" "=r")
	(unspec_volatile:DM [(match_operand:SI 1 "const_int_operand" "xAVpXD")]
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

(define_expand "riscv_arcv_apex_dest_ftype_v"
  [(set (match_operand 0 "register_operand")
	(unspec [(match_operand:SI 1 "const_int_operand")]
	UNSPEC_ARCV_APEX_DEST_V))]
  ""
{
  /* Build the SET exactly as it appears above, but with the
     real RTX objects.  Every operand already carries its mode,
     so nothing needs to be guessed.  The UNSPEC code is
     essential as it tags this RTL with a unique ID, so the
     recognizer can match it to the correct mode-specific
     define_insn.  */
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC_VOLATILE (GET_MODE (operands[0]),
				 gen_rtvec (1, operands[1]),
				 UNSPEC_ARCV_APEX_DEST_V)));
  DONE;
})

;; Used by "XD" insn. format: `insn dest`
(define_insn "riscv_arcv_apex_<DM:mode>_ftype"
  [(set (match_operand:DM 0 "register_operand" "=r")
	(unspec:DM [(match_operand:SI 1 "const_int_operand" "xAVpXD")]
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

(define_expand "riscv_arcv_apex_dest_ftype"
  [(set (match_operand 0 "register_operand")
	(unspec [(match_operand:SI 1 "const_int_operand")]
	UNSPEC_ARCV_APEX_DEST))]
  ""
{
  /* Build the SET exactly as it appears above, but with the
     real RTX objects.  Every operand already carries its mode,
     so nothing needs to be guessed.  The UNSPEC code is
     essential as it tags this RTL with a unique ID, so the
     recognizer can match it to the correct mode-specific
     define_insn.  */
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC (GET_MODE (operands[0]),
				 gen_rtvec (1, operands[1]),
				 UNSPEC_ARCV_APEX_DEST)));
  DONE;
})

;; Used by "XI","XD" insn. format: `insn dest, src0` volatile
(define_insn "riscv_arcv_apex_<DM:mode>_ftype_<S0M:mode>_v"
  [(set (match_operand:DM 0 "register_operand" "=r,r")
	(unspec_volatile:DM [(match_operand:SI 1 "const_int_operand" "xAVpXI,xAVpXD")
		    (match_operand:S0M 2 "nonmemory_operand" "I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0_V))]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[1]);
  const char *suffix = arcv_apex_get_insn_suffix (operands[1]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s%s\t%s,%d # 'XI' `insn des, src0` volatile",
			str,
			suffix,
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

(define_expand "riscv_arcv_apex_dest_ftype_src0_v"
  [(set (match_operand 0 "register_operand")
	(unspec_volatile [(match_operand:SI 1 "const_int_operand")
		    (match_operand 2 "nonmemory_operand")]
	UNSPEC_ARCV_APEX_DEST_SRC0_V))]
  ""
{
  /* Build the SET exactly as it appears above, but with the
     real RTX objects.  Every operand already carries its mode,
     so nothing needs to be guessed.  The UNSPEC code is
     essential as it tags this RTL with a unique ID, so the
     recognizer can match it to the correct mode-specific
     define_insn.  */
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC_VOLATILE (GET_MODE (operands[0]),
				 gen_rtvec (2, operands[1],
					       operands[2]),
				 UNSPEC_ARCV_APEX_DEST_SRC0_V)));
  DONE;
})

;; Used by "XI","XD" insn. format: `insn dest, src0`
(define_insn "riscv_arcv_apex_<DM:mode>_ftype_<S0M:mode>"
  [(set (match_operand:DM 0 "register_operand" "=r,r")
	(unspec:DM [(match_operand:SI 1 "const_int_operand" "xAVpXI,xAVpXD")
		    (match_operand:S0M 2 "nonmemory_operand" "I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0))]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[1]);
  const char *suffix = arcv_apex_get_insn_suffix (operands[1]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s%s\t%s,%d # 'XI' `insn des, src0`",
			str,
			suffix,
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

(define_expand "riscv_arcv_apex_dest_ftype_src0"
  [(set (match_operand 0 "register_operand")
	(unspec [(match_operand:SI 1 "const_int_operand")
		 (match_operand 2 "nonmemory_operand")]
		UNSPEC_ARCV_APEX_DEST_SRC0))]
  ""
{
  /* Build the SET exactly as it appears above, but with the
     real RTX objects.  Every operand already carries its mode,
     so nothing needs to be guessed.  The UNSPEC code is
     essential as it tags this RTL with a unique ID, so the
     recognizer can match it to the correct mode-specific
     define_insn.  */
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC (GET_MODE (operands[0]),
				 gen_rtvec (2, operands[1],
					       operands[2]),
				 UNSPEC_ARCV_APEX_DEST_SRC0)));
  DONE;
})

;; Used by "XS","XC","XD" insn. format: `insn dest, src0, imm/src1` volatile
(define_insn "riscv_arcv_apex_<DM:mode>_ftype_<S0M:mode>_<S1M:mode>_v"
  [(set (match_operand:DM 0 "register_operand" "=r,r,r")
	(unspec_volatile:DM [(match_operand:SI 1 "const_int_operand" "xAVpXS,xAVpXC,xAVpXD")
		    (match_operand:S0M 2 "register_operand" "r,0,r")
		    (match_operand:S1M 3 "nonmemory_operand" "B8,I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0_SRC1_V))]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[1]);
  const char *suffix = arcv_apex_get_insn_suffix (operands[1]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s%s\t%s,%s,%d # 'XS' `insn dest, src0, imm/src1` volatile",
			str,
			suffix,
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			(int) INTVAL (operands[3]));
    case 1:
      return xasprintf ("%s%s\t%s,%s,%d # 'XC' `insn dest/src0, imm` volatile",
			str,
			suffix,
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

(define_expand "riscv_arcv_apex_dest_ftype_src0_src1_v"
  [(set (match_operand 0 "register_operand")
	(unspec [(match_operand:SI 1 "const_int_operand")
		 (match_operand 2 "register_operand")
		 (match_operand 3 "nonmemory_operand")]
		UNSPEC_ARCV_APEX_DEST_SRC0_SRC1_V))]
  ""
{
  /* Build the SET exactly as it appears above, but with the
     real RTX objects.  Every operand already carries its mode,
     so nothing needs to be guessed.  The UNSPEC code is
     essential as it tags this RTL with a unique ID, so the
     recognizer can match it to the correct mode-specific
     define_insn.  */
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC_VOLATILE (GET_MODE (operands[0]),
				 gen_rtvec (3, operands[1],
					       operands[2],
					       operands[3]),
				 UNSPEC_ARCV_APEX_DEST_SRC0_SRC1_V)));
  DONE;
})

;; Used by "XS","XC","XD" insn. format: `insn dest, src0, imm/src1`
(define_insn "riscv_arcv_apex_<DM:mode>_ftype_<S0M:mode>_<S1M:mode>"
  [(set (match_operand:DM 0 "register_operand" "=r,r,r")
	(unspec:DM [(match_operand:SI 1 "const_int_operand" "xAVpXS,xAVpXC,xAVpXD")
		    (match_operand:S0M 2 "register_operand" "r,0,r")
		    (match_operand:S1M 3 "nonmemory_operand" "B8,I,r")]
	UNSPEC_ARCV_APEX_DEST_SRC0_SRC1))]
  ""
{
  const char *str = arcv_apex_get_insn_name (operands[1]);
  const char *suffix = arcv_apex_get_insn_suffix (operands[1]);
  switch (which_alternative)
  {
    case 0:
      return xasprintf ("%s%s\t%s,%s,%d # 'XS' `insn dest, src0, imm/src1`",
			str,
			suffix,
			reg_names[REGNO (operands[0])],
			reg_names[REGNO (operands[2])],
			(int) INTVAL (operands[3]));
    case 1:
      return xasprintf ("%s%s\t%s,%s,%d # 'XC' `insn dest/src0, imm`",
			str,
			suffix,
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

(define_expand "riscv_arcv_apex_dest_ftype_src0_src1"
  [(set (match_operand 0 "register_operand")
	(unspec [(match_operand:SI 1 "const_int_operand")
		 (match_operand 2 "register_operand")
		 (match_operand 3 "nonmemory_operand")]
		UNSPEC_ARCV_APEX_DEST_SRC0_SRC1))]
  ""
{
  /* Build the SET exactly as it appears above, but with the
     real RTX objects.  Every operand already carries its mode,
     so nothing needs to be guessed.  The UNSPEC code is
     essential as it tags this RTL with a unique ID, so the
     recognizer can match it to the correct mode-specific
     define_insn.  */
  emit_insn (gen_rtx_SET (operands[0],
		gen_rtx_UNSPEC (GET_MODE (operands[0]),
				 gen_rtvec (3, operands[1],
					       operands[2],
					       operands[3]),
				 UNSPEC_ARCV_APEX_DEST_SRC0_SRC1)));
  DONE;
})
