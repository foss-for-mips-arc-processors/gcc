/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian -fdump-tree-vect-details" } */

#include "autovec-sad-codegen.h"

/* { dg-final { scan-assembler-times {\tpabdsumau\.b\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpabdsumu\.b\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpadd\.w\t} 1 } } */
/* { dg-final { scan-assembler-not {\tpli\.b\t} } } */
/* { dg-final { scan-tree-dump {SAD_EXPR} "vect" } } */
/* { dg-final { scan-tree-dump {SAD_EXPR[^\n]*1 times vector_stmt costs 2 in body} "vect" } } */
/* { dg-final { scan-tree-dump {SAD_EXPR[^\n]*1 times vector_stmt costs 1 in body} "vect" } } */
