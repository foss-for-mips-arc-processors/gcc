/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details -fdump-tree-slp1-details" } */

#include "autovec-pack-ssat-negative.c"
#include "autovec-pack-ssat-promoted-negative.c"

/* { dg-final { scan-tree-dump-not "vect_recog_(promoted_)?sat_trunc_clamp" "vect" } } */
/* { dg-final { scan-tree-dump-not "vect_recog_(promoted_)?sat_trunc_clamp" "slp1" } } */
