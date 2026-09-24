/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-multiply.h"

/* { dg-final { scan-assembler-times {\mmulh\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmulhr\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmulhu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmulhru\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmulhsu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmulhrsu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmulq\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmulqr\M} 1 } } */
