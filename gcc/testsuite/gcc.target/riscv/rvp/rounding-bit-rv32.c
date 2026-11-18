/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "rounding-bit.h"

/* { dg-final { scan-assembler-times {\msrari\M} 8 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.h\M} 8 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.dh\M} 8 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.dw\M} 8 } } */
/* { dg-final { scan-assembler-not {\m(padd|psrai|psrli|pli)\.} } } */
