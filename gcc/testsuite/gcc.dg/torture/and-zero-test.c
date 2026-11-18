/* { dg-do run } */

#include "and-zero-test.h"

#ifdef EXTERNAL_KERNELS
#define DEF(T, N, S, E) extern T N##_##S (T, T, T);
#else
#define DEF(T, N, S, E) \
  __attribute__ ((noipa)) T N##_##S (T a, T b, T c) { return E; }
#endif
ALL_ZERO_TEST_FUNCTIONS (DEF)
#undef DEF

/* Keep the reference expressions out of combine.  The standalone cross
   harness also builds this translation unit with the baseline compiler.  */
#define REF(T, N, S, E) \
  __attribute__ ((noipa, optimize ("O0"))) \
  T ref_##N##_##S (T a, T b, T c) { return E; }
ALL_ZERO_TEST_FUNCTIONS (REF)
#undef REF

static void
check (__UINT64_TYPE__ a, __UINT64_TYPE__ b, __UINT64_TYPE__ c)
{
#define CHECK(T, N, S, E) \
  if (N##_##S ((T) a, (T) b, (T) c) \
      != ref_##N##_##S ((T) a, (T) b, (T) c)) \
    __builtin_abort ();
  ALL_ZERO_TEST_FUNCTIONS (CHECK)
#undef CHECK
}

int
main (void)
{
  static const __UINT64_TYPE__ edges[] =
    { 0, 1, 2, 3, 4, 5, 0x7f, 0x80, 0xff, 0x7fff, 0x8000, 0xffff,
      0x7fffffff, 0x80000000, 0xffffffff, 0x100000000ULL,
      0x7fffffffffffffffULL, 0x8000000000000000ULL,
      0xfffffffffffffffeULL, 0xffffffffffffffffULL };
  unsigned n = sizeof (edges) / sizeof (edges[0]);
  for (unsigned i = 0; i < n; ++i)
    for (unsigned j = 0; j < n; ++j)
      for (unsigned k = 0; k < n; ++k)
        check (edges[i], edges[j], edges[k]);
  __UINT64_TYPE__ state = 0xa81ce37e12e443d5ULL;
  for (unsigned i = 0; i < 4096; ++i)
    {
      state ^= state << 13;
      state ^= state >> 7;
      state ^= state << 17;
      check (state, state ^ 0xb1df721364ff9001ULL, state >> 13);
    }
  return 0;
}
