/* { dg-do run } */
/* { dg-require-effective-target int32 } */
/* { dg-require-effective-target longlong64 } */
/* { dg-options "-O2" } */

typedef unsigned int u32;
typedef unsigned long long u64;

static u64 __attribute__ ((noipa))
shared (u32 x, u32 y, u32 *out)
{
  u32 sum = x + y;
  u32 narrow = sum < x ? ~0u : sum;
  u64 wide = sum < x ? 4294967295ULL : (u64) sum;
  *out = narrow;
  return wide + ((u64) (narrow ^ x) << 32) + (narrow > y);
}

/* Exercise an ordinary conditional merge inside the loop, distinct from
   the loop-header PHIs carrying the accumulation and witness.  */
static u64 __attribute__ ((noipa))
loop_body (u32 x, u32 y, unsigned count, u32 *out)
{
  u64 total = 0;
  u32 witness = 0;
  for (unsigned i = 0; i < count; ++i)
    {
      u32 other = y ^ i;
      u32 sum = x + other;
      u32 narrow = sum < x ? ~0u : sum;
      u64 wide = sum < x ? 4294967295ULL : (u64) sum;
      witness ^= narrow;
      total += wide;
    }
  *out = witness;
  return total;
}

static u64 __attribute__ ((noipa))
side_effects (u32 x, u32 y, u32 *out, volatile unsigned *counts)
{
  u32 sum = x + y;
  u32 narrow;
  u64 wide;
  if (sum < x)
    {
      ++counts[0];
      narrow = ~0u;
      wide = 4294967295ULL;
    }
  else
    {
      ++counts[1];
      narrow = sum;
      wide = sum;
    }
  *out = narrow;
  return wide;
}

/* Use a wider arithmetic domain and disable optimization in the oracle,
   independently of the tested narrow sum and overflow comparison.  */
static u64 __attribute__ ((noipa, optimize ("O0")))
reference (u32 x, u32 y)
{
  u64 sum = (u64) x + (u64) y;
  if (sum > 4294967295ULL)
    return 4294967295ULL;
  return sum;
}

int
main (void)
{
  static const u32 values[] =
    { 0, 1, 41, 42, 65535, 0x7fffffff, 0x80000000, 0xfffffffe, 0xffffffff };
  for (unsigned i = 0; i < sizeof values / sizeof values[0]; ++i)
    for (unsigned j = 0; j < sizeof values / sizeof values[0]; ++j)
      {
        u32 x = values[i], y = values[j];
        u32 output[3] = { 0x13579bdf, 0, 0x2468ace0 };
        u32 narrow = reference (x, y);
        u64 expected = narrow + ((u64) (narrow ^ x) << 32) + (narrow > y);
        if (shared (x, y, output + 1) != expected || output[1] != narrow)
          __builtin_abort ();

        for (unsigned count = 0; count <= 9; ++count)
          {
            u64 total = 0;
            u32 witness = 0;
            for (unsigned k = 0; k < count; ++k)
              {
                u32 value = reference (x, y ^ k);
                witness ^= value;
                total += value;
              }
            if (loop_body (x, y, count, output + 1) != total
                || output[1] != witness)
              __builtin_abort ();
          }

        volatile unsigned counts[2] = { 11, 17 };
        unsigned overflow = (u64) x + y > 4294967295ULL;
        if (side_effects (x, y, output + 1, counts) != narrow
            || output[1] != narrow
            || counts[0] != 11 + overflow || counts[1] != 18 - overflow
            || output[0] != 0x13579bdf || output[2] != 0x2468ace0)
          __builtin_abort ();
      }
  return 0;
}
