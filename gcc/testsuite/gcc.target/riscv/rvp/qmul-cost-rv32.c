/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-vect-details" } */

#include "qmul-cost.h"

/* Scalar fusion and multiword loop-control costs are accounted together.  */
/* { dg-final { scan-tree-dump {>> 14[^\n]*times scalar_stmt costs 0} "vect" } } */
/* { dg-final { scan-tree-dump {>> 30[^\n]*times scalar_stmt costs 0} "vect" } } */
/* { dg-final { scan-tree-dump {RVP Q-format loop branch costs} "vect" } } */
/* { dg-final { scan-tree-dump {RVP Q-format loop has 3 pointer updates} "vect" } } */
/* { dg-final { scan-tree-dump-times {LOOP VECTORIZED} 6 "vect" } } */
