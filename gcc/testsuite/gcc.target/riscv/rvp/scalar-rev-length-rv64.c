/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gp -mabi=lp64d -mlittle-endian -dp" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */

#if __riscv_xlen != 64 || defined (__riscv_compressed)
#error "This test requires uncompressed RV64 code generation"
#endif

#include <riscv_packed_simd.h>

uint32_t
rev_length_word (uint32_t x)
{
  return __riscv_rev_32 (x);
}

uint64_t
rev_length_doubleword (uint64_t x)
{
  return __riscv_rev_64 (x);
}

/* The word macro includes both REV and SRAI, without pinning cost or regs.  */
/* { dg-final { scan-assembler-times {\trev\t[^\n]*l=8\][[:space:]]+riscv_rev_32_rv64\n\tsrai\t[^\n]*,32\n} 1 } } */
/* The existing full-width single instruction must retain length4.  */
/* { dg-final { scan-assembler-times {\trev\t[^\n]*l=4\][[:space:]]+riscv_rev_64_p\n} 1 } } */
/* { dg-final { scan-assembler-times {\trev\t} 2 } } */
