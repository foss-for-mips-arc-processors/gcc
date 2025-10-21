/* { dg-do compile } */
/* { dg-require-effective-target arcv_vdsp } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Og" "-Oz" "-flto" } } */
/* { dg-options "-march=rv32im_xarcvvdsp -mabi=ilp32 -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include <stddef.h>
#include <riscv_vector.h>


/*
** test_vclr_v_i_i8:
**  vsetivli	zero,1,e8,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint8m1_t test_vclr_v_i_i8 (vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i_i8m1 (vs2, 1, vl);
}

/*
** test_vclr_v_i_i8_m:
**  vsetivli	zero,1,e8,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1,\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint8m1_t test_vclr_v_i_i8_m (vbool8_t mask, vint8m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i_i8m1_m (mask, vs2, 1, vl);
}

/*
** test_vclr_v_i_i16:
**  vsetivli	zero,1,e16,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint16m1_t test_vclr_v_i_i16 (vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i_i16m1 (vs2, 1, vl);
}

/*
** test_vclr_v_i_i16_m:
**  vsetivli	zero,1,e16,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1,\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint16m1_t test_vclr_v_i_i16_m (vbool16_t mask, vint16m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i_i16m1_m (mask, vs2, 1, vl);
}

/*
** test_vclr_v_i_i32:
**  vsetivli	zero,1,e32,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint32m1_t test_vclr_v_i_i32 (vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i_i32m1 (vs2, 1, vl);
}

/*
** test_vclr_v_i_i32_m:
**  vsetivli	zero,1,e32,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1,\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint32m1_t test_vclr_v_i_i32_m (vbool32_t mask, vint32m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i_i32m1_m (mask, vs2, 1, vl);
}

/*
** test_vclr_v_i_i64:
**  vsetivli	zero,1,e64,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1
**  ret
*/
vint64m1_t test_vclr_v_i_i64 (vint64m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i_i64m1 (vs2, 1, vl);
}

/*
** test_vclr_v_i_i64_m:
**  vsetivli	zero,1,e64,m1,ta,ma
**  arcv\.vclr\.v\.i\s+(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1]),\s*1,\s*(?:v[0-9]|v[1-2][0-9]|[a-x0-9]+[0-1])\.t
**  ret
*/
vint64m1_t test_vclr_v_i_i64_m (vbool64_t mask, vint64m1_t vs2, size_t vl)
{
  return __riscv_arcv_vclr_v_i_i64m1_m (mask, vs2, 1, vl);
}
