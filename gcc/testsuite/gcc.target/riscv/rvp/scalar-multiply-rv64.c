/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-multiply.h"

/* { dg-final { scan-assembler-times {\mpmulh\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmulhr\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmulhu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmulhru\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmulhsu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmulhrsu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmulq\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmulqr\.w\M} 1 } } */
