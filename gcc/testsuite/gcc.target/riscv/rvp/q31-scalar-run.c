/* { dg-do run } */
/* { dg-options "-O3" } */

#include "q31-scalar.h"

static long long __attribute__ ((noipa, optimize ("O0")))
floor_scale (long long value, long long divisor)
{
  long long quotient = value / divisor;
  return quotient - (value < 0 && value % divisor != 0);
}

static int __attribute__ ((noipa, optimize ("O0")))
wrap32 (unsigned long long value)
{
  unsigned int bits = value;
  return bits < 2147483648U ? (long long) bits
			  : (long long) bits - 4294967296LL;
}

static long long __attribute__ ((noipa, optimize ("O0")))
clamp (long long value)
{
  return value > 2147483647 ? 2147483647 : value;
}

static void __attribute__ ((noipa, optimize ("O0")))
check (int a, int b, unsigned int high_a, unsigned int high_b)
{
  long long product = (long long) a * b;
  long long scaled = floor_scale (product, 2147483648LL);
  long long plain = clamp (scaled);
  long long rounded = clamp (floor_scale (product + 1073741824,
					 2147483648LL));
  long long saved, saved_round;
  unsigned long long full_a = ((unsigned long long) high_a << 32)
			     | (unsigned int) a;
  unsigned long long full_b = ((unsigned long long) high_b << 32)
			     | (unsigned int) b;
  unsigned long long saved_full;
  unsigned long long u = ((unsigned long long) (unsigned int) a
			 * (unsigned int) b + 1073741824) / 2147483648ULL;
  long long mixed = (long long) a * (unsigned int) b;
  int low = (unsigned short) plain;
  if (low >= 32768)
    low -= 65536;
  if (q31_scalar (a, b) != plain
      || q31_scalar_round (a, b) != rounded
      || q31_scalar_wide (a, b) != plain
      || q31_scalar_round_wide (a, b) != rounded
      || q31_scalar_save (a, b, &saved) != plain
      || q31_scalar_round_save (a, b, &saved_round) != rounded
      || saved != product || saved_round != product
      || q31_scalar_full (full_a, full_b, &saved_full) != plain
      || saved_full != full_a + full_b
      || q31_scalar_cond (a, b, 1) != plain
      || q31_scalar_cond (a, b, 0) != floor_scale (product, 4294967296LL)
      || q31_scalar_wrong_limit (a, b)
	 != (scaled > 2147483646 ? 2147483646 : scaled)
      || q31_scalar_wrong_round (a, b)
	 != clamp (floor_scale (product + 1073741823, 2147483648LL))
      || q31_scalar_unsigned (a, b) != (u > 2147483647 ? 2147483647 : u)
      || q31_scalar_mixed (a, b)
	 != wrap32 (clamp (floor_scale (mixed + 1073741824, 2147483648LL)))
      || q31_scalar_wrap (a, b) != wrap32 (scaled)
      || q31_scalar_truncated (a, b) != (wrap32 (product) < 0 ? -1 : 0)
      || q31_scalar_shift32 (a, b) != floor_scale (product, 4294967296LL)
      || q31_scalar_low_bits (a, b) != low)
    __builtin_abort ();
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const int values[] = { -2147483647 - 1, -2147483647, -1073741825,
    -1073741824, -65537, -65536, -32769, -32768, -2, -1, 0, 1, 2, 32767,
    32768, 65535, 65536, 1073741823, 1073741824, 2147483646, 2147483647 };
  unsigned int state = 0x12345678;
  for (unsigned int i = 0; i < sizeof (values) / sizeof (values[0]); ++i)
    for (unsigned int j = 0; j < sizeof (values) / sizeof (values[0]); ++j)
      check (values[i], values[j], i * 0x10001001U, j * 0x80010001U);
  for (unsigned int i = 0; i < 65536; ++i)
    {
      state = state * 1664525 + 1013904223;
      int a = wrap32 (state);
      state = state * 1664525 + 1013904223;
      int b = wrap32 (state);
      check (a, b, i * 0x80010001U, state);
    }
  return 0;
}
