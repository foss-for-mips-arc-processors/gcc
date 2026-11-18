/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcpv -mabi=ilp32d -mlittle-endian -fno-tree-vectorize" } */

#include "round-mulhi.h"

/* { dg-final { scan-assembler-times {\tmulhr\t} 2 } } */
/* { dg-final { scan-assembler-times {\tmulhru\t} 3 } } */
/* { dg-final { scan-assembler-times {\tmulhrsu\t} 4 } } */
