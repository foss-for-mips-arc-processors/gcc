/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gp -mabi=ilp32d -mlittle-endian -dp" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

#if __riscv_xlen != 32 || defined (__riscv_compressed)
#error "This test requires uncompressed RV32 code generation"
#endif

#include <riscv_packed_simd.h>

uint32_t
rev_length_word (uint32_t x)
{
  return __riscv_rev_32 (x);
}

/* The existing single-instruction word emitter must retain length4.  */
/* { dg-final { scan-assembler-times {\trev\t[^\n]*l=4\][[:space:]]+riscv_rev_32_rv32\n} 1 } } */
/* { dg-final { scan-assembler-times {\trev\t} 1 } } */
