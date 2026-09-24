/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-narrowing-clip.h"

/* { dg-final { scan-assembler-times {\msrli\M} 2 } } */
/* { dg-final { scan-assembler-times {\msrl\M} 2 } } */
/* { dg-final { scan-assembler-times {\msrai\M} 2 } } */
/* { dg-final { scan-assembler-times {\msra\M} 2 } } */
/* { dg-final { scan-assembler-times {\msrari\M} 2 } } */
/* { dg-final { scan-assembler-times {\mshlr\M} 4 } } */
/* { dg-final { scan-assembler-times {\mshar\M} 6 } } */
/* { dg-final { scan-assembler-times {\mpnclipup\.w\M} 8 } } */
/* { dg-final { scan-assembler-times {\mpnclipp\.w\M} 8 } } */
