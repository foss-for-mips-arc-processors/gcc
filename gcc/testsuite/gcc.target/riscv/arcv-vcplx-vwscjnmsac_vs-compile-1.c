/* { dg-do compile } */
/* { dg-require-effective-target arcv_vcplx } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvcplx -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>

/*
** test_vwscjnmsac_vs_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint32m2_t
test_vwscjnmsac_vs_i16 (vint32m2_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i32m2 (vd, vs1, vs2, vl);
}

/*
** test_vwscjnmsac_vs_i16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint32m2_t
test_vwscjnmsac_vs_i16_m (vbool16_t mask, vint32m2_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i32m2_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwscjnmsac_vs_i16m2:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m2,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)*arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint32m4_t
test_vwscjnmsac_vs_i16m2 (vint32m4_t vd, vint16m1_t vs2, vint16m2_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i32m4 (vd, vs2, vs1, vl);
}

/*
** test_vwscjnmsac_vs_i16m2_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m2,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)*arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint32m4_t
test_vwscjnmsac_vs_i16m2_m (vbool8_t mask, vint32m4_t vd, vint16m1_t vs2, vint16m2_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i32m4_m (mask, vd, vs2, vs1, vl);
}

/*
** test_vwscjnmsac_vs_i16m4:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m4,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)*arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint32m8_t
test_vwscjnmsac_vs_i16m4 (vint32m8_t vd, vint16m1_t vs2, vint16m4_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i32m8 (vd, vs2, vs1, vl);
}

/*
** test_vwscjnmsac_vs_i16m4_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m4,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)*arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint32m8_t
test_vwscjnmsac_vs_i16m4_m (vbool4_t mask, vint32m8_t vd, vint16m1_t vs2, vint16m4_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i32m8_m (mask, vd, vs2, vs1, vl);
}

/*
** test_vwscjnmsac_vs_i32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint64m2_t
test_vwscjnmsac_vs_i32 (vint64m2_t vd, vint32m1_t vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i64m2 (vd, vs1, vs2, vl);
}

/*
** test_vwscjnmsac_vs_i32_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint64m2_t
test_vwscjnmsac_vs_i32_m (vbool32_t mask, vint64m2_t vd, vint32m1_t vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i64m2_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwscjnmsac_vs_i32m2:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m2,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)*arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint64m4_t
test_vwscjnmsac_vs_i32m2 (vint64m4_t vd, vint32m1_t vs2, vint32m2_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i64m4 (vd, vs2, vs1, vl);
}

/*
** test_vwscjnmsac_vs_i32m2_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m2,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)*arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint64m4_t
test_vwscjnmsac_vs_i32m2_m (vbool16_t mask, vint64m4_t vd, vint32m1_t vs2, vint32m2_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i64m4_m (mask, vd, vs2, vs1, vl);
}

/*
** test_vwscjnmsac_vs_i32m4:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m4,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)*arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint64m8_t
test_vwscjnmsac_vs_i32m4 (vint64m8_t vd, vint32m1_t vs2, vint32m4_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i64m8 (vd, vs2, vs1, vl);
}

/*
** test_vwscjnmsac_vs_i32m4_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m4,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)*arcv.vwscjnmsac.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint64m8_t
test_vwscjnmsac_vs_i32m4_m (vbool8_t mask, vint64m8_t vd, vint32m1_t vs2, vint32m4_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjnmsac_vs_i64m8_m (mask, vd, vs2, vs1, vl);
}
