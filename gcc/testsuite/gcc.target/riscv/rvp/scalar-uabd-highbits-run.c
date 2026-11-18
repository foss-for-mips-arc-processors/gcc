/* { dg-do run } */
/* { dg-options "-O3" } */

#define FN __attribute__ ((noipa))

/* The low words fit unsigned halfwords, but the full registers need not.
   Keep their high bits live so they cannot be assumed to be zero.  */
unsigned long long FN
high_bits (unsigned long long a, unsigned long long b,
	   unsigned long long *saved)
{
  a &= 0xffffffff0000ffffULL;
  b &= 0xffffffff0000ffffULL;
  *saved = a ^ b;
  return __builtin_abs ((int) a - (int) b);
}

/* A signed halfword truncation before ABS is not an unsigned difference.  */
unsigned int FN
narrow_diff (unsigned short a, unsigned short b)
{
  return __builtin_abs ((short) ((int) a - (int) b));
}

unsigned int FN
volatile_diff (const volatile unsigned short *a,
	       const volatile unsigned short *b)
{
  return __builtin_abs ((int) *a - (int) *b);
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  unsigned long long state = 0xdeadbeef12345678ULL;
  for (unsigned int i = 0; i < 65536; ++i)
    {
      state = state * 0x123456789abcdefULL + 37;
      unsigned long long a = (state & ~65535ULL) | i;
      unsigned long long b = (~state & ~65535ULL) | (65535 - i);
      unsigned long long saved;
      int d = (int) (a & 65535) - (int) (b & 65535);
      short narrow = (short) d;
      unsigned long long expected = d < 0 ? -d : d;
      volatile unsigned short x = a, y = b;
      if (high_bits (a, b, &saved) != expected
	  || saved != ((a ^ b) & 0xffffffff0000ffffULL)
	  || narrow_diff (x, y) != (narrow < 0 ? -narrow : narrow)
	  || volatile_diff (&x, &y) != expected)
	__builtin_abort ();
    }
  return 0;
}
