/* { dg-do run } */
/* { dg-options "-O3" } */
/* { dg-require-effective-target vect_int } */

#include <stdint-gcc.h>
#ifndef TEST_FUNCTIONS_ONLY
#include "tree-vect.h"
#endif

#define TYPES(M) \
  M (int8_t, s8) M (uint8_t, u8) \
  M (int16_t, s16) M (uint16_t, u16) \
  M (int32_t, s32) M (uint32_t, u32)

/* Inlining should expose identical inputs and nonuniform constant lanes
   even if the helper has already been converted to an average IFN.  */
#define TEST(T, NAME) \
  typedef T NAME __attribute__ ((vector_size (8))); \
  static NAME avg_##NAME (NAME a, NAME b) \
  { return (a & b) + ((a ^ b) >> 1); } \
  NAME __attribute__ ((noipa)) same_##NAME (NAME a) \
  { return avg_##NAME (a, a); } \
  NAME __attribute__ ((noipa)) constant_##NAME (void) \
  { \
    NAME a = { (T) (1ULL << (sizeof (T) * 8 - 1)), \
               (T) ((1ULL << (sizeof (T) * 8 - 1)) - 1) }; \
    NAME b = { a[1], a[0] }; \
    return avg_##NAME (a, b); \
  } \
  NAME __attribute__ ((noipa)) constant_edge_##NAME (void) \
  { \
    NAME a = { (T) (1ULL << (sizeof (T) * 8 - 1)), \
               (T) ((1ULL << (sizeof (T) * 8 - 1)) - 1) }; \
    NAME b = { a[0] + 1, a[1] - 1 }; \
    return avg_##NAME (a, b); \
  } \
  NAME __attribute__ ((noipa)) zero_##NAME (NAME a) \
  { return avg_##NAME (a, (NAME) { 0 }); }
TYPES (TEST)

#ifndef TEST_FUNCTIONS_ONLY
int
main (void)
{
  check_vect ();
#define CHECK(T, NAME) \
  { \
    NAME a; \
    for (unsigned i = 0; i < 8 / sizeof (T); ++i) \
      a[i] = (T) (0x8765fedcu + 73u * i); \
    NAME r = same_##NAME (a); \
    for (unsigned i = 0; i < 8 / sizeof (T); ++i) \
      if (r[i] != a[i]) __builtin_abort (); \
    r = constant_##NAME (); \
    T low = (T) (1ULL << (sizeof (T) * 8 - 1)); \
    T high = (T) ((1ULL << (sizeof (T) * 8 - 1)) - 1); \
    int64_t sum = (int64_t) low + high; \
    T average = sum / 2 - (sum < 0 && sum % 2 != 0); \
    for (unsigned i = 0; i < 8 / sizeof (T); ++i) \
      if (r[i] != (i < 2 ? average : 0)) __builtin_abort (); \
    r = constant_edge_##NAME (); \
    for (unsigned i = 0; i < 8 / sizeof (T); ++i) \
      if (r[i] != (i == 0 ? low : i == 1 ? high - 1 : 0)) \
        __builtin_abort (); \
    r = zero_##NAME (a); \
    for (unsigned i = 0; i < 8 / sizeof (T); ++i) \
      { \
        int64_t value = a[i]; \
        T want = value / 2 - (value < 0 && value % 2 != 0); \
        if (r[i] != want) __builtin_abort (); \
      } \
  }
  TYPES (CHECK)
  return 0;
}
#endif
