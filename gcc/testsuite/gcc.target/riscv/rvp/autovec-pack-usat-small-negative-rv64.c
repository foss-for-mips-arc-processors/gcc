/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3" } */

#include "autovec-pack-usat-small-negative.h"

/* { dg-final { scan-assembler-not {\mpnclipup\.b\M} } } */
