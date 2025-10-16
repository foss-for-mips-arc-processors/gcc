/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */


#include <stddef.h>
#include <riscv_vector.h>

/*
** test_vnsra_2s_qx_i8:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**   arcv.vnsra.2s.qx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**   ret
*/
vint8m1_t
test_vnsra_2s_qx_i8 (vint32m1_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vnsra_2s_qx_i8m1 (vs2, vs1, 0, vl);
}

/*
** test_vnsra_2s_qx_i8_m:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**   arcv.vnsra.2s.qx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**   ret
*/
vint8m1_t
test_vnsra_2s_qx_i8_m (vbool8_t mask, vint32m1_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vnsra_2s_qx_i8m1_m (mask, vs2, vs1, 0, vl);
}

/*
** test_vnsra_2s_qx_i16:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**   arcv.vnsra.2s.qx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+
**   ret
*/
vint16m1_t
test_vnsra_2s_qx_i16 (vint64m1_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vnsra_2s_qx_i16m1 (vs2, vs1, 0, vl);
}

/*
** test_vnsra_2s_qx_i16_m:
**   csrwi\s+vxrm,0
**   vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**   arcv.vnsra.2s.qx\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*[a-x0-9]+,\s*v0\.t
**   ret
*/
vint16m1_t
test_vnsra_2s_qx_i16_m (vbool16_t mask, vint64m1_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vnsra_2s_qx_i16m1_m (mask, vs2, vs1, 0, vl);
}
