/* { dg-do compile } */
/* { dg-require-effective-target arcv_vsad } */
/* { dg-options "-march=rv32im_xarcvvsad -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint16m2_t test_vwsad_vv_i8 (vint8m1_t vs2, vint8m1_t vs1, size_t vl) {
  return __riscv_arcv_vwsad_vv_i16m2 (vs2, vs1, vl); }
vint16m2_t test_vwsad_vv_i8_m (vbool8_t mask, vint8m1_t vs2, vint8m1_t vs1, size_t vl) {
  return __riscv_arcv_vwsad_vv_i16m2_m (mask, vs2, vs1, vl); }
vint32m2_t test_vwsad_vv_i16 (vint16m1_t vs2, vint16m1_t vs1, size_t vl) {
  return __riscv_arcv_vwsad_vv_i32m2 (vs2, vs1, vl); }
vint32m2_t test_vwsad_vv_i16_m (vbool16_t mask, vint16m1_t vs2, vint16m1_t vs1, size_t vl) {
  return __riscv_arcv_vwsad_vv_i32m2_m (mask, vs2, vs1, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwsad\\.vv" 4 } } */