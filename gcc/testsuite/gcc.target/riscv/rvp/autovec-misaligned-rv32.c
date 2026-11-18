/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -mstrict-align" } */

#include "autovec-misaligned.h"

/* { dg-final { scan-assembler {\mlbu\M} } } */
/* { dg-final { scan-assembler {\msb\M} } } */
