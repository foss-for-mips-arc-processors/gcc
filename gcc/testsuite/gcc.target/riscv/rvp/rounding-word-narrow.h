#include <stdint.h>

#define WORD_SHIFTS(M) \
  M (1) M (2) M (3) M (4) M (5) M (6) M (7) M (8) M (9) M (10) \
  M (11) M (12) M (13) M (14) M (15) M (16) M (17) M (18) M (19) M (20) \
  M (21) M (22) M (23) M (24) M (25) M (26) M (27) M (28) M (29) M (30) \
  M (31) M (32) M (33) M (34) M (35) M (36) M (37) M (38) M (39) M (40) \
  M (41) M (42) M (43) M (44) M (45) M (46) M (47) M (48) M (49) M (50) \
  M (51) M (52) M (53) M (54) M (55) M (56) M (57) M (58) M (59) M (60) \
  M (61) M (62) M (63)

#ifdef TEST_DRIVER_ONLY
#define TEST(K) extern int32_t narrow_##K (int64_t);
#else
/* Unsigned word addition defines the wrapping controls for K <= 32.  */
#define TEST(K) \
  int32_t __attribute__ ((noipa)) narrow_##K (int64_t x) \
  { \
    uint32_t q = x >> K; \
    uint32_t bit = ((uint64_t) x >> (K - 1)) & 1; \
    return q + bit; \
  }
#endif
WORD_SHIFTS (TEST)
#undef TEST
