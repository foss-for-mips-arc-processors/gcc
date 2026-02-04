/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vmv_v_si_i8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.si\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint8m1_t test_vmv_v_si_i8 (vint8m1_t vd, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i8m1 (vd, vs2, 1, vl);
}

/*
** test_vmv_v_si_i8m4:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m4,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.si\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*-1
**  ret
*/
vint8m4_t test_vmv_v_si_i8m4 (vint8m4_t vd, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i8m4 (vd, vs2, -1, vl);
}

/*
** test_vmv_v_si_u8m2:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m2,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.si\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*3
**  ret
*/
vuint8m2_t test_vmv_v_si_u8m2 (vuint8m2_t vd, vuint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u8m2 (vd, vs2, 3, vl);
}

/*
** test_vmv_v_si_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.si\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint16m1_t test_vmv_v_si_i16 (vint16m1_t vd, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i16m1 (vd, vs2, 1, vl);
}

/*
** test_vmv_v_si_i16m2:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m2,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.si\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*15
**  ret
*/
vint16m2_t test_vmv_v_si_i16m2 (vint16m2_t vd, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i16m2 (vd, vs2, 15, vl);
}

/*
** test_vmv_v_si_u16m8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m8,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.si\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*-8
**  ret
*/
vuint16m8_t test_vmv_v_si_u16m8 (vuint16m8_t vd, vuint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u16m8 (vd, vs2, -8, vl);
}

/*
** test_vmv_v_si_i32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.si\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint32m1_t test_vmv_v_si_i32 (vint32m1_t vd, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i32m1 (vd, vs2, 1, vl);
}

/*
** test_vmv_v_si_i32m4:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m4,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.si\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*7
**  ret
*/
vint32m4_t test_vmv_v_si_i32m4 (vint32m4_t vd, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i32m4 (vd, vs2, 7, vl);
}

/*
** test_vmv_v_si_u32m2:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m2,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.si\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*12
**  ret
*/
vuint32m2_t test_vmv_v_si_u32m2 (vuint32m2_t vd, vuint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u32m2 (vd, vs2, 12, vl);
}

/*
** test_vmv_v_si_i64:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e64,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.si\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint64m1_t test_vmv_v_si_i64 (vint64m1_t vd, vint64m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i64m1 (vd, vs2, 1, vl);
}

/*
** test_vmv_v_si_u64m4:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e64,m4,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.si\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*-5
**  ret
*/
vuint64m4_t test_vmv_v_si_u64m4 (vuint64m4_t vd, vuint64m1_t vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u64m4 (vd, vs2, -5, vl);
}
