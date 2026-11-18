/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "average-wide.h"

/* { dg-final { scan-assembler-times {\mpaadd\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.db\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.dh\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaadd\.dw\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.db\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.dh\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpaaddu\.dw\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasub\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasub\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasub\.db\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasub\.dh\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasub\.dw\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasubu\.b\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasubu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasubu\.db\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasubu\.dh\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpasubu\.dw\M} 1 } } */
