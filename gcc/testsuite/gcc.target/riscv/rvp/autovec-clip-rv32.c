/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-clip.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 4 "vect" } } */
/* { dg-final { scan-assembler {\mpnclipiu\.b\M} } } */
/* { dg-final { scan-assembler {\mpnclipiu\.h\M} } } */
/* { dg-final { scan-assembler-not {\mpminu\.} } } */
/* { dg-final { scan-assembler-not {\mpusati\.} } } */
