/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "packed-absolute-difference-sum.h"

/* { dg-final { scan-assembler-times {\mpabdsumu\.b\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpabdsumau\.b\M} 3 } } */
