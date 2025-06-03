/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint16m2_t test_vwsra_vx_i8 (vint8m1_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwsra_vx_i16m2 (vs2, vs1, vl); }
vint16m2_t test_vwsra_vx_i8_m (vbool8_t mask, vint8m1_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwsra_vx_i16m2_m (mask, vs2, vs1, vl); }
vint32m2_t test_vwsra_vx_i16 (vint16m1_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwsra_vx_i32m2 (vs2, vs1, vl); }
vint32m2_t test_vwsra_vx_i16_m (vbool16_t mask, vint16m1_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwsra_vx_i32m2_m (mask, vs2, vs1, vl); }
vint64m2_t test_vwsra_vx_i32 (vint32m1_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwsra_vx_i64m2 (vs2, vs1, vl); }
vint64m2_t test_vwsra_vx_i32_m (vbool32_t mask, vint32m1_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vwsra_vx_i64m2_m (mask, vs2, vs1, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwsra\\.vx" 6 } } */