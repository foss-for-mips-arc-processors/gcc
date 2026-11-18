#include <stdint.h>

#define DOT(NAME, TYPE, A, B) \
  __attribute__ ((noinline, noclone)) TYPE \
  NAME (const A *a, const B *b, unsigned n) \
  { \
    TYPE sum = 0; \
    for (unsigned i = 0; i < n; ++i) \
      sum += (TYPE) a[i] * b[i]; \
    return sum; \
  }

DOT (dot_ss, int32_t, int8_t, int8_t)
DOT (dot_uu, uint32_t, uint8_t, uint8_t)
DOT (dot_us, int32_t, uint8_t, int8_t)

#undef DOT

__attribute__ ((noinline, noclone)) int32_t
sum_s16 (const int16_t *a, unsigned n)
{
  int32_t sum = 0;
  for (unsigned i = 0; i < n; ++i)
    sum += a[i];
  return sum;
}
