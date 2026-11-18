/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "mulhi-acc.h"

/*
** acc_s:
**	pmhacc.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/
/*
** acc_u:
**	pmhaccu.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/
/*
** acc_su:
**	...
**	pmhaccsu.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/
/*
** acc_us:
**	...
**	pmhaccsu.w	a0,a2,a1
**	sext.w	a0,a0
**	ret
*/
/*
** racc_s:
**	pmhracc.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/
/*
** racc_u:
**	pmhraccu.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/
/*
** racc_su:
**	...
**	pmhraccsu.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/
/*
** racc_us:
**	...
**	pmhraccsu.w	a0,a2,a1
**	sext.w	a0,a0
**	ret
*/
