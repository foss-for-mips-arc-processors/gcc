/* { dg-do compile } */
/* { dg-require-effective-target arcv_bitstream } */
/* { dg-options "-march=rv32im_xarcvbitstream -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

int test_bspush (int vs2, int vs1) {
  return __builtin_riscv_arcv_bspush (vs2, vs1); }

/* { dg-final { scan-assembler-times "arcv\\.bspush" 1 } } */