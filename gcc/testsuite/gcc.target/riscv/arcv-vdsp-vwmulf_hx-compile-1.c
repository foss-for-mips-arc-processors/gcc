/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>

/*
** test_vwmulf_hx_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwmulf.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/

vint32m2_t
test_vwmulf_hx_i16 (vint8mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulf_hx_i32m2 (vs2, vs1, vl);
}

/*
** test_vwmulf_hx_i16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*ma
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwmulf.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vint32m2_t
test_vwmulf_hx_i16_m (vbool16_t mask, vint8mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulf_hx_i32m2_m (mask, vs2, vs1, vl);
}

/*
** test_vwmulf_hx_i16_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*m[au]
**  arcv.vwmulf.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/

vint32m2_t
test_vwmulf_hx_i16_tu (vint32m2_t maskedoff, vint8mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulf_hx_i32m2_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vwmulf_hx_i16_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*mu
**  arcv.vwmulf.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vint32m2_t
test_vwmulf_hx_i16_tumu (vbool16_t mask, vint32m2_t maskedoff, vint8mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulf_hx_i32m2_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vwmulf_hx_i16_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*mu
**  arcv.vwmulf.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vint32m2_t
test_vwmulf_hx_i16_mu (vbool16_t mask, vint32m2_t pass, vint8mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulf_hx_i32m2_mu (mask, pass, vs2, vs1, vl);
}

/*
** test_vwmulf_hx_i32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwmulf.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/

vint64m2_t
test_vwmulf_hx_i32 (vint16mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulf_hx_i64m2 (vs2, vs1, vl);
}

/*
** test_vwmulf_hx_i32_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*ma
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwmulf.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vint64m2_t
test_vwmulf_hx_i32_m (vbool32_t mask, vint16mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulf_hx_i64m2_m (mask, vs2, vs1, vl);
}

/*
** test_vwmulf_hx_i32_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*tu,\s*m[au]
**  arcv.vwmulf.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/

vint64m2_t
test_vwmulf_hx_i32_tu (vint64m2_t maskedoff, vint16mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulf_hx_i64m2_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vwmulf_hx_i32_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*tu,\s*mu
**  arcv.vwmulf.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vint64m2_t
test_vwmulf_hx_i32_tumu (vbool32_t mask, vint64m2_t maskedoff, vint16mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulf_hx_i64m2_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vwmulf_hx_i32_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*mu
**  arcv.vwmulf.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vint64m2_t
test_vwmulf_hx_i32_mu (vbool32_t mask, vint64m2_t pass, vint16mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulf_hx_i64m2_mu (mask, pass, vs2, vs1, vl);
}
