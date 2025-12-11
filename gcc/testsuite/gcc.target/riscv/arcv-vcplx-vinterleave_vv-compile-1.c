/* { dg-do compile } */
/* { dg-require-effective-target arcv_vcplx } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvcplx -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vinterleave_vv_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vinterleave\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/

vint16m1_t test_vinterleave_vv_i16 (vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vinterleave_vv_i16m1 (vs2, vs1, vl);
}

/*
** test_vinterleave_vv_i16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*ma
**  arcv\.vinterleave\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/

vint16m1_t test_vinterleave_vv_i16_m (vbool16_t mask, vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vinterleave_vv_i16m1_m (mask, vs2, vs1, vl);
}

/*
** test_vinterleave_vv_i16_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*m[au]
**  arcv\.vinterleave\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/
vint16m1_t test_vinterleave_vv_i16_tu (vint16m1_t maskedoff, vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vinterleave_vv_i16m1_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vinterleave_vv_i16_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*tu,\s*mu
**  arcv\.vinterleave\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint16m1_t test_vinterleave_vv_i16_tumu (vbool16_t mask, vint16m1_t maskedoff, vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vinterleave_vv_i16m1_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vinterleave_vv_i16_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*mu
**  arcv\.vinterleave\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint16m1_t test_vinterleave_vv_i16_mu (vbool16_t mask, vint16m1_t pass, vint16m1_t vs2, vint16m1_t vs1, size_t vl)
{
  return __riscv_arcv_vinterleave_vv_i16m1_mu (mask, pass, vs2, vs1, vl);
}

/*
** test_vinterleave_vv_i32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vinterleave\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/

vint32m1_t test_vinterleave_vv_i32 (vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vinterleave_vv_i32m1 (vs2, vs1, vl);
}

/*
** test_vinterleave_vv_i32_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*ma
**  arcv\.vinterleave\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/

vint32m1_t test_vinterleave_vv_i32_m (vbool32_t mask, vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vinterleave_vv_i32m1_m (mask, vs2, vs1, vl);
}

/*
** test_vinterleave_vv_i32_tu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*tu,\s*m[au]
**  arcv\.vinterleave\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/
vint32m1_t test_vinterleave_vv_i32_tu (vint32m1_t maskedoff, vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vinterleave_vv_i32m1_tu (maskedoff, vs2, vs1, vl);
}

/*
** test_vinterleave_vv_i32_tumu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*tu,\s*mu
**  arcv\.vinterleave\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint32m1_t test_vinterleave_vv_i32_tumu (vbool32_t mask, vint32m1_t maskedoff, vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vinterleave_vv_i32m1_tumu (mask, maskedoff, vs2, vs1, vl);
}

/*
** test_vinterleave_vv_i32_mu:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*mu
**  arcv\.vinterleave\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint32m1_t test_vinterleave_vv_i32_mu (vbool32_t mask, vint32m1_t pass, vint32m1_t vs2, vint32m1_t vs1, size_t vl)
{
  return __riscv_arcv_vinterleave_vv_i32m1_mu (mask, pass, vs2, vs1, vl);
}
