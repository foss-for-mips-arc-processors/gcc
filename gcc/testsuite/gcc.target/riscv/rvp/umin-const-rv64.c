/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "umin-const.h"

/* { dg-final { scan-assembler-times {\mpminu\.h\M} 2 } } */
/* { dg-final { scan-assembler {\mpminu\.w\M} } } */
/* { dg-final { scan-assembler-not {\mpusati\.} } } */
