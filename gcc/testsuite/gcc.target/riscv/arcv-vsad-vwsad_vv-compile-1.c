/* { dg-do compile } */
/* { dg-require-effective-target arcv_vsad } */
/* { dg-options "-march=rv32im_xarcvvsad -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vuint16m2_t test_vwsad_vv_i8 (vuint16m2_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vwsad_vv_u16m2 (vd, vs1, vs2, vl); }
vuint16m2_t test_vwsad_vv_i8_m (vbool8_t mask, vuint16m2_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vwsad_vv_u16m2_m (mask, vd, vs1, vs2, vl); }
vuint32m2_t test_vwsad_vv_i16 (vuint32m2_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vwsad_vv_u32m2 (vd, vs1, vs2, vl); }
vuint32m2_t test_vwsad_vv_i16_m (vbool16_t mask, vuint32m2_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vwsad_vv_u32m2_m (mask, vd, vs1, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwsad\\.vv" 4 } } */
