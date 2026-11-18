/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "scalar-uabd-load.h"

/*
** load_byte:
**  lbu\s+[a-z][0-9]+,0\(a0\)
**  lbu\s+[a-z][0-9]+,0\(a1\)
**  pabdu\.h\s+a0,[a-z][0-9]+,[a-z][0-9]+
**  ret
*/

/* Preserve the native zero extension after assembling unaligned halfwords.
   Each input must still be read as two bytes.
** packed_load:
**  lbu\s+[a-z][0-9]+,2\(a0\)
**  lbu\s+[a-z][0-9]+,2\(a1\)
**  lbu\s+[a-z][0-9]+,1\(a0\)
**  lbu\s+[a-z][0-9]+,1\(a1\)
**  slli\s+[a-z][0-9]+,[a-z][0-9]+,8
**  slli\s+[a-z][0-9]+,[a-z][0-9]+,8
**  or\s+[a-z][0-9]+,[a-z][0-9]+,[a-z][0-9]+
**  or\s+[a-z][0-9]+,[a-z][0-9]+,[a-z][0-9]+
**  pabdu\.h\s+a0,[a-z][0-9]+,[a-z][0-9]+
**  ret
*/
/*
** load_half:
**  lhu\s+[a-z][0-9]+,0\(a0\)
**  lhu\s+[a-z][0-9]+,0\(a1\)
**  pabdu\.h\s+a0,[a-z][0-9]+,[a-z][0-9]+
**  ret
*/
/* Both volatile reads must survive, even though they use the same address.
** volatile_load:
**  lhu\s+[a-z][0-9]+,0\(a0\)
**  lhu\s+[a-z][0-9]+,0\(a0\)
**  pabdu\.h\s+a0,[a-z][0-9]+,[a-z][0-9]+
**  ret
*/
