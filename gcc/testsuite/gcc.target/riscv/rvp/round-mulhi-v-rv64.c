/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcpv -mabi=lp64d -mlittle-endian -fno-tree-vectorize" } */

#include "round-mulhi.h"

/* { dg-final { scan-assembler-times {\tpmulhr\.w\t} 3 } } */
/* { dg-final { scan-assembler-times {\tpmulhru\.w\t} 3 } } */
/* { dg-final { scan-assembler-times {\tpmulhrsu\.w\t} 5 } } */
