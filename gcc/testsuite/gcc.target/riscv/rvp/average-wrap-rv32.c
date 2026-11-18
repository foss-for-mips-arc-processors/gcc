/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "average-wrap.h"

/* { dg-final { scan-assembler-not {\mpa(add|sub)u?\.} } } */
