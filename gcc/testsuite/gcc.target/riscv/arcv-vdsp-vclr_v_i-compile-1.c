/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32imv_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vclr_v_i8:
**  vsetvli	zero,a0,e8,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint8m1_t test_vclr_v_i8 (size_t vl)
{
  return __riscv_arcv_vclr_v_i8m1 (1, vl);
}

/*
** test_vclr_v_i8_tu:
**  vsetvli	zero,a0,e8,m1,tu,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint8m1_t test_vclr_v_i8_tu (vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i8m1_tu (vs2, 1, vl);
}

/*
** test_vclr_v_i16:
**  vsetvli	zero,a0,e16,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint16m1_t test_vclr_v_i16 (size_t vl)
{
  return __riscv_arcv_vclr_v_i16m1 (1, vl);
}

/*
** test_vclr_v_i16_tu:
**  vsetvli	zero,a0,e16,m1,tu,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint16m1_t test_vclr_v_i16_tu (vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i16m1_tu (vs2, 1, vl);
}

/*
** test_vclr_v_i32:
**  vsetvli	zero,a0,e32,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint32m1_t test_vclr_v_i32 (size_t vl)
{
  return __riscv_arcv_vclr_v_i32m1 (1, vl);
}

/*
** test_vclr_v_i32_tu:
**  vsetvli	zero,a0,e32,m1,tu,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint32m1_t test_vclr_v_i32_tu (vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i32m1_tu (vs2, 1, vl);
}

/*
** test_vclr_v_i64:
**  vsetvli	zero,a0,e64,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint64m1_t test_vclr_v_i64 (size_t vl)
{
  return __riscv_arcv_vclr_v_i64m1 (1, vl);
}

/*
** test_vclr_v_i64_tu:
**  vsetvli	zero,a0,e64,m1,tu,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint64m1_t test_vclr_v_i64_tu (vint64m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i64m1_tu (vs2, 1, vl);
}
