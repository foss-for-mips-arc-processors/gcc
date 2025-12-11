/* { dg-do compile } */
/* { dg-require-effective-target arcv_vcplx } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvcplx -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>

/*
** test_vwscjmul_vs_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/
vint32m2_t
test_vwscjmul_vs_i16 (vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m2 (vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*ma
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/
vint32m2_t
test_vwscjmul_vs_i16_m (vbool16_t mask, vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m2_m (mask, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*m[au]
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/
vint32m2_t
test_vwscjmul_vs_i16_tu (vint32m2_t maskedoff, vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m2_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/
vint32m2_t
test_vwscjmul_vs_i16_tumu (vbool16_t mask, vint32m2_t maskedoff, vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m2_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/
vint32m2_t
test_vwscjmul_vs_i16_mu (vbool16_t mask, vint32m2_t pass, vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m2_mu (mask, pass, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16m2:
**  vsetivli\s+zero,\s*[0-9]+,\s*e16,m2,\s*t[au],\s*m[au]
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetivli\s+zero,\s*[0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m2,\s*t[au],\s*m[au]
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint32m4_t
test_vwscjmul_vs_i16m2 (vint16m2_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m4 (vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16m2_m:
**  vsetivli\s+zero,\s*[0-9]+,\s*e16,m2,\s*t[au],\s*ma
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetivli\s+zero,\s*[0-9]+,\s*e16,m1,\s*t[au],\s*ma
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m2,\s*t[au],\s*ma
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint32m4_t
test_vwscjmul_vs_i16m2_m (vbool8_t mask, vint16m2_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m4_m (mask, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16m2_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m2,\s*tu,\s*m[au]
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint32m4_t
test_vwscjmul_vs_i16m2_tu (vint32m4_t maskedoff, vint16m2_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m4_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16m2_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m2,\s*tu,\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint32m4_t
test_vwscjmul_vs_i16m2_tumu (vbool8_t mask, vint32m4_t maskedoff, vint16m2_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m4_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16m2_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m2,\s*t[au],\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint32m4_t
test_vwscjmul_vs_i16m2_mu (vbool8_t mask, vint32m4_t pass, vint16m2_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m4_mu (mask, pass, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16m4:
**  vsetivli\s+zero,\s*[0-9]+,\s*e16,m4,\s*t[au],\s*m[au]
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetivli\s+zero,\s*[0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m4,\s*t[au],\s*m[au]
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint32m8_t
test_vwscjmul_vs_i16m4 (vint16m4_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m8 (vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16m4_m:
**  vsetivli\s+zero,\s*[0-9]+,\s*e16,m4,\s*t[au],\s*ma
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetivli\s+zero,\s*[0-9]+,\s*e16,m1,\s*t[au],\s*ma
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m4,\s*t[au],\s*ma
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint32m8_t
test_vwscjmul_vs_i16m4_m (vbool4_t mask, vint16m4_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m8_m (mask, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16m4_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m4,\s*tu,\s*m[au]
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint32m8_t
test_vwscjmul_vs_i16m4_tu (vint32m8_t maskedoff, vint16m4_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m8_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16m4_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m4,\s*tu,\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint32m8_t
test_vwscjmul_vs_i16m4_tumu (vbool4_t mask, vint32m8_t maskedoff, vint16m4_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m8_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i16m4_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m4,\s*t[au],\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint32m8_t
test_vwscjmul_vs_i16m4_mu (vbool4_t mask, vint32m8_t pass, vint16m4_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i32m8_mu (mask, pass, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/
vint64m2_t
test_vwscjmul_vs_i32 (vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m2 (vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*ma
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/
vint64m2_t
test_vwscjmul_vs_i32_m (vbool32_t mask, vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m2_m (mask, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*tu,\s*m[au]
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/
vint64m2_t
test_vwscjmul_vs_i32_tu (vint64m2_t maskedoff, vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m2_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*tu,\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/
vint64m2_t
test_vwscjmul_vs_i32_tumu (vbool32_t mask, vint64m2_t maskedoff, vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m2_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/
vint64m2_t
test_vwscjmul_vs_i32_mu (vbool32_t mask, vint64m2_t pass, vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m2_mu (mask, pass, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32m2:
**  vsetivli\s+zero,\s*[0-9]+,\s*e32,m2,\s*t[au],\s*m[au]
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetivli\s+zero,\s*[0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m2,\s*t[au],\s*m[au]
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint64m4_t
test_vwscjmul_vs_i32m2 (vint32m2_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m4 (vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32m2_m:
**  vsetivli\s+zero,\s*[0-9]+,\s*e32,m2,\s*t[au],\s*ma
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetivli\s+zero,\s*[0-9]+,\s*e32,m1,\s*t[au],\s*ma
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m2,\s*t[au],\s*ma
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint64m4_t
test_vwscjmul_vs_i32m2_m (vbool16_t mask, vint32m2_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m4_m (mask, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32m2_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m2,\s*tu,\s*m[au]
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint64m4_t
test_vwscjmul_vs_i32m2_tu (vint64m4_t maskedoff, vint32m2_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m4_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32m2_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m2,\s*tu,\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint64m4_t
test_vwscjmul_vs_i32m2_tumu (vbool16_t mask, vint64m4_t maskedoff, vint32m2_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m4_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32m2_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m2,\s*t[au],\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint64m4_t
test_vwscjmul_vs_i32m2_mu (vbool16_t mask, vint64m4_t pass, vint32m2_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m4_mu (mask, pass, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32m4:
**  vsetivli\s+zero,\s*[0-9]+,\s*e32,m4,\s*t[au],\s*m[au]
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetivli\s+zero,\s*[0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m4,\s*t[au],\s*m[au]
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint64m8_t
test_vwscjmul_vs_i32m4 (vint32m4_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m8 (vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32m4_m:
**  vsetivli\s+zero,\s*[0-9]+,\s*e32,m4,\s*t[au],\s*ma
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetivli\s+zero,\s*[0-9]+,\s*e32,m1,\s*t[au],\s*ma
**  vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m4,\s*t[au],\s*ma
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint64m8_t
test_vwscjmul_vs_i32m4_m (vbool8_t mask, vint32m4_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m8_m (mask, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32m4_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m4,\s*tu,\s*m[au]
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint64m8_t
test_vwscjmul_vs_i32m4_tu (vint64m8_t maskedoff, vint32m4_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m8_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32m4_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m4,\s*tu,\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint64m8_t
test_vwscjmul_vs_i32m4_tumu (vbool8_t mask, vint64m8_t maskedoff, vint32m4_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m8_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vwscjmul_vs_i32m4_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m4,\s*t[au],\s*mu
**  arcv.vwscjmul.vs\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint64m8_t
test_vwscjmul_vs_i32m4_mu (vbool8_t mask, vint64m8_t pass, vint32m4_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vwscjmul_vs_i64m8_mu (mask, pass, vs2, vs1, vl);
}
