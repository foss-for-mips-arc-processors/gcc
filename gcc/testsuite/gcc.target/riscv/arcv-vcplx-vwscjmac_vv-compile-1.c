/* { dg-do compile } */
/* { dg-require-effective-target arcv_vcplx } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32im_xarcvvcplx -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>

/*
** test_vwscjmac_vv_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv.vwscjmac.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint32m2_t
test_vwscjmac_vv_i16 (vint32m2_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwscjmac_vv_i32m2 (vd, vs1, vs2, vl);
}

/*
** test_vwscjmac_vv_i16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv.vwscjmac.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint32m2_t
test_vwscjmac_vv_i16_m (vbool16_t mask, vint32m2_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwscjmac_vv_i32m2_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwscjmac_vv_i32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv.vwscjmac.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint64m2_t
test_vwscjmac_vv_i32 (vint64m2_t vd, vint32m1_t vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwscjmac_vv_i64m2 (vd, vs1, vs2, vl);
}

/*
** test_vwscjmac_vv_i32_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv.vwscjmac.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint64m2_t
test_vwscjmac_vv_i32_m (vbool32_t mask, vint64m2_t vd, vint32m1_t vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwscjmac_vv_i64m2_m (mask, vd, vs1, vs2, vl);
}
