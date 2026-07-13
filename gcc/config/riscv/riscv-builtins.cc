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
#include "function.h"
#include "emit-rtl.h"
#include "stringpool.h"
#include "expr.h"
#include "explow.h"
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
#define RISCV_FTYPE_NAME5(A, B, C, D, E, F)                                    \
  RISCV_##A##_FTYPE_##B##_##C##_##D##_##E##_##F
#define RISCV_FTYPE_NAME6(A, B, C, D, E, F, G)                                 \
  RISCV_##A##_FTYPE_##B##_##C##_##D##_##E##_##F##_##G
#define RISCV_FTYPE_NAME7(A, B, C, D, E, F, G, H)                              \
  RISCV_##A##_FTYPE_##B##_##C##_##D##_##E##_##F##_##G##_##H

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

/* CORE-V availability.  */
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

/* RVP AVAIL.  */
AVAIL (simd, TARGET_RVP)
AVAIL (simd32, TARGET_RVP && !TARGET_64BIT)
AVAIL (simd64, TARGET_RVP && TARGET_64BIT)

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

  #define DIRECT_BUILTIN_NO_PREFIX(INSN, NAME, FUNCTION_TYPE, AVAIL)             \
  {                                                                            \
    CODE_FOR_##INSN, "__builtin_riscv_" #NAME, RISCV_BUILTIN_DIRECT,           \
      FUNCTION_TYPE, riscv_builtin_avail_##AVAIL                               \
  }

/* Define __builtin_riscv_<INSN>, which is a RISCV_BUILTIN_DIRECT_NO_TARGET
   function mapped to instruction CODE_FOR_riscv_<INSN>,  FUNCTION_TYPE
   and AVAIL are as for RISCV_BUILTIN.  */
#define DIRECT_NO_TARGET_BUILTIN(INSN, FUNCTION_TYPE, AVAIL)		\
  RISCV_BUILTIN (INSN, #INSN, RISCV_BUILTIN_DIRECT_NO_TARGET,		\
		FUNCTION_TYPE, AVAIL)

#define DIRECT_NO_TARGET_BUILTIN_NO_PREFIX(INSN, NAME, FUNCTION_TYPE, AVAIL)			\
  { CODE_FOR_ ## INSN, "__builtin_riscv_" #NAME,			\
    RISCV_BUILTIN_DIRECT_NO_TARGET, FUNCTION_TYPE, riscv_builtin_avail_ ## AVAIL }

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

#define RISCV_ATYPE_IXLEN  riscv_int_xlen_node
#define RISCV_ATYPE_UIXLEN riscv_uint_xlen_node

/* P extension */
#define RISCV_ATYPE_V4QI build_vector_type (intQI_type_node, 4)
#define RISCV_ATYPE_UV4QI build_vector_type (unsigned_intQI_type_node, 4)
#define RISCV_ATYPE_V8QI build_vector_type (intQI_type_node, 8)
#define RISCV_ATYPE_UV8QI build_vector_type (unsigned_intQI_type_node, 8)
#define RISCV_ATYPE_V2HI build_vector_type (intHI_type_node, 2)
#define RISCV_ATYPE_UV2HI build_vector_type (unsigned_intHI_type_node, 2)
#define RISCV_ATYPE_V4HI build_vector_type (intHI_type_node, 4)
#define RISCV_ATYPE_UV4HI build_vector_type (unsigned_intHI_type_node, 4)
#define RISCV_ATYPE_V2SI build_vector_type (intSI_type_node, 2)
#define RISCV_ATYPE_UV2SI build_vector_type (unsigned_intSI_type_node, 2)
#define RISCV_ATYPE_V8HI build_vector_type (intHI_type_node, 8)
#define RISCV_ATYPE_UV8HI build_vector_type (unsigned_intHI_type_node, 8)

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
#define RISCV_FTYPE_ATYPES5(A, B, C, D, E, F) \
  RISCV_ATYPE_##A, RISCV_ATYPE_##B, RISCV_ATYPE_##C, RISCV_ATYPE_##D, \
  RISCV_ATYPE_##E, RISCV_ATYPE_##F
#define RISCV_FTYPE_ATYPES6(A, B, C, D, E, F, G) \
  RISCV_ATYPE_##A, RISCV_ATYPE_##B, RISCV_ATYPE_##C, RISCV_ATYPE_##D, \
  RISCV_ATYPE_##E, RISCV_ATYPE_##F, RISCV_ATYPE_##G
#define RISCV_FTYPE_ATYPES7(A, B, C, D, E, F, G, H) \
  RISCV_ATYPE_##A, RISCV_ATYPE_##B, RISCV_ATYPE_##C, RISCV_ATYPE_##D, \
  RISCV_ATYPE_##E, RISCV_ATYPE_##F, RISCV_ATYPE_##G, RISCV_ATYPE_##H

static const struct riscv_builtin_description riscv_builtins[] = {
  #include "riscv-cmo.def"
  #include "riscv-scalar-crypto.def"
  #include "corev.def"
  #include "andes.def"
  #include "arcv.def"
  #include "p-builtins.def"

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

  /* Suffix added to the instruction name when the format is resolved
      (e.g., XS, XI, or XC); set to "i" if resolved, otherwise "".  */
  const char *insn_suffix;
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

tree riscv_uint_xlen_node = NULL_TREE;
tree riscv_int_xlen_node = NULL_TREE;


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

  if (TARGET_64BIT)
    {
      riscv_int_xlen_node = intDI_type_node;
      riscv_uint_xlen_node = unsigned_intDI_type_node;
    }
  else
    {
      riscv_int_xlen_node = intSI_type_node;
      riscv_uint_xlen_node = unsigned_intSI_type_node;
    }
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
	    = simulate_builtin_function_decl (input_location, d->name, type,
					      (i << RISCV_BUILTIN_SHIFT)
						+ RISCV_BUILTIN_GENERAL,
					      NULL, NULL_TREE);
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

    case RISCV_BUILTIN_APEX:
      /* Trick GCC to think that the function is defined.
	 The actual fndecl used is created after this
	 validation from the GIMPLE representation in LTO.  */
      return integer_zero_node;
    }
  return error_mark_node;
}

/* Take argument ARGNO from EXP's argument list and convert it into
   an expand operand.  Store the operand in *OP.  */

static void

riscv_prepare_builtin_arg (struct expand_operand *op, tree exp, unsigned argno,
			   enum insn_code icode, bool has_target_p)
{
  enum machine_mode mode = insn_data[icode].operand[argno + has_target_p].mode;
  rtx arg = expand_normal (CALL_EXPR_ARG (exp, argno));
  rtx tmp_rtx = gen_reg_rtx (mode);

  if (!(*insn_data[icode].operand[argno + has_target_p].predicate) (arg, mode))
    {
	if (known_lt (GET_MODE_SIZE (mode), GET_MODE_SIZE (GET_MODE (arg))))
	{
	  tmp_rtx = simplify_gen_subreg (mode, arg, GET_MODE (arg), 0);
	  arg = tmp_rtx;
	}
      else if (VECTOR_MODE_P (mode)
	       && known_lt (GET_MODE_SIZE (mode), UNITS_PER_WORD))
	{
	  scalar_int_mode imode
	    = int_mode_for_size (GET_MODE_BITSIZE (mode), 0).require ();
	  rtx int_arg;
	  rtx tmp_int = gen_reg_rtx (imode);

	  if (GET_MODE (arg) == imode)
	    int_arg = arg;
	  else if (MEM_P (arg))
	    int_arg = adjust_address_nv (arg, imode, 0);
	  else
	    int_arg = simplify_gen_subreg (imode, arg, GET_MODE (arg), 0);

	  emit_move_insn (tmp_int, int_arg);
	  arg = simplify_gen_subreg (mode, tmp_int, imode, 0);
	}
      else if (VECTOR_MODE_P (mode) && CONST_INT_P (arg))
	{
	  /* Handle conversion from CONST_INT to CONST_VECTOR.  */
	  unsigned int nunits = GET_MODE_NUNITS (mode).to_constant ();
	  unsigned int i;
	  int shift = 0;
	  rtvec v = rtvec_alloc (nunits);
	  HOST_WIDE_INT val = INTVAL (arg);
	  enum machine_mode val_mode = GET_MODE_INNER (mode);
	  int shift_acc = GET_MODE_BITSIZE (val_mode).to_constant ();
	  unsigned HOST_WIDE_INT mask = GET_MODE_MASK (val_mode);
	  HOST_WIDE_INT tmp_val = val;

	  for (i = 0; i < nunits; i++)
	    {
	      tmp_val = (val >> shift) & mask;
	      RTVEC_ELT (v, i) = gen_int_mode (tmp_val, val_mode);
	      shift += shift_acc;
	    }

	  arg = copy_to_mode_reg (mode, gen_rtx_CONST_VECTOR (mode, v));
	}
      else
	{
	  convert_move (tmp_rtx, arg, false);
	  arg = tmp_rtx;
	}
    }

  create_input_operand (op, arg, mode);
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

/* Validate the immediate argument passed to an APEX intrinsic.

   This function checks if the argument to the intrinsic call is a constant
   integer and fits within the required immediate range depending on the
   format supported by the given SUBCODE.  Only instructions that do not
   support APEX_XD are validated here.

   - For APEX_XI and APEX_XC formats: the argument must be a
     signed 12-bit integer.
   - For APEX_XS format: the argument must be a signed 8-bit integer.

   Returns false and reports an error if the argument is invalid; true
   otherwise.  */

static bool
arcv_apex_immediate_argument_valid_p (unsigned int subcode, tree exp)
{
  if (!arcv_apex_format_supports_p (subcode, APEX_XD))
  {
    tree arg;
    /* Get the first (and only) argument passed to the intrinsic call.  */
    if (arcv_apex_format_supports_p (subcode, APEX_XI))
      arg = CALL_EXPR_ARG (exp, 0);
    else if (arcv_apex_format_supports_p (subcode, APEX_XC)
	     || arcv_apex_format_supports_p (subcode, APEX_XS))
      arg = CALL_EXPR_ARG (exp, 1);

    /* If the argument is NOT a constant integer.  */
    if (!TREE_CONSTANT (arg) || TREE_CODE (arg) != INTEGER_CST)
    {
      error ("argument to %qs must be a constant integer",
	     arcv_apex_builtins[subcode].name);
      return false;
    }

    /* If the current subcode supports the APEX_XI or APEX_XC format, then
       the operand must fit within a signed 12-bit immediate.  */
    if (arcv_apex_format_supports_p (subcode, APEX_XI)
	|| arcv_apex_format_supports_p (subcode, APEX_XC))
    {
      HOST_WIDE_INT val = tree_to_shwi (arg);
      /* Check if the value fits within a signed 12-bit immediate.  */
      if ((val < -2048 || val > 2047))
      {
	error ("argument value %d is outside the valid range [-2048, 2047]",
		val);
	return false;
      }
    }

    /* If the current subcode supports the APEX_XS format, then
      the operand must fit within a signed 8-bit immediate.  */
    if (arcv_apex_format_supports_p (subcode, APEX_XS))
    {
      HOST_WIDE_INT val = tree_to_shwi (arg);
      /* Check if the value fits within a signed 8-bit immediate.  */
      if ((val < -128 || val > 127))
      {
	error ("argument value %d is outside the valid range [-128, 127]",
		val);
	return false;
      }
    }
  }
  return true;
}

/* Expand a RISCV_BUILTIN_DIRECT or RISCV_BUILTIN_DIRECT_NO_TARGET function;
   HAS_TARGET_P says which.  EXP is the CALL_EXPR that calls the function
   and ICODE is the code of the associated .md pattern.  TARGET, if nonnull,
   suggests a good place to put the result.  */

static rtx
riscv_expand_builtin_direct (enum insn_code icode, rtx target, tree exp,
			     bool has_target_p, unsigned int subcode,
			     bool has_subcode_p)
{
  struct expand_operand ops[MAX_RECOG_OPERANDS];

  /* Map any target to operand 0.  */
  int opno = 0;
  enum machine_mode insn_return_mode = insn_data[icode].operand[opno].mode;
  enum machine_mode mode = TYPE_MODE (TREE_TYPE (exp));

  if (has_target_p)
    {
      if (VECTOR_MODE_P (insn_return_mode)
	  && known_lt (GET_MODE_SIZE (insn_return_mode), UNITS_PER_WORD))
	{
	  scalar_int_mode imode
	    = int_mode_for_size (GET_MODE_BITSIZE (insn_return_mode), 0).require ();

	  if (!(target && REG_P (target) && GET_MODE (target) == imode))
	    target = gen_reg_rtx (imode);

	  target = simplify_gen_subreg (insn_return_mode, target, imode, 0);
	  mode = insn_return_mode;
	}

      if ((!target || GET_MODE (target) != insn_return_mode
	   || !(*insn_data[icode].operand[opno].predicate) (target,
							    insn_return_mode)))
	{
	  mode = insn_return_mode;
	  target = gen_reg_rtx (mode);
	}

      create_output_operand (&ops[opno++], target, mode);
    }

  if (has_subcode_p)
  {
    /* Create an RTL constant for the APEX subcode.  */
    rtx const_rtx = GEN_INT (subcode);
    /* Add the subcode as an additional input operand to the RTL expression.  */
    create_input_operand (&ops[opno++], const_rtx, SImode);
    /* Validate the immediate argument passed to the APEX intrinsic.  */
    if (!arcv_apex_immediate_argument_valid_p (subcode, exp))
      return const0_rtx;
  }

  /* Map the arguments to the other operands.  */
  gcc_assert (opno + call_expr_nargs (exp)
	      == insn_data[icode].n_generator_args);
  for (int argno = 0; argno < call_expr_nargs (exp); argno++)
    riscv_prepare_builtin_arg (&ops[opno++], exp, argno, icode, has_target_p);

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
      case RISCV_BUILTIN_APEX: {
	const struct arcv_apex_builtin_description *d
		= &arcv_apex_builtins[subcode];

	switch (d->builtin_type)
	  {
	  case RISCV_BUILTIN_DIRECT:
	    return riscv_expand_builtin_direct (d->icode, target, exp, true,
						subcode, true);

	  case RISCV_BUILTIN_DIRECT_NO_TARGET:
	    return riscv_expand_builtin_direct (d->icode, target, exp, false,
						subcode, true);
	  }
	break;
      }
      case RISCV_BUILTIN_GENERAL: {
	const struct riscv_builtin_description *d = &riscv_builtins[subcode];

	switch (d->builtin_type)
	  {
	  case RISCV_BUILTIN_DIRECT:
	    return riscv_expand_builtin_direct (d->icode, target, exp, true,
						subcode, false);

	  case RISCV_BUILTIN_DIRECT_NO_TARGET:
	    return riscv_expand_builtin_direct (d->icode, target, exp, false,
						subcode, false);
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


/* Return the function name associated with a given subcode.   */

const char*
arcv_apex_get_fn_name (unsigned int subcode)
{
  return arcv_apex_builtins[subcode].name;
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

/* Return the instruction suffix for an APEX subcode operand.

   This suffix is used to mark instructions whose format was resolved
   (e.g., XS, XI, or XC) rather than explicitly specified via pragma.  */

const char*
arcv_apex_get_insn_suffix (rtx op)
{
  unsigned int subcode = UINTVAL (op);
  return arcv_apex_builtins[subcode].insn_suffix;
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

/* Check if an APEX builtin with the given characteristics already exists.
   Returns the index if found with matching parameters, -1 if not found,
   or -2 if found but with conflicting parameters.  */

static int
arcv_apex_lto_find_builtin (const char *fn_name, const char *insn_name,
			    unsigned int opcode, unsigned int insn_formats,
			    location_t loc)
{
  for (int i = 0; i < arcv_apex_builtin_index; i++)
  {
    const struct arcv_apex_builtin_description *d = &arcv_apex_builtins[i];

    /* Check if function name matches.  */
    if (strcmp (d->name, fn_name) == 0)
    {
      /* Validate all parameters match.  */
      bool mismatch = false;

      if (strcmp (d->insn_name, insn_name) != 0)
      {
	warning_at (loc, 0, "APEX builtin %qs already registered with different "
		    "instruction name: %qs vs %qs",
		    fn_name, d->insn_name, insn_name);
	mismatch = true;
      }

      if (d->opcode != opcode)
      {
	warning_at (loc, 0, "APEX builtin %qs already registered with different "
		    "opcode: 0x%x vs 0x%x",
		    fn_name, d->opcode, opcode);
	mismatch = true;
      }

      if (d->insn_formats != insn_formats)
      {
	warning_at (loc, 0, "APEX builtin %qs already registered with different "
		    "instruction formats: 0x%x vs 0x%x",
		    fn_name, d->insn_formats, insn_formats);
	mismatch = true;
      }

      /* Return special value for conflicting registration.  */
      if (mismatch)
	return -2;

      /* Found matching registration.  */
	return i;
    }
  }

  return -1; /* Not found.  */
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
  /* Extract the operand flags (DEST, SRC0, SRC1) from bits 5–7.
     These bits encode the operand signature used for format selection.  */
  unsigned int insn_operands = insn_format >> 5;

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

  /* Check for opcode duplication:
     Emit an error if a previously registered APEX instruction has both:
     - At least one matching insn format bit (among XD, XS, XI, XC).
     - The same opcode value.

     This prevents defining two intrinsics with overlapping formats
     that would conflict in opcode decoding.  */
  for (int i = 0; i < arcv_apex_builtin_index; i++)
  {
    if ((arcv_apex_builtins[i].insn_formats & 0xF) & insn_format
      && arcv_apex_builtins[i].opcode == opcode)
    {
      error ("pragma intrinsic: this specification defines an "
		"opcode that duplicates a previous one", fn_name, opcode);
      return;
    }
  }

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

/* Determine the appropriate GCC instruction code (insn_code)
   based on the given APEX instruction format flags.

   This function decodes the instruction operand pattern encoded
   in `insn_format` and returns the matching internal GCC insn_code
   that corresponds to the instruction variant used during RTL generation.

   The operand layout is extracted by right-shifting out APEX_DEST and
   APEX_SRC flags (bits 5–7).  The function matches the operand pattern
   against predefined instruction codes for different instruction formats
   such as XI, XS, XC, and XD.

   Returns the corresponding insn_code enum for the given operand pattern.  */

static enum insn_code
arcv_apex_get_icode (unsigned insn_format)
{
  unsigned int insn_operands = insn_format >> 5;
  bool is_volatile = insn_format & APEX_VOLATILE;

  switch (insn_operands)
  {
    /* Used by "XD" insn. format: `insn`  */
    case APEX_VOID_FTYPE:
      return CODE_FOR_riscv_arcv_apex_void_ftype_v;

    /* Used by "XI","XD" insn. format: `insn src0`  */
    case APEX_VOID_FTYPE_SRC0:
      return CODE_FOR_riscv_arcv_apex_void_ftype_src0_v;

    /* Used by "XS","XD" insn. format: `insn src0, src1`  */
    case APEX_VOID_FTYPE_SRC0_SRC1:
      return CODE_FOR_riscv_arcv_apex_void_ftype_src0_src1_v;

    /* Used by "XD" insn. format: `insn dest`  */
    case APEX_DEST_FTYPE:
     return is_volatile
      ? CODE_FOR_riscv_arcv_apex_dest_ftype_v
      : CODE_FOR_riscv_arcv_apex_dest_ftype;

    /* Used by "XI","XD" insn. format: `insn dest, src0`  */
    case APEX_DEST_FTYPE_SRC0:
      return is_volatile
      ? CODE_FOR_riscv_arcv_apex_dest_ftype_src0_v
      : CODE_FOR_riscv_arcv_apex_dest_ftype_src0;

    /* Used by "XS","XC","XD" insn. format: `insn dest, src0, imm/src1`  */
    case APEX_DEST_FTYPE_SRC0_SRC1:
      return is_volatile
      ? CODE_FOR_riscv_arcv_apex_dest_ftype_src0_src1_v
      : CODE_FOR_riscv_arcv_apex_dest_ftype_src0_src1;

    default:
      /* If none is selected, the default is "CODE_FOR_nothing".  */
      return CODE_FOR_nothing;
   }
}

/* Initialize a RISC-V APEX built-in function.

   This function is invoked for each user-defined APEX intrinsic declared via
   a pragma.  It processes the parased, resolves the appropriate instruction
   format, validates it and prints the corresponding .extInstruction section
   for the assembler.

   It then determines the internal instruction code (icode) and categorizes the
   built-in as either with or without a destination operand.  The function
   stores the resulting instruction metadata into the "arcv_apex_builtins"
   array, modifies the function declaration "fndecl" to be recognized as a
   built-in (BUILT_IN_MD), and encodes a custom function code for use
   during later compiler stages.

   Each call increments the global built-in index to allow defining multiple
   intrinsics in sequence.  */

void
arcv_apex_init_builtin (tree fndecl, const char *fn_name,
			const char *insn_name, unsigned int insn_formats,
			unsigned int opcode)
{
  /* Update operand flags based on the function declaration.  */
  insn_formats = arcv_apex_set_insn_operand_flags (insn_formats, fndecl);
  if (insn_formats == 0xFFFFFFFF)
    return;

  /* Resolve the instruction format:
     If the user did not specify an instruction format at pragma level,
     infer the concrete format based on opcode and operand flags.  Mark
     the insn. name with an "i" suffix for resolved XS/XI/XC formats;
     otherwise, leave it as is.  */
  const char *insn_suffix = "";
  if ((insn_formats & 0xF) == APEX_NONE)
  {
    insn_formats = arcv_apex_resolve_insn_format (insn_formats, opcode);
    insn_suffix = "i";
  }

  /* Validate the format is allowed for this instruction.  */
  arcv_apex_validate_insn_format (fn_name, insn_formats, opcode);

  /* Print .extInstruction section about APEX instruction.  */
  arcv_apex_print_insn_section (insn_name, insn_suffix, opcode, insn_formats);

  /* Determine the internal instruction code (icode).  */
  enum insn_code icode = arcv_apex_get_icode (insn_formats);

  /* Determine whether this builtin has a destination operand.  */
  enum riscv_builtin_type builtin_type
	= (insn_formats & APEX_DEST) ? RISCV_BUILTIN_DIRECT :
				       RISCV_BUILTIN_DIRECT_NO_TARGET;

  /* Store APEX insn information.  */
  arcv_apex_builtins[arcv_apex_builtin_index]
    = { icode, fn_name, insn_name, opcode,
	builtin_type, insn_formats, insn_suffix };

  /* Modify the prototype type as built-in.  */
  fndecl->function_decl.built_in_class = BUILT_IN_MD;

  /* Modify the prototype function code to match the index
     in "riscv_apex_builtins" with a mask for APEX only insns.  */
  fndecl->function_decl.function_code
	= (arcv_apex_builtin_index << RISCV_BUILTIN_SHIFT) + RISCV_BUILTIN_APEX;

  arcv_apex_builtin_index++;
}


void
arcv_apex_lto_register_builtin (const char *fn_name, const char *insn_name,
			      unsigned int opcode, unsigned int insn_formats,
			      bool wpa_p, tree fndecl)
{
  /* Get source location from function declaration.  */
  location_t loc = DECL_SOURCE_LOCATION (fndecl);

  /* Check if this APEX builtin is already registered.  */
  int existing_idx = arcv_apex_lto_find_builtin (fn_name, insn_name, opcode,
					      insn_formats, loc);

  if (existing_idx >= 0)
  {
    /* Assert that the function code is the same as the existing index.  */
    gcc_assert (fndecl->function_decl.function_code
	== (unsigned) ((existing_idx << RISCV_BUILTIN_SHIFT)
			+ RISCV_BUILTIN_APEX));
    return;
  }

  if (existing_idx == -2)
  {
    /* Conflicting registration - warnings already issued.  */
    error_at (loc, "APEX builtin %qs has conflicting definitions across "
	   "compilation units", fn_name);
    return;
  }

  /* Not registered yet - proceed with new registration.  */

  /* Check for array overflow before storing.  */
  gcc_assert (arcv_apex_builtin_index < arcv_apex_builtins_limit);

  /* Calculate instruction suffix for auto-resolved formats.  */
  bool suffix_p = (insn_formats & APEX_XD)
	&& (insn_formats & (APEX_XS | APEX_XI | APEX_XC));
  const char *insn_suffix = suffix_p ? "i" : "";

  /* Print .extInstruction section during WPA phase.  */
  if (wpa_p)
    arcv_apex_print_insn_section (insn_name, insn_suffix, opcode, insn_formats);

  /* Determine whether this builtin has a destination operand.  */
  enum riscv_builtin_type builtin_type
	= (insn_formats & APEX_DEST) ? RISCV_BUILTIN_DIRECT :
				       RISCV_BUILTIN_DIRECT_NO_TARGET;

  /* Store APEX builtin information.  */
  arcv_apex_builtins[arcv_apex_builtin_index] = {
    arcv_apex_get_icode (insn_formats), xasprintf ("%s", fn_name),
    xasprintf ("%s", insn_name), opcode, builtin_type, insn_formats,
    xasprintf ("%s", insn_suffix) /* TODO: Remove insn_suffix from struct.  */
  };

  /* Set function code for this builtin.  */
  fndecl->function_decl.function_code
    = (arcv_apex_builtin_index << RISCV_BUILTIN_SHIFT) + RISCV_BUILTIN_APEX;

  arcv_apex_builtin_index++;
}

/* Get the number of registered APEX builtins.  */

int
arcv_apex_get_builtin_count (void)
{
  return arcv_apex_builtin_index;
}

/* Get information about a specific APEX builtin by index.
   Returns the information about the builtin.  */

void
arcv_apex_get_builtin_info (int index, const char **fn_name,
			      const char **insn_name, unsigned int *opcode,
			      unsigned int *insn_formats)
{
  gcc_assert (index >= 0 && index < arcv_apex_builtins_limit);
  const struct arcv_apex_builtin_description *d = &arcv_apex_builtins[index];

  *fn_name = d->name;
  *insn_name = d->insn_name;
  *opcode = d->opcode;
  *insn_formats = d->insn_formats;
}
