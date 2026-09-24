/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-arithmetic.h"

/* { dg-final { scan-assembler-times {\mpsadd\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsaddu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpssub\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpssubu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasub\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasubu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpssh1sadd\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\msext\.w\M} 9 } } */
