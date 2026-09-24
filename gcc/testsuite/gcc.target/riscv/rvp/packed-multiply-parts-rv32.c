/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>

int64_t
mul_w00_i64 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_mul_w00_i64 (rs1, rs2);
}

int64_t
mul_w01_i64 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_mul_w01_i64 (rs1, rs2);
}

int64_t
mul_w11_i64 (int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_mul_w11_i64 (rs1, rs2);
}

uint64_t
mulu_w00_u64 (uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_mulu_w00_u64 (rs1, rs2);
}

uint64_t
mulu_w01_u64 (uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_mulu_w01_u64 (rs1, rs2);
}

uint64_t
mulu_w11_u64 (uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_mulu_w11_u64 (rs1, rs2);
}

int64_t
mulsu_w00_i64 (int32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_mulsu_w00_i64 (rs1, rs2);
}

int64_t
mulsu_w11_i64 (int32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_mulsu_w11_i64 (rs1, rs2);
}

int64_t
macc_w00_i64 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_macc_w00_i64 (rd, rs1, rs2);
}

int64_t
macc_w01_i64 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_macc_w01_i64 (rd, rs1, rs2);
}

int64_t
macc_w11_i64 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_macc_w11_i64 (rd, rs1, rs2);
}

uint64_t
maccu_w00_u64 (uint64_t rd, uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_maccu_w00_u64 (rd, rs1, rs2);
}

uint64_t
maccu_w01_u64 (uint64_t rd, uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_maccu_w01_u64 (rd, rs1, rs2);
}

uint64_t
maccu_w11_u64 (uint64_t rd, uint32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_maccu_w11_u64 (rd, rs1, rs2);
}

int64_t
maccsu_w00_i64 (int64_t rd, int32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_maccsu_w00_i64 (rd, rs1, rs2);
}

int64_t
maccsu_w11_i64 (int64_t rd, int32x2_t rs1, uint32x2_t rs2)
{
  return __riscv_maccsu_w11_i64 (rd, rs1, rs2);
}

int64_t
mqacc_w00_i64 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_mqacc_w00_i64 (rd, rs1, rs2);
}

int64_t
mqacc_w01_i64 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_mqacc_w01_i64 (rd, rs1, rs2);
}

int64_t
mqacc_w11_i64 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_mqacc_w11_i64 (rd, rs1, rs2);
}

int64_t
mqracc_w00_i64 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_mqracc_w00_i64 (rd, rs1, rs2);
}

int64_t
mqracc_w01_i64 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_mqracc_w01_i64 (rd, rs1, rs2);
}

int64_t
mqracc_w11_i64 (int64_t rd, int32x2_t rs1, int32x2_t rs2)
{
  return __riscv_mqracc_w11_i64 (rd, rs1, rs2);
}

/* { dg-final { scan-assembler-times {\mwmul\M} 3 } } */
/* { dg-final { scan-assembler-times {\mwmulu\M} 3 } } */
/* { dg-final { scan-assembler-times {\mwmulsu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mwmacc\M} 3 } } */
/* { dg-final { scan-assembler-times {\mwmaccu\M} 3 } } */
/* { dg-final { scan-assembler-times {\mwmaccsu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmqwacc\M} 3 } } */
/* { dg-final { scan-assembler-times {\mmqrwacc\M} 3 } } */
