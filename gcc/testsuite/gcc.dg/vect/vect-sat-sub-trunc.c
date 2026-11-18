/* { dg-require-effective-target stdint_types } */

#include "tree-vect.h"
#include "vect-sat-sub-trunc.h"

/* All inputs fit in int64_t.  Measure their mathematical distance before
   applying any unsigned modulo or boolean conversion.  */
static uint64_t __attribute__ ((noipa, optimize ("O0")))
reference (uint32_t x, uint32_t y)
{
  int64_t distance = (int64_t) x - (int64_t) y;
  if (distance < 0)
    return 0;
  return distance;
}

static uint8_t __attribute__ ((noipa, optimize ("O0")))
reference_boolean (uint16_t x, uint16_t y)
{
  uint64_t a = x != 0;
  uint64_t b = y != 0;
  if (x < y)
    return 0;
  return (a - b) & 255;
}

static const uint32_t edges[] =
  {
    0, 1, 127, 128, 255, 256, 257, 32767, 32768, 65535,
    65536, 65537, UINT32_MAX, UINT32_C (0x80000000)
  };
static const unsigned int lengths[] =
  { 0, 1, 7, 16, 17, 64, 65 };

static void
check (unsigned int round, unsigned int layout, unsigned int n)
{
  uint16_t x16[128] __attribute__ ((aligned (64)));
  uint16_t y16[128] __attribute__ ((aligned (64)));
  uint32_t x32[128] __attribute__ ((aligned (64)));
  uint32_t y32[128] __attribute__ ((aligned (64)));
  uint8_t low16[192] __attribute__ ((aligned (64)));
  uint8_t low32[192] __attribute__ ((aligned (64)));
  uint16_t wide[128] __attribute__ ((aligned (64)));
  _Bool boolean[192] __attribute__ ((aligned (64)));
  uint8_t logical[192] __attribute__ ((aligned (64)));
  uint8_t shared[192] __attribute__ ((aligned (64)));
  uint16_t raw[128] __attribute__ ((aligned (64)));
  _Bool flag[192] __attribute__ ((aligned (64)));
  unsigned int in16 = 64 / sizeof (uint16_t) + layout;
  unsigned int in32 = 64 / sizeof (uint32_t) + layout;
  unsigned int out8 = 64 / sizeof (uint8_t) + layout;
  unsigned int out16 = 64 / sizeof (uint16_t) + layout;
  unsigned int outbool = 64 / sizeof (_Bool) + layout;
  unsigned int count = sizeof (edges) / sizeof (edges[0]);

  for (unsigned int i = 0; i < 128; ++i)
    {
      x32[i] = edges[(i + round) % count];
      y32[i] = edges[(i + 2 * round) % count];
      x16[i] = x32[i];
      y16[i] = y32[i];
      wide[i] = 0x5a5a;
      raw[i] = 0x5a5a;
    }
  for (unsigned int i = 0; i < 192; ++i)
    {
      low16[i] = low32[i] = logical[i] = shared[i] = 0x5a;
      boolean[i] = flag[i] = i & 1;
    }

  sat_sub_16_8 (low16 + out8, x16 + in16, y16 + in16, n);
  sat_sub_32_16_8 (low32 + out8, x32 + in32, y32 + in32, n);
  sat_sub_wide (wide + out16, x16 + in16, y16 + in16, n);
  sat_sub_boolean_result (boolean + outbool, x16 + in16, y16 + in16, n);
  sat_sub_boolean_operands (logical + out8, x16 + in16, y16 + in16, n);
  sat_sub_shared (shared + out8, raw + out16, flag + outbool,
		  x32 + in32, y32 + in32, n);

  for (unsigned int i = 0; i < 128; ++i)
    {
      uint32_t a = edges[(i + round) % count];
      uint32_t b = edges[(i + 2 * round) % count];
      uint16_t expected_wide = 0x5a5a;
      uint16_t expected_raw = 0x5a5a;
      if (i >= out16 && i < out16 + n)
	{
	  unsigned int j = i - out16;
	  uint64_t p = x32[in32 + j] & 65535;
	  uint64_t q = y32[in32 + j] & 65535;
	  expected_wide = reference (x16[in16 + j], y16[in16 + j]) & 255;
	  expected_raw = (p + 65536 - q) & 65535;
	}
      if (x32[i] != a || y32[i] != b
	  || x16[i] != (uint16_t) a || y16[i] != (uint16_t) b
	  || wide[i] != expected_wide || raw[i] != expected_raw)
	__builtin_abort ();
    }

  for (unsigned int i = 0; i < 192; ++i)
    {
      uint8_t expected16 = 0x5a;
      uint8_t expected32 = 0x5a;
      uint8_t expected_logical = 0x5a;
      _Bool expected_boolean = i & 1;
      _Bool expected_flag = i & 1;
      if (i >= out8 && i < out8 + n)
	{
	  unsigned int j = i - out8;
	  expected16 = reference (x16[in16 + j], y16[in16 + j]);
	  expected32 = reference (x32[in32 + j], y32[in32 + j]);
	  expected_logical = reference_boolean (x16[in16 + j],
						y16[in16 + j]);
	}
      if (i >= outbool && i < outbool + n)
	{
	  unsigned int j = i - outbool;
	  expected_boolean = (reference (x16[in16 + j], y16[in16 + j])
			      & 255) != 0;
	  expected_flag = x32[in32 + j] >= y32[in32 + j];
	}
      if (low16[i] != expected16 || low32[i] != expected32
	  || shared[i] != expected32 || logical[i] != expected_logical
	  || boolean[i] != expected_boolean || flag[i] != expected_flag)
	__builtin_abort ();
    }
}

int
main (void)
{
  check_vect ();
  for (unsigned int round = 0;
       round < sizeof (edges) / sizeof (edges[0]); ++round)
    for (unsigned int layout = 0; layout < 2; ++layout)
      for (unsigned int i = 0;
	   i < sizeof (lengths) / sizeof (lengths[0]); ++i)
	check (round, layout, lengths[i]);
  return 0;
}
