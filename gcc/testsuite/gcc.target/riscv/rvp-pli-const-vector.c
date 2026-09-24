/* { dg-do compile } */
/* { dg-options "-march=rv32gcbp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-O0" } } */

typedef signed char int8x4_t __attribute__((vector_size(4)));
typedef unsigned char uint8x4_t __attribute__((vector_size(4)));
typedef short int16x2_t __attribute__((vector_size(4)));
typedef unsigned short uint16x2_t __attribute__((vector_size(4)));

/* Test PLI.B with CONST_VECTOR */
int8x4_t test_pli_b_positive (void) {
    return (int8x4_t){42, 42, 42, 42};
}

int8x4_t test_pli_b_negative (void) {
    return (int8x4_t){-5, -5, -5, -5};
}

uint8x4_t test_pli_b_unsigned (void) {
    return (uint8x4_t){200, 200, 200, 200};
}

/* Test PLI.H with CONST_VECTOR */
int16x2_t test_pli_h_positive (void) {
    return (int16x2_t){100, 100};
}

int16x2_t test_pli_h_negative (void) {
    return (int16x2_t){-100, -100};
}

uint16x2_t test_pli_h_unsigned (void) {
    return (uint16x2_t){500, 500};
}

/* { dg-final { scan-assembler-times "pli\\.b" 3 } } */
/* { dg-final { scan-assembler-times "pli\\.h" 3 } } */

