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

/* Approximates asin (x) using the MIPS trig intrinsics.  */
extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_fasin_hz (float x)
{
    /* fmul.s: x^2.  */
    float x_squared = x * x;

    /* fli.s + fsub.s: 1 - x^2.  */
    float one_minus_x_squared = 1.0f - x_squared ;

    /* mips.ffsqrt.s: sqrt (1 - x^2).  */
    float sqrt_term = __riscv_mips_ffsqrt (one_minus_x_squared);

    /* mips.ffrecip.s: 1 / x.  */
    float recip_x = __riscv_mips_ffrecip (x);

    /* fmul.s: sqrt (1 - x^2) / x.  */
    float complement_ratio = recip_x * sqrt_term;

    /* mips.fatanhz.s: atan (sqrt (1 - x^2) / x), in turns.  */
    float complement_atan_hz = __riscv_mips_fatan_hz (complement_ratio);

    /* fli.s + fsgnj.s: 0.25 turns with the sign of x.  */
    float signed_quarter = __builtin_copysignf (0.25f, x);

    /* fsub.s: 0.25 - atan (sqrt (1 - x^2) / x).  */
    /* Valid whein |x| is close to 1.  */
    float complement_branch_hz = signed_quarter - complement_atan_hz;

    /* mips.ffrsqrt.s: 1 / sqrt (1 - x^2).  */
    float rsqrt_term = __riscv_mips_ffrsqrt (one_minus_x_squared);

    /* fmul.s: x / sqrt (1 - x^2).  */
    float direct_ratio = x * rsqrt_term;

    /* mips.fatanhz.s: atan (x / sqrt (1 - x^2)), in turns.  */
    /* Valid for small |x|.  */
    float direct_atan_hz = __riscv_mips_fatan_hz (direct_ratio);

    return __builtin_fmaxf (direct_atan_hz, complement_branch_hz);
}

/* Hardware‑friendly approximation of the arccosine (acos).  */
extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_facos_hz (float x)
{
    return (0.25f - __riscv_mips_fasin_hz (x));
}

/* Approximates atan2 (x, y) using MIPS atan_hz intrinsics.  */
extern __inline float
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
__riscv_mips_fatan2_hz (float x, float y)
{
  /* mips.ffrecip.s: 1 / y.  */
  float recip_y = __riscv_mips_ffrecip (y);
  /* fmul.s x, recip_y: x/y.  */
  float prod_x_recip_y = x * recip_y;

  /* mips.ffrecip.s: 1 / x.  */
  float recip_x = __riscv_mips_ffrecip (x);
  /* fmul.s y, recip_x: y/x.  */
  float prod_y_recip_x = y * recip_x;

  float atan_xy = __riscv_mips_fatan_hz (prod_x_recip_y);
  float atan_yx = __riscv_mips_fatan_hz (prod_y_recip_x);

  return __builtin_fmaxf (atan_xy, 0.25f - atan_yx);
}

#endif // __riscv_xmipstrig

#if defined (__cplusplus)
}
#endif // __cplusplus
#endif // __RISCV_MIPS_H
