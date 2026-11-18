/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "autovec-dot64-negative.h"

/* { dg-final { scan-assembler-not {\tpm2wadda(u|su)?\.h\t} } } */
