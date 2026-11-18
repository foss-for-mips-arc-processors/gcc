/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "round-mulhi.h"

/* { dg-final { scan-assembler-times {\tmulhr\t} 2 } } */
/* { dg-final { scan-assembler-times {\tmulhru\t} 3 } } */
/* { dg-final { scan-assembler-times {\tmulhrsu\t} 4 } } */
