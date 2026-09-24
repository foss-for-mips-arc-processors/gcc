/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-data.h"

/* { dg-final { scan-assembler-times {\mabs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmseq\M} 4 } } */
/* { dg-final { scan-assembler-times {\mmslt\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmsgt\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmsltu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mmsgtu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnot\M} 6 } } */
/* { dg-final { scan-assembler-times {\m(merge|mvmn?)\M} 6 } } */
