/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" "-flto" } } */

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef uint16_t uint16x2_t __attribute__((vector_size(4)));

/* MACCU.H00: rd = rd + zext(rs1[15:0]) * zext(rs2[15:0]) */
uint32_t test_maccu_h00 (uint32_t acc, uint16x2_t a, uint16x2_t b) {
    return acc + (uint32_t)a[0] * (uint32_t)b[0];
}

/* MACCU.H01: rd = rd + zext(rs1[15:0]) * zext(rs2[31:16]) */
uint32_t test_maccu_h01 (uint32_t acc, uint16x2_t a, uint16x2_t b) {
    return acc + (uint32_t)a[0] * (uint32_t)b[1];
}

/* MACCU.H11: rd = rd + zext(rs1[31:16]) * zext(rs2[31:16]) */
uint32_t test_maccu_h11 (uint32_t acc, uint16x2_t a, uint16x2_t b) {
    return acc + (uint32_t)a[1] * (uint32_t)b[1];
}

/* Test with different operand order */
uint32_t test_maccu_h00_v2 (uint32_t acc, uint16x2_t a, uint16x2_t b) {
    return (uint32_t)a[0] * (uint32_t)b[0] + acc;
}

uint32_t test_maccu_h01_v2 (uint32_t acc, uint16x2_t a, uint16x2_t b) {
    return (uint32_t)a[0] * (uint32_t)b[1] + acc;
}

uint32_t test_maccu_h11_v2 (uint32_t acc, uint16x2_t a, uint16x2_t b) {
    return (uint32_t)a[1] * (uint32_t)b[1] + acc;
}

/* { dg-final { scan-assembler-times "\\mmaccu\\.h00\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmaccu\\.h01\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmaccu\\.h11\\M" 2 } } */
