/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "inverted-logical.h"

/* Two forms, two single-register modes and three register-pair modes.  */
/* { dg-final { scan-assembler-times {\mandn\M} 16 } } */
/* { dg-final { scan-assembler-times {\morn\M} 16 } } */
/* { dg-final { scan-assembler-times {\mxnor\M} 16 } } */
/* { dg-final { scan-assembler-not {\m(and|or|xor|not|mv)\M} } } */
