/* Narrowing permutes have no P extension form and must not reach the
   RVP vec_perm_const expanders, which build the result in the operand
   mode.  */
/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O3" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } } */

#include <stdint-gcc.h>

typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef int32_t int32x2_t __attribute__((vector_size(8)));

int32x2_t test_pm2add_h(int16x4_t a, int16x4_t b) {
    return (int32x2_t){
        (int32_t)a[0] * (int32_t)b[0] + (int32_t)a[1] * (int32_t)b[1],
        (int32_t)a[2] * (int32_t)b[2] + (int32_t)a[3] * (int32_t)b[3]
    };
}
