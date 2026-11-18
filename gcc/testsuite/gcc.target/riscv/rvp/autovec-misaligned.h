#include <riscv_packed_simd.h>

#define MOVE(NAME, TYPE) \
  __attribute__ ((noinline, noclone)) TYPE \
  load_##NAME (const void *src) \
  { \
    TYPE value; \
    __builtin_memcpy (&value, src, sizeof value); \
    return value; \
  } \
  __attribute__ ((noinline, noclone)) void \
  store_##NAME (void *dst, TYPE value) \
  { \
    __builtin_memcpy (dst, &value, sizeof value); \
  }

MOVE (b4, uint8x4_t)
MOVE (h2, uint16x2_t)
MOVE (b8, uint8x8_t)
MOVE (h4, uint16x4_t)
MOVE (w2, uint32x2_t)

#undef MOVE
