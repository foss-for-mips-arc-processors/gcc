/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vmv_v_s_i8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint8m1_t test_vmv_v_s_i8 (vint8m1_t vd, vint8m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i8m1 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i8m2:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m2,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint8m2_t test_vmv_v_s_i8m2 (vint8m2_t vd, vint8m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i8m2 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i8m8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m8,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint8m8_t test_vmv_v_s_i8m8 (vint8m8_t vd, vint8m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i8m8 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_u8m1:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vuint8m1_t test_vmv_v_s_u8m1 (vuint8m1_t vd, vuint8m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u8m1 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_u8m4:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,m4,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vuint8m4_t test_vmv_v_s_u8m4 (vuint8m4_t vd, vuint8m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u8m4 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i16:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint16m1_t test_vmv_v_s_i16 (vint16m1_t vd, vint16m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i16m1 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i16m4:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m4,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint16m4_t test_vmv_v_s_i16m4 (vint16m4_t vd, vint16m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i16m4 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i16m8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m8,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint16m8_t test_vmv_v_s_i16m8 (vint16m8_t vd, vint16m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i16m8 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_u16m1:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vuint16m1_t test_vmv_v_s_u16m1 (vuint16m1_t vd, vuint16m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u16m1 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_u16m2:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,m2,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vuint16m2_t test_vmv_v_s_u16m2 (vuint16m2_t vd, vuint16m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u16m2 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i32:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint32m1_t test_vmv_v_s_i32 (vint32m1_t vd, vint32m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i32m1 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i32m2:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m2,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint32m2_t test_vmv_v_s_i32m2 (vint32m2_t vd, vint32m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i32m2 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i32m8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m8,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint32m8_t test_vmv_v_s_i32m8 (vint32m8_t vd, vint32m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i32m8 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_u32m1:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vuint32m1_t test_vmv_v_s_u32m1 (vuint32m1_t vd, vuint32m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u32m1 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_u32m4:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,m4,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vuint32m4_t test_vmv_v_s_u32m4 (vuint32m4_t vd, vuint32m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u32m4 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i64:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e64,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint64m1_t test_vmv_v_s_i64 (vint64m1_t vd, vint64m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i64m1 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i64m2:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e64,m2,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint64m2_t test_vmv_v_s_i64m2 (vint64m2_t vd, vint64m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i64m2 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_i64m4:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e64,m4,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vint64m4_t test_vmv_v_s_i64m4 (vint64m4_t vd, vint64m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_i64m4 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_u64m1:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e64,m1,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vuint64m1_t test_vmv_v_s_u64m1 (vuint64m1_t vd, vuint64m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u64m1 (vd, vs1, vs2, vl);
}

/*
** test_vmv_v_s_u64m8:
**  vsetvli\s+zero,\s*[a-x0-9]+,\s*e64,m8,\s*t[au],\s*m[au]
**  arcv\.vmv\.v\.sx\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*[a-x0-9]+
**  ret
*/
vuint64m8_t test_vmv_v_s_u64m8 (vuint64m8_t vd, vuint64m1_t vs1, int vs2, size_t vl)
{
  return __riscv_arcv_vmv_v_s_u64m8 (vd, vs1, vs2, vl);
}
