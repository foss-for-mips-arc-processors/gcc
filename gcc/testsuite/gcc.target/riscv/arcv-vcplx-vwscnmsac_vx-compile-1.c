/* { dg-do compile } */
/* { dg-require-effective-target arcv_vcplx } */
/* { dg-options "-march=rv32im_xarcvvcplx -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint32m2_t test_vwscnmsac_vx_i16 (vint32m2_t vd, int vs1, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vwscnmsac_vx_i32m2 (vd, vs1, vs2, vl); }
vint32m2_t test_vwscnmsac_vx_i16_m (vbool16_t mask, vint32m2_t vd, int vs1, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vwscnmsac_vx_i32m2_m (mask, vd, vs1, vs2, vl); }
vint64m2_t test_vwscnmsac_vx_i32 (vint64m2_t vd, int vs1, vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vwscnmsac_vx_i64m2 (vd, vs1, vs2, vl); }
vint64m2_t test_vwscnmsac_vx_i32_m (vbool32_t mask, vint64m2_t vd, int vs1, vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vwscnmsac_vx_i64m2_m (mask, vd, vs1, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwscnmsac\\.vx" 4 } } */