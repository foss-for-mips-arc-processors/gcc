/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian -fdump-tree-widening_mul" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

/*
** q31_scalar:
**	pmulq\.w	a0,a0,a1
**	sext\.w	a0,a0
**	ret
*/
/*
** q31_scalar_round:
**	pmulqr\.w	a0,a0,a1
**	sext\.w	a0,a0
**	ret
*/
#include "q31-scalar.h"

/* { dg-final { scan-tree-dump-times {\.SAT_MULHS \(} 5 "widening_mul" } } */
/* { dg-final { scan-tree-dump-times {\.SAT_MULHRS \(} 3 "widening_mul" } } */
