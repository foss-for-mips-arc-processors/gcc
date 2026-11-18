/* { dg-do run } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-O2" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

#include "packed-sad-word-rtl-rv64.c"

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const unsigned long seeds[] = {
    0, 1, 0x7fffffff, 0x80000000, 0xfffffff0, 0xffffffff,
    0x100000000, 0x8000000000000000, ~0UL
  };
  for (unsigned int pair = 0; pair < 65536; ++pair)
    for (unsigned int lane = 0; lane < 8; ++lane)
      {
	unsigned long a = 0, b = 0, sum = 0, saved;
	for (unsigned int i = 0; i < 8; ++i)
	  {
	    unsigned int x = i == lane ? pair & 255
			     : (pair * 37 + i * 73) & 255;
	    unsigned int y = i == lane ? pair >> 8
			     : (~pair + i * 19) & 255;
	    a |= (unsigned long) x << (8 * i);
	    b |= (unsigned long) y << (8 * i);
	    sum += x < y ? y - x : x - y;
	  }
	if (word_sign_same (a, b, 0) != sum
	    || word_sign_copy (a, b, 0) != sum
	    || word_zero_same (a, b, 0) != sum
	    || word_zero_copy (a, b, 0) != sum
	    || word_live (a, b, (unsigned long) &saved) != sum
	    || saved != sum)
	  __builtin_abort ();
	for (unsigned int j = 0; j < sizeof seeds / sizeof seeds[0]; ++j)
	  {
	    unsigned long acc = seeds[j], total = acc + sum;
	    if (word_unrelated (a, b, acc)
		!= sum + (unsigned long) (long) (int) acc
		|| word_wrap_signed (a, b, acc)
		   != (unsigned long) (long) (int) total
		|| word_wrap_unsigned (a, b, acc) != (unsigned int) total)
	      __builtin_abort ();
	  }
      }
  return 0;
}
