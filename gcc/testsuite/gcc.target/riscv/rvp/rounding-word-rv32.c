/* { dg-do compile } */
/* { dg-options "-O2 -fno-tree-vectorize -march=rv32gcp -mabi=ilp32d" } */

#define TEST_POSITIVE_ONLY
#include "rounding-word.h"

/* { dg-final { scan-assembler-times {\msrari\M} 10 } } */
