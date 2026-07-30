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

#ifndef GCC_INSN_UID_DEBUG_H
#define GCC_INSN_UID_DEBUG_H

extern bool insn_uid_debug_enabled_p (void);
extern void insn_uid_debug_begin_function (void);
extern void insn_uid_debug_emit_insn_label (FILE *, rtx_insn *);
extern void insn_uid_debug_end_function (void);

#endif /* GCC_INSN_UID_DEBUG_H */
