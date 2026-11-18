/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fdump-tree-vect-details" } */

#include "versioning-count.h"

/* Compare the nonwrapping count directly in both alignment-versioning
   guards, retaining the packed arithmetic in their vector paths.  */
/* { dg-final { scan-tree-dump-times "versioning compares nonwrapping iteration count" 2 "vect" } } */
/* { dg-final { scan-assembler {\mpmulsu\.h\.b00\M} } } */
/* { dg-final { scan-assembler {\mpmaccsu\.w\.h00\M} } } */
/* { dg-final { scan-assembler-not {addi[w]?[ \t]+[a-z0-9]+,[ \t]*a3,[ \t]*-1\M} } } */
