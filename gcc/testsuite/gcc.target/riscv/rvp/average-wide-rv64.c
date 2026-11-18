/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "average-wide.h"

/* { dg-final { scan-assembler-times {\mpaadd\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasub\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpasub\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpasub\.w\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasubu\.b\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpasubu\.h\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpasubu\.w\M} 1 } } */
