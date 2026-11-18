/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian -fno-tree-vectorize" } */
/* { dg-final { check-function-bodies "**" "" } } */

/*
** repeat_bytes8:
**  ppaire\.b\s+a0,\s*a0,\s*a1
**  pmv\.hs\s+a0,a0
**  ret
*/

#include "vec-init-periodic.h"

/* { dg-final { scan-assembler-times {\tpmv\.hs\t} 2 } } */
/* { dg-final { scan-assembler-times {\tpmv\.ws\t} 1 } } */
