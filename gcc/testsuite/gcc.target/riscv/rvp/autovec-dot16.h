#include <stdint.h>

/* Use unsigned accumulators so the wraparound tests have defined C
   semantics even when the signed or mixed-sign products are negative.  */
#define DOT16(NAME, A, B, PRODUCT) \
  __attribute__ ((noipa)) uint32_t \
  NAME (const A *a, const B *b, unsigned int n) \
  { \
    uint32_t sum = 0; \
    for (unsigned int i = 0; i < n; ++i) \
      sum += (PRODUCT) a[i] * b[i]; \
    return sum; \
  }

DOT16 (dot16_ss, int16_t, int16_t, int32_t)
DOT16 (dot16_uu, uint16_t, uint16_t, uint32_t)
DOT16 (dot16_us, uint16_t, int16_t, int32_t)

#undef DOT16
