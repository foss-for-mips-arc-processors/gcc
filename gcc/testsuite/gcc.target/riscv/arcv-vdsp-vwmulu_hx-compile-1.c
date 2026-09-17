/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>

/*
** test_vwmulu_hx_u16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwmulu.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/

vuint32m2_t
test_vwmulu_hx_u16 (vuint8mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulu_hx_u32m2 (vs2, vs1, vl);
}

/*
** test_vwmulu_hx_u16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*ma
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwmulu.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vuint32m2_t
test_vwmulu_hx_u16_m (vbool16_t mask, vuint8mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulu_hx_u32m2_m (mask, vs2, vs1, vl);
}

/*
** test_vwmulu_hx_u16_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*m[au]
**  arcv.vwmulu.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/

vuint32m2_t
test_vwmulu_hx_u16_tu (vuint32m2_t maskedoff, vuint8mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulu_hx_u32m2_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vwmulu_hx_u16_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*mu
**  arcv.vwmulu.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vuint32m2_t
test_vwmulu_hx_u16_tumu (vbool16_t mask, vuint32m2_t maskedoff, vuint8mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulu_hx_u32m2_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vwmulu_hx_u16_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*mu
**  arcv.vwmulu.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vuint32m2_t
test_vwmulu_hx_u16_mu (vbool16_t mask, vuint32m2_t pass, vuint8mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulu_hx_u32m2_mu (mask, pass, vs2, vs1, vl);
}

/*
** test_vwmulu_hx_u32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwmulu.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/

vuint64m2_t
test_vwmulu_hx_u32 (vuint16mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulu_hx_u64m2 (vs2, vs1, vl);
}

/*
** test_vwmulu_hx_u32_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*ma
**  (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vwmulu.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vuint64m2_t
test_vwmulu_hx_u32_m (vbool32_t mask, vuint16mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulu_hx_u64m2_m (mask, vs2, vs1, vl);
}

/*
** test_vwmulu_hx_u32_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*tu,\s*m[au]
**  arcv.vwmulu.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**  ret
*/

vuint64m2_t
test_vwmulu_hx_u32_tu (vuint64m2_t maskedoff, vuint16mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulu_hx_u64m2_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vwmulu_hx_u32_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*tu,\s*mu
**  arcv.vwmulu.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vuint64m2_t
test_vwmulu_hx_u32_tumu (vbool32_t mask, vuint64m2_t maskedoff, vuint16mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulu_hx_u64m2_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vwmulu_hx_u32_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*mu
**  arcv.vwmulu.hx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**  ret
*/

vuint64m2_t
test_vwmulu_hx_u32_mu (vbool32_t mask, vuint64m2_t pass, vuint16mf2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vwmulu_hx_u64m2_mu (mask, pass, vs2, vs1, vl);
}
