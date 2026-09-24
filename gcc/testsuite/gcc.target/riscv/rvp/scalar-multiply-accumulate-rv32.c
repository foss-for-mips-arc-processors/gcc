/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-multiply-accumulate.h"

/* { dg-final { scan-assembler-times {\mmhacc\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmhracc\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmhaccu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmhraccu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmhaccsu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmhraccsu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmqwacc\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmqrwacc\M} 1 } } */
