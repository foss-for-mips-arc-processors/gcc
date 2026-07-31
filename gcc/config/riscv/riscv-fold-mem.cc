/* RISC-V memory folding pass
 * The phase is designed to exploit the zba extensions by targeting
 * address generation patterns where an index is being incremented
 * and then used to access an array.  The phase folds constants into
 * memory accesses: instead of performing a separate add and shift
 * or shiftadd followed by a load it folds the cumulative increment
 * directly into the offset field of the load/store instruction.
 * As a result it replaces two or more instructions (an address
 * calculation and a memory access) with a single instruction which
 * reduces both code size and execution time.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "rtl.h"
#include "df.h"
#include "options.h"
#include "insn-config.h"
#include "recog.h"
#include "target.h"
#include "tree-pass.h"
#include "memmodel.h"
#include "emit-rtl.h"
#include "rtl-iter.h"
#include <vector>

namespace
{

/* Configuration data.  */
const pass_data pass_data_riscv_fold_mem = {
  RTL_PASS,		/* type.  */
  "riscv_fold_mem",	/* name.  */
  OPTGROUP_LOOP,	/* optinfo_flags.  */
  TV_NONE,
  0,
  0,
  0,
  0,
  0,
};

class pass_riscv_fold_mem : public rtl_opt_pass
{
public:
  pass_riscv_fold_mem (gcc::context *ctxt)
      : rtl_opt_pass (pass_data_riscv_fold_mem, ctxt)
  {
  }

  /* run if zba extension and 64 bit mode are enabled.  */
  virtual bool
  gate (function *) final override
  {
    return optimize > 0 && TARGET_64BIT && riscv_fold_mem;
  }

  virtual unsigned int execute (function *) override;

private:
  rtx_insn *find_def (rtx_insn *insn, rtx reg);
  rtx_insn *find_nearest_def_in_bb (rtx_insn *insn, rtx reg);
  rtx trace_increments (rtx_insn *insn, rtx reg, HOST_WIDE_INT *total_offset);
};

/* Find the unique definition of REG used in INSN.  */
rtx_insn *
pass_riscv_fold_mem::find_def (rtx_insn *insn, rtx reg)
{
  if (!reg || !REG_P (reg))
    return NULL;

  df_ref use = df_find_use (insn, reg);
  if (!use)
    return NULL;

  struct df_link *defs = DF_REF_CHAIN (use);
  if (!defs || defs->next)
    return NULL;

  return DF_REF_INSN (defs->ref);
}

/* Locate the definition of REG that most closely precedes INSN
   within the same basic block.  */
rtx_insn *
pass_riscv_fold_mem::find_nearest_def_in_bb (rtx_insn *insn, rtx reg)
{
  df_ref def_ref;
  rtx_insn *best_def = NULL;
  int current_luid = DF_INSN_LUID (insn);
  int best_luid = -1;
  basic_block curr_bb = BLOCK_FOR_INSN (insn);

  for (def_ref = DF_REG_DEF_CHAIN (REGNO (reg)); def_ref;
       def_ref = DF_REF_NEXT_REG (def_ref))
    {
      rtx_insn *def_insn = DF_REF_INSN (def_ref);

      if (BLOCK_FOR_INSN (def_insn) == curr_bb)
	{
	  int def_luid = DF_INSN_LUID (def_insn);

	  if (def_luid < current_luid && def_luid > best_luid)
	    {
	      best_luid = def_luid;
	      best_def = def_insn;
	    }
	}
    }
  return best_def;
}

/* Recursively trace register increments to find the root register
 * and calculate the cumulative offset.  */
rtx
pass_riscv_fold_mem::trace_increments (rtx_insn *insn, rtx reg,
				       HOST_WIDE_INT *total_offset)
{
  if (!reg || !REG_P (reg))
    return reg;

  df_ref use = df_find_use (insn, reg);
  if (!use)
    return reg;

  struct df_link *defs = DF_REF_CHAIN (use);
  if (!defs || defs->next)
    return reg;

  rtx_insn *def_insn = DF_REF_INSN (defs->ref);

  if (BLOCK_FOR_INSN (def_insn) != BLOCK_FOR_INSN (insn))
    return reg;

  rtx set = single_set (def_insn);
  if (!set)
    return reg;

  rtx src = SET_SRC (set);
  /* Look for rtx insn:
   * (sign_extend (plus (subreg (reg)) (const_int)))  */
  if (GET_CODE (src) == SIGN_EXTEND && GET_CODE (XEXP (src, 0)) == PLUS)
    {
      rtx plus_op = XEXP (src, 0);
      if (CONST_INT_P (XEXP (plus_op, 1)))
	{
	  *total_offset += INTVAL (XEXP (plus_op, 1));
	  rtx inner_reg = NULL_RTX;

	  if (REG_P (XEXP (plus_op, 0)))
	    inner_reg = XEXP (plus_op, 0);
	  else if (GET_CODE (XEXP (plus_op, 0)) == SUBREG)
	    inner_reg = XEXP (XEXP (plus_op, 0), 0);

	  if (inner_reg != NULL_RTX)
	    return trace_increments (def_insn, inner_reg, total_offset);
	}
    }
  return reg;
}

/* Main entry point for memory folding pass.  */
unsigned int
pass_riscv_fold_mem::execute (function *fun)
{
  df_set_flags (DF_RD_PRUNE_DEAD_DEFS);
  df_chain_add_problem (DF_DU_CHAIN | DF_UD_CHAIN);
  df_analyze ();

  rtx_insn *insn;
  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    {
      if (!NONDEBUG_INSN_P (insn))
	continue;

      rtx set = single_set (insn);
      if (!set)
	continue;

      rtx mem = NULL_RTX;
      rtx src = (GET_CODE (SET_SRC (set)) == SIGN_EXTEND)
		    ? XEXP (SET_SRC (set), 0)
		    : SET_SRC (set);
      rtx dest = (GET_CODE (SET_DEST (set)) == SIGN_EXTEND)
		     ? XEXP (SET_DEST (set), 0)
		     : SET_DEST (set);

      if (MEM_P (src))
	{
	  mem = src;
	}
      else if (MEM_P (dest))
	{
	  mem = dest;
	}
      /* pick only loads or stores.  */
      if (!mem)
	continue;

      rtx addr_reg = XEXP (mem, 0);
      if (!REG_P (addr_reg))
	continue;

      df_ref addr_use = df_find_use (insn, addr_reg);
      if (!addr_use || !DF_REF_CHAIN (addr_use)
	  || DF_REF_CHAIN (addr_use)->next)
	continue;

      /* looking after shiftadd type of instructions through which
       * prior immediate adds can be propagated.  */
      rtx_insn *insn_addr = DF_REF_INSN (DF_REF_CHAIN (addr_use)->ref);
      rtx set_addr = single_set (insn_addr);
      if (!set_addr || GET_CODE (SET_SRC (set_addr)) != PLUS)
	continue;

      rtx plus_src = SET_SRC (set_addr);
      rtx and_rtx = XEXP (plus_src, 0);

      if (GET_CODE (and_rtx) != AND || GET_CODE (XEXP (and_rtx, 0)) != ASHIFT)
	continue;

      rtx index_reg = XEXP (XEXP (and_rtx, 0), 0);
      int shift_amount = INTVAL (XEXP (XEXP (and_rtx, 0), 1));

      HOST_WIDE_INT cumulative_inc = 0;
      rtx root_reg = trace_increments (insn_addr, index_reg, &cumulative_inc);

      if (cumulative_inc == 0 || root_reg == index_reg)
	continue;

      HOST_WIDE_INT scaled_offset = (unsigned HOST_WIDE_INT)cumulative_inc
				    << shift_amount;

      /* prevent immediates over 12bit.  */
      if (!SMALL_OPERAND (scaled_offset))
	continue;

      bool hazard = false;

      for (rtx_insn *curr = NEXT_INSN (insn_addr); curr && curr != insn;
	   curr = NEXT_INSN (curr))
	{
	  if (!NONDEBUG_INSN_P (curr))
	    continue;
	  subrtx_iterator::array_type array;
	  FOR_EACH_SUBRTX (iter, array, PATTERN (curr), NONCONST)
	  {
	    const_rtx x = *iter;
	    if (MEM_P (x))
	      {
		/* If we find any other access that coflicts with the picked
		 * store/load.  */
		if (true_dependence (mem, GET_MODE (mem), x)
		    || canon_output_dependence (mem, false, x, GET_MODE (x),
						curr))
		  {
		    hazard = true;
		    break;
		  }
	      }
	  }
	  if (hazard)
	    break;
	}

      if (hazard)
	continue;

      /* update index register and the load instruction.  */
      validate_change (insn_addr, &XEXP (XEXP (and_rtx, 0), 0), root_reg, 1);
      rtx new_mem_addr = plus_constant (Pmode, addr_reg, scaled_offset);
      validate_change (insn, &XEXP (mem, 0), new_mem_addr, 1);

      if (apply_change_group ())
	{
	  confirm_change_group ();
	  df_insn_rescan_all ();
	}
      else
	cancel_changes (0);
    }

  /* Clean up redundant copies and fold expressions.  */
  basic_block bb;
  FOR_EACH_BB_FN (bb, fun)
  {
    rtx_insn *insn, *next;
    std::vector<std::pair<rtx, rtx> > shadd_exprs;

    for (insn = BB_HEAD (bb); insn != NEXT_INSN (BB_END (bb)); insn = next)
      {
	next = NEXT_INSN (insn);
	if (!NONDEBUG_INSN_P (insn))
	  continue;

	rtx set = single_set (insn);
	if (!set)
	  continue;

	rtx src = SET_SRC (set);
	rtx dest = SET_DEST (set);

	/* registers propagation.  */
	if (REG_P (dest) && REG_P (src))
	  {
	    if (DF_REG_DEF_COUNT (REGNO (src)) == 1)
	      {
		df_ref def_ref = DF_REG_DEF_CHAIN (REGNO (src));
		if (def_ref && !DF_REF_CHAIN (def_ref))
		  {
		    rtx_insn *def_insn = DF_REF_INSN (def_ref);
		    rtx def_set = single_set (def_insn);
		    if (def_set && REG_P (SET_SRC (def_set)))
		      {
			rtx orig_src = SET_SRC (def_set);
			if (validate_change (insn, &SET_SRC (set), orig_src,
					     0))
			  df_insn_rescan (insn);
		      }
		  }
	      }
	  }

	/* Redundancy elimination for shadd expressions.  */
	if (GET_CODE (src) == PLUS && GET_CODE (XEXP (src, 0)) == AND)
	  {
	    rtx existing_reg = NULL_RTX;
	    for (auto const &entry : shadd_exprs)
	      if (rtx_equal_p (src, entry.first))
		{
		  existing_reg = entry.second;
		  break;
		}

	    if (existing_reg)
	      validate_change (insn, &SET_SRC (set), existing_reg, 0);
	    else
	      shadd_exprs.push_back ({ src, dest });
	  }
      }
  }

  df_finish_pass (true);
  return 0;
}

}

/* Create a new instance of the RISC-V memory folding pass.  */
rtl_opt_pass *
make_pass_riscv_fold_mem (gcc::context *ctxt)
{
  return new pass_riscv_fold_mem (ctxt);
}
