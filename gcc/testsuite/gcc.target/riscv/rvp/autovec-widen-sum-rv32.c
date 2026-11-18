/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-widen-sum.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 4 "vect" } } */
/* { dg-final { scan-assembler-times {\mpm4adda\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpm4addau\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpm2adda\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpm2addau\.h\M} 2 } } */
