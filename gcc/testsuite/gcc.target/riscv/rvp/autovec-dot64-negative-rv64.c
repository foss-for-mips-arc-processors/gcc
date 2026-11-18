/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "autovec-dot64-negative.h"

/* { dg-final { scan-assembler-not {\tpm4adda(u|su)?\.h\t} } } */
