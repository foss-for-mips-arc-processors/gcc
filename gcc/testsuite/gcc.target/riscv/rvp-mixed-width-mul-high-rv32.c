/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-O1" "-Os" "-Oz" } } */

#include <stdint-gcc.h>

typedef int16_t int16x2_t __attribute__ ((vector_size (4)));

int32_t test_mulh_h0 (int32_t a, int16x2_t b)
{
  return (int32_t) ((int64_t) a * (int64_t) b[0] >> 16);
}

int32_t test_mulh_h1(int32_t a, int16x2_t b) {
    return (int32_t)((int64_t)a * (int64_t)b[1] >> 16);
}

/* { dg-final { scan-assembler-times "\\mmulh\\.h0\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mmulh\\.h1\\M" 1 } } */
