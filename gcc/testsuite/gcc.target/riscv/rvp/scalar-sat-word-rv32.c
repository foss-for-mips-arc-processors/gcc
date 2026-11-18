/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "scalar-sat-word.h"

/*
** add_u:
**  saddu\s+a0,\s*(a0,\s*a1|a1,\s*a0)
**  ret
*/
/*
** sub_u:
**  ssubu\s+a0,\s*a0,\s*a1
**  ret
*/
/*
** add_s_overflow:
**  sadd\s+a0,\s*(a0,\s*a1|a1,\s*a0)
**  ret
*/
/*
** sub_s_overflow:
**  ssub\s+a0,\s*a0,\s*a1
**  ret
*/
