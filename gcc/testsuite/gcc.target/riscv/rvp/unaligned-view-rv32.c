/* { dg-do compile } */
/* { dg-options "-march=rv32gcp -mabi=ilp32d -O2 -mstrict-align -fdump-rtl-expand" } */

#include "unaligned-view.h"

/* { dg-final { scan-assembler-not {\msp\M} } } */
/* { dg-final { scan-assembler-not {\m(call|tail)\M} } } */
/* { dg-final { scan-assembler {\mlbu\M} } } */
/* { dg-final { scan-assembler {\mlhu\M} } } */
/* { dg-final { scan-assembler {\mlw\M} } } */
/* { dg-final { scan-rtl-dump-not "virtual-stack-vars" "expand" } } */
