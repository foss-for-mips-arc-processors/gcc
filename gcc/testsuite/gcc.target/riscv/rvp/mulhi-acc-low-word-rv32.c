/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "mulhi-acc-low-word.h"

/*
** low_su:
**	mhaccsu	a0,a1, a2
**	ret
*/

/*
** low_rsu:
**	mhraccsu	a0,a1, a2
**	ret
*/

/*
** low_us:
**	mhaccsu	a0,a2, a1
**	ret
*/

/*
** low_rus:
**	mhraccsu	a0,a2, a1
**	ret
*/
