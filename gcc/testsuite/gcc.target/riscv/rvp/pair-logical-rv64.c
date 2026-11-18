/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "pair-logical.h"

/* { dg-final { scan-assembler-times {\mand\M} 3 } } */
/* { dg-final { scan-assembler-times {\mor\M} 3 } } */
/* { dg-final { scan-assembler-times {\mxor\M} 3 } } */
/* { dg-final { scan-assembler-not {\mmv\M} } } */
