/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "scalar-uabd-word.h"

/*
** word_byte_add:
**  pabdu\.h\s+a0,a0,a1
**  addw\s+a0,a0,a2
**  ret
*/
/*
** word_half_add:
**  pabdu\.h\s+a0,a0,a1
**  addw\s+a0,a0,a2
**  ret
*/
/*
** word_load_add:
**  lhu\s+[a-z][0-9]+,0\(a0\)
**  lhu\s+[a-z][0-9]+,0\(a1\)
**  pabdu\.h\s+[a-z][0-9]+,[a-z][0-9]+,[a-z][0-9]+
**  addw\s+a0,[a-z][0-9]+,a2
**  ret
*/

/* { dg-final { scan-assembler-times {\tpabdu\.h\t} 4 } } */
/* { dg-final { scan-assembler-not {\tabsw\t} } } */
/* { dg-final { scan-assembler-not {\tsext\.w\t} } } */
