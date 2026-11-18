#ifdef __riscv_p
#include <riscv_packed_simd.h>
#endif

int __attribute__ ((noipa))
clrsb_word (int x)
{
  return __builtin_clrsb (x);
}

int __attribute__ ((noipa))
clrsb_low_word (long long x)
{
  return __builtin_clrsb ((int) x);
}

int __attribute__ ((noipa))
clrsb_doubleword (long long x)
{
  return __builtin_clrsbll (x);
}

unsigned long long __attribute__ ((noipa))
clrsb_word_wide (int x)
{
  return __builtin_clrsb (x);
}

#ifdef __riscv_p
unsigned int __attribute__ ((noipa))
cls_intrinsic_word (int x)
{
  return __riscv_cls_32 (x);
}

unsigned int __attribute__ ((noipa))
cls_intrinsic_word_high_bits (int x)
{
  return __riscv_cls_32 (x) & ~31U;
}

#if __riscv_xlen == 64
unsigned int __attribute__ ((noipa))
cls_intrinsic_doubleword (long long x)
{
  return __riscv_cls_64 (x);
}
#endif
#endif
