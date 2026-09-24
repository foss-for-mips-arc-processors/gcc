/* Test PAS/PSA (packed add-subtract) instructions.  */
/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } } */

typedef short int16_t;
typedef int int32_t;
typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef int32_t int32x2_t __attribute__((vector_size(8)));

/* pas.hx for V2HI: rd[0] = a[0] + b[0], rd[1] = a[1] - b[1] */
int16x2_t test_pas_hx_v2hi(int16x2_t a, int16x2_t b) {
    return (int16x2_t){
        (int16_t)(a[0] + b[0]),
        (int16_t)(a[1] - b[1])
    };
}

/* psa.hx for V2HI: rd[0] = a[0] - b[0], rd[1] = a[1] + b[1] */
int16x2_t test_psa_hx_v2hi(int16x2_t a, int16x2_t b) {
    return (int16x2_t){
        (int16_t)(a[0] - b[0]),
        (int16_t)(a[1] + b[1])
    };
}

/* pas.hx for V4HI (RV64 only) */
int16x4_t test_pas_hx_v4hi(int16x4_t a, int16x4_t b) {
    return (int16x4_t){
        (int16_t)(a[0] + b[0]),
        (int16_t)(a[1] - b[1]),
        (int16_t)(a[2] + b[2]),
        (int16_t)(a[3] - b[3])
    };
}

/* psa.hx for V4HI (RV64 only) */
int16x4_t test_psa_hx_v4hi(int16x4_t a, int16x4_t b) {
    return (int16x4_t){
        (int16_t)(a[0] - b[0]),
        (int16_t)(a[1] + b[1]),
        (int16_t)(a[2] - b[2]),
        (int16_t)(a[3] + b[3])
    };
}

/* pas.wx for V2SI (RV64 only) */
int32x2_t test_pas_wx_v2si(int32x2_t a, int32x2_t b) {
    return (int32x2_t){
        (int32_t)(a[0] + b[0]),
        (int32_t)(a[1] - b[1])
    };
}

/* psa.wx for V2SI (RV64 only) */
int32x2_t test_psa_wx_v2si(int32x2_t a, int32x2_t b) {
    return (int32x2_t){
        (int32_t)(a[0] - b[0]),
        (int32_t)(a[1] + b[1])
    };
}

/* { dg-final { scan-assembler-times "pas\\.hx" 2 } } */
/* { dg-final { scan-assembler-times "psa\\.hx" 2 } } */
/* { dg-final { scan-assembler-times "pas\\.wx" 1 } } */
/* { dg-final { scan-assembler-times "psa\\.wx" 1 } } */
