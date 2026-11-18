/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-pack-clip.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 2 "vect" } } */
/* { dg-final { scan-assembler-times {\mpnclipup\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpnclipup\.h\M} 1 } } */
/* { dg-final { scan-assembler-not {\m(pminu|pusati)\.} } } */
/* { dg-final { scan-assembler-not {\t(pack|unzip8p|unzip16p)\t} } } */
