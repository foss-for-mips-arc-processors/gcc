/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>

int64_t
test_pm2wadd_i64 (int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pm2wadd_i64 (rs1, rs2);
}

int64_t
test_pm2wadd_x_i64 (int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pm2wadd_x_i64 (rs1, rs2);
}

uint64_t
test_pm2waddu_u64 (uint16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pm2waddu_u64 (rs1, rs2);
}

int64_t
test_pm2wsub_i64 (int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pm2wsub_i64 (rs1, rs2);
}

int64_t
test_pm2wsub_x_i64 (int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pm2wsub_x_i64 (rs1, rs2);
}

uint64_t
test_pm2waddsu_u64 (int16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pm2waddsu_u64 (rs1, rs2);
}

int64_t
test_pm2wadda_i64 (int64_t rd, int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pm2wadda_i64 (rd, rs1, rs2);
}

int64_t
test_pm2wadda_x_i64 (int64_t rd, int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pm2wadda_x_i64 (rd, rs1, rs2);
}

uint64_t
test_pm2waddau_u64 (uint64_t rd, uint16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pm2waddau_u64 (rd, rs1, rs2);
}

int64_t
test_pm2wsuba_i64 (int64_t rd, int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pm2wsuba_i64 (rd, rs1, rs2);
}

int64_t
test_pm2wsuba_x_i64 (int64_t rd, int16x2_t rs1, int16x2_t rs2)
{
  return __riscv_pm2wsuba_x_i64 (rd, rs1, rs2);
}

int64_t
test_pm2waddasu_u64 (int64_t rd, int16x2_t rs1, uint16x2_t rs2)
{
  return __riscv_pm2waddasu_u64 (rd, rs1, rs2);
}

/* { dg-final { scan-assembler-times {\mzext\.w\M} 10 } } */
/* { dg-final { scan-assembler-times {\mppairoe\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpm4add\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpm4addu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm4addsu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2sub\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpm2sub\.hx\M} 2 } } */
/* { dg-final { scan-assembler-times {\msext\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpm4adda\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpm4addau\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm4addasu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpredsum\.ws\M} 2 } } */
