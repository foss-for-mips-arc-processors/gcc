/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint8m1_t test_vsra_vv_i8 (vint8m1_t vs2, vint8m1_t vs1, size_t vl) {
  return __riscv_arcv_vsra_vv_i8m1 (vs2, vs1, vl); }
vint8m1_t test_vsra_vv_i8_m (vbool8_t mask, vint8m1_t vs2, vint8m1_t vs1, size_t vl) {
  return __riscv_arcv_vsra_vv_i8m1_m (mask, vs2, vs1, vl); }
vint16m1_t test_vsra_vv_i16 (vint16m1_t vs2, vint16m1_t vs1, size_t vl) {
  return __riscv_arcv_vsra_vv_i16m1 (vs2, vs1, vl); }
vint16m1_t test_vsra_vv_i16_m (vbool16_t mask, vint16m1_t vs2, vint16m1_t vs1, size_t vl) {
  return __riscv_arcv_vsra_vv_i16m1_m (mask, vs2, vs1, vl); }
vint32m1_t test_vsra_vv_i32 (vint32m1_t vs2, vint32m1_t vs1, size_t vl) {
  return __riscv_arcv_vsra_vv_i32m1 (vs2, vs1, vl); }
vint32m1_t test_vsra_vv_i32_m (vbool32_t mask, vint32m1_t vs2, vint32m1_t vs1, size_t vl) {
  return __riscv_arcv_vsra_vv_i32m1_m (mask, vs2, vs1, vl); }
vint64m1_t test_vsra_vv_i64 (vint64m1_t vs2, vint64m1_t vs1, size_t vl) {
  return __riscv_arcv_vsra_vv_i64m1 (vs2, vs1, vl); }
vint64m1_t test_vsra_vv_i64_m (vbool64_t mask, vint64m1_t vs2, vint64m1_t vs1, size_t vl) {
  return __riscv_arcv_vsra_vv_i64m1_m (mask, vs2, vs1, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vsra\\.vv" 8 } } */