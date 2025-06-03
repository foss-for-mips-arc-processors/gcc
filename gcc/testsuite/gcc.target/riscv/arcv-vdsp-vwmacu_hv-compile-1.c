/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vuint32m2_t test_vwmacu_hv_u16 (vuint32m2_t vd, vuint16m1_t vs1, vuint8mf2_t vs2, size_t vl) {
  return __riscv_arcv_vwmacu_hv_u32m2 (vd, vs1, vs2, vl); }
vuint32m2_t test_vwmacu_hv_u16_m (vbool16_t mask, vuint32m2_t vd, vuint16m1_t vs1, vuint8mf2_t vs2, size_t vl) {
  return __riscv_arcv_vwmacu_hv_u32m2_m (mask, vd, vs1, vs2, vl); }
vuint64m2_t test_vwmacu_hv_u32 (vuint64m2_t vd, vuint32m1_t vs1, vuint16mf2_t vs2, size_t vl) {
  return __riscv_arcv_vwmacu_hv_u64m2 (vd, vs1, vs2, vl); }
vuint64m2_t test_vwmacu_hv_u32_m (vbool32_t mask, vuint64m2_t vd, vuint32m1_t vs1, vuint16mf2_t vs2, size_t vl) {
  return __riscv_arcv_vwmacu_hv_u64m2_m (mask, vd, vs1, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwmacu\\.hv" 4 } } */