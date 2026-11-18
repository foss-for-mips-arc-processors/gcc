/* { dg-do compile } */
/* { dg-options "-Os -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "packed-sad-zero.h"

/*
** zero4:
**  zext\.w\s+a1,a1
**  zext\.w\s+a0,a0
**  pabdsumu\.b\s+a0,a0,a1
**  ret
*/

/* { dg-final { scan-assembler-times {\tpabdsumu\.b\t} 5 } } */
/* { dg-final { scan-assembler-times {\tpabdsumau\.b\t} 3 } } */
