/* { dg-do run } */
/* { dg-options "-O3" } */
/* { dg-require-effective-target vect_int } */

#include <stdint-gcc.h>
#if !defined (TEST_FUNCTIONS_ONLY) && !defined (TEST_DRIVER_ONLY)
#include "tree-vect.h"
#endif

#define TYPES(M) \
  M (int8_t, s8) M (uint8_t, u8) \
  M (int16_t, s16) M (uint16_t, u16) \
  M (int32_t, s32) M (uint32_t, u32)

#define DECL(T, N) void half_##N (T *, const T *, unsigned);
TYPES (DECL)

#ifndef TEST_DRIVER_ONLY
/* This identity rounds up without overflowing at the largest input.  */
#define TEST(T, N) \
  void __attribute__ ((noipa)) \
  half_##N (T *restrict dst, const T *restrict src, unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      dst[i] = (src[i] >> 1) + (src[i] & 1); \
  }
TYPES (TEST)
#endif

#ifndef TEST_FUNCTIONS_ONLY
#define CHECK(T, N) \
  static T src_##N[288] __attribute__ ((aligned (64))); \
  static T dst_##N[288] __attribute__ ((aligned (64))); \
  static void check_##N (void) \
  { \
    for (unsigned i = 0; i < 288; ++i) \
      src_##N[i] = 0x94ab5d37u * i + 0x5ab819e1u; \
    src_##N[0] = 0; src_##N[1] = 1; src_##N[2] = -1; \
    src_##N[3] = (1ULL << (sizeof (T) * 8 - 1)); \
    src_##N[4] = (1ULL << (sizeof (T) * 8 - 1)) - 1; \
    for (unsigned n = 0; n <= 257; ++n) \
      for (unsigned a = 0; a < 4; ++a) \
        for (unsigned b = 0; b < 4; ++b) \
          { \
            for (unsigned i = 0; i < 288; ++i) dst_##N[i] = 93; \
            half_##N (dst_##N + b, src_##N + a, n); \
            for (unsigned i = 0; i < 288; ++i) \
              { \
                T want = 93; \
                if (i >= b && i < b + n) \
                  want = ((int64_t) src_##N[i - b + a] + 1) >> 1; \
                if (dst_##N[i] != want) __builtin_abort (); \
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
#define RUN(T, N) check_##N ();
  TYPES (RUN)
  return 0;
}
#endif
