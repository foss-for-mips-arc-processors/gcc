/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-narrow-shift.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 4 "vect" } } */
/* { dg-final { scan-assembler {\mpnsrli\.b\M} } } */
/* { dg-final { scan-assembler {\mpnsrli\.h\M} } } */
/* { dg-final { scan-assembler {\mpnsrai\.b\M} } } */
/* { dg-final { scan-assembler {\mpnsrai\.h\M} } } */
/* { dg-final { scan-assembler-not {\mpsr[al]i\.d[hw]\M} } } */
/* { dg-final { scan-assembler-not {\mpnclip} } } */
