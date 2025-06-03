/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint8m1_t test_vnsra_qv_i8 (vint32m4_t vs2, vint8m1_t vs1, size_t vl) {
  return __riscv_arcv_vnsra_qv_i8m1 (vs2, vs1, vl); }
vint8m1_t test_vnsra_qv_i8_m (vbool8_t mask, vint32m4_t vs2, vint8m1_t vs1, size_t vl) {
  return __riscv_arcv_vnsra_qv_i8m1_m (mask, vs2, vs1, vl); }
vint16m1_t test_vnsra_qv_i16 (vint64m4_t vs2, vint16m1_t vs1, size_t vl) {
  return __riscv_arcv_vnsra_qv_i16m1 (vs2, vs1, vl); }
vint16m1_t test_vnsra_qv_i16_m (vbool16_t mask, vint64m4_t vs2, vint16m1_t vs1, size_t vl) {
  return __riscv_arcv_vnsra_qv_i16m1_m (mask, vs2, vs1, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vnsra\\.qv" 4 } } */