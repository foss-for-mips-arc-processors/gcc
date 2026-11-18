/* { dg-do run } */
/* { dg-options "-O3" } */
/* { dg-require-effective-target vect_int } */

#include <stdint-gcc.h>
#if !defined (TEST_FUNCTIONS_ONLY) && !defined (TEST_DRIVER_ONLY)
#include "tree-vect.h"
#endif

#define TYPES(M) \
  M (int8_t, uint8_t, 4, 8, v8x4) \
  M (int16_t, uint16_t, 4, 16, v16x2) \
  M (int8_t, uint8_t, 8, 8, v8x8) \
  M (int16_t, uint16_t, 8, 16, v16x4) \
  M (int32_t, uint32_t, 8, 32, v32x2)

#define DECL(S, U, SIZE, BITS, NAME) \
  typedef S s##NAME __attribute__ ((vector_size (SIZE))); \
  typedef U u##NAME __attribute__ ((vector_size (SIZE))); \
  void test_##NAME (u##NAME *, s##NAME, s##NAME, s##NAME);
TYPES (DECL)

#ifndef TEST_DRIVER_ONLY
/* The addition is unsigned, but the positive forms use signed shifts.
   Reused intermediates must retain their original values.  */
#define TEST(S, U, SIZE, BITS, NAME) \
  void __attribute__ ((noipa)) \
  test_##NAME (u##NAME *r, s##NAME a, s##NAME b, s##NAME c) \
  { \
    r[0] = (u##NAME) (a & b) + (u##NAME) ((a ^ b) >> 1); \
    r[1] = (u##NAME) (a >> 1) + (u##NAME) (b >> 1) \
	   + (u##NAME) ((a & b) & 1); \
    r[2] = (u##NAME) (b >> 1) \
	   + ((u##NAME) ((a & b) & 1) + (u##NAME) (a >> 1)); \
    r[3] = (u##NAME) (a & b) + (u##NAME) ((a ^ b) >> 2); \
    r[4] = (u##NAME) (a & b) + (u##NAME) ((a ^ c) >> 1); \
    r[5] = (u##NAME) (a ^ b); \
    r[6] = (u##NAME) (a & b); \
    r[7] = (u##NAME) (a & b) + (((u##NAME) (a ^ b)) >> 1); \
    r[8] = (u##NAME) (a >> 1) + (u##NAME) (b >> 1) \
	   + (u##NAME) ((a & b) & 2); \
    r[9] = (u##NAME) (a >> 1) + (((u##NAME) b) >> 1) \
	   + (u##NAME) ((a & b) & 1); \
  }
TYPES (TEST)

/* These reinterpretations change lane boundaries.  Their additions can
   carry between the bytes and must not become byte averages.  */
uv16x4 __attribute__ ((noipa))
pun_xor (sv8x8 a, sv8x8 b)
{
  return (uv16x4) (a & b) + (uv16x4) ((a ^ b) >> 1);
}

uv16x4 __attribute__ ((noipa))
pun_carry (sv8x8 a, sv8x8 b)
{
  return (uv16x4) (a >> 1) + (uv16x4) (b >> 1)
    + (uv16x4) ((a & b) & 1);
}
#endif

#ifndef TEST_FUNCTIONS_ONLY
uv16x4 pun_xor (sv8x8, sv8x8);
uv16x4 pun_carry (sv8x8, sv8x8);

static int64_t __attribute__ ((noipa))
floor_div (int64_t x, unsigned int d)
{
  if (d == 2)
    return x / 2 - (x < 0 && x % 2 != 0);
  return x / 4 - (x < 0 && x % 4 != 0);
}

#define CHECK(S, U, SIZE, BITS, NAME) \
  static void check_##NAME (uint32_t x, uint32_t y) \
  { \
    s##NAME a, b, c; \
    u##NAME r[10]; \
    for (unsigned int i = 0; i < SIZE / sizeof (S); ++i) \
      { a[i] = x + 17u * i; b[i] = y - 29u * i; c[i] = x ^ y ^ i; } \
    test_##NAME (r, a, b, c); \
    _Pragma ("GCC novector") \
    for (unsigned int i = 0; i < SIZE / sizeof (S); ++i) \
      { \
	int64_t av = a[i], bv = b[i], cv = c[i]; \
	U want[] = { floor_div (av + bv, 2), floor_div (av + bv, 2), \
	  floor_div (av + bv, 2), (av & bv) + floor_div (av ^ bv, 4), \
	  (av & bv) + floor_div (av ^ cv, 2), av ^ bv, av & bv, \
	  ((uint64_t) (U) av + (uint64_t) (U) bv) / 2, \
	  floor_div (av, 2) + floor_div (bv, 2) + ((av & bv) & 2), \
	  floor_div (av, 2) + (uint64_t) (U) bv / 2 + ((av & bv) & 1) }; \
	for (unsigned int k = 0; k < 10; ++k) \
	  if (r[k][i] != want[k]) __builtin_abort (); \
      } \
  }
TYPES (CHECK)

static void
check_pun (uint32_t x, uint32_t y)
{
  sv8x8 a, b;
  union { uint8_t bytes[8]; uv16x4 words; } both, shifted, ah, bh, carry;
  for (unsigned int i = 0; i < 8; ++i)
    {
      a[i] = x + 17u * i;
      b[i] = y - 29u * i;
      int av = a[i], bv = b[i];
      both.bytes[i] = av & bv;
      shifted.bytes[i] = floor_div (av ^ bv, 2);
      ah.bytes[i] = floor_div (av, 2);
      bh.bytes[i] = floor_div (bv, 2);
      carry.bytes[i] = (av & bv) & 1;
    }
  uv16x4 r0 = pun_xor (a, b), r1 = pun_carry (a, b);
  for (unsigned int i = 0; i < 4; ++i)
    {
      uint16_t w0 = (unsigned int) both.words[i] + shifted.words[i];
      uint16_t w1 = (unsigned int) ah.words[i] + bh.words[i] + carry.words[i];
      if (r0[i] != w0 || r1[i] != w1)
	__builtin_abort ();
    }
}

int
main (void)
{
#ifndef TEST_DRIVER_ONLY
  check_vect ();
#endif
  static const uint32_t edge[] = { 0, 1, 127, 128, 255, 32767, 32768,
    65535, 0x7fffffff, 0x80000000, 0xffffffff, 0xaaaaaaaa, 0x55555555 };
  for (unsigned int x = 0; x < sizeof edge / sizeof edge[0]; ++x)
    for (unsigned int y = 0; y < sizeof edge / sizeof edge[0]; ++y)
      {
#define CALL(S, U, SIZE, BITS, NAME) check_##NAME (edge[x], edge[y]);
	TYPES (CALL)
	check_pun (edge[x], edge[y]);
      }
  uint32_t state = 0x639bec51;
  for (unsigned int i = 0; i < 65536; ++i)
    {
      check_v8x4 (i >> 8, i & 255);
      check_v8x8 (i >> 8, i & 255);
      check_pun (i >> 8, i & 255);
      state = state * 1664525u + 1013904223u;
      check_v16x2 (i, state);
      check_v16x4 (i, state);
      check_v32x2 (state, state ^ 0x736bd713);
    }
  return 0;
}
#endif
