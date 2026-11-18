/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details" } */

#include "../../../gcc.dg/vect/vect-pack-ssat-promoted.h"

/* { dg-final { scan-tree-dump "vect_recog_promoted_sat_trunc_clamp" "vect" } } */
/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 4 "vect" } } */
/* { dg-final { scan-assembler-times {\mpnclipp\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpnclipp\.h\M} 2 } } */
