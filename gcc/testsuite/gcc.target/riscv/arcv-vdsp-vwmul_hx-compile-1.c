/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint32m2_t test_vwmul_hx_i16 (vint8mf2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwmul_hx_i32m2 (vs2, vs1, vl); }
vint32m2_t test_vwmul_hx_i16_m (vbool16_t mask, vint8mf2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwmul_hx_i32m2_m (mask, vs2, vs1, vl); }
vint64m2_t test_vwmul_hx_i32 (vint16mf2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwmul_hx_i64m2 (vs2, vs1, vl); }
vint64m2_t test_vwmul_hx_i32_m (vbool32_t mask, vint16mf2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwmul_hx_i64m2_m (mask, vs2, vs1, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwmul\\.hx" 4 } } */