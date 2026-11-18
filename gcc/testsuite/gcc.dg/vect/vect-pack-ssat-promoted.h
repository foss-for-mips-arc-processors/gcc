#ifndef VECT_PACK_SSAT_PROMOTED_H
#define VECT_PACK_SSAT_PROMOTED_H

#include <stdint.h>

#define PACK_SSAT_PROMOTED(NAME, OUT, IN, TMP, LOW, HIGH, N, REVERSE) \
  void __attribute__ ((noipa)) \
  NAME (OUT *restrict dst, const IN *restrict src) \
  { \
    dst = __builtin_assume_aligned (dst, 8); \
    src = __builtin_assume_aligned (src, 8); \
    for (unsigned int i = 0; i < N; ++i) \
      { \
        TMP value = src[i]; \
        if (REVERSE) \
          { \
            if (value > HIGH) \
              value = HIGH; \
            if (value < LOW) \
              value = LOW; \
          } \
        else \
          { \
            if (value < LOW) \
              value = LOW; \
            if (value > HIGH) \
              value = HIGH; \
          } \
        dst[i] = value; \
      } \
  }

PACK_SSAT_PROMOTED (pack_promoted_s16_lo_hi, int8_t, int16_t, int32_t,
		    -128, 127, 8, 0)
PACK_SSAT_PROMOTED (pack_promoted_s16_hi_lo, int8_t, int16_t, int32_t,
		    -128, 127, 8, 1)
PACK_SSAT_PROMOTED (pack_promoted_s32_lo_hi, int16_t, int32_t, int64_t,
		    -32768, 32767, 4, 0)
PACK_SSAT_PROMOTED (pack_promoted_s32_hi_lo, int16_t, int32_t, int64_t,
		    -32768, 32767, 4, 1)

#undef PACK_SSAT_PROMOTED

#endif
