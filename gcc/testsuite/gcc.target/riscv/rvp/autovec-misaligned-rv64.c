/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -mstrict-align" } */

#include "autovec-misaligned.h"

/* { dg-final { scan-assembler {\mlbu\M} } } */
/* { dg-final { scan-assembler {\msb\M} } } */
