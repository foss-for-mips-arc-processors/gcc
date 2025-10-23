/* { dg-do compile } */
/* { dg-require-effective-target arcv_bitstream } */
/* { dg-options "-march=rv32im_xarcvbitstream -mabi=ilp32" } */

#include <stddef.h>

int test_bspop (int vs2)
{
  return __builtin_riscv_arcv_bspop (vs2);
}

/* { dg-final { scan-assembler-times "arcv\\.bspop" 1 } } */
