#include <riscv_packed_simd.h>

uint32_t __attribute__ ((noipa))
rev_roundtrip_word (uint32_t x)
{
  return __riscv_rev_32 (__riscv_rev_32 (x));
}

unsigned int __attribute__ ((noipa))
rev_population_word (uint32_t x)
{
  return __builtin_popcount (__riscv_rev_32 (x));
}

unsigned int __attribute__ ((noipa))
rev_parity_word (uint32_t x)
{
  return __builtin_parity (__riscv_rev_32 (x));
}

int __attribute__ ((noipa))
rev_constant_word (void)
{
  return __riscv_rev_32 (1u) == 0x80000000u;
}

#if __riscv_xlen == 64
uint64_t __attribute__ ((noipa))
rev_roundtrip_doubleword (uint64_t x)
{
  return __riscv_rev_64 (__riscv_rev_64 (x));
}

unsigned int __attribute__ ((noipa))
rev_population_doubleword (uint64_t x)
{
  return __builtin_popcountll (__riscv_rev_64 (x));
}

unsigned int __attribute__ ((noipa))
rev_parity_doubleword (uint64_t x)
{
  return __builtin_parityll (__riscv_rev_64 (x));
}

int __attribute__ ((noipa))
rev_constant_doubleword (void)
{
  return __riscv_rev_64 (1ULL) == 0x8000000000000000ULL;
}
#endif
