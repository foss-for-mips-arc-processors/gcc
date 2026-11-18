/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "rounding-bit.h"

/* { dg-final { scan-assembler-times {\msrari\M} 8 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.h\M} 16 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.w\M} 8 } } */
/* { dg-final { scan-assembler-not {\m(padd|psrai|psrli|pli)\.} } } */
