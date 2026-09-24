/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1"} } */

#include <stdint-gcc.h>

// RV32 vector types (also work on RV64)
typedef int8_t int8x4_t __attribute__((vector_size(4)));
typedef uint8_t uint8x4_t __attribute__((vector_size(4)));
typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef uint16_t uint16x2_t __attribute__((vector_size(4)));

// RV64 vector types
typedef int8_t int8x8_t __attribute__((vector_size(8)));
typedef uint8_t uint8x8_t __attribute__((vector_size(8)));
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef uint16_t uint16x4_t __attribute__((vector_size(8)));
typedef int32_t int32x2_t __attribute__((vector_size(8)));
typedef uint32_t uint32x2_t __attribute__((vector_size(8)));

// CHECK-LABEL: test_pm2add_h_scalar:
// CHECK: pm2add.h
int32_t test_pm2add_h_scalar(int16x2_t a, int16x2_t b) {
    return (int32_t)a[0] * (int32_t)b[0] + (int32_t)a[1] * (int32_t)b[1];
}

// CHECK-LABEL: test_pm2add_hx:
// CHECK: pm2add.hx
int32_t test_pm2add_hx(int16x2_t a, int16x2_t b) {
    return (int32_t)a[0] * (int32_t)b[1] + (int32_t)a[1] * (int32_t)b[0];
}

// --- pm2sub.h: a[0]*b[0] - a[1]*b[1] (scalar, RV32) ---

// CHECK-LABEL: test_pm2sub_h_scalar:
// CHECK: pm2sub.h
int32_t test_pm2sub_h_scalar(int16x2_t a, int16x2_t b) {
    return (int32_t)a[0] * (int32_t)b[0] - (int32_t)a[1] * (int32_t)b[1];
}

// CHECK-LABEL: test_pm2adda_h_scalar:
// CHECK: pm2adda.h
int32_t test_pm2adda_h_scalar(int16x2_t a, int16x2_t b, int32_t acc) {
    return acc + ((int32_t)a[0] * (int32_t)b[0] + (int32_t)a[1] * (int32_t)b[1]);
}

// CHECK-LABEL: test_pm2suba_h_scalar:
// CHECK: pm2suba.h
int32_t test_pm2suba_h_scalar(int16x2_t a, int16x2_t b, int32_t acc) {
    return acc + ((int32_t)a[0] * (int32_t)b[0] - (int32_t)a[1] * (int32_t)b[1]);
}

// CHECK-LABEL: test_pm2sub_hx:
// CHECK: pm2sub.hx
int32_t test_pm2sub_hx(int16x2_t a, int16x2_t b) {
    return (int32_t)a[0] * (int32_t)b[1] - (int32_t)a[1] * (int32_t)b[0];
}

/* { dg-final { scan-assembler-times {\mpm2add\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2add\.hx\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2sub\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2adda\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2suba\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2sub\.hx\M} 1 } } */
