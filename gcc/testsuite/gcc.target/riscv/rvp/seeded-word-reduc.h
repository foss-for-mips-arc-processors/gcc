typedef unsigned int u32;
typedef unsigned long long u64;
typedef u32 v2u32 __attribute__ ((vector_size (8)));
#define FN __attribute__ ((noipa))

u32 FN
scalar (u64 x, u32 seed)
{
  return (u32) x + (u32) (x >> 32) + seed;
}

u32 FN
vector (v2u32 x, u32 seed)
{
  return x[0] + x[1] + seed;
}

u32 FN
reversed (v2u32 x, u32 seed)
{
  return seed + x[1] + x[0];
}

u32 FN
signed_high (long long x, u32 seed)
{
  return (u32) x + (u32) (x >> 32) + seed;
}

u64 FN
widened (u64 x, u32 seed)
{
  return (u32) ((u32) x + (u32) (x >> 32) + seed);
}

void FN
store (u64 x, u32 seed, u32 *out)
{
  *out = (u32) x + (u32) (x >> 32) + seed;
}

u32 FN
shared (u64 x, u32 seed, u32 *out)
{
  u32 high = x >> 32;
  *out = high;
  return (u32) x + high + seed;
}

u32 FN
different (u64 x, u64 y, u32 seed)
{
  return (u32) x + (u32) (y >> 32) + seed;
}

u32 FN
wrong_shift (u64 x, u32 seed)
{
  return (u32) x + (u32) (x >> 31) + seed;
}

u64 FN
full_result (u64 x, u64 seed)
{
  return (u32) x + (x >> 32) + seed;
}

u32 FN
loaded (const volatile u64 *p, u32 seed)
{
  u64 x = *p;
  return (u32) x + (u32) (x >> 32) + seed;
}
