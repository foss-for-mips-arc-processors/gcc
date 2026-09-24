/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-data.h"

/* { dg-final { scan-assembler-times {\mabsw\M} 1 } } */
/* { dg-final { scan-assembler-times {\mabs\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmseq\.w\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpmslt\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmsgt\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmsltu\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmsgtu\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnot\M} 6 } } */
/* { dg-final { scan-assembler-times {\m(merge|mvmn?)\M} 4 } } */
/* { dg-final { scan-assembler-times {\msext\.w\M} 14 } } */
