/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "scalar-uabd-acc.h"

/*
** loop_acc:
**  ...
**  pabdsumau\.b\s+[a-z][0-9]+,[a-z][0-9]+,[a-z][0-9]+
**  ...
*/

/*
** overlap_acc:
**  pabdsumau\.b\s+a0,a0,a1
**  ret
*/

/* { dg-final { scan-assembler-times {\tpabdsumau\.b\t} 5 } } */
/* { dg-final { scan-assembler-times {\tpabdu\.h\t} 2 } } */
