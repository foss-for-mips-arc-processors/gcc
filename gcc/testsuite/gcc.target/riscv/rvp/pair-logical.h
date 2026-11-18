#define TEST(TYPE, NAME) \
  typedef TYPE NAME __attribute__ ((vector_size (8))); \
  NAME __attribute__ ((noipa)) and_##NAME (NAME a, NAME b) \
  { return a & b; } \
  NAME __attribute__ ((noipa)) or_##NAME (NAME a, NAME b) \
  { return a | b; } \
  NAME __attribute__ ((noipa)) xor_##NAME (NAME a, NAME b) \
  { return a ^ b; }

TEST (unsigned char, u8x8)
TEST (unsigned short, u16x4)
TEST (unsigned int, u32x2)
