/* { dg-do run } */
/* { dg-options "-O3" } */

typedef unsigned long long u64;

u64 __attribute__ ((noipa))
positive_first (int a, unsigned int b, u64 acc)
{
  return acc + (long long) (a & 0x7fffffff) + b;
}

u64 __attribute__ ((noipa))
positive_last (unsigned int a, int b, u64 acc)
{
  return acc + a + (long long) (b & 0x7fffffff);
}

u64 __attribute__ ((noipa))
signed_first (int a, unsigned int b, u64 acc)
{
  return acc + (long long) a + b;
}

u64 __attribute__ ((noipa))
signed_last (unsigned int a, int b, u64 acc)
{
  return acc + a + (long long) b;
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const unsigned int values[] = {
    0, 1, 255, 65535, 0x7fffffff, 0x80000000, 0xfffffffe, 0xffffffff
  };
  static const u64 seeds[] = {
    0, 1, 0xffffffffULL, 0x100000000ULL, 0x7fffffffffffffffULL, ~0ULL
  };
  for (unsigned int i = 0; i < sizeof (values) / sizeof (*values); ++i)
    for (unsigned int j = 0; j < sizeof (values) / sizeof (*values); ++j)
      for (unsigned int k = 0; k < sizeof (seeds) / sizeof (*seeds); ++k)
	{
	  unsigned int a = values[i], b = values[j];
	  u64 acc = seeds[k];
	  if (positive_first (a, b, acc) != acc + (u64) (a & 0x7fffffff) + b
	      || positive_last (a, b, acc) != acc + a + (u64) (b & 0x7fffffff)
	      || signed_first (a, b, acc) != acc + (u64) (long long) (int) a + b
	      || signed_last (a, b, acc) != acc + a + (u64) (long long) (int) b)
	    __builtin_abort ();
	}
  return 0;
}
