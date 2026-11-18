/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "autovec-dot64-shared.h"

/* { dg-final { scan-assembler-times {\tpm2wadda\.h\t} 2 } } */
