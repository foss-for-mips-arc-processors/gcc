/* Subroutines used for code generation for ARC-V processors.
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

bool
arcv_sched_fusion_priority (rtx_insn *insn, int max_pri, int *fusion_pri,
			     int *pri)
{
  gcc_assert (INSN_P (insn));

  /* Default priority for non-fusible instructions.  */
  int default_pri = max_pri - 1;

  struct riscv_fusion_mem_info mem;

  if (!riscv_fuse_mem_p (insn, &mem)
      || riscv_fuse_mem_direction (insn) == RISCV_FUSION_NONE)
    return false;

  machine_mode mode = mem.mode;
  int base = riscv_regno (mem.addr.reg);
  bool is_load = mem.type & (SCHED_FUSION_LD | SCHED_FUSION_LD_SIGN_EXTEND
			     | SCHED_FUSION_LD_ZERO_EXTEND);

  /* Start with half the default priority to distinguish fusible from
     non-fusible instructions.  */
  int priority = default_pri / 2;

  /* Scale priority by access width - narrower accesses get lower priority.
     HImode: divide by 2, QImode: divide by 4.  This encourages wider
     accesses to be scheduled together.  */
  if (mode == HImode)
    priority /= 2;
  else if (mode == QImode)
    priority /= 4;

  /* Factor in base register: instructions with smaller register numbers
     get higher priority.  The shift by 20 bits ensures this is the most
     significant component of the priority.  */
  const int BASE_REG_SHIFT = 20;
  const int BASE_REG_MASK = 0xff;
  priority -= (base & BASE_REG_MASK) << BASE_REG_SHIFT;

  /* Calculate fusion priority: group loads/stores with adjacent addresses
     into the same scheduling group.  We divide the offset by (mode_size * 2)
     to group pairs of adjacent accesses, then shift left by 1 to make room
     for the load/store bit.  */
  int off_val = (int)(INTVAL (mem.addr.offset));
  int addr_group = off_val / (GET_MODE_SIZE (mode).to_constant () * 2);
  *fusion_pri = priority - (addr_group << 1) + is_load;

  /* Factor in the actual offset value: instructions with smaller offsets
     get higher priority.  We use only the lower 20 bits to avoid overflow.  */
  const int OFFSET_MASK = 0xfffff;
  if (off_val >= 0)
    priority -= (off_val & OFFSET_MASK);
  else
    priority += ((-off_val) & OFFSET_MASK);

  *pri = priority;

  return true;
}
