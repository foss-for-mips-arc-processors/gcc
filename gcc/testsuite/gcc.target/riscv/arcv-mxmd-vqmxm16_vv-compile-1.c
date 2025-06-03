/* { dg-do compile } */
/* { dg-require-effective-target arcv_mxmd } */
/* { dg-options "-march=rv32im_xarcvmxmd -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint32m4_t test_vqmxm16_vv_i8 (vint32m4_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vqmxm16_vv_i32m4 (vd, vs1, vs2, vl); }
vint32m4_t test_vqmxm16_vv_i8_m (vbool8_t mask, vint32m4_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vqmxm16_vv_i32m4_m (mask, vd, vs1, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vqmxm16\\.vv" 2 } } */