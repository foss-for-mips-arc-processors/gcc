/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-arithmetic.h"

/* { dg-final { scan-assembler-times {\msadd\M} 1 } } */
/* { dg-final { scan-assembler-times {\msaddu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mssub\M} 1 } } */
/* { dg-final { scan-assembler-times {\mssubu\M} 1 } } */
/* { dg-final { scan-assembler-times {\maadd\M} 1 } } */
/* { dg-final { scan-assembler-times {\maaddu\M} 1 } } */
/* { dg-final { scan-assembler-times {\masub\M} 1 } } */
/* { dg-final { scan-assembler-times {\masubu\M} 1 } } */
/* { dg-final { scan-assembler-times {\mssh1sadd\M} 1 } } */
