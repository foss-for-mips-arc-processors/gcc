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

#define DECL(T, N) \
  typedef T N __attribute__ ((vector_size (8))); \
  N constant_##N (void); \
  N constant_max_##N (void);
TYPES (DECL)

#ifndef TEST_DRIVER_ONLY
/* Fold constant inputs after inlining a helper already recognized as an
   average.  Include both extrema and nonuniform lanes.  */
#define TEST(T, N) \
  static N half_##N (N a) { return (a >> 1) + (a & 1); } \
  N __attribute__ ((noipa)) constant_##N (void) \
  { \
    N a = { (T) (1ULL << (sizeof (T) * 8 - 1)), \
            (T) ((1ULL << (sizeof (T) * 8 - 1)) - 1) }; \
    return half_##N (a); \
  } \
  N __attribute__ ((noipa)) constant_max_##N (void) \
  { return half_##N ((N) { (T) -1, 1 }); }
TYPES (TEST)
#endif

#ifndef TEST_FUNCTIONS_ONLY
int
main (void)
{
#ifndef TEST_DRIVER_ONLY
  check_vect ();
#endif
#define CHECK(T, N) \
  { \
    N r = constant_##N (); \
    T low = (T) (1ULL << (sizeof (T) * 8 - 1)); \
    T high = (T) ((1ULL << (sizeof (T) * 8 - 1)) - 1); \
    for (unsigned i = 0; i < 8 / sizeof (T); ++i) \
      { \
        int64_t x = i == 0 ? low : i == 1 ? high : 0; \
        if (r[i] != (T) ((x + 1) >> 1)) __builtin_abort (); \
      } \
    r = constant_max_##N (); \
    for (unsigned i = 0; i < 8 / sizeof (T); ++i) \
      { \
        int64_t x = i == 0 ? (T) -1 : i == 1 ? 1 : 0; \
        if (r[i] != (T) ((x + 1) >> 1)) __builtin_abort (); \
      } \
  }
  TYPES (CHECK)
  return 0;
}
#endif
