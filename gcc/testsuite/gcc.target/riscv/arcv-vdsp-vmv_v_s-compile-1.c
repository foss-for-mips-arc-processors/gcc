/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint8m1_t test_vmv_v_s_i8 (vint8m1_t vd, int vs1, vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vmv_v_s_i8m1 (vd, vs1, vs2, vl); }
vint16m1_t test_vmv_v_s_i16 (vint16m1_t vd, int vs1, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vmv_v_s_i16m1 (vd, vs1, vs2, vl); }
vint32m1_t test_vmv_v_s_i32 (vint32m1_t vd, int vs1, vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vmv_v_s_i32m1 (vd, vs1, vs2, vl); }
vint64m1_t test_vmv_v_s_i64 (vint64m1_t vd, int vs1, vint64m1_t vs2, size_t vl) {
  return __riscv_arcv_vmv_v_s_i64m1 (vd, vs1, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vmv\\.v\\.s" 4 } } */