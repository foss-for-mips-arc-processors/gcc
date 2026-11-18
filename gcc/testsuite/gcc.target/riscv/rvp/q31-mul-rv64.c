/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian -fdump-tree-vect-details" } */

#include "q31-mul.h"

/* { dg-final { scan-tree-dump {\.SAT_MULHS .*vector_stmt costs 1 in body} "vect" } } */
/* { dg-final { scan-tree-dump {\.SAT_MULHRS .*vector_stmt costs 1 in body} "vect" } } */
/* { dg-final { scan-assembler-times {\tpmulq\.w\t} 9 } } */
/* { dg-final { scan-assembler-times {\tpmulqr\.w\t} 12 } } */
