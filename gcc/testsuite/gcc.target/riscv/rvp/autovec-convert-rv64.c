/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-convert.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 6 "vect" } } */
/* { dg-final { scan-assembler {zip8p} } } */
/* { dg-final { scan-assembler {zip16p} } } */
/* { dg-final { scan-assembler {psext\.h\.b} } } */
/* { dg-final { scan-assembler {psext\.w\.h} } } */
/* { dg-final { scan-assembler {unzip8p} } } */
/* { dg-final { scan-assembler-not {pncvt} } } */
