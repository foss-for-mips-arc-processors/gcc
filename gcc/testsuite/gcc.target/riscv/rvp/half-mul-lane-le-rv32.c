/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2 -mlittle-endian" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "half-mul-lane.h"

/*
** pair_low:
**  mul\.h00\s+[^\n]+
**  zext\.h\s+[^\n]+
**  ret
*/

/*
** quad_low:
**  mul\.h00\s+[^\n]+
**  zext\.h\s+[^\n]+
**  ret
*/
