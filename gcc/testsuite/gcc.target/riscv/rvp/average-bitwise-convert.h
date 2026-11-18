#define TEST(TYPE, NAME) \
  void __attribute__ ((noipa)) xor_##NAME \
    (TYPE *restrict d, const TYPE *restrict a, const TYPE *restrict b, \
     unsigned int n) \
  { \
    for (unsigned int i = 0; i < n; ++i) \
      d[i] = (a[i] & b[i]) + ((a[i] ^ b[i]) >> 1); \
  } \
  void __attribute__ ((noipa)) carry_##NAME \
    (TYPE *restrict d, const TYPE *restrict a, const TYPE *restrict b, \
     unsigned int n) \
  { \
    for (unsigned int i = 0; i < n; ++i) \
      d[i] = (a[i] >> 1) + (b[i] >> 1) + ((a[i] & b[i]) & 1); \
  } \
  void __attribute__ ((noipa)) swap_##NAME \
    (TYPE *restrict d, const TYPE *restrict a, const TYPE *restrict b, \
     unsigned int n) \
  { \
    for (unsigned int i = 0; i < n; ++i) \
      d[i] = ((b[i] ^ a[i]) >> 1) + (a[i] & b[i]); \
  }

TEST (signed char, s8)
TEST (short, s16)

#undef TEST
