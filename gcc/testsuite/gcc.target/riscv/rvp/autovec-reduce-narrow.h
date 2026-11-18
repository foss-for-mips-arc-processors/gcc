#include <stdint.h>

typedef uint16_t u16x2 __attribute__ ((vector_size (4)));

__attribute__ ((noipa)) uint8_t
reduce_bytes4 (const uint8_t *src)
{
  src = (const uint8_t *) __builtin_assume_aligned (src, 4);
  uint8_t sum = 0;
  for (unsigned int i = 0; i < 4; ++i)
    sum += src[i];
  return sum;
}

__attribute__ ((noipa)) uint16_t
reduce_halves2 (u16x2 src)
{
  return src[0] + src[1];
}
