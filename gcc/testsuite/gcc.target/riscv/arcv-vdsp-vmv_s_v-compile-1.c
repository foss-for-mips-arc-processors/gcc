/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vmv_s_v_i8m1:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.s\.vx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint8m1_t test_vmv_s_v_i8m1 (vint8m1_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vmv_s_v_i8m1_i8m1 (vs2, vs1, vl);
}

/*
** test_vmv_s_v_i8m2:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m2,\s*t[au],\s*m[au]
**  arcv\.vmv\.s\.vx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint8m1_t test_vmv_s_v_i8m2 (vint8m2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vmv_s_v_i8m2_i8m1 (vs2, vs1, vl);
}

/*
** test_vmv_s_v_i8m4:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m4,\s*t[au],\s*m[au]
**  arcv\.vmv\.s\.vx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint8m1_t test_vmv_s_v_i8m4 (vint8m4_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vmv_s_v_i8m4_i8m1 (vs2, vs1, vl);
}

/*
** test_vmv_s_v_i16m1:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.s\.vx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint16m1_t test_vmv_s_v_i16m1 (vint16m1_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vmv_s_v_i16m1_i16m1 (vs2, vs1, vl);
}

/*
** test_vmv_s_v_i32m1:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.s\.vx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint32m1_t test_vmv_s_v_i32m1 (vint32m1_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vmv_s_v_i32m1_i32m1 (vs2, vs1, vl);
}

/*
** test_vmv_s_v_i32m2:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m2,\s*t[au],\s*m[au]
**  arcv\.vmv\.s\.vx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint32m1_t test_vmv_s_v_i32m2 (vint32m2_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vmv_s_v_i32m2_i32m1 (vs2, vs1, vl);
}

/*
** test_vmv_s_v_i64m1:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e64,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.s\.vx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint64m1_t test_vmv_s_v_i64m1 (vint64m1_t vs2, int vs1, size_t vl)
{
  return __riscv_arcv_vmv_s_v_i64m1_i64m1 (vs2, vs1, vl);
}
