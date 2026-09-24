/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-O1" "-Os" "-Oz" "-Og" } } */

#include <stdint-gcc.h>

// RV32 vector types (also work on RV64)
typedef int8_t int8x4_t __attribute__((vector_size(4)));
typedef uint8_t uint8x4_t __attribute__((vector_size(4)));
typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef uint16_t uint16x2_t __attribute__((vector_size(4)));

// RV64 vector types
typedef int8_t int8x8_t __attribute__((vector_size(8)));
typedef uint8_t uint8x8_t __attribute__((vector_size(8)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef uint16_t uint16x4_t __attribute__((vector_size(8)));
typedef int32_t int32x2_t __attribute__((vector_size(8)));
typedef uint32_t uint32x2_t __attribute__((vector_size(8)));

// --- predsum.hs: signed halfword reduction sum (2 halfwords -> scalar) ---

// CHECK-LABEL: test_reduce_sum_h:
// CHECK: predsum.hs
int32_t test_reduce_sum_h(int16x2_t a) {
    return (int32_t)a[0] + (int32_t)a[1];
}

int32_t test_reduce_sum_h_2(int16x2_t a, int32_t b) {
    return b + (int32_t)a[0] + (int32_t)a[1];
}

// --- predsum.hu: unsigned halfword reduction sum (2 halfwords -> scalar) ---

// CHECK-LABEL: test_reduce_sum_hu:
// CHECK: predsumu.hs
uint32_t test_reduce_sum_hu(uint16x2_t a) {
    return (uint32_t)a[0] + (uint32_t)a[1];
}

uint32_t test_reduce_sum_hu_2(uint16x2_t a, uint32_t b) {
    return b + (uint32_t)a[0] + (uint32_t)a[1];
}

/* { dg-final { scan-assembler-times "\\mpredsum\\.hs\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mpredsumu\\.hs\\M" 2 } } */
