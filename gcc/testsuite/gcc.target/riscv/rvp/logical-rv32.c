/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>

int8x4_t
test_pand_i8x4 (int8x4_t rs1, int8x4_t rs2)
{
  return __riscv_pand_i8x4 (rs1, rs2);
}

uint8x4_t
test_por_u8x4 (uint8x4_t rs1, uint8x4_t rs2)
{
  return __riscv_por_u8x4 (rs1, rs2);
}

int16x2_t
test_pxor_i16x2 (int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pxor_i16x2 (rs1, rs2);
}

uint16x2_t
test_pnot_u16x2 (uint16x2_t rs1)
{
  return __riscv_pnot_u16x2 (rs1);
}

/* { dg-final { scan-assembler-times {\mand\M} 1 } } */
/* { dg-final { scan-assembler-times {\mor\M} 1 } } */
/* { dg-final { scan-assembler-times {\mxor\M} 1 } } */
/* { dg-final { scan-assembler-times {\mnot\M} 1 } } */
