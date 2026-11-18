/* { dg-require-effective-target stdint_types } */

#include "tree-vect.h"
#include "vect-pack-ssat-promoted.h"

/* Widen before measuring distance from the lower bound.  This reference is
   deliberately independent of the optimized same-width MIN/MAX idiom.  */
static long long __attribute__ ((noipa, optimize ("O0")))
reference (long long value, long long low, long long high)
{
  long long distance = value - low;
  if (distance < 0)
    return low;
  if (distance > high - low)
    return high;
  return value;
}

static const int16_t edges16[] =
  { INT16_MIN, -129, -128, -127, -1, 0, 1, 126, 127, 128, INT16_MAX };
static const int32_t edges32[] =
  { INT32_MIN, -32769, -32768, -32767, -1, 0, 1, 32766, 32767,
    32768, INT32_MAX };

static void
check_s16 (void (*fn) (int8_t *, const int16_t *))
{
  int16_t input[24] __attribute__ ((aligned (64)));
  int16_t saved[24];
  int8_t output[24] __attribute__ ((aligned (64)));
  unsigned int count = sizeof (edges16) / sizeof (edges16[0]);

  for (unsigned int round = 0; round < count; ++round)
    {
      for (unsigned int i = 0; i < 24; ++i)
        {
          input[i] = edges16[(round + i) % count];
          saved[i] = input[i];
          output[i] = 85;
        }
      fn (output + 8, input + 8);
      for (unsigned int i = 0; i < 24; ++i)
        {
          long long expected = 85;
          if (i >= 8 && i < 16)
            expected = reference (saved[i], -128, 127);
          if (input[i] != saved[i] || output[i] != expected)
            __builtin_abort ();
        }
    }
}

static void
check_s32 (void (*fn) (int16_t *, const int32_t *))
{
  int32_t input[12] __attribute__ ((aligned (64)));
  int32_t saved[12];
  int16_t output[12] __attribute__ ((aligned (64)));
  unsigned int count = sizeof (edges32) / sizeof (edges32[0]);

  for (unsigned int round = 0; round < count; ++round)
    {
      for (unsigned int i = 0; i < 12; ++i)
        {
          input[i] = edges32[(round + i) % count];
          saved[i] = input[i];
          output[i] = 21845;
        }
      fn (output + 4, input + 4);
      for (unsigned int i = 0; i < 12; ++i)
        {
          long long expected = 21845;
          if (i >= 4 && i < 8)
            expected = reference (saved[i], -32768, 32767);
          if (input[i] != saved[i] || output[i] != expected)
            __builtin_abort ();
        }
    }
}

/* Exercise every signed halfword value, with distinct values in each lane.  */
static void
check_all_s16 (void (*fn) (int8_t *, const int16_t *))
{
  int16_t input[8] __attribute__ ((aligned (64)));
  int8_t output[8] __attribute__ ((aligned (64)));
  for (int base = -32768; base < 32768; base += 8)
    {
      for (int i = 0; i < 8; ++i)
        input[i] = base + i;
      fn (output, input);
      for (int i = 0; i < 8; ++i)
        if (output[i] != reference (input[i], -128, 127))
          __builtin_abort ();
    }
}

int
main (void)
{
  check_vect ();
  check_s16 (pack_promoted_s16_lo_hi);
  check_s16 (pack_promoted_s16_hi_lo);
  check_s32 (pack_promoted_s32_lo_hi);
  check_s32 (pack_promoted_s32_hi_lo);
  check_all_s16 (pack_promoted_s16_lo_hi);
  check_all_s16 (pack_promoted_s16_hi_lo);
  return 0;
}
