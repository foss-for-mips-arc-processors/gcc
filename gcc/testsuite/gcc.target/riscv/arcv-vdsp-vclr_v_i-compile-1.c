/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint8m1_t test_vclr_v_i_i8 (vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vclr_v_i_i8m1 (vs2, 1, vl); }
vint8m1_t test_vclr_v_i_i8_m (vbool8_t mask, vint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vclr_v_i_i8m1_m (mask, vs2, 1, vl); }
vint16m1_t test_vclr_v_i_i16 (vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vclr_v_i_i16m1 (vs2, 1, vl); }
vint16m1_t test_vclr_v_i_i16_m (vbool16_t mask, vint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vclr_v_i_i16m1_m (mask, vs2, 1, vl); }
vint32m1_t test_vclr_v_i_i32 (vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vclr_v_i_i32m1 (vs2, 1, vl); }
vint32m1_t test_vclr_v_i_i32_m (vbool32_t mask, vint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vclr_v_i_i32m1_m (mask, vs2, 1, vl); }
vint64m1_t test_vclr_v_i_i64 (vint64m1_t vs2, size_t vl) {
  return __riscv_arcv_vclr_v_i_i64m1 (vs2, 1, vl); }
vint64m1_t test_vclr_v_i_i64_m (vbool64_t mask, vint64m1_t vs2, size_t vl) {
  return __riscv_arcv_vclr_v_i_i64m1_m (mask, vs2, 1, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vclr\\.v\\.i" 8 } } */