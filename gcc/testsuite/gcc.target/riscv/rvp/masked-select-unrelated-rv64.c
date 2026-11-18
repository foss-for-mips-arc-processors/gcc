/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fdump-rtl-combine" } */

#include "masked-select-unrelated.h"

/* The masks are unrelated, so the two ANDs are not a bitwise select.  */
/* { dg-final { scan-rtl-dump-not {\*mvm} "combine" } } */
/* { dg-final { scan-assembler-not {\mmvmn?\M} } } */
