#include <stdint.h>

/* Neither a neighbouring bias nor a scaled product is MULHR.  */
#define ROUND_CONTROL(NAME, BIAS, SHIFT) \
  int32_t __attribute__ ((noipa)) \
  NAME (int32_t a, int32_t b) \
  { \
    return ((int64_t) a * b + (BIAS)) >> (SHIFT); \
  }

ROUND_CONTROL (bias_low, INT64_C (2147483647), 32)
ROUND_CONTROL (bias_high, INT64_C (2147483649), 32)
ROUND_CONTROL (shift_low, INT64_C (2147483648), 31)
ROUND_CONTROL (shift_high, INT64_C (2147483648), 33)

uint64_t __attribute__ ((noipa))
full_product (uint32_t a, uint32_t b)
{
  return (uint64_t) a * b + UINT64_C (2147483648);
}

uint32_t __attribute__ ((noipa))
wide_inputs (uint64_t a, uint64_t b)
{
  return (a * b + UINT64_C (2147483648)) >> 32;
}

uint32_t __attribute__ ((noipa))
range_33 (uint32_t a, uint32_t b)
{
  uint64_t x = (uint64_t) a + 1;
  uint64_t y = (uint64_t) b + 1;
  return (x * y + UINT64_C (2147483648)) >> 32;
}

int16_t __attribute__ ((noipa))
q15 (int16_t a, int16_t b)
{
  int32_t p = ((int32_t) a * b + 16384) >> 15;
  return p > 32767 ? 32767 : p;
}
