/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "rounding-half.h"

/* { dg-final { scan-assembler-times {\mpaadd\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.db\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.db\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.dh\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.dw\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.dh\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.dw\M} 2 } } */
/* { dg-final { scan-assembler-not {\m(padd|psrai|psrli)\.} } } */
