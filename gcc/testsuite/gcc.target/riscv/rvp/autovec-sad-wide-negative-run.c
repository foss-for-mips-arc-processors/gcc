/* { dg-do run } */
/* { dg-options "-O3" } */

#ifndef SAD_EXTERNAL
#include "autovec-sad-wide-negative.h"
#else
extern unsigned long long narrow_u8 (const unsigned char *,
				     const unsigned char *, unsigned int);
extern unsigned long long narrow_i8 (const signed char *,
				     const signed char *, unsigned int);
extern unsigned long long narrow_u16 (const unsigned short *,
				      const unsigned short *, unsigned int);
extern unsigned long long narrow_i16 (const short *, const short *,
				      unsigned int);
#endif

#define CHECK(NAME, INPUT, NARROW) \
static void __attribute__ ((noipa, optimize ("O0"))) \
check_##NAME (void) \
{ \
  INPUT a[272] __attribute__ ((aligned (8))); \
  INPUT b[272] __attribute__ ((aligned (8))); \
  for (unsigned int pattern = 0; pattern < 4; ++pattern) \
    { \
      for (unsigned int i = 0; i < 272; ++i) \
	{ \
	  a[i] = pattern == 0 ? 0 : pattern == 1 ? 32768 \
	    : pattern == 2 ? i * 65521 + 128 : i * 32749 + 32768; \
	  b[i] = pattern == 0 ? 65535 : pattern == 1 ? 32767 \
	    : pattern == 2 ? i * 257 + 127 : i * 16381 + 65535; \
	} \
      for (unsigned int n = 0; n <= 257; ++n) \
	for (unsigned int offset = 0; offset < 8; ++offset) \
	  { \
	    unsigned long long sum = 0; \
	    for (unsigned int i = 0; i < n; ++i) \
	      { \
		NARROW diff = (NARROW) ((int) a[i + offset] - (int) b[i + offset]); \
		sum += diff < 0 ? -(int) diff : (int) diff; \
	      } \
	    if (NAME (a + offset, b + offset, n) != sum) \
	      __builtin_abort (); \
	  } \
    } \
}

CHECK (narrow_u8, unsigned char, signed char)
CHECK (narrow_i8, signed char, signed char)
CHECK (narrow_u16, unsigned short, short)
CHECK (narrow_i16, short, short)

int
main (void)
{
  check_narrow_u8 ();
  check_narrow_i8 ();
  check_narrow_u16 ();
  check_narrow_i16 ();
  return 0;
}
