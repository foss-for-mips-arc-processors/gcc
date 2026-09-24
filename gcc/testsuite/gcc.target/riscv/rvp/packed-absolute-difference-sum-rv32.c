/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "packed-absolute-difference-sum.h"

/* { dg-final { scan-assembler-times {\mpabdsumu\.b\M} 6 } } */
/* { dg-final { scan-assembler-times {\mpabdsumau\.b\M} 4 } } */
/* { dg-final { scan-assembler-times {\mwaddu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mwaddau\M} 1 } } */
