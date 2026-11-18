/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian -fdump-tree-vect-details" } */

#include "q31-unroll.h"

/* RV64 has native packed Q31 arithmetic and retains its existing model.  */
/* { dg-final { scan-tree-dump-not {RVP Q-format loop has [0-9]+ pointer updates} "vect" } } */
/* { dg-final { scan-tree-dump-not {Re-trying analysis for unrolling with unroll factor 2} "vect" } } */
/* { dg-final { scan-assembler {\tpmulqr\.w\t} } } */
