/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-dot.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 4 "vect" } } */
/* { dg-final { scan-assembler {pm4adda\.b} } } */
/* { dg-final { scan-assembler {pm4addau\.b} } } */
/* { dg-final { scan-assembler {pm4addasu\.b} } } */
