/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mbig-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "multiply-extract.h"

/*
** pair_mul_0:
**  mul\.h11\s+[^\n]+
**  zext\.h\s+[^\n]+
**  ret
*/
/*
** pair_mul_1:
**  mul\.h00\s+[^\n]+
**  zext\.h\s+[^\n]+
**  ret
*/
/*
** quad_mul_0:
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a0,\s*a2|a2,\s*a0)
**  zext\.h\s+[^\n]+
**  ret
*/
/*
** quad_mul_1:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a0,\s*a2|a2,\s*a0)
**  zext\.h\s+[^\n]+
**  ret
*/
/*
** quad_mul_2:
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a3|a3,\s*a1)
**  zext\.h\s+[^\n]+
**  ret
*/
/*
** quad_mul_3:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a1,\s*a3|a3,\s*a1)
**  zext\.h\s+[^\n]+
**  ret
*/
/*
** pair_signed_0:
**  mul\.h11\s+[^\n]+
**  sext\.h\s+[^\n]+
**  ret
*/
/*
** pair_signed_1:
**  mul\.h00\s+[^\n]+
**  sext\.h\s+[^\n]+
**  ret
*/
/*
** quad_signed_0:
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a0,\s*a2|a2,\s*a0)
**  sext\.h\s+[^\n]+
**  ret
*/
/*
** quad_signed_1:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a0,\s*a2|a2,\s*a0)
**  sext\.h\s+[^\n]+
**  ret
*/
/*
** quad_signed_2:
**  mul\.h11\s+[a-z][a-z0-9]*,\s*(a1,\s*a3|a3,\s*a1)
**  sext\.h\s+[^\n]+
**  ret
*/
/*
** quad_signed_3:
**  mul\.h00\s+[a-z][a-z0-9]*,\s*(a1,\s*a3|a3,\s*a1)
**  sext\.h\s+[^\n]+
**  ret
*/

/* Ordinary extraction must retain the physical big-endian half.  */
/*
** pair_plain_0:
**  srli\s+[^\n]+,16
**  ret
*/
/*
** pair_plain_1:
**  zext\.h\s+[^\n]+
**  ret
*/
/*
** quad_plain_0:
**  srli\s+[^\n]+,16
**  ret
*/
/*
** quad_plain_1:
**  zext\.h\s+[^\n]+
**  ret
*/
/*
** quad_plain_2:
**  srli\s+[^\n]+,16
**  ret
*/
/*
** quad_plain_3:
**  zext\.h\s+[^\n]+
**  ret
*/
