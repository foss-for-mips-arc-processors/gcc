#include <stdint.h>

#define CONVERT(NAME, TO, FROM) \
  __attribute__ ((noinline, noclone)) void \
  NAME (TO *restrict dst, const FROM *restrict src, unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      dst[i] = (TO) src[i]; \
  }

CONVERT (widen_s8, int16_t, int8_t)
CONVERT (widen_u8, uint16_t, uint8_t)
CONVERT (widen_s16, int32_t, int16_t)
CONVERT (widen_u16, uint32_t, uint16_t)
CONVERT (narrow_16, uint8_t, uint16_t)
CONVERT (narrow_32, uint16_t, uint32_t)

#undef CONVERT
