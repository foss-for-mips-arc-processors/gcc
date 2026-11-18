#define TEST(TYPE, NAME) \
  void __attribute__ ((noipa)) select_loop_unrelated_##NAME \
    (TYPE *restrict d, const TYPE *restrict a, const TYPE *restrict b, \
     const TYPE *restrict m, const TYPE *restrict other, unsigned int n) \
  { \
    for (unsigned int i = 0; i < n; ++i) \
      d[i] = (a[i] & m[i]) | (b[i] & ~other[i]); \
  }

TEST (unsigned char, 8)
TEST (unsigned short, 16)
TEST (unsigned int, 32)

#undef TEST
