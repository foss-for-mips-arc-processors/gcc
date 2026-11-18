/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-widening_mul" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

/*
** q15_scalar:
**  pmulq\.h\s+a0,a0,a1
**  sext\.h\s+a0,a0
**  ret
*/
/*
** q15_scalar_round:
**  pmulqr\.h\s+a0,a0,a1
**  sext\.h\s+a0,a0
**  ret
*/
/*
** q15_scalar_two_shifts:
**  pmulqr\.h\s+a0,a0,a1
**  sext\.h\s+a0,a0
**  ret
*/
#include "q15-scalar.h"

/* { dg-final { scan-tree-dump-times {\.SAT_MULHS \(} 6 "widening_mul" } } */
/* { dg-final { scan-tree-dump-times {\.SAT_MULHRS \(} 5 "widening_mul" } } */
