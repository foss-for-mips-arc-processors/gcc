/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vwrdotu_vv_u8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdotu\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/
vuint16m1_t test_vwrdotu_vv_u8 (vuint16m1_t vd, vuint8m1_t vs1, vuint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdotu_vv_u8m1_u16m1 (vd, vs1, vs2, vl);
}

/*
** test_vwrdotu_vv_u8_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdotu\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vuint16m1_t test_vwrdotu_vv_u8_m (vbool8_t mask, vuint16m1_t vd, vuint8m1_t vs1, vuint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdotu_vv_u8m1_u16m1_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwrdotu_vv_u16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdotu\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/
vuint32m1_t test_vwrdotu_vv_u16 (vuint32m1_t vd, vuint16m1_t vs1, vuint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdotu_vv_u16m1_u32m1 (vd, vs1, vs2, vl);
}

/*
** test_vwrdotu_vv_u16_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdotu\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vuint32m1_t test_vwrdotu_vv_u16_m (vbool16_t mask, vuint32m1_t vd, vuint16m1_t vs1, vuint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdotu_vv_u16m1_u32m1_m (mask, vd, vs1, vs2, vl);
}

/*
** test_vwrdotu_vv_u32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdotu\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])
**  ret
*/
vuint64m1_t test_vwrdotu_vv_u32 (vuint64m1_t vd, vuint32m1_t vs1, vuint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdotu_vv_u32m1_u64m1 (vd, vs1, vs2, vl);
}

/*
** test_vwrdotu_vv_u32_m:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vwrdotu\.vv\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vuint64m1_t test_vwrdotu_vv_u32_m (vbool32_t mask, vuint64m1_t vd, vuint32m1_t vs1, vuint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vwrdotu_vv_u32m1_u64m1_m (mask, vd, vs1, vs2, vl);
}
