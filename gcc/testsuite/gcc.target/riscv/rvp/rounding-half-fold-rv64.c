/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fdump-tree-optimized" } */

#define TEST_FUNCTIONS_ONLY
#include "../../../gcc.dg/vect/vect-round-half-fold.c"

/* { dg-final { scan-tree-dump-not {\.AVG_(FLOOR|CEIL)} "optimized" } } */
/* { dg-final { scan-assembler-not {\m(paaddu?|psrari)\.} } } */
