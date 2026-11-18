/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "packed-sad-word.h"

/*
** sad_word8:
**  pabdsumu\.b\s+a0,a0,a1
**  ret
*/
/*
** sad_unsigned8:
**  pabdsumu\.b\s+a0,a0,a1
**  ret
*/
/*
** sad_signed8:
**  pabdsumu\.b\s+a0,a0,a1
**  ret
*/

/*
** sad_shared:
**  pabdsumu\.b\s+a0,a0,a1
**  sd\s+a0,0\(a2\)
**  ret
*/

/* { dg-final { scan-assembler-times {\tpabdsumu\.b\t} 8 } } */
/* { dg-final { scan-assembler-times {\tpabdsumau\.b\t} 2 } } */
