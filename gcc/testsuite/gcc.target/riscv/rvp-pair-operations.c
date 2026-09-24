/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

// Test file for RISC-V P-extension pair operations
// Compiled as C++ (-x c++) for GNU vector operator support
// Instructions tested: ppaire.b, ppaire.h, ppaireo.b, ppaireo.h,
//                      ppairoe.b, ppairoe.h, ppairo.b, ppairo.h

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

// --- ppaire.b: pair even (low) bytes from rs1 and rs2 (RV64) ---
// For each 16-bit group, take low byte from rs1 and rs2

int8x8_t test_ppaire_b(int8x8_t a, int8x8_t b) {
    // {a[0], b[0], a[2], b[2], a[4], b[4], a[6], b[6]}
    return __builtin_shufflevector(a, b, 0, 8, 2, 10, 4, 12, 6, 14);
}

uint8x8_t test_ppaire_b_unsigned(uint8x8_t a, uint8x8_t b) {
    return __builtin_shufflevector(a, b, 0, 8, 2, 10, 4, 12, 6, 14);
}

// --- ppaireo.b: pair even byte from rs1 with odd byte from rs2 (RV64) ---

int8x8_t test_ppaireo_b(int8x8_t a, int8x8_t b) {
    // {a[0], b[1], a[2], b[3], a[4], b[5], a[6], b[7]}
    return __builtin_shufflevector(a, b, 0, 9, 2, 11, 4, 13, 6, 15);
}

// --- ppairoe.b: pair odd byte from rs1 with even byte from rs2 (RV64) ---

int8x8_t test_ppairoe_b(int8x8_t a, int8x8_t b) {
    // {a[1], b[0], a[3], b[2], a[5], b[4], a[7], b[6]}
    return __builtin_shufflevector(a, b, 1, 8, 3, 10, 5, 12, 7, 14);
}

// --- ppairo.b: pair odd (high) bytes from rs1 and rs2 (RV64) ---

int8x8_t test_ppairo_b(int8x8_t a, int8x8_t b) {
    // {a[1], b[1], a[3], b[3], a[5], b[5], a[7], b[7]}
    return __builtin_shufflevector(a, b, 1, 9, 3, 11, 5, 13, 7, 15);
}

// --- ppaire.h: pair even (low) halfwords from rs1 and rs2 (RV64) ---
// For each 32-bit group, take low halfword from rs1 and rs2

int16x4_t test_ppaire_h(int16x4_t a, int16x4_t b) {
    // {a[0], b[0], a[2], b[2]}
    return __builtin_shufflevector(a, b, 0, 4, 2, 6);
}

uint16x4_t test_ppaire_h_unsigned(uint16x4_t a, uint16x4_t b) {
    return __builtin_shufflevector(a, b, 0, 4, 2, 6);
}

// --- ppaireo.h: pair even halfword from rs1 with odd halfword from rs2 (RV64) ---

int16x4_t test_ppaireo_h(int16x4_t a, int16x4_t b) {
    // {a[0], b[1], a[2], b[3]}
    return __builtin_shufflevector(a, b, 0, 5, 2, 7);
}

// --- ppairoe.h: pair odd halfword from rs1 with even halfword from rs2 (RV64) ---

int16x4_t test_ppairoe_h(int16x4_t a, int16x4_t b) {
    // {a[1], b[0], a[3], b[2]}
    return __builtin_shufflevector(a, b, 1, 4, 3, 6);
}

// --- ppairo.h: pair odd (high) halfwords from rs1 and rs2 (RV64) ---

int16x4_t test_ppairo_h(int16x4_t a, int16x4_t b) {
    // {a[1], b[1], a[3], b[3]}
    return __builtin_shufflevector(a, b, 1, 5, 3, 7);
}

// --- RV32 pair operations with 4-element byte vectors ---

int8x4_t test_ppaire_b_4(int8x4_t a, int8x4_t b) {
    // Element-wise construction: {a[0], b[0], a[2], b[2]}
    return (int8x4_t){a[0], b[0], a[2], b[2]};
}

int8x4_t test_ppaireo_b_4(int8x4_t a, int8x4_t b) {
    // {a[0], b[1], a[2], b[3]}
    return (int8x4_t){a[0], b[1], a[2], b[3]};
}

int8x4_t test_ppairoe_b_4(int8x4_t a, int8x4_t b) {
    // {a[1], b[0], a[3], b[2]}
    return (int8x4_t){a[1], b[0], a[3], b[2]};
}

int8x4_t test_ppairo_b_4(int8x4_t a, int8x4_t b) {
    // {a[1], b[1], a[3], b[3]}
    return (int8x4_t){a[1], b[1], a[3], b[3]};
}

// --- RV32 pair operations with 2-element halfword vectors ---

int16x2_t test_ppaire_h_2(int16x2_t a, int16x2_t b) {
    // {a[0], b[0]}
    return (int16x2_t){a[0], b[0]};
}

int16x2_t test_ppaireo_h_2(int16x2_t a, int16x2_t b) {
    // {a[0], b[1]}
    return (int16x2_t){a[0], b[1]};
}

int16x2_t test_ppairo_h_2(int16x2_t a, int16x2_t b) {
    // {a[1], b[1]}
    return (int16x2_t){a[1], b[1]};
}

int16x2_t test_ppairoe_h_2(int16x2_t a, int16x2_t b) {
    // {a[1], b[0]}
    return (int16x2_t){a[1], b[0]};
}

int32x2_t test_ppaire_w_2(int32x2_t a, int32x2_t b) {
    // {a[0], b[0]}
    return (int32x2_t){a[0], b[0]};
}

int32x2_t test_ppaireo_w_2(int32x2_t a, int32x2_t b) {
    // {a[0], b[1]}
    return (int32x2_t){a[0], b[1]};
}

int32x2_t test_ppairo_w_2(int32x2_t a, int32x2_t b) {
    // {a[1], b[1]}
    return (int32x2_t){a[1], b[1]};
}

int32x2_t test_ppairoe_w_2(int32x2_t a, int32x2_t b) {
    // {a[1], b[0]}
    return (int32x2_t){a[1], b[0]};
}

// Consolidated scan-assembler-times for all instructions
/* { dg-final { scan-assembler-times "\\mppaire\\.b\\M" 3 } } */
/* { dg-final { scan-assembler-times "\\mppaireo\\.b\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mppairoe\\.b\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mppairo\\.b\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mppaire\\.h\\M" 3 } } */
/* { dg-final { scan-assembler-times "\\mppaireo\\.h\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mppairoe\\.h\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mppairo\\.h\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mpack\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppaireo\\.w\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppairo\\.w\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppairoe\\.w\\M" 1 } } */
