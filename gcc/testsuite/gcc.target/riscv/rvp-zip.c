/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-flto" } } */

#include <stdint-gcc.h>

// RV64 vector types
typedef int8_t int8x8_t __attribute__((vector_size(8)));
typedef uint8_t uint8x8_t __attribute__((vector_size(8)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef uint16_t uint16x4_t __attribute__((vector_size(8)));

// --- zip8p: interleave bytes from low halves (RV64) ---

int8x8_t test_zip8_p(int8x8_t a, int8x8_t b) {
    // {a[0],b[0], a[1],b[1], a[2],b[2], a[3],b[3]}
    return __builtin_shufflevector(a, b, 0, 8, 1, 9, 2, 10, 3, 11);
}

uint8x8_t test_zip8_p_unsigned(uint8x8_t a, uint8x8_t b) {
    return __builtin_shufflevector(a, b, 0, 8, 1, 9, 2, 10, 3, 11);
}

// --- zip8hp: interleave bytes from high halves (RV64) ---

int8x8_t test_zip8_hp(int8x8_t a, int8x8_t b) {
    // {a[4],b[4], a[5],b[5], a[6],b[6], a[7],b[7]}
    return __builtin_shufflevector(a, b, 4, 12, 5, 13, 6, 14, 7, 15);
}

uint8x8_t test_zip8_hp_unsigned(uint8x8_t a, uint8x8_t b) {
    return __builtin_shufflevector(a, b, 4, 12, 5, 13, 6, 14, 7, 15);
}

// --- zip16p: interleave halfwords from low halves (RV64) ---

int16x4_t test_zip16_p(int16x4_t a, int16x4_t b) {
    return __builtin_shufflevector(a, b, 0, 4, 1, 5);
}

uint16x4_t test_zip16_p_unsigned(uint16x4_t a, uint16x4_t b) {
    return __builtin_shufflevector(a, b, 0, 4, 1, 5);
}

// --- zip16hp: interleave halfwords from high halves (RV64) ---

int16x4_t test_zip16_hp(int16x4_t a, int16x4_t b) {
    return __builtin_shufflevector(a, b, 2, 6, 3, 7);
}

uint16x4_t test_zip16_hp_unsigned(uint16x4_t a, uint16x4_t b) {
    return __builtin_shufflevector(a, b, 2, 6, 3, 7);
}

// Consolidated scan-assembler-times for all instructions
/* { dg-final { scan-assembler-times "\\mzip8p\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mzip8hp\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mzip16p\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mzip16hp\\M" 2 } } */
