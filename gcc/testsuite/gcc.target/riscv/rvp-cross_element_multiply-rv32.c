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



// --- RV32 variants with 4-element byte vectors ---

int16x2_t test_pmul_h_b00_rv32(int8x4_t a, int8x4_t b) {
    // Extract even bytes from 4-byte vectors, sign-extend, multiply
    int16x2_t wa = __builtin_convertvector(
        __builtin_shufflevector(a, a, 0, 2), int16x2_t);
    int16x2_t wb = __builtin_convertvector(
        __builtin_shufflevector(b, b, 0, 2), int16x2_t);
    return wa * wb;
}

int16x2_t test_pmul_h_b00_rv32_2(int8x4_t a, int8x4_t b) {
    int16x2_t wa = (int16x2_t){(int16_t)a[0],(int16_t)a[2]};
    int16x2_t wb = (int16x2_t){(int16_t)b[0],(int16_t)b[2]};
    return wa * wb;
}

int16x2_t test_pmul_h_b01_rv32(int8x4_t a, int8x4_t b) {
    int16x2_t wa = __builtin_convertvector(
        __builtin_shufflevector(a, a, 0, 2), int16x2_t);
    int16x2_t wb = __builtin_convertvector(
        __builtin_shufflevector(b, b, 1, 3), int16x2_t);
    return wa * wb;
}

int16x2_t test_pmul_h_b10_rv32(int8x4_t a, int8x4_t b) {
    int16x2_t wa = __builtin_convertvector(
        __builtin_shufflevector(a, a, 1, 3), int16x2_t);
    int16x2_t wb = __builtin_convertvector(
        __builtin_shufflevector(b, b, 0, 2), int16x2_t);
    return wa * wb;
}

int16x2_t test_pmul_h_b11_rv32(int8x4_t a, int8x4_t b) {
    int16x2_t wa = __builtin_convertvector(
        __builtin_shufflevector(a, a, 1, 3), int16x2_t);
    int16x2_t wb = __builtin_convertvector(
        __builtin_shufflevector(b, b, 1, 3), int16x2_t);
    return wa * wb;
}

/* { dg-final { scan-assembler-times "\\mpmul\\.h\\.b00\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mpmul\\.h\\.b01\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mpmul\\.h\\.b11\\M" 1 } } */
