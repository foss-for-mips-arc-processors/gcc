/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "predsum-acc.h"

/* { dg-final { scan-assembler-times {\mpredsum\.bs\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpredsum\.hs\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpredsum\.bs\M[^\n]*,zero} 1 } } */
/* { dg-final { scan-assembler-times {\mpredsum\.hs\M[^\n]*,zero} 1 } } */
