/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fvect-cost-model=unlimited" } */

#include "autovec-reduce-narrow.h"

/* { dg-final { scan-assembler-times {\mpredsum\.bs\M[^\n]*,zero} 1 } } */
/* { dg-final { scan-assembler-times {\mpredsum\.hs\M[^\n]*,zero} 1 } } */
