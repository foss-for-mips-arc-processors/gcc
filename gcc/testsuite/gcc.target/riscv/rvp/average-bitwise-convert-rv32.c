/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3" } */

#include "average-bitwise-convert.h"

/* { dg-final { scan-assembler-times {\mpaadd\.db\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.dh\M} 3 } } */
/* { dg-final { scan-assembler-not {\m(padd|psrai|paaddu)\.} } } */
