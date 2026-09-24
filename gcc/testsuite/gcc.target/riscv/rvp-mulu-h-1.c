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
 * MULU.H00: rd = zext(rs1[15:0]) * zext(rs2[15:0])
 * MULU.H11: rd = zext(rs1[31:16]) * zext(rs2[31:16])
 *
 * Unsigned x Unsigned widening multiply.
 */

/* MULU.H00: rd = zext(rs1[15:0]) * zext(rs2[15:0]) */
uint32_t test_mulu_h00 (uint16x2_t a, uint16x2_t b) {
    return (uint32_t)a[0] * (uint32_t)b[0];
}

/* Reverse operand order - should still generate mulu.h00 */
uint32_t test_mulu_h00_v2 (uint16x2_t a, uint16x2_t b) {
    return (uint32_t)b[0] * (uint32_t)a[0];
}

/* MULU.H11: rd = zext(rs1[31:16]) * zext(rs2[31:16]) */
uint32_t test_mulu_h11 (uint16x2_t a, uint16x2_t b) {
    return (uint32_t)a[1] * (uint32_t)b[1];
}

/* Reverse operand order - should still generate mulu.h11 */
uint32_t test_mulu_h11_v2 (uint16x2_t a, uint16x2_t b) {
    return (uint32_t)b[1] * (uint32_t)a[1];
}

/* MULU.H01: rd = zext(rs1[15:0]) * zext(rs2[31:16]) */
uint32_t test_mulu_h01 (uint16x2_t a, uint16x2_t b) {
    return (uint32_t)a[0] * (uint32_t)b[1];
}

/* Reverse operand order - should still generate mulu.h01 */
uint32_t test_mulu_h01_v2 (uint16x2_t a, uint16x2_t b) {
    return (uint32_t)b[1] * (uint32_t)a[0];
}

/* { dg-final { scan-assembler-times "\\mmulu\\.h00\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmulu\\.h11\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmulu\\.h01\\M" 2 } } */
