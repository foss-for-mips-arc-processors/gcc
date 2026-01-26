/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vmv_v_s_i8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint8m1_t test_vmv_v_s_i8 (vint8m1_t vd, vint8m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i8m1 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint16m1_t test_vmv_v_s_i16 (vint16m1_t vd, vint16m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i16m1 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint32m1_t test_vmv_v_s_i32 (vint32m1_t vd, vint32m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i32m1 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i64:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e64,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint64m1_t test_vmv_v_s_i64 (vint64m1_t vd, vint64m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i64m1 (vd, vs1, vs2, vl);
}
