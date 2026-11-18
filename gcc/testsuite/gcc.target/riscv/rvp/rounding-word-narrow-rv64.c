/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d" } */

#include "rounding-word-narrow.h"

/* { dg-final { scan-assembler-times {\msrari\M} 31 } } */
