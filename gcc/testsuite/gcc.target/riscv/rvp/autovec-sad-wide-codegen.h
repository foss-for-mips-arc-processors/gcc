#define SAD_FIXED(NAME, INPUT, SUM) \
SUM __attribute__ ((noipa)) \
NAME (const INPUT *a, const INPUT *b) \
{ \
  a = __builtin_assume_aligned (a, 8); \
  b = __builtin_assume_aligned (b, 8); \
  SUM sum = 0; \
  for (unsigned int i = 0; i < 128; ++i) \
    sum += __builtin_abs ((int) a[i] - (int) b[i]); \
  return sum; \
}

SAD_FIXED (sad_i8_word, signed char, unsigned int)
SAD_FIXED (sad_i8_doubleword, signed char, unsigned long long)
SAD_FIXED (sad_u16_word, unsigned short, unsigned int)
SAD_FIXED (sad_u16_doubleword, unsigned short, unsigned long long)
SAD_FIXED (sad_i16_word, short, unsigned int)
SAD_FIXED (sad_i16_doubleword, short, unsigned long long)
