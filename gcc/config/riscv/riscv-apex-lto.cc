/* LTO serialization for RISC-V APEX intrinsics.
   Copyright (C) 2025 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/* RISC-V APEX (ARC Processor Extension) intrinsics are unique in GCC
   because they are registered dynamically at compile-time via #pragma intrinsic
   directives, rather than being statically defined like normal target builtins.

   This creates a challenge for LTO (Link Time Optimization): when compiling
   with -flto, each translation unit may register different APEX intrinsics via
   pragmas.  During the link-time optimization phase, all these intrinsic
   definitions must be preserved and made available for code generation.

   This file implements LTO serialization support for APEX intrinsics by:

   1. Writing Phase (produce_asm_for_decls):
      - Iterates through all registered APEX intrinsics
      - Serializes their metadata (name, mnemonic, opcode, instruction formats)
      - Writes to a dedicated .gnu.lto_riscv_apex section in object files

   2. Reading Phase (read_cgraph_and_symbols):
      - Reads .gnu.lto_riscv_apex sections from all input object files
      - Reconstructs and re-registers all APEX intrinsics
      - Makes them available for optimization and code generation

   Without this support, LTO would lose APEX intrinsic definitions, causing
   unavailable intrinsics errors during link-time optimization.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "tree.h"
#include "gimple.h"
#include "cgraph.h"
#include "lto-streamer.h"
#include "ipa-utils.h"
#include "data-streamer.h"
#include "stringpool.h"
#include "attribs.h"

/* Declarations from riscv-builtins.cc for accessing
   APEX builtin information.  */
extern int arcv_apex_get_builtin_count (void);
extern void arcv_apex_get_builtin_info (int, const char **, const char **,
					  unsigned int *, unsigned int *);
extern void arcv_apex_lto_register_builtin (const char *, const char *,
					  unsigned int, unsigned int, bool,
					  tree);
extern const char *arcv_apex_get_fn_name (unsigned int);

/* Write RISC-V APEX intrinsic information to the LTO bytecode stream.

   This function is called during the compilation phase when producing LTO
   bytecode.  It serializes all APEX intrinsics that were registered via
   #pragma directives in the current translation unit.

   The serialization format for each intrinsic is:
     - Function name length (uhwi)
     - Function name characters
     - Instruction name length (uhwi)
     - Instruction name characters
     - Opcode (uhwi)
     - Instruction format flags (uhwi)  */

void
arcv_apex_lto_write_section (void)
{
  /* Get the number of registered APEX builtins in this compilation unit.  */
  int apex_count = arcv_apex_get_builtin_count ();

  /* If no APEX builtins were registered via pragmas, skip section creation.
     This is common for translation units that don't use APEX intrinsics.  */
  if (apex_count == 0)
    return;

  /* Collect indices of intrinsics that are actually used and not optimized
     away.  Use an auto_vec to avoid manual memory management.  */
  auto_vec<int> used_indices;
  for (int i = 0; i < apex_count; i++)
  {
    const char *fn_name = arcv_apex_get_fn_name (i);
    gcc_assert (fn_name);

    /* Check if the intrinsic is still referenced in the program.  */
    symtab_node *snode = symtab_node::get_for_asmname (
      get_identifier (fn_name));

    /* Only keep intrinsics that exist and are actually used.
       Check if the symbol is referred to anywhere in the program.  */
    if (snode && snode->referred_to_p ())
      used_indices.safe_push (i);
  }

  /* If all intrinsics were optimized away, skip section creation.  */
  if (used_indices.is_empty ())
    return;

  /* Create a new LTO section for APEX intrinsics.  */
  struct lto_simple_output_block *ob
    = lto_create_simple_output_block (LTO_section_riscv_apex);

  if (!ob)
    return;

  /* Write the number of used APEX builtins so the reader knows
     how many to expect.  */
  streamer_write_uhwi_stream (ob->main_stream, used_indices.length ());

  /* Serialize only the intrinsics that are still used.  */
  for (unsigned int idx = 0; idx < used_indices.length (); idx++)
  {
    int i = used_indices[idx];
    const char *fn_name = NULL;
    const char *insn_name = NULL;
    unsigned int opcode = 0;
    unsigned int insn_formats = 0;

    /* Get builtin information from the registry.  */
    arcv_apex_get_builtin_info (i, &fn_name, &insn_name,
				&opcode, &insn_formats);

    /* Function and instruction names must exist.  */
    gcc_assert (fn_name && insn_name);

    /* Write function name as length-prefixed string.  */
    size_t name_len = strlen (fn_name);
    streamer_write_uhwi_stream (ob->main_stream, name_len);
    for (size_t j = 0; j < name_len; j++)
      streamer_write_char_stream (ob->main_stream, fn_name[j]);

    /* Write instruction name as length-prefixed string.  */
    size_t insn_name_len = strlen (insn_name);
    streamer_write_uhwi_stream (ob->main_stream, insn_name_len);
    for (size_t j = 0; j < insn_name_len; j++)
      streamer_write_char_stream (ob->main_stream, insn_name[j]);

    /* Write opcode value.  */
    streamer_write_uhwi_stream (ob->main_stream, opcode);

    /* Write instruction format flags.  */
    streamer_write_uhwi_stream (ob->main_stream, insn_formats);
  }

  lto_destroy_simple_output_block (ob);
}

/* Read RISC-V APEX intrinsic information from the LTO bytecode stream.

   This function is called during the link-time optimization phase.  It reads
   the .gnu.lto_riscv_apex sections from all input object files and
   re-registers all APEX intrinsics so they are available for optimization
   and code generation in the LTRANS phase.

   The function iterates over all input files, reads their APEX sections,
   and re-registers each intrinsic by calling riscv_register_apex_builtin.  */

void
arcv_apex_lto_read_section (void)
{
  struct lto_file_decl_data **file_data_vec = lto_get_file_decl_data ();
  struct lto_file_decl_data *file_data;
  unsigned int j = 0;

  /* Process each input file's APEX section.  */
  while ((file_data = file_data_vec[j++]))
  {
    const char *data;
    size_t len;
    class lto_input_block *ib
	= lto_create_simple_input_block (file_data, LTO_section_riscv_apex,
					 &data, &len);

    /* Skip files that don't have an APEX section
      (did not use APEX intrinsics).  */
    if (!ib)
      continue;

    /* Read the count of APEX builtins in this file.  */
    unsigned int apex_count = streamer_read_uhwi (ib);
    unsigned int registered_count = 0;

    /* Deserialize each APEX intrinsic.  */
    for (unsigned int i = 0; i < apex_count; i++)
    {
      /* Read function name.  */
      unsigned int fn_name_len = streamer_read_uhwi (ib);
      char *fn_name = XNEWVEC (char, fn_name_len + 1);
      for (unsigned int k = 0; k < fn_name_len; k++)
	fn_name[k] = streamer_read_uchar (ib);
      fn_name[fn_name_len] = '\0';

      /* Read instruction name.  */
      unsigned int insn_name_len = streamer_read_uhwi (ib);
      char *insn_name = XNEWVEC (char, insn_name_len + 1);
      for (unsigned int k = 0; k < insn_name_len; k++)
	insn_name[k] = streamer_read_uchar (ib);
      insn_name[insn_name_len] = '\0';

      /* Read opcode and instruction format flags.  */
      unsigned int opcode = streamer_read_uhwi (ib);
      unsigned int insn_formats = streamer_read_uhwi (ib);

      /* Look up the function declaration in the merged symbol table.
	 During LTO, all function declarations from all compilation units
	 are merged into a single global symbol table.  */
      symtab_node *snode = symtab_node::get_for_asmname (
      get_identifier (fn_name));

      cgraph_node *node = dyn_cast<cgraph_node *> (snode);
      if (node)
      {
	tree fndecl = node->decl;
	if (fndecl && TREE_CODE (fndecl) == FUNCTION_DECL)
	{
	  /* Re-register the intrinsic so it's available for code generation.
	     The !flag_wpa parameter controls whether to print .extInstruction
	     directives (only needed in final LTRANS phase, not WPA phase).  */
	  arcv_apex_lto_register_builtin (fn_name, insn_name, opcode,
				       insn_formats, !flag_wpa, fndecl);
	  registered_count++;
	}
      }

      /* Free allocated memory.  */
      XDELETEVEC (fn_name);
      XDELETEVEC (insn_name);
    }

    /* Verify we successfully re-registered all APEX intrinsics
       from the section.  If this fails, the LTO section is
       likely corrupted.  */
    gcc_assert (registered_count == apex_count);

    lto_destroy_simple_input_block (file_data, LTO_section_riscv_apex,
				    ib, data, len);
  }
}

