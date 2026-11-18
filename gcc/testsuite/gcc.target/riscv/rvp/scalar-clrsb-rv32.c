/* { dg-do compile } */
/* { dg-options "-Os -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */
/* { dg-final { scan-assembler-not "__clrsbsi2" } } */
/* { dg-final { scan-assembler-not {\tclsw\s} } } */

#if __riscv_xlen != 32
#error "This test requires actual RV32 code generation"
#endif

#include "scalar-clrsb.h"

/*
** clrsb_word:
**  cls\s+a0,\s*a0
**  ret
*/
/*
** clrsb_low_word:
**  cls\s+a0,\s*a0
**  ret
*/
/* RV32 must still count both halves through the existing DI fallback.  */
/*
** clrsb_doubleword:
**  ...
**  (call|tail)\s+__clrsbdi2(?:@plt)?
**  ...
*/
/*
** clrsb_word_wide:
**  ...
**  cls\s+[^\n]+
**  ...
**  ret
*/
/*
** cls_intrinsic_word:
**  cls\s+a0,\s*a0
**  ret
*/
/* A semantic count has no bits above bit4.  */
/*
** cls_intrinsic_word_high_bits:
**  li\s+a0,\s*0
**  ret
*/
