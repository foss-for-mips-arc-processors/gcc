/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2 -fsanitize=signed-integer-overflow -fdump-tree-optimized" } */

#define TEST_FUNCTIONS_ONLY
#include "../../../gcc.dg/vect/vect-round-half-wrap.c"

/* { dg-final { scan-tree-dump-not {\.AVG_(FLOOR|CEIL)} "optimized" } } */
