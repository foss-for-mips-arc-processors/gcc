/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian -fdump-tree-vect-details" } */

#include "q15-loop.h"

/* { dg-final { scan-tree-dump {\.SAT_MULHS } "vect" } } */
/* { dg-final { scan-tree-dump {\.SAT_MULHRS } "vect" } } */
/* { dg-final { scan-assembler-times {\tpmulq\.h\t} 13 } } */
/* { dg-final { scan-assembler-times {\tpmulqr\.h\t} 8 } } */
