/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "autovec-dot64.h"

/* Only the entry pointer and final result need copies.  Do not copy the
   doubleword accumulator into and out of a temporary on every iteration.  */
/* { dg-final { scan-assembler-times {\tmv\t} 4 } } */
/* Four native pair clears and four final result copies.  */
/* { dg-final { scan-assembler-times {\taddd\t} 8 } } */
/* { dg-final { scan-assembler-times {\taddd\t[^,]+,x0,x0} 4 } } */
