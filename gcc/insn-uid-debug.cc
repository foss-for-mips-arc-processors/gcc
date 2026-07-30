/* RTL instruction UID debug mapping.
   Copyright (C) 2026 Free Software Foundation, Inc.

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

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "target.h"
#include "rtl.h"
#include "tree.h"
#include "varasm.h"
#include "output.h"
#include "flags.h"
#include "insn-uid-debug.h"

struct insn_uid_map_entry
{
  unsigned long label_num;
  unsigned int insn_uid;
};

static vec<insn_uid_map_entry> insn_uid_map_entries;
static section *insn_uid_map_section;
static bitmap emitted_insn_uids;
/* Monotonic per translation unit; label names need only be unique in .s.  */
static unsigned long insn_uid_debug_next_label;

bool
insn_uid_debug_enabled_p (void)
{
  return debug_info_level > DINFO_LEVEL_NONE || dwarf_debuginfo_p ();
}

void
insn_uid_debug_begin_function (void)
{
  if (!insn_uid_debug_enabled_p ())
    return;

  insn_uid_map_entries.release ();
  insn_uid_map_section = NULL;
  if (emitted_insn_uids)
  {
    BITMAP_FREE (emitted_insn_uids);
    emitted_insn_uids = NULL;
  }
  emitted_insn_uids = BITMAP_ALLOC (NULL);
}

void
insn_uid_debug_emit_insn_label (FILE *file, rtx_insn *insn)
{
  unsigned int uid;

  if (!insn_uid_debug_enabled_p () || DEBUG_INSN_P (insn))
    return;

  uid = INSN_UID (insn);
  if (bitmap_bit_p (emitted_insn_uids, uid))
    return;

  bitmap_set_bit (emitted_insn_uids, uid);

  insn_uid_map_entry entry;
  entry.label_num = ++insn_uid_debug_next_label;
  entry.insn_uid = uid;
  insn_uid_map_entries.safe_push (entry);

  targetm.asm_out.internal_label (file, "Linsn", entry.label_num);
}

void
insn_uid_debug_end_function (void)
{
  section *save_section;
  unsigned int i;

  if (!insn_uid_debug_enabled_p ())
    return;

  if (emitted_insn_uids)
  {
    BITMAP_FREE (emitted_insn_uids);
    emitted_insn_uids = NULL;
  }

  if (insn_uid_map_entries.is_empty ())
    return;

  if (insn_uid_map_section == NULL)
    insn_uid_map_section
      = get_named_section (NULL, ".gnu.gcc.rtl_insn_map", 3);

  save_section = in_section;
  switch_to_section (insn_uid_map_section);
  assemble_align (POINTER_SIZE);

  /* Header: function name pointer, number of entries.  */
  assemble_integer (XEXP (DECL_RTL (current_function_decl), 0),
		    POINTER_SIZE_UNITS, POINTER_SIZE, 1);
  assemble_integer (GEN_INT (insn_uid_map_entries.length ()), 4, 32, 1);

  for (i = 0; i < insn_uid_map_entries.length (); i++)
    {
      const insn_uid_map_entry &entry = insn_uid_map_entries[i];
      char label[64];

      ASM_GENERATE_INTERNAL_LABEL (label, "Linsn", entry.label_num);
      assemble_integer (gen_rtx_SYMBOL_REF (Pmode, ggc_strdup (label)),
			POINTER_SIZE_UNITS, POINTER_SIZE, 1);
      assemble_integer (GEN_INT (entry.insn_uid), 4, 32, 1);
    }

  switch_to_section (save_section);
  insn_uid_map_entries.release ();
}
