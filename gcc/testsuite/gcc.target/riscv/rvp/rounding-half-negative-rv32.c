/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2 -fdump-tree-optimized" } */

#include "rounding-half-negative.h"

/* { dg-final { scan-tree-dump-not {\.AVG_(FLOOR|CEIL)} "optimized" } } */
