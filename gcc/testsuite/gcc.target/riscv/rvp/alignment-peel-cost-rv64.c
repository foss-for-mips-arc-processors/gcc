/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fdump-tree-vect-details" } */

#include "alignment-peel-cost.h"

/* Eight-byte alignment still requires four byte or two halfword peels.  */
/* { dg-final { scan-tree-dump "prologue peel iters estimated to 4 using alignment" "vect" } } */
/* { dg-final { scan-tree-dump "prologue peel iters estimated to 2 using alignment" "vect" } } */
/* { dg-final { scan-tree-dump-times "LOOP VECTORIZED" 2 "vect" } } */
