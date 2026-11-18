#define TEST(TYPE, NAME) \
  void __attribute__ ((noipa)) andn_##NAME \
    (TYPE *restrict d, const TYPE *restrict a, const TYPE *restrict b, \
     unsigned int n) \
  { for (unsigned int i = 0; i < n; ++i) d[i] = ~a[i] & b[i]; } \
  void __attribute__ ((noipa)) orn_##NAME \
    (TYPE *restrict d, const TYPE *restrict a, const TYPE *restrict b, \
     unsigned int n) \
  { for (unsigned int i = 0; i < n; ++i) d[i] = ~a[i] | b[i]; } \
  void __attribute__ ((noipa)) xnor_##NAME \
    (TYPE *restrict d, const TYPE *restrict a, const TYPE *restrict b, \
     unsigned int n) \
  { for (unsigned int i = 0; i < n; ++i) d[i] = ~(a[i] ^ b[i]); }

TEST (unsigned char, u8)
TEST (unsigned short, u16)
TEST (unsigned int, u32)

#undef TEST
