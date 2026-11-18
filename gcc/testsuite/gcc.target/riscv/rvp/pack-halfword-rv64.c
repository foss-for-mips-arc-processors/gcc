/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "pack-halfword.h"

/*
** pack_halfwords:
**  ppaire\.h\s+a0,\s*a0,\s*a1
**  sext\.w\s+a0,a0
**  ret
*/
/*
** store_halfwords:
**  ppaire\.h\s+a2,\s*a1,\s*a2
**  sw\s+a2,0\(a0\)
**  ret
*/
/*
** halfword_sign:
**  slli\s+[a-z][0-9]+,a1,48
**  srli\s+a0,[a-z][0-9]+,63
**  ret
*/
