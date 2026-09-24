/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>

int64_t
pm2add_i32x2 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pm2add_i32x2 (rs1, rs2);
}

int64_t
pm2add_x_i32x2 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pm2add_x_i32x2 (rs1, rs2);
}

uint64_t
pm2addu_u32x2 (uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pm2addu_u32x2 (rs1, rs2);
}

int64_t
pmq2add_i32x2 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pmq2add_i32x2 (rs1, rs2);
}

int64_t
pm2sub_i32x2 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pm2sub_i32x2 (rs1, rs2);
}

int64_t
pm2sub_x_i32x2 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pm2sub_x_i32x2 (rs1, rs2);
}

int64_t
pm2addsu_i32x2 (int32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pm2addsu_i32x2 (rs1, rs2);
}

int64_t
pmqr2add_i32x2 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pmqr2add_i32x2 (rs1, rs2);
}

int64_t
pm4add_i16x4 (int16x4_t rs1, int16x4_t rs2)
{
  return __riscv_pm4add_i16x4 (rs1, rs2);
}

uint64_t
pm4addu_u16x4 (uint16x4_t rs1, uint16x4_t rs2)
{
  return __riscv_pm4addu_u16x4 (rs1, rs2);
}

int64_t
pm4addsu_i16x4 (int16x4_t rs1, uint16x4_t rs2)
{
  return __riscv_pm4addsu_i16x4 (rs1, rs2);
}

int64_t
pm2adda_i32x2 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pm2adda_i32x2 (rd, rs1, rs2);
}

int64_t
pm2adda_x_i32x2 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pm2adda_x_i32x2 (rd, rs1, rs2);
}

uint64_t
pm2addau_u32x2 (uint64_t rd, uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pm2addau_u32x2 (rd, rs1, rs2);
}

int64_t
pmq2adda_i32x2 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pmq2adda_i32x2 (rd, rs1, rs2);
}

int64_t
pm2suba_i32x2 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pm2suba_i32x2 (rd, rs1, rs2);
}

int64_t
pm2suba_x_i32x2 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pm2suba_x_i32x2 (rd, rs1, rs2);
}

int64_t
pm2addasu_i32x2 (int64_t rd, int32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_pm2addasu_i32x2 (rd, rs1, rs2);
}

int64_t
pmqr2adda_i32x2 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_pmqr2adda_i32x2 (rd, rs1, rs2);
}

int64_t
pm4adda_i16x4 (int64_t rd, int16x4_t rs1, int16x4_t rs2)
{
  return __riscv_pm4adda_i16x4 (rd, rs1, rs2);
}

uint64_t
pm4addau_u16x4 (uint64_t rd, uint16x4_t rs1, uint16x4_t rs2)
{
  return __riscv_pm4addau_u16x4 (rd, rs1, rs2);
}

int64_t
pm4addasu_i16x4 (int64_t rd, int16x4_t rs1, uint16x4_t rs2)
{
  return __riscv_pm4addasu_i16x4 (rd, rs1, rs2);
}

/* { dg-final { scan-assembler-times {\mwmul\M} 8 } } */
/* { dg-final { scan-assembler-times {\mwmulu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mwmulsu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mwmacc\M} 8 } } */
/* { dg-final { scan-assembler-times {\mwmaccu\M} 3 } } */
/* { dg-final { scan-assembler-times {\mwmaccsu\M} 3 } } */
/* { dg-final { scan-assembler-times {\mmqwacc\M} 4 } } */
/* { dg-final { scan-assembler-times {\mmqrwacc\M} 4 } } */
/* { dg-final { scan-assembler-times {\msubd\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpm2wadd\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2wadda\.h\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpm2waddu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2waddau\.h\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpm2waddsu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2waddasu\.h\M} 3 } } */
