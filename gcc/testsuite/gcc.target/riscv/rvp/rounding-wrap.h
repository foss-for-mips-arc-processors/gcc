#include <stdint.h>

__attribute__ ((noipa)) intptr_t
wrap_signed (intptr_t x)
{
  return (x + 8) >> 4;
}

__attribute__ ((noipa)) intptr_t
wrap_unsigned (uintptr_t x)
{
  return (intptr_t) (x + 8) >> 4;
}

__attribute__ ((noipa)) intptr_t
wrap_max_shift (uintptr_t x)
{
  const unsigned int shift = sizeof (uintptr_t) * 8 - 1;
  return (intptr_t) (x + ((uintptr_t) 1 << (shift - 1))) >> shift;
}

__attribute__ ((noipa)) int32_t
wrap_word (uint32_t x)
{
  return (int32_t) (x + 8) >> 4;
}
