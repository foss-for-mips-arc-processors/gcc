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

#ifdef __cplusplus
extern "C" {
#endif

#if __riscv_xlen == 32
CREATE_RVP_INTRINSIC_ALIAS (uint32_t, abs_u32, abs, int32_t)
CREATE_RVP_INTRINSIC_ALIAS (unsigned, cls_32, cls, int32_t)
CREATE_RVP_INTRINSIC_ALIAS (uint32_t, rev_32, rev, uint32_t)
#else
CREATE_RVP_INTRINSIC_ALIAS (uint32_t, abs_u32, absw, int32_t)
CREATE_RVP_INTRINSIC_ALIAS (uint64_t, abs_u64, abs, int64_t)
CREATE_RVP_INTRINSIC_ALIAS (unsigned, cls_32, clsw, int32_t)
CREATE_RVP_INTRINSIC_ALIAS (unsigned, cls_64, cls, int64_t)
CREATE_RVP_INTRINSIC_ALIAS (uint64_t, rev_64, rev, uint64_t)
CREATE_RVP_INTRINSIC_ALIAS (uint64_t, rev16_64, rev16, uint64_t)
CREATE_RVP_INTRINSIC_ALIAS (int64_t, sha_i64, sha, int64_t, int)
CREATE_RVP_INTRINSIC_ALIAS (int64_t, shar_i64, shar, int64_t, int)
CREATE_RVP_INTRINSIC_ALIAS (uint64_t, shl_u64, shl, uint64_t, int)
CREATE_RVP_INTRINSIC_ALIAS (uint64_t, shlr_u64, shlr, uint64_t, int)
#endif

/* Packed Splat.  */
CREATE_RVP_INTRINSIC (uint8x4_t, pmv_s_u8x4, uint8_t)
CREATE_RVP_INTRINSIC (int8x4_t, pmv_s_i8x4, int8_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmv_s_u16x2, uint16_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmv_s_i16x2, int16_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmv_s_u8x8, uint8_t)
CREATE_RVP_INTRINSIC (int8x8_t, pmv_s_i8x8, int8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmv_s_u16x4, uint16_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmv_s_i16x4, int16_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmv_s_u32x2, uint32_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmv_s_i32x2, int32_t)

/* Packed Addition and Subtraction.  */
CREATE_RVP_INTRINSIC (int8x4_t, padd_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, padd_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, padd_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, padd_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int8x4_t, psub_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, psub_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, psub_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, psub_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int8x4_t, pneg_i8x4, int8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pneg_i16x2, int16x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, padd_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, padd_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, padd_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, padd_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, padd_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, padd_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, psub_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, psub_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, psub_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, psub_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, psub_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, psub_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, pneg_i8x8, int8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pneg_i16x4, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pneg_i32x2, int32x2_t)

/* Packed Addition with Scalar.  */
CREATE_RVP_INTRINSIC (uint8x4_t, padd_s_u8x4, uint8x4_t, uint8_t)
CREATE_RVP_INTRINSIC (int8x4_t, padd_s_i8x4, int8x4_t, int8_t)
CREATE_RVP_INTRINSIC (uint16x2_t, padd_s_u16x2, uint16x2_t, uint16_t)
CREATE_RVP_INTRINSIC (int16x2_t, padd_s_i16x2, int16x2_t, int16_t)
CREATE_RVP_INTRINSIC (uint8x8_t, padd_s_u8x8, uint8x8_t, uint8_t)
CREATE_RVP_INTRINSIC (int8x8_t, padd_s_i8x8, int8x8_t, int8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, padd_s_u16x4, uint16x4_t, uint16_t)
CREATE_RVP_INTRINSIC (int16x4_t, padd_s_i16x4, int16x4_t, int16_t)
CREATE_RVP_INTRINSIC (uint32x2_t, padd_s_u32x2, uint32x2_t, uint32_t)
CREATE_RVP_INTRINSIC (int32x2_t, padd_s_i32x2, int32x2_t, int32_t)

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
#if __riscv_xlen == 64
/* RV64 only: i32x2 exchanged saturating/averaging variants use the .wx  */
/* instructions.  On RV32 these have no equivalent cross-word instruction. */
CREATE_RVP_INTRINSIC (int32x2_t, psas_x_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pssa_x_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, paas_x_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pasa_x_i32x2, int32x2_t, int32x2_t)
#endif

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

/* TODO(difficult): Packed Absolute Difference Sum  */

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
/* TODO(difficult): RV32 i64 accumulate variants need wadda/waddau  */
/* (unimplemented); these six i64 intrinsics are RV64-only for now.  */
#if __riscv_xlen == 64
CREATE_RVP_INTRINSIC (int64_t, predsum_i8x8_i64, int8x8_t, int64_t)
CREATE_RVP_INTRINSIC (uint64_t, predsumu_u8x8_u64, uint8x8_t, uint64_t)
CREATE_RVP_INTRINSIC (int64_t, predsum_i16x4_i64, int16x4_t, int64_t)
CREATE_RVP_INTRINSIC (uint64_t, predsumu_u16x4_u64, uint16x4_t, uint64_t)
CREATE_RVP_INTRINSIC (int64_t, predsum_i32x2_i64, int32x2_t, int64_t)
CREATE_RVP_INTRINSIC (uint64_t, predsumu_u32x2_u64, uint32x2_t, uint64_t)
#endif

/* Packed Minimum and Maximum.  */
CREATE_RVP_INTRINSIC (int8x4_t, pmin_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmin_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pminu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pminu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int8x4_t, pmax_i8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmax_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmaxu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmaxu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, pmin_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmin_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmin_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pminu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pminu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pminu_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int8x8_t, pmax_i8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmax_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmax_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmaxu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmaxu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmaxu_u32x2, uint32x2_t, uint32x2_t)

/* Packed Comparison.  */
CREATE_RVP_INTRINSIC (uint8x4_t, pmseq_i8x4_u8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmseq_u8x4_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmslt_u8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmsgt_u8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmsge_u8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmsle_u8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmsltu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmsgtu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmsgeu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmsleu_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmsne_i8x4_u8x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (uint8x4_t, pmsne_u8x4_u8x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmseq_i16x2_u16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmseq_u16x2_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmslt_u16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmsgt_u16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmsge_u16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmsle_u16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmsltu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmsgtu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmsgeu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmsleu_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmsne_i16x2_u16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x2_t, pmsne_u16x2_u16x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmseq_i8x8_u8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmseq_u8x8_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmslt_u8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmsgt_u8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmsge_u8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmsle_u8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmsltu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmsgtu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmsgeu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmsleu_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmsne_i8x8_u8x8, int8x8_t, int8x8_t)
CREATE_RVP_INTRINSIC (uint8x8_t, pmsne_u8x8_u8x8, uint8x8_t, uint8x8_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmseq_i16x4_u16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmseq_u16x4_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmslt_u16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmsgt_u16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmsge_u16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmsle_u16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmsltu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmsgtu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmsgeu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmsleu_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmsne_i16x4_u16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pmsne_u16x4_u16x4, uint16x4_t, uint16x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmseq_i32x2_u32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmseq_u32x2_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmslt_u32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmsgt_u32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmsge_u32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmsle_u32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmsltu_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmsgtu_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmsgeu_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmsleu_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmsne_i32x2_u32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmsne_u32x2_u32x2, uint32x2_t, uint32x2_t)

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
CREATE_RVP_INTRINSIC (uint8x4_t, psll_s_u8x4, uint8x4_t, unsigned)
CREATE_RVP_INTRINSIC (int8x4_t, psll_s_i8x4, int8x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint16x2_t, psll_s_u16x2, uint16x2_t, unsigned)
CREATE_RVP_INTRINSIC (int16x2_t, psll_s_i16x2, int16x2_t, unsigned)
CREATE_RVP_INTRINSIC (uint8x4_t, psrl_s_u8x4, uint8x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint16x2_t, psrl_s_u16x2, uint16x2_t, unsigned)
CREATE_RVP_INTRINSIC (int8x4_t, psra_s_i8x4, int8x4_t, unsigned)
CREATE_RVP_INTRINSIC (int16x2_t, psra_s_i16x2, int16x2_t, unsigned)
CREATE_RVP_INTRINSIC (uint8x8_t, psll_s_u8x8, uint8x8_t, unsigned)
CREATE_RVP_INTRINSIC (int8x8_t, psll_s_i8x8, int8x8_t, unsigned)
CREATE_RVP_INTRINSIC (uint16x4_t, psll_s_u16x4, uint16x4_t, unsigned)
CREATE_RVP_INTRINSIC (int16x4_t, psll_s_i16x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint32x2_t, psll_s_u32x2, uint32x2_t, unsigned)
CREATE_RVP_INTRINSIC (int32x2_t, psll_s_i32x2, int32x2_t, unsigned)
CREATE_RVP_INTRINSIC (uint8x8_t, psrl_s_u8x8, uint8x8_t, unsigned)
CREATE_RVP_INTRINSIC (uint16x4_t, psrl_s_u16x4, uint16x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint32x2_t, psrl_s_u32x2, uint32x2_t, unsigned)
CREATE_RVP_INTRINSIC (int8x8_t, psra_s_i8x8, int8x8_t, unsigned)
CREATE_RVP_INTRINSIC (int16x4_t, psra_s_i16x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (int32x2_t, psra_s_i32x2, int32x2_t, unsigned)

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

/* Packed Pair 32x2 is RV64-only: the RV32 form would need to compose the.  */
/* result from both source register pairs' half registers, which a plain "mv"
 */
/* (the spec's RV32 mapping) cannot express.  TODO: implement the RV32 form  */
/* with paired emit_move when needed.  */
#if __riscv_xlen == 64
CREATE_RVP_INTRINSIC (uint32x2_t, ppaire_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, ppaire_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, ppaireo_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, ppaireo_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, ppairoe_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, ppairoe_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, ppairo_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, ppairo_i32x2, int32x2_t, int32x2_t)
#endif

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

/* Packed Widening Addition and Subtraction (RV32-only; RV64 TODO).  */
#if __riscv_xlen == 32
CREATE_RVP_INTRINSIC (int16x4_t, pwadd_i16x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwadd_i32x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwaddu_u16x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwaddu_u32x2, uint16x2_t, uint16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pwsub_i16x4, int8x4_t, int8x4_t)
CREATE_RVP_INTRINSIC (int32x2_t, pwsub_i32x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (uint16x4_t, pwsubu_u16x4, uint8x4_t, uint8x4_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pwsubu_u32x2, uint16x2_t, uint16x2_t)

/* Packed Widening Addition and Subtraction Accumulate (RV32-only; RV64 TODO)
 */
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

/* Packed Widening Shift (RV32-only; RV64 TODO).  */
CREATE_RVP_INTRINSIC (uint16x4_t, pwsll_s_u16x4, uint8x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint32x2_t, pwsll_s_u32x2, uint16x2_t, unsigned)
CREATE_RVP_INTRINSIC (int16x4_t, pwsla_s_i16x4, int8x4_t, unsigned)
CREATE_RVP_INTRINSIC (int32x2_t, pwsla_s_i32x2, int16x2_t, unsigned)

/* Packed Narrowing Shift (RV32-only; RV64 TODO).  */
CREATE_RVP_INTRINSIC (uint8x4_t, pnsrl_s_u8x4, uint16x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint16x2_t, pnsrl_s_u16x2, uint32x2_t, unsigned)
CREATE_RVP_INTRINSIC (int8x4_t, pnsra_s_i8x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (int16x2_t, pnsra_s_i16x2, int32x2_t, unsigned)
CREATE_RVP_INTRINSIC (int8x4_t, pnsrar_s_i8x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (int16x2_t, pnsrar_s_i16x2, int32x2_t, unsigned)

/* Packed Narrowing Clip (RV32-only; RV64 TODO).  */
CREATE_RVP_INTRINSIC (uint8x4_t, pnclipu_s_u8x4, uint16x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint16x2_t, pnclipu_s_u16x2, uint32x2_t, unsigned)
CREATE_RVP_INTRINSIC (uint8x4_t, pnclipru_s_u8x4, uint16x4_t, unsigned)
CREATE_RVP_INTRINSIC (uint16x2_t, pnclipru_s_u16x2, uint32x2_t, unsigned)
CREATE_RVP_INTRINSIC (int8x4_t, pnclip_s_i8x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (int16x2_t, pnclip_s_i16x2, int32x2_t, unsigned)
CREATE_RVP_INTRINSIC (int8x4_t, pnclipr_s_i8x4, int16x4_t, unsigned)
CREATE_RVP_INTRINSIC (int16x2_t, pnclipr_s_i16x2, int32x2_t, unsigned)
#endif

/* Packed Narrowing Clip Pair (TODO).  */

/* Packed Reverse (TODO).  */

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

/* Packed Multiply High for 64-bit i32x2 values.  RV64 uses one pmulh.w;
   the RV32 two-instruction forms are not implemented.  */
#if __riscv_xlen == 64
CREATE_RVP_INTRINSIC (int32x2_t, pmulh_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmulhr_i32x2, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmulhu_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (uint32x2_t, pmulhru_u32x2, uint32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmulhsu_i32x2, int32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int32x2_t, pmulhrsu_i32x2, int32x2_t, uint32x2_t)
#endif

/* Packed Multiply High Accumulate.  */
/* The i16x2 forms work on both ISAs.  The i16x4 and i32x2 forms are
   RV64-only; their RV32 two-instruction forms are not implemented.  */
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
#if __riscv_xlen == 64
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

/* Packed Q-format Multiplication.  The i16x2 and i16x4 forms work on both
   ISAs; the i32x2 forms are RV64-only.  */
CREATE_RVP_INTRINSIC (int16x2_t, pmulq_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x2_t, pmulqr_i16x2, int16x2_t, int16x2_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmulq_i16x4, int16x4_t, int16x4_t)
CREATE_RVP_INTRINSIC (int16x4_t, pmulqr_i16x4, int16x4_t, int16x4_t)
#if __riscv_xlen == 64
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
/* w-series i64 (RV64-only; RV32 mqwacc/mqrwacc register-pair TODO)  */
#if __riscv_xlen == 64
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
/* w-series i64 (scalar, RV64-only; RV32 wmul/wmulu/wmulsu register-pair TODO)
 */
#if __riscv_xlen == 64
CREATE_RVP_INTRINSIC (int64_t, mul_w00_i64, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mul_w01_i64, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mul_w11_i64, int32x2_t, int32x2_t)
CREATE_RVP_INTRINSIC_ALIAS (uint64_t, mulu_w00_i64, mulu_w00_u64, uint32x2_t,
			      uint32x2_t)
CREATE_RVP_INTRINSIC_ALIAS (uint64_t, mulu_w01_i64, mulu_w01_u64, uint32x2_t,
			      uint32x2_t)
CREATE_RVP_INTRINSIC_ALIAS (uint64_t, mulu_w11_i64, mulu_w11_u64, uint32x2_t,
			      uint32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mulsu_w00_i64, int32x2_t, uint32x2_t)
CREATE_RVP_INTRINSIC (int64_t, mulsu_w11_i64, int32x2_t, uint32x2_t)
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __riscv_p */
#endif /* __RISCV_PACKED_SIMD_H */
