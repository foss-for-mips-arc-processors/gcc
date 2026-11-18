/* { dg-do run } */

#include <stdint-gcc.h>

#define SHIFTS31(M, N) \
  M (N, 1) M (N, 2) M (N, 3) M (N, 4) M (N, 5) M (N, 6) M (N, 7) \
  M (N, 8) M (N, 9) M (N, 10) M (N, 11) M (N, 12) M (N, 13) M (N, 14) \
  M (N, 15) M (N, 16) M (N, 17) M (N, 18) M (N, 19) M (N, 20) \
  M (N, 21) M (N, 22) M (N, 23) M (N, 24) M (N, 25) M (N, 26) \
  M (N, 27) M (N, 28) M (N, 29) M (N, 30) M (N, 31)
#define SHIFTS63(M, N) \
  SHIFTS31 (M, N) M (N, 32) M (N, 33) M (N, 34) M (N, 35) M (N, 36) \
  M (N, 37) M (N, 38) M (N, 39) M (N, 40) M (N, 41) M (N, 42) \
  M (N, 43) M (N, 44) M (N, 45) M (N, 46) M (N, 47) M (N, 48) \
  M (N, 49) M (N, 50) M (N, 51) M (N, 52) M (N, 53) M (N, 54) \
  M (N, 55) M (N, 56) M (N, 57) M (N, 58) M (N, 59) M (N, 60) \
  M (N, 61) M (N, 62) M (N, 63)

#define DECL(N, K) void test_##N##_##K (uint##N##_t *, int##N##_t);
SHIFTS31 (DECL, 32)
SHIFTS63 (DECL, 64)

#ifndef TEST_DRIVER_ONLY
#define TEST(N, K) \
  int##N##_t __attribute__ ((noipa)) \
  signed_##N##_##K (int##N##_t x) \
  { return (x >> K) + ((x >> (K - 1)) & 1); } \
  uint##N##_t __attribute__ ((noipa)) \
  converted_##N##_##K (int##N##_t x) \
  { return (uint##N##_t) (x >> K) \
	   + (((uint##N##_t) x >> (K - 1)) & 1); } \
  uint##N##_t __attribute__ ((noipa)) \
  unsigned_##N##_##K (uint##N##_t x) \
  { return (x >> K) + ((x >> (K - 1)) & 1); } \
  void __attribute__ ((noipa)) \
  test_##N##_##K (uint##N##_t *r, int##N##_t x) \
  { \
    r[0] = signed_##N##_##K (x); \
    r[1] = converted_##N##_##K (x); \
    r[2] = unsigned_##N##_##K (x); \
    r[3] = (x >> K) + ((x >> (K - 1)) & 2); \
    r[4] = x >> (K - 1); \
  }
SHIFTS31 (TEST, 32)
SHIFTS63 (TEST, 64)
#endif

#ifndef TEST_FUNCTIONS_ONLY
/* Use unsigned shifts and explicit sign fill in the reference.  */
static uint64_t
asr (uint64_t x, unsigned int bits, unsigned int k)
{
  uint64_t mask = bits == 32 ? UINT32_MAX : UINT64_MAX;
  x &= mask;
  uint64_t r = x >> k;
  if (x & (UINT64_C (1) << (bits - 1)))
    r |= mask ^ (mask >> k);
  return r;
}

#define ENTRY(N, K) test_##N##_##K,
#define CHECK(N, SHIFTS) \
  static void (*const functions_##N[]) (uint##N##_t *, int##N##_t) \
    = { SHIFTS (ENTRY, N) }; \
  static void check_##N (uint##N##_t x, unsigned int k) \
  { \
    uint##N##_t r[5]; \
    functions_##N[k - 1] (r, x); \
    uint64_t q = asr (x, N, k), bit = (x >> (k - 1)) & 1; \
    uint##N##_t want[] = { q + bit, q + bit, (x >> k) + bit, \
      q + ((asr (x, N, k - 1)) & 2), asr (x, N, k - 1) }; \
    for (unsigned int i = 0; i < 5; ++i) \
      if (r[i] != want[i]) __builtin_abort (); \
  }
CHECK (32, SHIFTS31)
CHECK (64, SHIFTS63)

int
main (void)
{
  static const uint64_t edge[] = { 0, 1, 2, 3, UINT32_MAX, INT32_MAX,
    UINT64_C (0x80000000), UINT64_MAX, INT64_MAX,
    UINT64_C (0x8000000000000000), UINT64_C (0x8000000000000001),
    UINT64_C (0xaaaaaaaaaaaaaaaa), UINT64_C (0x5555555555555555) };
  for (unsigned int k = 1; k < 64; ++k)
    {
      for (unsigned int i = 0; i < sizeof edge / sizeof edge[0]; ++i)
	{
	  check_64 (edge[i], k);
	  if (k < 32)
	    check_32 (edge[i], k);
	}
      uint32_t state = 0x9a731dc5;
      for (unsigned int i = 0; i < 8192; ++i)
	{
	  state = state * 1664525u + 1013904223u;
	  uint64_t x = (uint64_t) state << 32;
	  state = state * 1664525u + 1013904223u;
	  x |= state;
	  check_64 (x, k);
	  if (k < 32)
	    check_32 (x, k);
	}
    }
  return 0;
}
#endif
