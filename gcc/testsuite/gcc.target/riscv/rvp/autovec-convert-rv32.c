/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-convert.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 6 "vect" } } */
/* { dg-final { scan-assembler {pwadd\.b} } } */
/* { dg-final { scan-assembler {pwadd\.h} } } */
/* { dg-final { scan-assembler {wzip8p} } } */
/* { dg-final { scan-assembler {wzip16p} } } */
/* { dg-final { scan-assembler-not {psext\.d[hw]} } } */
