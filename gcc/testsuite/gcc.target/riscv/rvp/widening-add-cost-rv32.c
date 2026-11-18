/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "widening-add-cost.h"

/* { dg-final { scan-assembler-times {\twaddau\t} 2 } } */
/* { dg-final { scan-assembler-times {\twadda\t} 2 } } */
/* { dg-final { scan-assembler-times {\twaddu\t} 1 } } */
/* { dg-final { scan-assembler-times {\twadd\t} 1 } } */
