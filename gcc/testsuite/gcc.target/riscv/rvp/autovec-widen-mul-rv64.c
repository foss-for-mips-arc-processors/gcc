/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "autovec-widen-mul.h"

/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 5 "vect" } } */
/* { dg-final { scan-assembler {pmul\.h\.b01} } } */
/* { dg-final { scan-assembler {pmulu\.h\.b01} } } */
/* { dg-final { scan-assembler {pmul\.w\.h01} } } */
/* { dg-final { scan-assembler {pmulu\.w\.h01} } } */
/* { dg-final { scan-assembler {zip8hp} } } */
/* { dg-final { scan-assembler {zip16hp} } } */
