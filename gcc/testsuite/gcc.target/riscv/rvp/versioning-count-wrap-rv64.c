/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fdump-tree-vect-details" } */

#define TEST_FUNCTIONS_ONLY
#include "../../../gcc.dg/vect/vect-versioning-niters.c"

/* Both counted loops are versioned, but only the nonwrapping count may
   use the direct comparison.  Keep the subtract-and-wrap guard for the
   unsigned-char do-while loop, including its 256-iteration case.  */
/* { dg-final { scan-tree-dump-times "vectorized 1 loops in function" 2 "vect" } } */
/* { dg-final { scan-tree-dump-times "versioning compares nonwrapping iteration count" 1 "vect" } } */
/* { dg-final { scan-assembler-times {addiw[ \t]+[a-z0-9]+,[ \t]*a2,[ \t]*-1\M} 1 } } */
