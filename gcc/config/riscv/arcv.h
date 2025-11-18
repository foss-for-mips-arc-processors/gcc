/* Definition of Synopsys ARC-V processors.
   Copyright (C) 2025 Free Software Foundation, Inc.

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

#ifndef GCC_RISCV_ARCV_H
#define GCC_RISCV_ARCV_H

/* ARCV scheduler interface functions.  */
extern bool arcv_can_issue_more_p (int);
extern int arcv_sched_variable_issue (rtx_insn *, int);
extern bool arcv_macro_fusion_pair_p (rtx_insn *, rtx_insn *);
extern void arcv_sched_init (void);
extern int arcv_sched_reorder2 (rtx_insn **, int *);
extern int arcv_sched_adjust_priority (rtx_insn *, int);
extern int arcv_sched_adjust_cost (rtx_insn *, int, int);
extern void arcv_sched_fusion_priority (rtx_insn *, int, int *, int *);

#endif /* GCC_RISCV_ARCV_H */

