/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fdump-tree-optimized" } */

#include "autovec-sat-sub-trunc.h"

/* { dg-final { scan-tree-dump {\.SAT_SUB } "optimized" } } */
/* { dg-final { scan-assembler {\mpssubu\.h\M} } } */
