#include <stdint.h>

#define NOIPA __attribute__ ((noipa))

#ifndef TEST_NEGATIVE_ONLY
NOIPA int32_t
word_bit (int32_t x)
{
  return (x >> 1) + (x & 1);
}

NOIPA int64_t
word_wide_result (int32_t x)
{
  return (x >> 1) + (x & 1);
}

NOIPA uint64_t
word_unsigned_result (int32_t x)
{
  return (uint32_t) ((x >> 1) + (x & 1));
}

NOIPA int32_t
word_low (uint64_t x)
{
  int32_t y = x;
  return (y >> 1) + (y & 1);
}

NOIPA int32_t
word_high (uint64_t x)
{
  int32_t y = x >> 32;
  return (y >> 1) + (y & 1);
}

NOIPA int32_t
word_load (const int32_t *x)
{
  int32_t y = *x;
  return (y >> 1) + (y & 1);
}

NOIPA int32_t
word_sum (uint32_t x, uint32_t y)
{
  int32_t z = x + y;
  return (z >> 1) + (z & 1);
}

NOIPA int32_t
word_product (uint32_t x, uint32_t y)
{
  int32_t z = x * y;
  return (z >> 1) + (z & 1);
}

#endif

#ifndef TEST_POSITIVE_ONLY
NOIPA uint32_t
word_logical (uint32_t x)
{
  return (x >> 1) + (x & 1);
}

NOIPA int64_t
word_extract (uint64_t x)
{
  /* Bit 32 supplies the sign of the extracted word, independently of bit
     31.  It must not be treated as rounding a sign-extended 32-bit input.  */
  return (int32_t) ((uint32_t) (x >> 1) + (uint32_t) (x & 1));
}

NOIPA int32_t
word_other (int32_t x, int32_t y)
{
  return (x >> 1) + (y & 1);
}

NOIPA int32_t
word_wrong_mask (int32_t x)
{
  return (x >> 1) + (x & 2);
}

NOIPA int32_t
word_wrap (uint32_t x)
{
  return (int32_t) (x + 1) >> 1;
}

#endif

#ifndef TEST_NEGATIVE_ONLY
NOIPA void
word_loop (int32_t *restrict dst, const int32_t *restrict src, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    dst[i] = (src[i] >> 1) + (src[i] & 1);
}

NOIPA void
word_low_loop (int32_t *restrict dst, const uint64_t *restrict src, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    {
      int32_t x = src[i];
      dst[i] = (x >> 1) + (x & 1);
    }
}

#endif

#undef NOIPA
