/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-vect-details" } */

#include "autovec-sad-codegen.h"

/* { dg-final { scan-assembler-times {\tpabdsumau\.b\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpabdsumu\.b\t} 2 } } */
/* { dg-final { scan-assembler-times {\twaddau\t} 1 } } */
/* { dg-final { scan-tree-dump {SAD_EXPR} "vect" } } */
/* { dg-final { scan-tree-dump {SAD_EXPR[^\n]*1 times vector_stmt costs 2 in body} "vect" } } */
/* { dg-final { scan-tree-dump {SAD_EXPR[^\n]*1 times vector_stmt costs 3 in body} "vect" } } */
