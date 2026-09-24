/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "packed-narrowing-clip-pair.h"

/* { dg-final { scan-assembler-times {\mpnclipi\.b\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpnclipiu\.b\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpnclipi\.h\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpnclipiu\.h\M} 3 } } */
/* { dg-final { scan-assembler-times {\mnclipi\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnclipiu\M} 2 } } */
