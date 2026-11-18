/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3" } */

#include "autovec-pack-usat-small.h"

/* { dg-final { scan-assembler-times {\mpnclipiu\.b\M} 1 } } */
/* { dg-final { scan-assembler-not {\mpminu\.h\M} } } */
/* { dg-final { scan-assembler-not {\mmv\M} } } */
