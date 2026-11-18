/* { dg-do run { target riscv64*-*-* } } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "mulhi-low-word.h"

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
check (u32 a, u32 b, u32 upper)
{
#define CHECK_SCALAR(NAME, KIND, ROUND) \
  do \
    { \
      u32 h = high_word (a, b, KIND, ROUND); \
      u32 d[3] = { 0x12345678U, 0, 0x87654321U }; \
      store_##NAME (d + 1, a, b); \
      if (low_##NAME (a, b) != h || zero_##NAME (a, b) != (u64) h \
	  || sign_##NAME (a, b) != (i64) (i32) h \
	  || d[0] != 0x12345678U || d[1] != h || d[2] != 0x87654321U) \
	__builtin_abort (); \
    } \
  while (0)
  CHECK_SCALAR (s, 0, 0);
  CHECK_SCALAR (u, 1, 0);
  CHECK_SCALAR (su, 2, 0);
  CHECK_SCALAR (rs, 0, 1);
  CHECK_SCALAR (ru, 1, 1);
  CHECK_SCALAR (rsu, 2, 1);

  u64 aa = ((u64) upper << 32) | a;
  u64 bb = ((u64) ~upper << 32) | b;
  u32 hs = high_word (a, b, 0, 1);
  u32 hu = high_word (a, b, 1, 1);
  u32 hsu = high_word (a, b, 2, 1);
  u64 expected = ((aa ^ bb) & 0xffffffff00000000ULL) | hsu;
  if (low_us (b, a) != high_word (a, b, 2, 0))
    __builtin_abort ();
  if (low_rus (b, a) != hsu)
    __builtin_abort ();
  if (keep_full (aa, bb) != expected)
    __builtin_abort ();
  if (masked_su (a, b) != high_word (a, b & 0xffff00ffU, 2, 1))
    __builtin_abort ();
  if ((u32) round_s (a, b) != hs || round_u (a, b) != hu)
    __builtin_abort ();
  if ((u32) round_su (a, b) != hsu || (u32) round_us (b, a) != hsu)
    __builtin_abort ();
  if (round_s_wide (a, b) != (i64) (i32) hs)
    __builtin_abort ();
  if (round_u_wide (a, b) != (u64) hu)
    __builtin_abort ();
  if (round_su_wide (a, b) != (i64) (i32) hsu)
    __builtin_abort ();

#if defined (__riscv_p) && __riscv_xlen == 64
#define CHECK_PACKED(NAME, KIND, ROUND) \
  do \
    { \
      u32 word = high_word (a, b, KIND, ROUND); \
      u64 d[3] = { 0x123456789abcdefULL, 0, 0xfedcba9876543210ULL }; \
      if (full_##NAME (aa, b) != (u64) word \
	  || packed_##NAME (aa, b) != word || both_##NAME (a, b) != word \
	  || builtin_##NAME (a, b) != word \
	  || shared_##NAME (aa, b, d + 1) != word \
	  || d[0] != 0x123456789abcdefULL || d[1] != (u64) word \
	  || d[2] != 0xfedcba9876543210ULL) \
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
}

#define SIZE 144
static i32 a[SIZE] __attribute__ ((aligned (64)));
static i32 b[SIZE] __attribute__ ((aligned (64)));
static u32 u[SIZE] __attribute__ ((aligned (64)));
static u32 v[SIZE] __attribute__ ((aligned (64)));
static i32 d[SIZE] __attribute__ ((aligned (64)));
static u32 e[SIZE] __attribute__ ((aligned (64)));

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const u32 values[]
    = { 0, 1, 2, 3, 0x7fff, 0x8000, 0xffff, 0x10000, 0x10001,
	0x3fffffff, 0x40000000, 0x7ffffffe, 0x7fffffff, 0x80000000,
	0x80000001, 0xfffffffe, 0xffffffff };
  static const unsigned sizes[]
    = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, 17, 31, 32, 33,
	63, 64, 65, 127, 128 };
  for (unsigned i = 0; i < sizeof values / sizeof values[0]; ++i)
    for (unsigned j = 0; j < sizeof values / sizeof values[0]; ++j)
      for (unsigned k = 0; k < sizeof values / sizeof values[0]; ++k)
	check (values[i], values[j], values[k]);
  u32 seed = 0x942b6a13U;
  for (unsigned i = 0; i < 16384; ++i)
    {
      seed = seed * 1664525U + 1013904223U;
      u32 av = seed;
      seed = seed * 1664525U + 1013904223U;
      u32 bv = seed;
      seed = seed * 1664525U + 1013904223U;
      check (av, bv, seed);
    }
  for (unsigned off = 0; off < 4; ++off)
    for (unsigned s = 0; s < sizeof sizes / sizeof sizes[0]; ++s)
      for (unsigned kind = 0; kind < 4; ++kind)
	{
	  unsigned n = sizes[s];
	  for (unsigned i = 0; i < SIZE; ++i)
	    {
	      a[i] = u[i] = i % 3 ? i * 2654435761U : values[i % 17];
	      b[i] = v[i] = i % 3 ? ~i * 987654321U : values[(i + off) % 17];
	      d[i] = e[i] = 0x13579bdfU;
	    }
	  if (kind == 0)
	    round_s_loop (d + 4, a + off, b + 3 - off, n);
	  else if (kind == 1)
	    round_u_loop (e + 4, u + off, v + 3 - off, n);
	  else if (kind == 2)
	    round_su_loop (d + 4, a + off, v + 3 - off, n);
	  else
	    round_us_loop (d + 4, u + off, b + 3 - off, n);
	  for (unsigned i = 0; i < SIZE; ++i)
	    {
	      u32 expected = 0x13579bdfU;
	      if (i >= 4 && i < 4 + n)
		{
		  u32 av = u[i - 4 + off], bv = v[i - 4 + 3 - off];
		  expected = kind == 3 ? high_word (bv, av, 2, 1)
			     : high_word (av, bv, kind, 1);
		}
	      if ((kind == 1 ? e[i] : (u32) d[i]) != expected)
		__builtin_abort ();
	    }
	}
  return 0;
}
