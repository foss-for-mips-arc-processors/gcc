/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>

int16x4_t
test_pwadd_i16x4 (int8x4_t rs1, int8x4_t rs2)
{
  return __riscv_pwadd_i16x4 (rs1, rs2);
}

int32x2_t
test_pwadd_i32x2 (int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pwadd_i32x2 (rs1, rs2);
}

uint16x4_t
test_pwaddu_u16x4 (uint8x4_t rs1, uint8x4_t rs2)
{
  return __riscv_pwaddu_u16x4 (rs1, rs2);
}

uint32x2_t
test_pwaddu_u32x2 (uint16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pwaddu_u32x2 (rs1, rs2);
}

int16x4_t
test_pwsub_i16x4 (int8x4_t rs1, int8x4_t rs2)
{
  return __riscv_pwsub_i16x4 (rs1, rs2);
}

int32x2_t
test_pwsub_i32x2 (int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pwsub_i32x2 (rs1, rs2);
}

uint16x4_t
test_pwsubu_u16x4 (uint8x4_t rs1, uint8x4_t rs2)
{
  return __riscv_pwsubu_u16x4 (rs1, rs2);
}

uint32x2_t
test_pwsubu_u32x2 (uint16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pwsubu_u32x2 (rs1, rs2);
}

int16x4_t
test_pwadda_i16x4 (int16x4_t rd, int8x4_t rs1, int8x4_t rs2)
{
  return __riscv_pwadda_i16x4 (rd, rs1, rs2);
}

int32x2_t
test_pwadda_i32x2 (int32x2_t rd, int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pwadda_i32x2 (rd, rs1, rs2);
}

uint16x4_t
test_pwaddau_u16x4 (uint16x4_t rd, uint8x4_t rs1, uint8x4_t rs2)
{
  return __riscv_pwaddau_u16x4 (rd, rs1, rs2);
}

uint32x2_t
test_pwaddau_u32x2 (uint32x2_t rd, uint16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pwaddau_u32x2 (rd, rs1, rs2);
}

int16x4_t
test_pwsuba_i16x4 (int16x4_t rd, int8x4_t rs1, int8x4_t rs2)
{
  return __riscv_pwsuba_i16x4 (rd, rs1, rs2);
}

int32x2_t
test_pwsuba_i32x2 (int32x2_t rd, int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pwsuba_i32x2 (rd, rs1, rs2);
}

uint16x4_t
test_pwsubau_u16x4 (uint16x4_t rd, uint8x4_t rs1, uint8x4_t rs2)
{
  return __riscv_pwsubau_u16x4 (rd, rs1, rs2);
}

uint32x2_t
test_pwsubau_u32x2 (uint32x2_t rd, uint16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pwsubau_u32x2 (rd, rs1, rs2);
}

/* { dg-final { scan-assembler-times {\mzip8p\M} 12 } } */
/* { dg-final { scan-assembler-times {\mzip16p\M} 10 } } */
/* { dg-final { scan-assembler-times {\mpli\.h\M} 6 } } */
/* { dg-final { scan-assembler-times {\mpsext\.h\.b\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpsrai\.h\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpadd\.h\M} 8 } } */
/* { dg-final { scan-assembler-times {\mpsub\.h\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpadd\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsub\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpm2add\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2addu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2sub\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2adda\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2addau\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2suba\.h\M} 1 } } */
