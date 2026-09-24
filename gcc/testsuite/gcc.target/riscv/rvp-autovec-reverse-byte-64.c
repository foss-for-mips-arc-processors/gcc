/* { dg-do compile } */
/* { dg-options "-march=rv64gcb_p0p21 -mabi=lp64" } */
 /* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-O1" "-Og" "-Os" "-Oz" } } */

typedef unsigned char uint8x8_t __attribute__((vector_size(8)));

uint8x8_t test_reverse_pv8qi(uint8x8_t a) {
    uint8x8_t result;
    result[0] = a[7];  result[1] = a[6];
    result[2] = a[5];  result[3] = a[4];
    result[4] = a[3];  result[5] = a[2];
    result[6] = a[1];  result[7] = a[0];
    return result;
}

/* Verify instruction counts */
/* { dg-final { scan-assembler-times "\\mrev8\\M" 1 } } */
