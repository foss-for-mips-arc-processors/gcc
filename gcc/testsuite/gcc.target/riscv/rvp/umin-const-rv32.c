/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2" } */

#include "umin-const.h"

/* PUSATI interprets its input as signed and is not an unsigned minimum.  */
/* { dg-final { scan-assembler {\mpminu\.h\M} } } */
/* { dg-final { scan-assembler {\mpminu\.dh\M} } } */
/* { dg-final { scan-assembler {\mpminu\.dw\M} } } */
/* { dg-final { scan-assembler-not {\mpusati\.} } } */
