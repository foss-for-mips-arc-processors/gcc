/* { dg-do compile } */
/* { dg-require-effective-target arcv_vcplx } */
/* { dg-options "-march=rv32im_xarcvvcplx -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint16m1_t test_veven_v_i16 (vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_veven_v_i16m1 (vs2, vl); }
vint16m1_t test_veven_v_i16_m (vbool16_t mask, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_veven_v_i16m1_m (mask, vs2, vl); }
vint32m1_t test_veven_v_i32 (vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_veven_v_i32m1 (vs2, vl); }
vint32m1_t test_veven_v_i32_m (vbool32_t mask, vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_veven_v_i32m1_m (mask, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.veven\\.v" 4 } } */