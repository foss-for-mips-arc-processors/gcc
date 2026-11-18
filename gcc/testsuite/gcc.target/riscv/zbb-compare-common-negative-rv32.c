/* { dg-do compile } */
/* { dg-options "-march=rv32gc -mabi=ilp32d -O2" } */
/* { dg-skip-if "Assembly check" { *-*-* } { "-flto" } } */

#include "zbb-compare-common.h"

/* { dg-final { scan-assembler-not {\t(?:minu?|maxu?)\t} } } */
