/* { dg-do run } */
/* { dg-options "-O3" } */

#ifndef SAD_EXTERNAL
#include "autovec-sad.h"
#else
typedef unsigned char sad_u8;
typedef unsigned int sad_u32;
typedef unsigned long long sad_u64;
#define DECLARE(BITS, TYPE) \
extern TYPE sad##BITS (const sad_u8 *, const sad_u8 *, unsigned int); \
extern TYPE sad##BITS##_aligned (const sad_u8 *, const sad_u8 *, unsigned int); \
extern TYPE sad##BITS##_seed (const sad_u8 *, const sad_u8 *, unsigned int, TYPE); \
extern TYPE sad##BITS##_fixed (const sad_u8 *, const sad_u8 *); \
extern void sad##BITS##_pair (const sad_u8 *, const sad_u8 *, unsigned int, \
			    TYPE *, TYPE, TYPE); \
extern TYPE sad##BITS##_chain (const sad_u8 *, const sad_u8 *, unsigned int, TYPE);
DECLARE (32, sad_u32)
DECLARE (64, sad_u64)
#endif

static void __attribute__ ((noipa, optimize ("O0")))
check (const sad_u8 *a, const sad_u8 *b, unsigned int n, sad_u64 seed,
       int aligned)
{
  sad_u64 sum = 0, chain = 0, even = 0, odd = 0;
  for (unsigned int i = 0; i < n; ++i)
    {
      int d = (int) a[i] - (int) b[i];
      int e = (int) a[2 * i] - (int) b[2 * i];
      int o = (int) a[2 * i + 1] - (int) b[2 * i + 1];
      sum += d < 0 ? -d : d;
      chain += a[i];
      even += e < 0 ? -e : e;
      odd += o < 0 ? -o : o;
    }
  if (sad32 (a, b, n) != (sad_u32) sum || sad64 (a, b, n) != sum
      || sad32_seed (a, b, n, seed) != (sad_u32) (sum + seed)
      || sad64_seed (a, b, n, seed) != sum + seed
      || sad32_chain (a, b, n, seed) != (sad_u32) (sum + chain + seed)
      || sad64_chain (a, b, n, seed) != sum + chain + seed)
    __builtin_abort ();
  sad_u32 p32[4] = { 23, 42, 55, 87 };
  sad_u64 p64[4] = { 23, 42, 55, 87 };
  sad32_pair (a, b, n, p32 + 1, seed, ~seed);
  sad64_pair (a, b, n, p64 + 1, seed, ~seed);
  if (p32[0] != 23 || p32[3] != 87 || p64[0] != 23 || p64[3] != 87
      || p32[1] != (sad_u32) (even + seed)
      || p32[2] != (sad_u32) (odd + ~seed)
      || p64[1] != even + seed || p64[2] != odd + ~seed)
    __builtin_abort ();
  if (aligned
      && (sad32_aligned (a, b, n) != sum || sad64_aligned (a, b, n) != sum))
    __builtin_abort ();
  if (n == 16
      && (sad32_fixed (a, b) != sum || sad64_fixed (a, b) != sum))
    __builtin_abort ();
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const unsigned int lengths[] = {
    0, 1, 2, 3, 4, 5, 7, 8, 9, 15, 16, 17, 31, 32, 33,
    63, 64, 65, 127, 128, 129, 255, 256, 257
  };
  static const sad_u64 seeds[] = { 0, 0xfffffff0ULL, ~15ULL };
  sad_u8 a[528] __attribute__ ((aligned (16)));
  sad_u8 b[528] __attribute__ ((aligned (16)));
  for (unsigned int pattern = 0; pattern < 3; ++pattern)
    {
      for (unsigned int i = 0; i < 528; ++i)
	{
	  a[i] = pattern == 0 ? 0 : pattern == 1 ? (i & 1 ? 255 : 0)
					       : i * 37 + 128;
	  b[i] = pattern == 0 ? 255 : pattern == 1 ? (i & 1 ? 0 : 255)
						 : i * 73 + 129;
	}
      for (unsigned int layout = 0; layout < 8; ++layout)
	for (unsigned int k = 0; k < sizeof (lengths) / sizeof (*lengths); ++k)
	  for (unsigned int s = 0; s < sizeof (seeds) / sizeof (*seeds); ++s)
	    check (a + layout, b + (7 * layout) % 8, lengths[k], seeds[s],
		   layout == 0);
      for (unsigned int x = 0; x < 8; ++x)
	for (unsigned int y = 0; y < 8; ++y)
	  check (a + x, b + y, 17, ~15ULL, x == 0 && y == 0);
    }
  return 0;
}
