/* { dg-do run } */
/* { dg-options "-O2" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

#if __riscv_xlen == 32
#include "packed-sad-zero-rtl-rv32.c"
typedef float result_t;
#else
#include "packed-sad-zero-rtl-rv64.c"
typedef double result_t;
#endif

unsigned long zero_copy (unsigned long, unsigned long);
unsigned long zero_left (unsigned long, unsigned long);
unsigned long zero_right (unsigned long, unsigned long);
unsigned long zero_live (unsigned long, unsigned long, unsigned long *);
result_t zero_float (unsigned long, unsigned long);

int __attribute__ ((optimize ("O0")))
main (void)
{
  for (unsigned int pair = 0; pair < 65536; ++pair)
    for (unsigned int lane = 0; lane < sizeof (unsigned long); ++lane)
      {
	unsigned long a = 0, b = 0, sum = 0, sum_b = 0, saved;
	for (unsigned int i = 0; i < sizeof (unsigned long); ++i)
	  {
	    unsigned int x = i == lane ? pair & 255
			     : (pair * 37 + i * 73) & 255;
	    unsigned int y = i == lane ? pair >> 8
			     : (~pair + i * 19) & 255;
	    a |= (unsigned long) x << (8 * i);
	    b |= (unsigned long) y << (8 * i);
	    sum += x < y ? y - x : x - y;
	    sum_b += y;
	  }
	union { result_t f; unsigned long u; } bits;
	bits.f = zero_float (a, b);
	if (zero_copy (a, b) != sum || zero_left (a, b) != sum_b
	    || zero_right (a, b) != sum_b || bits.u != sum
	    || zero_live (a, b, &saved) != sum || saved != sum)
	  __builtin_abort ();
      }
  return 0;
}
