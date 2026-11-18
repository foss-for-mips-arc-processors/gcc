#include <stdint.h>

void
sat_sub_trunc (uint8_t *restrict dst, const uint16_t *restrict x,
	       const uint16_t *restrict y, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      uint16_t a = x[i];
      uint16_t b = y[i];
      uint8_t d = (uint8_t) a - (uint8_t) b;
      dst[i] = a >= b ? d : 0;
    }
}
