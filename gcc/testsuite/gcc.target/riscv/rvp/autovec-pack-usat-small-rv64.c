/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3" } */

#include "autovec-pack-usat-small.h"

/* { dg-final { scan-assembler-times {\mpnclipup\.b\M} 1 } } */
/* { dg-final { scan-assembler-not {\mpminu\.h\M} } } */
/* { dg-final { scan-assembler-times {\mld\M} 1 } } */
/* { dg-final { scan-assembler-not {\mlwu?\M} } } */
