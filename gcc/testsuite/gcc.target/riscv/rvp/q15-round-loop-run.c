/* { dg-do run } */
/* { dg-options "-O3" } */

#include "q15-round-loop.h"

static long long __attribute__ ((noipa, optimize ("O0")))
floor_div (long long value, long long divisor)
{
  return value / divisor - (value < 0 && value % divisor != 0);
}

static short __attribute__ ((noipa, optimize ("O0")))
wrap16 (long long value)
{
  unsigned int bits = (unsigned long long) value & 65535;
  return bits < 32768 ? (int) bits : (int) bits - 65536;
}

static short __attribute__ ((noipa, optimize ("O0")))
reference (short a, short b, unsigned int kind)
{
  long long product = (long long) a * b;
  long long value;
  if (kind == 6)
    value = (unsigned int) (product + 16384) / 32768U;
  else if (kind == 7)
    value = ((unsigned int) product / 16384U + 1) / 2;
  else if (kind == 9)
    value = floor_div (floor_div (product, 16384) + 2, 2);
  else if (kind == 10)
    value = floor_div (wrap16 (floor_div (product, 16384)) + 1, 2);
  else
    {
      if (kind == 8)
	product = wrap16 (product);
      value = floor_div (product + (kind == 4 ? 16383 : 16384), 32768);
    }
  int limit = kind == 5 ? 32766 : 32767;
  return wrap16 (value > limit ? limit : value);
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  typedef void (*kernel) (short *, const short *, const short *, unsigned);
  static const kernel functions[] = {
    q15_round_wide, q15_round_two_shifts, q15_round_wide_two_shifts,
    q15_round_modular, q15_round_bad_constant, q15_round_bad_bound,
    q15_round_logical, q15_round_inner_logical,
    q15_round_truncated_product, q15_round_bad_two_shifts,
    q15_round_truncated_shift
  };
  static const short edges[] = { -32768, -32767, -16385, -16384, -1, 0,
				1, 16383, 16384, 16385, 32766, 32767 };
  static const unsigned int sizes[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 31, 32, 63, 64, 127, 128 };
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
	  a[i] = pattern < 12 ? edges[pattern] : wrap16 (state >> 16);
	  state = state * 1664525 + 1013904223;
	  b[i] = pattern < 12 ? edges[i % 12] : wrap16 (state >> 16);
	}
      for (unsigned int offset = 0; offset < 4; ++offset)
	for (unsigned int size = 0; size < sizeof sizes / sizeof sizes[0];
	     ++size)
	  {
	    unsigned int n = sizes[size];
	    unsigned int other = pattern & 3;
	    for (unsigned int kind = 0; kind < 12; ++kind)
	      {
		for (unsigned int i = 0; i < 144; ++i)
		  {
		    out[i] = 12345;
		    saved[i] = 0x12345678;
		  }
		if (kind < 11)
		  functions[kind] (out + offset, a + offset, b + other, n);
		else
		  q15_round_shared (out + offset, saved + offset,
				    a + offset, b + other, n);
		for (unsigned int i = 0; i < 144; ++i)
		  {
		    int active = i >= offset && i < offset + n;
		    short want = 12345;
		    int product = 0x12345678;
		    if (active)
		      {
			unsigned int j = i - offset + other;
			want = reference (a[i], b[j], kind);
			if (kind == 11)
			  product = (int) a[i] * b[j];
		      }
		    if (out[i] != want || saved[i] != product)
		      __builtin_abort ();
		  }
	      }
	  }
    }
  return 0;
}
