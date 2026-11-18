/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fdump-tree-vect-details" } */

#include "q31-mul.h"

/* { dg-final { scan-tree-dump {\.SAT_MULHS .*vector_stmt costs 2 in body} "vect" } } */
/* { dg-final { scan-tree-dump {\.SAT_MULHRS .*vector_stmt costs 2 in body} "vect" } } */
/* { dg-final { scan-assembler-times {\tmulq\t} 14 } } */
/* { dg-final { scan-assembler-times {\tmulqr\t} 20 } } */
/* { dg-final { scan-assembler-not {\tpmulqr?\.w\t} } } */
