/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32d -mlittle-endian" } */

#include "pair-zero.h"

/* { dg-final { scan-assembler-not {\taddd\t} } } */
