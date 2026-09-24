/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -mstrict-align -O2" } */

#include <riscv_packed_simd.h>
#include "memory-element.h"

/* Arbitrarily aligned packed accesses must not use wider memory operations
   when strict alignment is requested.  */
/* { dg-final { scan-assembler-not "\\s(?:lh|lhu|lw|ld|sh|sw|sd)\\s" } } */
