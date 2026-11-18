/* { dg-do run { target riscv64*-*-* } } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "mulhi-acc-low-word.h"

/* Independent 16-bit limbs avoid the optimized 64-bit product idiom.  */
static u32 __attribute__ ((noipa, optimize ("O0")))
high_word (u32 a, u32 b, unsigned kind, unsigned rounded)
{
  u32 a0 = a & 65535, a1 = a >> 16;
  u32 b0 = b & 65535, b1 = b >> 16;
  u32 t = a0 * b0, bottom = t & 65535;
  t = a1 * b0 + (t >> 16);
  u32 middle = t & 65535, high = t >> 16;
  t = a0 * b1 + middle;
  u32 low = (t << 16) | bottom;
  high += a1 * b1 + (t >> 16);
  if (kind != 1 && a >> 31)
    high -= b;
  if (kind == 0 && b >> 31)
    high -= a;
  return high + (rounded ? low >> 31 : 0);
}

static void __attribute__ ((noipa, optimize ("O0")))
check (u32 a, u32 b, u32 c, u32 upper)
{
  u32 h = high_word (a, b, 2, 0);
  u32 rh = high_word (a, b, 2, 1);
  if (low_su (c, a, b) != c + h
      || low_rsu (c, a, b) != c + rh
      || low_us (c, b, a) != c + h
      || low_rus (c, b, a) != c + rh
      || zero_su (c, a, b) != (u64) (u32) (c + h)
      || zero_rsu (c, a, b) != (u64) (u32) (c + rh)
      || masked_su (c, a, b) != c + high_word (a, b & 0xffff00ffU, 2, 0))
    __builtin_abort ();

  u32 d[3] = { 0x12345678U, 0, 0x87654321U };
  store_su (d + 1, c, a, b);
  if (d[0] != 0x12345678U || d[1] != c + h || d[2] != 0x87654321U)
    __builtin_abort ();
  store_rsu (d + 1, c, a, b);
  if (d[0] != 0x12345678U || d[1] != c + rh || d[2] != 0x87654321U)
    __builtin_abort ();

  u64 ac = ((u64) upper << 32) | c;
  u64 aa = ((u64) ~upper << 32) | a;
  u64 bb = ((u64) (upper ^ 0x76543210U) << 32) | b;
  u64 expected = ((ac ^ aa ^ bb) & 0xffffffff00000000ULL) | (u32) (c + h);
  if (keep_full (ac, aa, bb) != expected)
    __builtin_abort ();

#if defined (__riscv_p) && __riscv_xlen == 64
#define CHECK(NAME, KIND, ROUND) \
  do \
    { \
      u32 word = c + high_word (a, b, KIND, ROUND); \
      u64 full = (ac & 0xffffffff00000000ULL) | word; \
      u64 d[3] = { 0x123456789abcdefULL, 0, 0xfedcba9876543210ULL }; \
      if (full_##NAME (ac, aa, b) != full \
	  || packed_##NAME (ac, aa, b) != word \
	  || shared_##NAME (ac, aa, b, d + 1) != word \
	  || d[0] != 0x123456789abcdefULL || d[1] != full \
	  || d[2] != 0xfedcba9876543210ULL) \
	__builtin_abort (); \
    } \
  while (0)
  CHECK (s, 0, 0);
  CHECK (u, 1, 0);
  CHECK (su, 2, 0);
  CHECK (rs, 0, 1);
  CHECK (ru, 1, 1);
  CHECK (rsu, 2, 1);
#endif
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const u32 values[]
    = { 0, 1, 2, 3, 0x7fff, 0x8000, 0xffff, 0x10000, 0x10001,
	0x3fffffff, 0x40000000, 0x7ffffffe, 0x7fffffff, 0x80000000,
	0x80000001, 0xfffffffe, 0xffffffff };
  for (unsigned i = 0; i < sizeof values / sizeof values[0]; ++i)
    for (unsigned j = 0; j < sizeof values / sizeof values[0]; ++j)
      for (unsigned k = 0; k < sizeof values / sizeof values[0]; ++k)
	check (values[i], values[j], values[k], ~values[(i + j + k) % 17]);
  u32 seed = 0x942b6a13U;
  for (unsigned i = 0; i < 16384; ++i)
    {
      seed = seed * 1664525U + 1013904223U;
      u32 a = seed;
      seed = seed * 1664525U + 1013904223U;
      u32 b = seed;
      seed = seed * 1664525U + 1013904223U;
      check (a, b, seed, seed ^ 0xa55a5aa5U);
    }
  return 0;
}
