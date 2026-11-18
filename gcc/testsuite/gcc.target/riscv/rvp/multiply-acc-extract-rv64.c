/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

/* RV32 scalar halfword multiply and accumulate instructions are not valid
   replacements for RV64 packed operations.  */
#include "multiply-acc-extract.h"

/* { dg-final { scan-assembler-not "\\t(mul|macc)\\.h(00|01|11)\\t" } } */
