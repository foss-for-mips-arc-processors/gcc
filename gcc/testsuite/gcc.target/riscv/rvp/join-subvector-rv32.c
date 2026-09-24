/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "join-subvector.h"

/* { dg-final { scan-assembler {\mppaire\.h\M} } } */
