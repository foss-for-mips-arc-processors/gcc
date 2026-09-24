/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>

#define TEST_PREV(NAME, TYPE) \
  TYPE test_##NAME (TYPE a) \
  { \
    return __riscv_##NAME (a); \
  }

TEST_PREV (prev_i8x4, int8x4_t)
TEST_PREV (prev_u8x4, uint8x4_t)
TEST_PREV (prev_i16x2, int16x2_t)
TEST_PREV (prev_u16x2, uint16x2_t)
TEST_PREV (prev_i8x8, int8x8_t)
TEST_PREV (prev_u8x8, uint8x8_t)
TEST_PREV (prev_i16x4, int16x4_t)
TEST_PREV (prev_u16x4, uint16x4_t)
TEST_PREV (prev_i32x2, int32x2_t)
TEST_PREV (prev_u32x2, uint32x2_t)

/* { dg-final { scan-assembler-times {\mrev8\M} 6 } } */
/* { dg-final { scan-assembler-times {\mppairoe\.h\M} 6 } } */
/* { dg-final { scan-assembler-not {\mrev16\M|\mppairoe\.w\M} } } */
