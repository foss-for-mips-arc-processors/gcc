/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian --param=max-combine-insns=3" } */

#include "round-mulhi.h"

/* With three-input combinations, the same-sign loops use packed multiply
   instructions, but the scalar forms still need four inputs.  */
/* { dg-final { scan-assembler-times {\tpmulhr\.w\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpmulhru\.w\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpmulhrsu\.w\t} 5 } } */
