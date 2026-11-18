#define TEST(TYPE, NAME, SIZE) \
  typedef TYPE NAME __attribute__ ((vector_size (SIZE))); \
  NAME __attribute__ ((noipa)) select_or_##NAME (NAME a, NAME b, NAME m) \
  { return (a & m) | (b & ~m); } \
  NAME __attribute__ ((noipa)) select_xor_##NAME (NAME a, NAME b, NAME m) \
  { return b ^ ((a ^ b) & m); } \
  NAME __attribute__ ((noipa)) select_inv_##NAME (NAME a, NAME b, NAME m) \
  { return (b & m) | (a & ~m); } \
  NAME __attribute__ ((noipa)) select_xinv_##NAME (NAME a, NAME b, NAME m) \
  { return a ^ ((a ^ b) & m); }

TEST (unsigned char, u8x4, 4)
TEST (unsigned short, u16x2, 4)
TEST (unsigned char, u8x8, 8)
TEST (unsigned short, u16x4, 8)
TEST (unsigned int, u32x2, 8)

#undef TEST
