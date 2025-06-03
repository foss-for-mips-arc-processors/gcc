/* { dg-do compile } */
/* { dg-require-effective-target arcv_bitstream } */
/* { dg-options "-march=rv32im_xarcvbitstream -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

int test_bspeek (int vs2) {
  return __builtin_riscv_arcv_bspeek (vs2); }

/* { dg-final { scan-assembler-times "arcv\\.bspeek" 1 } } */