/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1"} } */

#include <stdint-gcc.h>

// RV32 vector types
typedef int16_t int16x2_t __attribute__((vector_size(4)));
typedef uint16_t uint16x2_t __attribute__((vector_size(4)));

// RV64 vector types (register pair on RV32)
typedef int16_t int16x4_t __attribute__((vector_size(8)));
typedef uint16_t uint16x4_t __attribute__((vector_size(8)));
typedef int32_t int32x2_t __attribute__((vector_size(8)));
typedef uint32_t uint32x2_t __attribute__((vector_size(8)));

// --- pm2wadd.h: widening 2-element dot product (RV32 scalar) ---
// rdp = rs1.h[0]*rs2.h[0] + rs1.h[1]*rs2.h[1]  (result is 32-bit / register pair)

// CHECK-LABEL: test_pm2wadd_h_scalar:
// CHECK: pm2wadd.h
int64_t test_pm2wadd_h_scalar(int16x2_t a, int16x2_t b) {
    return (int64_t)(int32_t)a[0] * (int64_t)(int32_t)b[0] + (int64_t)(int32_t)a[1] * (int64_t)(int32_t)b[1];
}

// --- pm2wsub.h: widening 2-element cross-subtract ---

// CHECK-LABEL: test_pm2wsub_h_scalar:
// CHECK: pm2wsub.h
int64_t test_pm2wsub_h_scalar(int16x2_t a, int16x2_t b) {
    return (int64_t)(int32_t)a[0] * (int64_t)(int32_t)b[0] - (int64_t)(int32_t)a[1] * (int64_t)(int32_t)b[1];
}

// --- pm2wadd.hx: cross variant (swapped rs2 halfwords) ---
// rdp.w[i] = rs1.h[2i] * rs2.h[2i+1] + rs1.h[2i+1] * rs2.h[2i]

// CHECK-LABEL: test_pm2wadd_hx_scalar:
// CHECK: pm2wadd.hx
int64_t test_pm2wadd_hx_scalar(int16x2_t a, int16x2_t b) {
    return (int64_t)(int32_t)a[0] * (int64_t)(int32_t)b[1] + (int64_t)(int32_t)a[1] * (int64_t)(int32_t)b[0];
}

/* { dg-final { scan-assembler-times {\mpm2wadd\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2wadd\.hx\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpm2wsub\.h\M} 1 } } */
