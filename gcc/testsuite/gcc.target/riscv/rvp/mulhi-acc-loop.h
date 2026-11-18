typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
#define FN __attribute__ ((noipa))

#define KERNEL(NAME, TA, TB, TW, BIAS) \
u32 FN \
reduce_##NAME (u32 c, const TA *a, const TB *b, unsigned n) \
{ \
  for (unsigned i = 0; i < n; ++i) \
    c += (u32) (((TW) a[i] * (TW) b[i] + (BIAS)) >> 32); \
  return c; \
} \
void FN \
map_##NAME (u32 *d, const TA *a, const TB *b, unsigned n) \
{ \
  for (unsigned i = 0; i < n; ++i) \
    d[i] += (u32) (((TW) a[i] * (TW) b[i] + (BIAS)) >> 32); \
}

KERNEL (s, i32, i32, i64, 0)
KERNEL (u, u32, u32, u64, 0)
KERNEL (su, i32, u32, i64, 0)
KERNEL (us, u32, i32, i64, 0)
KERNEL (rs, i32, i32, i64, 0x80000000LL)
KERNEL (ru, u32, u32, u64, 0x80000000ULL)
KERNEL (rsu, i32, u32, i64, 0x80000000LL)
KERNEL (rus, u32, i32, i64, 0x80000000LL)

u32 FN
shared_round (u32 c, const i32 *a, const i32 *b, i64 *saved, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    {
      i64 p = (i64) a[i] * b[i];
      saved[i] = p;
      c += (u32) ((p + 0x80000000LL) >> 32);
    }
  return c;
}

u32 FN
variable_bias (u32 c, const u32 *a, const u32 *b, u64 bias, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    c += (u32) (((u64) a[i] * b[i] + bias) >> 32);
  return c;
}

u32 FN
wrong_bias (u32 c, const i32 *a, const i32 *b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    c += (u32) (((i64) a[i] * b[i] + 0x40000000LL) >> 32);
  return c;
}

u32 FN
wrong_shift (u32 c, const i32 *a, const i32 *b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    c += (u32) (((i64) a[i] * b[i] + 0x80000000LL) >> 31);
  return c;
}

u32 FN
volatile_round (u32 c, const volatile i32 *a, const volatile i32 *b,
		unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    c += (u32) (((i64) a[i] * b[i] + 0x80000000LL) >> 32);
  return c;
}
