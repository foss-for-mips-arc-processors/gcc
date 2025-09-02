/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint8m1_t test_vmv_s_v_i8m1 (vint8m1_t vd, int vs1, vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vmv_s_v_i8m1_i8m1 (vd, vs1, vs2, vl); }
vint8m1_t test_vmv_s_v_i8m2 (vint8m1_t vd, int vs1, vint8m2_t vs2, size_t vl) {
  return __riscv_arcv_vmv_s_v_i8m2_i8m1 (vd, vs1, vs2, vl); }
vint8m1_t test_vmv_s_v_i8m4 (vint8m1_t vd, int vs1, vint8m4_t vs2, size_t vl) {
  return __riscv_arcv_vmv_s_v_i8m4_i8m1 (vd, vs1, vs2, vl); }
vint16m1_t test_vmv_s_v_i16m1 (vint16m1_t vd, int vs1, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vmv_s_v_i16m1_i16m1 (vd, vs1, vs2, vl); }
vint32m1_t test_vmv_s_v_i32m1 (vint32m1_t vd, int vs1, vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vmv_s_v_i32m1_i32m1 (vd, vs1, vs2, vl); }
vint32m1_t test_vmv_s_v_i32m2 (vint32m1_t vd, int vs1, vint32m2_t vs2, size_t vl) {
  return __riscv_arcv_vmv_s_v_i32m2_i32m1 (vd, vs1, vs2, vl); }
vint64m1_t test_vmv_s_v_i64m1 (vint64m1_t vd, int vs1, vint64m1_t vs2, size_t vl) {
  return __riscv_arcv_vmv_s_v_i64m1_i64m1 (vd, vs1, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vmv\\.s\\.v" 7 } } */
