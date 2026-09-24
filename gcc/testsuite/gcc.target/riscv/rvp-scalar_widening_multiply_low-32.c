/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-O1" "-Os" "-Oz" "-Og" } } */

#include <stdint-gcc.h>

int32_t test_mul_h00_sext_sext_inreg(int16_t a, int32_t b) {
    int32_t a_sext = (int32_t)a;
    int32_t b_sext = (int32_t)(int16_t)b;
    return a_sext * b_sext;
}

uint32_t test_mulu_h00_zext_and(uint16_t a, uint32_t b) {
    uint32_t a_zext = (uint32_t)a;
    uint32_t b_and = b & 0xFFFFu;
    return a_zext * b_and;
}

int32_t test_mulsu_h00_sext_and(int16_t a, uint32_t b) {
    int32_t a_sext = (int32_t)a;
    uint32_t b_and = (uint32_t)(b & 0xFFFFu);
    return a_sext * b_and;
}

int32_t test_mulsu_h00_sext_inreg_zext(int32_t a, uint16_t b) {
    int32_t a_sext = (int32_t)(int16_t)a;
    uint32_t b_zext = (uint32_t)b;
    return a_sext * b_zext;
}

/* { dg-final { scan-assembler-times "\\mmul\\.h00\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mmulu\\.h00\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mmulsu\\.h00\\M" 2 } } */
