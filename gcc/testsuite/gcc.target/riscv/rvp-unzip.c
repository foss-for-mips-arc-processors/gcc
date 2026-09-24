/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-flto" } } */

#include <stdint-gcc.h>

// RV64 vector types
typedef int8_t int8x8_t __attribute__((vector_size(8)));
typedef uint8_t uint8x8_t __attribute__((vector_size(8)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef uint16_t uint16x4_t __attribute__((vector_size(8)));

// --- unzip8p: de-interleave even bytes (RV64) ---

int8x8_t test_unzip8_p(int8x8_t a, int8x8_t b) {
    // {a[0],a[2],a[4],a[6], b[0],b[2],b[4],b[6]}
    return __builtin_shufflevector(a, b, 0, 2, 4, 6, 8, 10, 12, 14);
}

uint8x8_t test_unzip8_p_unsigned(uint8x8_t a, uint8x8_t b) {
    return __builtin_shufflevector(a, b, 0, 2, 4, 6, 8, 10, 12, 14);
}

// --- unzip8hp: de-interleave odd bytes (RV64) ---

int8x8_t test_unzip8_hp(int8x8_t a, int8x8_t b) {
    // {a[1],a[3],a[5],a[7], b[1],b[3],b[5],b[7]}
    return __builtin_shufflevector(a, b, 1, 3, 5, 7, 9, 11, 13, 15);
}

uint8x8_t test_unzip8_hp_unsigned(uint8x8_t a, uint8x8_t b) {
    return __builtin_shufflevector(a, b, 1, 3, 5, 7, 9, 11, 13, 15);
}

// --- unzip16p: de-interleave even halfwords (RV64) ---

int16x4_t test_unzip16_p(int16x4_t a, int16x4_t b) {
    return __builtin_shufflevector(a, b, 0, 2, 4, 6);
}

uint16x4_t test_unzip16_p_unsigned(uint16x4_t a, uint16x4_t b) {
    return __builtin_shufflevector(a, b, 0, 2, 4, 6);
}

// --- unzip16hp: de-interleave odd halfwords (RV64) ---

int16x4_t test_unzip16_hp(int16x4_t a, int16x4_t b) {
    return __builtin_shufflevector(a, b, 1, 3, 5, 7);
}

uint16x4_t test_unzip16_hp_unsigned(uint16x4_t a, uint16x4_t b) {
    return __builtin_shufflevector(a, b, 1, 3, 5, 7);
}

// Consolidated scan-assembler-times for all instructions
/* { dg-final { scan-assembler-times "\\munzip8p\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\munzip8hp\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\munzip16p\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\munzip16hp\\M" 2 } } */
