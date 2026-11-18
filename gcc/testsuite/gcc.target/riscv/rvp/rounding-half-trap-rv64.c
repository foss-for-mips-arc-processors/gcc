/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2 -ftrapv -fdump-tree-optimized" } */

#define TEST_FUNCTIONS_ONLY
#include "../../../gcc.dg/vect/vect-round-half-wrap.c"

/* The reverse conversion's signed addition can overflow at UINT_MAX.  */
/* { dg-final { scan-tree-dump-not {\.AVG_(FLOOR|CEIL)} "optimized" } } */
