/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "bswap32.h"

/* { dg-final { scan-assembler-times {\tppairoe\.b\t} 2 } } */
/* { dg-final { scan-assembler-times {\tppairoe\.h\t} 2 } } */
