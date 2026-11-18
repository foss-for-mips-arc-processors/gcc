/* { dg-do compile } */
/* { dg-options "-O3 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fvect-cost-model=unlimited --param=vect-epilogues-nomask=0 -fdump-tree-vect-details" } */

#define TEST_FUNCTIONS_ONLY
#include "../../../gcc.dg/vect/vect-epilogue-offset.c"

/* All five functions can reuse both input pointers and the output pointer.  */
/* { dg-final { scan-tree-dump-times {reusing vector data pointer in scalar epilogue} 15 "vect" } } */
/* { dg-final { scan-assembler {\tmulq\s} } } */
