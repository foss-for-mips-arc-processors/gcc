/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>

int8x8_t
test_pand_i8x8 (int8x8_t rs1, int8x8_t rs2)
{
  return __riscv_pand_i8x8 (rs1, rs2);
}

uint16x4_t
test_por_u16x4 (uint16x4_t rs1, uint16x4_t rs2)
{
  return __riscv_por_u16x4 (rs1, rs2);
}

int32x2_t
test_pxor_i32x2 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pxor_i32x2 (rs1, rs2);
}

uint32x2_t
test_pnot_u32x2 (uint32x2_t rs1)
{
  return __riscv_pnot_u32x2 (rs1);
}

/* { dg-final { scan-assembler-times {\mand\M} 1 } } */
/* { dg-final { scan-assembler-times {\mor\M} 1 } } */
/* { dg-final { scan-assembler-times {\mxor\M} 1 } } */
/* { dg-final { scan-assembler-times {\mnot\M} 1 } } */
