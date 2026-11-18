/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2 -fwrapv" } */

#include "rounding-wrap.h"

/* The bias must wrap before shifting; SRARI rounds without that wrap.  */
/* { dg-final { scan-assembler-not {\msrari\M} } } */
