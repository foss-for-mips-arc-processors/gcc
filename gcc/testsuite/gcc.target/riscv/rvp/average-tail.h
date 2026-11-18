#define TEST(TYPE, WIDE, NAME, OP) \
  void __attribute__ ((noipa)) \
  NAME (TYPE *restrict d, const TYPE *restrict a, \
	const TYPE *restrict b, unsigned n) \
  { \
    d = __builtin_assume_aligned (d, 8); \
    a = __builtin_assume_aligned (a, 8); \
    b = __builtin_assume_aligned (b, 8); \
    for (unsigned i = 0; i < n; ++i) \
      d[i] = ((WIDE) a[i] OP b[i]) >> 1; \
  }

TEST (signed char, long long, average_add_s8, +)
TEST (unsigned char, unsigned long long, average_add_u8, +)
TEST (signed char, long long, average_sub_s8, -)
TEST (unsigned char, unsigned long long, average_sub_u8, -)
