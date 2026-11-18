/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "packed-logic-imm-negative.h"

/* Only the six positive controls use logical immediates.  */
/* { dg-final { scan-assembler-times {\mandi\M} 3 } } */
/* { dg-final { scan-assembler-times {\mori\M} 3 } } */
/* { dg-final { scan-assembler-times {\mxori\M} 3 } } */
