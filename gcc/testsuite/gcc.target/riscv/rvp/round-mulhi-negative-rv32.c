/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "round-mulhi-negative.h"

/* { dg-final { scan-assembler-not {\t[p]?mulhr} } } */
