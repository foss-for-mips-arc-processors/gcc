/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "autovec-dot64.h"

/* Keep the loop accumulator in one register.  The entry pointer copy is
   the only move in each function.  */
/* { dg-final { scan-assembler-times {\tmv\t} 4 } } */
