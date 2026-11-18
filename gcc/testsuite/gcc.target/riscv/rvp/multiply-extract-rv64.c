/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#include "multiply-extract.h"

/* The RV32 scalar halfword multiply instructions are not available here.  */
/* { dg-final { scan-assembler-not {\tmul\.h[01][01]\t} } } */

/*
** quad_mul_0:
**  pmul\.w\.h00\s+[^\n]+
**  pmul\.w\.h11\s+[^\n]+
**  ppaire\.h\s+[^\n]+
**  zext\.h\s+[^\n]+
**  ret
*/
