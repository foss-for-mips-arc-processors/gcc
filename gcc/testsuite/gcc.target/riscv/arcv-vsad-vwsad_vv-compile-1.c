/* { dg-do compile } */
/* { dg-require-effective-target arcv_vsad } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32im_xarcvvsad -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>

/*
** test_vwsad_vv_i8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,\s*m1,\s*t[au],\s*m[au]
**  arcv\.vwsad\.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vuint16m2_t
test_vwsad_vv_i8 (vuint16m2_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsad_vv_u16m2 (vd, vs1, vs2, vl);
}

/*
** test_vwsad_vv_i8_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,\s*m1,\s*t[au],\s*m[au]
**  arcv\.vwsad\.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vuint16m2_t
test_vwsad_vv_i8_m (vbool8_t mask, vuint16m2_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsad_vv_u16m2_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwsad_vv_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,\s*m1,\s*t[au],\s*m[au]
**  arcv\.vwsad\.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vuint32m2_t
test_vwsad_vv_i16 (vuint32m2_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsad_vv_u32m2 (vd, vs1, vs2, vl);
}

/*
** test_vwsad_vv_i16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,\s*m1,\s*t[au],\s*m[au]
**  arcv\.vwsad\.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vuint32m2_t
test_vwsad_vv_i16_m (vbool16_t mask, vuint32m2_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsad_vv_u32m2_m (mask, vd, vs1, vs2, vl);
}
