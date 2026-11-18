/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */
/* { dg-final { scan-assembler-not {\tpmulh(su|u)?\.w\t} } } */

#include "word-mulhi.h"

/*
** word_su:
**	wmulsu	a0, a0, a1
**	mv	a0,a1
**	ret
*/

/*
** word_us:
**	wmulsu	a0, a1, a0
**	mv	a0,a1
**	ret
*/
