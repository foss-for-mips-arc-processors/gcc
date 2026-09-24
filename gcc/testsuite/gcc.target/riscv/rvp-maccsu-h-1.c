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
 * MACCSU.H00: rd = rd + sext(rs1[15:0]) * zext(rs2[15:0])
 * MACCSU.H11: rd = rd + sext(rs1[31:16]) * zext(rs2[31:16])
 *
 * These patterns match via combine pass:
 * - H00: uses usmulhisi3 pattern (unsigned x signed widening multiply)
 * - H11: uses shift patterns (ashiftrt x lshiftrt)
 */

/* MACCSU.H00: rd = rd + sext(rs1[15:0]) * zext(rs2[15:0]) */
int32_t test_maccsu_h00 (int32_t acc, int16x2_t a, uint16x2_t b) {
    return acc + (int32_t)a[0] * (int32_t)(uint32_t)b[0];
}

int32_t test_maccsu_h00_v2 (int32_t acc, int16x2_t a, uint16x2_t b) {
    return (int32_t)a[0] * (int32_t)(uint32_t)b[0] + acc;
}

/* Reverse operand order: unsigned x signed */
int32_t test_maccsu_h00_alt (int32_t acc, int16x2_t a, uint16x2_t b) {
    return acc + (int32_t)(uint32_t)b[0] * (int32_t)a[0];
}

/* MACCSU.H11: rd = rd + sext(rs1[31:16]) * zext(rs2[31:16]) */
int32_t test_maccsu_h11 (int32_t acc, int16x2_t a, uint16x2_t b) {
    return acc + (int32_t)a[1] * (int32_t)(uint32_t)b[1];
}

int32_t test_maccsu_h11_v2 (int32_t acc, int16x2_t a, uint16x2_t b) {
    return (int32_t)a[1] * (int32_t)(uint32_t)b[1] + acc;
}

/* Reverse operand order: unsigned x signed */
int32_t test_maccsu_h11_alt (int32_t acc, int16x2_t a, uint16x2_t b) {
    return acc + (int32_t)(uint32_t)b[1] * (int32_t)a[1];
}

/* { dg-final { scan-assembler-times "\\mmaccsu\\.h00\\M" 3 } } */
/* { dg-final { scan-assembler-times "\\mmaccsu\\.h11\\M" 3 } } */
