/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-dot16.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 3 "vect" } } */
/* { dg-final { scan-assembler {pm2adda\.h} } } */
/* { dg-final { scan-assembler {pm2addau\.h} } } */
/* { dg-final { scan-assembler {pm2addasu\.h} } } */
