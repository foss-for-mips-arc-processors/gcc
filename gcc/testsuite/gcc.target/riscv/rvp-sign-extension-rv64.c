/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

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

int32x2_t test_psext_w_h_rv64(int16x4_t a) {
    int32_t lo = a[0];
    int32_t hi = a[2];
    return (int32x2_t){lo, hi};
}

//TODO: Support psext.w.b and psext.h.b in RV64, currently can't combine due to cost model

// Consolidated scan-assembler-times for all instructions
/* { dg-final { scan-assembler-times "\\mpsext\\.w\\.h\\M" 1 } } */
