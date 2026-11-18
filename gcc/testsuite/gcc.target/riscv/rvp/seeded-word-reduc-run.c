/* { dg-do run } */
/* { dg-options "-O3" } */

#include "seeded-word-reduc.h"

static int __attribute__ ((noipa, optimize ("O0")))
check (u64 x, u64 y, u32 seed)
{
  u32 lo = x, hi = x >> 32, out = ~seed;
  u32 sum = (u64) lo + hi + seed;
  v2u32 lanes = { lo, hi };
  volatile u64 memory = x;
  if (scalar (x, seed) != sum || vector (lanes, seed) != sum
      || reversed (lanes, seed) != sum
      || signed_high ((long long) x, seed) != sum
      || widened (x, seed) != (u64) sum)
    return 1;
  store (x, seed, &out);
  if (out != sum)
    return 2;
  if (shared (x, seed, &out) != sum || out != hi)
    return 3;
  if (different (x, y, seed) != (u32) ((u64) lo + (u32) (y >> 32) + seed)
      || wrong_shift (x, seed) != (u32) ((u64) lo + (u32) (x >> 31) + seed))
    return 4;
  if (full_result (x, y) != (u64) lo + hi + y
      || loaded (&memory, seed) != sum || memory != x)
    return 5;
  return 0;
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const u32 edge[] = {
    0, 1, 255, 65535, 0x7fffffffU, 0x80000000U, 0xfffffffeU, 0xffffffffU
  };
  for (unsigned int i = 0; i < 8; ++i)
    for (unsigned int j = 0; j < 8; ++j)
      for (unsigned int k = 0; k < 8; ++k)
        if (check (((u64) edge[i] << 32) | edge[j],
                   ((u64) edge[k] << 32) | edge[i], edge[k]))
          return 1;
  u64 state = 0x123456789abcdef0ULL;
  for (unsigned int i = 0; i < 65536; ++i)
    {
      state ^= state << 13;
      state ^= state >> 7;
      state ^= state << 17;
      if (check (state, ~state, i * 65537U))
        return 2;
    }
  return 0;
}
