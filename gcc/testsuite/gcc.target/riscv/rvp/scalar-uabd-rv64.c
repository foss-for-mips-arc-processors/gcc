/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "scalar-uabd.h"

/* { dg-final { scan-assembler-times {\tpabdu\.h\t} 6 } } */
/* { dg-final { scan-assembler-times {\tabsw\t} 2 } } */
/* { dg-final { scan-assembler-not {\tsext\.w\t} } } */
