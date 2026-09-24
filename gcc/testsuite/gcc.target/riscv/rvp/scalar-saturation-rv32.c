/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-saturation.h"

/* { dg-final { scan-assembler-times {\msati\M} 2 } } */
/* { dg-final { scan-assembler-times {\musati\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsati\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.dh\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsati\.dw\M} 1 } } */
