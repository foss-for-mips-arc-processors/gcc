/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;

/* RV32 uses register pairs for 8-byte vectors */
typedef int8_t int8x8_t __attribute__((vector_size(8)));
typedef uint8_t uint8x8_t __attribute__((vector_size(8)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef uint16_t uint16x4_t __attribute__((vector_size(8)));

/* 4-byte vectors (single register on RV32) */
typedef int8_t int8x4_t __attribute__((vector_size(4)));
typedef uint8_t uint8x4_t __attribute__((vector_size(4)));
typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef uint16_t uint16x2_t __attribute__((vector_size(4)));

/* ====== 8-byte vectors (register pairs) ====== */

/* pabd.db: signed byte absolute difference, 8 elements */
int8x8_t test_pabd_db_8(int8x8_t a, int8x8_t b) {
    int8x8_t mask = a > b;
    int8x8_t max = (mask & a) | (~mask & b);
    int8x8_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* pabdu.db: unsigned byte absolute difference, 8 elements */
uint8x8_t test_pabdu_db_8(uint8x8_t a, uint8x8_t b) {
    uint8x8_t mask = a > b;
    uint8x8_t max = (mask & a) | (~mask & b);
    uint8x8_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* pabd.dh: signed halfword absolute difference, 4 elements */
int16x4_t test_pabd_dh_4(int16x4_t a, int16x4_t b) {
    int16x4_t mask = a > b;
    int16x4_t max = (mask & a) | (~mask & b);
    int16x4_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* pabdu.dh: unsigned halfword absolute difference, 4 elements */
uint16x4_t test_pabdu_dh_4(uint16x4_t a, uint16x4_t b) {
    uint16x4_t mask = a > b;
    uint16x4_t max = (mask & a) | (~mask & b);
    uint16x4_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* ====== 4-byte vectors (single register) ====== */

/* pabd.b: signed byte absolute difference, 4 elements */
int8x4_t test_pabd_b_4(int8x4_t a, int8x4_t b) {
    int8x4_t mask = a > b;
    int8x4_t max = (mask & a) | (~mask & b);
    int8x4_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* pabdu.b: unsigned byte absolute difference, 4 elements */
uint8x4_t test_pabdu_b_4(uint8x4_t a, uint8x4_t b) {
    uint8x4_t mask = a > b;
    uint8x4_t max = (mask & a) | (~mask & b);
    uint8x4_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* pabd.h: signed halfword absolute difference, 2 elements */
int16x2_t test_pabd_h_2(int16x2_t a, int16x2_t b) {
    int16x2_t mask = a > b;
    int16x2_t max = (mask & a) | (~mask & b);
    int16x2_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* pabdu.h: unsigned halfword absolute difference, 2 elements */
uint16x2_t test_pabdu_h_2(uint16x2_t a, uint16x2_t b) {
    uint16x2_t mask = a > b;
    uint16x2_t max = (mask & a) | (~mask & b);
    uint16x2_t min = (mask & b) | (~mask & a);
    return max - min;
}

/* Verify register-pair instructions use .db/.dh suffixes on RV32 */
/* { dg-final { scan-assembler-times {\tpabd\.db\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpabdu\.db\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpabd\.dh\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpabdu\.dh\t} 1 } } */

/* Verify single-register instructions use .b/.h suffixes on RV32 */
/* { dg-final { scan-assembler-times {\tpabd\.b\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpabdu\.b\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpabd\.h\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpabdu\.h\t} 1 } } */
