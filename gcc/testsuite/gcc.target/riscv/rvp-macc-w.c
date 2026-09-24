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

// --- macc.w00/w01/w11 family: scalar widening multiply-accumulate (RV64) ---
// rd = rd + sext(rs1.w[0]) * sext(rs2.w[0])

int64_t test_macc_w00(int64_t acc, int32x2_t a, int32x2_t b) {
    return acc + (int64_t)a[0] * (int64_t)b[0];
}

int64_t test_macc_w00_commute(int64_t acc, int32x2_t a, int32x2_t b) {
    return (int64_t)a[0] * (int64_t)b[0] + acc;
}

int64_t test_macc_w01(int64_t acc, int32x2_t a, int32x2_t b) {
    return acc + (int64_t)a[0] * (int64_t)b[1];
}

int64_t test_macc_w01_commute(int64_t acc, int32x2_t a, int32x2_t b) {
    return (int64_t)a[0] * (int64_t)b[1] + acc;
}

int64_t test_macc_w11(int64_t acc, int32x2_t a, int32x2_t b) {
    return acc + (int64_t)a[1] * (int64_t)b[1];
}

int64_t test_macc_w11_commute(int64_t acc, int32x2_t a, int32x2_t b) {
    return (int64_t)a[1] * (int64_t)b[1] + acc;
}

/* { dg-final { scan-assembler-times "\\mmacc\\.w00\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmacc\\.w01\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmacc\\.w11\\M" 2 } } */
