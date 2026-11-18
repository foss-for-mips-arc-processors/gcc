/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "mulhi-acc-store.h"

/*
** memory_s:
**	lw	a5,0\(a0\)
**	pmhacc.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** memory_su:
**	lw	a5,0\(a0\)
**	pmhaccsu.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** memory_us:
**	lw	a5,0\(a0\)
**	pmhaccsu.w	a5,a2,a1
**	sw	a5,0\(a0\)
**	ret
*/

/*
** memory_rs:
**	lw	a5,0\(a0\)
**	pmhracc.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** memory_ru:
**	lw	a5,0\(a0\)
**	pmhraccu.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** memory_rsu:
**	lw	a5,0\(a0\)
**	pmhraccsu.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** memory_rus:
**	lw	a5,0\(a0\)
**	pmhraccsu.w	a5,a2,a1
**	sw	a5,0\(a0\)
**	ret
*/

/*
** packed_s:
**	lw	a5,0\(a0\)
**	pmhacc.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** packed_u:
**	lw	a5,0\(a0\)
**	pmhaccu.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** packed_su:
**	lw	a5,0\(a0\)
**	pmhaccsu.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** packed_rs:
**	lw	a5,0\(a0\)
**	pmhracc.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** packed_ru:
**	lw	a5,0\(a0\)
**	pmhraccu.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** packed_rsu:
**	lw	a5,0\(a0\)
**	pmhraccsu.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** volatile_sum:
**	lw	a5,0\(a0\)
**	pmhacc.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** memory_u:
**	lw	a5,0\(a0\)
**	pmhaccu.w	a5,a1,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** wide_sum:
**	mul	a1,a1,a2
**	ld	a5,0\(a0\)
**	srli	a1,a1,32
**	add	a5,a5,a1
**	sd	a5,0\(a0\)
**	ret
*/

/*
** shared_high:
**	pmulh.w	a2,a2,a3
**	sw	a2,0\(a1\)
**	lw	a5,0\(a0\)
**	addw	a5,a5,a2
**	sw	a5,0\(a0\)
**	ret
*/

/*
** shift31:
**	mul	a1,a1,a2
**	lw	a5,0\(a0\)
**	srai	a1,a1,31
**	addw	a5,a5,a1
**	sw	a5,0\(a0\)
**	ret
*/

/*
** unknown_inputs:
**	mul	a1,a1,a2
**	lw	a5,0\(a0\)
**	srli	a1,a1,32
**	addw	a5,a5,a1
**	sw	a5,0\(a0\)
**	ret
*/
