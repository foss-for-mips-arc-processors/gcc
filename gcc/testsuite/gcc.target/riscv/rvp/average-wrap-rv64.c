/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "average-wrap.h"

/* { dg-final { scan-assembler-not {\mpa(add|sub)u?\.} } } */
