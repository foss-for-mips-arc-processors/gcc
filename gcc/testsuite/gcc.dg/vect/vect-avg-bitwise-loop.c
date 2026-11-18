/* { dg-do run } */
/* { dg-options "-O3" } */
/* { dg-require-effective-target vect_int } */

#include <stdint-gcc.h>
#if !defined (TEST_FUNCTIONS_ONLY) && !defined (TEST_DRIVER_ONLY)
#include "tree-vect.h"
#endif

#define TYPES(M) \
  M (int8_t, uint8_t, s8) M (uint8_t, uint8_t, u8) \
  M (int16_t, uint16_t, s16) M (uint16_t, uint16_t, u16) \
  M (int32_t, uint32_t, s32) M (uint32_t, uint32_t, u32)

#define DECL(T, U, N) \
  void xor_##N (T *, const T *, const T *, unsigned); \
  void swap_##N (T *, const T *, const T *, unsigned); \
  void one_##N (T *, const T *, const T *, unsigned); \
  void other_##N (T *, const T *, const T *, unsigned); \
  void shared_##N (T *, T *, T *, const T *, const T *, unsigned);
TYPES (DECL)

#ifndef TEST_DRIVER_ONLY
#define TEST(T, U, N) \
  void __attribute__ ((noipa)) \
  xor_##N (T *restrict d, const T *restrict a, const T *restrict b, \
	   unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      d[i] = (a[i] & b[i]) + ((a[i] ^ b[i]) >> 1); \
  } \
  void __attribute__ ((noipa)) \
  swap_##N (T *restrict d, const T *restrict a, const T *restrict b, \
	    unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      d[i] = (U) ((b[i] ^ a[i]) >> 1) + (U) (a[i] & b[i]); \
  } \
  void __attribute__ ((noipa)) \
  one_##N (T *restrict d, const T *restrict a, const T *, unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      d[i] = (a[i] & 1) + ((a[i] ^ 1) >> 1); \
  } \
  void __attribute__ ((noipa)) \
  other_##N (T *restrict d, const T *restrict a, const T *restrict b, \
	     unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      d[i] = (U) (a[i] & b[i]) + (U) ((a[i] ^ (T) 0x5b) >> 1); \
  } \
  void __attribute__ ((noipa)) \
  shared_##N (T *restrict d, T *restrict q, T *restrict m, \
	      const T *restrict a, const T *restrict b, unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      { \
	T x = (a[i] ^ b[i]) >> 1, y = a[i] & b[i]; \
	q[i] = x; m[i] = y; d[i] = x + y; \
      } \
  }
TYPES (TEST)
#endif

#ifndef TEST_FUNCTIONS_ONLY
static int64_t
floor_half (int64_t x)
{
  return x / 2 - (x < 0 && x % 2 != 0);
}

#define CHECK(T, U, N) \
  static T a_##N[288] __attribute__ ((aligned (64))); \
  static T b_##N[288] __attribute__ ((aligned (64))); \
  static T d_##N[288] __attribute__ ((aligned (64))); \
  static T q_##N[288], m_##N[288]; \
  static void check_##N (void) \
  { \
    void (*const f[]) (T *, const T *, const T *, unsigned) \
      = { xor_##N, swap_##N, one_##N, other_##N }; \
    for (unsigned i = 0; i < 288; ++i) \
      { \
	a_##N[i] = 0x94ab5d37u * i + 0x5ab819e1u; \
	b_##N[i] = 0x739f31bdu * i + 0x93e5ba79u; \
      } \
    a_##N[0] = 0; a_##N[1] = -1; \
    a_##N[2] = (1ULL << (sizeof (T) * 8 - 1)); \
    a_##N[3] = (1ULL << (sizeof (T) * 8 - 1)) - 1; \
    for (unsigned n = 0; n <= 257; ++n) \
      for (unsigned offset = 0; offset < 4; ++offset) \
	for (unsigned k = 0; k < 5; ++k) \
	  { \
	    for (unsigned i = 0; i < 288; ++i) \
	      d_##N[i] = q_##N[i] = m_##N[i] = 93; \
	    if (k < 4) \
	      f[k] (d_##N + offset, a_##N, b_##N + offset, n); \
	    else \
	      shared_##N (d_##N + offset, q_##N + offset, m_##N + offset, \
			  a_##N, b_##N + offset, n); \
	    for (unsigned i = 0; i < 288; ++i) \
	      { \
		T want = 93, q = 93, m = 93; \
		if (i >= offset && i < offset + n) \
		  { \
		    int64_t av = a_##N[i - offset], bv = b_##N[i]; \
		    want = floor_half (av + bv); \
		    if (k == 2) want = floor_half (av + 1); \
		    if (k == 3) \
		      want = (U) ((uint64_t) (U) (av & bv) \
				  + (U) floor_half (av ^ (T) 0x5b)); \
		    if (k == 4) \
		      { q = floor_half (av ^ bv); m = av & bv; } \
		  } \
		if (d_##N[i] != want || q_##N[i] != q || m_##N[i] != m) \
		  __builtin_abort (); \
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
#define RUN(T, U, N) check_##N ();
  TYPES (RUN)
  return 0;
}
#endif
