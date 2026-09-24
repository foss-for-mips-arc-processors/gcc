/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */

/* Test match.pd optimizations that transform absolute difference idioms
   into the canonical max - min form, enabling pabd/pabdu instructions.

   Patterns tested:
   1. Unsigned: (a > b ? a - b : b - a) -> pabdu via vec_cond
   2. Signed: abs(a - b) -> pabd via abs(minus)  */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;

typedef int8_t int8x8_t __attribute__((vector_size(8)));
typedef uint8_t uint8x8_t __attribute__((vector_size(8)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef uint16_t uint16x4_t __attribute__((vector_size(8)));

/* Unsigned ternary: (a > b ? a - b : b - a) -> pabdu */

uint8x8_t test_pabdu_b_8(uint8x8_t a, uint8x8_t b) {
    return a > b ? a - b : b - a;
}

uint16x4_t test_pabdu_h_4(uint16x4_t a, uint16x4_t b) {
    return a > b ? a - b : b - a;
}

/* Signed abs(diff): abs(a - b) -> pabd */

int8x8_t test_pabd_b_8(int8x8_t a, int8x8_t b) {
    int8x8_t diff = a - b;
    return diff < 0 ? -diff : diff;
}

int16x4_t test_pabd_h_4(int16x4_t a, int16x4_t b) {
    int16x4_t diff = a - b;
    return diff < 0 ? -diff : diff;
}

/* { dg-final { scan-assembler {\tpabdu\.b\t} } } */
/* { dg-final { scan-assembler {\tpabdu\.h\t} } } */
/* { dg-final { scan-assembler {\tpabd\.b\t} } } */
/* { dg-final { scan-assembler {\tpabd\.h\t} } } */
