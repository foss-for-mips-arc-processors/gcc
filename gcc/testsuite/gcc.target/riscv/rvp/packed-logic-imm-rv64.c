/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "packed-logic-imm.h"

/* { dg-final { scan-assembler-times {\mandi\M} 2 } } */
/* { dg-final { scan-assembler-times {\mori\M} 2 } } */
/* { dg-final { scan-assembler-times {\mxori\M} 2 } } */
/* { dg-final { scan-assembler-not {\m(li|lui|lw|ld|pli\.[bhw])\M} } } */
