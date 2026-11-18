/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-vect-details" } */

#include "q31-unroll.h"

/* { dg-final { scan-tree-dump {RVP Q-format loop has 2 pointer updates} "vect" } } */
/* { dg-final { scan-tree-dump {RVP Q-format loop has 3 pointer updates} "vect" } } */
/* { dg-final { scan-tree-dump {Re-trying analysis for unrolling with unroll factor 2} "vect" } } */
/* { dg-final { scan-tree-dump {2 times vector_stmt costs 4 in body} "vect" } } */
/* { dg-final { scan-tree-dump {LOOP VECTORIZED} "vect" } } */
