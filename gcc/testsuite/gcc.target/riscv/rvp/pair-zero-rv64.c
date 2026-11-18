/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "pair-zero.h"

/* { dg-final { scan-assembler-not {\taddd\t} } } */
