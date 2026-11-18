/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d" } */

#define TEST_NEGATIVE_ONLY
#include "rounding-word.h"

/* { dg-final { scan-assembler-not {\msrari\M} } } */
