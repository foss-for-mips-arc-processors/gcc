/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "pair-logical.h"

/* Exact source/destination overlap needs no register-pair copies.  */
/* { dg-final { scan-assembler-times {\mand\M} 6 } } */
/* { dg-final { scan-assembler-times {\mor\M} 6 } } */
/* { dg-final { scan-assembler-times {\mxor\M} 6 } } */
/* { dg-final { scan-assembler-not {\mmv\M} } } */
