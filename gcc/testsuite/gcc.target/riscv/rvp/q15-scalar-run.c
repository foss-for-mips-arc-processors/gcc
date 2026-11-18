/* { dg-do run } */
/* { dg-options "-O3" } */

#include "q15-scalar.h"

static long long __attribute__ ((noipa, optimize ("O0")))
scale (long long value, long long divisor)
{
  long long quotient = value / divisor;
  return quotient - (value < 0 && value % divisor != 0);
}

static int __attribute__ ((noipa, optimize ("O0")))
wrap16 (unsigned long long value)
{
  unsigned short bits = value;
  return bits < 32768 ? (int) bits : (int) bits - 65536;
}

static long long __attribute__ ((noipa, optimize ("O0")))
clamp (long long value)
{
  return value > 32767 ? 32767 : value;
}

static void __attribute__ ((noipa, optimize ("O0")))
check (int a, int b, unsigned int high_a, unsigned int high_b)
{
  long long product = (long long) a * b;
  long long scaled = scale (product, 32768);
  long long plain = clamp (scaled);
  long long rounded = clamp (scale (product + 16384, 32768));
  int saved;
  long long saved_round;
  unsigned long long full_a = ((unsigned long long) high_a << 16)
			     | (unsigned short) a;
  unsigned long long full_b = ((unsigned long long) high_b << 32)
			     | ((unsigned int) high_a << 16) | (unsigned short) b;
  unsigned long long saved_full;
  long long u = (long long) (unsigned short) a * (unsigned short) b;
  long long mixed = (long long) a * (unsigned short) b;
  long long cast = (long long) (unsigned int) a * (unsigned short) b;
  int low = (unsigned char) plain;
  if (low >= 128)
    low -= 256;
  if (q15_scalar (a, b) != plain
      || q15_scalar_round (a, b) != rounded
      || q15_scalar_wide (a, b) != plain
      || q15_scalar_ll (a, b) != plain
      || q15_scalar_ll_round (a, b) != rounded
      || q15_scalar_save (a, b, &saved) != plain
      || q15_scalar_round_save (a, b, &saved_round) != rounded
      || saved != product || saved_round != product
      || q15_scalar_full (full_a, full_b, &saved_full) != plain
      || saved_full != full_a + full_b
      || q15_scalar_cond (a, b, 1) != plain
      || q15_scalar_cond (a, b, 0) != scale (product, 65536)
      || q15_scalar_two_shifts (a, b) != rounded
      || q15_scalar_ll_two_shifts (a, b) != rounded
      || q15_scalar_wrong_limit (a, b)
	 != (scaled > 32766 ? 32766 : scaled)
      || q15_scalar_wrong_round (a, b) != clamp (scale (product + 16383, 32768))
      || q15_scalar_wrong_two_shifts (a, b)
	 != clamp (scale (scale (product, 16384) + 2, 2))
      || q15_scalar_unsigned (a, b) != clamp (scale (u + 16384, 32768))
      || q15_scalar_mixed (a, b) != clamp (scale (mixed + 16384, 32768))
      || q15_scalar_unsigned_cast (a, b) != clamp (scale (cast + 16384, 32768))
      || q15_scalar_wrap (a, b) != wrap16 (scaled)
      || q15_scalar_truncated (a, b) != (wrap16 (product) < 0 ? -1 : 0)
      || q15_scalar_low_bits (a, b) != low)
    __builtin_abort ();
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const int values[] = { -32768, -32767, -16385, -16384, -257,
    -256, -129, -128, -2, -1, 0, 1, 2, 127, 128, 255, 256,
    16383, 16384, 32766, 32767 };
  unsigned int state = 0x12345678;
  for (unsigned int i = 0; i < sizeof (values) / sizeof (values[0]); ++i)
    for (unsigned int j = 0; j < sizeof (values) / sizeof (values[0]); ++j)
      check (values[i], values[j], i * 0x10001001U, j * 0x80010001U);
  for (unsigned int i = 0; i < 65536; ++i)
    {
      state = state * 1664525 + 1013904223;
      int a = wrap16 (state);
      state = state * 1664525 + 1013904223;
      check (a, wrap16 (state), i * 0x80010001U, state);
    }
#ifdef RVP_FULL_SWEEP
  static const int partners[] = { -32768, -32767, -16384, -257, -1, 0,
    1, 2, 255, 16383, 32766, 32767 };
  for (unsigned int i = 0; i < 65536; ++i)
    for (unsigned int j = 0; j < sizeof (partners) / sizeof (partners[0]); ++j)
      check (wrap16 (i), partners[j], i * 0x1234567U, j * 0x80010001U);
#endif
  return 0;
}
