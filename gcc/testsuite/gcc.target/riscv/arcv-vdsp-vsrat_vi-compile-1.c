/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vsrat_vi_i8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vsrat\.vi\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint8m1_t test_vsrat_vi_i8 (vint8m1_t vs2, vint8m1_t vs1, size_t vl)
{
  return __riscv_arcv_vsrat_vx_i8m1 (vs2, 1, vl);
}

/*
** test_vsrat_vi_i8_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vsrat\.vi\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1,\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint8m1_t test_vsrat_vi_i8_m (vbool8_t mask, vint8m1_t vs2, vint8m1_t vs1, size_t vl)
{
  return __riscv_arcv_vsrat_vx_i8m1_m (mask, vs2, 1, vl);
}

/*
** test_vsrat_vi_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vsrat\.vi\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint16m1_t test_vsrat_vi_i16 (vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vsrat_vx_i16m1 (vs2, 1, vl);
}

/*
** test_vsrat_vi_i16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vsrat\.vi\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1,\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint16m1_t test_vsrat_vi_i16_m (vbool16_t mask, vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vsrat_vx_i16m1_m (mask, vs2, 1, vl);
}

/*
** test_vsrat_vi_i32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vsrat\.vi\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint32m1_t test_vsrat_vi_i32 (vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vsrat_vx_i32m1 (vs2, 1, vl);
}

/*
** test_vsrat_vi_i32_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vsrat\.vi\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1,\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint32m1_t test_vsrat_vi_i32_m (vbool32_t mask, vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vsrat_vx_i32m1_m (mask, vs2, 1, vl);
}

/*
** test_vsrat_vi_i64:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e64,m1,\s*t[au],\s*m[au]
**  arcv\.vsrat\.vi\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint64m1_t test_vsrat_vi_i64 (vint64m1_t vs2, vint64m1_t vs1, size_t vl)
{
  return __riscv_arcv_vsrat_vx_i64m1 (vs2, 1, vl);
}

/*
** test_vsrat_vi_i64_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e64,m1,\s*t[au],\s*m[au]
**  arcv\.vsrat\.vi\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1,\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint64m1_t test_vsrat_vi_i64_m (vbool64_t mask, vint64m1_t vs2, vint64m1_t vs1, size_t vl)
{
  return __riscv_arcv_vsrat_vx_i64m1_m (mask, vs2, 1, vl);
}
