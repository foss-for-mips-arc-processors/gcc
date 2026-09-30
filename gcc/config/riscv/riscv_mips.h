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

#endif // __riscv_xmipstrig

#if defined (__cplusplus)
}
#endif // __cplusplus
#endif // __RISCV_MIPS_H
