/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "full-half-mul.h"

/*
** full_mul:
**  pmul\.w\.h00\s+[^\n]+
**  pmul\.w\.h11\s+[^\n]+
**  ppaire\.h\s+[^\n]+
**  ret
*/

/*
** full_mul_signed_bits:
**  pmul\.w\.h00\s+[^\n]+
**  pmul\.w\.h11\s+[^\n]+
**  ppaire\.h\s+[^\n]+
**  ret
*/

/*
** full_square:
**  pmul\.w\.h00\s+[^\n]+
**  pmul\.w\.h11\s+[^\n]+
**  ppaire\.h\s+[^\n]+
**  ret
*/
