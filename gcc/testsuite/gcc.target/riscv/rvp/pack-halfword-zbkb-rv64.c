/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp_zbkb -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "pack-halfword.h"

/*
** pack_halfwords:
**  packw\s+a0,a0,a1
**  ret
*/
/*
** store_halfwords:
**  packw\s+a2,a1,a2
**  sw\s+a2,0\(a0\)
**  ret
*/
/*
** halfword_sign:
**  slli\s+[a-z][0-9]+,a1,48
**  srli\s+a0,[a-z][0-9]+,63
**  ret
*/
