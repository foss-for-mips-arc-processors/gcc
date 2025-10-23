/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>

/*
** test_vwmacu_hv_u16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv.vwmacu.hv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vuint32m2_t
test_vwmacu_hv_u16 (vuint32m2_t vd, vuint16m1_t vs1, vuint8mf2_t vs2, size_t vl)
{
  return __riscv_arcv_vwmacu_hv_u32m2 (vd, vs1, vs2, vl);
}

/*
** test_vwmacu_hv_u16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv.vwmacu.hv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vuint32m2_t
test_vwmacu_hv_u16_m (vbool16_t mask, vuint32m2_t vd, vuint16m1_t vs1, vuint8mf2_t vs2, size_t vl)
{
  return __riscv_arcv_vwmacu_hv_u32m2_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwmacu_hv_u32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv.vwmacu.hv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vuint64m2_t
test_vwmacu_hv_u32 (vuint64m2_t vd, vuint32m1_t vs1, vuint16mf2_t vs2, size_t vl)
{
  return __riscv_arcv_vwmacu_hv_u64m2 (vd, vs1, vs2, vl);
}

/*
** test_vwmacu_hv_u32_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv.vwmacu.hv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vuint64m2_t
test_vwmacu_hv_u32_m (vbool32_t mask, vuint64m2_t vd, vuint32m1_t vs1, vuint16mf2_t vs2, size_t vl)
{
  return __riscv_arcv_vwmacu_hv_u64m2_m (mask, vd, vs1, vs2, vl);
}
