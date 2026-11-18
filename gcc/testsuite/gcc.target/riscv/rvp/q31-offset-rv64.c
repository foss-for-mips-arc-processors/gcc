/* { dg-do compile } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian -fvect-cost-model=unlimited --param=vect-epilogues-nomask=0 -fdump-tree-vect-details" } */

#define TEST_FUNCTIONS_ONLY
#include "../../../gcc.dg/vect/vect-epilogue-offset.c"

/* Only the two explicitly aligned functions avoid an alignment prologue.  */
/* { dg-final { scan-tree-dump-times {reusing vector data pointer in scalar epilogue} 6 "vect" } } */
/* { dg-final { scan-assembler {\tpmulq\.w\s} } } */
