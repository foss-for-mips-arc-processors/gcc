/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "vector-concat-endian.h"

/* Vector element order is separate from physical P packing order.  */
/*
** concat_h_ctor:
**  ppaire\.h\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  ret
*/
/*
** concat_w_ctor:
**  pack\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  ret
*/
