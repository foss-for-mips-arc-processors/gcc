/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "packed-reinterpret.h"

/* Reinterpret operations are bit-preserving and need no memory traffic.  */
/* { dg-final { scan-assembler-times {\mret\M} 82 } } */
/* { dg-final { scan-assembler-not {\m(ld|sd|lw|sw)\M} } } */
