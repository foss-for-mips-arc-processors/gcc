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
   AC16_REGS,    AC16_REGS,    AC16_REGS,    AC16_REGS,
   GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
   GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
   AC16_REGS,    AC16_REGS,    AC16_REGS,    AC16_REGS,
   GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
   GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
   GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
   NO_REGS,      NO_REGS,      GENERAL_REGS, NO_REGS,

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


/* Prepare operands for move in MODE.  Return true iff the move has
   been emitted.  */

bool
arc64_prepare_move_operands (rtx op0, rtx op1, machine_mode mode)
{
  return false; /* FIXME: Place holder for move expand ops.  */
}

/* Split a mov with long immediate instruction into smaller, size
   friendly instructions.  */

bool
arc64_split_mov_const (rtx *operands)
{
  unsigned HOST_WIDE_INT ival;
  HOST_WIDE_INT shimm;
  machine_mode mode = GET_MODE (operands[0]);

  /* Manage a constant.  */
  gcc_assert (CONST_INT_P (operands[1]));
  ival = INTVAL (operands[1]) & 0xffffffff;

  if (SIGNED_INT12 (ival))
    return false;

  /* 1. Check if we can just rotate limm by 8 but using ROR8.  */
  if (TARGET_BARREL_SHIFTER && ((ival & ~0x3f000000) == 0))
    {
      shimm = (ival >> 24) & 0x3f;
      emit_insn (gen_rtx_SET (operands[0],
			      gen_rtx_ROTATERT (mode, GEN_INT (shimm),
						GEN_INT (8))));
      return true;
    }
  /* 2. Check if we can just shift by 8 to fit into the u6 of LSL8.  */
  if (TARGET_BARREL_SHIFTER && ((ival & ~0x3f00) == 0))
    {
      shimm = (ival >> 8) & 0x3f;
      emit_insn (gen_rtx_SET (operands[0],
			      gen_rtx_ASHIFT (mode, GEN_INT (shimm),
					      GEN_INT (8))));
      return true;
    }

  /* 3. Check if we can just shift by 16 to fit into the u6 of LSL16.  */
  if (TARGET_BARREL_SHIFTER && ((ival & ~0x3f0000) == 0))
    {
      shimm = (ival >> 16) & 0x3f;
      emit_insn (gen_rtx_SET (operands[0],
			      gen_rtx_ASHIFT (mode, GEN_INT (shimm),
					      GEN_INT (16))));
      return true;
    }

  /* 4. Check if we can do something like mov_s h,u8 / asl_s ra,h,#nb.  */
  if (((ival >> (__builtin_ffs (ival) - 1)) & 0xffffff00) == 0
      && TARGET_BARREL_SHIFTER)
    {
      HOST_WIDE_INT shift = __builtin_ffs (ival);
      shimm = (ival >> (shift - 1)) & 0xff;
      emit_insn (gen_rtx_SET (operands[0], GEN_INT (shimm)));
      emit_insn (gen_rtx_SET (operands[0],
			      gen_rtx_ASHIFT (mode, operands[0],
					      GEN_INT (shift - 1))));
      return true;
    }

  /* 5. Check if we can just rotate the limm, useful when no barrel
     shifter is present.  */
  if ((ival & ~0x8000001f) == 0)
    {
      shimm = (ival * 2 + 1) & 0x3f;
      emit_insn (gen_rtx_SET (operands[0],
			      gen_rtx_ROTATERT (mode, GEN_INT (shimm),
						const1_rtx)));
      return true;
    }

  /* 6. Check if we can do something with bmask.  */
  if (IS_POWEROF2_P (ival + 1))
    {
      emit_insn (gen_rtx_SET (operands[0], constm1_rtx));
      emit_insn (gen_rtx_SET (operands[0],
			      gen_rtx_AND (mode, operands[0],
					   GEN_INT (ival))));
      return true;
    }

  return false;
}

/* Helper to check Cax constraint.  */

bool
arc64_check_mov_const (HOST_WIDE_INT ival)
{
  ival = ival & 0xffffffff;

  if ((ival & ~0x8000001f) == 0)
    return true;

  if (IS_POWEROF2_P (ival + 1))
    return true;

  /* The next rules requires a barrel shifter.  */
  if (!TARGET_BARREL_SHIFTER)
    return false;

  if (((ival >> (__builtin_ffs (ival) - 1)) & 0xffffff00) == 0)
    return true;

  if ((ival & ~0x3f00) == 0)
    return true;

  if ((ival & ~0x3f0000) == 0)
    return true;

  if ((ival & ~0x3f000000) == 0)
    return true;

  return false;
}

/* This function is used by the call expanders of the machine description.
   RESULT is the register in which the result is returned.  It's NULL for
   "call" and "sibcall".
   MEM is the location of the function call.
   SIBCALL indicates whether this function call is normal call or sibling call.
   It will generate different pattern accordingly.  */

void
arc64_expand_call (rtx result, rtx mem, bool sibcall)
{
  rtx call, callee, tmp;
  machine_mode mode;

  gcc_assert (MEM_P (mem));
  callee = XEXP (mem, 0);
  mode = GET_MODE (callee);
  gcc_assert (mode == Pmode);

  /* Decide if we should generate indirect calls by loading the
     address of the callee into a register before performing the
     branch-and-link.  */
  if (arc64_is_long_call_p (callee) && !REG_P (callee))
    XEXP (mem, 0) = force_reg (mode, callee);

  call = gen_rtx_call (VOIDmode, mem, cont0_rtx);

  if (result != NULL_RTX)
    call = gen_rtx_SET (result, call);

  if (sibcall)
    tmp = ret_rtx;
  else
    tmp = gen_rtx_CLOBBER (VOIDmode, gen_rtx_REG (Pmode, BLINK_REGNUM));

  vec = gen_rtvec (2, call, tmp);
  call = gen_rtx_PARALLEL (VOIDmode, vec);

  emit_call_insn (call);
}

/* Return nonzero if this function is known to have a null epilogue.
   This allows the optimizer to omit jumps to jumps if no stack
   was created.  */

bool
arc64_can_use_return_insn_p (void)
{
  return (reload_completed); //FIXME!: && cfun->machine->frame.frame_size == 0);
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
