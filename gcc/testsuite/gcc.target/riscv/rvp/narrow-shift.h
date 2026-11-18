#include <stdint.h>

typedef uint8_t u8x4 __attribute__ ((vector_size (4)));
typedef int8_t s8x4 __attribute__ ((vector_size (4)));
typedef uint16_t u16x2 __attribute__ ((vector_size (4)));
typedef int16_t s16x2 __attribute__ ((vector_size (4)));
typedef uint16_t u16x4 __attribute__ ((vector_size (8)));
typedef int16_t s16x4 __attribute__ ((vector_size (8)));
typedef uint32_t u32x2 __attribute__ ((vector_size (8)));
typedef int32_t s32x2 __attribute__ ((vector_size (8)));

#define NARROW_SHIFT(NAME, TO, FROM, SHIFT) \
  __attribute__ ((noipa)) TO \
  NAME##_##SHIFT (FROM x) \
  { \
    return __builtin_convertvector (x >> SHIFT, TO); \
  }

#define BYTE_SHIFTS(M, NAME, TO, FROM) \
  M (NAME, TO, FROM, 0) \
  M (NAME, TO, FROM, 1) \
  M (NAME, TO, FROM, 7) \
  M (NAME, TO, FROM, 8) \
  M (NAME, TO, FROM, 9) \
  M (NAME, TO, FROM, 15)

#define HALF_SHIFTS(M, NAME, TO, FROM) \
  M (NAME, TO, FROM, 0) \
  M (NAME, TO, FROM, 1) \
  M (NAME, TO, FROM, 15) \
  M (NAME, TO, FROM, 16) \
  M (NAME, TO, FROM, 17) \
  M (NAME, TO, FROM, 31)

BYTE_SHIFTS (NARROW_SHIFT, narrow_u16, u8x4, u16x4)
BYTE_SHIFTS (NARROW_SHIFT, narrow_s16, s8x4, s16x4)
HALF_SHIFTS (NARROW_SHIFT, narrow_u32, u16x2, u32x2)
HALF_SHIFTS (NARROW_SHIFT, narrow_s32, s16x2, s32x2)

#undef HALF_SHIFTS
#undef BYTE_SHIFTS
#undef NARROW_SHIFT
