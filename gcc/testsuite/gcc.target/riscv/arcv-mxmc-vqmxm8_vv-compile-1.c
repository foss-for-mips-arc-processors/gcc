/* { dg-do compile } */
/* { dg-require-effective-target arcv_mxmc } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32im_xarcvmxmc -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vqmxm8_vv_i8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vqmxm8\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/
vint32m4_t test_vqmxm8_vv_i8 (vint32m4_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vqmxm8_vv_i32m4 (vd, vs1, vs2, vl);
}

/*
** test_vqmxm8_vv_i8_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vqmxm8\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint32m4_t test_vqmxm8_vv_i8_m (vbool8_t mask, vint32m4_t vd, vint8m1_t vs1, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vqmxm8_vv_i32m4_m (mask, vd, vs1, vs2, vl);
}
