/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "round-mulhi.h"

/* { dg-final { scan-assembler-times {\tpmulhr\.w\t} 3 } } */
/* { dg-final { scan-assembler-times {\tpmulhru\.w\t} 3 } } */
/* { dg-final { scan-assembler-times {\tpmulhrsu\.w\t} 5 } } */
