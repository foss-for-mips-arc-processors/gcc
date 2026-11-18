/* { dg-do run } */
/* { dg-options "-O3 -fwrapv" } */
/* { dg-require-effective-target vect_int } */

/* Overflow-free floor averages must preserve signed rounding and lane
   boundaries.  Ceil averages, a different shift and an unrelated operand
   are not interchangeable with floor averages.  */

#include <stdint-gcc.h>
#if !defined (TEST_FUNCTIONS_ONLY) && !defined (TEST_DRIVER_ONLY)
#include "tree-vect.h"
#endif

#define TYPES(M) \
  M (int8_t, 4, s8x4) M (uint8_t, 4, u8x4) \
  M (int16_t, 4, s16x2) M (uint16_t, 4, u16x2) \
  M (int8_t, 8, s8x8) M (uint8_t, 8, u8x8) \
  M (int16_t, 8, s16x4) M (uint16_t, 8, u16x4) \
  M (int32_t, 8, s32x2) M (uint32_t, 8, u32x2)

#define DECL(T, SIZE, NAME) \
  typedef T NAME __attribute__ ((vector_size (SIZE))); \
  void test_##NAME (NAME *, NAME, NAME, NAME);
TYPES (DECL)

#ifndef TEST_DRIVER_ONLY
#define TEST(T, SIZE, NAME) \
  void __attribute__ ((noipa)) \
  test_##NAME (NAME *r, NAME a, NAME b, NAME c) \
  { \
    r[0] = (a & b) + ((a ^ b) >> 1); \
    r[1] = (a >> 1) + (b >> 1) + ((a & b) & 1); \
    r[2] = ((b ^ a) >> 1) + (a & b); \
    r[3] = (a | b) - ((a ^ b) >> 1); \
    r[4] = (a & b) + ((a ^ b) >> 2); \
    r[5] = (a & b) + ((a ^ c) >> 1); \
    r[6] = a ^ b; \
    r[7] = a & b; \
    r[8] = (a >> 1) + (b >> 1) + ((a & c) & 1); \
    r[9] = (a >> 1) + (b >> 1) + ((a | b) & 1); \
    r[10] = (a >> 1) + (b >> 1) + ((a & b) & 2); \
  }
TYPES (TEST)
#endif

#ifndef TEST_FUNCTIONS_ONLY
static int64_t __attribute__ ((noipa))
floor_div (int64_t x, unsigned d)
{
  if (d == 2)
    return x / 2 - (x < 0 && x % 2 != 0);
  return x / 4 - (x < 0 && x % 4 != 0);
}

/* Keep unrelated-operand arithmetic defined even if its narrow result
   wraps.  The vector kernels below are compiled with -fwrapv by the test.  */
#define CHECK(T, SIZE, NAME) \
  static void check_##NAME (uint32_t x, uint32_t y) \
  { \
    NAME a, b, c, r[11]; \
    for (unsigned i = 0; i < SIZE / sizeof (T); ++i) \
      { a[i] = x + 17u * i; b[i] = y - 29u * i; c[i] = x ^ y ^ i; } \
    test_##NAME (r, a, b, c); \
    _Pragma ("GCC novector") \
    for (unsigned i = 0; i < SIZE / sizeof (T); ++i) \
      { \
	int64_t av = a[i], bv = b[i], cv = c[i]; \
	T want[] = { floor_div (av + bv, 2), floor_div (av + bv, 2), \
	  floor_div (av + bv, 2), floor_div (av + bv + 1, 2), \
	  (av & bv) + floor_div (av ^ bv, 4), \
	  (av & bv) + floor_div (av ^ cv, 2), av ^ bv, av & bv, \
	  floor_div (av, 2) + floor_div (bv, 2) + ((av & cv) & 1), \
	  floor_div (av + bv + 1, 2), \
	  floor_div (av, 2) + floor_div (bv, 2) + ((av & bv) & 2) }; \
	for (unsigned k = 0; k < 11; ++k) \
	  if (r[k][i] != want[k]) __builtin_abort (); \
      } \
  }
TYPES (CHECK)

int
main (void)
{
#ifndef TEST_DRIVER_ONLY
  check_vect ();
#endif
  static const uint32_t edge[] = { 0, 1, 127, 128, 255, 32767, 32768,
    65535, 0x7fffffff, 0x80000000, 0xffffffff, 0xaaaaaaaa, 0x55555555 };
  for (unsigned x = 0; x < sizeof edge / sizeof edge[0]; ++x)
    for (unsigned y = 0; y < sizeof edge / sizeof edge[0]; ++y)
      {
#define CALL(T, SIZE, NAME) check_##NAME (edge[x], edge[y]);
	TYPES (CALL)
      }
  uint32_t state = 0x639bec51;
  for (unsigned i = 0; i < 65536; ++i)
    {
      check_s8x4 (i >> 8, i & 255);
      check_u8x4 (i >> 8, i & 255);
      check_s8x8 (i >> 8, i & 255);
      check_u8x8 (i >> 8, i & 255);
      state = state * 1664525u + 1013904223u;
      check_s16x2 (i, state);
      check_u16x2 (i, state);
      check_s16x4 (i, state);
      check_u16x4 (i, state);
      check_s32x2 (state, state ^ 0x736bd713);
      check_u32x2 (state, state ^ 0x736bd713);
    }
  return 0;
}
#endif
