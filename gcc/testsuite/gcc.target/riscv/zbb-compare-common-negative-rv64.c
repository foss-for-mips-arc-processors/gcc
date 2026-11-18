/* { dg-do compile } */
/* { dg-options "-march=rv64gc -mabi=lp64d -O2" } */
/* { dg-skip-if "Assembly check" { *-*-* } { "-flto" } } */

#include "zbb-compare-common.h"

/* { dg-final { scan-assembler-not {\t(?:minu?|maxu?)\t} } } */
