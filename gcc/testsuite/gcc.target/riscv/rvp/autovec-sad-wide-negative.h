#define NARROW_SAD(NAME, INPUT, NARROW) \
unsigned long long __attribute__ ((noipa)) \
NAME (const INPUT *a, const INPUT *b, unsigned int n) \
{ \
  unsigned long long sum = 0; \
  for (unsigned int i = 0; i < n; ++i) \
    { \
      NARROW diff = (NARROW) ((int) a[i] - (int) b[i]); \
      sum += __builtin_abs ((int) diff); \
    } \
  return sum; \
}

NARROW_SAD (narrow_u8, unsigned char, signed char)
NARROW_SAD (narrow_i8, signed char, signed char)
NARROW_SAD (narrow_u16, unsigned short, short)
NARROW_SAD (narrow_i16, short, short)
