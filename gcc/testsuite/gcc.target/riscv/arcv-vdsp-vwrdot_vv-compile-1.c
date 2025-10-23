/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vwrdot_vv_i8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdot\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/
vint16m1_t test_vwrdot_vv_i8 (vint16m1_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdot_vv_i8m1_i16m1 (vd, vs1, vs2, vl);
}

/*
** test_vwrdot_vv_i8_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdot\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint16m1_t test_vwrdot_vv_i8_m (vbool8_t mask, vint16m1_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdot_vv_i8m1_i16m1_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwrdot_vv_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdot\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/
vint32m1_t test_vwrdot_vv_i16 (vint32m1_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdot_vv_i16m1_i32m1 (vd, vs1, vs2, vl);
}

/*
** test_vwrdot_vv_i16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdot\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint32m1_t test_vwrdot_vv_i16_m (vbool16_t mask, vint32m1_t vd, vint16m1_t vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdot_vv_i16m1_i32m1_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwrdot_vv_i32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdot\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/
vint64m1_t test_vwrdot_vv_i32 (vint64m1_t vd, vint32m1_t vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdot_vv_i32m1_i64m1 (vd, vs1, vs2, vl);
}

/*
** test_vwrdot_vv_i32_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdot\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint64m1_t test_vwrdot_vv_i32_m (vbool32_t mask, vint64m1_t vd, vint32m1_t vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdot_vv_i32m1_i64m1_m (mask, vd, vs1, vs2, vl);
}
