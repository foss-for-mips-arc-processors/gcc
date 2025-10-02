/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vmvi_v_s_i8:
**  arcv\.vmvi\.v\.s\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint8m1_t test_vmvi_v_s_i8 (vint8m1_t vd, int vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i8m1 (vd, 1, vs2, vl);
}

/*
** test_vmvi_v_s_i16:
**  arcv\.vmvi\.v\.s\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint16m1_t test_vmvi_v_s_i16 (vint16m1_t vd, int vs1, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i16m1 (vd, 1, vs2, vl);
}

/*
** test_vmvi_v_s_i32:
**  arcv\.vmvi\.v\.s\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint32m1_t test_vmvi_v_s_i32 (vint32m1_t vd, int vs1, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i32m1 (vd, 1, vs2, vl);
}

/*
** test_vmvi_v_s_i64:
**  arcv\.vmvi\.v\.s\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint64m1_t test_vmvi_v_s_i64 (vint64m1_t vd, int vs1, vint64m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i64m1 (vd, 1, vs2, vl);
}
