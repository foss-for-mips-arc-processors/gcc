/* { dg-do compile } */
/* { dg-options "-O2 -fno-tree-vectorize -march=rv64gcp -mabi=lp64d -mbig-endian" } */

#include "rounding-word.h"
#include "rounding-word-narrow.h"

/* { dg-final { scan-assembler-times {\msrari\M} 41 } } */
