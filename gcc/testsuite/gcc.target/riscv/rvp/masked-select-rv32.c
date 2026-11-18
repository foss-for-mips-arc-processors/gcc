/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "masked-select.h"

/* Four forms, two single-register modes and three register-pair modes.  */
/* { dg-final { scan-assembler-times {\mmvmn?\M} 32 } } */
/* { dg-final { scan-assembler-not {\m(and|or|xor|not|mv)\M} } } */
