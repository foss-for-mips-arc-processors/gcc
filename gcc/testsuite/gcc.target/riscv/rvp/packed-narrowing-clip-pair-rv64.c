/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "packed-narrowing-clip-pair.h"

/* The 32-bit return forms need PACK to place both half-width arguments in
   the low source register before PNCLIPP/PNCLIPUP.  */
/* { dg-final { scan-assembler-times {\mpack\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpnclipp\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpnclipup\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpnclipp\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpnclipup\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpnclipp\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpnclipup\.w\M} 1 } } */
