#define SAD_FIXED(NAME, TYPE) \
TYPE __attribute__ ((noipa)) \
NAME (const unsigned char *a, const unsigned char *b) \
{ \
  a = __builtin_assume_aligned (a, 8); \
  b = __builtin_assume_aligned (b, 8); \
  TYPE sum = 0; \
  for (unsigned int i = 0; i < 128; ++i) \
    sum += __builtin_abs ((int) a[i] - (int) b[i]); \
  return sum; \
}

SAD_FIXED (sad_word, unsigned int)
SAD_FIXED (sad_doubleword, unsigned long long)
