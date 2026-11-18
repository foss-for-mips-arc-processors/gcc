/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "mulhi-acc.h"

/*
** acc_s:
**	mhacc	a0,a1,a2
**	ret
*/
/*
** acc_u:
**	mhaccu	a0,a1,a2
**	ret
*/
/*
** acc_su:
**	mhaccsu	a0,a1, a2
**	ret
*/
/*
** acc_us:
**	mhaccsu	a0,a2, a1
**	ret
*/
/*
** racc_s:
**	mhracc	a0,a1,a2
**	ret
*/
/*
** racc_u:
**	mhraccu	a0,a1,a2
**	ret
*/
/*
** racc_su:
**	mhraccsu	a0,a1, a2
**	ret
*/
/*
** racc_us:
**	mhraccsu	a0,a2, a1
**	ret
*/
