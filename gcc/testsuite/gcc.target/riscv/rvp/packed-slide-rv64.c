/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "packed-slide.h"

/* { dg-final { scan-assembler-times {\mslx\M} 16 } } */
/* { dg-final { scan-assembler-times {\msrx\M} 16 } } */
/* { dg-final { scan-assembler-times {\mppaire\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mppairoe\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpack\M} 2 } } */
/* { dg-final { scan-assembler-times {\mppairoe\.w\M} 2 } } */
