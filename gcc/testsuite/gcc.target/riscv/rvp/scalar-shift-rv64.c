/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-shift.h"

/* { dg-final { scan-assembler-times {\mpssha\.ws\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsshar\.ws\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsshl\.ws\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsshlr\.ws\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsslai\.w\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpsrai\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsrari\.w\M} 2 } } */
/* { dg-final { scan-assembler-times {\msha\M} 2 } } */
/* { dg-final { scan-assembler-times {\mshar\M} 2 } } */
/* { dg-final { scan-assembler-times {\mshl\M} 1 } } */
/* { dg-final { scan-assembler-times {\mshlr\M} 1 } } */
/* { dg-final { scan-assembler-times {\mslli\M} 4 } } */
/* { dg-final { scan-assembler-times {\msrai\M} 2 } } */
/* { dg-final { scan-assembler-times {\msrari\M} 2 } } */
