/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mbig-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "multiply-acc-extract.h"

/* Subtraction preserves its operand order after selecting the product.  */

/*
** pair_sub_u0:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** pair_sub_s0:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** pair_rsub_u0:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** pair_rsub_s0:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** pair_sub_u1:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  sub\s+[a-z][a-z0-9]*,\s*a0,\s*[a-z][a-z0-9]*
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** pair_sub_s1:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  sub\s+[a-z][a-z0-9]*,\s*a0,\s*[a-z][a-z0-9]*
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** pair_rsub_u1:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*a0
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** pair_rsub_s1:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*a0
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_sub_u0:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_sub_s0:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_rsub_u0:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_rsub_s0:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_sub_u1:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  sub\s+[a-z][a-z0-9]*,\s*a0,\s*[a-z][a-z0-9]*
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_sub_s1:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  sub\s+[a-z][a-z0-9]*,\s*a0,\s*[a-z][a-z0-9]*
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_rsub_u1:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*a0
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_rsub_s1:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*a0
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_sub_u2:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  srli\s+[a-z][a-z0-9]*,\s*a1,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a1,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_sub_s2:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  srli\s+[a-z][a-z0-9]*,\s*a1,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a1,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_rsub_u2:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  srli\s+[a-z][a-z0-9]*,\s*a1,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a1,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_rsub_s2:
**  (
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  srli\s+[a-z][a-z0-9]*,\s*a1,\s*16
**  |
**  srli\s+[a-z][a-z0-9]*,\s*a1,\s*16
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  )
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_sub_u3:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  sub\s+[a-z][a-z0-9]*,\s*a1,\s*[a-z][a-z0-9]*
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_sub_s3:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  sub\s+[a-z][a-z0-9]*,\s*a1,\s*[a-z][a-z0-9]*
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_rsub_u3:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*a1
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_rsub_s3:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  sub\s+[a-z][a-z0-9]*,\s*[a-z][a-z0-9]*,\s*a1
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/* Each scalar result must use only the corresponding argument words.  */

/*
** pair_add_u0:
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  macc\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** pair_add_s0:
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  macc\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** pair_add_u1:
**  macc\.h00\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** pair_add_s1:
**  macc\.h00\s+[a-z][a-z0-9]*,\s*(a1,\s*a2|a2,\s*a1)
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_add_u0:
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  macc\.h11\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_add_s0:
**  srli\s+[a-z][a-z0-9]*,\s*a0,\s*16
**  macc\.h11\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_add_u1:
**  macc\.h00\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_add_s1:
**  macc\.h00\s+[a-z][a-z0-9]*,\s*(a2,\s*a4|a4,\s*a2)
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_add_u2:
**  srli\s+[a-z][a-z0-9]*,\s*a1,\s*16
**  macc\.h11\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_add_s2:
**  srli\s+[a-z][a-z0-9]*,\s*a1,\s*16
**  macc\.h11\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_add_u3:
**  macc\.h00\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  zext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/

/*
** quad_add_s3:
**  macc\.h00\s+[a-z][a-z0-9]*,\s*(a3,\s*a5|a5,\s*a3)
**  sext\.h\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
