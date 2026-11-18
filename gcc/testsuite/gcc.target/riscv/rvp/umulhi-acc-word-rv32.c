/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "umulhi-acc-word.h"

/*
** umulhi_acc:
**	mhaccu	a0,a1,a2
**	ret
*/

/*
** umulhi_store:
**	lw	a5,0\(a0\)
**	mhaccu	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** umulhi_volatile:
**	lw	a5,0\(a0\)
**	mhaccu	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** umulhi_left:
**	mhaccu	a0,a0,a1
**	ret
*/

/*
** umulhi_right:
**	mhaccu	a1,a0,a1
**	mv	a0,a1
**	ret
*/
