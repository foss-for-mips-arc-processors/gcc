/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "packed-logic-imm-negative.h"

/* Only the six positive controls use logical immediates.  */
/* { dg-final { scan-assembler-times {\mandi\M} 2 } } */
/* { dg-final { scan-assembler-times {\mori\M} 2 } } */
/* { dg-final { scan-assembler-times {\mxori\M} 2 } } */
