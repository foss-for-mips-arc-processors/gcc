/* Pointer-chasing loop optimization pass.
   Copyright (C) 2020-2024 Free Software Foundation, Inc.
   Contributed by Chao-ying Fu (cfu@wavecomp.com)

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

/* This file contains the implementation of optimizing pointer-chasing loops.
   The algorithm is as follows.
   1.  Find a simple loop that has only two basic blocks: header and latch.
      The header block has two successors.  The latch block has one predecessor
      and two successors.  Both blocks have the last instruction as a jump.
   2.  Find if the first instruction in the latch block is a pointer-chasing
      load that uses and sets the same base register.
   3.  Find if there is any load instruction in the header block that uses
      the same base register.
      This proves that it is safe to move the pointer-chasing load to the
      header block, because loads are safe to use the same base register.
   4.  Move the pointer-chasing load to the header block before the jump
      instruction, by changing the destination to a new virtual register.
      A new instruction that moves the new virtual register to the base
      register is inserted to the first instruction in the latch block.

   This optimization is beneficial, because the pointer-chasing load is
   executed earlier in the header block, so the testing of the base
   register against zero is not stalled in the latch block.
*/

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "target.h"
#include "rtl.h"
#include "tree.h"
#include "memmodel.h"
#include "regs.h"
#include "insn-attr.h"
#include "cfgrtl.h"
#include "cfgloop.h"
#include "expr.h"
#include "tree-pass.h"

#ifdef INSN_SCHEDULING

/* A simple pointer chasing loop has 2 BBs - a header and a latch.
   The header has two successors.
   The latch has one predecessor and two successors.
   The header has a jump at the end.
   The latch has a jump at the end.  */
#define SIMPLE_LOOP_P(loop) ((loop->num_nodes == 2)			\
			     && (EDGE_COUNT (loop->header->succs) == 2)	\
			     && (EDGE_COUNT (loop->latch->preds) == 1)	\
			     && (EDGE_COUNT (loop->latch->succs) == 2)	\
			     && JUMP_P (BB_END (loop->header))		\
			     && JUMP_P (BB_END (loop->latch)))

/* Check if BB has any insn that is a load and uses base.  */

static bool
bb_has_load_use_base_p (basic_block bb, rtx this_base)
{
  rtx set, src, dst, base;
  rtx_insn *insn;

  FOR_BB_INSNS (bb, insn)
    {
      if ((set = single_set (insn)) == NULL)
	continue;

      src = SET_SRC (set);
      dst = SET_DEST (set);

      /* Make sure it is a load insn and non volatile.  */
      if (!REG_P (dst) || !MEM_P (src) || MEM_VOLATILE_P (src))
	continue;

      base = XEXP (src, 0);
      if (GET_CODE (base) == PLUS)
	base = XEXP (base, 0);

      /* Make sure dst and base are the same.  */
      if (rtx_equal_p (this_base, base))
	{
	  if (dump_file)
	     fprintf (dump_file, "find a load uses same base uid = %i\n",
		      INSN_UID (insn));
	  return true;
	}
      else
	{
	  if (dump_file)
	     fprintf (dump_file, "find a load uses different base uid = %i\n",
		      INSN_UID (insn));
	}
    }

  return false;
}

/* Check if insn is a pointer-chasing load.  */

static bool
pointer_chasing_load_p (rtx_insn *insn)
{
  rtx set, src, dst, base;

  /* Make sure it is a single set insn.  */
  if ((set = single_set (insn)) == NULL)
    return false;

  src = SET_SRC (set);
  dst = SET_DEST (set);

  /* Make sure it is a load insn and non volatile.  */
  if (!REG_P (dst) || !MEM_P (src) || MEM_VOLATILE_P (src))
    return false;

  base = XEXP (src, 0);
  if (GET_CODE (base) == PLUS)
    base = XEXP (base, 0);

  /* Make sure dst and base are the same.  */
  if (!rtx_equal_p (dst, base))
    return false;

  return true;
}

/* Optimize the pointer chasing loop by moving the pointer-chasing load from
   the latch to the header.  */

static void
optimize_pointer_chasing ()
{
  rtx_insn *insn, *last_insn, *move_insn, *move_insn2;
  rtx old_src, old_dst, new_reg;

  loop_optimizer_init (LOOPS_HAVE_PREHEADERS
		       | LOOPS_HAVE_RECORDED_EXITS);

  if (number_of_loops (cfun) <= 1)
    {
      loop_optimizer_finalize ();
      return;
    }

  for (auto loop : loops_list (cfun, 0))
    {
      if (dump_file)
	{
	  fprintf (dump_file, "loop num: %d", loop->num);
	  insn = BB_END (loop->header);
	  if (INSN_HAS_LOCATION (insn))
	    {
	      expanded_location xloc = insn_location (insn);
	      fprintf (dump_file, " %s:%i", xloc.file, xloc.line);
	    }
	  fprintf (dump_file, "\n");
	}

      if (SIMPLE_LOOP_P (loop))
	{
	  FOR_BB_INSNS (loop->latch, insn)
	    {
	      if (!INSN_P (insn))
		continue;

	      if (targetm.pointer_chasing_load_profitable_p ()
		  && pointer_chasing_load_p (insn)
		  && bb_has_load_use_base_p (loop->header,
					     SET_DEST (single_set (insn))))
		{
		  if (dump_file)
		    fprintf (dump_file,
			     "optimize pointer chasing load uid = %i\n",
			     INSN_UID (insn));

		  last_insn = BB_END (loop->header);
		  old_src = SET_SRC (single_set (insn));
		  old_dst = SET_DEST (single_set (insn));
		  new_reg = gen_reg_rtx (GET_MODE (old_dst));
		  move_insn = gen_move_insn (new_reg, old_src);
		  emit_insn_before (move_insn, last_insn);
		  move_insn2 = gen_move_insn (old_dst, new_reg);
		  emit_insn_after (move_insn2, insn);
		  delete_insn (insn);
		}

		/* Done with scanning the first instruction.  */
		break;
	    }
	}
    }

  loop_optimizer_finalize ();
}
#endif /* INSN_SCHEDULING.  */

/* Return true if hosting pointer-chasing load is profitable.  */

bool
default_pointer_chasing_load_profitable_p ()
{
  return false;
}

namespace {

const pass_data pass_data_pointer_chasing =
{
  RTL_PASS, /* type.  */
  "pointer_chasing", /* name.  */
  OPTGROUP_NONE, /* optinfo_flags.  */
  TV_POINTER_CHASING, /* tv_id.  */
  0, /* properties_required.  */
  0, /* properties_provided.  */
  0, /* properties_destroyed.  */
  0, /* todo_flags_start.  */
  TODO_df_finish, /* todo_flags_finish.  */
};

class pass_pointer_chasing : public rtl_opt_pass
{
public:
  pass_pointer_chasing (gcc::context *ctxt)
    : rtl_opt_pass (pass_data_pointer_chasing, ctxt)
  {}

  /* opt_pass methods: */
  virtual bool gate (function *)
  {
    return optimize > 1 && flag_pointer_chasing;
  }

  virtual unsigned int execute (function *fun ATTRIBUTE_UNUSED)
  {
#ifdef INSN_SCHEDULING
    basic_block bb;

    /* Collect loop information to used.  */
    cfg_layout_initialize (0);
    optimize_pointer_chasing ();

    /* Update the life information, because we add pseudos.  */
    max_regno = max_reg_num ();

    /* Finalize layout changes.  */
    FOR_EACH_BB_FN (bb, fun)
    if (bb->next_bb != EXIT_BLOCK_PTR_FOR_FN (fun))
      bb->aux = bb->next_bb;
    free_dominance_info (CDI_DOMINATORS);
    cfg_layout_finalize ();
#endif /* INSN_SCHEDULING.  */
    return 0;
  }

}; // class pass_pointer_chasing

} // anon namespace

rtl_opt_pass *
make_pass_pointer_chasing (gcc::context *ctxt)
{
  return new pass_pointer_chasing (ctxt);
}
