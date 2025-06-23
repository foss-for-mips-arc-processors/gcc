/* Subroutines used for expanding RISC-V builtins.
   Copyright (C) 2011-2026 Free Software Foundation, Inc.
   Contributed by Andrew Waterman (andrew@sifive.com).

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
#include "tm.h"
#include "rtl.h"
#include "tree.h"
#include "gimple-expr.h"
#include "memmodel.h"
#include "expmed.h"
#include "profile-count.h"
#include "optabs.h"
#include "recog.h"
#include "diagnostic-core.h"
#include "stor-layout.h"
#include "stringpool.h"
#include "expr.h"
#include "langhooks.h"
#include "tm_p.h"
#include "backend.h"
#include "gimple.h"
#include "gimple-iterator.h"

/* Macros to create an enumeration identifier for a function prototype.  */
#define RISCV_FTYPE_NAME0(A) RISCV_##A##_FTYPE
#define RISCV_FTYPE_NAME1(A, B) RISCV_##A##_FTYPE_##B
#define RISCV_FTYPE_NAME2(A, B, C) RISCV_##A##_FTYPE_##B##_##C
#define RISCV_FTYPE_NAME3(A, B, C, D) RISCV_##A##_FTYPE_##B##_##C##_##D
#define RISCV_FTYPE_NAME4(A, B, C, D, E) \
  RISCV_##A##_FTYPE_##B##_##C##_##D##_##E

/* Classifies the prototype of a built-in function.  */
enum riscv_function_type {
#define DEF_RISCV_FTYPE(NARGS, LIST) RISCV_FTYPE_NAME##NARGS LIST,
#include "config/riscv/riscv-ftypes.def"
#undef DEF_RISCV_FTYPE
  RISCV_MAX_FTYPE_MAX
};

/* Specifies how a built-in function should be converted into rtl.  */
enum riscv_builtin_type {
  /* The function corresponds directly to an .md pattern.  */
  RISCV_BUILTIN_DIRECT,

  /* Likewise, but with return type VOID.  */
  RISCV_BUILTIN_DIRECT_NO_TARGET
};

/* Declare an availability predicate for built-in functions.  */
#define AVAIL(NAME, COND)		\
 static unsigned int			\
 riscv_builtin_avail_##NAME (void)	\
 {					\
   return (COND);			\
 }

/* This structure describes a single built-in function.  */
struct riscv_builtin_description {
  /* The code of the main .md file instruction.  See riscv_builtin_type
     for more information.  */
  enum insn_code icode;

  /* The name of the built-in function.  */
  const char *name;

  /* Specifies how the function should be expanded.  */
  enum riscv_builtin_type builtin_type;

  /* The function's prototype.  */
  enum riscv_function_type prototype;

  /* Whether the function is available.  */
  unsigned int (*avail) (void);
};

AVAIL (hard_float, TARGET_HARD_FLOAT || TARGET_ZFINX)
AVAIL (clean32, TARGET_ZICBOM && !TARGET_64BIT)
AVAIL (clean64, TARGET_ZICBOM && TARGET_64BIT)
AVAIL (flush32, TARGET_ZICBOM && !TARGET_64BIT)
AVAIL (flush64, TARGET_ZICBOM && TARGET_64BIT)
AVAIL (inval32, TARGET_ZICBOM && !TARGET_64BIT)
AVAIL (inval64, TARGET_ZICBOM && TARGET_64BIT)
AVAIL (zero32,  TARGET_ZICBOZ && !TARGET_64BIT)
AVAIL (zero64,  TARGET_ZICBOZ && TARGET_64BIT)
AVAIL (prefetchi32, TARGET_ZICBOP && !TARGET_64BIT)
AVAIL (prefetchi64, TARGET_ZICBOP && TARGET_64BIT)
AVAIL (crypto_zbkb, TARGET_ZBKB)
AVAIL (crypto_zbkb32, TARGET_ZBKB && !TARGET_64BIT)
AVAIL (crypto_zbkb64, TARGET_ZBKB && TARGET_64BIT)
AVAIL (crypto_zbkx32, TARGET_ZBKX && !TARGET_64BIT)
AVAIL (crypto_zbkx64, TARGET_ZBKX && TARGET_64BIT)
AVAIL (crypto_zknd32, TARGET_ZKND && !TARGET_64BIT)
AVAIL (crypto_zknd64, TARGET_ZKND && TARGET_64BIT)
AVAIL (crypto_zkne32, TARGET_ZKNE && !TARGET_64BIT)
AVAIL (crypto_zkne64, TARGET_ZKNE && TARGET_64BIT)
AVAIL (crypto_zkne_or_zknd, (TARGET_ZKNE || TARGET_ZKND) && TARGET_64BIT)
AVAIL (crypto_zknh, TARGET_ZKNH)
AVAIL (crypto_zknh32, TARGET_ZKNH && !TARGET_64BIT)
AVAIL (crypto_zknh64, TARGET_ZKNH && TARGET_64BIT)
AVAIL (crypto_zksh, TARGET_ZKSH)
AVAIL (crypto_zksed, TARGET_ZKSED)
AVAIL (clmul_zbkc_or_zbc, (TARGET_ZBKC || TARGET_ZBC))
AVAIL (clmul_zbkc32_or_zbc32, (TARGET_ZBKC || TARGET_ZBC) && !TARGET_64BIT)
AVAIL (clmul_zbkc64_or_zbc64, (TARGET_ZBKC || TARGET_ZBC) && TARGET_64BIT)
AVAIL (clmulr_zbc32, TARGET_ZBC && !TARGET_64BIT)
AVAIL (clmulr_zbc64, TARGET_ZBC && TARGET_64BIT)
AVAIL (zbb, TARGET_ZBB)
AVAIL (zbb64, TARGET_ZBB && TARGET_64BIT)
AVAIL (zbb64_or_zbkb64, (TARGET_ZBKB || TARGET_ZBB) && TARGET_64BIT)
AVAIL (zbb_or_zbkb, (TARGET_ZBKB || TARGET_ZBB))
AVAIL (hint_pause, (!0))

// CORE-V AVAIL
AVAIL (cvmac, TARGET_XCVMAC && !TARGET_64BIT)
AVAIL (cvalu, TARGET_XCVALU && !TARGET_64BIT)
AVAIL (cvelw, TARGET_XCVELW && !TARGET_64BIT)
AVAIL (cvsimd, TARGET_XCVSIMD && !TARGET_64BIT)

/* ANDES AVAIL.  */
AVAIL (andesperf32, !TARGET_64BIT && TARGET_XANDESPERF)
AVAIL (andesperf64, TARGET_64BIT && TARGET_XANDESPERF)
AVAIL (andesbfhcvt, TARGET_XANDESBFHCVT)

// ARC-V AVAIL
AVAIL (xarcvudsp, TARGET_XARCVUDSP && !TARGET_64BIT)
AVAIL (xarcvbitrev, TARGET_XARCVBITREV)
AVAIL (xarcvbitstream, TARGET_XARCVBITSTREAM)

/* Construct a riscv_builtin_description from the given arguments.

   INSN is the name of the associated instruction pattern, without the
   leading CODE_FOR_riscv_.

   NAME is the name of the function itself, without the leading
   "__builtin_riscv_".

   BUILTIN_TYPE and FUNCTION_TYPE are riscv_builtin_description fields.

   AVAIL is the name of the availability predicate, without the leading
   riscv_builtin_avail_.  */
#define RISCV_BUILTIN(INSN, NAME, BUILTIN_TYPE,	FUNCTION_TYPE, AVAIL)	\
  { CODE_FOR_riscv_ ## INSN, "__builtin_riscv_" NAME,			\
    BUILTIN_TYPE, FUNCTION_TYPE, riscv_builtin_avail_ ## AVAIL }

/* Construct a riscv_builtin_description from the given arguments like RISCV_BUILTIN.

   INSN is the name of the associated instruction pattern, without the
   leading CODE_FOR_.

   NAME is the name of the function itself, without the leading
   "__builtin_riscv_".

   BUILTIN_TYPE and FUNCTION_TYPE are riscv_builtin_description fields.

   AVAIL is the name of the availability predicate, without the leading
   riscv_builtin_avail_.  */
#define RISCV_BUILTIN_NO_PREFIX(INSN, NAME, BUILTIN_TYPE,	FUNCTION_TYPE, AVAIL)	\
  { CODE_FOR_ ## INSN, "__builtin_riscv_" NAME,			\
    BUILTIN_TYPE, FUNCTION_TYPE, riscv_builtin_avail_ ## AVAIL }

/* Define __builtin_riscv_<INSN>, which is a RISCV_BUILTIN_DIRECT function
   mapped to instruction CODE_FOR_riscv_<INSN>,  FUNCTION_TYPE and AVAIL
   are as for RISCV_BUILTIN.  */
#define DIRECT_BUILTIN(INSN, FUNCTION_TYPE, AVAIL)			\
  RISCV_BUILTIN (INSN, #INSN, RISCV_BUILTIN_DIRECT, FUNCTION_TYPE, AVAIL)

/* Define __builtin_riscv_<INSN>, which is a RISCV_BUILTIN_DIRECT_NO_TARGET
   function mapped to instruction CODE_FOR_riscv_<INSN>,  FUNCTION_TYPE
   and AVAIL are as for RISCV_BUILTIN.  */
#define DIRECT_NO_TARGET_BUILTIN(INSN, FUNCTION_TYPE, AVAIL)		\
  RISCV_BUILTIN (INSN, #INSN, RISCV_BUILTIN_DIRECT_NO_TARGET,		\
		FUNCTION_TYPE, AVAIL)

/* Argument types.  */
#define RISCV_ATYPE_VOID void_type_node
#define RISCV_ATYPE_UQI unsigned_intQI_type_node
#define RISCV_ATYPE_UHI unsigned_intHI_type_node
#define RISCV_ATYPE_USI unsigned_intSI_type_node
#define RISCV_ATYPE_UDI unsigned_intDI_type_node
#define RISCV_ATYPE_QI intQI_type_node
#define RISCV_ATYPE_HI intHI_type_node
#define RISCV_ATYPE_SI intSI_type_node
#define RISCV_ATYPE_DI intDI_type_node
#define RISCV_ATYPE_VOID_PTR ptr_type_node
#define RISCV_ATYPE_INT_PTR integer_ptr_type_node
#define RISCV_ATYPE_BF bfloat16_type_node
#define RISCV_ATYPE_SF float_type_node

/* RISCV_FTYPE_ATYPESN takes N RISCV_FTYPES-like type codes and lists
   their associated RISCV_ATYPEs.  */
#define RISCV_FTYPE_ATYPES0(A) \
  RISCV_ATYPE_##A
#define RISCV_FTYPE_ATYPES1(A, B) \
  RISCV_ATYPE_##A, RISCV_ATYPE_##B
#define RISCV_FTYPE_ATYPES2(A, B, C) \
  RISCV_ATYPE_##A, RISCV_ATYPE_##B, RISCV_ATYPE_##C
#define RISCV_FTYPE_ATYPES3(A, B, C, D) \
  RISCV_ATYPE_##A, RISCV_ATYPE_##B, RISCV_ATYPE_##C, RISCV_ATYPE_##D
#define RISCV_FTYPE_ATYPES4(A, B, C, D, E) \
  RISCV_ATYPE_##A, RISCV_ATYPE_##B, RISCV_ATYPE_##C, RISCV_ATYPE_##D, \
  RISCV_ATYPE_##E

static const struct riscv_builtin_description riscv_builtins[] = {
  #include "riscv-cmo.def"
  #include "riscv-scalar-crypto.def"
  #include "corev.def"
  #include "andes.def"
  #include "arcv.def"

  DIRECT_BUILTIN (frflags, RISCV_USI_FTYPE, hard_float),
  DIRECT_NO_TARGET_BUILTIN (fsflags, RISCV_VOID_FTYPE_USI, hard_float),
  RISCV_BUILTIN (pause, "pause", RISCV_BUILTIN_DIRECT_NO_TARGET, RISCV_VOID_FTYPE, hint_pause),
};

/* Index I is the function declaration for riscv_builtins[I], or null if the
   function isn't defined on this target.  */
static GTY(()) tree riscv_builtin_decls[ARRAY_SIZE (riscv_builtins)];

/* Get the index I of the function declaration for riscv_builtin_decls[I]
   using the instruction code or return null if not defined for the target.  */
static GTY(()) int riscv_builtin_decl_index[NUM_INSN_CODES];

#define GET_BUILTIN_DECL(CODE) \
  riscv_builtin_decls[riscv_builtin_decl_index[(CODE)]]

tree riscv_float16_type_node = NULL_TREE;
tree riscv_bfloat16_type_node = NULL_TREE;

struct arcv_apex_builtin_description {
  /* The code of the main .md file instruction.  See riscv_builtin_type
     for more information.  */
  enum insn_code icode;

  /* The name of the built-in function.  */
  const char *name;

  /* The name of the built-in instruction.  */
  const char *insn_name;

  /* The opcode of the built-in instruction.  */
  unsigned int opcode;

  /* Specifies how the function should be expanded.  */
  enum riscv_builtin_type builtin_type;

  /* Specifies the instruction format.  See "apex_insn_format" enum
    for more details.  */
  unsigned int insn_formats;
};

/* The XD-type has 8 function bits encoding up to 256 instructions.
   The XS-type has 6 function bits encoding up to 64 instructions.
   Both the XI-type and the XC-type have 5 function bits each encoding up
   to 32 instructions respectively.  Thus giving a total of 384 possible
   different instructions.  */
static const int arcv_apex_builtins_limit = 384;
static struct arcv_apex_builtin_description
arcv_apex_builtins[arcv_apex_builtins_limit];
static int arcv_apex_builtin_index = 0;

/* Return the function type associated with function prototype TYPE.  */

static tree
riscv_build_function_type (enum riscv_function_type type)
{
  static tree types[(int) RISCV_MAX_FTYPE_MAX];

  if (types[(int) type] == NULL_TREE)
    switch (type)
      {
#define DEF_RISCV_FTYPE(NUM, ARGS)					\
  case RISCV_FTYPE_NAME##NUM ARGS:					\
    types[(int) type]							\
      = build_function_type_list (RISCV_FTYPE_ATYPES##NUM ARGS,		\
				  NULL_TREE);				\
    break;
#include "config/riscv/riscv-ftypes.def"
#undef DEF_RISCV_FTYPE
      default:
	gcc_unreachable ();
      }

  return types[(int) type];
}

static void
riscv_init_builtin_types (void)
{
  /* Provide the _Float16 type and float16_type_node if needed.  */
  if (!float16_type_node)
    {
      riscv_float16_type_node = make_node (REAL_TYPE);
      TYPE_PRECISION (riscv_float16_type_node) = 16;
      SET_TYPE_MODE (riscv_float16_type_node, HFmode);
      layout_type (riscv_float16_type_node);
    }
  else
    riscv_float16_type_node = float16_type_node;

  if (!maybe_get_identifier ("_Float16"))
    lang_hooks.types.register_builtin_type (riscv_float16_type_node,
					    "_Float16");

  /* Provide the __bf16 type and bfloat16_type_node if needed.  */
  if (!bfloat16_type_node)
    {
      riscv_bfloat16_type_node = make_node (REAL_TYPE);
      TYPE_PRECISION (riscv_bfloat16_type_node) = 16;
      SET_TYPE_MODE (riscv_bfloat16_type_node, BFmode);
      layout_type (riscv_bfloat16_type_node);
    }
  else
    riscv_bfloat16_type_node = bfloat16_type_node;

  if (!maybe_get_identifier ("__bf16"))
    lang_hooks.types.register_builtin_type (riscv_bfloat16_type_node,
					    "__bf16");
}

/* Implement TARGET_INIT_BUILTINS.  */

void
riscv_init_builtins (void)
{
  riscv_init_builtin_types ();
  riscv_vector::init_builtins ();

  for (size_t i = 0; i < ARRAY_SIZE (riscv_builtins); i++)
    {
      const struct riscv_builtin_description *d = &riscv_builtins[i];
      if (d->avail ())
	{
	  tree type = riscv_build_function_type (d->prototype);
	  riscv_builtin_decls[i]
	    = add_builtin_function (d->name, type,
				    (i << RISCV_BUILTIN_SHIFT)
				      + RISCV_BUILTIN_GENERAL,
				    BUILT_IN_MD, NULL, NULL);
	  riscv_builtin_decl_index[d->icode] = i;
	}
    }
}

/* Implement TARGET_BUILTIN_DECL.  */

tree
riscv_builtin_decl (unsigned int code, bool initialize_p ATTRIBUTE_UNUSED)
{
  unsigned int subcode = code >> RISCV_BUILTIN_SHIFT;
  switch (code & RISCV_BUILTIN_CLASS)
    {
    case RISCV_BUILTIN_GENERAL:
      if (subcode >= ARRAY_SIZE (riscv_builtins))
	return error_mark_node;
      return riscv_builtin_decls[subcode];

    case RISCV_BUILTIN_VECTOR:
      return riscv_vector::builtin_decl (subcode, initialize_p);
    }
  return error_mark_node;
}

/* Take argument ARGNO from EXP's argument list and convert it into
   an expand operand.  Store the operand in *OP.  */

static void
riscv_prepare_builtin_arg (struct expand_operand *op, tree exp, unsigned argno)
{
  tree arg = CALL_EXPR_ARG (exp, argno);
  create_input_operand (op, expand_normal (arg), TYPE_MODE (TREE_TYPE (arg)));
}

/* Expand instruction ICODE as part of a built-in function sequence.
   Use the first NOPS elements of OPS as the instruction's operands.
   HAS_TARGET_P is true if operand 0 is a target; it is false if the
   instruction has no target.

   Return the target rtx if HAS_TARGET_P, otherwise return const0_rtx.  */

static rtx
riscv_expand_builtin_insn (enum insn_code icode, unsigned int n_ops,
			   struct expand_operand *ops, bool has_target_p)
{
  if (!maybe_expand_insn (icode, n_ops, ops))
    {
      error ("invalid argument to built-in function");
      return has_target_p ? gen_reg_rtx (ops[0].mode) : const0_rtx;
    }

  return has_target_p ? ops[0].value : const0_rtx;
}

/* Expand a RISCV_BUILTIN_DIRECT or RISCV_BUILTIN_DIRECT_NO_TARGET function;
   HAS_TARGET_P says which.  EXP is the CALL_EXPR that calls the function
   and ICODE is the code of the associated .md pattern.  TARGET, if nonnull,
   suggests a good place to put the result.  */

static rtx
riscv_expand_builtin_direct (enum insn_code icode, rtx target, tree exp,
			     bool has_target_p)
{
  struct expand_operand ops[MAX_RECOG_OPERANDS];

  /* Map any target to operand 0.  */
  int opno = 0;
  if (has_target_p)
    create_output_operand (&ops[opno++], target, TYPE_MODE (TREE_TYPE (exp)));

  /* Map the arguments to the other operands.  */
  gcc_assert (opno + call_expr_nargs (exp)
	      == insn_data[icode].n_generator_args);
  for (int argno = 0; argno < call_expr_nargs (exp); argno++)
    riscv_prepare_builtin_arg (&ops[opno++], exp, argno);

  return riscv_expand_builtin_insn (icode, opno, ops, has_target_p);
}

/* Implement TARGET_GIMPLE_FOLD_BUILTIN.  */

bool
riscv_gimple_fold_builtin (gimple_stmt_iterator *gsi)
{
  gcall *stmt = as_a<gcall *> (gsi_stmt (*gsi));
  tree fndecl = gimple_call_fndecl (stmt);
  unsigned int code = DECL_MD_FUNCTION_CODE (fndecl);
  unsigned int subcode = code >> RISCV_BUILTIN_SHIFT;
  gimple *new_stmt = NULL;
  switch (code & RISCV_BUILTIN_CLASS)
    {
    case RISCV_BUILTIN_GENERAL:
      new_stmt = NULL;
      break;

    case RISCV_BUILTIN_VECTOR:
      new_stmt = riscv_vector::gimple_fold_builtin (subcode, gsi, stmt);
      break;
    }

  if (!new_stmt)
    return false;

  gsi_replace (gsi, new_stmt, false);
  return true;
}

/* Implement TARGET_EXPAND_BUILTIN.  */

rtx
riscv_expand_builtin (tree exp, rtx target, rtx subtarget ATTRIBUTE_UNUSED,
		      machine_mode mode ATTRIBUTE_UNUSED,
		      int ignore ATTRIBUTE_UNUSED)
{
  tree fndecl = TREE_OPERAND (CALL_EXPR_FN (exp), 0);
  unsigned int fcode = DECL_MD_FUNCTION_CODE (fndecl);
  unsigned int subcode = fcode >> RISCV_BUILTIN_SHIFT;
  switch (fcode & RISCV_BUILTIN_CLASS)
    {
      case RISCV_BUILTIN_VECTOR:
	return riscv_vector::expand_builtin (subcode, exp, target);
      case RISCV_BUILTIN_GENERAL: {
	const struct riscv_builtin_description *d = &riscv_builtins[subcode];

	switch (d->builtin_type)
	  {
	  case RISCV_BUILTIN_DIRECT:
	    return riscv_expand_builtin_direct (d->icode, target, exp, true);

	  case RISCV_BUILTIN_DIRECT_NO_TARGET:
	    return riscv_expand_builtin_direct (d->icode, target, exp, false);
	  }
      }
    }

  gcc_unreachable ();
}

/* Implement TARGET_ATOMIC_ASSIGN_EXPAND_FENV.  */

void
riscv_atomic_assign_expand_fenv (tree *hold, tree *clear, tree *update)
{
  if (!(TARGET_HARD_FLOAT || TARGET_ZFINX))
    return;

  tree frflags = GET_BUILTIN_DECL (CODE_FOR_riscv_frflags);
  tree fsflags = GET_BUILTIN_DECL (CODE_FOR_riscv_fsflags);
  tree old_flags = create_tmp_var_raw (RISCV_ATYPE_USI);

  *hold = build4 (TARGET_EXPR, RISCV_ATYPE_USI, old_flags,
		  build_call_expr (frflags, 0), NULL_TREE, NULL_TREE);
  *clear = build_call_expr (fsflags, 1, old_flags);
  *update = NULL_TREE;
}

/* Return the APEX instruction name associated with a given subcode operand.

   The subcode is an unsigned integer extracted from `op` that indexes into
   the `arcv_apex_builtins` array, which holds metadata about APEX builtin
   instructions.

   This function retrieves the instruction name string corresponding to the
   specified subcode, allowing the backend code to reference the mnemonic
   of the builtin instruction during assembly emission.  */

const char*
arcv_apex_get_insn_name (rtx op)
{
  unsigned int subcode = UINTVAL (op);
  return arcv_apex_builtins[subcode].insn_name;
}

/* Checks if the APEX builtin instruction identified by the subcode
   supports the given instruction format.

   Returns true if the instruction format is included in the builtin's
   supported formats; otherwise, returns false.  */

bool
arcv_apex_format_supports_p (unsigned int subcode, unsigned int insn_format)
{
  const struct arcv_apex_builtin_description *d = &arcv_apex_builtins[subcode];
  return (d->insn_formats & insn_format);
}

/* Set APEX operand flags for a built-in function.
   This function inspects the function prototype in FNDECL and sets the
   appropriate operand flags in INSN_FORMAT:
     - APEX_DEST if the return type is not void.
     - APEX_SRC0 and/or APEX_SRC1 depending on the number of arguments.
   Emits an error if more than 2 arguments are present.  */

static unsigned int
arcv_apex_set_insn_operand_flags (unsigned int insn_format, tree fndecl)
{
  /* Set DEST flag if the function does not return void.  */
  tree return_type = TREE_TYPE (TREE_TYPE (fndecl));
  if (return_type != void_type_node)
    insn_format |= APEX_DEST;

  /* Count non‑void parameters, aborting if there are more than two.  */
  unsigned int nargs = 0;
  for (tree arg = TYPE_ARG_TYPES (TREE_TYPE (fndecl));
       arg && TREE_CODE (TREE_VALUE (arg)) != VOID_TYPE;
       arg = TREE_CHAIN (arg))
  {
    if (++nargs > 2)
    {
      warning (0, "pragma intrinsic: Associated function can have "
	"no more than 2 parameters");
      return 0xFFFFFFFF;
    }

    /* Only perform size checks on 32-bit architectures.  */
    if (POINTER_SIZE != 32)
      continue;

    /* We want to check the size of the value represented by the argument.
       - If it's a pointer, we check the size of the pointed-to type.
       - If it's a scalar or aggregate type, we check its own size.  */
    tree argtype = TREE_VALUE (arg);
    tree type_to_check = argtype;
    if (TREE_CODE (argtype) == POINTER_TYPE)
    {
      /* Skip size check if return type is void.  */
      if (return_type == void_type_node)
	continue;

      type_to_check = TREE_TYPE (argtype);
    }
    else
      type_to_check = argtype;

    /* If TYPE_SIZE_UNIT exists and represents a constant integer value,
       retrieve its size in bytes as a HOST_WIDE_INT.  */
    if (! (TYPE_SIZE_UNIT (type_to_check)
	&& tree_fits_uhwi_p (TYPE_SIZE_UNIT (type_to_check))))
      continue;

    HOST_WIDE_INT bytes = tree_to_uhwi (TYPE_SIZE_UNIT (type_to_check));

    /* If the type’s size is greater than 4 bytes, emit an error.
       This applies to both pointed-to types and scalar types
       larger than 4 bytes.  */
    if (bytes <= 4)
      continue;

    const char *fn_name = IDENTIFIER_POINTER (DECL_NAME (fndecl));
    if (TREE_CODE (argtype) == POINTER_TYPE)
    {
      /* Specific error for pointer parameters when return type is not void.  */
      error ("pragma intrinsic: APEX function %qs must return "
		"void or a scalar type that does not exceed 4 bytes",
		fn_name);
    }
    else
    {
      /* General error for large or non-scalar parameter types.  */
      error ("pragma intrinsic: APEX function %qs contains a parameter "
		"of a non-scalar type, or one that exceeds 4 bytes",
		fn_name);
    }
    return 0xFFFFFFFF;
  }

  /* Source‑operand flags.  */
  if (nargs >= 1)
    insn_format |= APEX_SRC0;
  if (nargs == 2)
    insn_format |= APEX_SRC1;

  return insn_format;
}

/* Infer APEX instruction format if none was explicitly specified.

   This function is only used when the user has not specified a concrete
   instruction format (i.e., INSN_FORMAT is APEX_NONE). It determines the
   actual format tag (APEX_XD, APEX_XS, APEX_XI, APEX_XC) based on
   the opcode and operand layout.

   The operand configuration is extracted by right-shifting out the
   APEX_DEST and APEX_SRC flags (bits 4–6).  The opcode is then used to
   select the most specific format that matches.

   Returns the updated instruction format with a resolved concrete type.  */

static unsigned int
arcv_apex_resolve_insn_format (unsigned int insn_format, unsigned int opcode)
{
  /* Return early if a instruction format was defined by the used.  */
  if ((insn_format & 0xF) != APEX_NONE)
    return insn_format;

  /* Extract the operand flags (DEST, SRC0, SRC1) from bits 4–6.
     These bits encode the operand signature used for format selection.  */
  unsigned int insn_operands = insn_format >> 4;

  /* Assign the most general format APEX_XD.  If opcode does not permit,
     it will report an error at "arcv_apex_validate_insn_format".  */
  insn_format |= APEX_XD; /* Any operands allowed.  */

  /* Assign APEX_XS format for two source operands patterns.  */
  if (opcode <= APEX_OP_MAX_XS
	&& (insn_operands == APEX_VOID_FTYPE_SRC0_SRC1
	|| insn_operands == APEX_DEST_FTYPE_SRC0_SRC1))
    insn_format |= APEX_XS;

  /* Assign APEX_XI format for one source operand patterns.  */
  if (opcode <= APEX_OP_MAX_XI
	&& (insn_operands == APEX_VOID_FTYPE_SRC0
	|| insn_operands == APEX_DEST_FTYPE_SRC0))
    insn_format |= APEX_XI;

  /* Assign APEX_XC format for one destination and two source operands.  */
  if (opcode <= APEX_OP_MAX_XC
	&& insn_operands == APEX_DEST_FTYPE_SRC0_SRC1)
    insn_format |= APEX_XC;

  return insn_format;
}

/* Represents a validation rule for an APEX instruction format.  */
struct format_rule {
  /* The instruction format bitmask.  */
  unsigned insn_format;

  /* The string name for diagnostics.  */
  const char *insn_format_str;

  /* The maximum allowed opcode value.  */
  unsigned max_opcode;

  /* Number of required scalar arguments.  */
  unsigned int required_args;

  /* Whether a destination is required.  */
  bool required_dest;
};

/* insn_format, string, max_opcode, has_return, max_args.  */
const struct format_rule rules[] = {
  { APEX_XD, "XD", 0xFF, /* Not taking into account.  */ 0, false },
  { APEX_XS, "XS", 0x3F, 2, false },
  { APEX_XI, "XI", 0x1F, 1, false },
  { APEX_XC, "XC", 0x1F, 2, true },
};

/* Validate that the given instruction format, opcode and operand count
   comply with the predefined APEX instruction format rules.

   This function checks the instruction format against a set of rules that
   define valid combinations of instruction formats, maximum allowed opcode
   values, and required number of operands.  It reports errors if:
   - The instruction format is invalid or not supported.
   - The opcode exceeds the maximum allowed for the given format.
   - The operand count does not match the expected count for the format.
   - Certain format-specific constraints are violated (e.g., return type
     requirements or invalid argument usage).  */

static void
arcv_apex_validate_insn_format (const char* fn_name, unsigned int insn_format,
				unsigned opcode)
{
  /* If the instruction format is APEX_NONE, report an error.  */
  gcc_assert (insn_format != APEX_NONE);

  bool has_dest = (insn_format & APEX_DEST) >> 5;
  unsigned int num_arguments = ((insn_format & APEX_SRC0) >> 6)
			+ ((insn_format & APEX_SRC1) >> 7);

  /* Iterate over each rule in the rules array.  */
  for (size_t i = 0; i < sizeof (rules)/sizeof (rules[0]); ++i)
  {
    /* If the instruction format does not matche the
       rule's insn_format, skip to the next rule.  */
    if (!(insn_format & rules[i].insn_format))
      continue;

    const struct format_rule *rule = &rules[i];

    /* Check if the opcode exceeds the rule's maximum
	 allowed opcode.  */
    if (opcode > rule->max_opcode)
    {
      error ("pragma intrinsic: APEX opcode value %qd must be an integer "
		"constant in the range 0 to 0x%x, inclusive",
		opcode, rule->max_opcode);
      return;
    }

    /* Check if the number of operands matches the rule's required
	 operand count.  */
    if (rule->insn_format != APEX_XD
	&& num_arguments != rule->required_args)
    {
      error ("pragma intrinsic: APEX function %qs must have %d scalar "
		"parameter(s) for the %qs format class",
		fn_name, rule->required_args, rule->insn_format_str);
      return;
    }

    if (rule->insn_format == APEX_XI && num_arguments == 0)
    {
      error ("argument 1 is not valid in \"constant\" designation");
      return;
    }

    /* FIXME: Same behavior as CCAC, but shouldnt it we actually
	 validate both datatypes? */
    if (rule->insn_format == APEX_XC && has_dest != rule->required_dest)
    {
      error ("pragma intrinsic: APEX function %qs must return the same "
		"type as the first parameter for the %qs format class",
		fn_name, rule->insn_format_str);
      return;
    }
  }
}
