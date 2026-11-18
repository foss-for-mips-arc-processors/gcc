/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */
/* { dg-final { scan-assembler-not {\tpmhr?acc(su|u)?\.w\t} } } */

#include "mulhi-acc-store.h"

/*
** memory_su:
**	lw	a5,0\(a0\)
**	mhaccsu	a5,a1, a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** memory_us:
**	lw	a5,0\(a0\)
**	mhaccsu	a5,a2, a1
**	sw	a5,0\(a0\)
**	ret
*/
