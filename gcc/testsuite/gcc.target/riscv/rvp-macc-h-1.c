/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-flto" } } */

typedef short int16_t;
typedef int int32_t;
typedef int16_t int16x2_t __attribute__((vector_size(4)));

/* MACC.H00: rd = rd + sext(rs1[15:0]) * sext(rs2[15:0]) */
int32_t test_macc_h00 (int32_t acc, int16x2_t a, int16x2_t b) {
    return acc + (int32_t)a[0] * (int32_t)b[0];
}

/* MACC.H01: rd = rd + sext(rs1[15:0]) * sext(rs2[31:16]) */
int32_t test_macc_h01 (int32_t acc, int16x2_t a, int16x2_t b) {
    return acc + (int32_t)a[0] * (int32_t)b[1];
}

/* MACC.H11: rd = rd + sext(rs1[31:16]) * sext(rs2[31:16]) */
int32_t test_macc_h11 (int32_t acc, int16x2_t a, int16x2_t b) {
    return acc + (int32_t)a[1] * (int32_t)b[1];
}

/* Test with different operand order for h00 */
int32_t test_macc_h00_v2 (int32_t acc, int16x2_t a, int16x2_t b) {
    return (int32_t)a[0] * (int32_t)b[0] + acc;
}

/* Test with different operand order for h01 */
int32_t test_macc_h01_v2 (int32_t acc, int16x2_t a, int16x2_t b) {
    return (int32_t)a[0] * (int32_t)b[1] + acc;
}

/* Test with different operand order for h11 */
int32_t test_macc_h11_v2 (int32_t acc, int16x2_t a, int16x2_t b) {
    return (int32_t)a[1] * (int32_t)b[1] + acc;
}

/* { dg-final { scan-assembler-times "\\mmacc\\.h00\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmacc\\.h01\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmacc\\.h11\\M" 2 } } */
