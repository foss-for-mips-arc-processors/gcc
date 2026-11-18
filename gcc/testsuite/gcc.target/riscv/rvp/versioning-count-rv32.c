/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3 -fdump-tree-vect-details" } */

#include "versioning-count.h"

/* { dg-final { scan-tree-dump "versioning compares nonwrapping iteration count" "vect" } } */
/* { dg-final { scan-assembler {\mpwmulsu\.b\M} } } */
