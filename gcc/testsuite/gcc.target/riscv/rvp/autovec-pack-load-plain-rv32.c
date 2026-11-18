/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -mlittle-endian -O3" } */

#include "autovec-pack-load-plain.h"

/* { dg-final { scan-assembler-times {\mpncvt\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mlw\M} 2 } } */
/* { dg-final { scan-assembler-not {\mmv\M} } } */
