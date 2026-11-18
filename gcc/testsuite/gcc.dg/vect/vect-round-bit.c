/* { dg-do run } */
/* { dg-options "-O3" } */
/* { dg-require-effective-target vect_int } */

#include <stdint-gcc.h>
#if !defined (TEST_FUNCTIONS_ONLY) && !defined (TEST_DRIVER_ONLY)
#include "tree-vect.h"
#endif

#define SHIFTS7(M, N) \
  M (N, 1) M (N, 2) M (N, 3) M (N, 4) M (N, 5) M (N, 6) M (N, 7)
#define SHIFTS15(M, N) \
  SHIFTS7 (M, N) M (N, 8) M (N, 9) M (N, 10) M (N, 11) M (N, 12) \
  M (N, 13) M (N, 14) M (N, 15)
#define SHIFTS31(M, N) \
  SHIFTS15 (M, N) M (N, 16) M (N, 17) M (N, 18) M (N, 19) M (N, 20) \
  M (N, 21) M (N, 22) M (N, 23) M (N, 24) M (N, 25) M (N, 26) \
  M (N, 27) M (N, 28) M (N, 29) M (N, 30) M (N, 31)

#define TYPES(M) \
  M (int8_t, uint8_t, 4, 8, v8x4, SHIFTS7) \
  M (int16_t, uint16_t, 4, 16, v16x2, SHIFTS15) \
  M (int8_t, uint8_t, 8, 8, v8x8, SHIFTS7) \
  M (int16_t, uint16_t, 8, 16, v16x4, SHIFTS15) \
  M (int32_t, uint32_t, 8, 32, v32x2, SHIFTS31)

#define DECL_ONE(N, K) void test_##N##_##K (u##N *, s##N, s##N);
#define DECL(S, U, SIZE, BITS, N, SHIFTS) \
  typedef S s##N __attribute__ ((vector_size (SIZE))); \
  typedef U u##N __attribute__ ((vector_size (SIZE))); \
  SHIFTS (DECL_ONE, N)
TYPES (DECL)

#ifndef TEST_DRIVER_ONLY
/* Keep signed, converted and unsigned forms, wrong-bit controls and shared
   intermediates in the same function.  The additions are overflow-free.  */
#define TEST_ONE(N, K) \
  s##N __attribute__ ((noipa)) signed_##N##_##K (s##N x) \
  { return (x >> K) + ((x >> (K - 1)) & 1); } \
  u##N __attribute__ ((noipa)) converted_##N##_##K (s##N x) \
  { return (u##N) (x >> K) + (((u##N) x >> (K - 1)) & 1); } \
  u##N __attribute__ ((noipa)) unsigned_##N##_##K (u##N x) \
  { return (x >> K) + ((x >> (K - 1)) & 1); } \
  void __attribute__ ((noipa)) \
  test_##N##_##K (u##N *r, s##N x, s##N y) \
  { \
    r[0] = (u##N) signed_##N##_##K (x); \
    r[1] = converted_##N##_##K (x); \
    r[2] = unsigned_##N##_##K ((u##N) x); \
    r[3] = (u##N) ((x >> K) + ((x >> K) & 1)); \
    r[4] = (u##N) ((x >> K) + ((x >> (K - 1)) & 2)); \
    r[5] = (u##N) ((x >> K) + ((y >> (K - 1)) & 1)); \
    r[6] = (u##N) x >> (K - 1); \
    r[7] = (u##N) (x >> K); \
  }
#define TEST(S, U, SIZE, BITS, N, SHIFTS) SHIFTS (TEST_ONE, N)
TYPES (TEST)
#endif

#ifndef TEST_FUNCTIONS_ONLY
#define ENTRY(N, K) test_##N##_##K,
#define CHECK(S, U, SIZE, BITS, N, SHIFTS) \
  static void (*const functions_##N[]) (u##N *, s##N, s##N) \
    = { SHIFTS (ENTRY, N) }; \
  static void check_##N (uint32_t value, unsigned int k) \
  { \
    s##N x, y; \
    u##N r[8]; \
    for (unsigned int i = 0; i < SIZE / sizeof (S); ++i) \
      { x[i] = value + 17u * i; y[i] = (value ^ 0x539ab16du) - 29u * i; } \
    functions_##N[k - 1] (r, x, y); \
    _Pragma ("GCC novector") \
    for (unsigned int i = 0; i < SIZE / sizeof (S); ++i) \
      { \
	int64_t a = x[i], b = y[i]; \
	int64_t bias = INT64_C (1) << (k - 1); \
	U want[] = { (a + bias) >> k, (a + bias) >> k, \
	  ((uint64_t) (U) a + bias) >> k, (a >> k) + ((a >> k) & 1), \
	  (a >> k) + ((a >> (k - 1)) & 2), \
	  (a >> k) + ((b >> (k - 1)) & 1), (uint64_t) (U) a >> (k - 1), \
	  a >> k }; \
	for (unsigned int j = 0; j < 8; ++j) \
	  if (r[j][i] != want[j]) __builtin_abort (); \
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
  for (unsigned int k = 1; k < 32; ++k)
    {
      for (unsigned int i = 0; i < sizeof edge / sizeof edge[0]; ++i)
	{
	  if (k < 8)
	    { check_v8x4 (edge[i], k); check_v8x8 (edge[i], k); }
	  if (k < 16)
	    { check_v16x2 (edge[i], k); check_v16x4 (edge[i], k); }
	  check_v32x2 (edge[i], k);
	}
      uint32_t state = 0x639bec51;
      for (unsigned int i = 0; i < 65536; ++i)
	{
	  if (k < 8 && i < 256)
	    { check_v8x4 (i, k); check_v8x8 (i, k); }
	  if (k < 16)
	    { check_v16x2 (i, k); check_v16x4 (i, k); }
	  state = state * 1664525u + 1013904223u;
	  check_v32x2 (state, k);
	}
    }
  return 0;
}
#endif
