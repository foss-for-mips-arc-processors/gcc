/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>

#define TEST_PAIR(NAME, TYPE) \
  TYPE test_##NAME (TYPE a, TYPE b) \
  { \
    return __riscv_##NAME (a, b); \
  }

TEST_PAIR (ppaire_u32x2, uint32x2_t)
TEST_PAIR (ppaire_i32x2, int32x2_t)
TEST_PAIR (ppaireo_u32x2, uint32x2_t)
TEST_PAIR (ppaireo_i32x2, int32x2_t)
TEST_PAIR (ppairoe_u32x2, uint32x2_t)
TEST_PAIR (ppairoe_i32x2, int32x2_t)
TEST_PAIR (ppairo_u32x2, uint32x2_t)
TEST_PAIR (ppairo_i32x2, int32x2_t)

/* { dg-final { scan-assembler-times {\mmv\M} 12 } } */
