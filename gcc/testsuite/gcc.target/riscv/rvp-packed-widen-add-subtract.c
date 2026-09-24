/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-Og" "-flto" } } */

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


int16x4_t test_widen_add_b(int8x4_t a, int8x4_t b) {
    int16x4_t wa = __builtin_convertvector(a, int16x4_t);
    int16x4_t wb = __builtin_convertvector(b, int16x4_t);
    return wa + wb;
}

int16x4_t test_widen_sub_b(int8x4_t a, int8x4_t b) {
    int16x4_t wa = __builtin_convertvector(a, int16x4_t);
    int16x4_t wb = __builtin_convertvector(b, int16x4_t);
    return wa - wb;
}

uint16x4_t test_widen_addu_b(uint8x4_t a, uint8x4_t b) {
    uint16x4_t wa = __builtin_convertvector(a, uint16x4_t);
    uint16x4_t wb = __builtin_convertvector(b, uint16x4_t);
    return wa + wb;
}

int32x2_t test_widen_add_h(int16x2_t a, int16x2_t b) {
    int32x2_t wa = __builtin_convertvector(a, int32x2_t);
    int32x2_t wb = __builtin_convertvector(b, int32x2_t);
    return wa + wb;
}

int32x2_t test_widen_sub_h(int16x2_t a, int16x2_t b) {
    int32x2_t wa = __builtin_convertvector(a, int32x2_t);
    int32x2_t wb = __builtin_convertvector(b, int32x2_t);
    return wa - wb;
}

uint32x2_t test_widen_addu_h(uint16x2_t a, uint16x2_t b) {
    uint32x2_t wa = __builtin_convertvector(a, uint32x2_t);
    uint32x2_t wb = __builtin_convertvector(b, uint32x2_t);
    return wa + wb;
}

/* { dg-final { scan-assembler-times "\\mpwadd\\.b\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpwaddu\\.b\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpwsub\\.b\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpwadd\\.h\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpwaddu\\.h\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpwsub\\.h\\M" 1 } } */
