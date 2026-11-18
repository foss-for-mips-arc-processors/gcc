/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "pack-masked-halfword.h"

/*
** pack_even_halves:
**  ppaire\.h\s+a0,\s*a0,\s*a1
**  ret
*/
/*
** pack_even_odd_halves:
**  ppaireo\.h\s+a0,\s*a0,\s*a1
**  ret
*/
/*
** pack_odd_even_halves:
**  ppairoe\.h\s+a0,\s*a0,\s*a1
**  ret
*/
/*
** pack_odd_halves:
**  ppairo\.h\s+a0,\s*a0,\s*a1
**  ret
*/
/*
** mask_even_halves:
**  ppaire\.h\s+a0,\s*a0,\s*zero
**  ret
*/
/*
** mask_odd_halves:
**  ppaireo\.h\s+a0,\s*zero,\s*a0
**  ret
*/
/*
** shift_even_halves:
**  ppaire\.h\s+a0,\s*zero,\s*a0
**  ret
*/
/*
** shift_odd_halves:
**  ppairo\.h\s+a0,\s*a0,\s*zero
**  ret
*/
