/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian -fdump-tree-vect-details" } */

#include "autovec-dot64-cost.h"

/* { dg-final { scan-assembler-times {\tpm4adda\.h\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpm4addau\.h\t} 1 } } */
/* { dg-final { scan-assembler-times {\tpm4addasu\.h\t} 2 } } */
/* { dg-final { scan-tree-dump-times {1 times vector_stmt costs 0 in epilogue} 4 "vect" } } */
/* { dg-final { scan-tree-dump-times {1 times vec_to_scalar costs 0 in epilogue} 4 "vect" } } */
/* { dg-final { scan-tree-dump-times {1 times vector_stmt costs 1 in body} 4 "vect" } } */
