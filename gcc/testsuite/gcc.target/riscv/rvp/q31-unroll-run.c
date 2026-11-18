/* { dg-do run } */
/* { dg-options "-O3" } */

#include "q31-unroll.h"

static int __attribute__ ((noipa, optimize ("O0")))
reference (int a, int b)
{
  long long x = (long long) a * b + 1073741824;
  long long d = 2147483648LL;
  x = x / d - (x < 0 && x % d != 0);
  return x > 2147483647 ? 2147483647 : x;
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  typedef void (*kernel) (int *, const int *, const int *, unsigned int);
  static const kernel functions[] = { q31u_plain, q31u_square,
    q31u_adjacent, q31u_strided, q31u_reverse, q31u_no_unroll,
    q31u_alias, q31u_fixed };
  static const int edges[] = { (-2147483647 - 1), -2147483647,
    -1073741824, -1, 0, 1, 1073741824, 2147483646, 2147483647 };
  static const unsigned int sizes[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 31, 32, 63, 64, 127, 128 };
  int a[272] __attribute__ ((aligned (16)));
  int b[272] __attribute__ ((aligned (16)));
  int out[144] __attribute__ ((aligned (16)));
  int saved[144], copy[144];
  unsigned int seed = 0x142857;
  for (unsigned int pattern = 0; pattern < 24; ++pattern)
    {
      for (unsigned int i = 0; i < 272; ++i)
	{
	  seed = seed * 1664525 + 1013904223;
	  a[i] = pattern < 9 ? edges[pattern] : (int) seed;
	  seed = seed * 1664525 + 1013904223;
	  b[i] = pattern < 9 ? edges[i % 9] : (int) seed;
	}
      for (unsigned int offset = 0; offset < 4; ++offset)
	for (unsigned int s = 0; s < sizeof sizes / sizeof sizes[0]; ++s)
	  for (unsigned int kind = 0; kind < 8; ++kind)
	    {
	      unsigned int n = kind == 7 ? 4 : sizes[s];
	      unsigned int other = pattern & 3;
	      for (unsigned int i = 0; i < 144; ++i)
		out[i] = 12345;
	      functions[kind] (out + offset, a + offset, b + other, n);
	      for (unsigned int i = 0; i < 144; ++i)
		{
		  int want = 12345;
		  if (i >= offset && i < offset + n)
		    {
		      unsigned int j = i - offset;
		      int x = a[kind == 4 ? offset + n - 1 - j : i];
		      int y = kind == 1 ? a[i] : kind == 2 ? a[i + 1]
			: b[other + (kind == 3 ? 2 * j : j)];
		      want = reference (x, y);
		    }
		  if (out[i] != want)
		    __builtin_abort ();
		}
	    }

      /* In-place and shifted aliases must retain sequential C semantics.  */
      for (unsigned int offset = 0; offset < 2; ++offset)
	{
	  for (unsigned int i = 0; i < 144; ++i)
	    saved[i] = copy[i] = a[i];
	  for (unsigned int i = 0; i < 128; ++i)
	    saved[i + offset] = reference (saved[i], b[i]);
	  q31u_alias (copy + offset, copy, b, 128);
	  for (unsigned int i = 0; i < 144; ++i)
	    if (copy[i] != saved[i])
	      __builtin_abort ();
	}
    }
  return 0;
}
