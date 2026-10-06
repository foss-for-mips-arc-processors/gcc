// LoadPair fusion optimization pass for riscv.
// Copyright (C) 2023-2025 Free Software Foundation, Inc.
//
// This file is part of GCC.
//
// GCC is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// GCC is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GCC; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "rtl.h"
#include "memmodel.h"
#include "emit-rtl.h"
#include "tm_p.h"
#include "rtl-iter.h"
#include "tree-pass.h"
#include "insn-attr.h"
#include "pair-fusion.h"

struct riscv_pair_fusion : public pair_fusion
{
  bool pair_mem_insn_p (rtx_insn *rti, bool &load_p) override final;

  bool pair_mem_ok_with_policy (rtx base_mem __attribute__((unused)),
    bool load_p __attribute__((unused))) override final
  {
    return true;
  }

  bool pair_reg_and_mem_ok_with_policy (rtx pat1, rtx pat2,
    bool load_p) override final
  {
    rtx operands[4];

    gcc_assert (GET_CODE (pat1) == SET && GET_CODE (pat2) == SET);

    operands[0] = SET_DEST (pat1);
    operands[1] = SET_SRC (pat1);
    operands[2] = SET_DEST (pat2);
    operands[3] = SET_SRC (pat2);

    if (load_p)
    {
      operands[1] = GET_CODE (operands[1]) == SIGN_EXTEND
      || GET_CODE (operands[1]) == ZERO_EXTEND
      ? XEXP (operands[1], 0) : operands[1];

      operands[3] = GET_CODE (operands[3]) == SIGN_EXTEND
      || GET_CODE (operands[3]) == ZERO_EXTEND
      ? XEXP (operands[3], 0) : operands[3];
    } else
    {
      operands[0] = GET_CODE (operands[0]) == SIGN_EXTEND
      || GET_CODE (operands[0]) == ZERO_EXTEND
      ? XEXP (operands[0], 0) : operands[0];

      operands[2] = GET_CODE (operands[2]) == SIGN_EXTEND
      || GET_CODE (operands[2]) == ZERO_EXTEND
      ? XEXP (operands[2], 0) : operands[2];
    }

    machine_mode mode = GET_MODE (operands[1]);

    return riscv_load_store_bonding_p (operands, mode, load_p);
  }

  bool pair_operand_mode_ok_p (machine_mode mode) override final;

  rtx gen_pair (rtx *pats, rtx writeback, bool load_p) override final;

  bool pair_reg_operand_ok_p (bool load_p __attribute__((unused)),
      rtx reg_op __attribute__((unused)),
      machine_mode mode __attribute__((unused))) override final
  {
    return true;
  }

  int pair_mem_alias_check_limit () override final
  {
    return riscv_load_store_alias_check_limit;
  }

  bool should_handle_writeback (writeback_type which __attribute__((unused)))
      override final
  {
    return false;
  }

  bool track_loads_p () override final
  {
    return true;
  }

  bool track_stores_p () override final
  {
    return true;
  }

  bool pair_mem_in_range_p (HOST_WIDE_INT offset) override final
  {
    return true;
  }

  rtx gen_promote_writeback_pair (rtx wb_effect, rtx mem, rtx regs[2],
				  bool load_p) override final;

  rtx destructure_pair (rtx regs[2], rtx pattern, bool load_p) override final;
};

bool
riscv_pair_fusion::pair_mem_insn_p (rtx_insn *rti __attribute__((unused)),
      bool &load_p __attribute__((unused)))
{
  return false;
}

rtx
riscv_pair_fusion::gen_pair (rtx *pats, rtx writeback __attribute__((unused)),
      bool load_p __attribute__((unused)))
{
  auto patvec = gen_rtvec (2, pats[0], pats[1]);
  return gen_rtx_PARALLEL (VOIDmode, patvec);
}

// Return true if we should consider forming ldp/stp insns from memory
// accesses with operand mode MODE at this stage in compilation.
bool
riscv_pair_fusion::pair_operand_mode_ok_p (machine_mode mode)
{
  /* Check the supported modes.  */
  if (mode == HImode || mode == SImode)
    {
      return true;		/* Ok.  */
    }
  else if (mode == DImode)
    {
      if (!TARGET_64BIT)
	return false;
    }
  else if (mode == SFmode)
    {
      if (!TARGET_HARD_FLOAT)
	return false;
    }
  else if (mode == DFmode)
    {
      if (!(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
	return false;
    }
  else
    {
      return false;
    }

  return true;
}

rtx
riscv_pair_fusion::destructure_pair (rtx regs[2] __attribute__((unused)),
      rtx pattern __attribute__((unused)),
      bool load_p __attribute__((unused)))
{
    return NULL_RTX;
}

rtx
riscv_pair_fusion::gen_promote_writeback_pair (
  rtx wb_effect __attribute__((unused)),
  rtx pair_mem __attribute__((unused)), rtx regs[2] __attribute__((unused)),
	bool load_p __attribute__((unused)))
{
  return NULL_RTX;
}

namespace {

const pass_data pass_data_ldst_bonding =
{
  RTL_PASS, /* type.  */
  "ldst_bonding", /* name.  */
  OPTGROUP_NONE, /* optinfo_flags.  */
  TV_NONE, /* tv_id.  */
  0, /* properties_required.  */
  0, /* properties_provided.  */
  0, /* properties_destroyed.  */
  0, /* todo_flags_start.  */
  TODO_df_finish, /* todo_flags_finish.  */
};

class pass_ldst_bonding : public rtl_opt_pass
{
public:
  pass_ldst_bonding (gcc::context *ctx)
    : rtl_opt_pass (pass_data_ldst_bonding, ctx)
    {}

  opt_pass *clone () override { return new pass_ldst_bonding (m_ctxt); }

  bool gate (function *) final override
    {
      if (!optimize || optimize_debug)
	return false;

      if (!reload_completed)
	return false;

      return TARGET_MIPS && TARGET_LATE_LOAD_STORE_BONDING;
    }

  unsigned execute (function *) final override
    {
      riscv_pair_fusion pass;
      pass.run ();
      return 0;
    }
};

} // anon namespace

rtl_opt_pass *
make_pass_ldst_bonding (gcc::context *ctx)
{
  return new pass_ldst_bonding (ctx);
}
