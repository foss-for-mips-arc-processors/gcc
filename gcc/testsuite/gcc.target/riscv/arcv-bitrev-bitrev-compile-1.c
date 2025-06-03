/* { dg-do compile } */
/* { dg-require-effective-target arcv_bitrev } */
/* { dg-options "-march=rv32im_xarcvbitrev -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

int test_bitrev (int vs2, int vs1) {
  return __builtin_riscv_arcv_bitrev (vs2, vs1); }

/* { dg-final { scan-assembler-times "arcv\\.bitrev" 1 } } */