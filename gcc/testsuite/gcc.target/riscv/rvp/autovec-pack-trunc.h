#include <stdint.h>

#define NARROW(NAME, TO, FROM, N) \
  __attribute__ ((noipa)) void \
  NAME (TO *restrict dst, const FROM *restrict src) \
  { \
    dst = __builtin_assume_aligned (dst, 8); \
    src = __builtin_assume_aligned (src, 8); \
    for (unsigned int i = 0; i < N; ++i) \
      dst[i] = (TO) src[i]; \
  }

NARROW (narrow_u16, uint8_t, uint16_t, 8)
NARROW (narrow_u32, uint16_t, uint32_t, 4)

#undef NARROW
