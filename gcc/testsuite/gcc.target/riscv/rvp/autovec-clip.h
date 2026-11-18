#include <stdint.h>

#define CLIP(NAME, TO, FROM, MAX, SHIFT) \
  __attribute__ ((noipa)) void \
  NAME (TO *restrict dst, const FROM *restrict src, unsigned int n) \
  { \
    for (unsigned int i = 0; i < n; ++i) \
      { \
	FROM value = src[i] >> SHIFT; \
	dst[i] = value > MAX ? MAX : value; \
      } \
  }

CLIP (clip_u16, uint8_t, uint16_t, UINT8_MAX, 0)
CLIP (clip_u32, uint16_t, uint32_t, UINT16_MAX, 0)
CLIP (clip_u16_shift, uint8_t, uint16_t, UINT8_MAX, 4)
CLIP (clip_u32_shift, uint16_t, uint32_t, UINT16_MAX, 4)

#undef CLIP
