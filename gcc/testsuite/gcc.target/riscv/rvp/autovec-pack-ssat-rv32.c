/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details -fdump-tree-slp1-details" } */

#include "../../../gcc.dg/vect/vect-pack-ssat.h"

/* { dg-final { scan-tree-dump "vect_recog_sat_trunc_clamp_pattern" "vect" } } */
/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 4 "vect" } } */
/* { dg-final { scan-assembler {\mpnclipi\.b\M} } } */
/* { dg-final { scan-assembler {\mpnclipi\.h\M} } } */
/* { dg-final { scan-assembler-not {\mpnclipp\.[bh]\M} } } */
