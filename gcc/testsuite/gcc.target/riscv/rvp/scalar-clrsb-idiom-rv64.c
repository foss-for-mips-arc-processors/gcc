/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -fdump-tree-optimized" } */

#include "../../../gcc.dg/clrsb-idiom.h"

/* The two shared-outer functions must retain their original calculation.  */
/* { dg-final { scan-tree-dump-times {\.CLRSB \(} 6 "optimized" } } */
/* { dg-final { scan-assembler-times {\tclsw\t} 3 } } */
/* { dg-final { scan-assembler-times {\tcls\t} 3 } } */
