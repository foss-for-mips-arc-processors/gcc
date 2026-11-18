/* { dg-do compile } */
/* { dg-require-effective-target stdint_types } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O3 -fvect-cost-model=unlimited -fdump-tree-vect-details -fdump-tree-slp1-details" } */

#include <stdint.h>

/* These clamps either have different bounds or retain a wider comparison
   domain.  Their casts are still representable.  */
#define CLAMP(NAME, OUT, IN, TEMP, LOW, HIGH) \
  void __attribute__ ((noipa)) \
  NAME (OUT *restrict dst, const IN *restrict src, unsigned int n) \
  { \
    for (unsigned int i = 0; i < n; ++i) \
      { \
        TEMP value = src[i]; \
        if (value < LOW) \
          value = LOW; \
        if (value > HIGH) \
          value = HIGH; \
        dst[i] = value; \
      } \
  }

CLAMP (small_s16, int8_t, int16_t, int16_t, -100, 100)
CLAMP (near_s16, int8_t, int16_t, int16_t, -127, 127)
CLAMP (small_s32, int16_t, int32_t, int32_t, -20000, 20000)
CLAMP (near_s32, int16_t, int32_t, int32_t, -32768, 32766)
CLAMP (wide_s32, int8_t, int32_t, int32_t, -128, 127)

#undef CLAMP

void __attribute__ ((noipa))
shared_inner_s16 (int8_t *restrict dst, int16_t *restrict observed,
                  const int16_t *restrict src, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      int16_t value = src[i];
      if (value < -128)
        value = -128;
      observed[i] = value;
      if (value > 127)
        value = 127;
      dst[i] = value;
    }
}

void __attribute__ ((noipa))
shared_inner_s32 (int16_t *restrict dst, int32_t *restrict observed,
                  const int32_t *restrict src, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      int32_t value = src[i];
      if (value > 32767)
        value = 32767;
      observed[i] = value;
      if (value < -32768)
        value = -32768;
      dst[i] = value;
    }
}

void __attribute__ ((noipa))
shared_outer_s32 (int16_t *restrict dst, int32_t *restrict observed,
                  const int32_t *restrict src, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      int32_t value = src[i];
      if (value < -32768)
        value = -32768;
      if (value > 32767)
        value = 32767;
      observed[i] = value;
      dst[i] = value;
    }
}

/* Reject only the new recognition.  Existing unary or combine patterns may
   legitimately generate narrowing instructions for some of these cases.  */
/* { dg-final { scan-tree-dump-not "vect_recog_(promoted_)?sat_trunc_clamp" "vect" } } */
/* { dg-final { scan-tree-dump-not "vect_recog_(promoted_)?sat_trunc_clamp" "slp1" } } */
