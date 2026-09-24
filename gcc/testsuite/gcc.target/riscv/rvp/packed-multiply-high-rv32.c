/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>

int32x2_t
pmulh_i32x2 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pmulh_i32x2 (rs1, rs2);
}

int32x2_t
pmulhr_i32x2 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pmulhr_i32x2 (rs1, rs2);
}

uint32x2_t
pmulhu_u32x2 (uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pmulhu_u32x2 (rs1, rs2);
}

uint32x2_t
pmulhru_u32x2 (uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pmulhru_u32x2 (rs1, rs2);
}

int32x2_t
pmulhsu_i32x2 (int32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pmulhsu_i32x2 (rs1, rs2);
}

int32x2_t
pmulhrsu_i32x2 (int32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pmulhrsu_i32x2 (rs1, rs2);
}

int16x4_t
pmhacc_i16x4 (int16x4_t rd, int16x4_t rs1, int16x4_t rs2)
{
  return __riscv_pmhacc_i16x4 (rd, rs1, rs2);
}

int16x4_t
pmhracc_i16x4 (int16x4_t rd, int16x4_t rs1, int16x4_t rs2)
{
  return __riscv_pmhracc_i16x4 (rd, rs1, rs2);
}

uint16x4_t
pmhaccu_u16x4 (uint16x4_t rd, uint16x4_t rs1, uint16x4_t rs2)
{
  return __riscv_pmhaccu_u16x4 (rd, rs1, rs2);
}

uint16x4_t
pmhraccu_u16x4 (uint16x4_t rd, uint16x4_t rs1, uint16x4_t rs2)
{
  return __riscv_pmhraccu_u16x4 (rd, rs1, rs2);
}

int16x4_t
pmhaccsu_i16x4 (int16x4_t rd, int16x4_t rs1, uint16x4_t rs2)
{
  return __riscv_pmhaccsu_i16x4 (rd, rs1, rs2);
}

int16x4_t
pmhraccsu_i16x4 (int16x4_t rd, int16x4_t rs1, uint16x4_t rs2)
{
  return __riscv_pmhraccsu_i16x4 (rd, rs1, rs2);
}

int32x2_t
pmhacc_i32x2 (int32x2_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pmhacc_i32x2 (rd, rs1, rs2);
}

int32x2_t
pmhracc_i32x2 (int32x2_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pmhracc_i32x2 (rd, rs1, rs2);
}

uint32x2_t
pmhaccu_u32x2 (uint32x2_t rd, uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pmhaccu_u32x2 (rd, rs1, rs2);
}

uint32x2_t
pmhraccu_u32x2 (uint32x2_t rd, uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pmhraccu_u32x2 (rd, rs1, rs2);
}

int32x2_t
pmhaccsu_i32x2 (int32x2_t rd, int32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pmhaccsu_i32x2 (rd, rs1, rs2);
}

int32x2_t
pmhraccsu_i32x2 (int32x2_t rd, int32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pmhraccsu_i32x2 (rd, rs1, rs2);
}

int32x2_t
pmulq_i32x2 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pmulq_i32x2 (rs1, rs2);
}

int32x2_t
pmulqr_i32x2 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pmulqr_i32x2 (rs1, rs2);
}

/* { dg-final { scan-assembler-times {\mmulh\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmulhr\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmulhu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmulhru\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmulhsu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmulhrsu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmhacc\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmhracc\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmhaccu\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmhraccu\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmhaccsu\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmhraccsu\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmhacc\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmhracc\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmhaccu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmhraccu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmhaccsu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmhraccsu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmulq\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmulqr\M} 2 } } */
