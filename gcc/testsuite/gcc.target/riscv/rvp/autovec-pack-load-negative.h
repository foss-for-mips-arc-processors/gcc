#include <stdint.h>

/* None of these source pairs can be replaced by one aligned PV4HI load.  */
#define PACK(NAME, ALIGN, KIND) \
  void __attribute__ ((noipa)) \
  NAME (uint8_t *restrict dst, const uint16_t *restrict a, \
	const uint16_t *restrict b) \
  { \
    dst = __builtin_assume_aligned (dst, 8); \
    a = __builtin_assume_aligned (a, ALIGN); \
    b = __builtin_assume_aligned (b, ALIGN); \
    for (unsigned int i = 0; i < 4; ++i) \
      { \
	uint16_t value; \
	if (KIND == 1) \
	  value = a[i ^ 2]; \
	else if (KIND == 2) \
	  value = i < 2 ? a[i] : b[i - 2]; \
	else if (KIND == 3) \
	  value = ((const volatile uint16_t *) a)[i]; \
	else if (KIND == 4) \
	  value = __atomic_load_n (a + i, __ATOMIC_RELAXED); \
	else \
	  value = a[i]; \
	dst[i] = value < 256 ? value : 255; \
      } \
  }

PACK (pack_low_alignment, 4, 0)
PACK (pack_reversed, 8, 1)
PACK (pack_separate, 8, 2)
PACK (pack_volatile, 8, 3)
PACK (pack_atomic, 8, 4)

#undef PACK
