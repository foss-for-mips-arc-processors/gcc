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

// --- pwmul.b: signed widening multiply byte -> halfword ---

int16x4_t test_widen_mul_b(int8x4_t a, int8x4_t b) {
    int16x4_t wa = __builtin_convertvector(a, int16x4_t);
    int16x4_t wb = __builtin_convertvector(b, int16x4_t);
    return wa * wb;
}

// --- pwmulu.b: unsigned widening multiply byte -> halfword ---

uint16x4_t test_widen_mulu_b(uint8x4_t a, uint8x4_t b) {
    uint16x4_t wa = __builtin_convertvector(a, uint16x4_t);
    uint16x4_t wb = __builtin_convertvector(b, uint16x4_t);
    return wa * wb;
}

// --- pwmul.h: signed widening multiply halfword -> word ---

int32x2_t test_widen_mul_h(int16x2_t a, int16x2_t b) {
    int32x2_t wa = __builtin_convertvector(a, int32x2_t);
    int32x2_t wb = __builtin_convertvector(b, int32x2_t);
    return wa * wb;
}

// --- pwmulu.h: unsigned widening multiply halfword -> word ---

uint32x2_t test_widen_mulu_h(uint16x2_t a, uint16x2_t b) {
    uint32x2_t wa = __builtin_convertvector(a, uint32x2_t);
    uint32x2_t wb = __builtin_convertvector(b, uint32x2_t);
    return wa * wb;
}

// --- pwmulsu.b: signed * unsigned widening multiply byte ---

int16x4_t test_widen_mulsu_b(int8x4_t a, uint8x4_t b) {
    int16x4_t wa = __builtin_convertvector(a, int16x4_t);
    int16x4_t wb = __builtin_convertvector(b, int16x4_t);
    return wa * wb;
}

int32x2_t test_widen_mulsu_h(int16x2_t a, uint16x2_t b) {
    int32x2_t wa = __builtin_convertvector(a, int32x2_t);
    int32x2_t wb = __builtin_convertvector(b, int32x2_t);
    return wa * wb;
}

/* { dg-final { scan-assembler-times "\\mpwmul\\.b\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpwmulu\\.b\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpwmul\\.h\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpwmulu\\.h\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpwmulsu\\.b\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpwmulsu\\.h\\M" 1 } } */
