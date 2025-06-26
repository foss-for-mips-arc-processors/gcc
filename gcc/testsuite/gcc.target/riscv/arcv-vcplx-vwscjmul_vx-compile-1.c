/* { dg-do compile } */
/* { dg-require-effective-target arcv_vcplx } */
/* { dg-options "-march=rv32im_xarcvvcplx -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint32m2_t test_vwscjmul_vx_i16 (vint16m1_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwscjmul_vx_i32m2 (vs2, vs1, vl); }
vint32m2_t test_vwscjmul_vx_i16_m (vbool16_t mask, vint16m1_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwscjmul_vx_i32m2_m (mask, vs2, vs1, vl); }
vint64m2_t test_vwscjmul_vx_i32 (vint32m1_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwscjmul_vx_i64m2 (vs2, vs1, vl); }
vint64m2_t test_vwscjmul_vx_i32_m (vbool32_t mask, vint32m1_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwscjmul_vx_i64m2_m (mask, vs2, vs1, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwscjmul\\.vx" 4 } } */