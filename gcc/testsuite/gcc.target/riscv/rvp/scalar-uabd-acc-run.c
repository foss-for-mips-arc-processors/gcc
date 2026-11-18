/* { dg-do run } */
/* { dg-options "-O3" } */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long word;
#include "scalar-uabd-acc.h"

static unsigned int __attribute__ ((optimize ("O0"), noipa))
diff (int a, int b)
{
  return a < b ? b - a : a - b;
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const word seeds[] = { 0, 1, ~0UL, ~1UL,
			       1UL << (sizeof (word) * 8 - 1),
			       (1UL << (sizeof (word) * 8 - 1)) - 1 };
  word state = 0xdeadbeefUL;
  u8 a[260] __attribute__ ((aligned (16)));
  u8 b[260] __attribute__ ((aligned (16)));
  for (unsigned int i = 0; i < 65536; ++i)
    {
      u8 x = i, y = i >> 8;
      u16 h = i, k = 65535 - i;
      unsigned int d = diff (x, y);
      state = state * 1664525 + 1013904223;
      word high_a = (state & ~255UL) | x;
      word high_b = (~state & ~255UL) | y;
      if (overlap_acc (x, y) != x + d)
	__builtin_abort ();
      for (unsigned int j = 0; j < sizeof seeds / sizeof seeds[0]; ++j)
	{
	  word sum = seeds[j], saved;
	  unsigned int kept;
	  if (byte_acc (x, y, sum) != sum + d
	      || load_acc (&x, &y, sum) != sum + d
	      || retained_acc (x, y, sum, &kept) != sum + d || kept != d
	      || high_acc (high_a, high_b, sum, &saved) != sum + d
	      || saved != (high_a ^ high_b)
	      || half_control (h, k, sum) != sum + diff (h, k)
	      || signed_control ((signed char) x, (signed char) y, sum)
		 != sum + diff ((signed char) x, (signed char) y))
	    __builtin_abort ();
	}
    }
  for (unsigned int i = 0; i < 260; ++i)
    {
      a[i] = i % 3 ? i * 37 : 0;
      b[i] = i % 5 ? i * 73 : 255;
    }
  for (unsigned int n = 0; n <= 257; ++n)
    for (unsigned int x = 0; x < 3; ++x)
      for (unsigned int y = 0; y < 3; ++y)
	for (unsigned int j = 0; j < sizeof seeds / sizeof seeds[0]; ++j)
	  {
	    word expected = seeds[j];
	    for (unsigned int i = 0; i < n; ++i)
	      expected += diff (a[i + x], b[i + y]);
	    if (loop_acc (a + x, b + y, n, seeds[j]) != expected
		|| loop_acc (a + x, a + x, n, seeds[j]) != seeds[j])
	      __builtin_abort ();
	  }
  return 0;
}
