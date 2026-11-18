typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
#define FN __attribute__ ((noipa))

u32 FN
acc_s (u32 c, i32 a, i32 b)
{
  return c + (u32) (((i64) a * b) >> 32);
}

u32 FN
acc_u (u32 c, u32 a, u32 b)
{
  return c + (u32) (((u64) a * b) >> 32);
}

u32 FN
acc_su (u32 c, i32 a, u32 b)
{
  return c + (u32) (((i64) a * (i64) b) >> 32);
}

u32 FN
acc_us (u32 c, u32 a, i32 b)
{
  return (u32) (((i64) a * (i64) b) >> 32) + c;
}

u32 FN
racc_s (u32 c, i32 a, i32 b)
{
  return c + (u32) (((i64) a * b + 0x80000000LL) >> 32);
}

u32 FN
racc_u (u32 c, u32 a, u32 b)
{
  return c + (u32) (((u64) a * b + 0x80000000ULL) >> 32);
}

u32 FN
racc_su (u32 c, i32 a, u32 b)
{
  return c + (u32) (((i64) a * (i64) b + 0x80000000LL) >> 32);
}

u32 FN
racc_us (u32 c, u32 a, i32 b)
{
  return (u32) (((i64) a * (i64) b + 0x80000000LL) >> 32) + c;
}

void FN
store_s (u32 *p, u32 c, i32 a, i32 b)
{
  *p = c + (u32) (((i64) a * b) >> 32);
}

void FN
store_rs (u32 *p, u32 c, i32 a, i32 b)
{
  *p = c + (u32) (((i64) a * b + 0x80000000LL) >> 32);
}

u32 FN
shared_s (u32 c, i32 a, i32 b, i64 *p)
{
  i64 product = (i64) a * b;
  *p = product;
  return c + (u32) (product >> 32);
}

u32 FN
shared_rs (u32 c, i32 a, i32 b, i64 *p)
{
  i64 product = (i64) a * b;
  *p = product;
  return c + (u32) ((product + 0x80000000LL) >> 32);
}

u64 FN
wide_s (u64 c, i32 a, i32 b)
{
  return c + (u64) (((i64) a * b) >> 32);
}

u64 FN
wide_u (u64 c, u32 a, u32 b)
{
  return c + (((u64) a * b) >> 32);
}

u32 FN
wrong_shift (u32 c, i32 a, i32 b)
{
  return c + (u32) (((i64) a * b) >> 31);
}

u32 FN
wrong_round (u32 c, i32 a, i32 b)
{
  return c + (u32) (((i64) a * b + 0x40000000LL) >> 32);
}

u64 FN
live_upper (u64 a, u64 b, u32 c)
{
  u32 result = c + (u32) (((i64) (i32) a * (i32) b) >> 32);
  return (a ^ b) + result;
}

u32 FN
overlap (i32 a, i32 b)
{
  return (u32) a + (u32) (((i64) a * b) >> 32);
}

u32 FN
loop_s (u32 c, const i32 *a, const i32 *b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    c += (u32) (((i64) a[i] * b[i]) >> 32);
  return c;
}

u32 FN
loop_rs (u32 c, const i32 *a, const i32 *b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    c += (u32) (((i64) a[i] * b[i] + 0x80000000LL) >> 32);
  return c;
}

void FN
map_s (u32 *restrict d, const i32 *restrict a, const i32 *restrict b,
       unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] += (u32) (((i64) a[i] * b[i]) >> 32);
}

void FN
map_rs (u32 *restrict d, const i32 *restrict a, const i32 *restrict b,
        unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] += (u32) (((i64) a[i] * b[i] + 0x80000000LL) >> 32);
}

u32 FN
square_s (u32 c, i32 a)
{
  return c + (u32) (((i64) a * a) >> 32);
}

u32 FN
square_rs (u32 c, i32 a)
{
  return c + (u32) (((i64) a * a + 0x80000000LL) >> 32);
}

u32 FN
square_u (u32 c, u32 a)
{
  return c + (u32) (((u64) a * a) >> 32);
}

u32 FN
square_ru (u32 c, u32 a)
{
  return c + (u32) (((u64) a * a + 0x80000000ULL) >> 32);
}

u32 FN
overlap_right (i32 a, i32 b)
{
  return (u32) b + (u32) (((i64) a * b) >> 32);
}

u32 FN
overlap_round (i32 a, u32 b)
{
  return b + (u32) (((i64) a * (i64) b + 0x80000000LL) >> 32);
}

u32 FN
shared_high (u32 c, i32 a, i32 b, u32 *p)
{
  u32 high = (u32) (((i64) a * b) >> 32);
  *p = high;
  return c + high;
}

u64 FN
preserve_acc (u64 c, i32 a, i32 b)
{
  u32 low = (u32) c + (u32) (((i64) a * b) >> 32);
  return (c & 0xffffffff00000000ULL) | low;
}

u32 FN
full_width (u32 c, u64 a, u64 b)
{
  return c + (u32) ((a * b) >> 32);
}
