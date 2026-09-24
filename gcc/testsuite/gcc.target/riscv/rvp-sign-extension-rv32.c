/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2 -Wno-riscv-implicit-extension-version" } */
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

// --- psext.h.b: sign-extend bytes to halfwords (RV32: 2 bytes -> 2 halfwords) ---

// CHECK-LABEL: test_psext_h_b_rv32:
// CHECK: psext.h.b

int16x2_t test_psext_h_b_rv32(int8x4_t a) {
    // Extract lower 2 bytes, sign-extend each to halfword
    int16_t lo = a[0];
    int16_t hi = a[2];
    return (int16x2_t){lo, hi};
}

// --- psext.h.b: sign-extend bytes to halfwords (RV64: 4 bytes -> 4 halfwords) ---

// CHECK-LABEL: test_psext_dh_b_rv32:
// CHECK: psext.dh.b
int16x4_t test_psext_dh_b_rv32(int8x4_t a) {
    // Sign-extend 4 bytes to 4 halfwords using __builtin_convertvector
    return __builtin_convertvector(a, int16x4_t);
}

// CHECK-LABEL: test_psext_dh_b_rv32_unsigned:
// CHECK: pzext.dh.b
uint16x4_t test_psext_dh_b_rv32_unsigned(uint8x4_t a) {
    // Zero-extend 4 bytes to 4 halfwords using __builtin_convertvector
    return __builtin_convertvector(a, uint16x4_t);
}

// CHECK-LABEL: test_psext_w_h_rv32:
// CHECK: psext.dw.h
int32x2_t test_psext_dw_h_rv32(int16x2_t a) {
    // Sign-extend 2 halfwords to 2 words using __builtin_convertvector
    return __builtin_convertvector(a, int32x2_t);
}

// CHECK-LABEL: test_psext_w_h_rv32_unsigned:
// CHECK: pzext.dw.h
uint32x2_t test_psext_dw_h_rv32_unsigned(uint16x2_t a) {
    // Zero-extend 2 halfwords to 2 words using __builtin_convertvector
    return __builtin_convertvector(a, uint32x2_t);
}

// CHECK-LABEL: test_psext_h_b_convert:
// CHECK: psext.h.b
int16x2_t test_psext_h_b_convert(int8x4_t a) {
    // Use a 2-element byte vector and convert
    typedef int8_t int8x2_t __attribute__((vector_size(2)));
    int8x2_t narrow = {a[0], a[2]};
    return __builtin_convertvector(narrow, int16x2_t);
}

// Consolidated scan-assembler-times for all instructions
/* { dg-final { scan-assembler-times "\\mpsext\\.h\\.b\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mpsext\\.dh\\.b\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpzext\\.dh\\.b\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpsext\\.dw\\.h\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mpzext\\.dw\\.h\\M" 1 } } */
