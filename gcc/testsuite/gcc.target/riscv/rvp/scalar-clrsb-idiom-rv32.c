/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -fdump-tree-optimized" } */

#include "../../../gcc.dg/clrsb-idiom.h"

/* Three owned SI forms fold; the shared unsigned outer result does not.  */
/* { dg-final { scan-tree-dump-times {\.CLRSB \(} 3 "optimized" } } */
/* { dg-final { scan-assembler-times {\tcls\t} 3 } } */
/* { dg-final { scan-assembler-not {\tclsw\t} } } */
