/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "average-bitwise.h"

/* { dg-final { scan-assembler-times {\mpaadd\.b\M} 6 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.b\M} 6 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.h\M} 6 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.h\M} 6 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.w\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.w\M} 3 } } */
/* { dg-final { scan-assembler-not {\m(padd|psrai|psrli)\.} } } */
