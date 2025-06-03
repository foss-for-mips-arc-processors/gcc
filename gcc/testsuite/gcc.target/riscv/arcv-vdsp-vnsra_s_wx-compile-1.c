/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint8m1_t test_vnsra_s_wx_i8 (vint16m2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vnsra_s_wx_i8m1 (vs2, vs1, vl); }
vint8m1_t test_vnsra_s_wx_i8_m (vbool8_t mask, vint16m2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vnsra_s_wx_i8m1_m (mask, vs2, vs1, vl); }
vint16m1_t test_vnsra_s_wx_i16 (vint32m2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vnsra_s_wx_i16m1 (vs2, vs1, vl); }
vint16m1_t test_vnsra_s_wx_i16_m (vbool16_t mask, vint32m2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vnsra_s_wx_i16m1_m (mask, vs2, vs1, vl); }
vint32m1_t test_vnsra_s_wx_i32 (vint64m2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vnsra_s_wx_i32m1 (vs2, vs1, vl); }
vint32m1_t test_vnsra_s_wx_i32_m (vbool32_t mask, vint64m2_t vs2, int vs1, size_t vl) {
  return __riscv_arcv_vnsra_s_wx_i32m1_m (mask, vs2, vs1, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vnsra\\.s\\.wx" 6 } } */