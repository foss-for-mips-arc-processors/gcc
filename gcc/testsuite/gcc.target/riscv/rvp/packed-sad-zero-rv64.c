/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "packed-sad-zero.h"

/*
** zero8d:
**  pabdsumu\.b\s+a0,a0,a1
**  ret
*/

/* { dg-final { scan-assembler-times {\tpabdsumu\.b\t} 5 } } */
/* { dg-final { scan-assembler-times {\tpabdsumau\.b\t} 3 } } */
