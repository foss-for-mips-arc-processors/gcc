#include <stdint.h>

#define PACK_CLIP(NAME, TO, FROM, MAX, N) \
  __attribute__ ((noipa)) void \
  NAME (TO *restrict dst, const FROM *restrict src) \
  { \
    dst = __builtin_assume_aligned (dst, 8); \
    src = __builtin_assume_aligned (src, 8); \
    for (unsigned int i = 0; i < N; ++i) \
      dst[i] = src[i] > MAX ? MAX : src[i]; \
  }

PACK_CLIP (pack_clip_u16, uint8_t, uint16_t, UINT8_MAX, 8)
PACK_CLIP (pack_clip_u32, uint16_t, uint32_t, UINT16_MAX, 4)

#undef PACK_CLIP
