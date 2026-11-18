/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mbig-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "vector-concat-endian.h"

/*
** concat_h_set0:
**  ppaire\.h\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  ret
*/
/*
** concat_h_set1:
**  ppaireo\.h\s+[a-z][a-z0-9]*,\s*a1,\s*a0
**  ret
*/

/* Vector element order is separate from physical P packing order.  */
/*
** concat_h_ctor:
**  ppaire\.h\s+[a-z][a-z0-9]*,\s*a1,\s*a0
**  ret
*/
