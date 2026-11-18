/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-pack-clip.h"

/* RV32 has no two-source narrowing clip.  */
/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 2 "vect" } } */
/* { dg-final { scan-assembler-times {\mpnclipiu\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpnclipiu\.h\M} 2 } } */
/* { dg-final { scan-assembler-not {\m(pminu|pusati)\.} } } */
