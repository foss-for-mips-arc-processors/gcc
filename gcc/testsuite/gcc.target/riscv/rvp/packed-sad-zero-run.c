/* { dg-do run } */
/* { dg-options "-O3" } */

#include "packed-sad-zero.h"

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const uint64_t seeds[] = {
    0, 1, ~(uint64_t) 0, ~(uint64_t) 1,
    (uint64_t) 1 << 32, (uint64_t) 1 << 63
  };
  for (unsigned int pair = 0; pair < 65536; ++pair)
    for (unsigned int lane = 0; lane < 8; ++lane)
      {
	uint8x8_t a, b;
	uint8x4_t a4, b4;
	uint32_t sum4 = 0, sum8 = 0, saved4;
	uint64_t saved8;
	for (unsigned int i = 0; i < 8; ++i)
	  {
	    unsigned int x = i == lane ? pair & 255
			     : (pair * 37 + i * 73) & 255;
	    unsigned int y = i == lane ? pair >> 8
			     : (~pair + i * 19) & 255;
	    a[i] = x;
	    b[i] = y;
	    sum8 += x < y ? y - x : x - y;
	    if (i < 4)
	      {
		a4[i] = x;
		b4[i] = y;
		sum4 += x < y ? y - x : x - y;
	      }
	  }
	if (zero4 (a4, b4) != sum4 || zero8w (a, b) != sum8
	    || zero8d (a, b) != sum8
	    || shared_zero4 (a4, b4, &saved4) != sum4 || saved4 != 0
	    || shared_zero8d (a, b, &saved8) != sum8 || saved8 != 0)
	  __builtin_abort ();
	for (unsigned int j = 0; j < sizeof seeds / sizeof seeds[0]; ++j)
	  {
	    uint32_t acc4 = seeds[j];
	    uint64_t acc8 = seeds[j];
	    if (variable4 (acc4, a4, b4) != (uint32_t) (acc4 + sum4)
		|| variable8w (acc4, a, b) != (uint32_t) (acc4 + sum8)
		|| variable8d (acc8, a, b) != acc8 + sum8)
	      __builtin_abort ();
	  }
      }
  return 0;
}
