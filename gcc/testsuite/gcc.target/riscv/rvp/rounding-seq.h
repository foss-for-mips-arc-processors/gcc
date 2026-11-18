#include <stdint.h>

__attribute__ ((noipa)) intptr_t
round_one (intptr_t x)
{
  return (x >> 1) + (x & 1);
}

#define ROUND_SEQ(NAME, SHIFT) \
  __attribute__ ((noipa)) intptr_t NAME (intptr_t x) \
  { return ((x >> ((SHIFT) - 1)) + 1) >> 1; }

ROUND_SEQ (round_two, 2)
ROUND_SEQ (round_four, 4)
ROUND_SEQ (round_sixteen, 16)
ROUND_SEQ (round_max, sizeof (intptr_t) * 8 - 1)

#undef ROUND_SEQ
