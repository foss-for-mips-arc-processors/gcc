/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "mulhi-low-word.h"

/*
** low_rs:
**	mulhr	a0, a0, a1
**	ret
*/

/*
** low_ru:
**	mulhru	a0, a0, a1
**	ret
*/

/*
** low_rsu:
**	mulhrsu	a0, a0, a1
**	ret
*/

/*
** low_rus:
**	mulhrsu	a0, a1, a0
**	ret
*/
