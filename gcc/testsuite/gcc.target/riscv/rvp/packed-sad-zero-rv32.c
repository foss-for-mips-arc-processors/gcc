/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "packed-sad-zero.h"

/*
** zero4:
**  pabdsumu\.b\s+a0,a0,a1
**  ret
*/

/*
** zero8w:
**  pabdsumu\.b\s+a5,a0,a2
**  pabdsumau\.b\s+a5,a1,a3
**  mv\s+a0,a5
**  ret
*/

/* { dg-final { scan-assembler-times {\tpabdsumu\.b\t} 9 } } */
/* { dg-final { scan-assembler-times {\tpabdsumau\.b\t} 4 } } */
