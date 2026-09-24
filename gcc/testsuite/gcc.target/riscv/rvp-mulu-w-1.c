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
 * MULU.W00: rd = zext(rs1[31:0]) * zext(rs2[31:0])
 * MULU.W11: rd = zext(rs1[63:32]) * zext(rs2[63:32])
 *
 *Unsigned x Unsigned widening multiply.
 */

/* MULU.W00: rd = zext(rs1[31:0]) * zext(rs2[31:0]) */
uint64_t test_mulu_w00 (uint32x2_t a, uint32x2_t b) {
    return (uint64_t)a[0] * (uint64_t)b[0];
}

/* Reverse operand order - should still generate mulu.w00 */
uint64_t test_mulu_w00_v2 (uint32x2_t a, uint32x2_t b) {
    return (uint64_t)b[0] * (uint64_t)a[0];
}

/* MULU.W11: rd = zext(rs1[63:32]) * zext(rs2[63:32]) */
uint64_t test_mulu_w11 (uint32x2_t a, uint32x2_t b) {
    return (uint64_t)a[1] * (uint64_t)b[1];
}

/* Reverse operand order - should still generate mulu.w11 */
uint64_t test_mulu_w11_v2 (uint32x2_t a, uint32x2_t b) {
    return (uint64_t)b[1] * (uint64_t)a[1];
}

/* MULU.W01: rd = zext(rs1[31:0]) * zext(rs2[63:32]) */
uint64_t test_mulu_w01 (uint32x2_t a, uint32x2_t b) {
    return (uint64_t)a[0] * (uint64_t)b[1];
}

/* Reverse operand order - should still generate mulu.w01 */
uint64_t test_mulu_w01_v2 (uint32x2_t a, uint32x2_t b) {
    return (uint64_t)b[1] * (uint64_t)a[0];
}

/* { dg-final { scan-assembler-times "\\mmulu\\.w00\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmulu\\.w11\\M" 2 } } */
/* { dg-final { scan-assembler-times "\\mmulu\\.w01\\M" 2 } } */
