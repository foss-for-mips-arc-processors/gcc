/* { dg-do compile } */
/* { dg-skip-if "LTO" { *-*-* } { "-flto" "-flto=*" } } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fno-vect-cost-model -fdump-tree-optimized" } */

#include "cadd-cross.h"

/* { dg-final { scan-tree-dump-times {\.COMPLEX_ADD_ROT90} 3 "optimized" } } */
/* { dg-final { scan-tree-dump-times {\.COMPLEX_ADD_ROT270} 3 "optimized" } } */
/* { dg-final { scan-assembler-times {\tpas\.hx\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpsa\.hx\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpas\.dhx\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpsa\.dhx\t} 2 } } */
/* { dg-final { scan-assembler-not {\t(pas|psa)\.wx\t} } } */
