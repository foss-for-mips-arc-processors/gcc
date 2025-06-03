/* { dg-do compile } */
/* { dg-require-effective-target arcv_mxmc } */
/* { dg-options "-march=rv32im_xarcvmxmc -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vuint32m4_t test_vqmxm8u_vv_u8 (vuint32m4_t vd, vuint8m1_t vs1, vuint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vqmxm8u_vv_u32m4 (vd, vs1, vs2, vl); }
vuint32m4_t test_vqmxm8u_vv_u8_m (vbool8_t mask, vuint32m4_t vd, vuint8m1_t vs1, vuint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vqmxm8u_vv_u32m4_m (mask, vd, vs1, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vqmxm8u\\.vv" 2 } } */