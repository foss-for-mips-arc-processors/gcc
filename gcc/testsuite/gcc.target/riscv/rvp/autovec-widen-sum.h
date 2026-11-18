#include <stdint.h>

#define WIDEN_SUM(NAME, TO, FROM) \
  __attribute__ ((noipa)) TO \
  NAME (const FROM *src, unsigned int n) \
  { \
    TO sum = 0; \
    for (unsigned int i = 0; i < n; ++i) \
      sum += src[i]; \
    return sum; \
  }

WIDEN_SUM (sum_s8, int32_t, int8_t)
WIDEN_SUM (sum_u8, uint32_t, uint8_t)
WIDEN_SUM (sum_s16, int32_t, int16_t)
WIDEN_SUM (sum_u16, uint32_t, uint16_t)

#undef WIDEN_SUM
