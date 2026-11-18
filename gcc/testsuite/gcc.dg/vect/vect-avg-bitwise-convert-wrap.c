/* { dg-do run } */
/* { dg-options "-O3 -fwrapv" } */
/* { dg-require-effective-target vect_int } */

/* Also check the reverse conversion: unsigned shifts followed by wrapping
   signed addition.  The selected average must remain unsigned.  */

#include <stdint-gcc.h>
#if !defined (TEST_FUNCTIONS_ONLY) && !defined (TEST_DRIVER_ONLY)
#include "tree-vect.h"
#endif

#define TYPES(M) \
  M (int8_t, uint8_t, v8) \
  M (int16_t, uint16_t, v16) \
  M (int32_t, uint32_t, v32)

#define DECL(S, U, NAME) \
  typedef S s##NAME __attribute__ ((vector_size (8))); \
  typedef U u##NAME __attribute__ ((vector_size (8))); \
  void test_##NAME (s##NAME *, u##NAME, u##NAME);
TYPES (DECL)

#ifndef TEST_DRIVER_ONLY
#define TEST(S, U, NAME) \
  void __attribute__ ((noipa)) \
  test_##NAME (s##NAME *r, u##NAME a, u##NAME b) \
  { \
    r[0] = (s##NAME) (a & b) + (s##NAME) ((a ^ b) >> 1); \
    r[1] = (s##NAME) (a >> 1) + (s##NAME) (b >> 1) \
	   + (s##NAME) ((a & b) & 1); \
    r[2] = (s##NAME) (b >> 1) \
	   + ((s##NAME) ((a & b) & 1) + (s##NAME) (a >> 1)); \
  }
TYPES (TEST)
#endif

#ifndef TEST_FUNCTIONS_ONLY
#define CHECK(S, U, NAME) \
  static void check_##NAME (uint32_t x, uint32_t y) \
  { \
    u##NAME a, b; \
    s##NAME r[3]; \
    for (unsigned int i = 0; i < 8 / sizeof (S); ++i) \
      { a[i] = x + 17u * i; b[i] = y - 29u * i; } \
    test_##NAME (r, a, b); \
    _Pragma ("GCC novector") \
    for (unsigned int i = 0; i < 8 / sizeof (S); ++i) \
      { \
	U want = ((uint64_t) a[i] + b[i]) / 2; \
	for (unsigned int k = 0; k < 3; ++k) \
	  if ((U) r[k][i] != want) __builtin_abort (); \
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
  for (unsigned int x = 0; x < sizeof edge / sizeof edge[0]; ++x)
    for (unsigned int y = 0; y < sizeof edge / sizeof edge[0]; ++y)
      {
#define CALL(S, U, NAME) check_##NAME (edge[x], edge[y]);
	TYPES (CALL)
      }
  uint32_t state = 0x639bec51;
  for (unsigned int i = 0; i < 65536; ++i)
    {
      check_v8 (i >> 8, i & 255);
      state = state * 1664525u + 1013904223u;
      check_v16 (i, state);
      check_v32 (state, state ^ 0x736bd713);
    }
  return 0;
}
#endif
