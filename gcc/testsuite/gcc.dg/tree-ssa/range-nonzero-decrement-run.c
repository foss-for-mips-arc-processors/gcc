/* { dg-do run } */
/* { dg-require-effective-target int32 } */
/* { dg-options "-O2" } */

#include "range-nonzero-decrement.h"
#include "range-nonzero-decrement-2.c"

typedef unsigned long long value;
typedef int (*function) (value);

#define GROUP(PREFIX, SUFFIX) PREFIX ## _lt_ ## SUFFIX, \
  PREFIX ## _le_ ## SUFFIX, PREFIX ## _gt_ ## SUFFIX, PREFIX ## _ge_ ## SUFFIX
static const function functions[] = {
  GROUP (u32, zero), GROUP (u32, small), GROUP (u32, high), GROUP (u32, top),
  GROUP (u64, zero), GROUP (u64, small), GROUP (u64, high), GROUP (u64, top)
};
#undef GROUP

static int __attribute__ ((noipa, optimize ("O0")))
reference (value input, unsigned int test)
{
  value max = test < 16 ? (value) ~0U : ~0ULL;
  value x = input & max;
  if (x == 0)
    return -1;
  value y = x - 1;
  unsigned int group = (test % 16) / 4;
  value bound = group == 0 ? 0 : group == 1 ? 2
    : group == 2 ? max - 1 : max;
  switch (test % 4)
    {
    case 0: return y < bound;
    case 1: return y <= bound;
    case 2: return y > bound;
    default: return y >= bound;
    }
}

static void __attribute__ ((noipa, optimize ("O0")))
check (value x)
{
  for (unsigned int i = 0; i < 32; ++i)
    if (functions[i] (x) != reference (x, i))
      __builtin_abort ();
  unsigned int n = x;
  unsigned int decremented = n == 0 ? ~0U : n - 1;
  if (unguarded (n) != (decremented <= 2)
      || zero_possible (n) != (n == 1 ? -1 : decremented <= 2))
    __builtin_abort ();
  unsigned int saved = 12345;
  int result = shared (n, &saved);
  if (result != (n == 0 ? -1 : decremented <= 2)
      || saved != (n == 0 ? 12345 : decremented))
    __builtin_abort ();
  value decremented64 = x == 0 ? ~0ULL : x - 1;
  if (unguarded64 (x) != (decremented64 <= 2)
      || zero_possible64 (x) != (x == 1 ? -1 : decremented64 <= 2))
    __builtin_abort ();
  value saved64 = 12345;
  result = shared64 (x, &saved64);
  if (result != (x == 0 ? -1 : decremented64 <= 2)
      || saved64 != (x == 0 ? 12345 : decremented64))
    __builtin_abort ();
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  for (value i = 0; i < 65536; ++i)
    {
      check (i);
      check ((value) ~0U - i);
      check (~0ULL - i);
    }
  static const value edges[] = {
    0x7fffffffULL, 0x80000000ULL, 0x100000000ULL,
    0x7fffffffffffffffULL, 0x8000000000000000ULL
  };
  for (unsigned int i = 0; i < sizeof edges / sizeof edges[0]; ++i)
    for (value j = 0; j < 8; ++j)
      check (edges[i] - 4 + j);
  return 0;
}
