/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2 -fwrapv" } */

#include "rounding-seq.h"

/* { dg-final { scan-assembler-times {\msrari\M} 5 } } */
/* { dg-final { scan-assembler-not {\msrai\M} } } */
