/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3" } */

#define TEST_FUNCTIONS_ONLY
#include "../../../gcc.dg/vect/vect-round-half.c"

/* { dg-final { scan-assembler-times {\mpaadd\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.[bhw]\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.w\M} 1 } } */
/* { dg-final { scan-assembler-not {\m(padd|psrai|psrli)\.} } } */
