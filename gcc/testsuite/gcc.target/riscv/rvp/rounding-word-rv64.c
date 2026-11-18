/* { dg-do compile } */
/* { dg-options "-O2 -fno-tree-vectorize -march=rv64gcp -mabi=lp64d" } */

#define TEST_POSITIVE_ONLY
#include "rounding-word.h"

/* { dg-final { scan-assembler-times {\msrari\M} 10 } } */
/* { dg-final { scan-assembler-not {\msraiw\M} } } */
