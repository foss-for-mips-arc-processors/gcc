/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>
#include "join-subvector.h"

/* { dg-final { scan-assembler {\mpack\M} } } */
/* { dg-final { scan-assembler {\mppaireo\.w\M} } } */
/* { dg-final { scan-assembler {\msrli\M[^\n]*,32} } } */
