/* Loop versioning pass for IV overflow.
   Copyright (C) 2026 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

GCC is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/* This pass versions loops where an induction variable (IV) may overflow/wrap.
   For IVs with types where overflow is defined (e.g., unsigned short), we
   create a versioned loop with a runtime bounds check that ensures the IV
   won't overflow. Later optimizations can then assume non-wrapping behavior
   in the versioned loop.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "tree.h"
#include "gimple.h"
#include "gimple-iterator.h"
#include "tree-pass.h"
#include "cfgloop.h"
#include "tree-ssa-loop.h"
#include "ssa.h"
#include "tree-scalar-evolution.h"
#include "fold-const.h"
#include "tree-ssa-loop-niter.h"
#include "gimple-pretty-print.h"
#include "cfgloopmanip.h"
#include "gimple-range.h"
#include "gimple-expr.h"
#include "tree-into-ssa.h"

namespace {

struct iv_overflow_info
{
  class loop *loop;
  tree bound;
  bool needs_versioning;
};

class loop_iv_versioning
{
public:
  loop_iv_versioning (function *fn) : m_fn (fn), m_loop_info (NULL) {}
  ~loop_iv_versioning () { free (m_loop_info); }
  unsigned int run ();

private:
  iv_overflow_info analyze_loop (class loop *loop);
  bool version_loop (iv_overflow_info &info);
  class loop *find_outermost_loop_to_version (class loop *loop);
  bool bound_invariant_in_loop_p (class loop *loop, tree bound);

  function *m_fn;
  iv_overflow_info *m_loop_info;
};

/* Arbitrary bound for IV versioning.  */
#define IV_OVERFLOW_BOUND 32768

/* Check if BOUND is invariant in LOOP.  */

bool
loop_iv_versioning::bound_invariant_in_loop_p (class loop *loop, tree bound)
{
  if (TREE_CODE (bound) != SSA_NAME)
    return is_gimple_min_invariant (bound);

  gimple *def = SSA_NAME_DEF_STMT (bound);
  basic_block def_bb = gimple_bb (def);

  if (!def_bb)
    return true;

  return !flow_bb_inside_loop_p (loop, def_bb);
}

/* Analyze LOOP and determine if it can be versioned.
   Checks for unsigned IV tied to the loop bound and verifies all
   prerequisites for versioning.  */

iv_overflow_info
loop_iv_versioning::analyze_loop (class loop *loop)
{
  iv_overflow_info info;
  info.needs_versioning = false;

  if (!loop_outer (loop))
    return info;

  edge exit_edge = single_exit (loop);
  if (!exit_edge)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "Loop %d: no single exit\n", loop->num);
      return info;
    }

  class tree_niter_desc niter;
  gcond *exit_cond;
  if (!number_of_iterations_exit_assumptions (loop, exit_edge, &niter,
					      &exit_cond, true, NULL))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "Loop %d: cannot analyze exit\n", loop->num);
      return info;
    }

  if (niter.bound == NULL_TREE)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "Loop %d: no bound available\n", loop->num);
      return info;
    }

  /* Skip if iteration count is constant and small.  */
  if (niter.niter != NULL_TREE && TREE_CODE (niter.niter) == INTEGER_CST)
    {
      widest_int niter_val = wi::to_widest (niter.niter);
      if (wi::ltu_p (niter_val, IV_OVERFLOW_BOUND))
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "Loop %d: constant niter %ld < %d, skipping\n",
		     loop->num, (long) niter_val.to_shwi (), IV_OVERFLOW_BOUND);
	  return info;
	}
    }

  /* Find the bound - prefer SSA_NAME from exit condition for SCEV.  */
  tree bound = niter.bound;
  if (exit_cond && TREE_CODE (bound) != SSA_NAME)
    {
      tree lhs = gimple_cond_lhs (exit_cond);
      tree rhs = gimple_cond_rhs (exit_cond);
      if (TREE_CODE (rhs) == SSA_NAME
	  && operand_equal_p (expand_simple_operations (rhs), bound, 0))
	bound = rhs;
      else if (TREE_CODE (lhs) == SSA_NAME
	       && operand_equal_p (expand_simple_operations (lhs), bound, 0))
	bound = lhs;
    }

  /* Verify bound is loop-invariant.  */
  if (!bound_invariant_in_loop_p (loop, bound))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "Loop %d: bound not loop-invariant\n", loop->num);
      return info;
    }

  /* Look for an unsigned IV that controls this loop.  */
  tree control_iv = niter.control.base;
  tree control_type = control_iv ? TREE_TYPE (control_iv) : NULL_TREE;

  bool found_unsigned_iv = false;
  tree iv_type = NULL_TREE;

  for (gphi_iterator psi = gsi_start_phis (loop->header);
       !gsi_end_p (psi); gsi_next (&psi))
    {
      gphi *phi = psi.phi ();
      tree def = gimple_phi_result (phi);
      tree type = TREE_TYPE (def);

      if (!INTEGRAL_TYPE_P (type) || TYPE_OVERFLOW_UNDEFINED (type)
	  || !TYPE_UNSIGNED (type))
	continue;

      affine_iv iv;
      if (!simple_iv (loop, loop, def, &iv, false))
	continue;

      if (TREE_CODE (iv.step) != INTEGER_CST
	  || wi::neg_p (wi::to_wide (iv.step), SIGNED)
	  || integer_zerop (iv.step))
	continue;

      if (control_iv && operand_equal_p (def, control_iv, 0))
	{
	  found_unsigned_iv = true;
	  iv_type = type;
	  break;
	}

      if (control_type && types_compatible_p (type, control_type))
	{
	  found_unsigned_iv = true;
	  iv_type = type;
	}
    }

  if (!found_unsigned_iv)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "Loop %d: no unsigned IV found\n", loop->num);
      return info;
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "Loop %d: candidate for versioning, bound: ",
	       loop->num);
      print_generic_expr (dump_file, bound);
      fprintf (dump_file, ", iv_type: ");
      print_generic_expr (dump_file, iv_type);
      fprintf (dump_file, "\n");
    }

  info.loop = loop;
  info.bound = bound;
  info.needs_versioning = true;
  return info;
}

/* Version LOOP with the bounds check from INFO.  Returns true on success.  */

bool
loop_iv_versioning::version_loop (iv_overflow_info &info)
{
  class loop *loop = info.loop;
  tree bound = info.bound;

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "Versioning loop %d with bound: ", loop->num);
      print_generic_expr (dump_file, bound);
      fprintf (dump_file, "\n");
    }

  tree max_val = build_int_cst (TREE_TYPE (bound), IV_OVERFLOW_BOUND);
  tree cond = fold_build2 (LT_EXPR, boolean_type_node, bound, max_val);

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "  condition: ");
      print_generic_expr (dump_file, cond);
      fprintf (dump_file, "\n");
    }

  initialize_original_copy_tables ();
  basic_block cond_bb;
  class loop *nloop = loop_version (loop, (void *) cond, &cond_bb,
				    profile_probability::likely (),
				    profile_probability::unlikely (),
				    profile_probability::likely (),
				    profile_probability::unlikely (),
				    true);
  free_original_copy_tables ();

  if (!nloop)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "  loop_version failed\n");
      return false;
    }

  /* Record iteration bound on versioned loop and all inner loops.  */
  widest_int bound_value = IV_OVERFLOW_BOUND - 1;

  record_niter_bound (loop, bound_value, true, true);
  loop->estimate_state = EST_AVAILABLE;
  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "  recorded bound %d on loop %d\n",
	     IV_OVERFLOW_BOUND - 1, loop->num);

  auto_vec<class loop *> worklist;
  for (class loop *inner = loop->inner; inner; inner = inner->next)
    worklist.safe_push (inner);

  while (!worklist.is_empty ())
    {
      class loop *inner = worklist.pop ();
      record_niter_bound (inner, bound_value, true, true);
      inner->estimate_state = EST_AVAILABLE;
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "  recorded bound %d on loop %d\n",
		 IV_OVERFLOW_BOUND - 1, inner->num);

      for (class loop *child = inner->inner; child; child = child->next)
	worklist.safe_push (child);
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "Successfully versioned loop %d\n", loop->num);

  return true;
}

/* Find the outermost loop where LOOP's bound is still invariant.  */

class loop *
loop_iv_versioning::find_outermost_loop_to_version (class loop *loop)
{
  tree bound = m_loop_info[loop->num].bound;
  class loop *result = loop;

  for (class loop *outer = loop_outer (loop);
       outer && loop_outer (outer);
       outer = loop_outer (outer))
    {
      if (!bound_invariant_in_loop_p (outer, bound))
	break;

      /* All nested loops must need versioning to hoist.  */
      bool all_need_versioning = true;
      for (class loop *inner = outer->inner; inner; inner = inner->next)
	{
	  if (!m_loop_info[inner->num].needs_versioning)
	    {
	      all_need_versioning = false;
	      break;
	    }
	}

      if (!all_need_versioning)
	break;

      result = outer;
    }

  return result;
}

unsigned int
loop_iv_versioning::run ()
{
  gcc_assert (scev_initialized_p ());
  scev_reset_htab ();

  bool changed = false;
  unsigned int num_loops = number_of_loops (m_fn);

  m_loop_info = XCNEWVEC (iv_overflow_info, num_loops);

  for (auto loop : loops_list (m_fn, LI_FROM_INNERMOST))
    {
      m_loop_info[loop->num] = analyze_loop (loop);
    }

  /* Collect loops before modifying since loop_version invalidates iterators.  */
  auto_vec<std::pair<class loop *, iv_overflow_info>> loops_to_version;
  auto_bitmap versioned_loops;

  for (auto loop : loops_list (m_fn, LI_FROM_INNERMOST))
    {
      if (!m_loop_info[loop->num].needs_versioning)
	continue;

      class loop *version_loop = find_outermost_loop_to_version (loop);

      if (bitmap_bit_p (versioned_loops, version_loop->num))
	continue;

      if (dump_file && (dump_flags & TDF_DETAILS) && version_loop != loop)
	fprintf (dump_file, "Hoisting versioning from loop %d to loop %d\n",
		 loop->num, version_loop->num);

      /* Use the original loop's info (bound) even when hoisting, since
	 that's the bound we're checking.  */
      iv_overflow_info info = m_loop_info[loop->num];
      info.loop = version_loop;
      loops_to_version.safe_push (std::make_pair (version_loop, info));
      bitmap_set_bit (versioned_loops, version_loop->num);
    }

  for (auto &entry : loops_to_version)
    {
      if (version_loop (entry.second))
	changed = true;
    }

  if (changed)
    {
      update_ssa (TODO_update_ssa);
      scev_reset_htab ();
    }

  return 0;
}

const pass_data pass_data_iv_bound_versioning =
{
  GIMPLE_PASS,
  "ivbound",
  OPTGROUP_LOOP,
  TV_IV_BOUND_VERSIONING,
  PROP_cfg,
  0,
  0,
  0,
  0,
};

class pass_iv_bound_versioning : public gimple_opt_pass
{
public:
  pass_iv_bound_versioning (gcc::context *ctxt)
    : gimple_opt_pass (pass_data_iv_bound_versioning, ctxt)
  {}

  bool gate (function *) final override
  {
    return flag_version_loops_for_iv_overflow;
  }

  unsigned int execute (function *fn) final override
  {
    if (number_of_loops (fn) <= 1)
      return 0;

    enable_ranger (fn);
    unsigned int ret = loop_iv_versioning (fn).run ();
    disable_ranger (fn);

    return ret;
  }
};

} // anon namespace

gimple_opt_pass *
make_pass_iv_bound_versioning (gcc::context *ctxt)
{
  return new pass_iv_bound_versioning (ctxt);
}
