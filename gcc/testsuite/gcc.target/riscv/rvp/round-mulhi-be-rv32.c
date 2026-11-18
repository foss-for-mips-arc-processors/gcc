/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mbig-endian" } */

#include "round-mulhi.h"

/* { dg-final { scan-assembler-not {\t[p]?mulhr} } } */
