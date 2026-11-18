/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gc_zbkb -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

#include "pack-volatile.h"

/* { dg-final { scan-assembler-times {\mlwu?\s} 5 } } */
