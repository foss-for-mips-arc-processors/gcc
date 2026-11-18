/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "scalar-sat-word.h"

/*
** add_u:
**  psaddu\.w\s+a0,\s*(a0,\s*a1|a1,\s*a0)
**  sext\.w\s+a0,\s*a0
**  ret
*/
/*
** sub_u:
**  pssubu\.w\s+a0,\s*a0,\s*a1
**  sext\.w\s+a0,\s*a0
**  ret
*/
/*
** add_s_overflow:
**  psadd\.w\s+a0,\s*(a0,\s*a1|a1,\s*a0)
**  sext\.w\s+a0,\s*a0
**  ret
*/
/*
** sub_s_overflow:
**  pssub\.w\s+a0,\s*a0,\s*a1
**  sext\.w\s+a0,\s*a0
**  ret
*/
