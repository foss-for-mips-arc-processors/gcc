/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mbig-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <riscv_packed_simd.h>

/* Preserve the explicit intrinsic's existing physical source packing.
   This does not specify a general big-endian API element-order contract.  */

int8x4_t
clip_s8 (int16x2_t a, int16x2_t b)
{
  return __riscv_pnclipp_i8x4 (a, b);
}

uint8x4_t
clip_u8 (uint16x2_t a, uint16x2_t b)
{
  return __riscv_pnclipup_u8x4 (a, b);
}

int16x2_t
clip_s16 (int32_t a, int32_t b)
{
  return __riscv_pnclipp_i16x2 (a, b);
}

uint16x2_t
clip_u16 (uint32_t a, uint32_t b)
{
  return __riscv_pnclipup_u16x2 (a, b);
}

/*
** clip_s8:
**  pack\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  pnclipp\.b\s+[^\n]+
**  ret
*/
/*
** clip_u8:
**  pack\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  pnclipup\.b\s+[^\n]+
**  ret
*/
/*
** clip_s16:
**  pack\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  pnclipp\.h\s+[^\n]+
**  ret
*/
/*
** clip_u16:
**  pack\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  pnclipup\.h\s+[^\n]+
**  ret
*/
