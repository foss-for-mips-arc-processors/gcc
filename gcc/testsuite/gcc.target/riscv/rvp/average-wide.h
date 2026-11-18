#define TEST(TYPE, WIDE, NAME, N, OP, SUFFIX) \
  typedef TYPE NAME __attribute__ ((vector_size (N * sizeof (TYPE)))); \
  NAME __attribute__ ((noipa)) \
  NAME##_##SUFFIX (NAME a, NAME b) \
  { \
    NAME r; \
    for (unsigned int i = 0; i < N; ++i) \
      r[i] = ((WIDE) a[i] OP (WIDE) b[i]) >> 1; \
    return r; \
  }

#define TEST_TYPE(TYPE, WIDE, NAME, N) \
  TEST (TYPE, WIDE, NAME, N, +, add) \
  TEST (TYPE, WIDE, NAME, N, -, sub)

TEST_TYPE (signed char, int, s8x4, 4)
TEST_TYPE (signed char, int, s8x8, 8)
TEST_TYPE (short, int, s16x2, 2)
TEST_TYPE (short, int, s16x4, 4)
TEST_TYPE (int, long long, s32x2, 2)
TEST_TYPE (unsigned char, unsigned int, u8x4, 4)
TEST_TYPE (unsigned char, unsigned int, u8x8, 8)
TEST_TYPE (unsigned short, unsigned int, u16x2, 2)
TEST_TYPE (unsigned short, unsigned int, u16x4, 4)
TEST_TYPE (unsigned int, unsigned long long, u32x2, 2)
