/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint16m1_t test_vsmulf_hx_i16 (vint8mf2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vsmulf_hx_i16m1 (vs2, vs1, vl); }
vint16m1_t test_vsmulf_hx_i16_m (vbool16_t mask, vint8mf2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vsmulf_hx_i16m1_m (mask, vs2, vs1, vl); }
vint32m1_t test_vsmulf_hx_i32 (vint16mf2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vsmulf_hx_i32m1 (vs2, vs1, vl); }
vint32m1_t test_vsmulf_hx_i32_m (vbool32_t mask, vint16mf2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vsmulf_hx_i32m1_m (mask, vs2, vs1, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vsmulf\\.hx" 4 } } */