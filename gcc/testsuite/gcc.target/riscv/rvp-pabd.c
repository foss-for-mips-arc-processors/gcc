/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */

/* Test P-extension PABD (Packed Absolute Difference) instructions.
   pabd.b/h: signed absolute difference
   pabdu.b/h: unsigned absolute difference

   Tests both 8-byte and 4-byte packed vector operations.  */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;

typedef int8_t int8x8_t __attribute__((vector_size(8)));
typedef uint8_t uint8x8_t __attribute__((vector_size(8)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef uint16_t uint16x4_t __attribute__((vector_size(8)));
typedef int8_t int8x4_t __attribute__((vector_size(4)));
typedef uint8_t uint8x4_t __attribute__((vector_size(4)));
typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef uint16_t uint16x2_t __attribute__((vector_size(4)));

/* 8-byte vectors: pabd.b */
int8x8_t test_pabd_b_8(int8x8_t a, int8x8_t b) {
    int8x8_t mask = a > b;
    int8x8_t max = (mask & a) | (~mask & b);
    int8x8_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* 8-byte vectors: pabdu.b */
uint8x8_t test_pabdu_b_8(uint8x8_t a, uint8x8_t b) {
    uint8x8_t mask = a > b;
    uint8x8_t max = (mask & a) | (~mask & b);
    uint8x8_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* 8-byte vectors: pabd.h */
int16x4_t test_pabd_h_4(int16x4_t a, int16x4_t b) {
    int16x4_t mask = a > b;
    int16x4_t max = (mask & a) | (~mask & b);
    int16x4_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* 8-byte vectors: pabdu.h */
uint16x4_t test_pabdu_h_4(uint16x4_t a, uint16x4_t b) {
    uint16x4_t mask = a > b;
    uint16x4_t max = (mask & a) | (~mask & b);
    uint16x4_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* 4-byte vectors: pabd.b */
int8x4_t test_pabd_b_4(int8x4_t a, int8x4_t b) {
    int8x4_t mask = a > b;
    int8x4_t max = (mask & a) | (~mask & b);
    int8x4_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* 4-byte vectors: pabdu.b */
uint8x4_t test_pabdu_b_4(uint8x4_t a, uint8x4_t b) {
    uint8x4_t mask = a > b;
    uint8x4_t max = (mask & a) | (~mask & b);
    uint8x4_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* 4-byte vectors: pabd.h */
int16x2_t test_pabd_h_2(int16x2_t a, int16x2_t b) {
    int16x2_t mask = a > b;
    int16x2_t max = (mask & a) | (~mask & b);
    int16x2_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* 4-byte vectors: pabdu.h */
uint16x2_t test_pabdu_h_2(uint16x2_t a, uint16x2_t b) {
    uint16x2_t mask = a > b;
    uint16x2_t max = (mask & a) | (~mask & b);
    uint16x2_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* { dg-final { scan-assembler-times {\tpabd\.b\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpabdu\.b\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpabd\.h\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpabdu\.h\t} 2 } } */