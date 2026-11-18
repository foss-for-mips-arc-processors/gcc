/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mbig-endian" } */

#include "round-mulhi.h"

/* { dg-final { scan-assembler-not {\t[p]?mulhr} } } */
