/* Subroutines used for code generation for Synopsys ARC-V processors.
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

/* Scheduler state tracking for dual-pipe ARCV architectures.  */

struct arcv_sched_state {
  /* True if the ALU pipe has been scheduled for the current cycle.
     The ALU pipe handles arithmetic, logical, and other computational
     instructions.  */
  int alu_pipe_scheduled_p;

  /* True if pipe B has been scheduled for the current cycle.
     Pipe B is the second execution pipe, typically used for memory
     operations (loads/stores) but can also handle other instructions.  */
  int pipeB_scheduled_p;

  /* The last instruction that was scheduled.  Used to detect fusion
     opportunities by looking ahead at the next instruction to be
     scheduled.  */
  rtx_insn *last_scheduled_insn;

  /* Cached value of how many more instructions can be issued in the
     current cycle.  Updated as instructions are scheduled and pipes
     become occupied.  */
  short cached_can_issue_more;
};

static struct arcv_sched_state sched_state;

/* If INSN is a load or store of address in the form of [base+offset],
   extract the two parts and set to BASE and OFFSET.  IS_LOAD is set
   to TRUE if it's a load.  Return TRUE if INSN is such an instruction,
   otherwise return FALSE.  */

static bool
arcv_fusion_load_store (rtx_insn *insn, rtx *base, rtx *offset,
			machine_mode *mode, bool *is_load)
{
  rtx x, dest, src;

  gcc_assert (INSN_P (insn));
  x = PATTERN (insn);
  if (GET_CODE (x) != SET)
    return false;

  src = SET_SRC (x);
  dest = SET_DEST (x);

  if ((GET_CODE (src) == SIGN_EXTEND || GET_CODE (src) == ZERO_EXTEND)
      && MEM_P (XEXP (src, 0)))
    src = XEXP (src, 0);

  if (REG_P (src) && MEM_P (dest))
    {
      *is_load = false;
      if (extract_base_offset_in_addr (dest, base, offset))
	*mode = GET_MODE (dest);
    }
  else if (MEM_P (src) && REG_P (dest))
    {
      *is_load = true;
      if (extract_base_offset_in_addr (src, base, offset))
	*mode = GET_MODE (src);
    }
  else
    return false;

  return (*base != NULL_RTX && *offset != NULL_RTX);
}

/* Return TRUE if the target microarchitecture supports macro-op
   fusion for two memory operations of mode MODE (the direction
   of transfer is determined by the IS_LOAD parameter).  */

bool
arcv_pair_fusion_mode_allowed_p (machine_mode mode, bool is_load)
{
  return ((is_load && (mode == SImode
		       || mode == HImode
		       || mode == QImode))
	  || (!is_load && mode == SImode));
}

bool
arcv_sched_fusion_priority (rtx_insn *insn, int max_pri, int *fusion_pri,
			     int *pri)
{
  rtx base, offset;
  machine_mode mode = SImode;
  bool is_load;

  gcc_assert (INSN_P (insn));

  /* Default priority for non-fusible instructions.  */
  int default_pri = max_pri - 1;

  /* Check if this is a fusible load/store instruction.  */
  if (!arcv_fusion_load_store (insn, &base, &offset, &mode, &is_load)
      || !arcv_pair_fusion_mode_allowed_p (mode, is_load))
      return false;

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
  priority -= ((REGNO (base) & BASE_REG_MASK) << BASE_REG_SHIFT);

  /* Calculate fusion priority: group loads/stores with adjacent addresses
     into the same scheduling group.  We divide the offset by (mode_size * 2)
     to group pairs of adjacent accesses, then shift left by 1 to make room
     for the load/store bit.  */
  int off_val = (int)(INTVAL (offset));
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

/* Initialize ARCV scheduler state at the beginning of scheduling.  */

void
arcv_sched_init (void)
{
  sched_state.last_scheduled_insn = 0;
}

/* Try to reorder ready queue to promote ARCV fusion opportunities.
   Returns the number of instructions that can be issued this cycle.  */

int
arcv_sched_reorder2 (rtx_insn **ready, int *n_readyp)
{
  if (sched_fusion)
    return sched_state.cached_can_issue_more;

  if (!sched_state.cached_can_issue_more)
    return 0;

  /* Fuse double load/store instances missed by sched_fusion.  */
  if (!sched_state.pipeB_scheduled_p && sched_state.last_scheduled_insn
      && ready && *n_readyp > 0
      && !SCHED_GROUP_P (sched_state.last_scheduled_insn)
      && (get_attr_type (sched_state.last_scheduled_insn) == TYPE_LOAD
	  || get_attr_type (sched_state.last_scheduled_insn) == TYPE_STORE))
    {
      for (int i = 1; i <= *n_readyp; i++)
       {
	 rtx_insn* next_insn = next_nonnote_nondebug_insn_bb (ready[*n_readyp - i]);
	 /* Try to fuse the last_scheduled_insn with.  */
	 /* Fuse only with nondebug insn.  */
	 if (NONDEBUG_INSN_P (ready[*n_readyp - i])
	     /* Which have not been already fused.  */
	     && !SCHED_GROUP_P (ready[*n_readyp - i])
	     && (!next_insn || !NONDEBUG_INSN_P (next_insn)
		 || !SCHED_GROUP_P (next_insn))
	     && riscv_macro_fusion_pair_p (sched_state.last_scheduled_insn,
					   ready[*n_readyp - i]))
	   {
	     std::swap (ready[*n_readyp - 1], ready[*n_readyp - i]);
	     SCHED_GROUP_P (ready[*n_readyp - 1]) = 1;
	     sched_state.pipeB_scheduled_p = 1;
	     return sched_state.cached_can_issue_more;
	  }
       }
      sched_state.pipeB_scheduled_p = 1;
    }

  /* Try to fuse a non-memory last_scheduled_insn.  */
  if ((!sched_state.alu_pipe_scheduled_p || !sched_state.pipeB_scheduled_p)
      && sched_state.last_scheduled_insn && ready && *n_readyp > 0
      && !SCHED_GROUP_P (sched_state.last_scheduled_insn)
      && (get_attr_type (sched_state.last_scheduled_insn) != TYPE_LOAD
	  && get_attr_type (sched_state.last_scheduled_insn) != TYPE_STORE))
    {
      for (int i = 1; i <= *n_readyp; i++)
       {
	 rtx_insn* next_insn
	   = next_nonnote_nondebug_insn_bb (ready[*n_readyp - i]);
	 if (NONDEBUG_INSN_P (ready[*n_readyp - i])
	     && !SCHED_GROUP_P (ready[*n_readyp - i])
	     && active_insn_p (ready[*n_readyp - i])
	     && (!next_insn || !NONDEBUG_INSN_P (next_insn)
		 || !SCHED_GROUP_P (next_insn))
	     && riscv_macro_fusion_pair_p (sched_state.last_scheduled_insn,
					   ready[*n_readyp - i]))
	   {
	     if (get_attr_type (ready[*n_readyp - i]) == TYPE_LOAD
		 || get_attr_type (ready[*n_readyp - i]) == TYPE_STORE)
	     {
	       if (sched_state.pipeB_scheduled_p)
		 continue;
	       else
		 sched_state.pipeB_scheduled_p = 1;
	     }
	     else if (!sched_state.alu_pipe_scheduled_p)
	       sched_state.alu_pipe_scheduled_p = 1;
	     else
	       sched_state.pipeB_scheduled_p = 1;

	     std::swap (ready[*n_readyp - 1], ready[*n_readyp - i]);
	     SCHED_GROUP_P (ready[*n_readyp - 1]) = 1;
	     return sched_state.cached_can_issue_more;
	   }
       }
      sched_state.alu_pipe_scheduled_p = 1;
    }
  /* When pipe B is scheduled, we can have no more memops this cycle.  */
  if (sched_state.pipeB_scheduled_p && *n_readyp > 0
      && NONDEBUG_INSN_P (ready[*n_readyp - 1])
      && recog_memoized (ready[*n_readyp - 1]) >= 0
      && !SCHED_GROUP_P (ready[*n_readyp - 1])
      && (get_attr_type (ready[*n_readyp - 1]) == TYPE_LOAD
	  || get_attr_type (ready[*n_readyp - 1]) == TYPE_STORE))
  {
    if (sched_state.alu_pipe_scheduled_p)
      return 0;

    for (int i = 2; i <= *n_readyp; i++)
      {
       rtx_insn* next_insn
	 = next_nonnote_nondebug_insn_bb (ready[*n_readyp - i]);
       if ((NONDEBUG_INSN_P (ready[*n_readyp - i])
	    && recog_memoized (ready[*n_readyp - i]) >= 0
	    && get_attr_type (ready[*n_readyp - i]) != TYPE_LOAD
	    && get_attr_type (ready[*n_readyp - i]) != TYPE_STORE
	    && !SCHED_GROUP_P (ready[*n_readyp - i])
	    && (!next_insn || !NONDEBUG_INSN_P (next_insn)
		|| !SCHED_GROUP_P (next_insn)))
	   || (next_insn && NONDEBUG_INSN_P (next_insn)
	       && recog_memoized (next_insn) >= 0
	       && get_attr_type (next_insn) != TYPE_LOAD
	       && get_attr_type (next_insn) != TYPE_STORE))
	 {
	   std::swap (ready[*n_readyp - 1], ready[*n_readyp - i]);
	   sched_state.alu_pipe_scheduled_p = 1;
	   sched_state.cached_can_issue_more = 1;
	   return 1;
	 }
      }
    return 0;
  }

  /* If all else fails, schedule a single instruction.  */
  if (ready && *n_readyp > 0
      && NONDEBUG_INSN_P (ready[*n_readyp - 1])
      && recog_memoized (ready[*n_readyp - 1]) >= 0)
  {
    rtx_insn *insn = ready[*n_readyp - 1];
    enum attr_type insn_type = get_attr_type (insn);

    /* Memory operations go to pipeB if available.  */
    if (!sched_state.pipeB_scheduled_p
       && (insn_type == TYPE_LOAD || insn_type == TYPE_STORE))
    {
      sched_state.pipeB_scheduled_p = 1;
      sched_state.cached_can_issue_more = 1;
    }
    /* Non-memory operations go to ALU pipe.  */
    else if (insn_type != TYPE_LOAD && insn_type != TYPE_STORE)
    {
      sched_state.alu_pipe_scheduled_p = 1;
      sched_state.cached_can_issue_more = 1;
    }
  }

  return sched_state.cached_can_issue_more;
}

int
arcv_sched_adjust_priority (rtx_insn *insn, int priority)
{
  /* Bump the priority of fused load-store pairs for easier
     scheduling of the memory pipe.  The specific increase
     value is determined empirically.  */
  rtx_insn *next = next_nonnote_nondebug_insn_bb (insn);
  if (next && single_set (insn) && single_set (next)
      && SCHED_GROUP_P (next)
      && ((get_attr_type (insn) == TYPE_STORE
	   && get_attr_type (next) == TYPE_STORE)
	  || (get_attr_type (insn) == TYPE_LOAD
	      && get_attr_type (next) == TYPE_LOAD)))
    return priority + 1;

  return priority;
}

/* Adjust scheduling cost for ARCV fusion.  */

int
arcv_sched_adjust_cost (rtx_insn *insn, int dep_type, int cost)
{
  if (dep_type == REG_DEP_ANTI && !SCHED_GROUP_P (insn))
    return cost + 1;

  return cost;
}

bool
arcv_can_issue_more_p (int issue_rate, int more)
{
  /* Beginning of cycle - reset variables.  */
  if (more == issue_rate)
    {
      sched_state.alu_pipe_scheduled_p = 0;
      sched_state.pipeB_scheduled_p = 0;
    }

  if (sched_state.alu_pipe_scheduled_p && sched_state.pipeB_scheduled_p)
    {
      sched_state.cached_can_issue_more = 0;
      return false;
    }

  sched_state.cached_can_issue_more = more;

  return true;
}

int
arcv_sched_variable_issue (rtx_insn *insn, int more)
{
  rtx_insn *next = next_nonnote_nondebug_insn_bb (insn);
  if (next && single_set (insn) && single_set (next)
      && SCHED_GROUP_P (next))
    {
      if (get_attr_type (insn) == TYPE_LOAD
	  || get_attr_type (insn) == TYPE_STORE
	  || get_attr_type (next) == TYPE_LOAD
	  || get_attr_type (next) == TYPE_STORE)
	sched_state.pipeB_scheduled_p = 1;
      else
	sched_state.alu_pipe_scheduled_p = 1;
    }

  if (get_attr_type (insn) == TYPE_ALU_FUSED
      || get_attr_type (insn) == TYPE_IMUL_FUSED)
    {
      sched_state.alu_pipe_scheduled_p = 1;
      more -= 1;
    }

  sched_state.last_scheduled_insn = insn;
  sched_state.cached_can_issue_more = more - 1;

  return sched_state.cached_can_issue_more;
}
