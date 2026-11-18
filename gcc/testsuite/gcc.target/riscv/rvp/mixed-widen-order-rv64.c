/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "mixed-widen-order-run.c"

/*
** word_product:
**	mulsu.w00	a0, a0, a1
**	ret
*/

/*
** reverse_product:
**	mulsu.w00	a0, a1, a0
**	ret
*/
