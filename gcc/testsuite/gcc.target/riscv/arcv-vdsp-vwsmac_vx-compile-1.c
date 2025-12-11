/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>

/*
** test_vwsmac_vx_i8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/

vint16m2_t
test_vwsmac_vx_i8 (vint16m2_t vd, int vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i16m2 (vd, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i8_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*ma
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/

vint16m2_t
test_vwsmac_vx_i8_m (vbool8_t mask, vint16m2_t vd, int vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i16m2_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i8_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*tu,\s*m[au]
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/

vint16m2_t
test_vwsmac_vx_i8_tu (vint16m2_t maskedoff, int vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i16m2_tu (maskedoff, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i8_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*tu,\s*mu
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/

vint16m2_t
test_vwsmac_vx_i8_tumu (vbool8_t mask, vint16m2_t maskedoff, int vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i16m2_tumu (mask, maskedoff, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i8_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*mu
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/

vint16m2_t
test_vwsmac_vx_i8_mu (vbool8_t mask, vint16m2_t pass, int vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i16m2_mu (mask, pass, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/

vint32m2_t
test_vwsmac_vx_i16 (vint32m2_t vd, int vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i32m2 (vd, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*ma
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/

vint32m2_t
test_vwsmac_vx_i16_m (vbool16_t mask, vint32m2_t vd, int vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i32m2_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i16_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*m[au]
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/

vint32m2_t
test_vwsmac_vx_i16_tu (vint32m2_t maskedoff, int vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i32m2_tu (maskedoff, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i16_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*mu
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/

vint32m2_t
test_vwsmac_vx_i16_tumu (vbool16_t mask, vint32m2_t maskedoff, int vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i32m2_tumu (mask, maskedoff, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i16_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*mu
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/

vint32m2_t
test_vwsmac_vx_i16_mu (vbool16_t mask, vint32m2_t pass, int vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i32m2_mu (mask, pass, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/

vint64m2_t
test_vwsmac_vx_i32 (vint64m2_t vd, int vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i64m2 (vd, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i32_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*ma
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/

vint64m2_t
test_vwsmac_vx_i32_m (vbool32_t mask, vint64m2_t vd, int vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i64m2_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i32_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*tu,\s*m[au]
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/

vint64m2_t
test_vwsmac_vx_i32_tu (vint64m2_t maskedoff, int vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i64m2_tu (maskedoff, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i32_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*tu,\s*mu
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/

vint64m2_t
test_vwsmac_vx_i32_tumu (vbool32_t mask, vint64m2_t maskedoff, int vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i64m2_tumu (mask, maskedoff, vs1, vs2, vl);
}

/*
** test_vwsmac_vx_i32_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*mu
**  arcv.vwsmac.vx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/

vint64m2_t
test_vwsmac_vx_i32_mu (vbool32_t mask, vint64m2_t pass, int vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwsmac_vx_i64m2_mu (mask, pass, vs1, vs2, vl);
}
