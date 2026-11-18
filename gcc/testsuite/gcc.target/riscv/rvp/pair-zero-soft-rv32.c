/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32ip -mabi=ilp32 -mlittle-endian -dp" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

#include "pair-zero.h"

/* { dg-final { scan-assembler-times {\taddd\t[^,]+,x0,x0} 2 } } */
/* { dg-final { scan-assembler-times {\taddd\t[^,]+,x0,x0[^\n]*l=4\]} 2 } } */
/* { dg-final { scan-assembler-not {\taddd\t[^\n]*l=8\]} } } */
