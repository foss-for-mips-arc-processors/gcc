/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "scalar-uabd.h"

/* { dg-final { scan-assembler-times {\tpabdu\.h\t} 6 } } */
/* { dg-final { scan-assembler-times {\tabs\t} 2 } } */
