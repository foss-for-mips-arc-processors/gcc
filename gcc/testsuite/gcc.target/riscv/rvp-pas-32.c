/* PAS/PSA are CROSS add-subtract instructions (PAS.HX: rd[even] =
   rs1[even] - rs2[odd], rd[odd] = rs1[odd] + rs2[even]), used for complex
   number arithmetic.  There is no P instruction for same-lane mixed
   add/subtract, so these must NOT be compiled into pas/psa.  */
/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p6 -mabi=ilp32 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } } */

typedef short int16_t;
typedef int int32_t;
typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef int32_t int32x2_t __attribute__((vector_size(8)));

int16x2_t test_same_lane_v2hi (int16x2_t a, int16x2_t b) {
    return (int16x2_t){
        (int16_t)(a[0] + b[0]),
        (int16_t)(a[1] - b[1])
    };
}

int16x4_t test_same_lane_v4hi (int16x4_t a, int16x4_t b) {
    return (int16x4_t){
        (int16_t)(a[0] + b[0]),
        (int16_t)(a[1] - b[1]),
        (int16_t)(a[2] + b[2]),
        (int16_t)(a[3] - b[3])
    };
}

int32x2_t test_same_lane_v2si (int32x2_t a, int32x2_t b) {
    return (int32x2_t){
        (int32_t)(a[0] + b[0]),
        (int32_t)(a[1] - b[1])
    };
}

/* { dg-final { scan-assembler-not "pas\\.hx" } } */
/* { dg-final { scan-assembler-not "psa\\.hx" } } */
/* { dg-final { scan-assembler-not "pas\\.dhx" } } */
/* { dg-final { scan-assembler-not "psa\\.dhx" } } */
