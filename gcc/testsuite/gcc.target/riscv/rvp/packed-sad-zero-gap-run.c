/* { dg-do run } */
/* { dg-options "-O2" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

#if __riscv_xlen == 32
#include "packed-sad-zero-gap-rv32.c"
#else
#include "packed-sad-zero-gap-rv64.c"
#endif

int __attribute__ ((optimize ("O0")))
main (void)
{
  for (unsigned int pair = 0; pair < 65536; ++pair)
    for (unsigned int lane = 0; lane < sizeof (unsigned long); ++lane)
      {
	unsigned long a = 0, b = 0, sum = 0;
	unsigned long p = ~15UL, q = 37, saved = ~0UL;
	for (unsigned int i = 0; i < sizeof (unsigned long); ++i)
	  {
	    unsigned int x = i == lane ? pair & 255
			     : (pair * 37 + i * 73) & 255;
	    unsigned int y = i == lane ? pair >> 8
			     : (~pair + i * 19) & 255;
	    a |= (unsigned long) x << (8 * i);
	    b |= (unsigned long) y << (8 * i);
	    sum += x < y ? y - x : x - y;
	  }
	if (gap_one (a, b, &p) != sum + p
	    || gap_two (a, b, &p, &q) != sum + p + q
	    || gap_shared (a, b, &saved) != sum || saved != 0
	    || gap_overwrite (a, b, p) != sum + p
	    || gap_barrier (a, b) != sum
	    || gap_merge (a, b, 0, p) != sum
	    || gap_merge (a, b, 1, p) != sum + p
	    || gap_call (a, b) != sum)
	  __builtin_abort ();
      }
  return 0;
}
