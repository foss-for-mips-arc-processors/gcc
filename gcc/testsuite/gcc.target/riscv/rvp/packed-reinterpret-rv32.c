/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "packed-reinterpret.h"

/* Reinterpret operations are bit-preserving and need no memory traffic.  */
/* { dg-final { scan-assembler-times {\mret\M} 82 } } */
/* { dg-final { scan-assembler-not {\m(lw|sw)\M} } } */
