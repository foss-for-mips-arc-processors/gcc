/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "mulhi-acc-loop.h"

/* Both reductions and word-update maps use the fused operation.  The
   signed count also includes the volatile-input reduction.  */
/* { dg-final { scan-assembler-times {\tpmhracc\.w\t} 3 } } */
/* { dg-final { scan-assembler-times {\tpmhraccu\.w\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpmhraccsu\.w\t} 4 } } */
