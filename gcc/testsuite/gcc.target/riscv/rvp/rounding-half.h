#include <stdint.h>

#define TEST(S, U, SIZE, N) \
  typedef S s##N __attribute__ ((vector_size (SIZE))); \
  typedef U u##N __attribute__ ((vector_size (SIZE))); \
  s##N __attribute__ ((noipa)) half_s_##N (s##N x) \
  { return (x >> 1) + (x & 1); } \
  u##N __attribute__ ((noipa)) half_u_##N (u##N x) \
  { return (x >> 1) + (x & 1); } \
  u##N __attribute__ ((noipa)) half_c_##N (s##N x) \
  { return (u##N) (x >> 1) + ((u##N) x & 1); }

TEST (int8_t, uint8_t, 4, b4)
TEST (int16_t, uint16_t, 4, h2)
TEST (int8_t, uint8_t, 8, b8)
TEST (int16_t, uint16_t, 8, h4)
TEST (int32_t, uint32_t, 8, w2)

#undef TEST
