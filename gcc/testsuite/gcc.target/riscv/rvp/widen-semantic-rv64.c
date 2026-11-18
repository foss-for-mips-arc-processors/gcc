/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include "widen-semantic.h"

/* Same-signedness products use one interleave and a cross product.
   Mixed products must preserve which operand is signed.  */
/* The shared signed extension also retains the widening MAC.  */
/* { dg-final { scan-assembler-times {\mpmacc\.w\.h01\M} 3 } } */
/* { dg-final { scan-assembler-times {\mpmaccu\.w\.h01\M} 1 } } */
/* { dg-final { scan-assembler-times {\mpmaccsu\.w\.h00\M} 2 } } */
/* { dg-final { scan-assembler-times {\mpmulsu\.h\.b00\M} 4 } } */
/* { dg-final { scan-assembler-times {\mpmulsu\.w\.h00\M} 2 } } */

/* RV32 register-pair instructions are not available on RV64.  */
/* { dg-final { scan-assembler-not {\mpwm(acc|ul)} } } */
/* { dg-final { scan-assembler-not {\mpw(add|sub)} } } */
