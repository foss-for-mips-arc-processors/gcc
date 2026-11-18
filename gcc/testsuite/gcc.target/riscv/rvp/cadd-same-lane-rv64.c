/* { dg-do compile } */
/* { dg-skip-if "LTO" { *-*-* } { "-flto" "-flto=*" } } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian -fno-vect-cost-model -fdump-tree-optimized" } */

#define CADD_SAME_LANE
#include "cadd-cross.h"

/* { dg-final { scan-tree-dump-not {\.COMPLEX_ADD_ROT(90|270)} "optimized" } } */
/* { dg-final { scan-assembler-not {\t(pas|psa)\.} } } */
