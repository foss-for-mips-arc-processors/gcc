/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3" } */

#include "average-bitwise-convert.h"

/* { dg-final { scan-assembler-times {\mpaadd\.b\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.h\M} 3 } } */
/* { dg-final { scan-assembler-not {\m(padd|psrai|paaddu)\.} } } */
