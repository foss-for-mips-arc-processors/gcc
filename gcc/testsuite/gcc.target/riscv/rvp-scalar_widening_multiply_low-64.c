/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-O1" "-Os" "-Oz" "-Og" } } */

#include <stdint-gcc.h>

int64_t test_mul_w00_sext_sext_inreg(int32_t a, int64_t b) {
    int64_t a_sext = (int64_t)a;
    int64_t b_sext = (int64_t)(int32_t)b;
    return a_sext * b_sext;
}

uint64_t test_mulu_w00_zext_and(uint32_t a, uint64_t b) {
    uint64_t a_zext = (uint64_t)a;
    uint64_t b_and = b & 0xFFFFFFFFull;
    return a_zext * b_and;
}

int64_t test_mulsu_w00_sext_inreg_zext(int64_t a, uint32_t b) {
    int64_t a_sext = (int64_t)(int32_t)a;
    int64_t b_zext = (int64_t)b;
    return a_sext * b_zext;
}

/* { dg-final { scan-assembler-times "\\mmul\\.w00\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mmulu\\.w00\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mmulsu\\.w00\\M" 1 } } */
