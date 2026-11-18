/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "round-mulhi-negative.h"

/* { dg-final { scan-assembler-not {\t[p]?mulhr} } } */
