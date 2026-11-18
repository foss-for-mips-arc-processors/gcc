typedef unsigned char sad_u8;
typedef unsigned int sad_u32;
typedef unsigned long long sad_u64;

#define SAD_LOOP(NAME, TYPE, INPUT, ALIGN) \
TYPE __attribute__ ((noipa)) \
NAME (const INPUT *a, const INPUT *b, unsigned int n) \
{ \
  if (ALIGN) \
    { \
      a = __builtin_assume_aligned (a, 8); \
      b = __builtin_assume_aligned (b, 8); \
    } \
  TYPE sum = 0; \
  for (unsigned int i = 0; i < n; ++i) \
    sum += __builtin_abs ((int) a[i] - (int) b[i]); \
  return sum; \
}

SAD_LOOP (sad32, sad_u32, sad_u8, 0)
SAD_LOOP (sad64, sad_u64, sad_u8, 0)
SAD_LOOP (sad32_aligned, sad_u32, sad_u8, 1)
SAD_LOOP (sad64_aligned, sad_u64, sad_u8, 1)
SAD_LOOP (sad_signed_control, sad_u32, signed char, 0)
SAD_LOOP (sad_halfword_control, sad_u32, unsigned short, 0)

#define SAD_MORE(BITS, TYPE) \
TYPE __attribute__ ((noipa)) \
sad##BITS##_seed (const sad_u8 *a, const sad_u8 *b, unsigned int n, TYPE sum) \
{ \
  for (unsigned int i = 0; i < n; ++i) \
    sum += __builtin_abs ((int) a[i] - (int) b[i]); \
  return sum; \
} \
TYPE __attribute__ ((noipa)) \
sad##BITS##_fixed (const sad_u8 *a, const sad_u8 *b) \
{ \
  TYPE sum = 0; \
  for (unsigned int i = 0; i < 16; ++i) \
    sum += __builtin_abs ((int) a[i] - (int) b[i]); \
  return sum; \
} \
void __attribute__ ((noipa)) \
sad##BITS##_pair (const sad_u8 *a, const sad_u8 *b, unsigned int n, \
		 TYPE *out, TYPE x, TYPE y) \
{ \
  for (unsigned int i = 0; i < n; ++i) \
    { \
      x += __builtin_abs ((int) a[2 * i] - (int) b[2 * i]); \
      y += __builtin_abs ((int) a[2 * i + 1] - (int) b[2 * i + 1]); \
    } \
  out[0] = x; \
  out[1] = y; \
} \
TYPE __attribute__ ((noipa)) \
sad##BITS##_chain (const sad_u8 *a, const sad_u8 *b, unsigned int n, TYPE sum) \
{ \
  for (unsigned int i = 0; i < n; ++i) \
    { \
      sum += __builtin_abs ((int) a[i] - (int) b[i]); \
      sum += a[i]; \
    } \
  return sum; \
}

SAD_MORE (32, sad_u32)
SAD_MORE (64, sad_u64)
