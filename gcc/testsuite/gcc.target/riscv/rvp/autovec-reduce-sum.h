#include <stdint.h>

#define REDUCE_SUM(NAME, TYPE) \
  __attribute__ ((noipa)) TYPE \
  NAME (const TYPE *src, unsigned int n) \
  { \
    TYPE sum = 0; \
    for (unsigned int i = 0; i < n; ++i) \
      sum += src[i]; \
    return sum; \
  }

REDUCE_SUM (sum_mod_u8, uint8_t)
REDUCE_SUM (sum_mod_u16, uint16_t)

#undef REDUCE_SUM
