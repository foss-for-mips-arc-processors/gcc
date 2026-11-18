/* { dg-do run } */
/* { dg-options "-O3" } */

#define SAD_SIGNED(NAME, TYPE) \
TYPE __attribute__ ((noipa)) \
NAME (const unsigned char *a, const unsigned char *b, unsigned int n, TYPE sum) \
{ \
  for (unsigned int i = 0; i < n; ++i) \
    sum += __builtin_abs ((int) a[i] - (int) b[i]); \
  return sum; \
}

#ifndef SAD_EXTERNAL
SAD_SIGNED (sad_signed32, int)
SAD_SIGNED (sad_signed64, long long)
#else
extern int sad_signed32 (const unsigned char *, const unsigned char *,
			 unsigned int, int);
extern long long sad_signed64 (const unsigned char *, const unsigned char *,
			      unsigned int, long long);
#endif

#ifndef SAD_KERNELS_ONLY
int __attribute__ ((optimize ("O0")))
main (void)
{
  static const int seeds32[] = { 0, -1, -12345, -2147483647 - 1,
				2147483647 - 65535 };
  static const long long seeds64[] = { 0, -1, -12345,
    -9223372036854775807LL - 1, 9223372036854775807LL - 65535 };
  unsigned char a[272] __attribute__ ((aligned (8)));
  unsigned char b[272] __attribute__ ((aligned (8)));
  for (unsigned int pattern = 0; pattern < 3; ++pattern)
    {
      for (unsigned int i = 0; i < 272; ++i)
	{
	  a[i] = pattern == 0 ? 0 : i * 37 + 128;
	  b[i] = pattern == 0 ? 255 : pattern == 1 ? 0 : i * 73 + 129;
	}
      for (unsigned int n = 0; n <= 257; ++n)
	for (unsigned int offset = 0; offset < 8; ++offset)
	  {
	    int sum = 0;
	    for (unsigned int i = 0; i < n; ++i)
	      {
		int d = (int) a[offset + i] - (int) b[offset + i];
		sum += d < 0 ? -d : d;
	      }
	    for (unsigned int s = 0; s < 5; ++s)
	      if (sad_signed32 (a + offset, b + offset, n, seeds32[s])
		  != sum + seeds32[s]
		  || sad_signed64 (a + offset, b + offset, n, seeds64[s])
		     != sum + seeds64[s])
		__builtin_abort ();
	  }
    }
  return 0;
}
#endif
