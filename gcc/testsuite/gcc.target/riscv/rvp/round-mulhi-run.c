/* { dg-do run } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-O3" } */

#include "round-mulhi.h"

/* Use modular arithmetic and an unoptimized reference to keep the oracle
   independent of the signed multiply/add/shift patterns under test.  */
static uint32_t __attribute__ ((noipa, optimize ("O0")))
reference (uint32_t a, uint32_t b, int sa, int sb)
{
  uint64_t p = (uint64_t) a * b;
  if (sa && (a >> 31))
    p -= (uint64_t) b << 32;
  if (sb && (b >> 31))
    p -= (uint64_t) a << 32;
  return (p + UINT64_C (2147483648)) >> 32;
}

static int
scalar (uint32_t a, uint32_t b)
{
  uint32_t s = reference (a, b, 1, 1);
  uint32_t u = reference (a, b, 0, 0);
  uint32_t m = reference (a, b, 1, 0);
  return ((uint32_t) round_s (a, b) != s || round_u (a, b) != u
	  || (uint32_t) round_su (a, b) != m
	  || (uint32_t) round_us (b, a) != m
	  || round_s_wide (a, b) != (int64_t) (int32_t) s
	  || round_u_wide (a, b) != (uint64_t) u
	  || round_su_wide (a, b) != (int64_t) (int32_t) m);
}

int
main (void)
{
  static const uint32_t edge[] = {
    0, 1, 2, 32767, 32768, 65535, 65536, 0x3fffffff,
    0x40000000, 0x7ffffffe, 0x7fffffff, 0x80000000, 0x80000001,
    0xc0000000, 0xfffffffe, 0xffffffff
  };
  for (unsigned int i = 0; i < 16; ++i)
    for (unsigned int j = 0; j < 16; ++j)
      if (scalar (edge[i], edge[j]))
	return 1;
  uint32_t state = 123456789;
  for (unsigned int i = 0; i < 4096; ++i)
    {
      state = state * 1664525u + 1013904223u;
      uint32_t a = state;
      state = state * 1664525u + 1013904223u;
      if (scalar (a, state))
	return 2;
    }

  static const unsigned int lengths[] = { 0, 1, 2, 3, 7, 8, 9, 65, 128 };
  int32_t a[160], b[160], d[160], m[160], r[160];
  uint32_t ua[160], ub[160], ud[160];
  for (unsigned int k = 0; k < 9; ++k)
    {
      for (unsigned int i = 0; i < 160; ++i)
	{
	  a[i] = ua[i] = edge[i % 16];
	  b[i] = ub[i] = edge[(i * 7 + k) % 16];
	  d[i] = ud[i] = m[i] = r[i] = 42;
	}
      unsigned int n = lengths[k];
      round_s_loop (d + 4, a + 1, b + 3, n);
      round_u_loop (ud + 4, ua + 1, ub + 3, n);
      round_su_loop (m + 4, a + 1, ub + 3, n);
      round_us_loop (r + 4, ub + 3, a + 1, n);
      for (unsigned int i = 0; i < 160; ++i)
	{
	  uint32_t s = 42, u = 42, su = 42;
	  if (i >= 4 && i < n + 4)
	    {
	      s = reference (a[i - 3], b[i - 1], 1, 1);
	      u = reference (ua[i - 3], ub[i - 1], 0, 0);
	      su = reference (a[i - 3], ub[i - 1], 1, 0);
	    }
	  if ((uint32_t) d[i] != s || ud[i] != u
	      || (uint32_t) m[i] != su || (uint32_t) r[i] != su)
	    return 3;
	}
    }
  return 0;
}
