#define IN_TARGET_CODE 1

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "memmodel.h"
#include "backend.h"
#include "target.h"
#include "rtl.h"
#include "tree.h"
#include "cfghooks.h"
#include "df.h"
#include "tm_p.h"
#include "stringpool.h"
#include "attribs.h"
#include "optabs.h"
#include "regs.h"
#include "emit-rtl.h"
#include "recog.h"
#include "diagnostic.h"
#include "fold-const.h"
#include "varasm.h"
#include "stor-layout.h"
#include "calls.h"
#include "output.h"
#include "insn-attr.h"
#include "flags.h"
#include "explow.h"
#include "expr.h"
#include "langhooks.h"
#include "tm-constrs.h"
#include "cfgrtl.h"
#include "tree-pass.h"
#include "context.h"
#include "builtins.h"
#include "rtl-iter.h"
#include "alias.h"
#include "opts.h"

/* This file should be included last.  */
#include "target-def.h"

/* Implement REGNO_REG_CLASS.  */
const enum reg_class arc64_regno_to_regclass[FIRST_PSEUDO_REGISTER] =
  {
   AC16_REGS, AC16_REGS, AC16_REGS, AC16_REGS,
   HI_REGS, HI_REGS, HI_REGS, HI_REGS,
   HI_REGS, HI_REGS, HI_REGS, HI_REGS,
   AC16_REGS, AC16_REGS, AC16_REGS, AC16_REGS,
   HI_REGS, HI_REGS, HI_REGS, HI_REGS,
   HI_REGS, HI_REGS, HI_REGS, HI_REGS,
   HI_REGS, HI_REGS, HI_REGS, HI_REGS,
   NO_REGS, NO_REGS, HI_REGS, NO_REGS,

   NO_REGS, NO_REGS, NO_REGS, NO_REGS,
   NO_REGS, NO_REGS, NO_REGS, NO_REGS,
   NO_REGS, NO_REGS, NO_REGS, NO_REGS,
   NO_REGS, NO_REGS, NO_REGS, NO_REGS,
   NO_REGS, NO_REGS, NO_REGS, NO_REGS,
   NO_REGS, NO_REGS, NO_REGS, NO_REGS,
   NO_REGS, NO_REGS, NO_REGS, NO_REGS,
   NO_REGS, NO_REGS, NO_REGS, NO_REGS,

   NO_REGS, NO_REGS, NO_REGS,
  };

/* Return 1 if the register is used by the epilogue.  We need to say the
   return register is used, but only after epilogue generation is complete.
   Note that in the case of sibcalls, the values "used by the epilogue" are
   considered live at the start of the called function.  */

int
arc64_epilogue_uses (int regno)
{
  if (epilogue_completed)
    if (regno == BLINK_REGNUM)
      return 1;

  return 0;
}

/* Implement INITIAL_ELIMINATION_OFFSET.  FROM is either the frame pointer
   or argument pointer.  TO is either the stack pointer or hard frame
   pointer.  */

HOST_WIDE_INT
arc64_initial_elimination_offset (unsigned from, unsigned to)
{
  return 0;
}

void arc64_init_expanders (void)
{
  /* FIXME! Not sure if I need it.  */
}

/* Given a comparison code (EQ, NE, etc.) and the first operand of a
   COMPARE, return the mode to be used for the comparison.  */

machine_mode
arc64_select_cc_mode (RTX_CODE op, rtx x, rtx y)
{
  return CC_Cmode;
}

/* Implement RETURN_ADDR_RTX.  We do not support moving back to a
   previous frame.  */

rtx
arc64_return_addr (int count , rtx frame ATTRIBUTE_UNUSED)
{
  if (count != 0)
    return const0_rtx;
  return get_hard_reg_initial_val (Pmode, BLINK_REGNUM);
}

/* Implement REGMODE_NATURAL_SIZE.  */

HOST_WIDE_INT
arc64_regmode_natural_size (machine_mode mode)
{
  return UNITS_PER_WORD; /*FIXME! do I need it? */
}

/* Given FROM and TO register numbers, say whether this elimination is allowed.
   Frame pointer elimination is automatically handled.

   All eliminations are permissible. If we need a frame
   pointer, we must eliminate ARG_POINTER_REGNUM into
   FRAME_POINTER_REGNUM and not into STACK_POINTER_REGNUM.  */

static bool
arc64_can_eliminate (const int from ATTRIBUTE_UNUSED, const int to)
{
  return ((to == HARD_FRAME_POINTER_REGNUM) || (to == STACK_POINTER_REGNUM));
}


/* Return TRUE if X is a legitimate address for accessing memory in
   mode MODE.  */

static bool
arc_legitimate_address_p (machine_mode mode, rtx x, bool strict)
{
  return true;
}

/* Implement TARGET_LEGITIMATE_CONSTANT_P hook.  Return true for constants
   that should be rematerialized rather than spilled.  */

static bool
arc64_legitimate_constant_p (machine_mode mode, rtx x)
{
  if (CONST_INT_P (x))
    return true;
  return false;
}

/* Target hooks.  */

#undef TARGET_ASM_ALIGNED_DI_OP
#define TARGET_ASM_ALIGNED_DI_OP "\t.xword\t"

#undef TARGET_ASM_ALIGNED_HI_OP
#define TARGET_ASM_ALIGNED_HI_OP "\t.hword\t"

#undef TARGET_ASM_ALIGNED_SI_OP
#define TARGET_ASM_ALIGNED_SI_OP "\t.word\t"

#undef  TARGET_ASM_CAN_OUTPUT_MI_THUNK
#define TARGET_ASM_CAN_OUTPUT_MI_THUNK \
  hook_bool_const_tree_hwi_hwi_const_tree_true

#undef TARGET_CAN_ELIMINATE
#define TARGET_CAN_ELIMINATE arc64_can_eliminate

#undef TARGET_LEGITIMATE_ADDRESS_P
#define TARGET_LEGITIMATE_ADDRESS_P arc64_legitimate_address_p

#undef TARGET_LEGITIMATE_CONSTANT_P
#define TARGET_LEGITIMATE_CONSTANT_P arc64_legitimate_constant_p

struct gcc_target targetm = TARGET_INITIALIZER;

#include "gt-arc64.h"
