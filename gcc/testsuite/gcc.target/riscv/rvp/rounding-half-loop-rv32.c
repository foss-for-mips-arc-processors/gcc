/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3" } */

#define TEST_FUNCTIONS_ONLY
#include "../../../gcc.dg/vect/vect-round-half.c"

/* { dg-final { scan-assembler-times {\mpaadd\.db\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.d[bhw]\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.dh\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.dw\M} 1 } } */
/* { dg-final { scan-assembler-not {\m(padd|psrai|psrli)\.} } } */
