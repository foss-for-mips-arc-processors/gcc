/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "mulhi-acc-low-word.h"

/*
** low_su:
**	pmhaccsu.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/

/*
** low_rsu:
**	pmhraccsu.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/

/*
** low_us:
**	pmhaccsu.w	a0,a2,a1
**	sext.w	a0,a0
**	ret
*/

/*
** low_rus:
**	pmhraccsu.w	a0,a2,a1
**	sext.w	a0,a0
**	ret
*/

/*
** zero_su:
**	pmhaccsu.w	a0,a1,a2
**	zext.w	a0,a0
**	ret
*/

/*
** zero_rsu:
**	pmhraccsu.w	a0,a1,a2
**	zext.w	a0,a0
**	ret
*/

/*
** store_su:
**	pmhaccsu.w	a1,a2,a3
**	sw	a1,0\(a0\)
**	ret
*/

/*
** store_rsu:
**	pmhraccsu.w	a1,a2,a3
**	sw	a1,0\(a0\)
**	ret
*/

/*
** full_s:
**	zext.w	a2,a2
**	pmhacc.w	a0,a1,a2
**	ret
*/

/*
** packed_s:
**	pmhacc.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/

/*
** full_u:
**	zext.w	a2,a2
**	pmhaccu.w	a0,a1,a2
**	ret
*/

/*
** packed_u:
**	pmhaccu.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/

/*
** full_su:
**	zext.w	a2,a2
**	pmhaccsu.w	a0,a1,a2
**	ret
*/

/*
** packed_su:
**	pmhaccsu.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/

/*
** full_rs:
**	zext.w	a2,a2
**	pmhracc.w	a0,a1,a2
**	ret
*/

/*
** packed_rs:
**	pmhracc.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/

/*
** full_ru:
**	zext.w	a2,a2
**	pmhraccu.w	a0,a1,a2
**	ret
*/

/*
** packed_ru:
**	pmhraccu.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/

/*
** full_rsu:
**	zext.w	a2,a2
**	pmhraccsu.w	a0,a1,a2
**	ret
*/

/*
** packed_rsu:
**	pmhraccsu.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/
