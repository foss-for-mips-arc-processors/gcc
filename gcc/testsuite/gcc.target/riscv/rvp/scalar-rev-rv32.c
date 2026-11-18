/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gcp -mabi=ilp32d -mlittle-endian" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

#if __riscv_xlen != 32
#error "This test requires actual RV32 code generation"
#endif

#include "scalar-rev.h"

/*
** rev_roundtrip_word:
**  ret
*/
/*
** rev_population_word:
**  cpop\s+a0,\s*a0
**  ret
*/
/*
** rev_parity_word:
**  cpop\s+a0,\s*a0
**  andi\s+a0,\s*a0,\s*1
**  ret
*/
/*
** rev_constant_word:
**  li\s+a0,\s*1
**  ret
*/
