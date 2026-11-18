/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "pack-insert-halfword.h"

/*
** insert_low_halfword:
**  ppaireo\.h\s+a0,\s*a0,\s*a1
**  sext\.w\s+a0,\s*a0
**  ret
*/
/*
** store_insert_low_halfword:
**  ppaireo\.h\s+a2,\s*a1,\s*a2
**  sw\s+a2,\s*0\(a0\)
**  ret
*/
/*
** pair_cross_halfwords:
**  ppairoe\.h\s+a0,\s*a0,\s*a1
**  sext\.w\s+a0,\s*a0
**  ret
*/
/*
** store_pair_cross_halfwords:
**  ppairoe\.h\s+a1,\s*a1,\s*a2
**  sw\s+a1,\s*0\(a0\)
**  ret
*/
/*
** pair_odd_halfwords:
**  ppairo\.h\s+a0,\s*a0,\s*a1
**  sext\.w\s+a0,\s*a0
**  ret
*/
/*
** store_pair_odd_halfwords:
**  ppairo\.h\s+a2,\s*a1,\s*a2
**  sw\s+a2,\s*0\(a0\)
**  ret
*/

