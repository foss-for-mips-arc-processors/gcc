/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32d -mlittle-endian" } */

#include "round-mulhi.h"

/* { dg-final { scan-assembler-not {\t[p]?mulhr} } } */
