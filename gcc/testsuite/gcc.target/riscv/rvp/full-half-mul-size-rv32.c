/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -Os" } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "full-half-mul.h"

/*
** full_mul:
**  mul\.h(?:00|11)\s+[^\n]+
**  mul\.h(?:00|11)\s+[^\n]+
**  mul\.h(?:00|11)\s+[^\n]+
**  mul\.h(?:00|11)\s+[^\n]+
**  pack\s+[^\n]+
**  pack\s+[^\n]+
**  ret
*/

/*
** full_mul_signed_bits:
**  mul\.h(?:00|11)\s+[^\n]+
**  mul\.h(?:00|11)\s+[^\n]+
**  mul\.h(?:00|11)\s+[^\n]+
**  mul\.h(?:00|11)\s+[^\n]+
**  pack\s+[^\n]+
**  pack\s+[^\n]+
**  ret
*/

/*
** full_square:
**  mul\.h(?:00|11)\s+[^\n]+
**  mul\.h(?:00|11)\s+[^\n]+
**  mul\.h(?:00|11)\s+[^\n]+
**  mul\.h(?:00|11)\s+[^\n]+
**  pack\s+[^\n]+
**  pack\s+[^\n]+
**  ret
*/
