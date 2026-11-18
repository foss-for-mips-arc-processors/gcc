/* { dg-do run } */
/* { dg-options "-O3" } */
/* { dg-require-effective-target vect_int } */

/* An average with a wide intermediate must also be recognized at the
   final truncation, without requiring a vector of the intermediate type.  */

#include <stdint-gcc.h>
#if !defined (TEST_FUNCTIONS_ONLY) && !defined (TEST_DRIVER_ONLY)
#include "tree-vect.h"
#endif

#define TYPES(M) \
  M (int8_t, int64_t, s8) \
  M (uint8_t, uint64_t, u8) \
  M (int16_t, int64_t, s16) \
  M (uint16_t, uint64_t, u16) \
  M (int32_t, int64_t, s32) \
  M (uint32_t, uint64_t, u32)

#define DECL(T, W, NAME) \
  void NAME (T *, const T *, const T *, unsigned, unsigned);
TYPES (DECL)
void shared (uint8_t *, uint64_t *, const uint8_t *, const uint8_t *, unsigned);
void wrapping (uint8_t *, const uint8_t *, const uint8_t *, unsigned);
void shift_two (uint8_t *, const uint8_t *, const uint8_t *, unsigned);
void truth (_Bool *, const uint8_t *, const uint8_t *, unsigned);
void signed_to_unsigned (uint8_t *, const int8_t *, const int8_t *, unsigned);
void unsigned_to_signed (int8_t *, const uint8_t *, const uint8_t *, unsigned);

#ifndef TEST_DRIVER_ONLY
#define TEST(T, W, NAME) \
  void __attribute__ ((noipa)) \
  NAME (T *restrict d, const T *restrict a, const T *restrict b, \
	unsigned n, unsigned kind) \
  { \
    if (kind == 0) \
      for (unsigned i = 0; i < n; ++i) \
	d[i] = ((W) a[i] + b[i]) >> 1; \
    else if (kind == 1) \
      for (unsigned i = 0; i < n; ++i) \
	d[i] = ((W) a[i] - b[i]) >> 1; \
    else \
      for (unsigned i = 0; i < n; ++i) \
	d[i] = ((W) a[i] + b[i] + 1) >> 1; \
  }
TYPES (TEST)

void __attribute__ ((noipa))
shared (uint8_t *restrict d, uint64_t *restrict wide,
	const uint8_t *restrict a, const uint8_t *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    {
      uint64_t v = ((uint64_t) a[i] - b[i]) >> 1;
      d[i] = v;
      wide[i] = v;
    }
}

void __attribute__ ((noipa))
wrapping (uint8_t *restrict d, const uint8_t *restrict a,
	  const uint8_t *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = (uint8_t) (a[i] + b[i]) >> 1;
}

void __attribute__ ((noipa))
shift_two (uint8_t *restrict d, const uint8_t *restrict a,
	   const uint8_t *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = ((uint64_t) a[i] + b[i]) >> 2;
}

void __attribute__ ((noipa))
truth (_Bool *restrict d, const uint8_t *restrict a,
       const uint8_t *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = ((uint64_t) a[i] + b[i]) >> 1;
}

void __attribute__ ((noipa))
signed_to_unsigned (uint8_t *restrict d, const int8_t *restrict a,
		    const int8_t *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = ((int64_t) a[i] + b[i]) >> 1;
}

void __attribute__ ((noipa))
unsigned_to_signed (int8_t *restrict d, const uint8_t *restrict a,
		    const uint8_t *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = ((uint64_t) a[i] - b[i]) >> 1;
}
#endif

#ifndef TEST_FUNCTIONS_ONLY
/* Division plus a negative remainder correction is an independent
   reference for floor rounding; all input sums fit int64_t.  */
static int64_t __attribute__ ((noipa))
reference (int64_t a, int64_t b, unsigned kind)
{
  int64_t v = kind == 1 ? a - b : a + b + (kind == 2);
  return v / 2 - (v < 0 && v % 2 != 0);
}

#define CHECK(T, W, NAME) \
  static void check_##NAME (unsigned seed, unsigned n, unsigned offset) \
  { \
    T a[264] __attribute__ ((aligned (8))); \
    T b[264] __attribute__ ((aligned (8))); \
    T d[264] __attribute__ ((aligned (8))); \
    static const uint32_t edge[] = { \
      0, 1, 127, 128, 255, 32767, 32768, 65535, \
      0x7fffffff, 0x80000000, 0xffffffff, 0xaaaaaaaa \
    }; \
    for (unsigned i = 0; i < 264; ++i) \
      { \
	a[i] = seed < 256 ? seed : edge[(i + seed) % 12]; \
	b[i] = seed < 256 ? i : edge[(i * 7 + seed / 12) % 12]; \
      } \
    for (unsigned kind = 0; kind < 3; ++kind) \
      { \
	for (unsigned i = 0; i < 264; ++i) d[i] = 0x5a; \
	NAME (d + 4 + offset, a + offset, b + offset, n, kind); \
	_Pragma ("GCC novector") \
	for (unsigned i = 0; i < 264; ++i) \
	  { \
	    T want = i < 4 + offset || i >= 4 + offset + n ? 0x5a \
	      : (T) reference (a[i - 4], b[i - 4], kind); \
	    if (d[i] != want) __builtin_abort (); \
	  } \
      } \
  }
TYPES (CHECK)

int
main (void)
{
#ifndef TEST_DRIVER_ONLY
  check_vect ();
#endif
  for (unsigned seed = 0; seed < 400; ++seed)
    {
      unsigned n = seed < 256 ? 256 : (seed - 256) % 33;
      unsigned offset = seed & 3;
#define CALL(T, W, NAME) check_##NAME (seed, n, offset);
      TYPES (CALL)
    }
  uint8_t a[257], b[257], d[257];
  int8_t sa[257], sb[257], sd[257];
  uint64_t wide[257];
  _Bool bd[257];
  for (unsigned seed = 0; seed < 256; ++seed)
    {
      for (unsigned i = 0; i < 257; ++i)
	{ a[i] = seed; b[i] = i; sa[i] = a[i]; sb[i] = b[i]; }
      shared (d, wide, a, b, 257);
#pragma GCC novector
      for (unsigned i = 0; i < 257; ++i)
	{
	  uint64_t want = ((uint64_t) a[i] - b[i]) >> 1;
	  if (wide[i] != want || d[i] != (uint8_t) want) __builtin_abort ();
	}
      wrapping (d, a, b, 257);
#pragma GCC novector
      for (unsigned i = 0; i < 257; ++i)
	if (d[i] != ((uint8_t) (a[i] + b[i]) >> 1)) __builtin_abort ();
      shift_two (d, a, b, 257);
#pragma GCC novector
      for (unsigned i = 0; i < 257; ++i)
	if (d[i] != (a[i] + b[i]) / 4) __builtin_abort ();
      truth (bd, a, b, 257);
#pragma GCC novector
      for (unsigned i = 0; i < 257; ++i)
	if (bd[i] != ((a[i] + b[i]) / 2 != 0)) __builtin_abort ();
      signed_to_unsigned (d, sa, sb, 257);
#pragma GCC novector
      for (unsigned i = 0; i < 257; ++i)
	if (d[i] != (uint8_t) reference (sa[i], sb[i], 0)) __builtin_abort ();
      unsigned_to_signed (sd, a, b, 257);
#pragma GCC novector
      for (unsigned i = 0; i < 257; ++i)
	if (sd[i] != (int8_t) reference (a[i], b[i], 1)) __builtin_abort ();
    }
  return 0;
}
#endif
