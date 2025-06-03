/* { dg-do compile } */
/* { dg-require-effective-target arcv_vsad } */
/* { dg-options "-march=rv32im_xarcvvsad -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vuint16m2_t test_vwsadu_vv_u8 (vuint8m1_t vs2, vuint8m1_t vs1, size_t vl) {
  return __riscv_arcv_vwsadu_vv_u16m2 (vs2, vs1, vl); }
vuint16m2_t test_vwsadu_vv_u8_m (vbool8_t mask, vuint8m1_t vs2, vuint8m1_t vs1, size_t vl) {
  return __riscv_arcv_vwsadu_vv_u16m2_m (mask, vs2, vs1, vl); }
vuint32m2_t test_vwsadu_vv_u16 (vuint16m1_t vs2, vuint16m1_t vs1, size_t vl) {
  return __riscv_arcv_vwsadu_vv_u32m2 (vs2, vs1, vl); }
vuint32m2_t test_vwsadu_vv_u16_m (vbool16_t mask, vuint16m1_t vs2, vuint16m1_t vs1, size_t vl) {
  return __riscv_arcv_vwsadu_vv_u32m2_m (mask, vs2, vs1, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwsadu\\.vv" 4 } } */