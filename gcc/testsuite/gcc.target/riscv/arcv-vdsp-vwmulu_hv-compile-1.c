/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vuint32m2_t test_vwmulu_hv_u16 (vuint8mf2_t vs2, vuint16m1_t vs1, size_t vl) {
  return __riscv_arcv_vwmulu_hv_u32m2 (vs2, vs1, vl); }
vuint32m2_t test_vwmulu_hv_u16_m (vbool16_t mask, vuint8mf2_t vs2, vuint16m1_t vs1, size_t vl) {
  return __riscv_arcv_vwmulu_hv_u32m2_m (mask, vs2, vs1, vl); }
vuint64m2_t test_vwmulu_hv_u32 (vuint16mf2_t vs2, vuint32m1_t vs1, size_t vl) {
  return __riscv_arcv_vwmulu_hv_u64m2 (vs2, vs1, vl); }
vuint64m2_t test_vwmulu_hv_u32_m (vbool32_t mask, vuint16mf2_t vs2, vuint32m1_t vs1, size_t vl) {
  return __riscv_arcv_vwmulu_hv_u64m2_m (mask, vs2, vs1, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwmulu\\.hv" 4 } } */