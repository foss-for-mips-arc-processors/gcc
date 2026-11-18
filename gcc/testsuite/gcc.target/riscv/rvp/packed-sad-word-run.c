/* { dg-do run } */
/* { dg-options "-O3" } */

#include "packed-sad-word.h"

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const uint32_t seeds[] = {
    0, 1, 0x7fffffff, 0x80000000, 0xfffffff0, 0xffffffff
  };
  for (unsigned int pair = 0; pair < 65536; ++pair)
    for (unsigned int lane = 0; lane < 8; ++lane)
      {
	uint8x8_t a, b;
	uint8x4_t a4, b4;
	uint32_t sum4 = 0, sum8 = 0;
	uint64_t saved;
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
	if (sad_word4 (a4, b4) != sum4 || sad_word8 (a, b) != sum8
	    || sad_unsigned4 (a4, b4) != sum4
	    || sad_unsigned8 (a, b) != sum8
	    || sad_signed4 (a4, b4) != sum4
	    || sad_signed8 (a, b) != sum8
	    || sad_shared (a, b, &saved) != sum8 || saved != sum8
	    || sad_byte (a, b) != (uint8_t) sum8)
	  __builtin_abort ();
	for (unsigned int j = 0; j < sizeof seeds / sizeof seeds[0]; ++j)
	  {
	    uint32_t sum = seeds[j] + sum8;
	    if (sad_wrap_unsigned (seeds[j], a, b) != (uint64_t) sum
		|| sad_wrap_signed (seeds[j], a, b) != (int64_t) (int32_t) sum)
	      __builtin_abort ();
	  }
      }
  /* Check the exact bound, including all eight active lanes.  */
  uint8x8_t zero = { 0 };
  uint8x8_t ones = { 255, 255, 255, 255, 255, 255, 255, 255 };
  if (sad_word8 (zero, ones) != 2040
      || sad_signed8 (zero, ones) != 2040
      || sad_unsigned8 (zero, ones) != 2040
      || sad_byte (zero, ones) != (uint8_t) 2040)
    __builtin_abort ();
  return 0;
}
