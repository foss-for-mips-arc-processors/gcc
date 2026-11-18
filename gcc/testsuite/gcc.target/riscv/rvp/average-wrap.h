#define TEST(SIGNED, UNSIGNED, NAME, N) \
  typedef SIGNED s##NAME __attribute__ ((vector_size (N * sizeof (SIGNED)))); \
  typedef UNSIGNED u##NAME \
    __attribute__ ((vector_size (N * sizeof (UNSIGNED)))); \
  s##NAME __attribute__ ((noipa)) \
  add_s##NAME (s##NAME a, s##NAME b) \
  { return (s##NAME) ((u##NAME) a + (u##NAME) b) >> 1; } \
  s##NAME __attribute__ ((noipa)) \
  sub_s##NAME (s##NAME a, s##NAME b) \
  { return (s##NAME) ((u##NAME) a - (u##NAME) b) >> 1; } \
  u##NAME __attribute__ ((noipa)) \
  add_u##NAME (u##NAME a, u##NAME b) \
  { return (a + b) >> 1; } \
  u##NAME __attribute__ ((noipa)) \
  sub_u##NAME (u##NAME a, u##NAME b) \
  { return (a - b) >> 1; }

TEST (signed char, unsigned char, 8x4, 4)
TEST (signed char, unsigned char, 8x8, 8)
TEST (short, unsigned short, 16x2, 2)
TEST (short, unsigned short, 16x4, 4)
TEST (int, unsigned int, 32x2, 2)
