/* { dg-do run } */
/* { dg-options "-O3" } */

#ifndef SAD_EXTERNAL
#include "autovec-sad-wide.h"
#else
typedef unsigned int sad_u32;
typedef unsigned long long sad_u64;
#define DECL(NAME, INPUT, SUM) \
extern SUM NAME (const INPUT *, const INPUT *, unsigned int); \
extern SUM NAME##_aligned (const INPUT *, const INPUT *, unsigned int); \
extern SUM NAME##_seed (const INPUT *, const INPUT *, unsigned int, SUM); \
extern SUM NAME##_fixed (const INPUT *, const INPUT *); \
extern void NAME##_pair (const INPUT *, const INPUT *, unsigned int, SUM *, SUM, SUM); \
extern SUM NAME##_chain (const INPUT *, const INPUT *, unsigned int, SUM);
DECL (u8_32, unsigned char, sad_u32)
DECL (u8_64, unsigned char, sad_u64)
DECL (i8_32, signed char, sad_u32)
DECL (i8_64, signed char, sad_u64)
DECL (u16_32, unsigned short, sad_u32)
DECL (u16_64, unsigned short, sad_u64)
DECL (i16_32, short, sad_u32)
DECL (i16_64, short, sad_u64)
#endif

#define CHECK(NAME, TYPE) \
static void __attribute__ ((noipa, optimize ("O0"))) \
check_##NAME (const TYPE *a, const TYPE *b, unsigned int n, sad_u64 seed) \
{ \
  sad_u64 sum = 0, chain = 0, even = 0, odd = 0; \
  for (unsigned int i = 0; i < n; ++i) \
    { \
      int d = (int) a[i] - (int) b[i]; \
      int e = (int) a[2 * i] - (int) b[2 * i]; \
      int o = (int) a[2 * i + 1] - (int) b[2 * i + 1]; \
      sum += d < 0 ? -d : d; \
      chain += (unsigned char) a[i]; \
      even += e < 0 ? -e : e; \
      odd += o < 0 ? -o : o; \
    } \
  if (NAME##_32 (a, b, n) != (sad_u32) sum || NAME##_64 (a, b, n) != sum \
      || NAME##_32_seed (a, b, n, seed) != (sad_u32) (sum + seed) \
      || NAME##_64_seed (a, b, n, seed) != sum + seed \
      || NAME##_32_chain (a, b, n, seed) != (sad_u32) (sum + chain + seed) \
      || NAME##_64_chain (a, b, n, seed) != sum + chain + seed) \
    __builtin_abort (); \
  sad_u32 p32[4] = { 23, 42, 55, 87 }; \
  sad_u64 p64[4] = { 23, 42, 55, 87 }; \
  NAME##_32_pair (a, b, n, p32 + 1, seed, ~seed); \
  NAME##_64_pair (a, b, n, p64 + 1, seed, ~seed); \
  if (p32[0] != 23 || p32[3] != 87 || p64[0] != 23 || p64[3] != 87 \
      || p32[1] != (sad_u32) (even + seed) \
      || p32[2] != (sad_u32) (odd + ~seed) \
      || p64[1] != even + seed || p64[2] != odd + ~seed) \
    __builtin_abort (); \
  if (!(((unsigned long) a | (unsigned long) b) & 7) \
      && (NAME##_32_aligned (a, b, n) != sum \
	  || NAME##_64_aligned (a, b, n) != sum)) \
    __builtin_abort (); \
  if (n == 16 \
      && (NAME##_32_fixed (a, b) != sum || NAME##_64_fixed (a, b) != sum)) \
    __builtin_abort (); \
}

CHECK (u8, unsigned char)
CHECK (i8, signed char)
CHECK (u16, unsigned short)
CHECK (i16, short)

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const unsigned int lengths[] = {
    0, 1, 2, 3, 4, 5, 7, 8, 9, 15, 16, 17, 31, 32, 33,
    63, 64, 65, 127, 128, 129, 255, 256, 257
  };
  static const sad_u64 seeds[] = { 0, 0xfffffff0ULL, ~15ULL };
  unsigned char ua[528] __attribute__ ((aligned (16)));
  unsigned char ub[528] __attribute__ ((aligned (16)));
  signed char sa[528] __attribute__ ((aligned (16)));
  signed char sb[528] __attribute__ ((aligned (16)));
  unsigned short uha[528] __attribute__ ((aligned (16)));
  unsigned short uhb[528] __attribute__ ((aligned (16)));
  short sha[528] __attribute__ ((aligned (16)));
  short shb[528] __attribute__ ((aligned (16)));
  for (unsigned int pattern = 0; pattern < 4; ++pattern)
    {
      for (unsigned int i = 0; i < 528; ++i)
	{
	  ua[i] = pattern == 0 ? 0 : pattern == 1 ? 128 : i * 37 + 128;
	  ub[i] = pattern == 0 ? 255 : pattern == 1 ? 127 : i * 73 + 129;
	  sa[i] = (signed char) ua[i];
	  sb[i] = (signed char) ub[i];
	  uha[i] = pattern == 0 ? 0 : pattern == 1 ? 32768 : i * 65521 + 32768;
	  uhb[i] = pattern == 0 ? 65535 : pattern == 1 ? 32767 : i * 257 + 32769;
	  sha[i] = (short) uha[i];
	  shb[i] = (short) uhb[i];
	}
      for (unsigned int layout = 0; layout < 8; ++layout)
	for (unsigned int k = 0; k < sizeof (lengths) / sizeof (*lengths); ++k)
	  for (unsigned int s = 0; s < sizeof (seeds) / sizeof (*seeds); ++s)
	    {
	      unsigned int y = (7 * layout) % 8;
	      check_u8 (ua + layout, ub + y, lengths[k], seeds[s]);
	      check_i8 (sa + layout, sb + y, lengths[k], seeds[s]);
	      check_u16 (uha + layout, uhb + y, lengths[k], seeds[s]);
	      check_i16 (sha + layout, shb + y, lengths[k], seeds[s]);
	    }
    }

  /* Cover all byte pairs and every halfword value in packed batches.  */
  for (unsigned int batch = 0; batch < 256; ++batch)
    {
      for (unsigned int i = 0; i < 512; ++i)
	{
	  ua[i] = batch;
	  ub[i] = i & 255;
	  sa[i] = (signed char) ua[i];
	  sb[i] = (signed char) ub[i];
	  uha[i] = (batch << 8) | (i & 255);
	  uhb[i] = (i & 1) ? 65535 : 0;
	  sha[i] = (short) uha[i];
	  shb[i] = (i & 1) ? 32767 : -32768;
	}
      check_u8 (ua, ub, 256, ~15ULL);
      check_i8 (sa, sb, 256, ~15ULL);
      check_u16 (uha, uhb, 256, ~15ULL);
      check_i16 (sha, shb, 256, ~15ULL);
    }
  return 0;
}
