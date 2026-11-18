/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#if __riscv_xlen != 64
#error "This test requires actual RV64 code generation"
#endif

#include "scalar-rev.h"

/*
** rev_roundtrip_word:
**  sext\.w\s+a0,\s*a0
**  ret
*/
/*
** rev_population_word:
**  cpopw\s+a0,\s*a0
**  ret
*/
/*
** rev_parity_word:
**  cpopw\s+a0,\s*a0
**  andi\s+a0,\s*a0,\s*1
**  ret
*/
/*
** rev_constant_word:
**  li\s+a0,\s*1
**  ret
*/
/*
** rev_roundtrip_doubleword:
**  ret
*/
/*
** rev_population_doubleword:
**  cpop\s+a0,\s*a0
**  ret
*/
/*
** rev_parity_doubleword:
**  cpop\s+a0,\s*a0
**  andi\s+a0,\s*a0,\s*1
**  ret
*/
/*
** rev_constant_doubleword:
**  li\s+a0,\s*1
**  ret
*/
