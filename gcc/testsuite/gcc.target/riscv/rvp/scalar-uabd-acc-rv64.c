/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
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

/* Preserve the original high bits for the store, and mask the complete
   native inputs before accumulating their unsigned byte difference.
** high_acc:
**  xor\s+[a-z][0-9]+,a0,a1
**  andi\s+[a-z][0-9]+,a0,0xff
**  andi\s+[a-z][0-9]+,a1,0xff
**  pabdsumau\.b\s+a2,[a-z][0-9]+,[a-z][0-9]+
**  sd\s+[a-z][0-9]+,0\(a3\)
**  mv\s+a0,a2
**  ret
*/

/* { dg-final { scan-assembler-times {\tpabdsumau\.b\t} 5 } } */
/* { dg-final { scan-assembler-times {\tpabdu\.h\t} 2 } } */
