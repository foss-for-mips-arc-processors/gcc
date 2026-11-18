/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gc -mabi=lp64d -mlittle-endian" } */

#include "round-mulhi.h"

/* { dg-final { scan-assembler-not {\t[p]?mulhr} } } */
