/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2 -fdump-tree-optimized" } */

#include "rounding-half-negative.h"

/* { dg-final { scan-tree-dump-not {\.AVG_(FLOOR|CEIL)} "optimized" } } */
