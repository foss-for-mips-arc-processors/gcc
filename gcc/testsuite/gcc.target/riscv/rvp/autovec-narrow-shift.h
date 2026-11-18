#include <stdint.h>

#define NARROW_SHIFT_LOOP(NAME, TO, FROM) \
  __attribute__ ((noipa)) void \
  NAME (TO *restrict dst, const FROM *restrict src, unsigned int n) \
  { \
    for (unsigned int i = 0; i < n; ++i) \
      dst[i] = src[i] >> 4; \
  }

NARROW_SHIFT_LOOP (shift_u16, uint8_t, uint16_t)
NARROW_SHIFT_LOOP (shift_s16, int8_t, int16_t)
NARROW_SHIFT_LOOP (shift_u32, uint16_t, uint32_t)
NARROW_SHIFT_LOOP (shift_s32, int16_t, int32_t)

#undef NARROW_SHIFT_LOOP
