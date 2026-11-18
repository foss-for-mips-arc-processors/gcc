/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "bswap16-scalar.h"

/*
** swap_store:
**  ppairoe\.b\s+a1,\s*a1,\s*a1
**  sh\s+a1,0\(a0\)
**  ret
*/
/*
** swap_volatile:
**  lhu\s+a5,0\(a1\)
**  ppairoe\.b\s+a5,\s*a5,\s*a5
**  sh\s+a5,0\(a0\)
**  ret
*/
