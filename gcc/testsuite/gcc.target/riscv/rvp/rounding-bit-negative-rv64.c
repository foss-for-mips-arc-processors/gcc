/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "rounding-bit-negative.h"

/* { dg-final { scan-assembler-not {\m(p?srari|psshar|sshar|shar)\M} } } */
