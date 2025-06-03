/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32" } */

#include <stddef.h>
#include <riscv_vector.h>

vint32m2_t test_vwmac_hx_i16 (vint32m2_t vd, int vs1, vint8mf2_t vs2, size_t vl) {
  return __riscv_arcv_vwmac_hx_i32m2 (vd, vs1, vs2, vl); }
vint32m2_t test_vwmac_hx_i16_m (vbool16_t mask, vint32m2_t vd, int vs1, vint8mf2_t vs2, size_t vl) {
  return __riscv_arcv_vwmac_hx_i32m2_m (mask, vd, vs1, vs2, vl); }
vint64m2_t test_vwmac_hx_i32 (vint64m2_t vd, int vs1, vint16mf2_t vs2, size_t vl) {
  return __riscv_arcv_vwmac_hx_i64m2 (vd, vs1, vs2, vl); }
vint64m2_t test_vwmac_hx_i32_m (vbool32_t mask, vint64m2_t vd, int vs1, vint16mf2_t vs2, size_t vl) {
  return __riscv_arcv_vwmac_hx_i64m2_m (mask, vd, vs1, vs2, vl); }

/* { dg-final { scan-assembler-times "arcv\\.vwmac\\.hx" 4 } } */