/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "umulhi-acc-word.h"

/*
** umulhi_acc:
**	pmhaccu.w	a0,a1,a2
**	sext.w	a0,a0
**	ret
*/

/*
** umulhi_store:
**	lw	a5,0\(a0\)
**	pmhaccu.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** umulhi_store_return:
**	lw	a5,0\(a0\)
**	pmhaccu.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	sext.w	a0,a5
**	ret
*/

/*
** umulhi_volatile:
**	lw	a5,0\(a0\)
**	pmhaccu.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** umulhi_left:
**	pmhaccu.w	a0,a0,a1
**	sext.w	a0,a0
**	ret
*/

/*
** umulhi_right:
**	pmhaccu.w	a1,a0,a1
**	sext.w	a0,a1
**	ret
*/

/*
** umulhi_wide:
**	mulu.w00	a1, a1, a2
**	srli	a1,a1,32
**	add	a0,a1,a0
**	ret
*/
