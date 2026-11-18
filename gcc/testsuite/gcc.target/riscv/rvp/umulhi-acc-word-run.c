/* { dg-do run } */
/* { dg-options "-O3" } */

#include "umulhi-acc-word.h"

/* Compute the product with unsigned 16-bit limbs, independently of the
   widening multiply and high-word extraction being tested.  */
static u32 __attribute__ ((noipa, optimize ("O0")))
high_word (u32 a, u32 b, u32 *low)
{
  u32 a0 = a & 65535, a1 = a >> 16;
  u32 b0 = b & 65535, b1 = b >> 16;
  u32 t = a0 * b0, bottom = t & 65535;
  t = a1 * b0 + (t >> 16);
  u32 middle = t & 65535, high = t >> 16;
  t = a0 * b1 + middle;
  *low = (t << 16) | bottom;
  return high + a1 * b1 + (t >> 16);
}

static void __attribute__ ((noipa, optimize ("O0")))
check (u32 a, u32 b, u32 c, u32 upper)
{
  u32 low;
  u32 high = high_word (a, b, &low);
  u32 sum = c + high;
  u64 product = ((u64) high << 32) | low;
  u64 aa = ((u64) upper << 32) | a;
  u64 bb = ((u64) ~upper << 32) | b;
  u64 acc = ((u64) upper << 32) | c;
  u32 d[3] = { 0x12345678U, c, 0x87654321U };
  u64 saved[3] = { 0x123456789abcdefULL, 0, 0xfedcba9876543210ULL };

  if (umulhi_acc (c, a, b) != sum
      || umulhi_left (a, b) != a + high
      || umulhi_right (a, b) != b + high
      || umulhi_live_upper (aa, bb, c) != (aa ^ bb) + sum
      || umulhi_preserve_acc (acc, a, b) != (((u64) upper << 32) | sum)
      || umulhi_wide (acc, a, b) != acc + high)
    __builtin_abort ();

  umulhi_store (d + 1, a, b);
  if (d[1] != sum)
    __builtin_abort ();
  d[1] = c;
  if (umulhi_store_return (d + 1, a, b) != sum || d[1] != sum)
    __builtin_abort ();
  d[1] = c;
  umulhi_volatile (d + 1, a, b);
  if (d[1] != sum)
    __builtin_abort ();

  if (umulhi_shared_product (c, a, b, saved + 1) != sum
      || saved[1] != product
      || umulhi_shared_high (c, a, b, d + 1) != sum
      || d[1] != high)
    __builtin_abort ();
  if (d[0] != 0x12345678U || d[2] != 0x87654321U
      || saved[0] != 0x123456789abcdefULL
      || saved[2] != 0xfedcba9876543210ULL)
    __builtin_abort ();

  u32 biased_low = low + 0x40000000U;
  u32 cross_a, cross_b;
  high_word (upper, b, &cross_a);
  high_word (a, ~upper, &cross_b);
  if (umulhi_shift31 (c, a, b) != c + ((high << 1) | (low >> 31))
      || umulhi_wrong_bias (c, a, b) != c + high + (biased_low < low)
      || umulhi_full_width (c, aa, bb) != c + high + cross_a + cross_b)
    __builtin_abort ();
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const u32 values[]
    = { 0, 1, 2, 0x7fff, 0x8000, 0xffff, 0x10000, 0x7fffffff,
	0x80000000, 0x80000001, 0xfffffffe, 0xffffffff };
  for (unsigned i = 0; i < 12; ++i)
    for (unsigned j = 0; j < 12; ++j)
      {
	u32 a = values[i], b = values[j];
	u32 upper = values[(i + j) % 12];
	check (a, b, 0, upper);
	check (a, b, ~0U, ~upper);
	check (a, b, values[(i + 2 * j) % 12], upper ^ 0xa55a5aa5U);
      }
  u32 seed = 0x8162b4d3U;
  for (unsigned i = 0; i < 1024; ++i)
    {
      seed = seed * 1664525U + 1013904223U;
      u32 a = seed;
      seed = seed * 1664525U + 1013904223U;
      u32 b = seed;
      seed = seed * 1664525U + 1013904223U;
      u32 c = seed;
      seed = seed * 1664525U + 1013904223U;
      check (a, b, c, seed);
    }
  return 0;
}
