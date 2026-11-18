/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "bswap16-scalar-extend.h"

/*
** swap_unsigned:
**  rev8\s+a0,a0
**  srli\s+a0,a0,16
**  ret
*/
/*
** swap_signed:
**  rev8\s+a0,a0
**  srai\s+a0,a0,16
**  ret
*/
/*
** swap_shared:
**  rev8\s+([a-z][0-9]+),a1
**  srli\s+\1,\1,16
**  sh\s+\1,0\(a0\)
**  add\s+a0,\1,a1
**  ret
*/
