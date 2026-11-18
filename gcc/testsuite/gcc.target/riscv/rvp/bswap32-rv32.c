/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "bswap32.h"

/* { dg-final { scan-assembler-times {\tppairoe\.db\t} 2 } } */
/* { dg-final { scan-assembler-times {\tppairoe\.dh\t} 2 } } */
