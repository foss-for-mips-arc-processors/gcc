/* { dg-do compile } */
/* { dg-require-effective-target arcv_mxmc } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32im_xarcvmxmc -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vqmxm8u_vv_u8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vqmxm8u\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/
vuint32m4_t test_vqmxm8u_vv_u8 (vuint32m4_t vd, vuint8m1_t vs1, vuint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vqmxm8u_vv_u32m4 (vd, vs1, vs2, vl);
}

/*
** test_vqmxm8u_vv_u8_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vqmxm8u\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vuint32m4_t test_vqmxm8u_vv_u8_m (vbool8_t mask, vuint32m4_t vd, vuint8m1_t vs1, vuint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vqmxm8u_vv_u32m4_m (mask, vd, vs1, vs2, vl);
}
