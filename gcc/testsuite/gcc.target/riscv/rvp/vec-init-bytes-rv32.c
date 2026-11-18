/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fno-tree-vectorize" } */

#include "vec-init-bytes.h"

/* { dg-final { scan-assembler-times {\tppaire\.b\t} 6 } } */
/* { dg-final { scan-assembler-times {\tppaire\.h\t} 3 } } */
/* { dg-final { scan-assembler-not {\t(?:andi|slli|srli|or)\t} } } */
