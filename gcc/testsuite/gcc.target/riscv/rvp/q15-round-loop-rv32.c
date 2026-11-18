/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-vect-details" } */

#define Q15_ROUND_POSITIVE_ONLY
#include "q15-round-loop.h"

/* The saturated call must be in the vector loop, not just its scalar tail.  */
/* { dg-final { scan-tree-dump-times "vectorized 1 loops in function" 5 "vect" } } */
/* { dg-final { scan-tree-dump-times {add new stmt: vect_[^=]* = \.SAT_MULHRS } 5 "vect" } } */
/* { dg-final { scan-assembler {\tpmulqr\.h\t} } } */
