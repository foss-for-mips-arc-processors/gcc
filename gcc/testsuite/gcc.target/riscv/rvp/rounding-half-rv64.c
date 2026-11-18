/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "rounding-half.h"

/* { dg-final { scan-assembler-times {\mpaadd\.b\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.h\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.w\M} 2 } } */
/* { dg-final { scan-assembler-not {\m(padd|psrai|psrli)\.} } } */
