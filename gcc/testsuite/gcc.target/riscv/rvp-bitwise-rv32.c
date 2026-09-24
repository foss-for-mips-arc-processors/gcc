/* { dg-do compile } */
/* { dg-options "-march=rv32gcbp0p21 -mabi=ilp32 -O2 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

/* Test bitwise AND/OR/XOR/NOT on 8-byte packed vectors on RV32.
   On RV32, 8-byte vectors use register pairs; each operation must split
   into two 32-bit instructions (one per half).  */

typedef signed char int8x8_t __attribute__((vector_size(8)));
typedef short int16x4_t __attribute__((vector_size(8)));
typedef int int32x2_t __attribute__((vector_size(8)));

int8x8_t test_and_8qi (int8x8_t a, int8x8_t b) { return a & b; }
int16x4_t test_and_4hi (int16x4_t a, int16x4_t b) { return a & b; }
int32x2_t test_and_2si (int32x2_t a, int32x2_t b) { return a & b; }

int8x8_t test_or_8qi (int8x8_t a, int8x8_t b) { return a | b; }
int16x4_t test_or_4hi (int16x4_t a, int16x4_t b) { return a | b; }
int32x2_t test_or_2si (int32x2_t a, int32x2_t b) { return a | b; }

int8x8_t test_xor_8qi (int8x8_t a, int8x8_t b) { return a ^ b; }
int16x4_t test_xor_4hi (int16x4_t a, int16x4_t b) { return a ^ b; }
int32x2_t test_xor_2si (int32x2_t a, int32x2_t b) { return a ^ b; }

int8x8_t test_not_8qi (int8x8_t a) { return ~a; }
int16x4_t test_not_4hi (int16x4_t a) { return ~a; }
int32x2_t test_not_2si (int32x2_t a) { return ~a; }

/* Each operation on a 3-mode register pair splits into 2 SI instructions.  */
/* { dg-final { scan-assembler-times {\tand\t} 6 } } */
/* { dg-final { scan-assembler-times {\tor\t}  6 } } */
/* { dg-final { scan-assembler-times {\txor\t} 6 } } */
/* { dg-final { scan-assembler-times {\tnot\t} 6 } } */
