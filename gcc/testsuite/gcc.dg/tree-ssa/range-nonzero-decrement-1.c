/* { dg-do compile } */
/* { dg-require-effective-target int32 } */
/* { dg-options "-O2 -fdump-tree-optimized" } */

#include "range-nonzero-decrement.h"

/* Nonzero guards let the comparisons use the original input.  */
/* { dg-final { scan-tree-dump-not { \+ 4294967295;} "optimized" } } */
/* { dg-final { scan-tree-dump-not { \+ 18446744073709551615;} "optimized" } } */
