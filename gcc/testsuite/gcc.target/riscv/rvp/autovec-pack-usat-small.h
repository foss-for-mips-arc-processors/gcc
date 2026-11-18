#include <stdint.h>

void __attribute__ ((noipa))
pack_four_unsigned (uint8_t *restrict dst, const uint16_t *restrict src)
{
  dst = __builtin_assume_aligned (dst, 8);
  src = __builtin_assume_aligned (src, 8);
  for (unsigned int i = 0; i < 4; ++i)
    {
      uint16_t value = src[i];
      if (value > 255)
	value = 255;
      dst[i] = value;
    }
}
