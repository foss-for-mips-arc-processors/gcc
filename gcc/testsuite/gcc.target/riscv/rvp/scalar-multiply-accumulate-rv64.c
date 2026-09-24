/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-multiply-accumulate.h"

/* { dg-final { scan-assembler-times {\mpmhacc\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmhracc\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmhaccu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmhraccu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmhaccsu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmhraccsu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmqacc\.w00\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmqracc\.w00\M} 1 } } */
