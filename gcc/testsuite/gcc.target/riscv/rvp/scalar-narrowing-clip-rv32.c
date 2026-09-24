/* { dg-do compile { target riscv32*-*-* } } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include <riscv_packed_simd.h>
#include "scalar-narrowing-clip.h"

/* { dg-final { scan-assembler-times {\mnclipiu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnclipu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnclipriu\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnclipru\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnsrari\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnsrar\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnclipi\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnclip\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnclipri\M} 2 } } */
/* { dg-final { scan-assembler-times {\mnclipr\M} 2 } } */
