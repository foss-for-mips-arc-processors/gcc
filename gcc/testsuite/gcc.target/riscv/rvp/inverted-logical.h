#define TEST(TYPE, NAME, SIZE) \
  typedef TYPE NAME __attribute__ ((vector_size (SIZE))); \
  NAME __attribute__ ((noipa)) andn_##NAME (NAME a, NAME b) \
  { return ~a & b; } \
  NAME __attribute__ ((noipa)) orn_##NAME (NAME a, NAME b) \
  { return ~a | b; } \
  NAME __attribute__ ((noipa)) xnor_##NAME (NAME a, NAME b) \
  { return ~(a ^ b); } \
  NAME __attribute__ ((noipa)) andn_alt_##NAME (NAME a, NAME b) \
  { return b & ~a; } \
  NAME __attribute__ ((noipa)) orn_alt_##NAME (NAME a, NAME b) \
  { return b | ~a; } \
  NAME __attribute__ ((noipa)) xnor_alt_##NAME (NAME a, NAME b) \
  { return ~a ^ b; }

TEST (unsigned char, u8x4, 4)
TEST (unsigned short, u16x2, 4)
TEST (unsigned char, u8x8, 8)
TEST (unsigned short, u16x4, 8)
TEST (unsigned int, u32x2, 8)

#undef TEST
