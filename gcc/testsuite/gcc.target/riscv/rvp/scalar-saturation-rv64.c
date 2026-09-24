/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-saturation.h"

/* { dg-final { scan-assembler-times {\mpsati\.w\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpusati\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\msati\M} 2 } } */
/* { dg-final { scan-assembler-times {\musati\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsati\.h\M} 2 } } */
