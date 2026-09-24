/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>

int16x4_t
test_pwmul_i16x4 (int8x4_t rs1, int8x4_t rs2)
{
  return __riscv_pwmul_i16x4 (rs1, rs2);
}

int32x2_t
test_pwmul_i32x2 (int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pwmul_i32x2 (rs1, rs2);
}

uint16x4_t
test_pwmulu_u16x4 (uint8x4_t rs1, uint8x4_t rs2)
{
  return __riscv_pwmulu_u16x4 (rs1, rs2);
}

uint32x2_t
test_pwmulu_u32x2 (uint16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pwmulu_u32x2 (rs1, rs2);
}

int16x4_t
test_pwmulsu_i16x4 (int8x4_t rs1, uint8x4_t rs2)
{
  return __riscv_pwmulsu_i16x4 (rs1, rs2);
}

int32x2_t
test_pwmulsu_i32x2 (int16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pwmulsu_i32x2 (rs1, rs2);
}

int32x2_t
test_pwmacc_i32x2 (int32x2_t rd, int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pwmacc_i32x2 (rd, rs1, rs2);
}

uint32x2_t
test_pwmaccu_u32x2 (uint32x2_t rd, uint16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pwmaccu_u32x2 (rd, rs1, rs2);
}

int32x2_t
test_pwmaccsu_i32x2 (int32x2_t rd, int16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pwmaccsu_i32x2 (rd, rs1, rs2);
}

int32x2_t
test_pmqwacc_i32x2 (int32x2_t rd, int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pmqwacc_i32x2 (rd, rs1, rs2);
}

int32x2_t
test_pmqrwacc_i32x2 (int32x2_t rd, int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pmqrwacc_i32x2 (rd, rs1, rs2);
}

/* { dg-final { scan-assembler-times {zip8p} 4 } } */
/* { dg-final { scan-assembler-times {zip16p} 10 } } */
/* { dg-final { scan-assembler-times {pmul\.h\.b01} 1 } } */
/* { dg-final { scan-assembler-times {pmul\.w\.h01} 1 } } */
/* { dg-final { scan-assembler-times {pmulu\.h\.b01} 1 } } */
/* { dg-final { scan-assembler-times {pmulu\.w\.h01} 1 } } */
/* { dg-final { scan-assembler-times {pmulsu\.h\.b00} 1 } } */
/* { dg-final { scan-assembler-times {pmulsu\.w\.h00} 1 } } */
/* { dg-final { scan-assembler-times {pmacc\.w\.h01} 1 } } */
/* { dg-final { scan-assembler-times {pmaccu\.w\.h01} 1 } } */
/* { dg-final { scan-assembler-times {pmaccsu\.w\.h00} 1 } } */
/* { dg-final { scan-assembler-times {pmqacc\.w\.h01} 1 } } */
/* { dg-final { scan-assembler-times {pmqracc\.w\.h01} 1 } } */
