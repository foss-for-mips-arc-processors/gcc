/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "average-bitwise.h"

/* { dg-final { scan-assembler-times {\mpaadd\.b\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.b\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.h\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.h\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.db\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.db\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.dh\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.dh\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.dw\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.dw\M} 3 } } */
/* { dg-final { scan-assembler-not {\m(padd|psrai|psrli)\.} } } */
