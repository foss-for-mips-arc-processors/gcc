/* { dg-do run } */
/* { dg-options "-O2" } */

#include "vector-concat-endian.h"

#define CHECK_VECTOR(EXPR, X, Y) \
  do \
    { \
      __typeof__ (EXPR) result = (EXPR); \
      if (result[0] != (X) || result[1] != (Y)) \
        __builtin_abort (); \
    } \
  while (0)

int
main (void)
{
  concat_h2 a = { 3, 5 }, b = { 7, 11 }, c = { 13, 17 };
  CHECK_VECTOR (concat_h_ctor (0x12345678U, 0x9abcdef0U), 0x5678, 0xdef0);
  CHECK_VECTOR (concat_h_ctor_signed (-1, -2), 0xffff, 0xfffe);
  CHECK_VECTOR (concat_h_ctor_eo (0x12345678U, 0x9abcdef0U), 0x5678, 0x9abc);
  CHECK_VECTOR (concat_h_ctor_oe (0x12345678U, 0x9abcdef0U), 0x1234, 0xdef0);
  CHECK_VECTOR (concat_h_ctor_oo (0x12345678U, 0x9abcdef0U), 0x1234, 0x9abc);
  CHECK_VECTOR (concat_h_mul (a, b), 21, 55);
  CHECK_VECTOR (concat_h_mac (c, a, b), 34, 72);
  CHECK_VECTOR (concat_h_shared (c, a, b), 21, 72);
  CHECK_VECTOR (concat_h_identity (a), 3, 5);
  CHECK_VECTOR (concat_h_memory (&a, &b), 21, 55);
  CHECK_VECTOR (concat_h_set0 (a, 0x1234abcdU), 0xabcd, 5);
  CHECK_VECTOR (concat_h_set1 (a, 0x1234abcdU), 3, 0xabcd);
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  concat_uint64 original = 0x000d0011ULL << 32;
#else
  concat_uint64 original = 0x0011000dULL << 32;
#endif
  if (concat_h_mul0 (a, b) != 21 || concat_h_mul1 (a, b) != 55
      || concat_h_mac0 (c, a, b) != 34 || concat_h_mac1 (c, a, b) != 72
      || concat_h_live0 (c, a, b) != (original | 34)
      || concat_h_live1 (c, a, b) != (original | 72)
      || concat_original_wide (c, a, b) != (original | 34))
    __builtin_abort ();

  concat_w2 x = { 0xffffffffU, 0x80000001U }, y = { 2, 3 }, z = { 5, 7 };
  concat_uint64 first = 0x0123456789abcdefULL;
  concat_uint64 second = 0xfedcba9876543210ULL;
  CHECK_VECTOR (concat_w_ctor (0x89abcdefU, 0xfedcba98U),
                0x89abcdefU, 0xfedcba98U);
  CHECK_VECTOR (concat_w_ctor_signed (-1, -2), 0xffffffffU, 0xfffffffeU);
  CHECK_VECTOR (concat_w_ctor_eo (first, second), 0x89abcdefU, 0xfedcba98U);
  CHECK_VECTOR (concat_w_ctor_oe (first, second), 0x01234567U, 0x76543210U);
  CHECK_VECTOR (concat_w_ctor_oo (first, second), 0x01234567U, 0xfedcba98U);
  CHECK_VECTOR (concat_w_mul (x, y), 0xfffffffeU, 0x80000003U);
  CHECK_VECTOR (concat_w_mac (z, x, y), 3, 0x8000000aU);
  CHECK_VECTOR (concat_w_shared (z, x, y), 0xfffffffeU, 0x8000000aU);
  CHECK_VECTOR (concat_w_identity (x), 0xffffffffU, 0x80000001U);
  CHECK_VECTOR (concat_w_memory (&x, &y), 0xfffffffeU, 0x80000003U);
  CHECK_VECTOR (concat_w_set0 (x, 0x1234abcdU), 0x1234abcdU, 0x80000001U);
  CHECK_VECTOR (concat_w_set1 (x, 0x1234abcdU), 0xffffffffU, 0x1234abcdU);
  if (concat_w_mul0 (x, y) != 0xfffffffeU
      || concat_w_mul1 (x, y) != 0x80000003U
      || concat_w_mac0 (z, x, y) != 3
      || concat_w_mac1 (z, x, y) != 0x8000000aU
      || concat_w_live0 (z, x, y) != 0x200000003ULL
      || concat_w_live1 (z, x, y) != 0x28000000aULL)
    __builtin_abort ();
  concat_h2 narrow_a = { 0x1234, 0xabcd }, narrow_b = { 0x5678, 0xef01 };
  concat_q4 low = concat_narrow_low (narrow_a, narrow_b);
  concat_q4 high = concat_narrow_high (narrow_a, narrow_b);
  if (low[0] != 0x34 || low[1] != 0xcd || low[2] != 0x78 || low[3] != 0x01
      || high[0] != 0x12 || high[1] != 0xab
      || high[2] != 0x56 || high[3] != 0xef)
    __builtin_abort ();
  return 0;
}
