/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2 -fwrapv" } */

#include "rounding-wrap.h"

/* This also checks word-mode wrapping before extension to XLEN.  */
/* { dg-final { scan-assembler-not {\msrari\M} } } */
