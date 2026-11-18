/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "word-mulhi.h"

/*
** word_su:
**	pmulhsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** word_us:
**	pmulhsu.w	a0,a1,a0
**	sext.w	a0,a0
**	ret
*/

/*
** word_su_zero:
**	pmulhsu.w	a0,a0,a1
**	zext.w	a0,a0
**	ret
*/

/*
** word_us_zero:
**	pmulhsu.w	a0,a1,a0
**	zext.w	a0,a0
**	ret
*/

/*
** word_su_sign:
**	pmulhsu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** word_us_sign:
**	pmulhsu.w	a0,a1,a0
**	sext.w	a0,a0
**	ret
*/

/*
** word_su_store:
**	pmulhsu.w	a1,a1,a2
**	sw	a1,0\(a0\)
**	ret
*/

/*
** word_us_store:
**	pmulhsu.w	a2,a2,a1
**	sw	a2,0\(a0\)
**	ret
*/

/*
** word_s_store:
**	pmulh.w	a1,a1,a2
**	sw	a1,0\(a0\)
**	ret
*/

/*
** word_su_shared:
**	zext.w	a2,a2
**	mul	a1,a1,a2
**	sd	a1,0\(a0\)
**	srai	a0,a1,32
**	ret
*/

/*
** word_us_shared:
**	zext.w	a1,a1
**	mul	a2,a1,a2
**	sd	a2,0\(a0\)
**	srai	a0,a2,32
**	ret
*/

/*
** unknown_product:
**	mul	a0,a0,a1
**	srli	a0,a0,32
**	ret
*/

/*
** unknown_left:
**	zext.w	a1,a1
**	mul	a0,a1,a0
**	srli	a0,a0,32
**	ret
*/

/*
** shift31:
**	zext.w	a1,a1
**	mul	a0,a0,a1
**	srai	a0,a0,31
**	ret
*/

/*
** shift33:
**	zext.w	a1,a1
**	mul	a0,a0,a1
**	srai	a0,a0,33
**	ret
*/
