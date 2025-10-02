/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vqrdotsu_vv_i8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vqrdotsu\.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint32m1_t test_vqrdotsu_vv_i8 (vint32m1_t vd, vint8m1_t vs1, vuint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vqrdotsu_vv_i8m1_i32m1 (vd, vs1, vs2, vl);
}

/*
** test_vqrdotsu_vv_i8_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vqrdotsu\.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint32m1_t test_vqrdotsu_vv_i8_m (vbool8_t mask, vint32m1_t vd, vint8m1_t vs1, vuint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vqrdotsu_vv_i8m1_i32m1_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vqrdotsu_vv_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vqrdotsu\.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1])
**  ret
*/
vint64m1_t test_vqrdotsu_vv_i16 (vint64m1_t vd, vint16m1_t vs1, vuint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vqrdotsu_vv_i16m1_i64m1 (vd, vs1, vs2, vl);
}

/*
** test_vqrdotsu_vv_i16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vqrdotsu\.vv\s+(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|v3[0-1]),\s*v0\.t
**  ret
*/
vint64m1_t test_vqrdotsu_vv_i16_m (vbool16_t mask, vint64m1_t vd, vint16m1_t vs1, vuint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vqrdotsu_vv_i16m1_i64m1_m (mask, vd, vs1, vs2, vl);
}
