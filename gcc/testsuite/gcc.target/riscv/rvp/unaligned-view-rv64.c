/* { dg-do compile } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2 -mstrict-align -fdump-rtl-expand" } */

#include "unaligned-view.h"

/* { dg-final { scan-assembler-not {\msp\M} } } */
/* { dg-final { scan-assembler-not {\m(call|tail)\M} } } */
/* { dg-final { scan-assembler {\mlbu\M} } } */
/* { dg-final { scan-assembler {\mlhu\M} } } */
/* { dg-final { scan-assembler {\mlwu\M} } } */
/* { dg-final { scan-rtl-dump-not "virtual-stack-vars" "expand" } } */
