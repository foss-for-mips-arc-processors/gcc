/* ARCV (ARC RISC-V) builtin functions.
   Copyright (C) 2024-2025 Free Software Foundation, Inc.

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
#include "tm.h"
#include "rtl.h"
#include "tree.h"
#include "gimple-expr.h"
#include "memmodel.h"
#include "expmed.h"
#include "profile-count.h"
#include "optabs.h"
#include "recog.h"
#include "diagnostic-core.h"
#include "stor-layout.h"
#include "stringpool.h"
#include "expr.h"
#include "langhooks.h"
#include "tm_p.h"
#include "backend.h"
#include "gimple.h"
#include "gimple-iterator.h"

/* Specifies how a built-in function should be converted into rtl.  */
enum riscv_builtin_type {
  /* The function corresponds directly to an .md pattern.  */
  RISCV_BUILTIN_DIRECT,

  /* Likewise, but with return type VOID.  */
  RISCV_BUILTIN_DIRECT_NO_TARGET
};

/* This structure describes an APEX built-in function.  */
struct arcv_apex_builtin_description {
  /* The code of the main .md file instruction.  See riscv_builtin_type
     for more information.  */
  enum insn_code icode;

  /* The name of the built-in function.  */
  const char *name;

  /* The assembly mnemonic of the built-in instruction.  */
  const char *mnemonic;

  /* The opcode of the built-in instruction.  */
  unsigned int opcode;

  /* Specifies how the function should be expanded.  */
  enum riscv_builtin_type builtin_type;

  /* Specifies the instruction format.  See "apex_insn_format" enum
    for more details.  */
  unsigned int format_flags;
};

/* The XD-type has 8 function bits encoding up to 256 instructions.
   The XS-type has 6 function bits encoding up to 64 instructions.
   Both the XI-type and the XC-type have 5 function bits each encoding up
   to 32 instructions respectively.  Thus giving a total of 384 possible
   different instructions.  */
static const int arcv_apex_builtins_limit = 384;
static struct arcv_apex_builtin_description
arcv_apex_builtins[arcv_apex_builtins_limit];

/* Return the assembly mnemonic for an APEX instruction.
   Appends "i" suffix if immediate_p is true and multiple formats exist.  */

const char*
arcv_apex_asm_mnemonic (rtx op, bool immediate_p)
{
  unsigned int subcode = UINTVAL (op);
  const char *base_mnemonic = arcv_apex_builtins[subcode].mnemonic;
  unsigned int format_flags = arcv_apex_builtins[subcode].format_flags;

  /* Add suffix only for immediate alternatives when XD coexists.  */
  if (immediate_p
      && (format_flags & APEX_XD)
      && (format_flags & (APEX_XS | APEX_XI | APEX_XC)))
    return xasprintf ("%si", base_mnemonic);

  return base_mnemonic;
}

/* Checks if the APEX builtin instruction identified by the subcode
   supports the given instruction format.  */

bool
arcv_apex_format_enabled_p (unsigned int subcode, unsigned int insn_format)
{
  const struct arcv_apex_builtin_description *d = &arcv_apex_builtins[subcode];
  return (d->format_flags & insn_format);
}
