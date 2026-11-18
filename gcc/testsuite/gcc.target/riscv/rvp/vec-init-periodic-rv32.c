/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian -fno-tree-vectorize" } */
/* { dg-final { check-function-bodies "**" "" } } */

/*
** repeat_bytes8:
**  ppaire\.b\s+a0,\s*a0,\s*a1
**  pmv\.dhs\s+a0,a0
**  ret
*/

#include "vec-init-periodic.h"

/* { dg-final { scan-assembler-times {\tpmv\.hs\t} 1 } } */
/* { dg-final { scan-assembler-not {\tpmv\.dws\t} } } */
