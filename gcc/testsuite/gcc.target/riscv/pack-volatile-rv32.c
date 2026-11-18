/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp_zbkb -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

#include "pack-volatile.h"

/* Include the pointer load in pack_volatile_step.  */
/* { dg-final { scan-assembler-times {\mlwu?\s} 6 } } */
