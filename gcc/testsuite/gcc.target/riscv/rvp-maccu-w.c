/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-flto" } } */

#include <stdint-gcc.h>

// RV32 vector types (also work on RV64)
typedef int8_t int8x4_t __attribute__((vector_size(4)));
typedef uint8_t uint8x4_t __attribute__((vector_size(4)));
typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef uint16_t uint16x2_t __attribute__((vector_size(4)));

// RV64 vector types
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef uint16_t uint16x4_t __attribute__((vector_size(8)));
typedef int32_t int32x2_t __attribute__((vector_size(8)));
typedef uint32_t uint32x2_t __attribute__((vector_size(8)));

// --- maccu.w00/w01/w11 family: scalar widening multiply-accumulate (RV64) ---
// rd = rd + zext(rs1.w[0]) * zext(rs2.w[0])

uint64_t test_maccu_w00(uint64_t acc, uint32x2_t a, uint32x2_t b) {
    return acc + (uint64_t)a[0] * (uint64_t)b[0];
}

uint64_t test_maccu_w00_commute(uint64_t acc, uint32x2_t a, uint32x2_t b) {
    return (uint64_t)a[0] * (uint64_t)b[0] + acc;
}

uint64_t test_maccu_w01(uint64_t acc, uint32x2_t a, uint32x2_t b) {
    return acc + (uint64_t)a[0] * (uint64_t)b[1];
}

uint64_t test_maccu_w01_commute(uint64_t acc, uint32x2_t a, uint32x2_t b) {
    return (uint64_t)a[0] * (uint64_t)b[1] + acc;
}

uint64_t test_maccu_w11(uint64_t acc, uint32x2_t a, uint32x2_t b) {
    return acc + (uint64_t)a[1] * (uint64_t)b[1];
}

uint64_t test_maccu_w11_commute(uint64_t acc, uint32x2_t a, uint32x2_t b) {
    return (uint64_t)a[1] * (uint64_t)b[1] + acc;
}

/* { dg-final { scan-assembler-times "\\mmaccu\\.w00\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmaccu\\.w01\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmaccu\\.w11\\M" 2 } } */
