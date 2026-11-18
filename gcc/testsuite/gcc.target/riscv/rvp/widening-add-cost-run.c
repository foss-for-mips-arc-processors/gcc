/* { dg-do run } */
/* { dg-options "-O3" } */

#include "widening-add-cost.h"

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
	  s64 sa = (int) a, sb = (int) b;
	  if (acc_unsigned (a, b, acc) != acc + (u64) a + b
	      || acc_signed (a, b, acc) != acc + (u64) sa + (u64) sb
	      || acc_one_unsigned (a, acc) != acc + (u64) a
	      || acc_one_signed (a, acc) != acc + (u64) sa
	      || add_unsigned (a, b) != (u64) a + b
	      || add_signed (a, b) != sa + sb)
	    __builtin_abort ();
	}
  return 0;
}
