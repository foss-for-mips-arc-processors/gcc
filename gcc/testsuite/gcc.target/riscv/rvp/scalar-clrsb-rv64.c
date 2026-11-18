/* { dg-do compile } */
/* { dg-options "-Os -march=rv64gcp -mabi=lp64d" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */
/* { dg-final { scan-assembler-not "__clrsb(si|di)2" } } */

#if __riscv_xlen != 64
#error "This test requires actual RV64 code generation"
#endif

#include "scalar-clrsb.h"

/*
** clrsb_word:
**  clsw\s+a0,\s*a0
**  ret
*/
/* An SI count must ignore unrelated bits in the DI argument's upper word.  */
/*
** clrsb_low_word:
**  clsw\s+a0,\s*a0
**  ret
*/
/*
** clrsb_doubleword:
**  cls\s+a0,\s*a0
**  ret
*/
/* The full XLEN result is already zero-extended, with range0..31.  */
/*
** clrsb_word_wide:
**  clsw\s+a0,\s*a0
**  ret
*/
/*
** cls_intrinsic_word:
**  clsw\s+a0,\s*a0
**  ret
*/
/*
** cls_intrinsic_word_high_bits:
**  li\s+a0,\s*0
**  ret
*/
/*
** cls_intrinsic_doubleword:
**  cls\s+a0,\s*a0
**  ret
*/
