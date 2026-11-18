/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "inverted-logical.h"

/* Two forms and five single-register modes.  */
/* { dg-final { scan-assembler-times {\mandn\M} 10 } } */
/* { dg-final { scan-assembler-times {\morn\M} 10 } } */
/* { dg-final { scan-assembler-times {\mxnor\M} 10 } } */
/* { dg-final { scan-assembler-not {\m(and|or|xor|not|mv)\M} } } */
