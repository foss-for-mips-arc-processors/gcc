/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "autovec-dot64.h"

/* { dg-final { scan-assembler-times {\tpm2wadda\.h\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpm2waddau\.h\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpm2waddasu\.h\t} 4 } } */
