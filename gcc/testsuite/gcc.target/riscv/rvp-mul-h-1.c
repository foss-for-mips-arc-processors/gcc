/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-flto" } } */

typedef short int16_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef uint16_t uint16x2_t __attribute__((vector_size(4)));

/*
 * MUL.H00: rd = sext(rs1[15:0]) * sext(rs2[15:0])
 * MUL.H11: rd = sext(rs1[31:16]) * sext(rs2[31:16])
 *
 * Signed x Signed widening multiply.
 */

/* MUL.H00: rd = sext(rs1[15:0]) * sext(rs2[15:0]) */
int32_t test_mul_h00 (int16x2_t a, int16x2_t b) {
    return (int32_t)a[0] * (int32_t)b[0];
}

/* Reverse operand order - should still generate mul.h00 */
int32_t test_mul_h00_v2 (int16x2_t a, int16x2_t b) {
    return (int32_t)b[0] * (int32_t)a[0];
}

/* MUL.H11: rd = sext(rs1[31:16]) * sext(rs2[31:16]) */
int32_t test_mul_h11 (int16x2_t a, int16x2_t b) {
    return (int32_t)a[1] * (int32_t)b[1];
}

/* Reverse operand order - should still generate mul.h11 */
int32_t test_mul_h11_v2 (int16x2_t a, int16x2_t b) {
    return (int32_t)b[1] * (int32_t)a[1];
}

/* MUL.H01: rd = sext(rs1[15:0]) * sext(rs2[31:16]) */
int32_t test_mul_h01 (int16x2_t a, int16x2_t b) {
    return (int32_t)a[0] * (int32_t)b[1];
}

/* Reverse operand order - should still generate mul.h01 */
int32_t test_mul_h01_v2 (int16x2_t a, int16x2_t b) {
    return (int32_t)b[1] * (int32_t)a[0];
}

/* { dg-final { scan-assembler-times "\\mmul\\.h00\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmul\\.h11\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmul\\.h01\\M" 2 } } */
