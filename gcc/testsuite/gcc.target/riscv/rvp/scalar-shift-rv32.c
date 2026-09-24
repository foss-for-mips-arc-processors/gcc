/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-shift.h"

/* { dg-final { scan-assembler-times {\mssha\M} 2 } } */
/* { dg-final { scan-assembler-times {\msshar\M} 2 } } */
/* { dg-final { scan-assembler-times {\msshl\M} 1 } } */
/* { dg-final { scan-assembler-times {\msshlr\M} 1 } } */
/* { dg-final { scan-assembler-times {\msslai\M} 4 } } */
/* { dg-final { scan-assembler-times {\msrai\M} 2 } } */
/* { dg-final { scan-assembler-times {\msrari\M} 2 } } */
