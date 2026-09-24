/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-flto" } } */

typedef int int32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef int32_t int32x2_t __attribute__((vector_size(8)));
typedef uint32_t uint32x2_t __attribute__((vector_size(8)));

/*
 * MUL.W00: rd = sext(rs1[31:0]) * sext(rs2[31:0])
 * MUL.W11: rd = sext(rs1[63:32]) * sext(rs2[63:32])
 *
 * Signed x Signed widening multiply.
 */

/* MUL.W00: rd = sext(rs1[31:0]) * sext(rs2[31:0]) */
int64_t test_mul_w00 (int32x2_t a, int32x2_t b) {
    return (int64_t)a[0] * (int64_t)b[0];
}

/* Reverse operand order - should still generate mul.w00 */
int64_t test_mul_w00_v2 (int32x2_t a, int32x2_t b) {
    return (int64_t)b[0] * (int64_t)a[0];
}

/* MUL.W11: rd = sext(rs1[63:32]) * sext(rs2[63:32]) */
int64_t test_mul_w11 (int32x2_t a, int32x2_t b) {
    return (int64_t)a[1] * (int64_t)b[1];
}

/* Reverse operand order - should still generate mul.w11 */
int64_t test_mul_w11_v2 (int32x2_t a, int32x2_t b) {
    return (int64_t)b[1] * (int64_t)a[1];
}

/* MUL.W01: rd = sext(rs1[31:0]) * sext(rs2[63:32]) */
int64_t test_mul_w01 (int32x2_t a, int32x2_t b) {
    return (int64_t)a[0] * (int64_t)b[1];
}

/* Reverse operand order - should still generate mul.w01 */
int64_t test_mul_w01_v2 (int32x2_t a, int32x2_t b) {
    return (int64_t)b[1] * (int64_t)a[0];
}

/* { dg-final { scan-assembler-times "\\mmul\\.w00\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmul\\.w11\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmul\\.w01\\M" 2 } } */
