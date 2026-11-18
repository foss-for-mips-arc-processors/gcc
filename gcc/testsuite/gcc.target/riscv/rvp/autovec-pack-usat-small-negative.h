#include <stdint.h>

/* Neither adjacent bounds nor unequal bounds on the two input halves are
   an unsigned byte-saturating pack.  */
#define PACK(NAME, LOW, HIGH) \
  void __attribute__ ((noipa)) \
  NAME (uint8_t *restrict dst, const uint16_t *restrict src) \
  { \
    dst = __builtin_assume_aligned (dst, 8); \
    src = __builtin_assume_aligned (src, 8); \
    for (unsigned int i = 0; i < 4; ++i) \
      { \
	uint16_t bound = i < 2 ? LOW : HIGH; \
	uint16_t value = src[i]; \
	if (value > bound) \
	  value = bound; \
	dst[i] = value; \
      } \
  }

PACK (pack_four_near, 254, 254)
PACK (pack_four_outer, 256, 256)
PACK (pack_four_mixed, 255, 254)
PACK (pack_four_mixed_reverse, 254, 255)

#undef PACK
