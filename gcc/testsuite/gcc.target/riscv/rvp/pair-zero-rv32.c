/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian -dp" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

#include "pair-zero.h"

/* Only complete even pairs use ADDD for zero initialization.  A partial
   overwrite keeps a word clear, which can use the compressed encoding.  */
/* { dg-final { scan-assembler-times {\taddd\t[^,]+,x0,x0} 2 } } */
/* { dg-final { scan-assembler-times {\taddd\t[^,]+,x0,x0[^\n]*l=4\]} 2 } } */
/* { dg-final { scan-assembler-not {\taddd\t[^\n]*l=8\]} } } */
