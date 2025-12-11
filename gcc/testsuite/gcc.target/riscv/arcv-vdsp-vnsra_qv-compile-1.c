/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>

/*
** test_vnsra_qv_i8:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**   (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vnsra.qv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**   ret
*/

vint8m1_t
test_vnsra_qv_i8 (vint32m4_t vs2, vint8m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_qv_i8m1 (vs2, vs1, 0, vl);
}

/*
** test_vnsra_qv_i8_m:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*ma
**   (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vnsra.qv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**   ret
*/

vint8m1_t
test_vnsra_qv_i8_m (vbool8_t mask, vint32m4_t vs2, vint8m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_qv_i8m1_m (mask, vs2, vs1, 0, vl);
}

/*
** test_vnsra_qv_i8_tu:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*tu,\s*m[au]
**   arcv.vnsra.qv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**   ret
*/

vint8m1_t
test_vnsra_qv_i8_tu (vint8m1_t maskedoff, vint32m4_t vs2, vint8m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_qv_i8m1_tu (maskedoff, vs2, vs1, 0, vl);
}

/*
** test_vnsra_qv_i8_tumu:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*tu,\s*mu
**   arcv.vnsra.qv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**   ret
*/

vint8m1_t
test_vnsra_qv_i8_tumu (vbool8_t mask, vint8m1_t maskedoff, vint32m4_t vs2, vint8m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_qv_i8m1_tumu (mask, maskedoff, vs2, vs1, 0, vl);
}

/*
** test_vnsra_qv_i8_mu:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*mu
**   arcv.vnsra.qv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**   ret
*/

vint8m1_t
test_vnsra_qv_i8_mu (vbool8_t mask, vint8m1_t pass, vint32m4_t vs2, vint8m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_qv_i8m1_mu (mask, pass, vs2, vs1, 0, vl);
}

/*
** test_vnsra_qv_i16:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**   (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vnsra.qv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**   ret
*/

vint16m1_t
test_vnsra_qv_i16 (vint64m4_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_qv_i16m1 (vs2, vs1, 0, vl);
}

/*
** test_vnsra_qv_i16_m:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*ma
**   (?:vmv[0-9]*r\.v\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])\n\s+)+arcv.vnsra.qv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**   ret
*/

vint16m1_t
test_vnsra_qv_i16_m (vbool16_t mask, vint64m4_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_qv_i16m1_m (mask, vs2, vs1, 0, vl);
}

/*
** test_vnsra_qv_i16_tu:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*m[au]
**   arcv.vnsra.qv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**   ret
*/

vint16m1_t
test_vnsra_qv_i16_tu (vint16m1_t maskedoff, vint64m4_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_qv_i16m1_tu (maskedoff, vs2, vs1, 0, vl);
}

/*
** test_vnsra_qv_i16_tumu:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*mu
**   arcv.vnsra.qv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**   ret
*/

vint16m1_t
test_vnsra_qv_i16_tumu (vbool16_t mask, vint16m1_t maskedoff, vint64m4_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_qv_i16m1_tumu (mask, maskedoff, vs2, vs1, 0, vl);
}

/*
** test_vnsra_qv_i16_mu:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*mu
**   arcv.vnsra.qv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**   ret
*/

vint16m1_t
test_vnsra_qv_i16_mu (vbool16_t mask, vint16m1_t pass, vint64m4_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vnsra_qv_i16m1_mu (mask, pass, vs2, vs1, 0, vl);
}
