/* Test PAS/PSA (packed add-subtract) instructions on RV32.  */
/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } } */

#include <stdint-gcc.h>

typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));

int16x2_t test_pas_hx_v2hi(int16x2_t a, int16x2_t b) {
    return (int16x2_t){
        (int16_t)(a[0] + b[0]),
        (int16_t)(a[1] - b[1])
    };
}

int16x2_t test_psa_hx_v2hi(int16x2_t a, int16x2_t b) {
    return (int16x2_t){
        (int16_t)(a[0] - b[0]),
        (int16_t)(a[1] + b[1])
    };
}

/* PV4HI is a register pair on RV32, so these use the double-wide form.  */
int16x4_t test_pas_dhx_v4hi(int16x4_t a, int16x4_t b) {
    return (int16x4_t){
        (int16_t)(a[0] + b[0]),
        (int16_t)(a[1] - b[1]),
        (int16_t)(a[2] + b[2]),
        (int16_t)(a[3] - b[3])
    };
}

int16x4_t test_psa_dhx_v4hi(int16x4_t a, int16x4_t b) {
    return (int16x4_t){
        (int16_t)(a[0] - b[0]),
        (int16_t)(a[1] + b[1]),
        (int16_t)(a[2] - b[2]),
        (int16_t)(a[3] + b[3])
    };
}

/* { dg-final { scan-assembler-times "pas\\.hx" 1 } } */
/* { dg-final { scan-assembler-times "psa\\.hx" 1 } } */
/* { dg-final { scan-assembler-times "pas\\.dhx" 1 } } */
/* { dg-final { scan-assembler-times "psa\\.dhx" 1 } } */
