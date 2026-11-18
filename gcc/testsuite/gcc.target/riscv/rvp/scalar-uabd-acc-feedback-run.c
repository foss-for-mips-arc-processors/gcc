/* { dg-do run } */
/* { dg-options "-O3" } */

/* The accumulator is also an input to the absolute difference.  The
   native packed instruction must read both uses before writing it.  */
unsigned long __attribute__ ((noipa))
feedback_acc (const unsigned char *b, unsigned int n, unsigned long sum)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      sum &= 255;
      sum += __builtin_abs ((int) sum - (int) b[i]);
    }
  return sum;
}

#ifndef RVP_ACC_COMPILE_ONLY
int __attribute__ ((optimize ("O0")))
main (void)
{
  static const unsigned long seeds[] = { 0, 255, 256, ~0UL, ~1UL,
					1UL << (sizeof (long) * 8 - 1) };
  unsigned char b[258];
  for (unsigned int i = 0; i < 65536; ++i)
    {
      unsigned int x = i & 255, y = i >> 8;
      unsigned int diff = x < y ? y - x : x - y;
      b[0] = y;
      if (feedback_acc (b, 1, x) != x + diff)
	__builtin_abort ();
    }
  for (unsigned int i = 0; i < 258; ++i)
    b[i] = i % 3 ? i * 73 : 255;
  for (unsigned int n = 0; n <= 257; ++n)
    for (unsigned int offset = 0; offset < 2; ++offset)
      for (unsigned int j = 0; j < sizeof seeds / sizeof seeds[0]; ++j)
	{
	  unsigned long expected = seeds[j];
	  for (unsigned int i = 0; i < n; ++i)
	    {
	      unsigned int x = expected & 255, y = b[i + offset];
	      expected = x + (x < y ? y - x : x - y);
	    }
	  if (feedback_acc (b + offset, n, seeds[j]) != expected)
	    __builtin_abort ();
	}
  return 0;
}
#endif
