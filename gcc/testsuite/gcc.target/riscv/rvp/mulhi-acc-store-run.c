/* { dg-do run { target riscv64*-*-* } } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "mulhi-acc-store.h"

static u32 __attribute__ ((noipa, optimize ("O0")))
high_word (u32 a, u32 b, unsigned kind, unsigned rounded, u32 *low)
{
  u32 a0 = a & 65535, a1 = a >> 16;
  u32 b0 = b & 65535, b1 = b >> 16;
  u32 t = a0 * b0, bottom = t & 65535;
  t = a1 * b0 + (t >> 16);
  u32 middle = t & 65535, high = t >> 16;
  t = a0 * b1 + middle;
  *low = (t << 16) | bottom;
  high += a1 * b1 + (t >> 16);
  if (kind != 1 && a >> 31)
    high -= b;
  if (kind == 0 && b >> 31)
    high -= a;
  return high + (rounded ? *low >> 31 : 0);
}

static void __attribute__ ((noipa, optimize ("O0")))
check (u32 a, u32 b, u32 c, u32 upper)
{
  u32 low;
  u32 hs = high_word (a, b, 0, 0, &low);
  u32 hu = high_word (a, b, 1, 0, &low);
  u32 hsu = high_word (a, b, 2, 0, &low);
  u32 carry = low >> 31;
  u32 d[3] = { 0x12345678U, c, 0x87654321U };
#define CHECK(NAME, A, B, HIGH) \
  do \
    { \
      d[1] = c; \
      memory_##NAME (d + 1, A, B); \
      if (d[0] != 0x12345678U || d[1] != (u32) (c + (HIGH)) \
	  || d[2] != 0x87654321U) \
	__builtin_abort (); \
    } \
  while (0)
  CHECK (s, a, b, hs);
  CHECK (u, a, b, hu);
  CHECK (su, a, b, hsu);
  CHECK (us, b, a, hsu);
  CHECK (rs, a, b, hs + carry);
  CHECK (ru, a, b, hu + carry);
  CHECK (rsu, a, b, hsu + carry);
  CHECK (rus, b, a, hsu + carry);

  u64 ac = ((u64) upper << 32) | c;
  u64 aa = ((u64) upper << 32) | a;
  u64 bb = ((u64) ~upper << 32) | b;
  u64 full[3] = { 0x123456789abcdefULL, ac, 0xfedcba9876543210ULL };
  wide_sum (full + 1, a, b);
  if (full[1] != ac + hs || full[0] != 0x123456789abcdefULL
      || full[2] != 0xfedcba9876543210ULL)
    __builtin_abort ();
  u32 saved = 0;
  d[1] = c;
  shared_high (d + 1, &saved, a, b);
  if (d[1] != c + hs || saved != hs)
    __builtin_abort ();
  shared_high (d + 1, d + 1, a, b);
  if (d[1] != hs + hs)
    __builtin_abort ();
  d[1] = c;
  volatile_sum (d + 1, a, b);
  if (d[1] != c + hs)
    __builtin_abort ();
  d[1] = c;
  shift31 (d + 1, a, b);
  if (d[1] != c + ((hs << 1) | carry))
    __builtin_abort ();
  d[1] = c;
  unknown_inputs (d + 1, aa, bb);
  if (d[1] != c + hu + upper * b + ~upper * a)
    __builtin_abort ();

#if defined (__riscv_p) && __riscv_xlen == 64
#define CHECK_PACKED(NAME, KIND, ROUND) \
  do \
    { \
      u32 bottom = high_word (a, b, KIND, ROUND, &low); \
      u32 top = high_word (upper, ~upper, KIND, ROUND, &low); \
      d[1] = c; \
      packed_##NAME (d + 1, aa, bb); \
      if (d[1] != c + bottom) \
	__builtin_abort (); \
      d[1] = c; \
      shared_##NAME (d + 1, full + 1, aa, bb); \
      if (d[1] != c + bottom || full[1] != ((u64) top << 32 | bottom) \
	  || full[0] != 0x123456789abcdefULL \
	  || full[2] != 0xfedcba9876543210ULL) \
	__builtin_abort (); \
    } \
  while (0)
  CHECK_PACKED (s, 0, 0);
  CHECK_PACKED (u, 1, 0);
  CHECK_PACKED (su, 2, 0);
  CHECK_PACKED (rs, 0, 1);
  CHECK_PACKED (ru, 1, 1);
  CHECK_PACKED (rsu, 2, 1);
#endif
  if (d[0] != 0x12345678U || d[2] != 0x87654321U)
    __builtin_abort ();
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const u32 values[]
    = { 0, 1, 2, 3, 0x7fff, 0x8000, 0xffff, 0x10000, 0x10001,
	0x3fffffff, 0x40000000, 0x7ffffffe, 0x7fffffff, 0x80000000,
	0x80000001, 0xfffffffe, 0xffffffff };
  for (unsigned i = 0; i < 17; ++i)
    for (unsigned j = 0; j < 17; ++j)
      for (unsigned k = 0; k < 17; ++k)
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
