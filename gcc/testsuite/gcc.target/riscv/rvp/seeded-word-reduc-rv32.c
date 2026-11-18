/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */

#include "seeded-word-reduc.h"

/* RV32 already has scalar registers for the two words.  */
/* { dg-final { scan-assembler-not {\tpredsum\.ws\t} } } */
