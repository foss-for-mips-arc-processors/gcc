/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-widen-mul.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 5 "vect" } } */
/* { dg-final { scan-assembler {pwmul\.b} } } */
/* { dg-final { scan-assembler {pwmulu\.b} } } */
/* { dg-final { scan-assembler {pwmul\.h} } } */
/* { dg-final { scan-assembler {pwmulu\.h} } } */
