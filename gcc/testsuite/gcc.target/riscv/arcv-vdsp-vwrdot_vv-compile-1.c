/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint16m1_t test_vwrdot_vv_i8 (vint16m1_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdot_vv_i8m1_i16m1 (vd, vs1, vs2, vl); }
vint16m1_t test_vwrdot_vv_i8_m (vbool8_t mask, vint16m1_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdot_vv_i8m1_i16m1_m (mask, vd, vs1, vs2, vl); }
vint32m1_t test_vwrdot_vv_i16 (vint32m1_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdot_vv_i16m1_i32m1 (vd, vs1, vs2, vl); }
vint32m1_t test_vwrdot_vv_i16_m (vbool16_t mask, vint32m1_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdot_vv_i16m1_i32m1_m (mask, vd, vs1, vs2, vl); }
vint64m1_t test_vwrdot_vv_i32 (vint64m1_t vd, vint32m1_t vs1, vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdot_vv_i32m1_i64m1 (vd, vs1, vs2, vl); }
vint64m1_t test_vwrdot_vv_i32_m (vbool32_t mask, vint64m1_t vd, vint32m1_t vs1, vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdot_vv_i32m1_i64m1_m (mask, vd, vs1, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwrdot\\.vv" 6 } } */