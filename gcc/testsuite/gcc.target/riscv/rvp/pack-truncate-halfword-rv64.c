/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "pack-truncate-halfword.h"

/*
** wide_insert:
**  ppaireo\.h\s+a0,\s*a0,\s*a1
**  sext\.w\s+a0,\s*a0
**  ret
*/
/*
** wide_insert_zero:
**  ppaireo\.h\s+a0,\s*a0,\s*a1
**  zext\.w\s+a0,\s*a0
**  ret
*/
/*
** wide_insert_sign:
**  ppaireo\.h\s+a0,\s*a0,\s*a1
**  sext\.w\s+a0,\s*a0
**  ret
*/
/*
** wide_pair_odd:
**  ppairo\.h\s+a0,\s*a0,\s*a1
**  sext\.w\s+a0,\s*a0
**  ret
*/
/*
** wide_pair_odd_zero:
**  ppairo\.h\s+a0,\s*a0,\s*a1
**  zext\.w\s+a0,\s*a0
**  ret
*/
/*
** wide_pair_odd_sign:
**  ppairo\.h\s+a0,\s*a0,\s*a1
**  sext\.w\s+a0,\s*a0
**  ret
*/
