/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-flto" } } */

#include <stdint-gcc.h>

// RV32 vector types
typedef int8_t int8x4_t __attribute__((vector_size(4)));
typedef uint8_t uint8x4_t __attribute__((vector_size(4)));

int8x4_t test_rev_2byte_pv4qi(int8x4_t a) {
    return __builtin_shufflevector(a, a, 2, 3, 0, 1);
}

uint8x4_t test_rev_2byte_pv4qi_unsigned(uint8x4_t a) {
    return __builtin_shufflevector(a, a, 2, 3, 0, 1);
}


/* rev16 is RV64-only and reverses the halfwords of the whole 64-bit register;
   ppairoe.h swaps them per 32-bit word, which is what PV4QI needs.  */
/* { dg-final { scan-assembler-times "\\mppairoe\\.h\\M" 2 } } */
/* { dg-final { scan-assembler-not "\\mrev16\\M" } } */
