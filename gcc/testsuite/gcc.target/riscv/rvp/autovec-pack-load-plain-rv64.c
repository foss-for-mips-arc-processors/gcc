/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -mlittle-endian -O3" } */

#include "autovec-pack-load-plain.h"

/* { dg-final { scan-assembler-times {\munzip8p\M} 1 } } */
/* { dg-final { scan-assembler-times {\mld\M} 1 } } */
/* { dg-final { scan-assembler-not {\mlwu?\M} } } */
