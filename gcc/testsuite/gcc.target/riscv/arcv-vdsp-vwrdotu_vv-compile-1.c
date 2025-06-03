/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vuint16m1_t test_vwrdotu_vv_u8 (vuint16m1_t vd, vuint8m1_t vs1, vuint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdotu_vv_u8m1_u16m1 (vd, vs1, vs2, vl); }
vuint16m1_t test_vwrdotu_vv_u8_m (vbool8_t mask, vuint16m1_t vd, vuint8m1_t vs1, vuint8m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdotu_vv_u8m1_u16m1_m (mask, vd, vs1, vs2, vl); }
vuint32m1_t test_vwrdotu_vv_u16 (vuint32m1_t vd, vuint16m1_t vs1, vuint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdotu_vv_u16m1_u32m1 (vd, vs1, vs2, vl); }
vuint32m1_t test_vwrdotu_vv_u16_m (vbool16_t mask, vuint32m1_t vd, vuint16m1_t vs1, vuint16m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdotu_vv_u16m1_u32m1_m (mask, vd, vs1, vs2, vl); }
vuint64m1_t test_vwrdotu_vv_u32 (vuint64m1_t vd, vuint32m1_t vs1, vuint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdotu_vv_u32m1_u64m1 (vd, vs1, vs2, vl); }
vuint64m1_t test_vwrdotu_vv_u32_m (vbool32_t mask, vuint64m1_t vd, vuint32m1_t vs1, vuint32m1_t vs2, size_t vl) {
  return __riscv_arcv_vwrdotu_vv_u32m1_u64m1_m (mask, vd, vs1, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwrdotu\\.vv" 6 } } */