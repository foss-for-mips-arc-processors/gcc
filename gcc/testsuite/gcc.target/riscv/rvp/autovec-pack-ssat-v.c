/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv64gcpv -mabi=lp64d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details -fdump-tree-slp1-details" } */

#include "../../../gcc.dg/vect/vect-pack-ssat.h"

/* { dg-final { scan-tree-dump-not "vect_recog_sat_trunc_clamp_pattern" "vect" } } */
/* { dg-final { scan-tree-dump-not "vect_recog_sat_trunc_clamp_pattern" "slp1" } } */
/* { dg-final { scan-assembler-not {\mpnclipp\.[bh]\M} } } */
