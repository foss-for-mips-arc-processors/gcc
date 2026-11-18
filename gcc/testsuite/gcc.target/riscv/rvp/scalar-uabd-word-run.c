/* { dg-do run } */
/* { dg-options "-O3" } */

#include "scalar-uabd-word.h"

/* The low word is an unsigned halfword, but the upper word remains live.
   Only the scalar difference may be used in the wrapping word addition.  */
unsigned int FN
word_shared (unsigned long long a, unsigned long long b, unsigned int sum,
	     unsigned long long *saved)
{
  a &= 0xffffffff0000ffffULL;
  b &= 0xffffffff0000ffffULL;
  *saved = a ^ b;
  return sum + __builtin_abs ((int) a - (int) b);
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const unsigned int seeds[] = { 0, 1, 0x7fffffffU, 0x80000000U,
				       0xfffffffeU, 0xffffffffU };
  unsigned short a[258], b[258];
  unsigned long long state = 0xdeadbeef12345678ULL;
  for (unsigned int i = 0; i < 65536; ++i)
    {
      unsigned char ca = i, cb = i >> 8;
      int byte_diff = (int) ca - (int) cb;
      unsigned int byte_abs = byte_diff < 0 ? -byte_diff : byte_diff;
      unsigned short ha = i, hb = i * 31337;
      int half_diff = (int) ha - (int) hb;
      unsigned int half_abs = half_diff < 0 ? -half_diff : half_diff;
      state = state * 0x123456789abcdefULL + 37;
      unsigned long long x = (state & ~65535ULL) | ha;
      unsigned long long y = (~state & ~65535ULL) | hb;
      for (unsigned int j = 0; j < sizeof seeds / sizeof seeds[0]; ++j)
	{
	  unsigned int sum = seeds[j];
	  unsigned long long saved;
	  if (word_byte_add (ca, cb, sum) != sum + byte_abs
	      || word_half_add (ha, hb, sum) != sum + half_abs
	      || word_load_add (&ha, &hb, sum) != sum + half_abs
	      || word_shared (x, y, sum, &saved) != sum + half_abs
	      || saved != ((x ^ y) & 0xffffffff0000ffffULL))
	    __builtin_abort ();
	}
    }
  for (unsigned int i = 0; i < 258; ++i)
    {
      a[i] = i % 3 ? i * 32749 : 0;
      b[i] = i % 5 ? i * 65521 : 65535;
    }
  for (unsigned int n = 0; n <= 257; ++n)
    for (unsigned int offset = 0; offset < 2; ++offset)
      for (unsigned int j = 0; j < sizeof seeds / sizeof seeds[0]; ++j)
	{
	  unsigned int expected = seeds[j];
	  for (unsigned int i = 0; i < n; ++i)
	    {
	      int diff = (int) a[i + offset] - (int) b[i + offset];
	      expected += diff < 0 ? -diff : diff;
	    }
	  if (word_loop (a + offset, b + offset, n, seeds[j]) != expected)
	    __builtin_abort ();
	}
  return 0;
}
