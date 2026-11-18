/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-tree-vect-details" } */

#include "average-pattern-negative.h"

/* { dg-final { scan-tree-dump-not "bitwise_average pattern recognized" "vect" } } */
