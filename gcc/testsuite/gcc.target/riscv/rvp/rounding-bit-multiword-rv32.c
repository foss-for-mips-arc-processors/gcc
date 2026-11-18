/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -fdump-tree-optimized" } */

#include <stdint.h>

/* A multiword add followed by a shift costs more than adding the extracted
   rounding bit.  Keep the original form for RV32 64-bit scalars.  */
int64_t
signed_round (int64_t x)
{
  return (x >> 4) + ((x >> 3) & 1);
}

uint64_t
unsigned_round (uint64_t x)
{
  return (x >> 4) + ((x >> 3) & 1);
}

/* { dg-final { scan-tree-dump-not " \\+ 1;" "optimized" } } */
