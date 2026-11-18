/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

/*
** exact:
**  pmulq.h\ta0,a0,a1
**  ret
*/
/*
** rounding:
**  pmulqr.h\ta0,a0,a1
**  ret
*/

#include "q15-pair.h"

/* Exact, widened and shared-product Q15 results use saturating operations.  */
/* { dg-final { scan-assembler-times {\tpmulq\.h\t} 3 } } */
/* { dg-final { scan-assembler-times {\tpmulqr\.h\t} 3 } } */
/* { dg-final { check-function-bodies "**" "" } } */
