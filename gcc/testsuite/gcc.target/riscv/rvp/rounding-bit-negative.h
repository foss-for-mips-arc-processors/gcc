#include <stdint.h>

typedef int16_t s16x2 __attribute__ ((vector_size (4)));
typedef int16_t s16x4 __attribute__ ((vector_size (8)));
typedef int32_t s32x2 __attribute__ ((vector_size (8)));

#define TEST(T, NAME) \
  T __attribute__ ((noipa)) wrong_bit_##NAME (T x) \
  { return (x >> 4) + ((x >> 4) & 1); } \
  T __attribute__ ((noipa)) wrong_mask_##NAME (T x) \
  { return (x >> 4) + ((x >> 3) & 2); } \
  T __attribute__ ((noipa)) other_bit_##NAME (T x, T y) \
  { return (x >> 4) + ((y >> 3) & 1); }

TEST (intptr_t, native)
TEST (s16x2, s16x2)
TEST (s16x4, s16x4)
TEST (s32x2, s32x2)

#undef TEST
