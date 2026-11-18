/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-tree-vect-details" } */

#include "alignment-peel-cost.h"

/* Eight-byte vectors require only four-byte alignment on RV32.  */
/* { dg-final { scan-tree-dump "prologue peel iters estimated to 2 using alignment" "vect" } } */
/* { dg-final { scan-tree-dump "prologue peel iters estimated to 1 using alignment" "vect" } } */
/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 2 "vect" } } */

/* The byte-loop guard compares n - 1 with 9, allowing one full vector
   after at most three alignment peels.  The old seven-peel bound used 13.  */
/* { dg-final { scan-assembler {\tli\t[a-z0-9]+,9\n} } } */
/* { dg-final { scan-assembler-not {\tli\t[a-z0-9]+,13\n} } } */
