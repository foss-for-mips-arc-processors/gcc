/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-widening_mul" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

/*
** q31_scalar:
**	mulq	a0,a0,a1
**	ret
*/
/*
** q31_scalar_round:
**	mulqr	a0,a0,a1
**	ret
*/
#include "q31-scalar.h"

/* { dg-final { scan-tree-dump-times {\.SAT_MULHS \(} 5 "widening_mul" } } */
/* { dg-final { scan-tree-dump-times {\.SAT_MULHRS \(} 3 "widening_mul" } } */
/* { dg-final { scan-assembler-not {\tpmulqr?\.w\t} } } */
