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
};

static struct arcv_sched_state sched_state;

static bool
arcv_memop_p (rtx_insn *insn)
{
  enum attr_type type = get_attr_type (insn);
  return (type == TYPE_LOAD || type == TYPE_STORE
	  || type == TYPE_FPLOAD || type == TYPE_FPSTORE);
}

/* Try to reorder ready queue to promote ARCV fusion opportunities.
   Returns the number of instructions that can be issued this cycle.  */

int
arcv_sched_reorder2 (rtx_insn **ready, int *n_readyp)
{
  if (sched_fusion)
    return riscv_cached_can_issue_more;

  if (!riscv_cached_can_issue_more)
    return 0;

  /* Fuse double load/store instances missed by sched_fusion.  */
  if (!sched_state.pipeB_scheduled_p && riscv_last_scheduled_insn
      && ready && *n_readyp > 0
      && !SCHED_GROUP_P (riscv_last_scheduled_insn)
      && arcv_memop_p (riscv_last_scheduled_insn))
    {
      for (int i = 1; i <= *n_readyp; i++)
       {
	 rtx_insn *next_insn
	   = next_nonnote_nondebug_insn_bb (ready[*n_readyp - i]);
	 /* Try to fuse the last_scheduled_insn with.  */
	 /* Fuse only with nondebug insn.  */
	 if (NONDEBUG_INSN_P (ready[*n_readyp - i])
	     /* Which have not been already fused.  */
	     && !SCHED_GROUP_P (ready[*n_readyp - i])
	     && (!next_insn || !NONDEBUG_INSN_P (next_insn)
		 || !SCHED_GROUP_P (next_insn))
	     && riscv_macro_fusion_pair_p (riscv_last_scheduled_insn,
					   ready[*n_readyp - i]))
	   {
	     std::swap (ready[*n_readyp - 1], ready[*n_readyp - i]);
	     SCHED_GROUP_P (ready[*n_readyp - 1]) = 1;
	     sched_state.pipeB_scheduled_p = 1;
	     return riscv_cached_can_issue_more;
	  }
       }
      sched_state.pipeB_scheduled_p = 1;
    }

  /* Try to fuse a non-memory last_scheduled_insn.  */
  if ((!sched_state.alu_pipe_scheduled_p || !sched_state.pipeB_scheduled_p)
      && riscv_last_scheduled_insn && ready && *n_readyp > 0
      && !SCHED_GROUP_P (riscv_last_scheduled_insn)
      && !arcv_memop_p (riscv_last_scheduled_insn))
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
	     && riscv_macro_fusion_pair_p (riscv_last_scheduled_insn,
					   ready[*n_readyp - i]))
	   {
	     if (arcv_memop_p (ready[*n_readyp - i]))
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
	     return riscv_cached_can_issue_more;
	   }
       }
      sched_state.alu_pipe_scheduled_p = 1;
    }
  /* When pipe B is scheduled, we can have no more memops this cycle.  */
  if (sched_state.pipeB_scheduled_p && *n_readyp > 0
      && NONDEBUG_INSN_P (ready[*n_readyp - 1])
      && recog_memoized (ready[*n_readyp - 1]) >= 0
      && !SCHED_GROUP_P (ready[*n_readyp - 1]))
  {
    rtx_insn *head_next = next_nonnote_nondebug_insn_bb (ready[*n_readyp - 1]);
    if (arcv_memop_p (ready[*n_readyp - 1])
	|| (head_next && NONDEBUG_INSN_P (head_next)
	    && SCHED_GROUP_P (head_next) && recog_memoized (head_next) >= 0
	    && arcv_memop_p (head_next)))
    {
      if (sched_state.alu_pipe_scheduled_p)
	return 0;

      for (int i = 2; i <= *n_readyp; i++)
	{
	 rtx_insn* next_insn
	   = next_nonnote_nondebug_insn_bb (ready[*n_readyp - i]);
	 if ((NONDEBUG_INSN_P (ready[*n_readyp - i])
	      && recog_memoized (ready[*n_readyp - i]) >= 0
	      && !arcv_memop_p (ready[*n_readyp - i])
	      && !SCHED_GROUP_P (ready[*n_readyp - i])
	      && (!next_insn || !NONDEBUG_INSN_P (next_insn)
		  || !SCHED_GROUP_P (next_insn)))
	     || (next_insn && NONDEBUG_INSN_P (next_insn)
		 && recog_memoized (next_insn) >= 0
		 && !arcv_memop_p (next_insn)))
	   {
	     std::swap (ready[*n_readyp - 1], ready[*n_readyp - i]);
	     sched_state.alu_pipe_scheduled_p = 1;
	     riscv_cached_can_issue_more = 1;
	     return 1;
	   }
	}
      return 0;
    }
  }

  /* If all else fails, schedule a single (fused) instruction.  */
  if (ready && *n_readyp > 0
      && NONDEBUG_INSN_P (ready[*n_readyp - 1])
      && recog_memoized (ready[*n_readyp - 1]) >= 0)
  {
    rtx_insn *next_insn = next_nonnote_nondebug_insn_bb (ready[*n_readyp - 1]);

    riscv_cached_can_issue_more
      = next_insn && NONDEBUG_INSN_P (next_insn) && SCHED_GROUP_P (next_insn)
	? 2 : 1;
  }

  return riscv_cached_can_issue_more;
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
arcv_can_issue_more_p (int issue_rate, int more, rtx_insn *insn)
{
  /* Beginning of cycle - reset variables.  */
  if (more == issue_rate)
    {
      sched_state.alu_pipe_scheduled_p = 0;
      sched_state.pipeB_scheduled_p = 0;
    }

  if (!(insn && NONDEBUG_INSN_P (insn) && SCHED_GROUP_P (insn))
      && sched_state.alu_pipe_scheduled_p && sched_state.pipeB_scheduled_p)
    {
      riscv_cached_can_issue_more = 0;
      return false;
    }

  riscv_cached_can_issue_more = more;

  return true;
}

int
arcv_sched_variable_issue (rtx_insn *insn, int more)
{
  rtx_insn *next = next_nonnote_nondebug_insn_bb (insn);
  if (next && NONDEBUG_INSN_P (next) && SCHED_GROUP_P (next)
      && single_set (insn) && single_set (next))
    {
      if (arcv_memop_p (insn) || arcv_memop_p (next)
	  || sched_state.alu_pipe_scheduled_p)
	sched_state.pipeB_scheduled_p = 1;
      else
	sched_state.alu_pipe_scheduled_p = 1;
    }

  riscv_last_scheduled_insn = insn;
  riscv_cached_can_issue_more = more - 1;

  return riscv_cached_can_issue_more;
}

/* Check whether out_insn's output reg is passed into input register 3 of
   an fmadd instruction.  */
bool
arcv_fmadd_acc_bypass_p (rtx_insn *out_insn, rtx_insn *in_insn)
{
  rtx out_set = single_set (out_insn);
  rtx in_set  = single_set (in_insn);

  if (!out_set || !in_set || !REG_P (SET_DEST (out_set)))
    return false;

  rtx src = SET_SRC (in_set);

  if (GET_CODE (src) == NEG)
    src = XEXP (src, 0);

  if (GET_CODE (src) != FMA)
    return false;

  rtx acc = XEXP (src, 2);
  if (GET_CODE (acc) == NEG)
    acc = XEXP (acc, 0);

  return REG_P (acc) && REGNO (acc) == REGNO (SET_DEST (out_set));
}
