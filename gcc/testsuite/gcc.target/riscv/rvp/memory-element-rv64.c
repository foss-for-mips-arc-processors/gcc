/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -mstrict-align -O2" } */

#include <riscv_packed_simd.h>
#include "memory-element.h"

/* Arbitrarily aligned packed accesses must not use wider memory operations
   when strict alignment is requested.  */
/* { dg-final { scan-assembler-not "\\s(?:lh|lhu|lw|ld|sh|sw|sd)\\s" } } */
