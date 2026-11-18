/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "mulhi-acc-loop.h"

/* The rounding bias is loop-invariant.  Its cost must not prevent fusion
   of the scalar reductions, maps or volatile-input loop.  Shared products
   and different biases and shift amounts must retain their semantics.  */

/* { dg-final { scan-assembler-times {\tmhracc\t} 3 } } */
/* { dg-final { scan-assembler-times {\tmhraccu\t} 2 } } */
/* { dg-final { scan-assembler-times {\tmhraccsu\t} 4 } } */
