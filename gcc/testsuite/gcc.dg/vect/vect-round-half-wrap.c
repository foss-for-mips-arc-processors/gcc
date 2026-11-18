/* { dg-do run } */
/* { dg-options "-O3 -fwrapv" } */
/* { dg-require-effective-target vect_int } */

#include <stdint-gcc.h>
#if !defined (TEST_FUNCTIONS_ONLY) && !defined (TEST_DRIVER_ONLY)
#include "tree-vect.h"
#endif

#define TYPES(M) \
  M (int8_t, uint8_t, 4, b4) M (int16_t, uint16_t, 4, h2) \
  M (int8_t, uint8_t, 8, b8) M (int16_t, uint16_t, 8, h4) \
  M (int32_t, uint32_t, 8, w2)

#define DECL(S, U, SIZE, N) \
  typedef S s##N __attribute__ ((vector_size (SIZE))); \
  typedef U u##N __attribute__ ((vector_size (SIZE))); \
  s##N reverse_##N (u##N);
TYPES (DECL)

#ifndef TEST_DRIVER_ONLY
/* At the largest unsigned input the signed addition wraps.  Select the
   average's signedness from the shift, not from the result type.  */
#define TEST(S, U, SIZE, N) \
  s##N __attribute__ ((noipa)) reverse_##N (u##N x) \
  { return (s##N) (x >> 1) + (s##N) (x & 1); }
TYPES (TEST)
#endif

#ifndef TEST_FUNCTIONS_ONLY
#define CHECK(S, U, SIZE, N) \
  static void check_##N (uint32_t value) \
  { \
    u##N x; \
    for (unsigned i = 0; i < SIZE / sizeof (S); ++i) \
      x[i] = value + 17u * i; \
    s##N r = reverse_##N (x); \
    for (unsigned i = 0; i < SIZE / sizeof (S); ++i) \
      if ((U) r[i] != (U) (((uint64_t) x[i] + 1) >> 1)) \
        __builtin_abort (); \
  }
TYPES (CHECK)

int
main (void)
{
#ifndef TEST_DRIVER_ONLY
  check_vect ();
#endif
  uint32_t state = 0x9b3a173d;
  check_b4 (-1); check_b8 (-1); check_h2 (-1); check_h4 (-1); check_w2 (-1);
  for (unsigned i = 0; i < 65536; ++i)
    {
      if (i < 256) { check_b4 (i); check_b8 (i); }
      check_h2 (i); check_h4 (i);
      state = state * 1664525u + 1013904223u;
      check_w2 (state);
    }
  return 0;
}
#endif
