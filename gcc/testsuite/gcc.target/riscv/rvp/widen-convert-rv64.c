/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "widen-convert.h"

/* A complete signed extension needs both instructions.  */
/* { dg-final { scan-assembler-times {\mzip8p\M} 2 } } */
/* { dg-final { scan-assembler-times {\mzip16p\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpsext\.h\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpsext\.w\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmul\.w\.h00\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmul\.w\.h11\M} 1 } } */
/* { dg-final { scan-assembler-times {\mppaire\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mmulw\M} 2 } } */
