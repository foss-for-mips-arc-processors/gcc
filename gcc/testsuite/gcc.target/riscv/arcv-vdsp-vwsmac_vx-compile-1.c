/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint16m2_t test_vwsmac_vx_i8 (vint16m2_t vd, int vs1, vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vwsmac_vx_i16m2 (vd, vs1, vs2, vl); }
vint16m2_t test_vwsmac_vx_i8_m (vbool8_t mask, vint16m2_t vd, int vs1, vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vwsmac_vx_i16m2_m (mask, vd, vs1, vs2, vl); }
vint32m2_t test_vwsmac_vx_i16 (vint32m2_t vd, int vs1, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vwsmac_vx_i32m2 (vd, vs1, vs2, vl); }
vint32m2_t test_vwsmac_vx_i16_m (vbool16_t mask, vint32m2_t vd, int vs1, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vwsmac_vx_i32m2_m (mask, vd, vs1, vs2, vl); }
vint64m2_t test_vwsmac_vx_i32 (vint64m2_t vd, int vs1, vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vwsmac_vx_i64m2 (vd, vs1, vs2, vl); }
vint64m2_t test_vwsmac_vx_i32_m (vbool32_t mask, vint64m2_t vd, int vs1, vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vwsmac_vx_i64m2_m (mask, vd, vs1, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwsmac\\.vx" 6 } } */