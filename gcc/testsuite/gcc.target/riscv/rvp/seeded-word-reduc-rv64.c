/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

/*
** scalar:
**  predsum.ws\ta0,a0,a1
**  sext.w\ta0,a0
**  ret
*/
/*
** vector:
**  predsum.ws\ta0,a0,a1
**  sext.w\ta0,a0
**  ret
*/
/*
** widened:
**  predsum.ws\ta0,a0,a1
**  zext.w\ta0,a0
**  ret
*/
/*
** store:
**  predsum.ws\ta0,a0,a1
**  sw\ta0,0\(a2\)
**  ret
*/

#include "seeded-word-reduc.h"

/* Shared high words and different-source or full-width sums must not fold.  */
/* { dg-final { scan-assembler-times {\tpredsum\.ws\t} 7 } } */
/* { dg-final { check-function-bodies "**" "" } } */
