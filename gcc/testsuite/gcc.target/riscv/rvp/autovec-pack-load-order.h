#include <stdint.h>

/* The unknown store can overlap either half of the source.  Its ordering
   must not be lost by combining the two source loads.  */
#define PACK(NAME, LOW, HIGH) \
  void __attribute__ ((noipa)) \
  NAME (uint8_t *dst, const uint16_t *src, uint16_t *write, uint16_t value) \
  { \
    dst = __builtin_assume_aligned (dst, 8); \
    src = __builtin_assume_aligned (src, 8); \
    uint16_t a = src[0]; \
    uint16_t b = src[1]; \
    *write = value; \
    uint16_t c = src[2]; \
    uint16_t d = src[3]; \
    dst[0] = a <= LOW ? a : LOW; \
    dst[1] = b <= LOW ? b : LOW; \
    dst[2] = c <= HIGH ? c : HIGH; \
    dst[3] = d <= HIGH ? d : HIGH; \
  }

PACK (pack_store_plain, 65535, 65535)
PACK (pack_store_sat, 255, 255)
PACK (pack_store_mixed, 255, 254)

#undef PACK
