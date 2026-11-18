/* { dg-do compile } */
/* { dg-skip-if "LTO" { *-*-* } { "-flto" "-flto=*" } } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian -fno-vect-cost-model -fdump-tree-optimized" } */

#include "cadd-cross.h"

/* { dg-final { scan-tree-dump-times {\.COMPLEX_ADD_ROT90} 5 "optimized" } } */
/* { dg-final { scan-tree-dump-times {\.COMPLEX_ADD_ROT270} 5 "optimized" } } */
/* { dg-final { scan-assembler-times {\tpas\.hx\t} 3 } } */
/* { dg-final { scan-assembler-times {\tpsa\.hx\t} 3 } } */
/* { dg-final { scan-assembler-times {\tpas\.wx\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpsa\.wx\t} 2 } } */
