#include <stdint.h>

typedef int16_t s16x2 __attribute__ ((vector_size (4)));
typedef uint16_t u16x2 __attribute__ ((vector_size (4)));
typedef int16_t s16x4 __attribute__ ((vector_size (8)));
typedef uint16_t u16x4 __attribute__ ((vector_size (8)));
typedef int32_t s32x2 __attribute__ ((vector_size (8)));
typedef uint32_t u32x2 __attribute__ ((vector_size (8)));

#define TEST(T, U, NAME, LABEL, K) \
  T __attribute__ ((noipa)) bit_##NAME##_##LABEL (T x) \
  { return (x >> K) + ((x >> ((K) - 1)) & 1); } \
  T __attribute__ ((noipa)) ubit_##NAME##_##LABEL (T x) \
  { return (x >> K) + (((U) x >> ((K) - 1)) & 1); }

#define SHIFTS(T, U, NAME, LAST) \
  TEST (T, U, NAME, one, 1) \
  TEST (T, U, NAME, two, 2) \
  TEST (T, U, NAME, four, 4) \
  TEST (T, U, NAME, max, LAST)

SHIFTS (intptr_t, uintptr_t, native, __riscv_xlen - 1)
SHIFTS (s16x2, u16x2, s16x2, 15)
SHIFTS (s16x4, u16x4, s16x4, 15)
SHIFTS (s32x2, u32x2, s32x2, 31)

#undef TEST
#undef SHIFTS
