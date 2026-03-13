/* Subroutines used for code generation for Synopsys ARC-V processors.
   Copyright (C) 2026 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#define IN_TARGET_CODE 1

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "target.h"
#include "rtl.h"
#include "tree.h"
#include "memmodel.h"
#include "tm.h"
#include "optabs.h"
#include "regs.h"
#include "emit-rtl.h"
#include "recog.h"
#include "diagnostic-core.h"
#include "stor-layout.h"
#include "alias.h"
#include "fold-const.h"
#include "output.h"
#include "insn-attr.h"
#include "flags.h"
#include "explow.h"
#include "calls.h"
#include "varasm.h"
#include "expr.h"
#include "tm_p.h"
#include "df.h"
#include "reload.h"
#include "sched-int.h"
#include "tm-constrs.h"

/* Print .extInstruction assembly directives for APEX instruction formats.  */

void
arcv_apex_emit_ext_directive (const char *mnemonic, int opcode,
			       unsigned int format_flags)
{
  unsigned int operand_sig = format_flags >> 5;
  bool has_immediate = format_flags & (APEX_XS | APEX_XI | APEX_XC);
  const char *suffix = (format_flags & APEX_XD) && has_immediate ? "i" : "";

  /* XD: most general, includes operand flags.  */
  if (format_flags & APEX_XD)
    {
      fprintf (asm_out_file, "\t.extInstruction %s,%d,XD", mnemonic, opcode);
      if (format_flags & APEX_VOID)
	fputs (",void", asm_out_file);
      if (format_flags & APEX_NO_SRC0)
	fputs (",no_src0", asm_out_file);
      if (format_flags & APEX_NO_SRC1)
	fputs (",no_src1", asm_out_file);
      fputc ('\n', asm_out_file);
    }

  /* XS/XC: dest, src0, src1.  */
  if ((format_flags & (APEX_XS | APEX_XC))
      && (operand_sig == APEX_DEST_FTYPE_SRC0_SRC1))
    {
      fprintf (asm_out_file, "\t.extInstruction %s%s,%d",
	       mnemonic, suffix, opcode);
      if (format_flags & APEX_XS)
	fputs (",XS", asm_out_file);
      if (format_flags & APEX_XC)
	fputs (",XC", asm_out_file);
      fputc ('\n', asm_out_file);
    }

  /* XI: dest (optional), src0.  */
  if (format_flags & APEX_XI)
    {
      fprintf (asm_out_file, "\t.extInstruction %s%s,%d,XI",
	       mnemonic, suffix, opcode);
      if (format_flags & APEX_VOID)
	fputs (",void", asm_out_file);
      fputc ('\n', asm_out_file);
    }

  /* XS: void, src0, src1.  */
  if ((format_flags & APEX_XS) && (operand_sig == APEX_VOID_FTYPE_SRC0_SRC1))
    fprintf (asm_out_file, "\t.extInstruction %s%s,%d,XS,void\n",
	     mnemonic, suffix, opcode);
}
