#define TEST(TYPE, NAME) \
  void NAME (TYPE *restrict d, const TYPE *restrict a, \
	     const TYPE *restrict b, unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      d[i] = a[i] & b[i]; \
  }

TEST (unsigned char, and_bytes)
TEST (unsigned short, and_halfwords)

#undef TEST
