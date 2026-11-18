/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-vect-details" } */

#include "autovec-dot64-cost.h"

/* Keep the default very-cheap model: an artificial horizontal-reduction
   cost prevents these loops from vectorizing.  */
/* { dg-final { scan-assembler-times {\tpm2wadda\.h\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpm2waddau\.h\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpm2waddasu\.h\t} 4 } } */
/* { dg-final { scan-tree-dump-times {1 times vector_stmt costs 0 in epilogue} 4 "vect" } } */
/* { dg-final { scan-tree-dump-times {1 times vec_to_scalar costs 0 in epilogue} 4 "vect" } } */
/* { dg-final { scan-tree-dump-times {1 times vector_stmt costs 2 in body} 4 "vect" } } */
