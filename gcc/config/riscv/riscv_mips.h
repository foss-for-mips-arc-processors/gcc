/* RISC-V MIPS intrinsics include file.
   Copyright (C) 2024-2026 Free Software Foundation, Inc.

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

#ifndef __RISCV_MIPS_H
#define __RISCV_MIPS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__riscv_xmipstrig)

extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_fsin_hz (float x)
{
  return __builtin_riscv_mips_fsin_hz (x);
}

extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_fcos_hz (float x)
{
  return __builtin_riscv_mips_fcos_hz (x);
}

extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_ftan_hz (float x)
{
  return __builtin_riscv_mips_ftan_hz (x);
}

extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_fversin_hz (float x)
{
  return __builtin_riscv_mips_fversin_hz (x);
}

extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_ffrecip (float x)
{
  return __builtin_riscv_mips_ffrecip (x);
}

extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_ffrsqrt (float x)
{
  return __builtin_riscv_mips_ffrsqrt (x);
}

extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_fatan_hz (float x)
{
  return __builtin_riscv_mips_fatan_hz (x);
}

extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_ffexp2 (float x)
{
  return __builtin_riscv_mips_ffexp2 (x);
}

extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_ffsqrt (float x)
{
  return __builtin_riscv_mips_ffsqrt (x);
}

extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_fftanh (float x)
{
  return __builtin_riscv_mips_fftanh (x);
}

extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_fflog2 (float x)
{
  return __builtin_riscv_mips_fflog2 (x);
}

// This function is designed to approximate asin (x) using specialized
// MIPS intrinsics.
extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_asinf_hz (float x)
{
     // fli.s fa5, 0.25 and fsgnj.s fa5, fa5, fa0
    float fa5 = __builtin_copysignf (0.25f, x);

    // fmul.s fa4, fa0, fa0
    float fa4 = x * x;

    // fli.s fa3, 1.0 and fsub.s fa4, fa3, fa4
    fa4 = 1.0f - fa4;

    // mips.ffsqrt.s fa3, fa4
    float fa3 = __builtin_riscv_mips_ffsqrt (fa4);

    // mips.ffrecip.s fa2, fa0
    float fa2 = 1.0f / x;

    // fmul.s fa3, fa2, fa3
    fa3 = fa2 * fa3;

    // mips.fatanhz.s fa3, fa3
    fa3 = __builtin_riscv_mips_fatan_hz (fa3);

    // fsub.s fa5, fa5, fa3
    fa5 = fa5 - fa3;

    // mips.ffrsqrt.s fa4, fa4
    float fa4_rsqrt = 1.0f / __builtin_riscv_mips_ffsqrt (fa4);

    // fmul.s fa4, fa0, fa4
    fa4 = x * fa4_rsqrt;

    // mips.fatanhz.s fa4, fa4
    fa4 = __builtin_riscv_mips_fatan_hz (fa4);

    // fmax.s fa5, fa4, fa5
    fa5 = __builtin_fmaxf (fa4, fa5);

    // mips.flti.s fa4, 3
    fa4 = 3.0f;

    // fmul.s fa0, fa5, fa4
    return fa5 * fa4;
}

// Hardware‑friendly approximation of the arccosine (acos).
extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_acosf_hz (float x)
{
    return (0.25f - __riscv_mips_asinf_hz (x));
}

// Approximates a tangent‑like function using MIPS hyperbolic.
// arctangent intrinsics.
extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_tanf_fc_hz (float x)
{
    float t0,a0;

    // fli.s ft0, 0.250
    t0 = 0.250f;

    // fsub.s ft0, ft0, fa0
    t0 = t0 - x;

    // ftanhz.s fa0, fa0
    a0 = __builtin_riscv_mips_fatan_hz (x);

    // ftanhz.s ft0, ft0
    t0 = __builtin_riscv_mips_fatan_hz (t0);

    // ffrecip.s ft0, ft0
    t0 = 1.0f / t0;

    // fmax.s fa0, fa0, ft0
    return __builtin_fmaxf (a0, t0);;
}

// Provides an alternative arctangent approximation using reciprocal and
// subtraction logic.
extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_atan2f_fc_hz (float x)
{
    float ft0, ft1, a0;

    // ffrecip.s ft0, fa0
    ft0 = __builtin_riscv_mips_ffrecip (x);

    // fli.s ft1, 0.250
    ft1 = 0.250f;

    // fatanhz.s ft0, ft0
    ft0 = __builtin_riscv_mips_fatan_hz (ft0);

    // fsub.s ft0, ft1, ft0
    ft0 = ft1 - ft0;

    // fatanhz.s fa0, fa0
    a0 = __builtin_riscv_mips_fatan_hz (x);

    // fmin.s fa0, fa0, ft0
    return __builtin_fminf (a0, ft0);;
}

// Approximates the two‑argument arctangent (atan2) using MIPS intrinsics.
extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_atan2f_hz (float x, float y)
{

    // atan_hz (x / y)
    float expr1 = __builtin_riscv_mips_fatan_hz (x / y);

    // 0.25 - atan_hz (y / x)
    float expr2 = 0.25f - __builtin_riscv_mips_fatan_hz (y / x);

    return __builtin_fmaxf (expr1, expr2);
}

#endif // __riscv_xmipstrig

#if defined (__cplusplus)
}
#endif // __cplusplus
#endif // __RISCV_MIPS_H
