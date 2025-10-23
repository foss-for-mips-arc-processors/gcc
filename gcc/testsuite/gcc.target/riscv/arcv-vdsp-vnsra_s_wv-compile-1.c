/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>

/*
** test_vnsra_s_wv_i8:
**   csrwi\s+vxrm,0
**   vset(?:iv)?li\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**   (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**   arcv.vnsra.s.wv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**   ret
*/
vint8m1_t
test_vnsra_s_wv_i8 (vint16m1_t vs2, vint8m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_s_wv_i8m1 (vs2, vs1, 0, vl);
}

/*
** test_vnsra_s_wv_i8_m:
**   csrwi\s+vxrm,0
**   vset(?:iv)?li\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**   (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**   arcv.vnsra.s.wv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**   ret
*/
vint8m1_t
test_vnsra_s_wv_i8_m (vbool8_t mask, vint16m1_t vs2, vint8m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_s_wv_i8m1_m (mask, vs2, vs1, 0, vl);
}

/*
** test_vnsra_s_wv_i16:
**   csrwi\s+vxrm,0
**   vset(?:iv)?li\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**   (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**   arcv.vnsra.s.wv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**   ret
*/
vint16m1_t
test_vnsra_s_wv_i16 (vint32m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_s_wv_i16m1 (vs2, vs1, 0, vl);
}

/*
** test_vnsra_s_wv_i16_m:
**   csrwi\s+vxrm,0
**   vset(?:iv)?li\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**   (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**   arcv.vnsra.s.wv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**   ret
*/
vint16m1_t
test_vnsra_s_wv_i16_m (vbool16_t mask, vint32m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_s_wv_i16m1_m (mask, vs2, vs1, 0, vl);
}

/*
** test_vnsra_s_wv_i32:
**   csrwi\s+vxrm,0
**   vset(?:iv)?li\s+zero,\s*[a-x0-9]+,\s*e64,m1,\s*t[au],\s*m[au]
**   (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**   arcv.vnsra.s.wv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**   ret
*/
vint32m1_t
test_vnsra_s_wv_i32 (vint64m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_s_wv_i32m1 (vs2, vs1, 0, vl);
}

/*
** test_vnsra_s_wv_i32_m:
**   csrwi\s+vxrm,0
**   vset(?:iv)?li\s+zero,\s*[a-x0-9]+,\s*e64,m1,\s*t[au],\s*m[au]
**   (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**   arcv.vnsra.s.wv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**   ret
*/
vint32m1_t
test_vnsra_s_wv_i32_m (vbool32_t mask, vint64m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_s_wv_i32m1_m (mask, vs2, vs1, 0, vl);
}
