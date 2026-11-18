/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "masked-select.h"

/* All five vector modes fit in one register.  */
/* { dg-final { scan-assembler-times {\mmvmn?\M} 20 } } */
/* { dg-final { scan-assembler-not {\m(and|or|xor|not|mv)\M} } } */
