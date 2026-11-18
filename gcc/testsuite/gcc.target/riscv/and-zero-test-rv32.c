/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32d" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

#include "and-zero-test.h"

/* { dg-final { scan-assembler-times {\tseqz\t} 1 } } */
/* { dg-final { scan-assembler-times {\tor\t} 2 } } */
