/* { dg-do compile } */
/* { dg-options "-march=rv32gcb_p0p21 -mabi=ilp32" } */
 /* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-O1" "-Og" "-Os" "-Oz" } } */

typedef unsigned char uint8x4_t __attribute__((vector_size(4)));

uint8x4_t test_reverse_pv4qi(uint8x4_t a) {
    uint8x4_t result;
    result[0] = a[3];  result[1] = a[2];
    result[2] = a[1];  result[3] = a[0];
    return result;
}

/* Verify instruction counts */
/* { dg-final { scan-assembler-times "\\mrev8\\M" 1 } } */
