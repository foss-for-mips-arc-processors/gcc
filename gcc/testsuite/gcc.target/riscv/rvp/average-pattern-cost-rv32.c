/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-tree-vect-details" } */

#include "average-pattern-cost.h"

/* Cost the vector average, retaining the original scalar dependencies.  */
/* { dg-final { scan-tree-dump "bitwise_average pattern recognized" "vect" } } */
/* { dg-final { scan-tree-dump "Vector inside of loop cost: 7" "vect" } } */
/* { dg-final { scan-tree-dump "Scalar iteration cost: 7" "vect" } } */
/* { dg-final { scan-tree-dump "Vector inside of loop cost: 5" "vect" } } */
/* { dg-final { scan-tree-dump "Scalar iteration cost: 5" "vect" } } */
