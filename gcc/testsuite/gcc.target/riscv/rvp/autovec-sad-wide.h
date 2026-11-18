typedef unsigned int sad_u32;
typedef unsigned long long sad_u64;

#define SAD_WIDE(NAME, INPUT, SUM) \
SUM __attribute__ ((noipa)) \
NAME (const INPUT *a, const INPUT *b, unsigned int n) \
{ \
  SUM sum = 0; \
  for (unsigned int i = 0; i < n; ++i) \
    sum += __builtin_abs ((int) a[i] - (int) b[i]); \
  return sum; \
} \
SUM __attribute__ ((noipa)) \
NAME##_aligned (const INPUT *a, const INPUT *b, unsigned int n) \
{ \
  a = __builtin_assume_aligned (a, 8); \
  b = __builtin_assume_aligned (b, 8); \
  SUM sum = 0; \
  for (unsigned int i = 0; i < n; ++i) \
    sum += __builtin_abs ((int) a[i] - (int) b[i]); \
  return sum; \
} \
SUM __attribute__ ((noipa)) \
NAME##_seed (const INPUT *a, const INPUT *b, unsigned int n, SUM sum) \
{ \
  for (unsigned int i = 0; i < n; ++i) \
    sum += __builtin_abs ((int) a[i] - (int) b[i]); \
  return sum; \
} \
SUM __attribute__ ((noipa)) \
NAME##_fixed (const INPUT *a, const INPUT *b) \
{ \
  SUM sum = 0; \
  for (unsigned int i = 0; i < 16; ++i) \
    sum += __builtin_abs ((int) a[i] - (int) b[i]); \
  return sum; \
} \
void __attribute__ ((noipa)) \
NAME##_pair (const INPUT *a, const INPUT *b, unsigned int n, \
	     SUM *out, SUM x, SUM y) \
{ \
  for (unsigned int i = 0; i < n; ++i) \
    { \
      x += __builtin_abs ((int) a[2 * i] - (int) b[2 * i]); \
      y += __builtin_abs ((int) a[2 * i + 1] - (int) b[2 * i + 1]); \
    } \
  out[0] = x; \
  out[1] = y; \
} \
SUM __attribute__ ((noipa)) \
NAME##_chain (const INPUT *a, const INPUT *b, unsigned int n, SUM sum) \
{ \
  for (unsigned int i = 0; i < n; ++i) \
    { \
      sum += __builtin_abs ((int) a[i] - (int) b[i]); \
      sum += (unsigned char) a[i]; \
    } \
  return sum; \
}

SAD_WIDE (u8_32, unsigned char, sad_u32)
SAD_WIDE (u8_64, unsigned char, sad_u64)
SAD_WIDE (i8_32, signed char, sad_u32)
SAD_WIDE (i8_64, signed char, sad_u64)
SAD_WIDE (u16_32, unsigned short, sad_u32)
SAD_WIDE (u16_64, unsigned short, sad_u64)
SAD_WIDE (i16_32, short, sad_u32)
SAD_WIDE (i16_64, short, sad_u64)

#define SAD_CONTROL(NAME, TYPE) \
sad_u64 __attribute__ ((noipa)) \
NAME (const TYPE *a, const TYPE *b, unsigned int n) \
{ \
  sad_u64 sum = 0; \
  for (unsigned int i = 0; i < n; ++i) \
    sum += __builtin_llabs ((long long) a[i] - (long long) b[i]); \
  return sum; \
}

SAD_CONTROL (u32_control, unsigned int)
SAD_CONTROL (i32_control, int)
