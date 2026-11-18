/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3" } */

#define TEST_FUNCTIONS_ONLY
#include "../../../gcc.dg/vect/vect-avg-bitwise-fold.c"

/* { dg-final { scan-assembler-not {\mpaaddu?\.} } } */
