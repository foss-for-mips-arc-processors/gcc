#include <stdint.h>

#define TEST(S, SIZE, N) \
  typedef S N __attribute__ ((vector_size (SIZE))); \
  N __attribute__ ((noipa)) wrong_bit_##N (N x) \
  { return (x >> 1) + ((x >> 1) & 1); } \
  N __attribute__ ((noipa)) wrong_mask_##N (N x) \
  { return (x >> 1) + (x & 2); } \
  N __attribute__ ((noipa)) other_bit_##N (N x, N y) \
  { return (x >> 1) + (y & 1); } \
  void __attribute__ ((noipa)) shared_##N (N *r, N x) \
  { \
    N q = x >> 1, bit = x & 1; \
    r[0] = q; r[1] = bit; r[2] = q + bit; \
  }

TEST (int8_t, 4, b4)
TEST (int16_t, 4, h2)
TEST (int8_t, 8, b8)
TEST (int16_t, 8, h4)
TEST (int32_t, 8, w2)

#undef TEST
