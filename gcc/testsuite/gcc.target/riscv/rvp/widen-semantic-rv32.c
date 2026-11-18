/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "widen-semantic.h"

/* The shared signed extension also retains the widening MAC.  */
/* { dg-final { scan-assembler-times {\mpwmacc\.h\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpwmaccu\.h\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpwmaccsu\.h\M} 2 } } */
/* Both signed/unsigned operand orders must match.  */
/* { dg-final { scan-assembler-times {\mpwmulsu\.b\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpwmulsu\.h\M} 2 } } */
/* { dg-final { scan-assembler {\mpwsubu\.b\M} } } */
/* { dg-final { scan-assembler {\mpwsubu\.h\M} } } */
