/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "pack-halfword.h"

/*
** pack_halfwords:
**  pack\s+a0,a0,a1
**  ret
*/
/*
** store_halfwords:
**  pack\s+a2,a1,a2
**  sw\s+a2,0\(a0\)
**  ret
*/
/*
** halfword_sign:
**  slli\s+([a-z][0-9]+),a1,16
**  srli\s+a0,\1,31
**  ret
*/
