/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "autovec-dot64.h"

/* { dg-final { scan-assembler-times {\tpm4adda\.h\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpm4addau\.h\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpm4addasu\.h\t} 2 } } */
