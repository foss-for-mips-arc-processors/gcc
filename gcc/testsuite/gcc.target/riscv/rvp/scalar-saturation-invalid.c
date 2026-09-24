/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d" } */

#include <riscv_packed_simd.h>

int32_t
test_sati_i32_zero (int32_t rs1)
{
  return __builtin_riscv_sati_i32 (rs1, 0); /* { dg-error "invalid argument" } */
}

uint32_t
test_usati_u32_variable (int32_t rs1, unsigned int width)
{
  return __builtin_riscv_usati_u32 (rs1, width); /* { dg-error "invalid argument" } */
}

int64_t
test_sati_i64_too_large (int64_t rs1)
{
  return __builtin_riscv_sati_i64 (rs1, 65); /* { dg-error "invalid argument" } */
}

uint64_t
test_usati_u64_too_large (int64_t rs1)
{
  return __builtin_riscv_usati_u64 (rs1, 64); /* { dg-error "invalid argument" } */
}

int16x2_t
test_psati_i16x2_zero (int16x2_t rs1)
{
  return __builtin_riscv_psati_i16x2 (rs1, 0); /* { dg-error "invalid argument" } */
}

uint16x4_t
test_pusati_u16x4_too_large (int16x4_t rs1)
{
  return __builtin_riscv_pusati_u16x4 (rs1, 16); /* { dg-error "invalid argument" } */
}

int32x2_t
test_psati_i32x2_too_large (int32x2_t rs1)
{
  return __builtin_riscv_psati_i32x2 (rs1, 33); /* { dg-error "invalid argument" } */
}

uint32x2_t
test_pusati_u32x2_too_large (int32x2_t rs1)
{
  return __builtin_riscv_pusati_u32x2 (rs1, 32); /* { dg-error "invalid argument" } */
}
