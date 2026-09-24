/* { dg-do compile } */
/* { dg-options "-march=rv64gcbp0p21 -mabi=lp64" } */
/* { dg-skip-if "" { *-*-* } { "-O0" } } */

/* Test PLI.B/PLI.H with CONST_VECTOR on RV64.
   Use 8-byte vectors to ensure the 64-bit replicated value matches.
   4-byte vectors on RV64 cannot use PLI because the 64-bit broadcast
   result would not match the 32-bit target value.  */

typedef signed char int8x8_t __attribute__((vector_size(8)));
typedef unsigned char uint8x8_t __attribute__((vector_size(8)));
typedef short int16x4_t __attribute__((vector_size(8)));
typedef unsigned short uint16x4_t __attribute__((vector_size(8)));

/* Test PLI.B with 8-byte CONST_VECTOR on RV64 */
int8x8_t test_pli_b_positive (void) {
    return (int8x8_t){42, 42, 42, 42, 42, 42, 42, 42};
}

int8x8_t test_pli_b_negative (void) {
    return (int8x8_t){-5, -5, -5, -5, -5, -5, -5, -5};
}

uint8x8_t test_pli_b_unsigned (void) {
    return (uint8x8_t){200, 200, 200, 200, 200, 200, 200, 200};
}

/* Test PLI.H with 8-byte CONST_VECTOR on RV64 */
int16x4_t test_pli_h_positive (void) {
    return (int16x4_t){100, 100, 100, 100};
}

int16x4_t test_pli_h_negative (void) {
    return (int16x4_t){-100, -100, -100, -100};
}

uint16x4_t test_pli_h_unsigned (void) {
    return (uint16x4_t){500, 500, 500, 500};
}

/* { dg-final { scan-assembler-times "pli\\.b" 3 } } */
/* { dg-final { scan-assembler-times "pli\\.h" 3 } } */

