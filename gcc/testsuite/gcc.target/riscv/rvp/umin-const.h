#include <stdint.h>

typedef uint16_t u16x2 __attribute__ ((vector_size (4)));
typedef uint16_t u16x4 __attribute__ ((vector_size (8)));
typedef uint32_t u32x2 __attribute__ ((vector_size (8)));

#define UMIN(NAME, VEC, ELEM, N) \
  __attribute__ ((noipa)) void \
  NAME (ELEM *restrict dst, const ELEM *restrict src) \
  { \
    VEC value, bound; \
    src = __builtin_assume_aligned (src, 8); \
    dst = __builtin_assume_aligned (dst, 8); \
    __builtin_memcpy (&value, src, sizeof value); \
    for (unsigned int i = 0; i < N; ++i) \
      bound[i] = 255; \
    VEC mask = value > bound; \
    VEC result = (mask & bound) | (~mask & value); \
    __builtin_memcpy (dst, &result, sizeof result); \
  }

UMIN (umin16x2, u16x2, uint16_t, 2)
UMIN (umin16x4, u16x4, uint16_t, 4)
UMIN (umin32x2, u32x2, uint32_t, 2)

#undef UMIN
