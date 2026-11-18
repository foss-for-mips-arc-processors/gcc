/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "rounding-bit-negative.h"

/* { dg-final { scan-assembler-not {\m(p?srari|psshar|sshar|shar)\M} } } */
