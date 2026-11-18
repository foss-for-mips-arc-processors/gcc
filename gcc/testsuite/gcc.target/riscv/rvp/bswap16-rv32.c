/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "bswap16.h"

/*
** swap16_word:
**  ppairoe\.b\s+a0,\s*a0,\s*a0
**  ret
*/
/*
** swap16_loop:
**  ...
**  ppairoe\.d?b\s+[^\n]+
**  ...
*/
