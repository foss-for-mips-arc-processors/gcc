/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>

int32x2_t
test_psas_x_i32x2 (int32x2_t a, int32x2_t b)
{
  return __riscv_psas_x_i32x2 (a, b);
}

int32x2_t
test_pssa_x_i32x2 (int32x2_t a, int32x2_t b)
{
  return __riscv_pssa_x_i32x2 (a, b);
}

int32x2_t
test_paas_x_i32x2 (int32x2_t a, int32x2_t b)
{
  return __riscv_paas_x_i32x2 (a, b);
}

int32x2_t
test_pasa_x_i32x2 (int32x2_t a, int32x2_t b)
{
  return __riscv_pasa_x_i32x2 (a, b);
}

/* { dg-final { scan-assembler-times {\msadd\M} 2 } } */
/* { dg-final { scan-assembler-times {\mssub\M} 2 } } */
/* { dg-final { scan-assembler-times {\maadd\M} 2 } } */
/* { dg-final { scan-assembler-times {\masub\M} 2 } } */
