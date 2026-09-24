/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1"} } */

#include <stdint-gcc.h>

typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef uint16_t uint16x2_t __attribute__((vector_size(4)));
typedef int32_t int32x2_t __attribute__((vector_size(8)));
typedef uint32_t uint32x2_t __attribute__((vector_size(8)));

int32x2_t test_pwmacc_h(int32x2_t acc, int16x2_t a, int16x2_t b) {
    int32x2_t wa = __builtin_convertvector(a, int32x2_t);
    int32x2_t wb = __builtin_convertvector(b, int32x2_t);
    return acc + wa * wb;
}

uint32x2_t test_pwmaccu_h(uint32x2_t acc, uint16x2_t a, uint16x2_t b) {
    uint32x2_t wa = __builtin_convertvector(a, uint32x2_t);
    uint32x2_t wb = __builtin_convertvector(b, uint32x2_t);
    return acc + wa * wb;
}

int32x2_t test_pwmaccsu_h(int32x2_t acc, int16x2_t a, uint16x2_t b) {
    int32x2_t wa = __builtin_convertvector(a, int32x2_t);
    int32x2_t wb = __builtin_convertvector(b, int32x2_t);
    return acc + wa * wb;
}

/* { dg-final { scan-assembler-times {\mpwmacc\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpwmaccu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpwmaccsu\.h\M} 1 } } */
