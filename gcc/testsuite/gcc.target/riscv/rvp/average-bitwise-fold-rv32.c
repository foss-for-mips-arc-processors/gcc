/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3" } */

#define TEST_FUNCTIONS_ONLY
#include "../../../gcc.dg/vect/vect-avg-bitwise-fold.c"

/* { dg-final { scan-assembler-not {\mpaaddu?\.} } } */
