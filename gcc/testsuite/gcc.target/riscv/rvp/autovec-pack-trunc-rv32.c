/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-pack-trunc.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 2 "vect" } } */
/* { dg-final { scan-assembler-times {\tpncvt\.b\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpncvt\.h\t} 2 } } */
