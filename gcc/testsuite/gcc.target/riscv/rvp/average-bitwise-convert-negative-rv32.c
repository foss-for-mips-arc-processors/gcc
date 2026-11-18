/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-tree-optimized" } */

#include "average-bitwise-convert-negative.h"

/* { dg-final { scan-tree-dump-not {\.AVG_FLOOR} "optimized" } } */
/* { dg-final { scan-assembler-not {\mpaaddu?\.} } } */
