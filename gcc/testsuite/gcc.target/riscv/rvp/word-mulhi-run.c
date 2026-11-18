/* { dg-do run { target riscv64*-*-* } } */
/* { dg-options "-O3 -march=rv64gcp -mabi=lp64d -mlittle-endian" } */

#include "word-mulhi.h"

/* Shift-and-add is independent of multiply-high instruction selection.  */
static u64 __attribute__ ((noipa, optimize ("O0")))
product (u64 a, u64 b)
{
  u64 result = 0;
  for (unsigned i = 0; i < 64; ++i)
    {
      if (b & 1)
	result += a;
      a <<= 1;
      b >>= 1;
    }
  return result;
}

static u64 __attribute__ ((noipa, optimize ("O0")))
word_product (u32 a, u32 b, unsigned kind)
{
  u64 result = product (a, b);
  if (kind != 1 && a >> 31)
    result -= (u64) b << 32;
  if (kind == 0 && b >> 31)
    result -= (u64) a << 32;
  return result;
}

static void __attribute__ ((noipa, optimize ("O0")))
check (u32 a, u32 b, u32 upper)
{
  u64 p = word_product (a, b, 2);
  u32 h = p >> 32;
  u32 d[3] = { 0x12345678U, 0, 0x87654321U };
  u64 full[3] = { 0x123456789abcdefULL, 0, 0xfedcba9876543210ULL };
#define CHECK(NAME, A, B) \
  do \
    { \
      word_##NAME##_store (d + 1, A, B); \
      if (word_##NAME (A, B) != h || word_##NAME##_zero (A, B) != (u64) h \
	  || word_##NAME##_sign (A, B) != (i64) (i32) h \
	  || word_##NAME##_shared (full + 1, A, B) != h \
	  || full[1] != p || d[1] != h) \
	__builtin_abort (); \
    } \
  while (0)
  CHECK (su, a, b);
  CHECK (us, b, a);
  word_s_store (d + 1, a, b);
  if (d[1] != (u32) (word_product (a, b, 0) >> 32))
    __builtin_abort ();
  word_u_store (d + 1, a, b);
  if (d[1] != (u32) (word_product (a, b, 1) >> 32)
      || d[0] != 0x12345678U || d[2] != 0x87654321U
      || full[0] != 0x123456789abcdefULL
      || full[2] != 0xfedcba9876543210ULL)
    __builtin_abort ();
  u64 aa = ((u64) upper << 32) | a;
  u64 bb = ((u64) ~upper << 32) | b;
  if (unknown_product (aa, bb) != product (aa, bb) >> 32
      || unknown_left (aa, b) != product (aa, b) >> 32
      || shift31 (a, b) != (i64) p >> 31
      || shift33 (a, b) != (i64) p >> 33
      || word_masked (a, b) != word_product (a, b & 0xffff00ffU, 2) >> 32
      || word_narrowed (aa, bb) != h || word_logical (a, b) != (u64) h)
    __builtin_abort ();
}

#define SIZE 144
static i32 a[SIZE], b[SIZE];
static u32 u[SIZE], v[SIZE], d[SIZE];

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const u32 values[]
    = { 0, 1, 0xffff, 0x10000, 0x7fffffff, 0x80000000,
	0x80000001, 0xfffffffe, 0xffffffff };
  static const unsigned sizes[] = { 0, 1, 2, 3, 4, 7, 8, 15, 16, 17,
				   31, 32, 33, 63, 64, 65, 127, 128 };
  for (unsigned i = 0; i < 9; ++i)
    for (unsigned j = 0; j < 9; ++j)
      for (unsigned k = 0; k < 9; ++k)
	check (values[i], values[j], values[k]);
  u32 seed = 0x123a89ef;
  for (unsigned i = 0; i < 4096; ++i)
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
	      a[i] = u[i] = i % 3 ? i * 2654435761U : values[i % 9];
	      b[i] = v[i] = i % 3 ? ~i * 987654321U : values[(i + off) % 9];
	      d[i] = 0x13579bdfU;
	    }
	  if (kind == 0)
	    word_s_loop (d + 4, a + off, b + 3 - off, n);
	  else if (kind == 1)
	    word_u_loop (d + 4, u + off, v + 3 - off, n);
	  else if (kind == 2)
	    word_su_loop (d + 4, a + off, v + 3 - off, n);
	  else
	    word_us_loop (d + 4, u + off, b + 3 - off, n);
	  for (unsigned i = 0; i < SIZE; ++i)
	    {
	      u32 expected = 0x13579bdfU;
	      if (i >= 4 && i < 4 + n)
		{
		  u32 av = u[i - 4 + off], bv = v[i - 4 + 3 - off];
		  expected = (kind == 3 ? word_product (bv, av, 2)
			      : word_product (av, bv, kind)) >> 32;
		}
	      if (d[i] != expected)
		__builtin_abort ();
	    }
	}
  return 0;
}
