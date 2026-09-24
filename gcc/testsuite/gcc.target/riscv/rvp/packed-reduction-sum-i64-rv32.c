/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>

int64_t
test_predsum_i8x8_i64 (int8x8_t a, int64_t acc)
{
  return __riscv_predsum_i8x8_i64 (a, acc);
}

uint64_t
test_predsumu_u8x8_u64 (uint8x8_t a, uint64_t acc)
{
  return __riscv_predsumu_u8x8_u64 (a, acc);
}

int64_t
test_predsum_i16x4_i64 (int16x4_t a, int64_t acc)
{
  return __riscv_predsum_i16x4_i64 (a, acc);
}

uint64_t
test_predsumu_u16x4_u64 (uint16x4_t a, uint64_t acc)
{
  return __riscv_predsumu_u16x4_u64 (a, acc);
}

int64_t
test_predsum_i32x2_i64 (int32x2_t a, int64_t acc)
{
  return __riscv_predsum_i32x2_i64 (a, acc);
}

uint64_t
test_predsumu_u32x2_u64 (uint32x2_t a, uint64_t acc)
{
  return __riscv_predsumu_u32x2_u64 (a, acc);
}

/* { dg-final { scan-assembler-times {\mpredsum\.dbs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpredsumu\.dbs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpredsum\.dhs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpredsumu\.dhs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mwadda\M} 3 } } */
/* { dg-final { scan-assembler-times {\mwaddau\M} 3 } } */
