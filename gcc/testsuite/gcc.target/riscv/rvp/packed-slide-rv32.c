/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "packed-slide.h"

/* The dynamic 64-bit forms contain two paths so that shifts can cross the
   32-bit register-pair boundary.  */
/* { dg-final { scan-assembler-times {\mslx\M} 38 } } */
/* { dg-final { scan-assembler-times {\msrx\M} 38 } } */
/* { dg-final { scan-assembler-times {\mbeq\M} 12 } } */
/* { dg-final { scan-assembler-times {\mpack\M} 2 } } */
/* { dg-final { scan-assembler-times {\mppairoe\.h\M} 2 } } */
