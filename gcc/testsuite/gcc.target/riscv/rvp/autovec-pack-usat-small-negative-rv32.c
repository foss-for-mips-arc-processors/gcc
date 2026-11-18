/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O3" } */

#include "autovec-pack-usat-small-negative.h"

/* { dg-final { scan-assembler-not {\mpnclipiu\.b\M} } } */
