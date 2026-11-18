/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-pack-trunc.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 2 "vect" } } */
/* { dg-final { scan-assembler-times {\tunzip8p\t} 1 } } */
/* { dg-final { scan-assembler-times {\tunzip16p\t} 1 } } */
/* { dg-final { scan-assembler-not {\tpack\t} } } */
