/* { dg-do run } */
/* { dg-options "-O3" } */

#include "q15-loop.h"

static short __attribute__ ((noipa, optimize ("O0")))
wrap (long long value)
{
  unsigned int bits = (unsigned long long) value & 65535;
  return bits < 32768 ? (int) bits : (int) bits - 65536;
}

static short __attribute__ ((noipa, optimize ("O0")))
reference (short a, short b, unsigned int kind)
{
  long long value = (long long) a * b;
  if (kind == 6)
    value = wrap (value);
  value += kind == 1 ? 16384 : kind == 3 ? 16383 : 0;
  long long divisor = kind == 4 ? 65536 : 32768;
  long long result = value / divisor;
  if (value < 0 && value % divisor)
    --result;
  int limit = kind == 2 ? 32766 : 32767;
  if (kind != 5 && kind != 6 && result > limit)
    result = limit;
  return wrap (result);
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  typedef void (*kernel) (short *, const short *, const short *, unsigned);
  static const kernel functions[] = { q15, q15_round, q15_wrong_limit,
    q15_wrong_round, q15_shift16, q15_unclamped, q15_narrowed_product };
  static const short edges[] = { -32768, -32767, -16385, -16384, -1, 0,
				1, 16383, 16384, 16385, 32766, 32767 };
  short a[144] __attribute__ ((aligned (16)));
  short b[144] __attribute__ ((aligned (16)));
  short out[144] __attribute__ ((aligned (16)));
  int saved[144] __attribute__ ((aligned (16)));
  unsigned int state = 0x12345678;
  for (unsigned int pattern = 0; pattern < 24; ++pattern)
    {
      for (unsigned int i = 0; i < 144; ++i)
	{
	  state = state * 1664525 + 1013904223;
	  a[i] = pattern < 12 ? edges[pattern] : wrap (state >> 16);
	  state = state * 1664525 + 1013904223;
	  b[i] = pattern < 12 ? edges[i % 12] : wrap (state >> 16);
	}
      for (unsigned int offset = 0; offset < 4; ++offset)
	for (unsigned int size = 0; size < 20; ++size)
	  {
	    unsigned int n = size < 18 ? size : size == 18 ? 127 : 128;
	    unsigned int other = pattern & 3;
	    for (unsigned int kind = 0; kind < 8; ++kind)
	      {
		for (unsigned int i = 0; i < 144; ++i)
		  {
		    out[i] = 12345;
		    saved[i] = 0x12345678;
		  }
		if (kind < 7)
		  functions[kind] (out + offset, a + offset, b + other, n);
		else
		  q15_shared_product (out + offset, saved + offset,
				      a + offset, b + other, n);
		for (unsigned int i = 0; i < 144; ++i)
		  {
		    int active = i >= offset && i < offset + n;
		    short want = 12345;
		    int product = 0x12345678;
		    if (active)
		      {
			unsigned int j = i - offset + other;
			want = reference (a[i], b[j], kind < 7 ? kind : 0);
			if (kind == 7)
			  product = (int) a[i] * b[j];
		      }
		    if (out[i] != want || saved[i] != product)
		      return 1;
		  }
	      }
	  }
    }
  return 0;
}
