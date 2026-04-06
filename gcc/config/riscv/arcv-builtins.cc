/* ARCV (ARC RISC-V) builtin functions.
   Copyright (C) 2024-2025 Free Software Foundation, Inc.

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
#include "cgraph.h"
#include "lto-streamer.h"
#include "ipa-utils.h"
#include "data-streamer.h"

/* Specifies how a built-in function should be converted into rtl.  */
enum riscv_builtin_type {
  /* The function corresponds directly to an .md pattern.  */
  RISCV_BUILTIN_DIRECT,

  /* Likewise, but with return type VOID.  */
  RISCV_BUILTIN_DIRECT_NO_TARGET
};

/* This structure describes an APEX built-in function.  */
struct arcv_apex_builtin_description {
  /* The code of the main .md file instruction.  See riscv_builtin_type
     for more information.  */
  enum insn_code icode;

  /* The name of the built-in function.  */
  const char *name;

  /* The assembly mnemonic of the built-in instruction.  */
  const char *mnemonic;

  /* The opcode of the built-in instruction.  */
  unsigned int opcode;

  /* Specifies how the function should be expanded.  */
  enum riscv_builtin_type builtin_type;

  /* Specifies the instruction format.  See "apex_insn_format" enum
    for more details.  */
  unsigned int format_flags;
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

/* Return the assembly mnemonic for an APEX instruction.
   Appends "i" suffix if immediate_p is true and multiple formats exist.  */

const char*
arcv_apex_asm_mnemonic (rtx op, bool immediate_p)
{
  unsigned int subcode = UINTVAL (op);
  const char *base_mnemonic = arcv_apex_builtins[subcode].mnemonic;
  unsigned int format_flags = arcv_apex_builtins[subcode].format_flags;

  /* Add suffix only for immediate alternatives when XD coexists.  */
  if (immediate_p
      && (format_flags & APEX_XD)
      && (format_flags & (APEX_XS | APEX_XI | APEX_XC)))
    return xasprintf ("%si", base_mnemonic);

  return base_mnemonic;
}

/* Checks if the APEX builtin instruction identified by the subcode
   supports the given instruction format.  */

bool
arcv_apex_format_enabled_p (unsigned int subcode, unsigned int insn_format)
{
  const struct arcv_apex_builtin_description *d = &arcv_apex_builtins[subcode];
  return (d->format_flags & insn_format);
}

/* Infer APEX operand flags from a built-in function signature.
   Sets APEX_VOID if return type is void.
   Sets APEX_NO_SRC0/APEX_NO_SRC1 if parameters are absent.
   Returns true on success, false on error.  */

static bool
arcv_apex_infer_operand_flags (unsigned int *insn_format, tree fndecl)
{
  tree return_type = TREE_TYPE (TREE_TYPE (fndecl));
  if (return_type == void_type_node)
    *insn_format |= APEX_VOID;

  unsigned int nargs = 0;
  const char *fn_name = IDENTIFIER_POINTER (DECL_NAME (fndecl));
  for (tree arg = TYPE_ARG_TYPES (TREE_TYPE (fndecl));
       arg && TREE_CODE (TREE_VALUE (arg)) != VOID_TYPE;
       arg = TREE_CHAIN (arg))
  {
    if (++nargs > 2)
    {
      warning (0, "pragma intrinsic: Associated function can have no more "
		  "than 2 parameters");
      return false;
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

    /* If the type's size is greater than 4 bytes, emit an error.
       This applies to both pointed-to types and scalar types
       larger than 4 bytes.  */
    HOST_WIDE_INT bytes = tree_to_uhwi (TYPE_SIZE_UNIT (type_to_check));
    if (bytes <= 4)
      continue;

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
      return false;
  }

  if (nargs < 1)
    *insn_format |= APEX_NO_SRC0;
  if (nargs < 2)
    *insn_format |= APEX_NO_SRC1;

  return true;
}

/* Infer APEX instruction format when not explicitly specified.
   Determines the format (XD, XS, XI, XC) based on opcode and operand
   layout.  */

static unsigned int
arcv_apex_infer_format (unsigned int insn_format, unsigned int opcode)
{
  unsigned int insn_operands = insn_format >> 5;

  /* APEX_XD is always available (most general format).  */
  insn_format |= APEX_XD;

  /* Add APEX_XS if opcode fits and has two source operands.  */
  if (opcode <= APEX_OP_MAX_XS
      && (insn_operands == APEX_VOID_FTYPE_SRC0_SRC1
	  || insn_operands == APEX_DEST_FTYPE_SRC0_SRC1))
    insn_format |= APEX_XS;

  /* Add APEX_XI if opcode fits and has one source operand.  */
  if (opcode <= APEX_OP_MAX_XI
      && (insn_operands == APEX_VOID_FTYPE_SRC0
	  || insn_operands == APEX_DEST_FTYPE_SRC0))
    insn_format |= APEX_XI;

  /* Add APEX_XC if opcode fits and has dest + two sources.  */
  if (opcode <= APEX_OP_MAX_XC
      && insn_operands == APEX_DEST_FTYPE_SRC0_SRC1)
    insn_format |= APEX_XC;

  return insn_format;
}

/* Validate APEX instruction format, opcode, and operand count.
   Checks that the format, opcode, and operands comply with APEX rules.  */

static void
arcv_apex_validate_format (const char* fn_name, unsigned int insn_format,
			    unsigned int opcode)
{
  gcc_assert (insn_format != APEX_NONE);

  /* Check for duplicate opcode registration.  */
  for (int i = 0; i < arcv_apex_builtin_index; i++)
    {
      if ((arcv_apex_builtins[i].format_flags & 0xF) & insn_format
	  && arcv_apex_builtins[i].opcode == opcode)
	{
	  error ("pragma intrinsic: this specification defines an opcode "
      "that duplicates a previous one");
	  return;
	}
    }

  bool void_p = (insn_format & APEX_VOID) ? true : false;
  unsigned int num_args = ((insn_format & APEX_NO_SRC0) ? 0 : 1)
			+ ((insn_format & APEX_NO_SRC1) ? 0 : 1);

  /* Validate XD format: opcode <= 0xFF.  */
  if (insn_format & APEX_XD)
    {
      if (opcode > 0xFF)
	{
	  error ("pragma intrinsic: APEX opcode value %<%d%> must be an "
		 "integer constant in the range 0 to 0xff, inclusive", opcode);
	  return;
	}
    }

  /* Validate XS format: opcode <= 0x3F, requires 2 arguments.  */
  if (insn_format & APEX_XS)
    {
      if (opcode > 0x3F)
	{
	  error ("pragma intrinsic: APEX opcode value %<%d%> must be an "
		 "integer constant in the range 0 to 0x3f, inclusive", opcode);
	  return;
	}
      if (num_args != 2)
	{
	  error ("pragma intrinsic: APEX function %qs must have 2 scalar "
		 "parameter(s) for the 'XS' format class", fn_name);
	  return;
	}
    }

  /* Validate XI format: opcode <= 0x1F, requires 1 argument.  */
  if (insn_format & APEX_XI)
    {
      if (opcode > 0x1F)
	{
	  error ("pragma intrinsic: APEX opcode value %<%d%> must be an "
		 "integer constant in the range 0 to 0x1f, inclusive", opcode);
	  return;
	}
      if (num_args != 1)
	{
	  error ("pragma intrinsic: APEX function %qs must have 1 scalar "
		 "parameter(s) for the 'XI' format class", fn_name);
	  return;
	}
    }

  /* Validate XC format: opcode <= 0x1F, requires 2 arguments and return
     value.  */
  if (insn_format & APEX_XC)
    {
      if (opcode > 0x1F)
	{
	  error ("pragma intrinsic: APEX opcode value %<%d%> must be an "
		 "integer constant in the range 0 to 0x1f, inclusive", opcode);
	  return;
	}
      if (num_args != 2)
	{
	  error ("pragma intrinsic: APEX function %qs must have 2 scalar "
		 "parameter(s) for the 'XC' format class", fn_name);
	  return;
	}
      if (void_p)
	{
	  error ("pragma intrinsic: APEX function %qs must return the same "
		 "type as the first parameter for the 'XC' format class",
		 fn_name);
	  return;
	}
    }
}

/* Map APEX operand layout to the corresponding instruction code.  */

static enum insn_code
arcv_apex_icode (unsigned int insn_format)
{
  unsigned int insn_operands = insn_format >> 5;
  bool is_volatile = insn_format & APEX_VOLATILE;

  /* Void return types are always volatile (side effects).  */
  switch (insn_operands)
  {
    case APEX_VOID_FTYPE:
      return CODE_FOR_riscv_arcv_apex_void_ftype_v;

    case APEX_VOID_FTYPE_SRC0:
      return CODE_FOR_riscv_arcv_apex_void_ftype_src0_v;

    case APEX_VOID_FTYPE_SRC0_SRC1:
      return CODE_FOR_riscv_arcv_apex_void_ftype_src0_src1_v;

    case APEX_DEST_FTYPE:
      return is_volatile ? CODE_FOR_riscv_arcv_apex_dest_ftype_v
			 : CODE_FOR_riscv_arcv_apex_dest_ftype;

    case APEX_DEST_FTYPE_SRC0:
      return is_volatile ? CODE_FOR_riscv_arcv_apex_dest_ftype_src0_v
			 : CODE_FOR_riscv_arcv_apex_dest_ftype_src0;

    case APEX_DEST_FTYPE_SRC0_SRC1:
      return is_volatile ? CODE_FOR_riscv_arcv_apex_dest_ftype_src0_src1_v
			 : CODE_FOR_riscv_arcv_apex_dest_ftype_src0_src1;

    default:
      return CODE_FOR_nothing;
   }
}

/* Initialize an APEX built-in from pragma directive.  */

void
arcv_apex_register_builtin (tree fndecl, const char *fn_name,
			const char *mnemonic, unsigned int format_flags,
			unsigned int opcode)
{
  if (!arcv_apex_infer_operand_flags (&format_flags, fndecl))
    return;

  if ((format_flags & APEX_FORMAT_MASK) == APEX_NONE)
    format_flags = arcv_apex_infer_format (format_flags, opcode);
  arcv_apex_validate_format (fn_name, format_flags, opcode);

  enum insn_code icode = arcv_apex_icode (format_flags);
  enum riscv_builtin_type builtin_type
	= (format_flags & APEX_VOID) ? RISCV_BUILTIN_DIRECT_NO_TARGET
				     : RISCV_BUILTIN_DIRECT;

  /* Store APEX insn information.  */
  arcv_apex_builtins[arcv_apex_builtin_index]
    = { icode, fn_name, xstrdup (mnemonic), opcode, builtin_type,
	format_flags };

  fndecl->function_decl.built_in_class = BUILT_IN_MD;

  fndecl->function_decl.function_code
	= (arcv_apex_builtin_index << RISCV_BUILTIN_SHIFT) + RISCV_BUILTIN_APEX;

  arcv_apex_builtin_index++;

  arcv_apex_emit_ext_directive (mnemonic, opcode, format_flags);
}

/* Check if an APEX builtin with the given characteristics already exists.
   Returns the index if found with matching parameters, -1 if not found,
   or -2 if found but with conflicting parameters.  */

static int
arcv_apex_lto_lookup_builtin (const char *fn_name, const char *mnemonic,
			    unsigned int opcode, unsigned int format_flags,
			    location_t loc)
{
  for (int i = 0; i < arcv_apex_builtin_index; i++)
    {
      const struct arcv_apex_builtin_description *d = &arcv_apex_builtins[i];

      /* Skip if function name doesn't match.  */
      if (strcmp (d->name, fn_name) != 0)
	continue;

      /* Function name matches - validate all parameters.  */
      bool mismatch = false;

      if (strcmp (d->mnemonic, mnemonic) != 0)
	{
	  warning_at (loc, 0, "APEX builtin %qs already registered with "
		      "different mnemonic: %qs vs %qs",
		      fn_name, d->mnemonic, mnemonic);
	  mismatch = true;
	}

      if (d->opcode != opcode)
	{
	  warning_at (loc, 0, "APEX builtin %qs already registered with "
		      "different opcode: 0x%x vs 0x%x",
		      fn_name, d->opcode, opcode);
	  mismatch = true;
	}

      if (d->format_flags != format_flags)
	{
	  warning_at (loc, 0, "APEX builtin %qs already registered with "
		      "different instruction formats: 0x%x vs 0x%x",
		      fn_name, d->format_flags, format_flags);
	  mismatch = true;
	}

      /* Return -2 for conflicting registration, or index if match.  */
      return mismatch ? -2 : i;
    }

  return -1;
}

static void
arcv_apex_lto_register_builtin (const char *fn_name, const char *mnemonic,
			      unsigned int opcode, unsigned int format_flags,
			      bool emit_directive_p, tree fndecl)
{
  location_t loc = DECL_SOURCE_LOCATION (fndecl);

  int existing_idx = arcv_apex_lto_lookup_builtin (fn_name, mnemonic, opcode,
					      format_flags, loc);

  if (existing_idx == -2)
    {
      error_at (loc, "APEX builtin %qs has conflicting definitions across "
	     "compilation units", fn_name);
      return;
    }

  if (existing_idx >= 0)
    {
      fndecl->function_decl.function_code
	= (existing_idx << RISCV_BUILTIN_SHIFT) + RISCV_BUILTIN_APEX;
      return;
    }

  gcc_assert (arcv_apex_builtin_index < arcv_apex_builtins_limit);

  enum riscv_builtin_type builtin_type
	= (format_flags & APEX_VOID) ? RISCV_BUILTIN_DIRECT_NO_TARGET
				     : RISCV_BUILTIN_DIRECT;

  enum insn_code icode = arcv_apex_icode (format_flags);

  /* Store APEX insn information.  */
  arcv_apex_builtins[arcv_apex_builtin_index]
    = { icode, xstrdup (fn_name), xstrdup (mnemonic), opcode,
	builtin_type, format_flags };

  fndecl->function_decl.function_code
    = (arcv_apex_builtin_index << RISCV_BUILTIN_SHIFT) + RISCV_BUILTIN_APEX;

  arcv_apex_builtin_index++;

  if (emit_directive_p)
    arcv_apex_emit_ext_directive (mnemonic, opcode, format_flags);
}

/* LTO serialization for APEX intrinsics.

   APEX intrinsics are registered dynamically via #pragma intrinsic,
   so their metadata must be explicitly serialized to survive LTO.
   See lto-streamer-out.cc (produce_asm_for_decls) and
   lto/lto-common.cc (read_cgraph_and_symbols) for the call sites.  */

/* Serialize all referenced APEX intrinsics to the LTO stream.  */

void
arcv_apex_lto_write_section (void)
{
  if (arcv_apex_builtin_index == 0)
    return;

  auto_vec<int> used_indices;
  for (int i = 0; i < arcv_apex_builtin_index; i++)
    {
      const struct arcv_apex_builtin_description *d = &arcv_apex_builtins[i];
      gcc_assert (d->name);

      symtab_node *snode
	= symtab_node::get_for_asmname (get_identifier (d->name));

      if (snode && snode->referred_to_p ())
	used_indices.safe_push (i);
    }

  if (used_indices.is_empty ())
    return;

  struct lto_simple_output_block *ob
    = lto_create_simple_output_block (LTO_section_riscv_apex);

  if (!ob)
    return;

  streamer_write_uhwi_stream (ob->main_stream, used_indices.length ());

  for (unsigned int idx = 0; idx < used_indices.length (); idx++)
    {
      const struct arcv_apex_builtin_description *d
	= &arcv_apex_builtins[used_indices[idx]];

      gcc_assert (d->name && d->mnemonic);

      size_t name_len = strlen (d->name);
      streamer_write_uhwi_stream (ob->main_stream, name_len);
      for (size_t j = 0; j < name_len; j++)
	streamer_write_char_stream (ob->main_stream, d->name[j]);

      size_t mnemonic_len = strlen (d->mnemonic);
      streamer_write_uhwi_stream (ob->main_stream, mnemonic_len);
      for (size_t j = 0; j < mnemonic_len; j++)
	streamer_write_char_stream (ob->main_stream, d->mnemonic[j]);

      streamer_write_uhwi_stream (ob->main_stream, d->opcode);
      streamer_write_uhwi_stream (ob->main_stream, d->format_flags);
    }

  lto_destroy_simple_output_block (ob);
}

/* Deserialize and re-register APEX intrinsics from all LTO input files.  */

void
arcv_apex_lto_read_section (void)
{
  struct lto_file_decl_data **file_data_vec = lto_get_file_decl_data ();
  struct lto_file_decl_data *file_data;
  unsigned int j = 0;

  while ((file_data = file_data_vec[j++]))
    {
      const char *data;
      size_t len;
      class lto_input_block *ib
	= lto_create_simple_input_block (file_data, LTO_section_riscv_apex,
					 &data, &len);

      if (!ib)
	continue;

      unsigned int apex_count = streamer_read_uhwi (ib);
      unsigned int registered_count = 0;

      for (unsigned int i = 0; i < apex_count; i++)
	{
	  unsigned int fn_name_len = streamer_read_uhwi (ib);
	  char *fn_name = XNEWVEC (char, fn_name_len + 1);
	  for (unsigned int k = 0; k < fn_name_len; k++)
	    fn_name[k] = streamer_read_uchar (ib);
	  fn_name[fn_name_len] = '\0';

	  unsigned int mnemonic_len = streamer_read_uhwi (ib);
	  char *mnemonic = XNEWVEC (char, mnemonic_len + 1);
	  for (unsigned int k = 0; k < mnemonic_len; k++)
	    mnemonic[k] = streamer_read_uchar (ib);
	  mnemonic[mnemonic_len] = '\0';

	  unsigned int opcode = streamer_read_uhwi (ib);
	  unsigned int format_flags = streamer_read_uhwi (ib);

	  symtab_node *snode
	    = symtab_node::get_for_asmname (get_identifier (fn_name));

	  cgraph_node *node = dyn_cast<cgraph_node *> (snode);
	  if (node)
	    {
	      tree fndecl = node->decl;
	      if (fndecl && TREE_CODE (fndecl) == FUNCTION_DECL)
		{
		  arcv_apex_lto_register_builtin (fn_name, mnemonic, opcode,
						  format_flags, !flag_wpa,
						  fndecl);
		  registered_count++;
		}
	    }

	  XDELETEVEC (fn_name);
	  XDELETEVEC (mnemonic);
	}

      if (registered_count != apex_count)
	warning (0, "APEX LTO: expected %u intrinsics but registered %u",
		 apex_count, registered_count);

      lto_destroy_simple_input_block (file_data, LTO_section_riscv_apex,
				      ib, data, len);
    }
}

/* Validate the immediate argument passed to an APEX intrinsic.
   Used during builtin expansion.  */

bool
arcv_apex_immediate_argument_valid_p (unsigned int subcode, tree exp)
{
  if (arcv_apex_format_enabled_p (subcode, APEX_XD))
    return true;

  tree arg;
  HOST_WIDE_INT val;
  HOST_WIDE_INT min_val, max_val;

  if (arcv_apex_format_enabled_p (subcode, APEX_XI))
  {
    arg = CALL_EXPR_ARG (exp, 0);
    min_val = -2048;
    max_val = 2047;
  }
  else if (arcv_apex_format_enabled_p (subcode, APEX_XC)
	   || arcv_apex_format_enabled_p (subcode, APEX_XS))
  {
    arg = CALL_EXPR_ARG (exp, 1);
    min_val = arcv_apex_format_enabled_p (subcode, APEX_XS) ? -128 : -2048;
    max_val = arcv_apex_format_enabled_p (subcode, APEX_XS) ? 127 : 2047;
  }
  else
    return true;

  if (!TREE_CONSTANT (arg) || TREE_CODE (arg) != INTEGER_CST)
  {
    error ("argument to %qs must be a constant integer",
	   arcv_apex_builtins[subcode].name);
    return false;
  }

  val = tree_to_shwi (arg);
  if (val < min_val || val > max_val)
  {
    error ("argument value %wd is outside the valid range [%wd, %wd]",
	   val, min_val, max_val);
    return false;
  }

  return true;
}

/* Take argument ARGNO from EXP's argument list and convert it into
   an expand operand.  Store the operand in *OP.  */

static void
arcv_apex_prepare_builtin_arg (struct expand_operand *op, tree exp,
			       unsigned argno)
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
arcv_apex_expand_builtin_insn (enum insn_code icode, unsigned int n_ops,
			       struct expand_operand *ops, bool has_target_p)
{
  if (!maybe_expand_insn (icode, n_ops, ops))
    {
      error ("invalid argument to built-in function");
      return has_target_p ? gen_reg_rtx (ops[0].mode) : const0_rtx;
    }

  return has_target_p ? ops[0].value : const0_rtx;
}

/* Expand a RISCV_BUILTIN_DIRECT or RISCV_BUILTIN_DIRECT_NO_TARGET function
   for APEX builtins; HAS_TARGET_P says which.  EXP is the CALL_EXPR that
   calls the function and ICODE is the code of the associated .md pattern.
   TARGET, if nonnull, suggests a good place to put the result.  */

static rtx
arcv_apex_expand_builtin_direct (enum insn_code icode, rtx target, tree exp,
				 bool has_target_p, unsigned int subcode)
{
  struct expand_operand ops[MAX_RECOG_OPERANDS];

  /* Map any target to operand 0.  */
  int opno = 0;
  if (has_target_p)
    create_output_operand (&ops[opno++], target, TYPE_MODE (TREE_TYPE (exp)));

  /* Create an RTL constant for the APEX subcode.  */
  rtx const_rtx = GEN_INT (subcode);
  /* Add the subcode as an additional input operand to the RTL expression.  */
  create_input_operand (&ops[opno++], const_rtx, SImode);
  /* Validate the immediate argument passed to the APEX intrinsic.  */
  if (!arcv_apex_immediate_argument_valid_p (subcode, exp))
    return const0_rtx;

  /* Map the arguments to the other operands.  */
  gcc_assert (opno + call_expr_nargs (exp)
	      == insn_data[icode].n_generator_args);
  for (int argno = 0; argno < call_expr_nargs (exp); argno++)
    arcv_apex_prepare_builtin_arg (&ops[opno++], exp, argno);

  return arcv_apex_expand_builtin_insn (icode, opno, ops, has_target_p);
}

/* Expand an APEX builtin.  */

rtx
arcv_apex_expand_builtin (unsigned int subcode, tree exp, rtx target)
{
  const struct arcv_apex_builtin_description *d = &arcv_apex_builtins[subcode];

  switch (d->builtin_type)
    {
    case RISCV_BUILTIN_DIRECT:
      return arcv_apex_expand_builtin_direct (d->icode, target, exp, true,
					      subcode);

    case RISCV_BUILTIN_DIRECT_NO_TARGET:
      return arcv_apex_expand_builtin_direct (d->icode, target, exp, false,
					      subcode);
    }

  gcc_unreachable ();
}
