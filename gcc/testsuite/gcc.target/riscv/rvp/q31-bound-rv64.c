/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian -fvect-cost-model=unlimited --param=vect-epilogues-nomask=0" } */

#include "q31-bound.h"

/* Reuse the offset start in the end address instead of adding it again.  */
/* { dg-final { scan-assembler-times {\tsh3add\s} 1 } } */
/* { dg-final { scan-assembler-not {\tadd\s} } } */
