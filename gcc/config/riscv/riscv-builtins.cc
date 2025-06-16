// 20240527 3.36pm

/* Subroutines used for expanding RISC-V builtins.
   Copyright (C) 2011-2024 Free Software Foundation, Inc.
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

struct riscv_builtin_description_apex {
  /* The code of the main .md file instruction.  See riscv_builtin_type
     for more information.  */
  enum insn_code icode;

  /* The name of the built-in function.  */
  const char *name;

  /* The name of the built-in instruction.  */
  const char *insn_name;

  /* Specifies how the function should be expanded.  */
  enum riscv_builtin_type builtin_type;

  unsigned int insn_formats;
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
#define RISCV_ATYPE_VOID_PTR ptr_type_node
#define RISCV_ATYPE_INT_PTR integer_ptr_type_node

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

static struct riscv_builtin_description riscv_builtins[] = {
  #include "riscv-cmo.def"
  #include "riscv-scalar-crypto.def"
  #include "corev.def"

  DIRECT_BUILTIN (frflags, RISCV_USI_FTYPE, hard_float),
  DIRECT_NO_TARGET_BUILTIN (fsflags, RISCV_VOID_FTYPE_USI, hard_float),
  RISCV_BUILTIN (pause, "pause", RISCV_BUILTIN_DIRECT_NO_TARGET, RISCV_VOID_FTYPE, hint_pause),
};

static const int riscv_apex_limit = 2;
static struct riscv_builtin_description_apex riscv_apex_builtins[riscv_apex_limit];

/* Index I is the function declaration for riscv_builtins[I], or null if the
   function isn't defined on this target.  */
static GTY(()) tree riscv_builtin_decls[ARRAY_SIZE (riscv_builtins)];

static GTY(()) tree riscv_builtin_decls_apex[riscv_apex_limit];

/* Get the index I of the function declaration for riscv_builtin_decls[I]
   using the instruction code or return null if not defined for the target.  */
static GTY(()) int riscv_builtin_decl_index[NUM_INSN_CODES];

#define GET_BUILTIN_DECL(CODE) \
  riscv_builtin_decls[riscv_builtin_decl_index[(CODE)]]

tree riscv_float16_type_node = NULL_TREE;

const char*
arcv_get_apex_insn_name (unsigned int subcode)
{
  return riscv_apex_builtins[subcode].insn_name;
}

/* Return the function type associated with function prototype TYPE.  */

static tree
riscv_build_function_type (enum riscv_function_type type)
{
//  warning(0, "LUIS: riscv_build_function_type");
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
}

/* Implement TARGET_INIT_BUILTINS.  */

void
riscv_init_builtins (void)
{
  warning (0, "luis: riscv_init_builtins");
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

bool
arcv_format_supports_p (unsigned int subcode, unsigned int insn_format)
{
  const struct riscv_builtin_description_apex *d = &riscv_apex_builtins[subcode];
  if (d->insn_formats & insn_format)
    return true;
  else
    return false;
}


static bool
arcv_get_return_type (tree fndecl)
{
  tree fntype = TREE_TYPE (fndecl);
  tree return_type = TREE_TYPE (fntype);
  return return_type == void_type_node;
}

/* Counts the number of operands for an APEX built-in function.
  This function analyzes the given function declaration and determines
  the number of operands, including the return type as the first operand.
  It iterates through the argument types of the function and increments
  the operand count for each argument. If the number of operands exceeds
  three, it reports an error.  */
static int
arcv_get_operand_count (tree fndecl)
{
	/* Get the function type from the function declaration
	   and the list of argument types for the function.  */
	tree fntype = TREE_TYPE (fndecl);
	tree operands = TYPE_ARG_TYPES (fntype);

	/* Get the return type of the function.  */
	tree return_type = TREE_TYPE (fntype);

  /* Count as 0 if return type is void.  */
  int num_operands = return_type == void_type_node ? 0 : 1;

	/* Iterate through the argument types.  */
	for (tree t = operands; t && TREE_CODE (TREE_VALUE (t)) != VOID_TYPE;
		 t = TREE_CHAIN (t))
	{
		/* Increment the operand count for each argument.  */
		num_operands++;
		/* If more than 3 operands, report an error.  */
		if (num_operands > 3)
		{
			error_at (DECL_SOURCE_LOCATION (fndecl),
				"too many operands for APEX built-in function %qE",
				fndecl);
			/* FIXME: terminate program.  */
		}
	}

	/* Return the total number of operands (including return type). */
	return num_operands;
}

struct format_rule {
    unsigned flag;
    unsigned max_opcode;
    unsigned num_operands;
};

const struct format_rule rules[] = {
    { RISCV_APEX_XD, 0xFF, 3 },
    { RISCV_APEX_XD_NO_TARGET, 0xFF, 2 },
    { RISCV_APEX_XS, 0x3F, 3 },
    { RISCV_APEX_XS_NO_TARGET, 0x3F, 2 },
    { RISCV_APEX_XI, 0x1F, 2 },
    { RISCV_APEX_XI_NO_TARGET, 0x1F, 1 },
    { RISCV_APEX_XC, 0x1F, 3 },
};

/* This function checks whether the provided instruction format, opcode and
   number of operands conform to the rules defined for APEX instructions.  */

static void
arcv_validate_insn_format (unsigned int insn_format,
						   unsigned opcode, unsigned num_operands)
{
	/* If the instruction format is RISCV_APEX_NONE, report an error.  */
	if (insn_format == RISCV_APEX_NONE)
		error("APEX instruction not valid.\n");

	/* Iterate over each rule in the rules array.  */
	for (int i = 0; i < sizeof(rules)/sizeof(rules[0]); ++i)
	{
		/* If the instruction format matches the rule's flag.  */
		if (insn_format & rules[i].flag)
		{
			/* Check if the opcode exceeds the rule's maximum
			   allowed opcode.  */
			if (opcode > rules[i].max_opcode)
				error("APEX opcode must be in range 0x%X.\n",
					   rules[i].max_opcode);
			/* Check if the number of operands matches the rule's required
			   operand count.  */
			if (num_operands != rules[i].num_operands)
				error("Function must have exactly %d operands.\n",
					  rules[i].num_operands);
		}
	}
}

/* This function modifies the given instruction format bitmask (`insn_format`)
   by clearing all RISCV_APEX_ALL bits, then selectively setting specific
   APEX instruction format flags depending on the provided opcode and the
   number of operands.  The function is intended to ensure that the
   instruction format accurately reflects the requirements for the
   given opcode and operand count.  */

static unsigned int
arcv_adjust_insn_format (unsigned int insn_format, unsigned opcode,
						 unsigned num_operands, bool is_return_void)
{
	/* If any RISCV_APEX_ALL bits are set, adjust the format flags.  */
	if (insn_format & RISCV_APEX_ALL)
	{
		/* Clear RISCV_APEX_ALL bit from the format.  */
		insn_format &= ~RISCV_APEX_ALL;

    if (is_return_void)
    {
      if (num_operands == 1)
      {
	if (opcode <= APEX_INSN_FORMAT_XI)
	  insn_format |= RISCV_APEX_XI_NO_TARGET;
	return insn_format;
      } else
      {
	if (opcode <= APEX_INSN_FORMAT_XD)
	    insn_format |= RISCV_APEX_XD_NO_TARGET;
	if (opcode <= APEX_INSN_FORMAT_XS)
	    insn_format |= RISCV_APEX_XS_NO_TARGET;
      return insn_format;
      }
    }

		/* Select format flags based on the number of operands.  */
		switch (num_operands)
		{
			case 3:
				/* For 3 operands, set XD, XS, or XC if opcode is in range.  */
				if (opcode <= APEX_INSN_FORMAT_XD)
					insn_format |= RISCV_APEX_XD;
				if (opcode <= APEX_INSN_FORMAT_XS)
					insn_format |= RISCV_APEX_XS;
				if (opcode <= APEX_INSN_FORMAT_XC)
					insn_format |= RISCV_APEX_XC;
				break;
			case 2:
				/* For 2 operands, set XI if opcode is in range.  */
				if (opcode <= APEX_INSN_FORMAT_XI)
					insn_format |= RISCV_APEX_XI;
				break;
		}
	}
	/* Return the updated instruction format bitmask.  */
	return insn_format;
}

/* This function maps a provided instruction format bitmask to a specific
   instruction code (insn_code) used in the RISC-V backend. It checks the
   format flags and returns the appropriate code.  */

static enum insn_code
arcv_get_icode (unsigned insn_format)
{
	/* If the instruction format includes RISCV_APEX_XI,
	   return CODE_FOR_riscv_xi.  */
	if (insn_format & RISCV_APEX_XI)
		return CODE_FOR_riscv_xi;

	/* If the instruction format includes RISCV_APEX_XD, RISCV_APEX_XS
	   or RISCV_APEX_XC, return CODE_FOR_riscv_xscd.  */
	if (insn_format & (RISCV_APEX_XD | RISCV_APEX_XS | RISCV_APEX_XC))
		return CODE_FOR_riscv_xscd;

  if (insn_format & (RISCV_APEX_XD_NO_TARGET | RISCV_APEX_XS_NO_TARGET))
    return CODE_FOR_riscv_xsd_no_target;

  if (insn_format & RISCV_APEX_XI_NO_TARGET)
    return CODE_FOR_riscv_xi_no_target;

	/* Otherwise, return CODE_FOR_nothing.  */
	return CODE_FOR_nothing;
}

void
riscv_apex_init_builtin (tree fndecl)
{
  if (fndecl)
  {
    static int i = 0;
    
    const char *fn_name = apex.fn_name;
    const char *insn_name = apex.insn_name;
    unsigned int insn_formats = apex.insn_formats;
    int opcode = apex.opcode;
    enum insn_code icode;

    int num_operands = arcv_get_operand_count (fndecl);
    bool is_return_void = (arcv_get_return_type (fndecl));
    insn_formats = arcv_adjust_insn_format (insn_formats, opcode, num_operands, is_return_void);
    arcv_validate_insn_format (insn_formats, opcode, num_operands);
    arcv_print_insn_section (insn_name, opcode, insn_formats);
    icode = arcv_get_icode (insn_formats);

    /* Store APEX insn information.  */
//    riscv_apex_builtins[i] =  { icode, fn_name, insn_name, RISCV_BUILTIN_DIRECT, insn_formats };
    enum riscv_builtin_type builtin_type = is_return_void ? RISCV_BUILTIN_DIRECT_NO_TARGET : RISCV_BUILTIN_DIRECT;
    riscv_apex_builtins[i] =  { icode, fn_name, insn_name, builtin_type, insn_formats };

    /* Modify the prototype type as built-in.  */
    fndecl->function_decl.built_in_class = BUILT_IN_MD;

    /* Modify the prototype function code to match the index
       in "riscv_apex_builtins" with a mask for APEX only insns.  */
    fndecl->function_decl.function_code = (i << RISCV_BUILTIN_SHIFT) + RISCV_BUILTIN_APEX;

    i++;
  } else {
    error ("%s is not declared.", apex.fn_name);
  }
}

/* Implement TARGET_BUILTIN_DECL.  */

tree
riscv_builtin_decl (unsigned int code, bool initialize_p ATTRIBUTE_UNUSED)
{
  warning (0, "luis: riscv_builtin_decl");
  unsigned int subcode = code >> RISCV_BUILTIN_SHIFT;
  switch (code & RISCV_BUILTIN_CLASS)
    {
    case RISCV_BUILTIN_GENERAL:
      if (subcode >= ARRAY_SIZE (riscv_builtins))
	return error_mark_node;
      return riscv_builtin_decls[subcode];

    case RISCV_BUILTIN_VECTOR:
      return riscv_vector::builtin_decl (subcode, initialize_p);

    case RISCV_BUILTIN_APEX:
      return riscv_builtin_decls_apex[subcode];
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
riscv_expand_builtin_direct (enum insn_code icode, unsigned int subcode, rtx target, tree exp,
			     bool has_target_p)
{
  struct expand_operand ops[MAX_RECOG_OPERANDS];

  /* Map any target to operand 0.  */
  int opno = 0;
  if (has_target_p)
    create_output_operand (&ops[opno++], target, TYPE_MODE (TREE_TYPE (exp)));

  rtx const_rtx = GEN_INT (subcode);
  create_input_operand (&ops[opno++], const_rtx, SImode);

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
  switch (fcode & 0b11) //switch (fcode & RISCV_BUILTIN_CLASS)
    {
      case RISCV_BUILTIN_VECTOR:
	return riscv_vector::expand_builtin (subcode, exp, target);
      case RISCV_BUILTIN_GENERAL: {
	const struct riscv_builtin_description *d = &riscv_builtins[subcode];

	switch (d->builtin_type)
	  {
	  case RISCV_BUILTIN_DIRECT:
	    return riscv_expand_builtin_direct (d->icode, 0, target, exp, true);

	  case RISCV_BUILTIN_DIRECT_NO_TARGET:
	    return riscv_expand_builtin_direct (d->icode, 0, target, exp, false);
	  }
      }
      case RISCV_BUILTIN_APEX: {
  const struct riscv_builtin_description_apex *d = &riscv_apex_builtins[subcode];

	switch (d->builtin_type)
	  {
	  case RISCV_BUILTIN_DIRECT:
	    return riscv_expand_builtin_direct (d->icode, subcode, target, exp, true);

	  case RISCV_BUILTIN_DIRECT_NO_TARGET:
	    return riscv_expand_builtin_direct (d->icode, subcode, target, exp, false);
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
