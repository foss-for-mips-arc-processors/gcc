/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mbig-endian" } */

#include "pair-zero.h"

/* { dg-final { scan-assembler-not {\taddd\t[^,]+,x0,x0} } } */
