/* { dg-do run } */
/* { dg-options "-O3" } */

#include "qmul-cost.h"

static long long __attribute__ ((noipa, optimize ("O0")))
reference (long long a, long long b, unsigned int precision)
{
  long long divisor = 1LL << (precision - 1);
  long long value = a * b + divisor / 2;
  return value / divisor - (value < 0 && value % divisor != 0);
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  typedef void (*kernel16) (short *, int *, const short *, const short *,
			   unsigned int);
  typedef void (*kernel32) (int *, long long *, const int *, const int *,
			   unsigned int);
  static const kernel16 functions16[] = { cost_q15_round, cost_q15_two,
    cost_q15_product, cost_q15_scaled };
  static const kernel32 functions32[] = { cost_q31_round, cost_q31_two,
    cost_q31_product, cost_q31_wide };
  static const int edges[] = { (-2147483647 - 1), -2147483647, -1073741824,
    -32768, -1, 0, 1, 32767, 1073741824, 2147483646, 2147483647 };
  static const short half[] = { -32768, -32767, -16384, -2, -1, 0,
    1, 2, 16384, 32766, 32767 };
  static const unsigned int sizes[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 31, 32, 63, 64, 127, 128 };
  short a[144] __attribute__ ((aligned (16)));
  short b[144] __attribute__ ((aligned (16)));
  short out16[144] __attribute__ ((aligned (16)));
  int x[144] __attribute__ ((aligned (16)));
  int y[144] __attribute__ ((aligned (16)));
  int out32[144] __attribute__ ((aligned (16)));
  int saved16[144] __attribute__ ((aligned (16)));
  long long saved32[144] __attribute__ ((aligned (16)));
  unsigned int state = 0x12345678;
  for (unsigned int pattern = 0; pattern < 24; ++pattern)
    {
      for (unsigned int i = 0; i < 144; ++i)
	{
	  state = state * 1664525 + 1013904223;
	  a[i] = pattern < 11 ? half[pattern] : (short) (state >> 16);
	  x[i] = pattern < 11 ? edges[pattern] : (int) state;
	  state = state * 1664525 + 1013904223;
	  b[i] = pattern < 11 ? half[i % 11] : (short) (state >> 16);
	  y[i] = pattern < 11 ? edges[i % 11] : (int) state;
	}
      for (unsigned int offset = 0; offset < 4; ++offset)
	for (unsigned int size = 0; size < sizeof sizes / sizeof sizes[0];
	     ++size)
	  {
	    unsigned int n = sizes[size], other = pattern & 3;
	    for (unsigned int kind = 0; kind < 4; ++kind)
	      {
		for (unsigned int i = 0; i < 144; ++i)
		  {
		    out16[i] = out32[i] = 12345;
		    saved16[i] = saved32[i] = 0x12345678;
		  }
		functions16[kind] (out16 + offset, saved16 + offset,
				   a + offset, b + other, n);
		functions32[kind] (out32 + offset, saved32 + offset,
				   x + offset, y + other, n);
		for (unsigned int i = 0; i < 144; ++i)
		  {
		    long long want16 = 12345, want32 = 12345;
		    long long save16 = 0x12345678, save32 = 0x12345678;
		    if (i >= offset && i < offset + n)
		      {
			unsigned int j = i - offset + other;
			want16 = reference (a[i], b[j], 16);
			want32 = reference (x[i], y[j], 32);
			if (kind == 3)
			  save16 = want16;
			if (want16 > 32767)
			  want16 = 32767;
			if (want32 > 2147483647)
			  want32 = 2147483647;
			if (kind == 2)
			  {
			    save16 = (int) a[i] * b[j];
			    save32 = (long long) x[i] * y[j];
			  }
			else if (kind == 3)
			  save32 = want32;
		      }
		    if (out16[i] != want16 || out32[i] != want32
			|| saved16[i] != save16 || saved32[i] != save32)
		      __builtin_abort ();
		  }
	      }
	  }
    }
  return 0;
}
