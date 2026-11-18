/* { dg-do run } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-O2" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

#include "packed-sad-word-gap-rv64.c"

static unsigned long __attribute__ ((noipa))
check_call (unsigned long a, unsigned long b)
{
  register unsigned long saved __asm__ ("s1") = 0xdeadbeef87654321UL;
  __asm__ volatile ("" : "+r" (saved));
  unsigned long result = sad_gap_call (a, b);
  __asm__ volatile ("" : "+r" (saved));
  if (saved != 0xdeadbeef87654321UL)
    __builtin_abort ();
  return result;
}

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
	unsigned long a = 0, b = 0, sum = 0, saved, values[16];
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
	if (sad_gap_sign (a, b, (unsigned long) &saved, 0) != sum
	    || saved != sum
	    || sad_gap_zero (a, b, (unsigned long) &saved, 0) != sum
	    || saved != sum
	    || sad_gap_copy (a, b, (unsigned long) &saved, 0) != sum
	    || saved != sum
	    || sad_gap_load (a, b, (unsigned long) &saved, 0) != 2 * sum
	    || sad_gap_barrier (a, b, 0, 0) != sum
	    || check_call (a, b) != sum)
	  __builtin_abort ();
	for (unsigned int i = 0; i < 16; ++i)
	  values[i] = ~0UL;
	if (sad_gap_limit (a, b, (unsigned long) values, 0) != sum)
	  __builtin_abort ();
	for (unsigned int i = 0; i < 16; ++i)
	  if (values[i] != (i < 15 ? sum : ~0UL))
	    __builtin_abort ();
	if (sad_gap_far (a, b, (unsigned long) values, 0) != sum)
	  __builtin_abort ();
	for (unsigned int i = 0; i < 16; ++i)
	  if (values[i] != sum)
	    __builtin_abort ();
	for (unsigned int j = 0; j < sizeof seeds / sizeof seeds[0]; ++j)
	  {
	    unsigned long acc = seeds[j];
	    unsigned long extended = (unsigned long) (long) (int) acc;
	    if (sad_gap_overwrite (a, b, acc, (unsigned long) &saved)
		!= extended || saved != sum
		|| sad_gap_merge (a, b, 0, acc) != sum
		|| sad_gap_merge (a, b, 1, acc) != extended)
	      __builtin_abort ();
	  }
      }
  return 0;
}
