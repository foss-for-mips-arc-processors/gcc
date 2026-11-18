#define TEST(T, SIZE, NAME) \
  typedef T NAME __attribute__ ((vector_size (SIZE))); \
  NAME __attribute__ ((noipa)) \
  xor_##NAME (NAME a, NAME b) \
  { return (a & b) + ((a ^ b) >> 1); } \
  NAME __attribute__ ((noipa)) \
  carry_##NAME (NAME a, NAME b) \
  { return (a >> 1) + (b >> 1) + ((a & b) & 1); } \
  NAME __attribute__ ((noipa)) \
  swap_##NAME (NAME a, NAME b) \
  { return ((b ^ a) >> 1) + (a & b); }

TEST (signed char, 4, s8x4)
TEST (unsigned char, 4, u8x4)
TEST (short, 4, s16x2)
TEST (unsigned short, 4, u16x2)
TEST (signed char, 8, s8x8)
TEST (unsigned char, 8, u8x8)
TEST (short, 8, s16x4)
TEST (unsigned short, 8, u16x4)
TEST (int, 8, s32x2)
TEST (unsigned int, 8, u32x2)
