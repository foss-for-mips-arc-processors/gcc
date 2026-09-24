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
 * MULSU.H00: rd = sext(rs1[15:0]) * zext(rs2[15:0])
 * MULSU.H11: rd = sext(rs1[31:16]) * zext(rs2[31:16])
 *
 * Signed x Unsigned widening multiply.
 * Uses the standard usmulhisi3 pattern from GCC internals.
 */

/* MULSU.H00: rd = sext(rs1[15:0]) * zext(rs2[15:0]) */
int32_t test_mulsu_h00 (int16x2_t a, uint16x2_t b) {
    return (int32_t)a[0] * (int32_t)(uint32_t)b[0];
}

/* Reverse operand order - should still generate mulsu.h00 */
int32_t test_mulsu_h00_v2 (int16x2_t a, uint16x2_t b) {
    return (int32_t)(uint32_t)b[0] * (int32_t)a[0];
}

/* MULSU.H11: rd = sext(rs1[31:16]) * zext(rs2[31:16]) */
int32_t test_mulsu_h11 (int16x2_t a, uint16x2_t b) {
    return (int32_t)a[1] * (int32_t)(uint32_t)b[1];
}

/* Reverse operand order - should still generate mulsu.h11 */
int32_t test_mulsu_h11_v2 (int16x2_t a, uint16x2_t b) {
    return (int32_t)(uint32_t)b[1] * (int32_t)a[1];
}

/* { dg-final { scan-assembler-times "\\mmulsu\\.h00\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmulsu\\.h11\\M" 2 } } */
