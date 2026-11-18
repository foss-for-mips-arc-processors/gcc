/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-reduce-sum.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 2 "vect" } } */
/* { dg-final { scan-assembler-times {\mpredsum\.dbs\M[^\n]*,zero} 1 } } */
/* { dg-final { scan-assembler-times {\mpredsum\.dhs\M[^\n]*,zero} 1 } } */
