/* { dg-do run } */
/* { dg-options "-O3" } */

#include "q31-mul.h"

#define REF __attribute__ ((noipa, optimize ("O0")))
typedef void (*kernel) (int *, const int *, const int *, unsigned int);

static int REF
wrap32 (unsigned long long value)
{
  unsigned int bits = value;
  return bits < 2147483648U ? (long long) bits
			  : (long long) bits - 4294967296LL;
}

static long long REF
scale (long long value, long long divisor)
{
  long long result = value / divisor;
  return result - (value < 0 && value % divisor != 0);
}

static int REF
reference (int a, int b, unsigned int kind)
{
  long long value = (long long) a * b;
  if (kind == 6)
    value = wrap32 (value);
  if (kind == 10)
    value = (long long) a * (unsigned int) b;
  if (kind == 9)
    {
      unsigned long long product = (unsigned long long) (unsigned int) a
				   * (unsigned int) b;
      product = (product + 1073741824) / 2147483648ULL;
      return product > 2147483647 ? 2147483647 : product;
    }
  if (kind == 1 || kind == 8 || kind == 10 || kind == 13)
    value += 1073741824;
  if (kind == 3)
    value += 1073741823;
  value = scale (value, kind == 4 ? 4294967296LL : 2147483648LL);
  if (kind == 7 && value < -2147483646)
    value = -2147483646;
  long long limit = kind == 2 ? 2147483646 : 2147483647;
  if (kind != 5 && kind != 6 && value > limit)
    value = limit;
  return wrap32 (value);
}

static int REF
check_vectors (int a0, int a1, int b0, int b1)
{
  v2si a = { a0, a1 }, b = { b0, b1 };
  v2di saved, saved_round;
  v2si p = pair (a, b), r = pair_round (a, b);
  v2si s = shared (a, b, &saved);
  v2si t = shared_round (a, b, &saved_round);
  for (unsigned int lane = 0; lane < 2; ++lane)
    {
      int want = reference (a[lane], b[lane], 0);
      int rounded_want = reference (a[lane], b[lane], 1);
      long long product = (long long) a[lane] * b[lane];
      if (scalar (a[lane], b[lane]) != want || p[lane] != want
	  || s[lane] != want || rounded (a[lane], b[lane]) != rounded_want
	  || r[lane] != rounded_want || t[lane] != rounded_want
	  || saved[lane] != product || saved_round[lane] != product)
	return 1;
    }
  return 0;
}

static int REF
check_loops (const int *a, const int *b, unsigned int offset,
	     unsigned int other, unsigned int n)
{
  static const kernel functions[] = { q31, q31_round, q31_wrong_limit,
    q31_wrong_round, q31_shift32, q31_unclamped, q31_narrowed,
    q31_lower_clamp, q31_two_shifts };
  unsigned int u[272] __attribute__ ((aligned (16)));
  unsigned int v[272] __attribute__ ((aligned (16)));
  int out[272] __attribute__ ((aligned (16)));
  long long saved[272] __attribute__ ((aligned (16)));
  for (unsigned int i = 0; i < 272; ++i)
    {
      u[i] = a[i];
      v[i] = b[i];
    }
  for (unsigned int kind = 0; kind < 14; ++kind)
    {
      for (unsigned int i = 0; i < 272; ++i)
	{
	  out[i] = 0x12345678;
	  saved[i] = 0x123456789abcdefLL;
	}
      if (kind < 9)
	functions[kind] (out + offset, a + offset, b + other, n);
      else if (kind == 9)
	q31_unsigned (out + offset, u + offset, v + other, n);
      else if (kind == 10)
	q31_mixed (out + offset, a + offset, v + other, n);
      else if (kind == 11)
	q31_shared (out + offset, saved + offset, a + offset, b + other, n);
      else if (kind == 12)
	q31_wide (saved + offset, a + offset, b + other, n);
      else
	q31_wide_round (saved + offset, a + offset, b + other, n);
      for (unsigned int i = 0; i < 272; ++i)
	{
	  int active = i >= offset && i < offset + n;
	  int want = 0x12345678;
	  long long wide = 0x123456789abcdefLL;
	  if (active)
	    {
	      unsigned int j = i - offset + other;
	      int value = reference (a[i], b[j], kind);
	      if (kind < 12)
		want = value;
	      if (kind == 11)
		wide = (long long) a[i] * b[j];
	      if (kind >= 12)
		wide = value;
	    }
	  if (out[i] != want || saved[i] != wide)
	    return kind + 1;
	}
    }
  return 0;
}

int REF
main (void)
{
  static const int edges[] = { -2147483647 - 1, -2147483647, -1073741825,
    -1073741824, -65537, -65536, -32769, -32768, -2, -1, 0, 1, 2, 32767,
    32768, 65535, 65536, 1073741823, 1073741824, 2147483646, 2147483647 };
  const unsigned int count = sizeof (edges) / sizeof (edges[0]);
  int a[272] __attribute__ ((aligned (16)));
  int b[272] __attribute__ ((aligned (16)));
  unsigned int state = 0x12345678;
  for (unsigned int pattern = 0; pattern < 48; ++pattern)
    {
      for (unsigned int i = 0; i < 272; ++i)
	{
	  state = state * 1664525 + 1013904223;
	  a[i] = pattern < count ? edges[pattern] : wrap32 (state);
	  state = state * 1664525 + 1013904223;
	  b[i] = pattern < count ? edges[i % count] : wrap32 (state);
	}
      for (unsigned int offset = 0; offset < 4; ++offset)
	for (unsigned int size = 0; size < 20; ++size)
	  {
	    unsigned int n = size < 18 ? size : size == 18 ? 127 : 128;
	    if (check_loops (a, b, offset, pattern & 3, n))
	      return 1;
	  }
      if (check_loops (a, b, 0, 0, 256)
	  || check_loops (a, a, 1, 1, 255))
	return 2;
      for (unsigned int i = 0; i < 270; i += 2)
	if (check_vectors (a[i], a[i + 1], b[i], b[i + 1]))
	  return 3;
    }
  return 0;
}
