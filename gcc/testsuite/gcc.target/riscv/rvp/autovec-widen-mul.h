#include <stdint.h>

#define WIDEN_MUL(NAME, TO, FROM) \
  __attribute__ ((noipa)) void \
  NAME (TO *restrict r, const FROM *a, const FROM *b, unsigned int n) \
  { \
    for (unsigned int i = 0; i < n; ++i) \
      r[i] = (TO) a[i] * b[i]; \
  }

WIDEN_MUL (mul_s8, int16_t, int8_t)
WIDEN_MUL (mul_u8, uint16_t, uint8_t)
WIDEN_MUL (mul_s16, int32_t, int16_t)
WIDEN_MUL (mul_u16, uint32_t, uint16_t)

#undef WIDEN_MUL

__attribute__ ((noipa)) void
mul_q15 (int16_t *restrict r, const int16_t *a, const int16_t *b,
	 unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      int32_t product = ((int32_t) a[i] * b[i]) >> 15;
      r[i] = product > INT16_MAX ? INT16_MAX : product;
    }
}
