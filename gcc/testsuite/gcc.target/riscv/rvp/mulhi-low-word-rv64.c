/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "mulhi-low-word.h"

/*
** round_su:
**	pmulhrsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** round_us:
**	pmulhrsu.w	a0,a1,a0
**	sext.w	a0,a0
**	ret
*/

/*
** round_su_wide:
**	pmulhrsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** low_rsu:
**	pmulhrsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** sign_rsu:
**	pmulhrsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** zero_rsu:
**	pmulhrsu.w	a0,a0,a1
**	zext.w	a0,a0
**	ret
*/

/*
** store_rsu:
**	pmulhrsu.w	a1,a1,a2
**	sw	a1,0\(a0\)
**	ret
*/

/*
** full_s:
**	zext.w	a1,a1
**	pmulh.w	a0,a0,a1
**	ret
*/

/*
** packed_s:
**	pmulh.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** both_s:
**	pmulh.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** builtin_s:
**	pmulh.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** full_u:
**	zext.w	a1,a1
**	pmulhu.w	a0,a0,a1
**	ret
*/

/*
** packed_u:
**	pmulhu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** both_u:
**	pmulhu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** builtin_u:
**	pmulhu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** full_su:
**	zext.w	a1,a1
**	pmulhsu.w	a0,a0,a1
**	ret
*/

/*
** packed_su:
**	pmulhsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** both_su:
**	pmulhsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** builtin_su:
**	pmulhsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** full_rs:
**	zext.w	a1,a1
**	pmulhr.w	a0,a0,a1
**	ret
*/

/*
** packed_rs:
**	pmulhr.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** both_rs:
**	pmulhr.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** builtin_rs:
**	pmulhr.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** full_ru:
**	zext.w	a1,a1
**	pmulhru.w	a0,a0,a1
**	ret
*/

/*
** packed_ru:
**	pmulhru.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** both_ru:
**	pmulhru.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** builtin_ru:
**	pmulhru.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** full_rsu:
**	zext.w	a1,a1
**	pmulhrsu.w	a0,a0,a1
**	ret
*/

/*
** packed_rsu:
**	pmulhrsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** both_rsu:
**	pmulhrsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** builtin_rsu:
**	pmulhrsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/
