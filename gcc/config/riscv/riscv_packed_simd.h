/* RISC-V 'Packed SIMD' Extension intrinsics include file.
   Copyright (C) 2025-2026 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef __RISCV_PACKED_SIMD_H
#define __RISCV_PACKED_SIMD_H

#include <stdint.h>

#ifndef __riscv_p
#error "Packed SIMD intrinsics require the P extension"
#else

typedef signed char int8x4_t __attribute__ ((vector_size (4)));
typedef signed char int8x8_t __attribute__ ((vector_size (8)));
typedef short int16x2_t __attribute__ ((vector_size (4)));
typedef short int16x4_t __attribute__ ((vector_size (8)));
typedef int int32x2_t __attribute__ ((vector_size (8)));
typedef unsigned char uint8x4_t __attribute__ ((vector_size (4)));
typedef unsigned char uint8x8_t __attribute__ ((vector_size (8)));
typedef unsigned short uint16x2_t __attribute__ ((vector_size (4)));
typedef unsigned short uint16x4_t __attribute__ ((vector_size (8)));
typedef unsigned int uint32x2_t __attribute__ ((vector_size (8)));

/* The memory intrinsics accept pointers with arbitrary alignment.  These
   types also avoid imposing the aliasing rules of their scalar types on the
   pointed-to objects.  */
typedef uint32_t __rvp_unaligned_uint32_t
  __attribute__ ((__aligned__ (1), __may_alias__));
typedef uint64_t __rvp_unaligned_uint64_t
  __attribute__ ((__aligned__ (1), __may_alias__));

#if __riscv_xlen == 32
typedef int32_t intXLEN_t;
typedef uint32_t uintXLEN_t;
typedef int32_t int32xN_t;
typedef uint32_t uint32xN_t;
typedef uint16x2_t uint16xN_t;
typedef int16x2_t int16xN_t;
typedef uint8x4_t uint8xN_t;
typedef int8x4_t int8xN_t;
#else
typedef int64_t intXLEN_t;
typedef uint64_t uintXLEN_t;
typedef int32x2_t int32xN_t;
typedef uint32x2_t uint32xN_t;
typedef uint16x4_t uint16xN_t;
typedef int16x4_t int16xN_t;
typedef uint8x8_t uint8xN_t;
typedef int8x8_t int8xN_t;
#endif

#define RVP_INTRINSIC_PREFIX __riscv_
#define RVP_INTRINSIC_VECTOR_PREFIX __riscv_v_

#define RVP_OP_ATTRS \
  __extension__ extern __inline __attribute__ ((__always_inline__, __gnu_inline__, __artificial__))

#define RVP_ARGUMENT_LIST(_0, _1, _2, _3, _4, _5, ...) _5
#define RVP_N_ARG(...) RVP_ARGUMENT_LIST (_, ##__VA_ARGS__, 4, 3, 2, 1, 0)

#define RVP_VAR0(...)
#define RVP_VAR1(type1) a
#define RVP_VAR2(type1, type2) RVP_VAR1 (type1), b
#define RVP_VAR3(type1, type2, type3) RVP_VAR2 (type1, type2), c
#define RVP_VAR4(type1, type2, type3, type4) RVP_VAR3 (type1, type2, type3), d

#define RVP_ARG0(...)
#define RVP_ARG1(type1) type1 a
#define RVP_ARG2(type1, type2) RVP_ARG1 (type1), type2 b
#define RVP_ARG3(type1, type2, type3) RVP_ARG2 (type1, type2), type3 c
#define RVP_ARG4(type1, type2, type3, type4)                                  \
RVP_ARG3 (type1, type2, type3), type4 d

#define RVP_CONCAT_IMPL(x, y) x##y
#define RVP_CONCAT(x, y) RVP_CONCAT_IMPL (x, y)
#define RVP_EXPAND_ARGS(...)                                                  \
RVP_CONCAT (RVP_ARG, RVP_N_ARG (__VA_ARGS__)) (__VA_ARGS__)
#define RVP_EXPAND_VARS(...)                                                  \
RVP_CONCAT (RVP_VAR, RVP_N_ARG (__VA_ARGS__)) (__VA_ARGS__)

#define RVP_VECTOR_BUILTIN_PREFIX __builtin_riscv_v_

#define CREATE_RVP_INTRINSIC(return_type, name, ...)                          \
DIRECT_CREATE_RVP_INTRINSIC (return_type, name, name, __riscv_,             \
			       __builtin_riscv_, RVP_EXPAND_ARGS,             \
			       RVP_EXPAND_VARS, __VA_ARGS__)

#define CREATE_RVP_INTRINSIC_ALIAS(return_type, name, internal_name, ...)     \
DIRECT_CREATE_RVP_INTRINSIC (return_type, name, internal_name, __riscv_,    \
			       __builtin_riscv_, RVP_EXPAND_ARGS,             \
			       RVP_EXPAND_VARS, __VA_ARGS__)

/* RVP_N_ARG() expands to 0 in C89.  */
#define CREATE_RVP_INTRINSIC_EMPTY_ARGS(return_type, name, ...)               \
DIRECT_CREATE_RVP_INTRINSIC (return_type, name, name, RVP_INTRINSIC_PREFIX, \
			       __builtin_riscv_, RVP_ARG0, RVP_VAR0,          \
			       __VA_ARGS__)

#define CREATE_RVP_INTRINSIC_VECTOR(return_type, name, ...)                   \
DIRECT_CREATE_RVP_INTRINSIC (                                               \
  return_type, name, name, RVP_INTRINSIC_VECTOR_PREFIX,                     \
  RVP_VECTOR_BUILTIN_PREFIX, RVP_EXPAND_ARGS, RVP_EXPAND_VARS, __VA_ARGS__)

#define CREATE_RVP_INTRINSIC_VECTOR_ALIAS(return_type, name, internal_name,   \
					  ...)                                \
DIRECT_CREATE_RVP_INTRINSIC (                                               \
  return_type, name, internal_name, RVP_INTRINSIC_VECTOR_PREFIX,            \
  RVP_VECTOR_BUILTIN_PREFIX, RVP_EXPAND_ARGS, RVP_EXPAND_VARS, __VA_ARGS__)

#define DIRECT_CREATE_RVP_INTRINSIC(return_type, name, internal_name,         \
				    intrinsic_prefix, builtin_prefix,         \
				    arg_expand_macro, var_expand_macro, ...)  \
__extension__ extern __inline __attribute__ ((                              \
  __always_inline__, __gnu_inline__, __artificial__)) return_type           \
RVP_CONCAT (intrinsic_prefix, name (arg_expand_macro (__VA_ARGS__)))        \
{                                                                           \
  return RVP_CONCAT (builtin_prefix,                                        \
		       internal_name) (var_expand_macro (__VA_ARGS__));       \
}

#define RVP_UNARY_OP(name, ty, op)                                         \
RVP_OP_ATTRS ty __riscv_##name (ty __rs1)                                  \
  {                                                                        \
    return op __rs1;                                                       \
  }

#define RVP_VECTOR_OP(name, ty, ty2, rty, op)                              \
RVP_OP_ATTRS rty __riscv_##name (ty __rs1, ty2 __rs2)                      \
  {                                                                        \
    return (rty) (__rs1 op __rs2);                                         \
  }

#define RVP_BINARY_OP(name, ty, op)                                        \
  RVP_VECTOR_OP (name, ty, ty, ty, op)

#define RVP_SPLAT2(ty, x) ((ty){(x), (x)})
#define RVP_SPLAT4(ty, x) ((ty){(x), (x), (x), (x)})
#define RVP_SPLAT8(ty, x) \
  ((ty){(x), (x), (x), (x), (x), (x), (x), (x)})

#define RVP_SPLAT(name, ty, scalar_ty, splat)                              \
RVP_OP_ATTRS ty __riscv_##name (scalar_ty __x)                             \
  {                                                                        \
    return splat (ty, __x);                                                \
  }

#define RVP_SCALAR_BINARY_OP(name, ty, scalar_ty, op, splat)               \
RVP_OP_ATTRS ty __riscv_##name (ty __rs1, scalar_ty __rs2)                 \
  {                                                                        \
    return __rs1 op splat (ty, __rs2);                                     \
  }

#define RVP_SCALAR_SHIFT_OP(name, ty, scalar_ty, op)                       \
  RVP_VECTOR_OP (name, ty, scalar_ty, ty, op)

#define RVP_CMP_OP(name, ty, rty, op)                                      \
  RVP_VECTOR_OP (name, ty, ty, rty, op)

#define RVP_MINMAX_OP(name, ty, cmp)                                       \
RVP_OP_ATTRS ty __riscv_##name (ty __rs1, ty __rs2)                        \
  {                                                                        \
    return ((__rs1 cmp __rs2) & __rs1) | (~(__rs1 cmp __rs2) & __rs2);     \
  }

#define RVP_LOAD(name, vector_type, element_type, memory_type)              \
RVP_OP_ATTRS vector_type __riscv_##name (element_type *__p)                 \
  {                                                                        \
    union                                                                  \
    {                                                                      \
      vector_type __vector;                                                \
      memory_type __memory;                                                \
    } __value;                                                             \
    __value.__memory = *(const memory_type *) __p;                          \
    return __value.__vector;                                               \
  }

#define RVP_STORE(name, vector_type, element_type, memory_type)             \
RVP_OP_ATTRS void __riscv_##name (element_type *__p, vector_type __v)       \
  {                                                                        \
    union                                                                  \
    {                                                                      \
      vector_type __vector;                                                \
      memory_type __memory;                                                \
    } __value;                                                             \
    __value.__vector = __v;                                                \
    *(memory_type *) __p = __value.__memory;                               \
  }

#define RVP_CHECK_INDEX(index, limit)                                      \
  (__builtin_constant_p (index) && (unsigned int) (index) <= (limit)       \
   ? (void) 0                                                             \
   : __rvp_invalid_element_index ())

#define RVP_GET(value, index, limit)                                       \
  (RVP_CHECK_INDEX (index, limit), (value)[index])

#define RVP_SET(type, value, element, index, limit)                        \
  __extension__ ({                                                        \
    type __rvp_value = (value);                                           \
    RVP_CHECK_INDEX (index, limit);                                       \
    __rvp_value[index] = (element);                                       \
    __rvp_value;                                                          \
  })

#define RVP_JOIN2(name, vector_type, element_type)                         \
RVP_OP_ATTRS vector_type __riscv_##name (element_type __e0,                \
					 element_type __e1)                \
  {                                                                        \
    return (vector_type) { __e0, __e1 };                                   \
  }

#define RVP_JOIN4(name, vector_type, element_type)                         \
RVP_OP_ATTRS vector_type __riscv_##name (element_type __e0,                \
					 element_type __e1,                \
					 element_type __e2,                \
					 element_type __e3)                \
  {                                                                        \
    return (vector_type) { __e0, __e1, __e2, __e3 };                       \
  }

#define RVP_SUBVECTOR_GET(vector_type, subvector_type, value, index)       \
  __extension__ ({                                                        \
    union                                                                  \
    {                                                                      \
      vector_type __vector;                                                \
      subvector_type __subvectors[2];                                      \
    } __rvp_value;                                                         \
    __rvp_value.__vector = (value);                                        \
    RVP_CHECK_INDEX (index, 1);                                            \
    __rvp_value.__subvectors[index];                                       \
  })

#define RVP_SUBVECTOR_SET(vector_type, subvector_type, value, subvector,   \
			  index)                                            \
  __extension__ ({                                                        \
    union                                                                  \
    {                                                                      \
      vector_type __vector;                                                \
      subvector_type __subvectors[2];                                      \
    } __rvp_value;                                                         \
    __rvp_value.__vector = (value);                                        \
    RVP_CHECK_INDEX (index, 1);                                            \
    __rvp_value.__subvectors[index] = (subvector);                          \
    __rvp_value.__vector;                                                  \
  })

#define RVP_SUBVECTOR_JOIN(name, vector_type, subvector_type)              \
RVP_OP_ATTRS vector_type __riscv_##name (subvector_type __lo,              \
					 subvector_type __hi)              \
  {                                                                        \
    union                                                                  \
    {                                                                      \
      vector_type __vector;                                                \
      subvector_type __subvectors[2];                                      \
    } __value;                                                             \
    __value.__subvectors[0] = __lo;                                        \
    __value.__subvectors[1] = __hi;                                        \
    return __value.__vector;                                               \
  }

#define RVP_REINTERPRET(name, to_type, from_type) \
RVP_OP_ATTRS to_type __riscv_##name (from_type __x) \
  { \
    union \
    { \
      from_type __from; \
      to_type __to; \
    } __value; \
    __value.__from = __x; \
    return __value.__to; \
  }

#define RVP_SLIDE1(suffix, vector_type, scalar_type, unsigned_scalar_type, \
		   to_word, from_word, word_type, word_bits, \
		   element_bits, slx, srx) \
RVP_OP_ATTRS vector_type __riscv_pslide1up_##suffix \
  (vector_type __rd, scalar_type __rs1) \
  { \
    word_type __insert = ((word_type) (unsigned_scalar_type) __rs1 \
			  << ((word_bits) - (element_bits))); \
    return from_word (slx (to_word (__rd), __insert, element_bits)); \
  } \
RVP_OP_ATTRS vector_type __riscv_pslide1down_##suffix \
  (vector_type __rd, scalar_type __rs1) \
  { \
    word_type __insert = (word_type) (unsigned_scalar_type) __rs1; \
    return from_word (srx (to_word (__rd), __insert, element_bits)); \
  }

#define RVP_SLIDE1_PAIR(suffix, vector_type, scalar_type, to_vector, \
			pair_even, pair_odd_even) \
RVP_OP_ATTRS vector_type __riscv_pslide1up_##suffix \
  (vector_type __rd, scalar_type __rs1) \
  { \
    vector_type __insert = to_vector (__rs1); \
    return pair_even (__insert, __rd); \
  } \
RVP_OP_ATTRS vector_type __riscv_pslide1down_##suffix \
  (vector_type __rd, scalar_type __rs1) \
  { \
    vector_type __insert = to_vector (__rs1); \
    return pair_odd_even (__rd, __insert); \
  }

#define RVP_SLIDE1_PAIR_INIT(suffix, vector_type, scalar_type, pair_even, \
			     pair_odd_even) \
RVP_OP_ATTRS vector_type __riscv_pslide1up_##suffix \
  (vector_type __rd, scalar_type __rs1) \
  { \
    vector_type __insert = { __rs1, 0 }; \
    return pair_even (__insert, __rd); \
  } \
RVP_OP_ATTRS vector_type __riscv_pslide1down_##suffix \
  (vector_type __rd, scalar_type __rs1) \
  { \
    vector_type __insert = { __rs1, 0 }; \
    return pair_odd_even (__rd, __insert); \
  }

#define RVP_SLIDE(suffix, vector_type, to_word, from_word, element_bits, \
		  slx, srx) \
RVP_OP_ATTRS vector_type __riscv_pslideupx_##suffix \
  (vector_type __rd, vector_type __rs1, unsigned int __rs2) \
  { \
    return from_word (slx (to_word (__rd), to_word (__rs1), \
			    __rs2 * (element_bits))); \
  } \
RVP_OP_ATTRS vector_type __riscv_pslidedownx_##suffix \
  (vector_type __rd, vector_type __rs1, unsigned int __rs2) \
  { \
    return from_word (srx (to_word (__rd), to_word (__rs1), \
			    __rs2 * (element_bits))); \
  }

#ifdef __cplusplus
extern "C" {
#endif

extern void __rvp_invalid_element_index (void)
  __attribute__ ((__error__
		  ("P intrinsic index must be a constant in range")));

// Bitmanip (manual "Bitmanip" section, spec lines 48-133): suffixed names.
// These are the explicit, non-overloaded interfaces named per the spec.
// 32-bit (RV32 + RV64):
CREATE_RVP_INTRINSIC(unsigned, cls_32, int32_t)
CREATE_RVP_INTRINSIC(uint32_t, rev_32, uint32_t)
CREATE_RVP_INTRINSIC(uint32_t, slx_32, uint32_t, uint32_t, unsigned)
CREATE_RVP_INTRINSIC(uint32_t, srx_32, uint32_t, uint32_t, unsigned)
CREATE_RVP_INTRINSIC(uint64_t, wzip8p_64, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC(uint64_t, wzip16p_64, uint32_t, uint32_t)
// 64-bit (RV64 only):
#if __riscv_xlen == 64
CREATE_RVP_INTRINSIC(unsigned, cls_64, int64_t)
CREATE_RVP_INTRINSIC(uint64_t, rev_64, uint64_t)
CREATE_RVP_INTRINSIC(uint64_t, rev16_64, uint64_t)
CREATE_RVP_INTRINSIC(uint64_t, slx_64, uint64_t, uint64_t, unsigned)
CREATE_RVP_INTRINSIC(uint64_t, srx_64, uint64_t, uint64_t, unsigned)
CREATE_RVP_INTRINSIC(uint64_t, zip8p_64, uint64_t, uint64_t)
CREATE_RVP_INTRINSIC(uint64_t, zip16p_64, uint64_t, uint64_t)
CREATE_RVP_INTRINSIC(uint64_t, zip8hp_64, uint64_t, uint64_t)
CREATE_RVP_INTRINSIC(uint64_t, zip16hp_64, uint64_t, uint64_t)
CREATE_RVP_INTRINSIC(uint64_t, unzip8p_64, uint64_t, uint64_t)
CREATE_RVP_INTRINSIC(uint64_t, unzip16p_64, uint64_t, uint64_t)
CREATE_RVP_INTRINSIC(uint64_t, unzip8hp_64, uint64_t, uint64_t)
CREATE_RVP_INTRINSIC(uint64_t, unzip16hp_64, uint64_t, uint64_t)
#endif

/* Scalar Saturating and Averaging Arithmetic.  */
CREATE_RVP_INTRINSIC (int32_t, sadd_i32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, saddu_u32, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, ssub_i32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, ssubu_u32, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, aadd_i32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, aaddu_u32, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, asub_i32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, asubu_u32, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, ssh1sadd_i32, int32_t, int32_t)

/* Scalar Absolute Value.  */
CREATE_RVP_INTRINSIC (uint32_t, abs_u32, int32_t)
#if __riscv_xlen == 64
CREATE_RVP_INTRINSIC (uint64_t, abs_u64, int64_t)
#endif

/* Scalar Comparison.  */
CREATE_RVP_INTRINSIC (uint32_t, mseq_i32_u32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, mseq_u32_u32, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (uint32_t, mslt_u32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, msgt_u32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, msltu_u32, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (uint32_t, msgtu_u32, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (uint32_t, msne_i32_u32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, msne_u32_u32, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (uint32_t, msge_u32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, msle_u32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, msgeu_u32, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (uint32_t, msleu_u32, uint32_t, uint32_t)

/* Scalar Merge.  */
CREATE_RVP_INTRINSIC (int32_t, merge_i32, int32_t, int32_t, uint32_t)
CREATE_RVP_INTRINSIC (uint32_t, merge_u32, uint32_t, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (int64_t, merge_i64, int64_t, int64_t, uint64_t)
CREATE_RVP_INTRINSIC (uint64_t, merge_u64, uint64_t, uint64_t, uint64_t)

/* Scalar saturation.  */
CREATE_RVP_INTRINSIC (int32_t, sati_i32, int32_t, const unsigned)
CREATE_RVP_INTRINSIC (uint32_t, usati_u32, int32_t, const unsigned)
#if __riscv_xlen == 64
CREATE_RVP_INTRINSIC (int64_t, sati_i64, int64_t, const unsigned)
CREATE_RVP_INTRINSIC (uint64_t, usati_u64, int64_t, const unsigned)
#endif

/* Scalar saturating and rounding shifts.  */
CREATE_RVP_INTRINSIC (int32_t, ssha_i32, int32_t, int)
CREATE_RVP_INTRINSIC (int32_t, sshar_i32, int32_t, int)
CREATE_RVP_INTRINSIC (uint32_t, sshl_u32, int32_t, int)
CREATE_RVP_INTRINSIC (uint32_t, sshlr_u32, int32_t, int)
#if __riscv_xlen == 64
CREATE_RVP_INTRINSIC (int64_t, sha_i64, int64_t, int)
CREATE_RVP_INTRINSIC (int64_t, shar_i64, int64_t, int)
CREATE_RVP_INTRINSIC (uint64_t, shl_u64, uint64_t, int)
CREATE_RVP_INTRINSIC (uint64_t, shlr_u64, uint64_t, int)
#endif

/* Scalar narrowing clips.  */
CREATE_RVP_INTRINSIC (uint32_t, nclipu_u32, uint64_t, unsigned)
CREATE_RVP_INTRINSIC (uint32_t, nclipru_u32, uint64_t, unsigned)
CREATE_RVP_INTRINSIC (int32_t, nsrar_i32, int64_t, unsigned)
CREATE_RVP_INTRINSIC (int32_t, nclip_i32, int64_t, unsigned)
CREATE_RVP_INTRINSIC (int32_t, nclipr_i32, int64_t, unsigned)

/* Scalar multiply high and Q-format multiplication.  */
CREATE_RVP_INTRINSIC (int32_t, mulh_i32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (int32_t, mulhr_i32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, mulhu_u32, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (uint32_t, mulhru_u32, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, mulhsu_i32, int32_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, mulhrsu_i32, int32_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, mulq_i32, int32_t, int32_t)
CREATE_RVP_INTRINSIC (int32_t, mulqr_i32, int32_t, int32_t)

/* Scalar multiply high accumulate.  */
CREATE_RVP_INTRINSIC (int32_t, mhacc_i32, int32_t, int32_t, int32_t)
CREATE_RVP_INTRINSIC (int32_t, mhracc_i32, int32_t, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, mhaccu_u32, uint32_t, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (uint32_t, mhraccu_u32, uint32_t, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, mhaccsu_i32, int32_t, int32_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, mhraccsu_i32, int32_t, int32_t, uint32_t)

/* Scalar Q-format multiply with widening accumulate.  */
CREATE_RVP_INTRINSIC (int64_t, mqwacc_i64, int64_t, int32_t, int32_t)
CREATE_RVP_INTRINSIC (int64_t, mqrwacc_i64, int64_t, int32_t, int32_t)

/* Packed Splat */
RVP_SPLAT (pmv_s_u8x4, uint8x4_t, uint8_t, RVP_SPLAT4)
RVP_SPLAT (pmv_s_i8x4, int8x4_t, int8_t, RVP_SPLAT4)
RVP_SPLAT (pmv_s_u16x2, uint16x2_t, uint16_t, RVP_SPLAT2)
RVP_SPLAT (pmv_s_i16x2, int16x2_t, int16_t, RVP_SPLAT2)
RVP_SPLAT (pmv_s_u8x8, uint8x8_t, uint8_t, RVP_SPLAT8)
RVP_SPLAT (pmv_s_i8x8, int8x8_t, int8_t, RVP_SPLAT8)
RVP_SPLAT (pmv_s_u16x4, uint16x4_t, uint16_t, RVP_SPLAT4)
RVP_SPLAT (pmv_s_i16x4, int16x4_t, int16_t, RVP_SPLAT4)
RVP_SPLAT (pmv_s_u32x2, uint32x2_t, uint32_t, RVP_SPLAT2)
RVP_SPLAT (pmv_s_i32x2, int32x2_t, int32_t, RVP_SPLAT2)

/* Packed Addition and Subtraction (32-bit) */
RVP_BINARY_OP (padd_i8x4, int8x4_t, +)
RVP_BINARY_OP (padd_u8x4, uint8x4_t, +)
RVP_BINARY_OP (padd_i16x2, int16x2_t, +)
RVP_BINARY_OP (padd_u16x2, uint16x2_t, +)
RVP_BINARY_OP (psub_i8x4, int8x4_t, -)
RVP_BINARY_OP (psub_u8x4, uint8x4_t, -)
RVP_BINARY_OP (psub_i16x2, int16x2_t, -)
RVP_BINARY_OP (psub_u16x2, uint16x2_t, -)
RVP_UNARY_OP (pneg_i8x4, int8x4_t, -)
RVP_UNARY_OP (pneg_i16x2, int16x2_t, -)

/* Packed Addition and Subtraction (64-bit) */
RVP_BINARY_OP (padd_i8x8, int8x8_t, +)
RVP_BINARY_OP (padd_u8x8, uint8x8_t, +)
RVP_BINARY_OP (padd_i16x4, int16x4_t, +)
RVP_BINARY_OP (padd_u16x4, uint16x4_t, +)
RVP_BINARY_OP (padd_i32x2, int32x2_t, +)
RVP_BINARY_OP (padd_u32x2, uint32x2_t, +)
RVP_BINARY_OP (psub_i8x8, int8x8_t, -)
RVP_BINARY_OP (psub_u8x8, uint8x8_t, -)
RVP_BINARY_OP (psub_i16x4, int16x4_t, -)
RVP_BINARY_OP (psub_u16x4, uint16x4_t, -)
RVP_BINARY_OP (psub_i32x2, int32x2_t, -)
RVP_BINARY_OP (psub_u32x2, uint32x2_t, -)
RVP_UNARY_OP (pneg_i8x8, int8x8_t, -)
RVP_UNARY_OP (pneg_i16x4, int16x4_t, -)
RVP_UNARY_OP (pneg_i32x2, int32x2_t, -)

/* Packed Addition with Scalar */
RVP_SCALAR_BINARY_OP (padd_s_u8x4,  uint8x4_t,  uint8_t,  +, RVP_SPLAT4)
RVP_SCALAR_BINARY_OP (padd_s_i8x4,  int8x4_t,   int8_t,   +, RVP_SPLAT4)
RVP_SCALAR_BINARY_OP (padd_s_u16x2, uint16x2_t, uint16_t, +, RVP_SPLAT2)
RVP_SCALAR_BINARY_OP (padd_s_i16x2, int16x2_t,  int16_t,  +, RVP_SPLAT2)
RVP_SCALAR_BINARY_OP (padd_s_u8x8,  uint8x8_t,  uint8_t,  +, RVP_SPLAT8)
RVP_SCALAR_BINARY_OP (padd_s_i8x8,  int8x8_t,   int8_t,   +, RVP_SPLAT8)
RVP_SCALAR_BINARY_OP (padd_s_u16x4, uint16x4_t, uint16_t, +, RVP_SPLAT4)
RVP_SCALAR_BINARY_OP (padd_s_i16x4, int16x4_t,  int16_t,  +, RVP_SPLAT4)
RVP_SCALAR_BINARY_OP (padd_s_u32x2, uint32x2_t, uint32_t, +, RVP_SPLAT2)
RVP_SCALAR_BINARY_OP (padd_s_i32x2, int32x2_t,  int32_t,  +, RVP_SPLAT2)

/* Packed Saturating Addition and Subtraction.  */
CREATE_RVP_INTRINSIC (int8x4_t, psadd_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, psadd_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x4_t, psaddu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, psaddu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int8x4_t, pssub_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pssub_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pssubu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pssubu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, psadd_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, psadd_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, psadd_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint8x8_t, psaddu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, psaddu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, psaddu_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, pssub_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pssub_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pssub_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pssubu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pssubu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pssubu_u32x2, uint32x2_t, uint32x2_t)

/* Packed Averaging Addition and Subtraction.  */
CREATE_RVP_INTRINSIC (int8x4_t, paadd_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, paadd_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x4_t, paaddu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, paaddu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int8x4_t, pasub_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pasub_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pasubu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pasubu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, paadd_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, paadd_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, paadd_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint8x8_t, paaddu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, paaddu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, paaddu_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, pasub_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pasub_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pasub_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pasubu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pasubu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pasubu_u32x2, uint32x2_t, uint32x2_t)

/* Packed Shift-Add.  */
CREATE_RVP_INTRINSIC (int16x2_t, psh1add_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, psh1add_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, pssh1sadd_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, psh1add_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, psh1add_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, psh1add_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, psh1add_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pssh1sadd_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pssh1sadd_i32x2, int32x2_t, int32x2_t)

/* Packed Exchanged Addition and Subtraction.  */
CREATE_RVP_INTRINSIC (int16x2_t, pas_x_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pas_x_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pas_x_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, psa_x_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, psa_x_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, psa_x_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, psas_x_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, psas_x_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pssa_x_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pssa_x_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, paas_x_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, paas_x_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pasa_x_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pasa_x_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, psas_x_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pssa_x_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, paas_x_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pasa_x_i32x2, int32x2_t, int32x2_t)

/* Packed Absolute Value and Absolute Difference.  */
CREATE_RVP_INTRINSIC (uint8x4_t, pabs_i8x4, int8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pabs_i16x2, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pabd_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pabd_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pabdu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pabdu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pabs_i8x8, int8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pabs_i16x4, int16x4_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pabd_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pabd_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pabdu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pabdu_u16x4, uint16x4_t, uint16x4_t)

/* Packed Absolute Difference Sum.  */
CREATE_RVP_INTRINSIC (uint32_t, pabdsumu_u8x4_u32, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint32_t, pabdsumau_u8x4_u32, uint32_t, uint8x4_t,
		      uint8x4_t)
CREATE_RVP_INTRINSIC (uint32_t, pabdsumu_u8x8_u32, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint64_t, pabdsumu_u8x8_u64, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint32_t, pabdsumau_u8x8_u32, uint32_t, uint8x8_t,
		      uint8x8_t)
CREATE_RVP_INTRINSIC (uint64_t, pabdsumau_u8x8_u64, uint64_t, uint8x8_t,
		      uint8x8_t)

/* Packed Saturating Absolute Value.  */
CREATE_RVP_INTRINSIC (int8x4_t, psabs_i8x4, int8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, psabs_i16x2, int16x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, psabs_i8x8, int8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, psabs_i16x4, int16x4_t)

/* Packed Reduction Sum.  */
CREATE_RVP_INTRINSIC (int32_t, predsum_i8x4_i32, int8x4_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, predsumu_u8x4_u32, uint8x4_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, predsum_i16x2_i32, int16x2_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, predsumu_u16x2_u32, uint16x2_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, predsum_i8x8_i32, int8x8_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, predsumu_u8x8_u32, uint8x8_t, uint32_t)
CREATE_RVP_INTRINSIC (int32_t, predsum_i16x4_i32, int16x4_t, int32_t)
CREATE_RVP_INTRINSIC (uint32_t, predsumu_u16x4_u32, uint16x4_t, uint32_t)
CREATE_RVP_INTRINSIC (int64_t, predsum_i8x8_i64, int8x8_t, int64_t)
CREATE_RVP_INTRINSIC (uint64_t, predsumu_u8x8_u64, uint8x8_t, uint64_t)
CREATE_RVP_INTRINSIC (int64_t, predsum_i16x4_i64, int16x4_t, int64_t)
CREATE_RVP_INTRINSIC (uint64_t, predsumu_u16x4_u64, uint16x4_t, uint64_t)
CREATE_RVP_INTRINSIC (int64_t, predsum_i32x2_i64, int32x2_t, int64_t)
CREATE_RVP_INTRINSIC (uint64_t, predsumu_u32x2_u64, uint32x2_t, uint64_t)

/* Packed Minimum and Maximum.  */
RVP_MINMAX_OP (pmin_i8x4,   int8x4_t,   <)
RVP_MINMAX_OP (pmin_i16x2,  int16x2_t,  <)
RVP_MINMAX_OP (pminu_u8x4,  uint8x4_t,  <)
RVP_MINMAX_OP (pminu_u16x2, uint16x2_t, <)
RVP_MINMAX_OP (pmax_i8x4,   int8x4_t,   >)
RVP_MINMAX_OP (pmax_i16x2,  int16x2_t,  >)
RVP_MINMAX_OP (pmaxu_u8x4,  uint8x4_t,  >)
RVP_MINMAX_OP (pmaxu_u16x2, uint16x2_t, >)
RVP_MINMAX_OP (pmin_i8x8,   int8x8_t,   <)
RVP_MINMAX_OP (pmin_i16x4,  int16x4_t,  <)
RVP_MINMAX_OP (pmin_i32x2,  int32x2_t,  <)
RVP_MINMAX_OP (pminu_u8x8,  uint8x8_t,  <)
RVP_MINMAX_OP (pminu_u16x4, uint16x4_t, <)
RVP_MINMAX_OP (pminu_u32x2, uint32x2_t, <)
RVP_MINMAX_OP (pmax_i8x8,   int8x8_t,   >)
RVP_MINMAX_OP (pmax_i16x4,  int16x4_t,  >)
RVP_MINMAX_OP (pmax_i32x2,  int32x2_t,  >)
RVP_MINMAX_OP (pmaxu_u8x8,  uint8x8_t,  >)
RVP_MINMAX_OP (pmaxu_u16x4, uint16x4_t, >)
RVP_MINMAX_OP (pmaxu_u32x2, uint32x2_t, >)

/* Packed Comparison.  */
RVP_CMP_OP (pmseq_i8x4_u8x4, int8x4_t, uint8x4_t, ==)
RVP_CMP_OP (pmseq_u8x4_u8x4, uint8x4_t, uint8x4_t, ==)
RVP_CMP_OP (pmslt_u8x4, int8x4_t, uint8x4_t, <)
RVP_CMP_OP (pmsgt_u8x4, int8x4_t, uint8x4_t, >)
RVP_CMP_OP (pmsge_u8x4, int8x4_t, uint8x4_t, >=)
RVP_CMP_OP (pmsle_u8x4, int8x4_t, uint8x4_t, <=)
RVP_CMP_OP (pmsltu_u8x4, uint8x4_t, uint8x4_t, <)
RVP_CMP_OP (pmsgtu_u8x4, uint8x4_t, uint8x4_t, >)
RVP_CMP_OP (pmsgeu_u8x4, uint8x4_t, uint8x4_t, >=)
RVP_CMP_OP (pmsleu_u8x4, uint8x4_t, uint8x4_t, <=)
RVP_CMP_OP (pmsne_i8x4_u8x4, int8x4_t, uint8x4_t, !=)
RVP_CMP_OP (pmsne_u8x4_u8x4, uint8x4_t, uint8x4_t, !=)
RVP_CMP_OP (pmseq_i16x2_u16x2, int16x2_t, uint16x2_t, ==)
RVP_CMP_OP (pmseq_u16x2_u16x2, uint16x2_t, uint16x2_t, ==)
RVP_CMP_OP (pmslt_u16x2, int16x2_t, uint16x2_t, <)
RVP_CMP_OP (pmsgt_u16x2, int16x2_t, uint16x2_t, >)
RVP_CMP_OP (pmsge_u16x2, int16x2_t, uint16x2_t, >=)
RVP_CMP_OP (pmsle_u16x2, int16x2_t, uint16x2_t, <=)
RVP_CMP_OP (pmsltu_u16x2, uint16x2_t, uint16x2_t, <)
RVP_CMP_OP (pmsgtu_u16x2, uint16x2_t, uint16x2_t, >)
RVP_CMP_OP (pmsgeu_u16x2, uint16x2_t, uint16x2_t, >=)
RVP_CMP_OP (pmsleu_u16x2, uint16x2_t, uint16x2_t, <=)
RVP_CMP_OP (pmsne_i16x2_u16x2, int16x2_t, uint16x2_t, !=)
RVP_CMP_OP (pmsne_u16x2_u16x2, uint16x2_t, uint16x2_t, !=)
RVP_CMP_OP (pmseq_i8x8_u8x8, int8x8_t, uint8x8_t, ==)
RVP_CMP_OP (pmseq_u8x8_u8x8, uint8x8_t, uint8x8_t, ==)
RVP_CMP_OP (pmslt_u8x8, int8x8_t, uint8x8_t, <)
RVP_CMP_OP (pmsgt_u8x8, int8x8_t, uint8x8_t, >)
RVP_CMP_OP (pmsge_u8x8, int8x8_t, uint8x8_t, >=)
RVP_CMP_OP (pmsle_u8x8, int8x8_t, uint8x8_t, <=)
RVP_CMP_OP (pmsltu_u8x8, uint8x8_t, uint8x8_t, <)
RVP_CMP_OP (pmsgtu_u8x8, uint8x8_t, uint8x8_t, >)
RVP_CMP_OP (pmsgeu_u8x8, uint8x8_t, uint8x8_t, >=)
RVP_CMP_OP (pmsleu_u8x8, uint8x8_t, uint8x8_t, <=)
RVP_CMP_OP (pmsne_i8x8_u8x8, int8x8_t, uint8x8_t, !=)
RVP_CMP_OP (pmsne_u8x8_u8x8, uint8x8_t, uint8x8_t, !=)
RVP_CMP_OP (pmseq_i16x4_u16x4, int16x4_t, uint16x4_t, ==)
RVP_CMP_OP (pmseq_u16x4_u16x4, uint16x4_t, uint16x4_t, ==)
RVP_CMP_OP (pmslt_u16x4, int16x4_t, uint16x4_t, <)
RVP_CMP_OP (pmsgt_u16x4, int16x4_t, uint16x4_t, >)
RVP_CMP_OP (pmsge_u16x4, int16x4_t, uint16x4_t, >=)
RVP_CMP_OP (pmsle_u16x4, int16x4_t, uint16x4_t, <=)
RVP_CMP_OP (pmsltu_u16x4, uint16x4_t, uint16x4_t, <)
RVP_CMP_OP (pmsgtu_u16x4, uint16x4_t, uint16x4_t, >)
RVP_CMP_OP (pmsgeu_u16x4, uint16x4_t, uint16x4_t, >=)
RVP_CMP_OP (pmsleu_u16x4, uint16x4_t, uint16x4_t, <=)
RVP_CMP_OP (pmsne_i16x4_u16x4, int16x4_t, uint16x4_t, !=)
RVP_CMP_OP (pmsne_u16x4_u16x4, uint16x4_t, uint16x4_t, !=)
RVP_CMP_OP (pmseq_i32x2_u32x2, int32x2_t, uint32x2_t, ==)
RVP_CMP_OP (pmseq_u32x2_u32x2, uint32x2_t, uint32x2_t, ==)
RVP_CMP_OP (pmslt_u32x2, int32x2_t, uint32x2_t, <)
RVP_CMP_OP (pmsgt_u32x2, int32x2_t, uint32x2_t, >)
RVP_CMP_OP (pmsge_u32x2, int32x2_t, uint32x2_t, >=)
RVP_CMP_OP (pmsle_u32x2, int32x2_t, uint32x2_t, <=)
RVP_CMP_OP (pmsltu_u32x2, uint32x2_t, uint32x2_t, <)
RVP_CMP_OP (pmsgtu_u32x2, uint32x2_t, uint32x2_t, >)
RVP_CMP_OP (pmsgeu_u32x2, uint32x2_t, uint32x2_t, >=)
RVP_CMP_OP (pmsleu_u32x2, uint32x2_t, uint32x2_t, <=)
RVP_CMP_OP (pmsne_i32x2_u32x2, int32x2_t, uint32x2_t, !=)
RVP_CMP_OP (pmsne_u32x2_u32x2, uint32x2_t, uint32x2_t, !=)

/* Packed Merge.  */
CREATE_RVP_INTRINSIC (uint8x4_t, pmerge_u8x4, uint8x4_t, uint8x4_t,
			uint8x4_t)
CREATE_RVP_INTRINSIC (int8x4_t, pmerge_i8x4, int8x4_t, int8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmerge_u16x2, uint16x2_t, uint16x2_t,
			uint16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmerge_i16x2, int16x2_t, int16x2_t,
			uint16x2_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmerge_u8x8, uint8x8_t, uint8x8_t,
			uint8x8_t)
CREATE_RVP_INTRINSIC (int8x8_t, pmerge_i8x8, int8x8_t, int8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmerge_u16x4, uint16x4_t, uint16x4_t,
			uint16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmerge_i16x4, int16x4_t, int16x4_t,
			uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmerge_u32x2, uint32x2_t, uint32x2_t,
			uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmerge_i32x2, int32x2_t, int32x2_t,
			uint32x2_t)

/* Packed Sign and Zero Extend.  */
CREATE_RVP_INTRINSIC (int16x2_t, psext_b_i16x2, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pzext_b_u16x2, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, psext_b_i16x4, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, psext_b_i32x2, int32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, psext_h_i32x2, int32x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pzext_b_u16x4, uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pzext_h_u32x2, uint32x2_t)

/* Packed Saturation.  */
CREATE_RVP_INTRINSIC (uint16x2_t, pusati_u16x2, int16x2_t, unsigned)
CREATE_RVP_INTRINSIC (int16x2_t, psati_i16x2, int16x2_t, unsigned)
CREATE_RVP_INTRINSIC (uint16x4_t, pusati_u16x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint32x2_t, pusati_u32x2, int32x2_t, unsigned)
CREATE_RVP_INTRINSIC (int16x4_t, psati_i16x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (int32x2_t, psati_i32x2, int32x2_t, unsigned)

/* Packed Shifts.  */
RVP_SCALAR_SHIFT_OP (psll_s_u8x4,  uint8x4_t,  unsigned, <<)
RVP_SCALAR_SHIFT_OP (psll_s_i8x4,  int8x4_t,   unsigned, <<)
RVP_SCALAR_SHIFT_OP (psll_s_u16x2, uint16x2_t, unsigned, <<)
RVP_SCALAR_SHIFT_OP (psll_s_i16x2, int16x2_t,  unsigned, <<)
RVP_SCALAR_SHIFT_OP (psrl_s_u8x4,  uint8x4_t,  unsigned, >>)
RVP_SCALAR_SHIFT_OP (psrl_s_u16x2, uint16x2_t, unsigned, >>)
RVP_SCALAR_SHIFT_OP (psra_s_i8x4,  int8x4_t,   unsigned, >>)
RVP_SCALAR_SHIFT_OP (psra_s_i16x2, int16x2_t,  unsigned, >>)
RVP_SCALAR_SHIFT_OP (psll_s_u8x8,  uint8x8_t,  unsigned, <<)
RVP_SCALAR_SHIFT_OP (psll_s_i8x8,  int8x8_t,   unsigned, <<)
RVP_SCALAR_SHIFT_OP (psll_s_u16x4, uint16x4_t, unsigned, <<)
RVP_SCALAR_SHIFT_OP (psll_s_i16x4, int16x4_t,  unsigned, <<)
RVP_SCALAR_SHIFT_OP (psll_s_u32x2, uint32x2_t, unsigned, <<)
RVP_SCALAR_SHIFT_OP (psll_s_i32x2, int32x2_t,  unsigned, <<)
RVP_SCALAR_SHIFT_OP (psrl_s_u8x8,  uint8x8_t,  unsigned, >>)
RVP_SCALAR_SHIFT_OP (psrl_s_u16x4, uint16x4_t, unsigned, >>)
RVP_SCALAR_SHIFT_OP (psrl_s_u32x2, uint32x2_t, unsigned, >>)
RVP_SCALAR_SHIFT_OP (psra_s_i8x8,  int8x8_t,   unsigned, >>)
RVP_SCALAR_SHIFT_OP (psra_s_i16x4, int16x4_t,  unsigned, >>)
RVP_SCALAR_SHIFT_OP (psra_s_i32x2, int32x2_t,  unsigned, >>)

/* Packed Saturating and Rounding Shifts.  */
CREATE_RVP_INTRINSIC (int16x2_t, pssha_s_i16x2, int16x2_t, int)
CREATE_RVP_INTRINSIC (int16x2_t, psshar_s_i16x2, int16x2_t, int)
CREATE_RVP_INTRINSIC (uint16x2_t, psshl_s_u16x2, uint16x2_t, int)
CREATE_RVP_INTRINSIC (uint16x2_t, psshlr_s_u16x2, uint16x2_t, int)
CREATE_RVP_INTRINSIC (int16x4_t, pssha_s_i16x4, int16x4_t, int)
CREATE_RVP_INTRINSIC (int32x2_t, pssha_s_i32x2, int32x2_t, int)
CREATE_RVP_INTRINSIC (int16x4_t, psshar_s_i16x4, int16x4_t, int)
CREATE_RVP_INTRINSIC (int32x2_t, psshar_s_i32x2, int32x2_t, int)
CREATE_RVP_INTRINSIC (uint16x4_t, psshl_s_u16x4, uint16x4_t, int)
CREATE_RVP_INTRINSIC (uint32x2_t, psshl_s_u32x2, uint32x2_t, int)
CREATE_RVP_INTRINSIC (uint16x4_t, psshlr_s_u16x4, uint16x4_t, int)
CREATE_RVP_INTRINSIC (uint32x2_t, psshlr_s_u32x2, uint32x2_t, int)

/* Packed Pair.  */
CREATE_RVP_INTRINSIC (uint8x4_t, ppaire_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (int8x4_t, ppaire_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, ppaireo_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (int8x4_t, ppaireo_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, ppairoe_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (int8x4_t, ppairoe_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, ppairo_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (int8x4_t, ppairo_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, ppaire_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, ppaire_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, ppaireo_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, ppaireo_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, ppairoe_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, ppairoe_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, ppairo_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, ppairo_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x8_t, ppaire_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (int8x8_t, ppaire_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, ppaireo_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (int8x8_t, ppaireo_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, ppairoe_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (int8x8_t, ppairoe_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, ppairo_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (int8x8_t, ppairo_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, ppaire_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, ppaire_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, ppaireo_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, ppaireo_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, ppairoe_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, ppairoe_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, ppairo_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, ppairo_i16x4, int16x4_t, int16x4_t)

CREATE_RVP_INTRINSIC (uint32x2_t, ppaire_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, ppaire_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, ppaireo_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, ppaireo_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, ppairoe_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, ppairoe_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, ppairo_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, ppairo_i32x2, int32x2_t, int32x2_t)

/* Packed Widening Convert.  */
CREATE_RVP_INTRINSIC (int16x4_t, pwcvt_i16x4, int8x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwcvt_i32x2, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwcvtu_u16x4, uint8x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwcvtu_u32x2, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pwcvth_i16x4, int8x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwcvth_u16x4, uint8x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwcvth_i32x2, int16x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwcvth_u32x2, uint16x2_t)

/* Packed Narrowing Convert.  */
CREATE_RVP_INTRINSIC (int8x4_t, pncvt_i8x4, int16x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pncvt_u8x4, uint16x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pncvt_i16x2, int32x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pncvt_u16x2, uint32x2_t)
CREATE_RVP_INTRINSIC (int8x4_t, pncvth_i8x4, int16x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pncvth_u8x4, uint16x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pncvth_i16x2, int32x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pncvth_u16x2, uint32x2_t)

/* Packed Zip.  */
CREATE_RVP_INTRINSIC (int8x8_t, pzip_i8x8, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pzip_u8x8, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pzip_i16x4, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pzip_u16x4, uint16x2_t, uint16x2_t)

/* Packed Unzip.  */
CREATE_RVP_INTRINSIC (int8x4_t, punzipe_i8x4, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x4_t, punzipe_u8x4, uint8x8_t)
CREATE_RVP_INTRINSIC (int8x4_t, punzipo_i8x4, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x4_t, punzipo_u8x4, uint8x8_t)
CREATE_RVP_INTRINSIC (int16x2_t, punzipe_i16x2, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, punzipe_u16x2, uint16x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, punzipo_i16x2, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, punzipo_u16x2, uint16x4_t)

/* Packed Narrowing Zip.  */
CREATE_RVP_INTRINSIC (int8x4_t, pnzip_i8x4, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pnzip_u8x4, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int8x4_t, pnziph_i8x4, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pnziph_u8x4, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, pnzip_i8x8, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pnzip_u8x8, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int8x8_t, pnziph_i8x8, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pnziph_u8x8, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pnzip_i16x4, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pnzip_u16x4, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pnziph_i16x4, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pnziph_u16x4, uint32x2_t, uint32x2_t)

/* Packed Widening Unzip.  */
CREATE_RVP_INTRINSIC (int16x2_t, pwunzipe_i16x2, int8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pwunzipo_i16x2, int8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pwunzipue_u16x2, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pwunzipuo_u16x2, uint8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pwunziphe_i16x2, int8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pwunziphe_u16x2, uint8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pwunzipho_i16x2, int8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pwunzipho_u16x2, uint8x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pwunzipe_i16x4, int8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pwunzipo_i16x4, int8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwunzipue_u16x4, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwunzipuo_u16x4, uint8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pwunziphe_i16x4, int8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwunziphe_u16x4, uint8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pwunzipho_i16x4, int8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwunzipho_u16x4, uint8x8_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwunzipe_i32x2, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwunzipo_i32x2, int16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwunzipue_u32x2, uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwunzipuo_u32x2, uint16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwunziphe_i32x2, int16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwunziphe_u32x2, uint16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwunzipho_i32x2, int16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwunzipho_u32x2, uint16x4_t)

/* Packed Widening Addition and Subtraction.  */
#if __riscv_xlen == 32
CREATE_RVP_INTRINSIC (int16x4_t, pwadd_i16x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwadd_i32x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwaddu_u16x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwaddu_u32x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pwsub_i16x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwsub_i32x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwsubu_u16x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwsubu_u32x2, uint16x2_t, uint16x2_t)

/* Packed Widening Addition and Subtraction Accumulate.  */
CREATE_RVP_INTRINSIC (int16x4_t, pwadda_i16x4, int16x4_t, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwadda_i32x2, int32x2_t, int16x2_t,
			int16x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwaddau_u16x4, uint16x4_t, uint8x4_t,
			uint8x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwaddau_u32x2, uint32x2_t, uint16x2_t,
			uint16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pwsuba_i16x4, int16x4_t, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwsuba_i32x2, int32x2_t, int16x2_t,
			int16x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwsubau_u16x4, uint16x4_t, uint8x4_t,
			uint8x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwsubau_u32x2, uint32x2_t, uint16x2_t,
			uint16x2_t)
#else
RVP_OP_ATTRS int16x4_t
__riscv_pwadd_i16x4 (int8x4_t __rs1, int8x4_t __rs2)
{
  union
  {
    int8x8_t __bytes;
    int16x4_t __halves;
  } __zipped;

  __zipped.__bytes = __builtin_riscv_pzip_i8x8 (__rs1, __rs2);
  return (__builtin_riscv_psext_b_i16x4 (__zipped.__halves)
	  + __riscv_psra_s_i16x4 (__zipped.__halves, 8));
}

RVP_OP_ATTRS int32x2_t
__riscv_pwadd_i32x2 (int16x2_t __rs1, int16x2_t __rs2)
{
  int16x4_t __ones = { 1, 1, 1, 1 };
  int16x4_t __zipped = __builtin_riscv_pzip_i16x4 (__rs1, __rs2);
  return __builtin_riscv_pm2add_i16x4 (__zipped, __ones);
}

RVP_OP_ATTRS uint16x4_t
__riscv_pwaddu_u16x4 (uint8x4_t __rs1, uint8x4_t __rs2)
{
  return (__builtin_riscv_pwcvtu_u16x4 (__rs1)
	  + __builtin_riscv_pwcvtu_u16x4 (__rs2));
}

RVP_OP_ATTRS uint32x2_t
__riscv_pwaddu_u32x2 (uint16x2_t __rs1, uint16x2_t __rs2)
{
  uint16x4_t __ones = { 1, 1, 1, 1 };
  uint16x4_t __zipped = __builtin_riscv_pzip_u16x4 (__rs1, __rs2);
  return __builtin_riscv_pm2addu_u16x4 (__zipped, __ones);
}

RVP_OP_ATTRS int16x4_t
__riscv_pwsub_i16x4 (int8x4_t __rs1, int8x4_t __rs2)
{
  union
  {
    int8x8_t __bytes;
    int16x4_t __halves;
  } __zipped;

  __zipped.__bytes = __builtin_riscv_pzip_i8x8 (__rs1, __rs2);
  return (__builtin_riscv_psext_b_i16x4 (__zipped.__halves)
	  - __riscv_psra_s_i16x4 (__zipped.__halves, 8));
}

RVP_OP_ATTRS int32x2_t
__riscv_pwsub_i32x2 (int16x2_t __rs1, int16x2_t __rs2)
{
  int16x4_t __ones = { 1, 1, 1, 1 };
  int16x4_t __zipped = __builtin_riscv_pzip_i16x4 (__rs1, __rs2);
  return __builtin_riscv_pm2sub_i16x4 (__zipped, __ones);
}

RVP_OP_ATTRS uint16x4_t
__riscv_pwsubu_u16x4 (uint8x4_t __rs1, uint8x4_t __rs2)
{
  return (__builtin_riscv_pwcvtu_u16x4 (__rs1)
	  - __builtin_riscv_pwcvtu_u16x4 (__rs2));
}

RVP_OP_ATTRS uint32x2_t
__riscv_pwsubu_u32x2 (uint16x2_t __rs1, uint16x2_t __rs2)
{
  return (__builtin_riscv_pwcvtu_u32x2 (__rs1)
	  - __builtin_riscv_pwcvtu_u32x2 (__rs2));
}

RVP_OP_ATTRS int16x4_t
__riscv_pwadda_i16x4 (int16x4_t __rd, int8x4_t __rs1, int8x4_t __rs2)
{
  return __rd + __riscv_pwadd_i16x4 (__rs1, __rs2);
}

RVP_OP_ATTRS int32x2_t
__riscv_pwadda_i32x2 (int32x2_t __rd, int16x2_t __rs1, int16x2_t __rs2)
{
  int16x4_t __ones = { 1, 1, 1, 1 };
  int16x4_t __zipped = __builtin_riscv_pzip_i16x4 (__rs1, __rs2);
  return __builtin_riscv_pm2adda_i16x4 (__rd, __zipped, __ones);
}

RVP_OP_ATTRS uint16x4_t
__riscv_pwaddau_u16x4 (uint16x4_t __rd, uint8x4_t __rs1,
			uint8x4_t __rs2)
{
  return __rd + __riscv_pwaddu_u16x4 (__rs1, __rs2);
}

RVP_OP_ATTRS uint32x2_t
__riscv_pwaddau_u32x2 (uint32x2_t __rd, uint16x2_t __rs1,
			uint16x2_t __rs2)
{
  uint16x4_t __ones = { 1, 1, 1, 1 };
  uint16x4_t __zipped = __builtin_riscv_pzip_u16x4 (__rs1, __rs2);
  return __builtin_riscv_pm2addau_u16x4 (__rd, __zipped, __ones);
}

RVP_OP_ATTRS int16x4_t
__riscv_pwsuba_i16x4 (int16x4_t __rd, int8x4_t __rs1, int8x4_t __rs2)
{
  return __rd + __riscv_pwsub_i16x4 (__rs1, __rs2);
}

RVP_OP_ATTRS int32x2_t
__riscv_pwsuba_i32x2 (int32x2_t __rd, int16x2_t __rs1, int16x2_t __rs2)
{
  int16x4_t __ones = { 1, 1, 1, 1 };
  int16x4_t __zipped = __builtin_riscv_pzip_i16x4 (__rs1, __rs2);
  return __builtin_riscv_pm2suba_i16x4 (__rd, __zipped, __ones);
}

RVP_OP_ATTRS uint16x4_t
__riscv_pwsubau_u16x4 (uint16x4_t __rd, uint8x4_t __rs1,
			uint8x4_t __rs2)
{
  return __rd + __riscv_pwsubu_u16x4 (__rs1, __rs2);
}

RVP_OP_ATTRS uint32x2_t
__riscv_pwsubau_u32x2 (uint32x2_t __rd, uint16x2_t __rs1,
			uint16x2_t __rs2)
{
  return __rd + __riscv_pwsubu_u32x2 (__rs1, __rs2);
}
#endif

/* Packed Widening Shift.  */
#if __riscv_xlen == 32
CREATE_RVP_INTRINSIC (uint16x4_t, pwsll_s_u16x4, uint8x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint32x2_t, pwsll_s_u32x2, uint16x2_t, unsigned)
CREATE_RVP_INTRINSIC (int16x4_t, pwsla_s_i16x4, int8x4_t, unsigned)
CREATE_RVP_INTRINSIC (int32x2_t, pwsla_s_i32x2, int16x2_t, unsigned)

/* Packed Narrowing Shift.  */
CREATE_RVP_INTRINSIC (uint8x4_t, pnsrl_s_u8x4, uint16x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint16x2_t, pnsrl_s_u16x2, uint32x2_t, unsigned)
CREATE_RVP_INTRINSIC (int8x4_t, pnsra_s_i8x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (int16x2_t, pnsra_s_i16x2, int32x2_t, unsigned)
CREATE_RVP_INTRINSIC (int8x4_t, pnsrar_s_i8x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (int16x2_t, pnsrar_s_i16x2, int32x2_t, unsigned)
#else
RVP_OP_ATTRS uint16x4_t
__riscv_pwsll_s_u16x4 (uint8x4_t __rs1, unsigned int __shamt)
{
  uint16x4_t __wide = __builtin_riscv_pwcvtu_u16x4 (__rs1);
  return __riscv_psll_s_u16x4 (__wide, __shamt);
}

RVP_OP_ATTRS uint32x2_t
__riscv_pwsll_s_u32x2 (uint16x2_t __rs1, unsigned int __shamt)
{
  uint32x2_t __wide = __builtin_riscv_pwcvtu_u32x2 (__rs1);
  return __riscv_psll_s_u32x2 (__wide, __shamt);
}

RVP_OP_ATTRS int16x4_t
__riscv_pwsla_s_i16x4 (int8x4_t __rs1, unsigned int __shamt)
{
  if (__builtin_constant_p (__shamt))
    {
      unsigned int __shift = __shamt & 31;
      int16x4_t __wide = __builtin_riscv_pwcvth_i16x4 (__rs1);

      if (__shift <= 8)
	return __riscv_psra_s_i16x4 (__wide, 8 - __shift);
      if (__shift < 16)
	return __riscv_psll_s_i16x4 (__wide, __shift - 8);
      return (int16x4_t) { 0, 0, 0, 0 };
    }

  int16x4_t __wide = __builtin_riscv_pwcvt_i16x4 (__rs1);
  return __riscv_psll_s_i16x4 (__wide, __shamt);
}

RVP_OP_ATTRS int32x2_t
__riscv_pwsla_s_i32x2 (int16x2_t __rs1, unsigned int __shamt)
{
  if (__builtin_constant_p (__shamt))
    {
      unsigned int __shift = __shamt & 31;
      int32x2_t __wide = __builtin_riscv_pwcvth_i32x2 (__rs1);

      if (__shift <= 16)
	return __riscv_psra_s_i32x2 (__wide, 16 - __shift);
      return __riscv_psll_s_i32x2 (__wide, __shift - 16);
    }

  int32x2_t __wide = __builtin_riscv_pwcvt_i32x2 (__rs1);
  return __riscv_psll_s_i32x2 (__wide, __shamt);
}

RVP_OP_ATTRS uint8x4_t
__riscv_pnsrl_s_u8x4 (uint16x4_t __rs1, unsigned int __shamt)
{
  uint16x4_t __shifted = __riscv_psrl_s_u16x4 (__rs1, __shamt);
  return __builtin_riscv_pncvt_u8x4 (__shifted);
}

RVP_OP_ATTRS uint16x2_t
__riscv_pnsrl_s_u16x2 (uint32x2_t __rs1, unsigned int __shamt)
{
  uint32x2_t __shifted = __riscv_psrl_s_u32x2 (__rs1, __shamt);
  return __builtin_riscv_pncvt_u16x2 (__shifted);
}

RVP_OP_ATTRS int8x4_t
__riscv_pnsra_s_i8x4 (int16x4_t __rs1, unsigned int __shamt)
{
  int16x4_t __shifted = __riscv_psra_s_i16x4 (__rs1, __shamt);
  return __builtin_riscv_pncvt_i8x4 (__shifted);
}

RVP_OP_ATTRS int16x2_t
__riscv_pnsra_s_i16x2 (int32x2_t __rs1, unsigned int __shamt)
{
  int32x2_t __shifted = __riscv_psra_s_i32x2 (__rs1, __shamt);
  return __builtin_riscv_pncvt_i16x2 (__shifted);
}

RVP_OP_ATTRS int8x4_t
__riscv_pnsrar_s_i8x4 (int16x4_t __rs1, unsigned int __shamt)
{
  int __shift = -((int) __shamt & 31);
  int16x4_t __shifted = __builtin_riscv_psshar_s_i16x4 (__rs1, __shift);
  return __builtin_riscv_pncvt_i8x4 (__shifted);
}

RVP_OP_ATTRS int16x2_t
__riscv_pnsrar_s_i16x2 (int32x2_t __rs1, unsigned int __shamt)
{
  int __shift = -((int) __shamt & 31);
  int32x2_t __shifted = __builtin_riscv_psshar_s_i32x2 (__rs1, __shift);
  return __builtin_riscv_pncvt_i16x2 (__shifted);
}
#endif

/* Packed Narrowing Clip.  */
#if __riscv_xlen == 32
CREATE_RVP_INTRINSIC (uint8x4_t, pnclipu_s_u8x4, uint16x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint16x2_t, pnclipu_s_u16x2, uint32x2_t, unsigned)
CREATE_RVP_INTRINSIC (uint8x4_t, pnclipru_s_u8x4, uint16x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint16x2_t, pnclipru_s_u16x2, uint32x2_t, unsigned)
CREATE_RVP_INTRINSIC (int8x4_t, pnclip_s_i8x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (int16x2_t, pnclip_s_i16x2, int32x2_t, unsigned)
CREATE_RVP_INTRINSIC (int8x4_t, pnclipr_s_i8x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (int16x2_t, pnclipr_s_i16x2, int32x2_t, unsigned)
#else
RVP_OP_ATTRS uint8x4_t
__riscv_pnclipu_s_u8x4 (uint16x4_t __rs1, unsigned int __shamt)
{
  uint16x4_t __shifted = __riscv_psrl_s_u16x4 (__rs1, __shamt);
  uint8x8_t __narrowed
    = __builtin_riscv_pnclipup_u8x8 (__shifted, (uint16x4_t) { 0 });
  return RVP_SUBVECTOR_GET (uint8x8_t, uint8x4_t, __narrowed, 0);
}

RVP_OP_ATTRS uint16x2_t
__riscv_pnclipu_s_u16x2 (uint32x2_t __rs1, unsigned int __shamt)
{
  uint32x2_t __shifted = __riscv_psrl_s_u32x2 (__rs1, __shamt);
  uint16x4_t __narrowed
    = __builtin_riscv_pnclipup_u16x4 (__shifted, (uint32x2_t) { 0 });
  return RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __narrowed, 0);
}

RVP_OP_ATTRS uint8x4_t
__riscv_pnclipru_s_u8x4 (uint16x4_t __rs1, unsigned int __shamt)
{
  int __shift = -((int) __shamt & 31);
  uint16x4_t __shifted = __builtin_riscv_psshlr_s_u16x4 (__rs1, __shift);
  uint8x8_t __narrowed
    = __builtin_riscv_pnclipup_u8x8 (__shifted, (uint16x4_t) { 0 });
  return RVP_SUBVECTOR_GET (uint8x8_t, uint8x4_t, __narrowed, 0);
}

RVP_OP_ATTRS uint16x2_t
__riscv_pnclipru_s_u16x2 (uint32x2_t __rs1, unsigned int __shamt)
{
  int __shift = -((int) __shamt & 31);
  uint32x2_t __shifted = __builtin_riscv_psshlr_s_u32x2 (__rs1, __shift);
  uint16x4_t __narrowed
    = __builtin_riscv_pnclipup_u16x4 (__shifted, (uint32x2_t) { 0 });
  return RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __narrowed, 0);
}

RVP_OP_ATTRS int8x4_t
__riscv_pnclip_s_i8x4 (int16x4_t __rs1, unsigned int __shamt)
{
  int16x4_t __shifted = __riscv_psra_s_i16x4 (__rs1, __shamt);
  int8x8_t __narrowed
    = __builtin_riscv_pnclipp_i8x8 (__shifted, (int16x4_t) { 0 });
  return RVP_SUBVECTOR_GET (int8x8_t, int8x4_t, __narrowed, 0);
}

RVP_OP_ATTRS int16x2_t
__riscv_pnclip_s_i16x2 (int32x2_t __rs1, unsigned int __shamt)
{
  int32x2_t __shifted = __riscv_psra_s_i32x2 (__rs1, __shamt);
  int16x4_t __narrowed
    = __builtin_riscv_pnclipp_i16x4 (__shifted, (int32x2_t) { 0 });
  return RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __narrowed, 0);
}

RVP_OP_ATTRS int8x4_t
__riscv_pnclipr_s_i8x4 (int16x4_t __rs1, unsigned int __shamt)
{
  int __shift = -((int) __shamt & 31);
  int16x4_t __shifted = __builtin_riscv_psshar_s_i16x4 (__rs1, __shift);
  int8x8_t __narrowed
    = __builtin_riscv_pnclipp_i8x8 (__shifted, (int16x4_t) { 0 });
  return RVP_SUBVECTOR_GET (int8x8_t, int8x4_t, __narrowed, 0);
}

RVP_OP_ATTRS int16x2_t
__riscv_pnclipr_s_i16x2 (int32x2_t __rs1, unsigned int __shamt)
{
  int __shift = -((int) __shamt & 31);
  int32x2_t __shifted = __builtin_riscv_psshar_s_i32x2 (__rs1, __shift);
  int16x4_t __narrowed
    = __builtin_riscv_pnclipp_i16x4 (__shifted, (int32x2_t) { 0 });
  return RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __narrowed, 0);
}
#endif

/* Packed Narrowing Clip Pair.  */
CREATE_RVP_INTRINSIC (int8x4_t, pnclipp_i8x4, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pnclipup_u8x4, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, pnclipp_i16x2, int32_t, int32_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pnclipup_u16x2, uint32_t, uint32_t)
CREATE_RVP_INTRINSIC (int8x8_t, pnclipp_i8x8, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pnclipup_u8x8, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pnclipp_i16x4, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pnclipup_u16x4, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pnclipp_i32x2, int64_t, int64_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pnclipup_u32x2, uint64_t, uint64_t)

/* Packed Reverse.  */
CREATE_RVP_INTRINSIC (int8x4_t, prev_i8x4, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, prev_u8x4, uint8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, prev_i16x2, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, prev_u16x2, uint16x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, prev_i8x8, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, prev_u8x8, uint8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, prev_i16x4, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, prev_u16x4, uint16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, prev_i32x2, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, prev_u32x2, uint32x2_t)

/* Packed Multiply High.  */
CREATE_RVP_INTRINSIC (int16x2_t, pmulh_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmulhr_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmulhu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmulhru_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmulhsu_i16x2, int16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmulhrsu_i16x2, int16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmulh_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmulhr_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmulhu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmulhru_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmulhsu_i16x4, int16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmulhrsu_i16x4, int16x4_t, uint16x4_t)

/* Packed Multiply High for 64-bit i32x2 values.  */
#if __riscv_xlen == 32
RVP_OP_ATTRS int32x2_t
__riscv_pmulh_i32x2 (int32x2_t __rs1, int32x2_t __rs2)
{
  return (int32x2_t) { __builtin_riscv_mulh_i32 (__rs1[0], __rs2[0]),
		       __builtin_riscv_mulh_i32 (__rs1[1], __rs2[1]) };
}

RVP_OP_ATTRS int32x2_t
__riscv_pmulhr_i32x2 (int32x2_t __rs1, int32x2_t __rs2)
{
  return (int32x2_t) { __builtin_riscv_mulhr_i32 (__rs1[0], __rs2[0]),
		       __builtin_riscv_mulhr_i32 (__rs1[1], __rs2[1]) };
}

RVP_OP_ATTRS uint32x2_t
__riscv_pmulhu_u32x2 (uint32x2_t __rs1, uint32x2_t __rs2)
{
  return (uint32x2_t) { __builtin_riscv_mulhu_u32 (__rs1[0], __rs2[0]),
			__builtin_riscv_mulhu_u32 (__rs1[1], __rs2[1]) };
}

RVP_OP_ATTRS uint32x2_t
__riscv_pmulhru_u32x2 (uint32x2_t __rs1, uint32x2_t __rs2)
{
  return (uint32x2_t) { __builtin_riscv_mulhru_u32 (__rs1[0], __rs2[0]),
			__builtin_riscv_mulhru_u32 (__rs1[1], __rs2[1]) };
}

RVP_OP_ATTRS int32x2_t
__riscv_pmulhsu_i32x2 (int32x2_t __rs1, uint32x2_t __rs2)
{
  return (int32x2_t) { __builtin_riscv_mulhsu_i32 (__rs1[0], __rs2[0]),
		       __builtin_riscv_mulhsu_i32 (__rs1[1], __rs2[1]) };
}

RVP_OP_ATTRS int32x2_t
__riscv_pmulhrsu_i32x2 (int32x2_t __rs1, uint32x2_t __rs2)
{
  return (int32x2_t) { __builtin_riscv_mulhrsu_i32 (__rs1[0], __rs2[0]),
		       __builtin_riscv_mulhrsu_i32 (__rs1[1], __rs2[1]) };
}
#else
CREATE_RVP_INTRINSIC (int32x2_t, pmulh_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmulhr_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmulhu_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmulhru_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmulhsu_i32x2, int32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmulhrsu_i32x2, int32x2_t, uint32x2_t)
#endif

/* Packed Multiply High Accumulate.  */
CREATE_RVP_INTRINSIC (int16x2_t, pmhacc_i16x2, int16x2_t, int16x2_t,
			int16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmhracc_i16x2, int16x2_t, int16x2_t,
			int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmhaccu_u16x2, uint16x2_t, uint16x2_t,
			uint16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmhraccu_u16x2, uint16x2_t, uint16x2_t,
			uint16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmhaccsu_i16x2, int16x2_t, int16x2_t,
			uint16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmhraccsu_i16x2, int16x2_t, int16x2_t,
			uint16x2_t)
#if __riscv_xlen == 32
RVP_OP_ATTRS int16x4_t
__riscv_pmhacc_i16x4 (int16x4_t __rd, int16x4_t __rs1, int16x4_t __rs2)
{
  int16x2_t __lo = __builtin_riscv_pmhacc_i16x2 (
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rd, 0),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 0),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs2, 0));
  int16x2_t __hi = __builtin_riscv_pmhacc_i16x2 (
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rd, 1),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 1),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs2, 1));
  int16x4_t __result
    = RVP_SUBVECTOR_SET (int16x4_t, int16x2_t, __rd, __lo, 0);
  return RVP_SUBVECTOR_SET (int16x4_t, int16x2_t, __result, __hi, 1);
}

RVP_OP_ATTRS int16x4_t
__riscv_pmhracc_i16x4 (int16x4_t __rd, int16x4_t __rs1, int16x4_t __rs2)
{
  int16x2_t __lo = __builtin_riscv_pmhracc_i16x2 (
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rd, 0),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 0),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs2, 0));
  int16x2_t __hi = __builtin_riscv_pmhracc_i16x2 (
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rd, 1),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 1),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs2, 1));
  int16x4_t __result
    = RVP_SUBVECTOR_SET (int16x4_t, int16x2_t, __rd, __lo, 0);
  return RVP_SUBVECTOR_SET (int16x4_t, int16x2_t, __result, __hi, 1);
}

RVP_OP_ATTRS uint16x4_t
__riscv_pmhaccu_u16x4 (uint16x4_t __rd, uint16x4_t __rs1,
			uint16x4_t __rs2)
{
  uint16x2_t __lo = __builtin_riscv_pmhaccu_u16x2 (
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rd, 0),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs1, 0),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 0));
  uint16x2_t __hi = __builtin_riscv_pmhaccu_u16x2 (
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rd, 1),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs1, 1),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 1));
  uint16x4_t __result
    = RVP_SUBVECTOR_SET (uint16x4_t, uint16x2_t, __rd, __lo, 0);
  return RVP_SUBVECTOR_SET (uint16x4_t, uint16x2_t, __result, __hi, 1);
}

RVP_OP_ATTRS uint16x4_t
__riscv_pmhraccu_u16x4 (uint16x4_t __rd, uint16x4_t __rs1,
			 uint16x4_t __rs2)
{
  uint16x2_t __lo = __builtin_riscv_pmhraccu_u16x2 (
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rd, 0),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs1, 0),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 0));
  uint16x2_t __hi = __builtin_riscv_pmhraccu_u16x2 (
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rd, 1),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs1, 1),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 1));
  uint16x4_t __result
    = RVP_SUBVECTOR_SET (uint16x4_t, uint16x2_t, __rd, __lo, 0);
  return RVP_SUBVECTOR_SET (uint16x4_t, uint16x2_t, __result, __hi, 1);
}

RVP_OP_ATTRS int16x4_t
__riscv_pmhaccsu_i16x4 (int16x4_t __rd, int16x4_t __rs1,
			 uint16x4_t __rs2)
{
  int16x2_t __lo = __builtin_riscv_pmhaccsu_i16x2 (
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rd, 0),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 0),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 0));
  int16x2_t __hi = __builtin_riscv_pmhaccsu_i16x2 (
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rd, 1),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 1),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 1));
  int16x4_t __result
    = RVP_SUBVECTOR_SET (int16x4_t, int16x2_t, __rd, __lo, 0);
  return RVP_SUBVECTOR_SET (int16x4_t, int16x2_t, __result, __hi, 1);
}

RVP_OP_ATTRS int16x4_t
__riscv_pmhraccsu_i16x4 (int16x4_t __rd, int16x4_t __rs1,
			  uint16x4_t __rs2)
{
  int16x2_t __lo = __builtin_riscv_pmhraccsu_i16x2 (
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rd, 0),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 0),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 0));
  int16x2_t __hi = __builtin_riscv_pmhraccsu_i16x2 (
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rd, 1),
    RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 1),
    RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 1));
  int16x4_t __result
    = RVP_SUBVECTOR_SET (int16x4_t, int16x2_t, __rd, __lo, 0);
  return RVP_SUBVECTOR_SET (int16x4_t, int16x2_t, __result, __hi, 1);
}

RVP_OP_ATTRS int32x2_t
__riscv_pmhacc_i32x2 (int32x2_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  return (int32x2_t) {
    __builtin_riscv_mhacc_i32 (__rd[0], __rs1[0], __rs2[0]),
    __builtin_riscv_mhacc_i32 (__rd[1], __rs1[1], __rs2[1]) };
}

RVP_OP_ATTRS int32x2_t
__riscv_pmhracc_i32x2 (int32x2_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  return (int32x2_t) {
    __builtin_riscv_mhracc_i32 (__rd[0], __rs1[0], __rs2[0]),
    __builtin_riscv_mhracc_i32 (__rd[1], __rs1[1], __rs2[1]) };
}

RVP_OP_ATTRS uint32x2_t
__riscv_pmhaccu_u32x2 (uint32x2_t __rd, uint32x2_t __rs1,
			uint32x2_t __rs2)
{
  return (uint32x2_t) {
    __builtin_riscv_mhaccu_u32 (__rd[0], __rs1[0], __rs2[0]),
    __builtin_riscv_mhaccu_u32 (__rd[1], __rs1[1], __rs2[1]) };
}

RVP_OP_ATTRS uint32x2_t
__riscv_pmhraccu_u32x2 (uint32x2_t __rd, uint32x2_t __rs1,
			 uint32x2_t __rs2)
{
  return (uint32x2_t) {
    __builtin_riscv_mhraccu_u32 (__rd[0], __rs1[0], __rs2[0]),
    __builtin_riscv_mhraccu_u32 (__rd[1], __rs1[1], __rs2[1]) };
}

RVP_OP_ATTRS int32x2_t
__riscv_pmhaccsu_i32x2 (int32x2_t __rd, int32x2_t __rs1,
			 uint32x2_t __rs2)
{
  return (int32x2_t) {
    __builtin_riscv_mhaccsu_i32 (__rd[0], __rs1[0], __rs2[0]),
    __builtin_riscv_mhaccsu_i32 (__rd[1], __rs1[1], __rs2[1]) };
}

RVP_OP_ATTRS int32x2_t
__riscv_pmhraccsu_i32x2 (int32x2_t __rd, int32x2_t __rs1,
			  uint32x2_t __rs2)
{
  return (int32x2_t) {
    __builtin_riscv_mhraccsu_i32 (__rd[0], __rs1[0], __rs2[0]),
    __builtin_riscv_mhraccsu_i32 (__rd[1], __rs1[1], __rs2[1]) };
}
#else
CREATE_RVP_INTRINSIC (int16x4_t, pmhacc_i16x4, int16x4_t, int16x4_t,
			int16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmhracc_i16x4, int16x4_t, int16x4_t,
			int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmhaccu_u16x4, uint16x4_t, uint16x4_t,
			uint16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmhraccu_u16x4, uint16x4_t, uint16x4_t,
			uint16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmhaccsu_i16x4, int16x4_t, int16x4_t,
			uint16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmhraccsu_i16x4, int16x4_t, int16x4_t,
			uint16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmhacc_i32x2, int32x2_t, int32x2_t,
			int32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmhracc_i32x2, int32x2_t, int32x2_t,
			int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmhaccu_u32x2, uint32x2_t, uint32x2_t,
			uint32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmhraccu_u32x2, uint32x2_t, uint32x2_t,
			uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmhaccsu_i32x2, int32x2_t, int32x2_t,
			uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmhraccsu_i32x2, int32x2_t, int32x2_t,
			uint32x2_t)
#endif

/* Packed Q-format Multiplication.  */
CREATE_RVP_INTRINSIC (int16x2_t, pmulq_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmulqr_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmulq_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmulqr_i16x4, int16x4_t, int16x4_t)
#if __riscv_xlen == 32
RVP_OP_ATTRS int32x2_t
__riscv_pmulq_i32x2 (int32x2_t __rs1, int32x2_t __rs2)
{
  return (int32x2_t) { __builtin_riscv_mulq_i32 (__rs1[0], __rs2[0]),
		       __builtin_riscv_mulq_i32 (__rs1[1], __rs2[1]) };
}

RVP_OP_ATTRS int32x2_t
__riscv_pmulqr_i32x2 (int32x2_t __rs1, int32x2_t __rs2)
{
  return (int32x2_t) { __builtin_riscv_mulqr_i32 (__rs1[0], __rs2[0]),
		       __builtin_riscv_mulqr_i32 (__rs1[1], __rs2[1]) };
}
#else
CREATE_RVP_INTRINSIC (int32x2_t, pmulq_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmulqr_i32x2, int32x2_t, int32x2_t)
#endif

/* Packed Q-format Multiply Parts Accumulate.  */
/* h-series i32 (both ISAs): RV32 mqacc.hNN/mqracc.hNN, RV64  */
/* pmqacc.w.hNN/pmqracc.w.hNN  */
CREATE_RVP_INTRINSIC (int32_t, mqacc_h00_i32, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int32_t, mqacc_h01_i32, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int32_t, mqacc_h11_i32, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int32_t, mqracc_h00_i32, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int32_t, mqracc_h01_i32, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int32_t, mqracc_h11_i32, int32_t, int16x2_t, int16x2_t)
/* h-series i32x2 (packed): RV64 pmqacc.w.hNN/pmqracc.w.hNN, RV32 2x  */
/* mqacc.hNN/mqracc.hNN  */
CREATE_RVP_INTRINSIC (int32x2_t, pmqacc_h00_i32x2, int32x2_t, int16x4_t,
			int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmqacc_h01_i32x2, int32x2_t, int16x4_t,
			int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmqacc_h11_i32x2, int32x2_t, int16x4_t,
			int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmqracc_h00_i32x2, int32x2_t, int16x4_t,
			int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmqracc_h01_i32x2, int32x2_t, int16x4_t,
			int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmqracc_h11_i32x2, int32x2_t, int16x4_t,
			int16x4_t)
/* w-series i64.  */
#if __riscv_xlen == 32
RVP_OP_ATTRS int64_t
__riscv_mqacc_w00_i64 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  return __builtin_riscv_mqwacc_i64 (__rd, __rs1[0], __rs2[0]);
}

RVP_OP_ATTRS int64_t
__riscv_mqacc_w01_i64 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  return __builtin_riscv_mqwacc_i64 (__rd, __rs1[0], __rs2[1]);
}

RVP_OP_ATTRS int64_t
__riscv_mqacc_w11_i64 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  return __builtin_riscv_mqwacc_i64 (__rd, __rs1[1], __rs2[1]);
}

RVP_OP_ATTRS int64_t
__riscv_mqracc_w00_i64 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  return __builtin_riscv_mqrwacc_i64 (__rd, __rs1[0], __rs2[0]);
}

RVP_OP_ATTRS int64_t
__riscv_mqracc_w01_i64 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  return __builtin_riscv_mqrwacc_i64 (__rd, __rs1[0], __rs2[1]);
}

RVP_OP_ATTRS int64_t
__riscv_mqracc_w11_i64 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  return __builtin_riscv_mqrwacc_i64 (__rd, __rs1[1], __rs2[1]);
}
#else
CREATE_RVP_INTRINSIC (int64_t, mqacc_w00_i64, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mqacc_w01_i64, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mqacc_w11_i64, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mqracc_w00_i64, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mqracc_w01_i64, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mqracc_w11_i64, int64_t, int32x2_t, int32x2_t)
#endif

/* Packed Multiply Parts.  */
/* b-series i16x2 (both ISAs, single insn):  */
/* pmul.h.bNN/pmulu.h.bNN/pmulsu.h.bNN  */
CREATE_RVP_INTRINSIC (int16x2_t, pmul_b00_i16x2, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmul_b01_i16x2, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmul_b11_i16x2, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmulu_b00_u16x2, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmulu_b01_u16x2, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmulu_b11_u16x2, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmulsu_b00_i16x2, int8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmulsu_b11_i16x2, int8x4_t, uint8x4_t)
/* h-series i32 (scalar): RV32 mul.hNN/mulu.hNN/mulsu.hNN; RV64  */
/* pmul.w.hNN/etc  */
CREATE_RVP_INTRINSIC (int32_t, mul_h00_i32, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int32_t, mul_h01_i32, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int32_t, mul_h11_i32, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint32_t, mulu_h00_u32, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (uint32_t, mulu_h01_u32, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (uint32_t, mulu_h11_u32, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int32_t, mulsu_h00_i32, int16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int32_t, mulsu_h11_i32, int16x2_t, uint16x2_t)
/* b-series i16x4 (packed): RV64 single pmul.h.bNN; RV32 2x  */
CREATE_RVP_INTRINSIC (int16x4_t, pmul_b00_i16x4, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmul_b01_i16x4, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmul_b11_i16x4, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmulu_b00_u16x4, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmulu_b01_u16x4, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmulu_b11_u16x4, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmulsu_b00_i16x4, int8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmulsu_b11_i16x4, int8x8_t, uint8x8_t)
/* h-series i32x2 (packed): RV64 pmul.w.hNN; RV32 2x mul.hNN  */
CREATE_RVP_INTRINSIC (int32x2_t, pmul_h00_i32x2, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmul_h01_i32x2, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmul_h11_i32x2, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmulu_h00_u32x2, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmulu_h01_u32x2, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmulu_h11_u32x2, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmulsu_h00_i32x2, int16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmulsu_h11_i32x2, int16x4_t, uint16x4_t)
/* w-series i64.  */
#if __riscv_xlen == 32
RVP_OP_ATTRS int64_t
__riscv_mul_w00_i64 (int32x2_t __rs1, int32x2_t __rs2)
{
  return (int64_t) __rs1[0] * (int64_t) __rs2[0];
}

RVP_OP_ATTRS int64_t
__riscv_mul_w01_i64 (int32x2_t __rs1, int32x2_t __rs2)
{
  return (int64_t) __rs1[0] * (int64_t) __rs2[1];
}

RVP_OP_ATTRS int64_t
__riscv_mul_w11_i64 (int32x2_t __rs1, int32x2_t __rs2)
{
  return (int64_t) __rs1[1] * (int64_t) __rs2[1];
}

RVP_OP_ATTRS uint64_t
__riscv_mulu_w00_u64 (uint32x2_t __rs1, uint32x2_t __rs2)
{
  return (uint64_t) __rs1[0] * (uint64_t) __rs2[0];
}

RVP_OP_ATTRS uint64_t
__riscv_mulu_w01_u64 (uint32x2_t __rs1, uint32x2_t __rs2)
{
  return (uint64_t) __rs1[0] * (uint64_t) __rs2[1];
}

RVP_OP_ATTRS uint64_t
__riscv_mulu_w11_u64 (uint32x2_t __rs1, uint32x2_t __rs2)
{
  return (uint64_t) __rs1[1] * (uint64_t) __rs2[1];
}

RVP_OP_ATTRS int64_t
__riscv_mulsu_w00_i64 (int32x2_t __rs1, uint32x2_t __rs2)
{
  return (int64_t) ((uint64_t) (int64_t) __rs1[0] * __rs2[0]);
}

RVP_OP_ATTRS int64_t
__riscv_mulsu_w11_i64 (int32x2_t __rs1, uint32x2_t __rs2)
{
  return (int64_t) ((uint64_t) (int64_t) __rs1[1] * __rs2[1]);
}
#else
CREATE_RVP_INTRINSIC (int64_t, mul_w00_i64, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mul_w01_i64, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mul_w11_i64, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint64_t, mulu_w00_u64, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (uint64_t, mulu_w01_u64, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (uint64_t, mulu_w11_u64, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mulsu_w00_i64, int32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mulsu_w11_i64, int32x2_t, uint32x2_t)
#endif

/* Packed Multiply Parts Accumulate.  */
/* h-series i32 (both ISAs): RV32 macc.hNN/maccu.hNN/maccsu.hNN, RV64  */
/* pmacc.w.hNN/etc  */
CREATE_RVP_INTRINSIC(int32_t, macc_h00_i32, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, macc_h01_i32, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, macc_h11_i32, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(uint32_t, maccu_h00_u32, uint32_t, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC(uint32_t, maccu_h01_u32, uint32_t, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC(uint32_t, maccu_h11_u32, uint32_t, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC(int32_t, maccsu_h00_i32, int32_t, int16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC(int32_t, maccsu_h11_i32, int32_t, int16x2_t, uint16x2_t)
/* h-series i32x2 (packed): RV64 pmacc.w.hNN/etc, RV32 2x macc.hNN/etc  */
CREATE_RVP_INTRINSIC(int32x2_t, pmacc_h00_i32x2, int32x2_t, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmacc_h01_i32x2, int32x2_t, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmacc_h11_i32x2, int32x2_t, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(uint32x2_t, pmaccu_h00_u32x2, uint32x2_t, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC(uint32x2_t, pmaccu_h01_u32x2, uint32x2_t, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC(uint32x2_t, pmaccu_h11_u32x2, uint32x2_t, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmaccsu_h00_i32x2, int32x2_t, int16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmaccsu_h11_i32x2, int32x2_t, int16x4_t, uint16x4_t)
/* w-series i64.  */
#if __riscv_xlen == 32
RVP_OP_ATTRS int64_t
__riscv_macc_w00_i64 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  return (int64_t) ((uint64_t) __rd
		    + (uint64_t) __riscv_mul_w00_i64 (__rs1, __rs2));
}

RVP_OP_ATTRS int64_t
__riscv_macc_w01_i64 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  return (int64_t) ((uint64_t) __rd
		    + (uint64_t) __riscv_mul_w01_i64 (__rs1, __rs2));
}

RVP_OP_ATTRS int64_t
__riscv_macc_w11_i64 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  return (int64_t) ((uint64_t) __rd
		    + (uint64_t) __riscv_mul_w11_i64 (__rs1, __rs2));
}

RVP_OP_ATTRS uint64_t
__riscv_maccu_w00_u64 (uint64_t __rd, uint32x2_t __rs1,
			uint32x2_t __rs2)
{
  return __rd + __riscv_mulu_w00_u64 (__rs1, __rs2);
}

RVP_OP_ATTRS uint64_t
__riscv_maccu_w01_u64 (uint64_t __rd, uint32x2_t __rs1,
			uint32x2_t __rs2)
{
  return __rd + __riscv_mulu_w01_u64 (__rs1, __rs2);
}

RVP_OP_ATTRS uint64_t
__riscv_maccu_w11_u64 (uint64_t __rd, uint32x2_t __rs1,
			uint32x2_t __rs2)
{
  return __rd + __riscv_mulu_w11_u64 (__rs1, __rs2);
}

RVP_OP_ATTRS int64_t
__riscv_maccsu_w00_i64 (int64_t __rd, int32x2_t __rs1,
			 uint32x2_t __rs2)
{
  return (int64_t) ((uint64_t) __rd
		    + (uint64_t) __riscv_mulsu_w00_i64 (__rs1, __rs2));
}

RVP_OP_ATTRS int64_t
__riscv_maccsu_w11_i64 (int64_t __rd, int32x2_t __rs1,
			 uint32x2_t __rs2)
{
  return (int64_t) ((uint64_t) __rd
		    + (uint64_t) __riscv_mulsu_w11_i64 (__rs1, __rs2));
}
#else
CREATE_RVP_INTRINSIC(int64_t, macc_w00_i64, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, macc_w01_i64, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, macc_w11_i64, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(uint64_t, maccu_w00_u64, uint64_t, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC(uint64_t, maccu_w01_u64, uint64_t, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC(uint64_t, maccu_w11_u64, uint64_t, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC(int64_t, maccsu_w00_i64, int64_t, int32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC(int64_t, maccsu_w11_i64, int64_t, int32x2_t, uint32x2_t)
#endif

/* Packed Multiplication with Horizontal Addition.  */
/* 32-bit (both ISAs, single insn): pm4add.b/pm2add.h/pm2add.hx/etc  */
CREATE_RVP_INTRINSIC(int32_t, pm4add_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC(int32_t, pm2add_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pm2add_x_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(uint32_t, pm4addu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC(uint32_t, pm2addu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pmq2add_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pmqr2add_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pm2sadd_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pm2sadd_x_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pm2sub_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pm2sub_x_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pm4addsu_i8x4, int8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC(int32_t, pm2addsu_i16x2, int16x2_t, uint16x2_t)
/* 64-bit i32x2 (packed): RV64 single pm2add.h/etc; RV32 2x  */
CREATE_RVP_INTRINSIC(int32x2_t, pm4add_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2add_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2add_x_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(uint32x2_t, pm4addu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC(uint32x2_t, pm2addu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmq2add_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmqr2add_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2sadd_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2sadd_x_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2sub_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2sub_x_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm4addsu_i8x8, int8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2addsu_i16x4, int16x4_t, uint16x4_t)
/* 64-bit i64.  */
#if __riscv_xlen == 32
RVP_OP_ATTRS int64_t
__riscv_pm2add_i32x2 (int32x2_t __rs1, int32x2_t __rs2)
{
  int64_t __result = __riscv_mul_w00_i64 (__rs1, __rs2);
  return __riscv_macc_w11_i64 (__result, __rs1, __rs2);
}

RVP_OP_ATTRS int64_t
__riscv_pm2add_x_i32x2 (int32x2_t __rs1, int32x2_t __rs2)
{
  int64_t __result = __riscv_mul_w01_i64 (__rs1, __rs2);
  return __riscv_macc_w01_i64 (__result, __rs2, __rs1);
}

RVP_OP_ATTRS uint64_t
__riscv_pm2addu_u32x2 (uint32x2_t __rs1, uint32x2_t __rs2)
{
  uint64_t __result = __riscv_mulu_w00_u64 (__rs1, __rs2);
  return __riscv_maccu_w11_u64 (__result, __rs1, __rs2);
}

RVP_OP_ATTRS int64_t
__riscv_pmq2add_i32x2 (int32x2_t __rs1, int32x2_t __rs2)
{
  int64_t __result = __riscv_mqacc_w00_i64 (0, __rs1, __rs2);
  return __riscv_mqacc_w11_i64 (__result, __rs1, __rs2);
}

RVP_OP_ATTRS int64_t
__riscv_pm2sub_i32x2 (int32x2_t __rs1, int32x2_t __rs2)
{
  uint64_t __lhs = (uint64_t) __riscv_mul_w00_i64 (__rs1, __rs2);
  uint64_t __rhs = (uint64_t) __riscv_mul_w11_i64 (__rs1, __rs2);
  return (int64_t) (__lhs - __rhs);
}

RVP_OP_ATTRS int64_t
__riscv_pm2sub_x_i32x2 (int32x2_t __rs1, int32x2_t __rs2)
{
  uint64_t __lhs = (uint64_t) __riscv_mul_w01_i64 (__rs1, __rs2);
  uint64_t __rhs = (uint64_t) __riscv_mul_w01_i64 (__rs2, __rs1);
  return (int64_t) (__lhs - __rhs);
}

RVP_OP_ATTRS int64_t
__riscv_pm2addsu_i32x2 (int32x2_t __rs1, uint32x2_t __rs2)
{
  int64_t __result = __riscv_mulsu_w00_i64 (__rs1, __rs2);
  return __riscv_maccsu_w11_i64 (__result, __rs1, __rs2);
}

RVP_OP_ATTRS int64_t
__riscv_pmqr2add_i32x2 (int32x2_t __rs1, int32x2_t __rs2)
{
  int64_t __result = __riscv_mqracc_w00_i64 (0, __rs1, __rs2);
  return __riscv_mqracc_w11_i64 (__result, __rs1, __rs2);
}

RVP_OP_ATTRS int64_t
__riscv_pm4add_i16x4 (int16x4_t __rs1, int16x4_t __rs2)
{
  int16x2_t __rs1_lo
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 0);
  int16x2_t __rs2_lo
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs2, 0);
  int16x2_t __rs1_hi
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 1);
  int16x2_t __rs2_hi
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs2, 1);
  int64_t __result = __builtin_riscv_pm2wadd_i64 (__rs1_lo, __rs2_lo);
  return __builtin_riscv_pm2wadda_i64 (__result, __rs1_hi, __rs2_hi);
}

RVP_OP_ATTRS uint64_t
__riscv_pm4addu_u16x4 (uint16x4_t __rs1, uint16x4_t __rs2)
{
  uint16x2_t __rs1_lo
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs1, 0);
  uint16x2_t __rs2_lo
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 0);
  uint16x2_t __rs1_hi
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs1, 1);
  uint16x2_t __rs2_hi
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 1);
  uint64_t __result = __builtin_riscv_pm2waddu_u64 (__rs1_lo, __rs2_lo);
  return __builtin_riscv_pm2waddau_u64 (__result, __rs1_hi, __rs2_hi);
}

RVP_OP_ATTRS int64_t
__riscv_pm4addsu_i16x4 (int16x4_t __rs1, uint16x4_t __rs2)
{
  int16x2_t __rs1_lo
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 0);
  uint16x2_t __rs2_lo
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 0);
  int16x2_t __rs1_hi
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 1);
  uint16x2_t __rs2_hi
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 1);
  int64_t __result = __builtin_riscv_pm2waddsu_u64 (__rs1_lo, __rs2_lo);
  return __builtin_riscv_pm2waddasu_u64 (__result, __rs1_hi, __rs2_hi);
}
#else
CREATE_RVP_INTRINSIC(int64_t, pm2add_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pm2add_x_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(uint64_t, pm2addu_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pmq2add_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pm2sub_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pm2sub_x_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pm2addsu_i32x2, int32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pmqr2add_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pm4add_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(uint64_t, pm4addu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC(int64_t, pm4addsu_i16x4, int16x4_t, uint16x4_t)
#endif

/* Packed Multiplication with Horizontal Addition and Accumulate.  */
/* 32-bit (both ISAs, single insn, RMW): pm4adda.b/pm2adda.h/etc  */
CREATE_RVP_INTRINSIC(int32_t, pm4adda_i8x4, int32_t, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC(int32_t, pm2adda_i16x2, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pm2adda_x_i16x2, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(uint32_t, pm4addau_u8x4, uint32_t, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC(uint32_t, pm2addau_u16x2, uint32_t, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pmq2adda_i16x2, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pmqr2adda_i16x2, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pm2suba_i16x2, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pm2suba_x_i16x2, int32_t, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, pm4addasu_i8x4, int32_t, int8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC(int32_t, pm2addasu_i16x2, int32_t, int16x2_t, uint16x2_t)
/* 64-bit i32x2 (packed, RMW): RV64 single pm2adda.h/etc; RV32 2x  */
CREATE_RVP_INTRINSIC(int32x2_t, pm4adda_i8x8, int32x2_t, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2adda_i16x4, int32x2_t, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2adda_x_i16x4, int32x2_t, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(uint32x2_t, pm4addau_u8x8, uint32x2_t, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC(uint32x2_t, pm2addau_u16x4, uint32x2_t, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmq2adda_i16x4, int32x2_t, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmqr2adda_i16x4, int32x2_t, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2suba_i16x4, int32x2_t, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2suba_x_i16x4, int32x2_t, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm4addasu_i8x8, int32x2_t, int8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC(int32x2_t, pm2addasu_i16x4, int32x2_t, int16x4_t, uint16x4_t)
/* 64-bit i64.  */
#if __riscv_xlen == 32
RVP_OP_ATTRS int64_t
__riscv_pm2adda_i32x2 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  int64_t __result = __riscv_macc_w00_i64 (__rd, __rs1, __rs2);
  __result = __builtin_assoc_barrier (__result);
  return __riscv_macc_w11_i64 (__result, __rs1, __rs2);
}

RVP_OP_ATTRS int64_t
__riscv_pm2adda_x_i32x2 (int64_t __rd, int32x2_t __rs1,
			  int32x2_t __rs2)
{
  int64_t __result = __riscv_macc_w01_i64 (__rd, __rs1, __rs2);
  __result = __builtin_assoc_barrier (__result);
  return __riscv_macc_w01_i64 (__result, __rs2, __rs1);
}

RVP_OP_ATTRS uint64_t
__riscv_pm2addau_u32x2 (uint64_t __rd, uint32x2_t __rs1,
			 uint32x2_t __rs2)
{
  uint64_t __result = __riscv_maccu_w00_u64 (__rd, __rs1, __rs2);
  __result = __builtin_assoc_barrier (__result);
  return __riscv_maccu_w11_u64 (__result, __rs1, __rs2);
}

RVP_OP_ATTRS int64_t
__riscv_pmq2adda_i32x2 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  int64_t __result = __riscv_mqacc_w00_i64 (__rd, __rs1, __rs2);
  return __riscv_mqacc_w11_i64 (__result, __rs1, __rs2);
}

RVP_OP_ATTRS int64_t
__riscv_pm2suba_i32x2 (int64_t __rd, int32x2_t __rs1, int32x2_t __rs2)
{
  uint64_t __lhs = (uint64_t) __riscv_macc_w00_i64 (__rd, __rs1, __rs2);
  uint64_t __rhs = (uint64_t) __riscv_mul_w11_i64 (__rs1, __rs2);
  return (int64_t) (__lhs - __rhs);
}

RVP_OP_ATTRS int64_t
__riscv_pm2suba_x_i32x2 (int64_t __rd, int32x2_t __rs1,
			  int32x2_t __rs2)
{
  uint64_t __lhs = (uint64_t) __riscv_macc_w01_i64 (__rd, __rs1,
						      __rs2);
  uint64_t __rhs = (uint64_t) __riscv_mul_w01_i64 (__rs2, __rs1);
  return (int64_t) (__lhs - __rhs);
}

RVP_OP_ATTRS int64_t
__riscv_pm2addasu_i32x2 (int64_t __rd, int32x2_t __rs1,
			  uint32x2_t __rs2)
{
  int64_t __result = __riscv_maccsu_w00_i64 (__rd, __rs1, __rs2);
  __result = __builtin_assoc_barrier (__result);
  return __riscv_maccsu_w11_i64 (__result, __rs1, __rs2);
}

RVP_OP_ATTRS int64_t
__riscv_pmqr2adda_i32x2 (int64_t __rd, int32x2_t __rs1,
			  int32x2_t __rs2)
{
  int64_t __result = __riscv_mqracc_w00_i64 (__rd, __rs1, __rs2);
  return __riscv_mqracc_w11_i64 (__result, __rs1, __rs2);
}

RVP_OP_ATTRS int64_t
__riscv_pm4adda_i16x4 (int64_t __rd, int16x4_t __rs1, int16x4_t __rs2)
{
  int16x2_t __rs1_lo
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 0);
  int16x2_t __rs2_lo
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs2, 0);
  int16x2_t __rs1_hi
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 1);
  int16x2_t __rs2_hi
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs2, 1);
  int64_t __result
    = __builtin_riscv_pm2wadda_i64 (__rd, __rs1_lo, __rs2_lo);
  return __builtin_riscv_pm2wadda_i64 (__result, __rs1_hi, __rs2_hi);
}

RVP_OP_ATTRS uint64_t
__riscv_pm4addau_u16x4 (uint64_t __rd, uint16x4_t __rs1,
			 uint16x4_t __rs2)
{
  uint16x2_t __rs1_lo
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs1, 0);
  uint16x2_t __rs2_lo
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 0);
  uint16x2_t __rs1_hi
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs1, 1);
  uint16x2_t __rs2_hi
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 1);
  uint64_t __result
    = __builtin_riscv_pm2waddau_u64 (__rd, __rs1_lo, __rs2_lo);
  return __builtin_riscv_pm2waddau_u64 (__result, __rs1_hi, __rs2_hi);
}

RVP_OP_ATTRS int64_t
__riscv_pm4addasu_i16x4 (int64_t __rd, int16x4_t __rs1,
			  uint16x4_t __rs2)
{
  int16x2_t __rs1_lo
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 0);
  uint16x2_t __rs2_lo
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 0);
  int16x2_t __rs1_hi
    = RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, __rs1, 1);
  uint16x2_t __rs2_hi
    = RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, __rs2, 1);
  int64_t __result
    = __builtin_riscv_pm2waddasu_u64 (__rd, __rs1_lo, __rs2_lo);
  return __builtin_riscv_pm2waddasu_u64 (__result, __rs1_hi, __rs2_hi);
}
#else
CREATE_RVP_INTRINSIC(int64_t, pm2adda_i32x2, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pm2adda_x_i32x2, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(uint64_t, pm2addau_u32x2, uint64_t, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pmq2adda_i32x2, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pm2suba_i32x2, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pm2suba_x_i32x2, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pm2addasu_i32x2, int64_t, int32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pmqr2adda_i32x2, int64_t, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC(int64_t, pm4adda_i16x4, int64_t, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC(uint64_t, pm4addau_u16x4, uint64_t, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC(int64_t, pm4addasu_i16x4, int64_t, int16x4_t, uint16x4_t)
#endif

/* Packed Multiply High Parts.  */
/* b-series i16x2 (both ISAs, single insn): pmulh.h.bN/pmulhsu.h.bN  */
CREATE_RVP_INTRINSIC(int16x2_t, pmulh_b0_i16x2, int16x2_t, int8x4_t)
CREATE_RVP_INTRINSIC(int16x2_t, pmulh_b1_i16x2, int16x2_t, int8x4_t)
CREATE_RVP_INTRINSIC(int16x2_t, pmulhsu_b0_i16x2, int16x2_t, uint8x4_t)
CREATE_RVP_INTRINSIC(int16x2_t, pmulhsu_b1_i16x2, int16x2_t, uint8x4_t)
/* h-series i32 (scalar): RV32 mulh.hN/mulhsu.hN; RV64 pmulh.w.hN/etc  */
CREATE_RVP_INTRINSIC(int32_t, mulh_h0_i32, int32_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, mulh_h1_i32, int32_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, mulhsu_h0_i32, int32_t, uint16x2_t)
CREATE_RVP_INTRINSIC(int32_t, mulhsu_h1_i32, int32_t, uint16x2_t)
/* b-series i16x4 (packed): RV64 single pmulh.h.bN; RV32 2x  */
CREATE_RVP_INTRINSIC(int16x4_t, pmulh_b0_i16x4, int16x4_t, int8x8_t)
CREATE_RVP_INTRINSIC(int16x4_t, pmulh_b1_i16x4, int16x4_t, int8x8_t)
CREATE_RVP_INTRINSIC(int16x4_t, pmulhsu_b0_i16x4, int16x4_t, uint8x8_t)
CREATE_RVP_INTRINSIC(int16x4_t, pmulhsu_b1_i16x4, int16x4_t, uint8x8_t)
/* h-series i32x2 (packed): RV64 pmulh.w.hN; RV32 2x mulh.hN  */
CREATE_RVP_INTRINSIC(int32x2_t, pmulh_h0_i32x2, int32x2_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmulh_h1_i32x2, int32x2_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmulhsu_h0_i32x2, int32x2_t, uint16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmulhsu_h1_i32x2, int32x2_t, uint16x4_t)

/* Packed Multiply High Parts Accumulate.  */
/* b-series i16x2 (both ISAs, single RMW insn): pmhacc.h.bN/pmhaccsu.h.bN  */
CREATE_RVP_INTRINSIC(int16x2_t, pmhacc_b0_i16x2, int16x2_t, int16x2_t, int8x4_t)
CREATE_RVP_INTRINSIC(int16x2_t, pmhacc_b1_i16x2, int16x2_t, int16x2_t, int8x4_t)
CREATE_RVP_INTRINSIC(int16x2_t, pmhaccsu_b0_i16x2, int16x2_t, int16x2_t, uint8x4_t)
CREATE_RVP_INTRINSIC(int16x2_t, pmhaccsu_b1_i16x2, int16x2_t, int16x2_t, uint8x4_t)
/* h-series i32 (scalar, RMW): RV32 mhacc.hN/mhaccsu.hN; RV64 pmhacc.w.hN/etc  */
CREATE_RVP_INTRINSIC(int32_t, mhacc_h0_i32, int32_t, int32_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, mhacc_h1_i32, int32_t, int32_t, int16x2_t)
CREATE_RVP_INTRINSIC(int32_t, mhaccsu_h0_i32, int32_t, int32_t, uint16x2_t)
CREATE_RVP_INTRINSIC(int32_t, mhaccsu_h1_i32, int32_t, int32_t, uint16x2_t)
/* b-series i16x4 (packed, RMW): RV64 single pmhacc.h.bN; RV32 2x  */
CREATE_RVP_INTRINSIC(int16x4_t, pmhacc_b0_i16x4, int16x4_t, int16x4_t, int8x8_t)
CREATE_RVP_INTRINSIC(int16x4_t, pmhacc_b1_i16x4, int16x4_t, int16x4_t, int8x8_t)
CREATE_RVP_INTRINSIC(int16x4_t, pmhaccsu_b0_i16x4, int16x4_t, int16x4_t, uint8x8_t)
CREATE_RVP_INTRINSIC(int16x4_t, pmhaccsu_b1_i16x4, int16x4_t, int16x4_t, uint8x8_t)
/* h-series i32x2 (packed, RMW): RV64 pmhacc.w.hN; RV32 2x mhacc.hN  */
CREATE_RVP_INTRINSIC(int32x2_t, pmhacc_h0_i32x2, int32x2_t, int32x2_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmhacc_h1_i32x2, int32x2_t, int32x2_t, int16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmhaccsu_h0_i32x2, int32x2_t, int32x2_t, uint16x4_t)
CREATE_RVP_INTRINSIC(int32x2_t, pmhaccsu_h1_i32x2, int32x2_t, int32x2_t, uint16x4_t)

/* Packed Widening Multiply.  */
#if __riscv_xlen == 32
CREATE_RVP_INTRINSIC (int16x4_t, pwmul_i16x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwmul_i32x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwmulu_u16x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwmulu_u32x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pwmulsu_i16x4, int8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwmulsu_i32x2, int16x2_t, uint16x2_t)
#else
RVP_OP_ATTRS int16x4_t
__riscv_pwmul_i16x4 (int8x4_t __rs1, int8x4_t __rs2)
{
  int8x8_t __zipped = __builtin_riscv_pzip_i8x8 (__rs1, __rs2);
  return __builtin_riscv_pmul_b01_i16x4 (__zipped, __zipped);
}

RVP_OP_ATTRS int32x2_t
__riscv_pwmul_i32x2 (int16x2_t __rs1, int16x2_t __rs2)
{
  int16x4_t __zipped = __builtin_riscv_pzip_i16x4 (__rs1, __rs2);
  return __builtin_riscv_pmul_h01_i32x2 (__zipped, __zipped);
}

RVP_OP_ATTRS uint16x4_t
__riscv_pwmulu_u16x4 (uint8x4_t __rs1, uint8x4_t __rs2)
{
  uint8x8_t __zipped = __builtin_riscv_pzip_u8x8 (__rs1, __rs2);
  return __builtin_riscv_pmulu_b01_u16x4 (__zipped, __zipped);
}

RVP_OP_ATTRS uint32x2_t
__riscv_pwmulu_u32x2 (uint16x2_t __rs1, uint16x2_t __rs2)
{
  uint16x4_t __zipped = __builtin_riscv_pzip_u16x4 (__rs1, __rs2);
  return __builtin_riscv_pmulu_h01_u32x2 (__zipped, __zipped);
}

RVP_OP_ATTRS int16x4_t
__riscv_pwmulsu_i16x4 (int8x4_t __rs1, uint8x4_t __rs2)
{
  union
  {
    uint16x4_t __halves;
    int8x8_t __bytes;
  } __lhs;
  union
  {
    uint16x4_t __halves;
    uint8x8_t __bytes;
  } __rhs;

  __lhs.__halves
    = __builtin_riscv_pwcvtu_u16x4 ((uint8x4_t) __rs1);
  __rhs.__halves = __builtin_riscv_pwcvtu_u16x4 (__rs2);
  return __builtin_riscv_pmulsu_b00_i16x4 (__lhs.__bytes,
					   __rhs.__bytes);
}

RVP_OP_ATTRS int32x2_t
__riscv_pwmulsu_i32x2 (int16x2_t __rs1, uint16x2_t __rs2)
{
  union
  {
    uint32x2_t __words;
    int16x4_t __halves;
  } __lhs;
  union
  {
    uint32x2_t __words;
    uint16x4_t __halves;
  } __rhs;

  __lhs.__words
    = __builtin_riscv_pwcvtu_u32x2 ((uint16x2_t) __rs1);
  __rhs.__words = __builtin_riscv_pwcvtu_u32x2 (__rs2);
  return __builtin_riscv_pmulsu_h00_i32x2 (__lhs.__halves,
					   __rhs.__halves);
}
#endif

/* Packed Widening Multiply Accumulate.  */
#if __riscv_xlen == 32
CREATE_RVP_INTRINSIC (int32x2_t, pwmacc_i32x2, int32x2_t, int16x2_t,
		      int16x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwmaccu_u32x2, uint32x2_t, uint16x2_t,
		      uint16x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwmaccsu_i32x2, int32x2_t, int16x2_t,
		      uint16x2_t)
#else
RVP_OP_ATTRS int32x2_t
__riscv_pwmacc_i32x2 (int32x2_t __rd, int16x2_t __rs1,
		       int16x2_t __rs2)
{
  int16x4_t __zipped = __builtin_riscv_pzip_i16x4 (__rs1, __rs2);
  return __builtin_riscv_pmacc_h01_i32x2 (__rd, __zipped, __zipped);
}

RVP_OP_ATTRS uint32x2_t
__riscv_pwmaccu_u32x2 (uint32x2_t __rd, uint16x2_t __rs1,
			uint16x2_t __rs2)
{
  uint16x4_t __zipped = __builtin_riscv_pzip_u16x4 (__rs1, __rs2);
  return __builtin_riscv_pmaccu_h01_u32x2 (__rd, __zipped, __zipped);
}

RVP_OP_ATTRS int32x2_t
__riscv_pwmaccsu_i32x2 (int32x2_t __rd, int16x2_t __rs1,
			 uint16x2_t __rs2)
{
  union
  {
    uint32x2_t __words;
    int16x4_t __halves;
  } __lhs;
  union
  {
    uint32x2_t __words;
    uint16x4_t __halves;
  } __rhs;

  __lhs.__words
    = __builtin_riscv_pwcvtu_u32x2 ((uint16x2_t) __rs1);
  __rhs.__words = __builtin_riscv_pwcvtu_u32x2 (__rs2);
  return __builtin_riscv_pmaccsu_h00_i32x2 (__rd, __lhs.__halves,
					     __rhs.__halves);
}
#endif

/* Packed "Q-format" Multiply with Widening Accumulate.  */
#if __riscv_xlen == 32
CREATE_RVP_INTRINSIC (int32x2_t, pmqwacc_i32x2, int32x2_t, int16x2_t,
		      int16x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmqrwacc_i32x2, int32x2_t, int16x2_t,
		      int16x2_t)
#else
RVP_OP_ATTRS int32x2_t
__riscv_pmqwacc_i32x2 (int32x2_t __rd, int16x2_t __rs1,
			int16x2_t __rs2)
{
  int16x4_t __zipped = __builtin_riscv_pzip_i16x4 (__rs1, __rs2);
  return __builtin_riscv_pmqacc_h01_i32x2 (__rd, __zipped, __zipped);
}

RVP_OP_ATTRS int32x2_t
__riscv_pmqrwacc_i32x2 (int32x2_t __rd, int16x2_t __rs1,
			 int16x2_t __rs2)
{
  int16x4_t __zipped = __builtin_riscv_pzip_i16x4 (__rs1, __rs2);
  return __builtin_riscv_pmqracc_h01_i32x2 (__rd, __zipped, __zipped);
}
#endif

/* Packed Multiplication with Widening Horizontal Addition.  */
CREATE_RVP_INTRINSIC (int64_t, pm2wadd_i64, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int64_t, pm2wadd_x_i64, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint64_t, pm2waddu_u64, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int64_t, pm2wsub_i64, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int64_t, pm2wsub_x_i64, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int64_t, pm2waddsu_u64, int16x2_t, uint16x2_t)

/* Packed Multiplication with Widening Horizontal Addition and Accumulate.  */
CREATE_RVP_INTRINSIC (int64_t, pm2wadda_i64, int64_t, int16x2_t,
		      int16x2_t)
CREATE_RVP_INTRINSIC (int64_t, pm2wadda_x_i64, int64_t, int16x2_t,
		      int16x2_t)
CREATE_RVP_INTRINSIC (uint64_t, pm2waddau_u64, uint64_t, uint16x2_t,
		      uint16x2_t)
CREATE_RVP_INTRINSIC (int64_t, pm2wsuba_i64, int64_t, int16x2_t,
		      int16x2_t)
CREATE_RVP_INTRINSIC (int64_t, pm2wsuba_x_i64, int64_t, int16x2_t,
		      int16x2_t)
CREATE_RVP_INTRINSIC (int64_t, pm2waddasu_u64, int64_t, int16x2_t,
		      uint16x2_t)

/* Packed Logical Operations.  */
RVP_BINARY_OP (pand_i8x4, int8x4_t, &)
RVP_BINARY_OP (pand_u8x4, uint8x4_t, &)
RVP_BINARY_OP (pand_i16x2, int16x2_t, &)
RVP_BINARY_OP (pand_u16x2, uint16x2_t, &)
RVP_BINARY_OP (por_i8x4, int8x4_t, |)
RVP_BINARY_OP (por_u8x4, uint8x4_t, |)
RVP_BINARY_OP (por_i16x2, int16x2_t, |)
RVP_BINARY_OP (por_u16x2, uint16x2_t, |)
RVP_BINARY_OP (pxor_i8x4, int8x4_t, ^)
RVP_BINARY_OP (pxor_u8x4, uint8x4_t, ^)
RVP_BINARY_OP (pxor_i16x2, int16x2_t, ^)
RVP_BINARY_OP (pxor_u16x2, uint16x2_t, ^)
RVP_UNARY_OP (pnot_i8x4, int8x4_t, ~)
RVP_UNARY_OP (pnot_u8x4, uint8x4_t, ~)
RVP_UNARY_OP (pnot_i16x2, int16x2_t, ~)
RVP_UNARY_OP (pnot_u16x2, uint16x2_t, ~)
RVP_BINARY_OP (pand_i8x8, int8x8_t, &)
RVP_BINARY_OP (pand_u8x8, uint8x8_t, &)
RVP_BINARY_OP (pand_i16x4, int16x4_t, &)
RVP_BINARY_OP (pand_u16x4, uint16x4_t, &)
RVP_BINARY_OP (pand_i32x2, int32x2_t, &)
RVP_BINARY_OP (pand_u32x2, uint32x2_t, &)
RVP_BINARY_OP (por_i8x8, int8x8_t, |)
RVP_BINARY_OP (por_u8x8, uint8x8_t, |)
RVP_BINARY_OP (por_i16x4, int16x4_t, |)
RVP_BINARY_OP (por_u16x4, uint16x4_t, |)
RVP_BINARY_OP (por_i32x2, int32x2_t, |)
RVP_BINARY_OP (por_u32x2, uint32x2_t, |)
RVP_BINARY_OP (pxor_i8x8, int8x8_t, ^)
RVP_BINARY_OP (pxor_u8x8, uint8x8_t, ^)
RVP_BINARY_OP (pxor_i16x4, int16x4_t, ^)
RVP_BINARY_OP (pxor_u16x4, uint16x4_t, ^)
RVP_BINARY_OP (pxor_i32x2, int32x2_t, ^)
RVP_BINARY_OP (pxor_u32x2, uint32x2_t, ^)
RVP_UNARY_OP (pnot_i8x8, int8x8_t, ~)
RVP_UNARY_OP (pnot_u8x8, uint8x8_t, ~)
RVP_UNARY_OP (pnot_i16x4, int16x4_t, ~)
RVP_UNARY_OP (pnot_u16x4, uint16x4_t, ~)
RVP_UNARY_OP (pnot_i32x2, int32x2_t, ~)
RVP_UNARY_OP (pnot_u32x2, uint32x2_t, ~)

/* Packed Load.  */
RVP_LOAD (pld_i8x4, int8x4_t, int8_t, __rvp_unaligned_uint32_t)
RVP_LOAD (pld_u8x4, uint8x4_t, uint8_t, __rvp_unaligned_uint32_t)
RVP_LOAD (pld_i16x2, int16x2_t, int16_t, __rvp_unaligned_uint32_t)
RVP_LOAD (pld_u16x2, uint16x2_t, uint16_t, __rvp_unaligned_uint32_t)
RVP_LOAD (pld_i8x8, int8x8_t, int8_t, __rvp_unaligned_uint64_t)
RVP_LOAD (pld_u8x8, uint8x8_t, uint8_t, __rvp_unaligned_uint64_t)
RVP_LOAD (pld_i16x4, int16x4_t, int16_t, __rvp_unaligned_uint64_t)
RVP_LOAD (pld_u16x4, uint16x4_t, uint16_t, __rvp_unaligned_uint64_t)
RVP_LOAD (pld_i32x2, int32x2_t, int32_t, __rvp_unaligned_uint64_t)
RVP_LOAD (pld_u32x2, uint32x2_t, uint32_t, __rvp_unaligned_uint64_t)

/* Packed Store.  */
RVP_STORE (pst_i8x4, int8x4_t, int8_t, __rvp_unaligned_uint32_t)
RVP_STORE (pst_u8x4, uint8x4_t, uint8_t, __rvp_unaligned_uint32_t)
RVP_STORE (pst_i16x2, int16x2_t, int16_t, __rvp_unaligned_uint32_t)
RVP_STORE (pst_u16x2, uint16x2_t, uint16_t, __rvp_unaligned_uint32_t)
RVP_STORE (pst_i8x8, int8x8_t, int8_t, __rvp_unaligned_uint64_t)
RVP_STORE (pst_u8x8, uint8x8_t, uint8_t, __rvp_unaligned_uint64_t)
RVP_STORE (pst_i16x4, int16x4_t, int16_t, __rvp_unaligned_uint64_t)
RVP_STORE (pst_u16x4, uint16x4_t, uint16_t, __rvp_unaligned_uint64_t)
RVP_STORE (pst_i32x2, int32x2_t, int32_t, __rvp_unaligned_uint64_t)
RVP_STORE (pst_u32x2, uint32x2_t, uint32_t, __rvp_unaligned_uint64_t)

/* Packed Element Extract.  */
#define __riscv_pget_i8x4_i8(value, index) RVP_GET (value, index, 3)
#define __riscv_pget_u8x4_u8(value, index) RVP_GET (value, index, 3)
#define __riscv_pget_i16x2_i16(value, index) RVP_GET (value, index, 1)
#define __riscv_pget_u16x2_u16(value, index) RVP_GET (value, index, 1)
#define __riscv_pget_i8x8_i8(value, index) RVP_GET (value, index, 7)
#define __riscv_pget_u8x8_u8(value, index) RVP_GET (value, index, 7)
#define __riscv_pget_i16x4_i16(value, index) RVP_GET (value, index, 3)
#define __riscv_pget_u16x4_u16(value, index) RVP_GET (value, index, 3)
#define __riscv_pget_i32x2_i32(value, index) RVP_GET (value, index, 1)
#define __riscv_pget_u32x2_u32(value, index) RVP_GET (value, index, 1)

/* Packed Element Insert.  */
#define __riscv_pset_i8_i8x4(value, element, index)                         \
  RVP_SET (int8x4_t, value, element, index, 3)
#define __riscv_pset_u8_u8x4(value, element, index)                         \
  RVP_SET (uint8x4_t, value, element, index, 3)
#define __riscv_pset_i16_i16x2(value, element, index)                       \
  RVP_SET (int16x2_t, value, element, index, 1)
#define __riscv_pset_u16_u16x2(value, element, index)                       \
  RVP_SET (uint16x2_t, value, element, index, 1)
#define __riscv_pset_i8_i8x8(value, element, index)                         \
  RVP_SET (int8x8_t, value, element, index, 7)
#define __riscv_pset_u8_u8x8(value, element, index)                         \
  RVP_SET (uint8x8_t, value, element, index, 7)
#define __riscv_pset_i16_i16x4(value, element, index)                       \
  RVP_SET (int16x4_t, value, element, index, 3)
#define __riscv_pset_u16_u16x4(value, element, index)                       \
  RVP_SET (uint16x4_t, value, element, index, 3)
#define __riscv_pset_i32_i32x2(value, element, index)                       \
  RVP_SET (int32x2_t, value, element, index, 1)
#define __riscv_pset_u32_u32x2(value, element, index)                       \
  RVP_SET (uint32x2_t, value, element, index, 1)

/* Packed Element Join.  */
RVP_JOIN4 (pjoin4_i8x4, int8x4_t, int8_t)
RVP_JOIN4 (pjoin4_u8x4, uint8x4_t, uint8_t)
RVP_JOIN2 (pjoin2_i16x2, int16x2_t, int16_t)
RVP_JOIN2 (pjoin2_u16x2, uint16x2_t, uint16_t)
RVP_JOIN4 (pjoin4_i16x4, int16x4_t, int16_t)
RVP_JOIN4 (pjoin4_u16x4, uint16x4_t, uint16_t)
RVP_JOIN2 (pjoin2_i32x2, int32x2_t, int32_t)
RVP_JOIN2 (pjoin2_u32x2, uint32x2_t, uint32_t)

/* Packed Subvector Extract.  */
#define __riscv_pget_i8x8_i8x4(value, index)                               \
  RVP_SUBVECTOR_GET (int8x8_t, int8x4_t, value, index)
#define __riscv_pget_u8x8_u8x4(value, index)                               \
  RVP_SUBVECTOR_GET (uint8x8_t, uint8x4_t, value, index)
#define __riscv_pget_i16x4_i16x2(value, index)                             \
  RVP_SUBVECTOR_GET (int16x4_t, int16x2_t, value, index)
#define __riscv_pget_u16x4_u16x2(value, index)                             \
  RVP_SUBVECTOR_GET (uint16x4_t, uint16x2_t, value, index)

/* Packed Subvector Insert.  */
#define __riscv_pset_i8x4_i8x8(value, subvector, index)                    \
  RVP_SUBVECTOR_SET (int8x8_t, int8x4_t, value, subvector, index)
#define __riscv_pset_u8x4_u8x8(value, subvector, index)                    \
  RVP_SUBVECTOR_SET (uint8x8_t, uint8x4_t, value, subvector, index)
#define __riscv_pset_i16x2_i16x4(value, subvector, index)                  \
  RVP_SUBVECTOR_SET (int16x4_t, int16x2_t, value, subvector, index)
#define __riscv_pset_u16x2_u16x4(value, subvector, index)                  \
  RVP_SUBVECTOR_SET (uint16x4_t, uint16x2_t, value, subvector, index)

/* Packed Subvector Join.  */
RVP_SUBVECTOR_JOIN (pjoin2_i8x8, int8x8_t, int8x4_t)
RVP_SUBVECTOR_JOIN (pjoin2_u8x8, uint8x8_t, uint8x4_t)
RVP_SUBVECTOR_JOIN (pjoin2_i16x4, int16x4_t, int16x2_t)
RVP_SUBVECTOR_JOIN (pjoin2_u16x4, uint16x4_t, uint16x2_t)

/* Reinterpret casts between packed and scalar types.  */
RVP_REINTERPRET (preinterpret_u8x4_u32, uint32_t, uint8x4_t)
RVP_REINTERPRET (preinterpret_u16x2_u32, uint32_t, uint16x2_t)
RVP_REINTERPRET (preinterpret_i8x4_u32, uint32_t, int8x4_t)
RVP_REINTERPRET (preinterpret_i16x2_u32, uint32_t, int16x2_t)
RVP_REINTERPRET (preinterpret_u8x4_i32, int32_t, uint8x4_t)
RVP_REINTERPRET (preinterpret_u16x2_i32, int32_t, uint16x2_t)
RVP_REINTERPRET (preinterpret_i8x4_i32, int32_t, int8x4_t)
RVP_REINTERPRET (preinterpret_i16x2_i32, int32_t, int16x2_t)
RVP_REINTERPRET (preinterpret_u32_u8x4, uint8x4_t, uint32_t)
RVP_REINTERPRET (preinterpret_u32_u16x2, uint16x2_t, uint32_t)
RVP_REINTERPRET (preinterpret_u32_i8x4, int8x4_t, uint32_t)
RVP_REINTERPRET (preinterpret_u32_i16x2, int16x2_t, uint32_t)
RVP_REINTERPRET (preinterpret_i32_u8x4, uint8x4_t, int32_t)
RVP_REINTERPRET (preinterpret_i32_u16x2, uint16x2_t, int32_t)
RVP_REINTERPRET (preinterpret_i32_i8x4, int8x4_t, int32_t)
RVP_REINTERPRET (preinterpret_i32_i16x2, int16x2_t, int32_t)

RVP_REINTERPRET (preinterpret_u8x8_u64, uint64_t, uint8x8_t)
RVP_REINTERPRET (preinterpret_u16x4_u64, uint64_t, uint16x4_t)
RVP_REINTERPRET (preinterpret_u32x2_u64, uint64_t, uint32x2_t)
RVP_REINTERPRET (preinterpret_i8x8_u64, uint64_t, int8x8_t)
RVP_REINTERPRET (preinterpret_i16x4_u64, uint64_t, int16x4_t)
RVP_REINTERPRET (preinterpret_i32x2_u64, uint64_t, int32x2_t)
RVP_REINTERPRET (preinterpret_u8x8_i64, int64_t, uint8x8_t)
RVP_REINTERPRET (preinterpret_u16x4_i64, int64_t, uint16x4_t)
RVP_REINTERPRET (preinterpret_u32x2_i64, int64_t, uint32x2_t)
RVP_REINTERPRET (preinterpret_i8x8_i64, int64_t, int8x8_t)
RVP_REINTERPRET (preinterpret_i16x4_i64, int64_t, int16x4_t)
RVP_REINTERPRET (preinterpret_i32x2_i64, int64_t, int32x2_t)
RVP_REINTERPRET (preinterpret_u64_u8x8, uint8x8_t, uint64_t)
RVP_REINTERPRET (preinterpret_u64_u16x4, uint16x4_t, uint64_t)
RVP_REINTERPRET (preinterpret_u64_u32x2, uint32x2_t, uint64_t)
RVP_REINTERPRET (preinterpret_u64_i8x8, int8x8_t, uint64_t)
RVP_REINTERPRET (preinterpret_u64_i16x4, int16x4_t, uint64_t)
RVP_REINTERPRET (preinterpret_u64_i32x2, int32x2_t, uint64_t)
RVP_REINTERPRET (preinterpret_i64_u8x8, uint8x8_t, int64_t)
RVP_REINTERPRET (preinterpret_i64_u16x4, uint16x4_t, int64_t)
RVP_REINTERPRET (preinterpret_i64_u32x2, uint32x2_t, int64_t)
RVP_REINTERPRET (preinterpret_i64_i8x8, int8x8_t, int64_t)
RVP_REINTERPRET (preinterpret_i64_i16x4, int16x4_t, int64_t)
RVP_REINTERPRET (preinterpret_i64_i32x2, int32x2_t, int64_t)

/* Reinterpret casts between packed types.  */
RVP_REINTERPRET (preinterpret_i8x4_u8x4, uint8x4_t, int8x4_t)
RVP_REINTERPRET (preinterpret_u16x2_u8x4, uint8x4_t, uint16x2_t)
RVP_REINTERPRET (preinterpret_i16x2_u8x4, uint8x4_t, int16x2_t)
RVP_REINTERPRET (preinterpret_u8x4_i8x4, int8x4_t, uint8x4_t)
RVP_REINTERPRET (preinterpret_u16x2_i8x4, int8x4_t, uint16x2_t)
RVP_REINTERPRET (preinterpret_i16x2_i8x4, int8x4_t, int16x2_t)
RVP_REINTERPRET (preinterpret_u8x4_u16x2, uint16x2_t, uint8x4_t)
RVP_REINTERPRET (preinterpret_i8x4_u16x2, uint16x2_t, int8x4_t)
RVP_REINTERPRET (preinterpret_i16x2_u16x2, uint16x2_t, int16x2_t)
RVP_REINTERPRET (preinterpret_u8x4_i16x2, int16x2_t, uint8x4_t)
RVP_REINTERPRET (preinterpret_i8x4_i16x2, int16x2_t, int8x4_t)
RVP_REINTERPRET (preinterpret_u16x2_i16x2, int16x2_t, uint16x2_t)

RVP_REINTERPRET (preinterpret_i8x8_u8x8, uint8x8_t, int8x8_t)
RVP_REINTERPRET (preinterpret_u16x4_u8x8, uint8x8_t, uint16x4_t)
RVP_REINTERPRET (preinterpret_i16x4_u8x8, uint8x8_t, int16x4_t)
RVP_REINTERPRET (preinterpret_u32x2_u8x8, uint8x8_t, uint32x2_t)
RVP_REINTERPRET (preinterpret_i32x2_u8x8, uint8x8_t, int32x2_t)
RVP_REINTERPRET (preinterpret_u8x8_i8x8, int8x8_t, uint8x8_t)
RVP_REINTERPRET (preinterpret_u16x4_i8x8, int8x8_t, uint16x4_t)
RVP_REINTERPRET (preinterpret_i16x4_i8x8, int8x8_t, int16x4_t)
RVP_REINTERPRET (preinterpret_u32x2_i8x8, int8x8_t, uint32x2_t)
RVP_REINTERPRET (preinterpret_i32x2_i8x8, int8x8_t, int32x2_t)
RVP_REINTERPRET (preinterpret_u8x8_u16x4, uint16x4_t, uint8x8_t)
RVP_REINTERPRET (preinterpret_i8x8_u16x4, uint16x4_t, int8x8_t)
RVP_REINTERPRET (preinterpret_i16x4_u16x4, uint16x4_t, int16x4_t)
RVP_REINTERPRET (preinterpret_u32x2_u16x4, uint16x4_t, uint32x2_t)
RVP_REINTERPRET (preinterpret_i32x2_u16x4, uint16x4_t, int32x2_t)
RVP_REINTERPRET (preinterpret_u8x8_i16x4, int16x4_t, uint8x8_t)
RVP_REINTERPRET (preinterpret_i8x8_i16x4, int16x4_t, int8x8_t)
RVP_REINTERPRET (preinterpret_u16x4_i16x4, int16x4_t, uint16x4_t)
RVP_REINTERPRET (preinterpret_u32x2_i16x4, int16x4_t, uint32x2_t)
RVP_REINTERPRET (preinterpret_i32x2_i16x4, int16x4_t, int32x2_t)
RVP_REINTERPRET (preinterpret_u8x8_u32x2, uint32x2_t, uint8x8_t)
RVP_REINTERPRET (preinterpret_i8x8_u32x2, uint32x2_t, int8x8_t)
RVP_REINTERPRET (preinterpret_u16x4_u32x2, uint32x2_t, uint16x4_t)
RVP_REINTERPRET (preinterpret_i16x4_u32x2, uint32x2_t, int16x4_t)
RVP_REINTERPRET (preinterpret_i32x2_u32x2, uint32x2_t, int32x2_t)
RVP_REINTERPRET (preinterpret_u8x8_i32x2, int32x2_t, uint8x8_t)
RVP_REINTERPRET (preinterpret_i8x8_i32x2, int32x2_t, int8x8_t)
RVP_REINTERPRET (preinterpret_u16x4_i32x2, int32x2_t, uint16x4_t)
RVP_REINTERPRET (preinterpret_i16x4_i32x2, int32x2_t, int16x4_t)
RVP_REINTERPRET (preinterpret_u32x2_i32x2, int32x2_t, uint32x2_t)

/* The scalar SLX and SRX intrinsics operate on one XLEN-bit register.  Split
   64-bit values into two halves when XLEN is 32 so that slides across the
   register-pair boundary retain the same concatenation semantics.  */
#if __riscv_xlen == 32
RVP_OP_ATTRS uint64_t
__rvp_slx_64 (uint64_t __rd, uint64_t __rs1, unsigned int __shamt)
{
  uint32_t __rd_lo = (uint32_t) __rd;
  uint32_t __rd_hi = (uint32_t) (__rd >> 32);
  uint32_t __rs1_lo = (uint32_t) __rs1;
  uint32_t __rs1_hi = (uint32_t) (__rs1 >> 32);
  uint32_t __result_lo;
  uint32_t __result_hi;

  __shamt &= 63;
  if (__shamt & 32)
    {
      __shamt &= 31;
      __result_lo = __riscv_slx_32 (__rs1_hi, __rs1_lo, __shamt);
      __result_hi = __riscv_slx_32 (__rd_lo, __rs1_hi, __shamt);
    }
  else
    {
      __result_lo = __riscv_slx_32 (__rd_lo, __rs1_hi, __shamt);
      __result_hi = __riscv_slx_32 (__rd_hi, __rd_lo, __shamt);
    }

  return ((uint64_t) __result_hi << 32) | __result_lo;
}

RVP_OP_ATTRS uint64_t
__rvp_srx_64 (uint64_t __rd, uint64_t __rs1, unsigned int __shamt)
{
  uint32_t __rd_lo = (uint32_t) __rd;
  uint32_t __rd_hi = (uint32_t) (__rd >> 32);
  uint32_t __rs1_lo = (uint32_t) __rs1;
  uint32_t __rs1_hi = (uint32_t) (__rs1 >> 32);
  uint32_t __result_lo;
  uint32_t __result_hi;

  __shamt &= 63;
  if (__shamt & 32)
    {
      __shamt &= 31;
      __result_lo = __riscv_srx_32 (__rd_hi, __rs1_lo, __shamt);
      __result_hi = __riscv_srx_32 (__rs1_lo, __rs1_hi, __shamt);
    }
  else
    {
      __result_lo = __riscv_srx_32 (__rd_lo, __rd_hi, __shamt);
      __result_hi = __riscv_srx_32 (__rd_hi, __rs1_lo, __shamt);
    }

  return ((uint64_t) __result_hi << 32) | __result_lo;
}

#define RVP_SLX_64 __rvp_slx_64
#define RVP_SRX_64 __rvp_srx_64
#else
#define RVP_SLX_64 __riscv_slx_64
#define RVP_SRX_64 __riscv_srx_64
#endif

/* Packed slide 1 up and down.  */
RVP_SLIDE1 (i8x4, int8x4_t, int8_t, uint8_t,
	    __riscv_preinterpret_i8x4_u32,
	    __riscv_preinterpret_u32_i8x4, uint32_t, 32, 8,
	    __riscv_slx_32, __riscv_srx_32)
RVP_SLIDE1 (u8x4, uint8x4_t, uint8_t, uint8_t,
	    __riscv_preinterpret_u8x4_u32,
	    __riscv_preinterpret_u32_u8x4, uint32_t, 32, 8,
	    __riscv_slx_32, __riscv_srx_32)
RVP_SLIDE1_PAIR (i16x2, int16x2_t, int16_t,
		 __riscv_preinterpret_i32_i16x2,
		 __riscv_ppaire_i16x2, __riscv_ppairoe_i16x2)
RVP_SLIDE1_PAIR (u16x2, uint16x2_t, uint16_t,
		 __riscv_preinterpret_u32_u16x2,
		 __riscv_ppaire_u16x2, __riscv_ppairoe_u16x2)
RVP_SLIDE1 (i8x8, int8x8_t, int8_t, uint8_t,
	    __riscv_preinterpret_i8x8_u64,
	    __riscv_preinterpret_u64_i8x8, uint64_t, 64, 8,
	    RVP_SLX_64, RVP_SRX_64)
RVP_SLIDE1 (u8x8, uint8x8_t, uint8_t, uint8_t,
	    __riscv_preinterpret_u8x8_u64,
	    __riscv_preinterpret_u64_u8x8, uint64_t, 64, 8,
	    RVP_SLX_64, RVP_SRX_64)
RVP_SLIDE1 (i16x4, int16x4_t, int16_t, uint16_t,
	    __riscv_preinterpret_i16x4_u64,
	    __riscv_preinterpret_u64_i16x4, uint64_t, 64, 16,
	    RVP_SLX_64, RVP_SRX_64)
RVP_SLIDE1 (u16x4, uint16x4_t, uint16_t, uint16_t,
	    __riscv_preinterpret_u16x4_u64,
	    __riscv_preinterpret_u64_u16x4, uint64_t, 64, 16,
	    RVP_SLX_64, RVP_SRX_64)
#if __riscv_xlen == 32
RVP_SLIDE1_PAIR_INIT (i32x2, int32x2_t, int32_t,
		      __riscv_ppaire_i32x2, __riscv_ppairoe_i32x2)
RVP_SLIDE1_PAIR_INIT (u32x2, uint32x2_t, uint32_t,
		      __riscv_ppaire_u32x2, __riscv_ppairoe_u32x2)
#else
RVP_SLIDE1_PAIR (i32x2, int32x2_t, int32_t,
		 __riscv_preinterpret_i64_i32x2,
		 __riscv_ppaire_i32x2, __riscv_ppairoe_i32x2)
RVP_SLIDE1_PAIR (u32x2, uint32x2_t, uint32_t,
		 __riscv_preinterpret_u64_u32x2,
		 __riscv_ppaire_u32x2, __riscv_ppairoe_u32x2)
#endif

/* Packed slide up and down by a run-time element count.  Multiplying the
   count by the element width leaves the instruction's masked shift amount
   equivalent to masking the count by the number of elements.  */
RVP_SLIDE (i8x4, int8x4_t, __riscv_preinterpret_i8x4_u32,
	   __riscv_preinterpret_u32_i8x4, 8,
	   __riscv_slx_32, __riscv_srx_32)
RVP_SLIDE (u8x4, uint8x4_t, __riscv_preinterpret_u8x4_u32,
	   __riscv_preinterpret_u32_u8x4, 8,
	   __riscv_slx_32, __riscv_srx_32)
RVP_SLIDE (i16x2, int16x2_t, __riscv_preinterpret_i16x2_u32,
	   __riscv_preinterpret_u32_i16x2, 16,
	   __riscv_slx_32, __riscv_srx_32)
RVP_SLIDE (u16x2, uint16x2_t, __riscv_preinterpret_u16x2_u32,
	   __riscv_preinterpret_u32_u16x2, 16,
	   __riscv_slx_32, __riscv_srx_32)
RVP_SLIDE (i8x8, int8x8_t, __riscv_preinterpret_i8x8_u64,
	   __riscv_preinterpret_u64_i8x8, 8, RVP_SLX_64, RVP_SRX_64)
RVP_SLIDE (u8x8, uint8x8_t, __riscv_preinterpret_u8x8_u64,
	   __riscv_preinterpret_u64_u8x8, 8, RVP_SLX_64, RVP_SRX_64)
RVP_SLIDE (i16x4, int16x4_t, __riscv_preinterpret_i16x4_u64,
	   __riscv_preinterpret_u64_i16x4, 16, RVP_SLX_64, RVP_SRX_64)
RVP_SLIDE (u16x4, uint16x4_t, __riscv_preinterpret_u16x4_u64,
	   __riscv_preinterpret_u64_u16x4, 16, RVP_SLX_64, RVP_SRX_64)
RVP_SLIDE (i32x2, int32x2_t, __riscv_preinterpret_i32x2_u64,
	   __riscv_preinterpret_u64_i32x2, 32, RVP_SLX_64, RVP_SRX_64)
RVP_SLIDE (u32x2, uint32x2_t, __riscv_preinterpret_u32x2_u64,
	   __riscv_preinterpret_u64_u32x2, 32, RVP_SLX_64, RVP_SRX_64)

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __riscv_p */
#endif /* __RISCV_PACKED_SIMD_H */
