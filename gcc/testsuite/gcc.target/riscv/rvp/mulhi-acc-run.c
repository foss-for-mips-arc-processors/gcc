/* { dg-do run } */
/* { dg-options "-O3" } */

#include "mulhi-acc.h"

/* A 16-bit limb oracle does not use a 64-bit multiplication or a
   multiply-high operation.  Every intermediate sum below fits in u32.  */
static u32 __attribute__ ((noipa, optimize ("O0")))
product (u32 a, u32 b, u32 *low)
{
  u32 a0 = a & 65535, a1 = a >> 16;
  u32 b0 = b & 65535, b1 = b >> 16;
  u32 t = a0 * b0;
  u32 bottom = t & 65535;
  t = a1 * b0 + (t >> 16);
  u32 middle = t & 65535;
  u32 high = t >> 16;
  t = a0 * b1 + middle;
  *low = (t << 16) | bottom;
  return high + a1 * b1 + (t >> 16);
}

static void __attribute__ ((noipa, optimize ("O0")))
check (u32 a, u32 b, u32 c, u32 upper)
{
  u32 low;
  u32 hu = product (a, b, &low);
  u32 hsu = hu - (a >> 31 ? b : 0);
  u32 hus = hu - (b >> 31 ? a : 0);
  u32 hs = hsu - (b >> 31 ? a : 0);
  u32 carry = low >> 31;
  if (acc_s (c, a, b) != c + hs
      || acc_u (c, a, b) != c + hu
      || acc_su (c, a, b) != c + hsu
      || acc_us (c, a, b) != c + hus
      || racc_s (c, a, b) != c + hs + carry
      || racc_u (c, a, b) != c + hu + carry
      || racc_su (c, a, b) != c + hsu + carry
      || racc_us (c, a, b) != c + hus + carry
      || overlap (a, b) != a + hs
      || overlap_right (a, b) != b + hs
      || overlap_round (a, b) != b + hsu + carry
      || wrong_shift (c, a, b) != c + ((hs << 1) | (low >> 31))
      || wrong_round (c, a, b) != c + hs + (low >= 0xc0000000U))
    __builtin_abort ();

  u32 d[3] = { 0x12345678U, 0, 0x87654321U };
  store_s (d + 1, c, a, b);
  if (d[0] != 0x12345678U || d[1] != c + hs || d[2] != 0x87654321U)
    __builtin_abort ();
  store_rs (d + 1, c, a, b);
  if (d[0] != 0x12345678U || d[1] != c + hs + carry
      || d[2] != 0x87654321U)
    __builtin_abort ();

  i64 full[3] = { 0x123456789abcdefLL, 0, -0x123456789abcdefLL };
  u64 bits = ((u64) hs << 32) | low;
  if (shared_s (c, a, b, full + 1) != c + hs || (u64) full[1] != bits
      || shared_rs (c, a, b, full + 1) != c + hs + carry
      || (u64) full[1] != bits || full[0] != 0x123456789abcdefLL
      || full[2] != -0x123456789abcdefLL)
    __builtin_abort ();

  u64 ac = ((u64) upper << 32) | c;
  u64 aa = ((u64) upper << 32) | a;
  u64 bb = ((u64) ~upper << 32) | b;
  if (wide_s (ac, a, b) != ac + (u64) (i64) (i32) hs
      || wide_u (ac, a, b) != ac + hu
      || live_upper (aa, bb, c) != (aa ^ bb) + (u32) (c + hs)
      || preserve_acc (ac, a, b)
	 != (ac & 0xffffffff00000000ULL) + (u32) (c + hs)
      || full_width (c, aa, bb) != c + hu + upper * b + ~upper * a)
    __builtin_abort ();

  u32 saved = 0xdeadbeefU;
  if (shared_high (c, a, b, &saved) != c + hs || saved != hs)
    __builtin_abort ();
  hu = product (a, a, &low);
  hs = hu - (a >> 31 ? a + a : 0);
  carry = low >> 31;
  if (square_s (c, a) != c + hs || square_rs (c, a) != c + hs + carry
      || square_u (c, a) != c + hu || square_ru (c, a) != c + hu + carry)
    __builtin_abort ();
}

#define SIZE 272
static i32 a[SIZE] __attribute__ ((aligned (64)));
static i32 b[SIZE] __attribute__ ((aligned (64)));
static u32 d[SIZE] __attribute__ ((aligned (64)));
static u32 r[SIZE];

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const u32 values[]
    = { 0, 1, 2, 3, 0x7fff, 0x8000, 0xffff, 0x10000, 0x10001,
        0x3fffffff, 0x40000000, 0x7ffffffe, 0x7fffffff, 0x80000000,
        0x80000001, 0xfffffffe, 0xffffffff };
  static const unsigned sizes[]
    = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, 17, 31, 32, 33, 63, 64,
        65, 127, 128, 129, 255, 256 };
  for (unsigned i = 0; i < sizeof values / sizeof values[0]; ++i)
    for (unsigned j = 0; j < sizeof values / sizeof values[0]; ++j)
      for (unsigned k = 0; k < sizeof values / sizeof values[0]; ++k)
        check (values[i], values[j], values[k], ~values[(i + j + k) % 17]);
  u32 seed = 0x942b6a13U;
  for (unsigned i = 0; i < 16384; ++i)
    {
      seed = seed * 1664525U + 1013904223U;
      u32 av = seed;
      seed = seed * 1664525U + 1013904223U;
      u32 bv = seed;
      seed = seed * 1664525U + 1013904223U;
      check (av, bv, seed, seed ^ 0xa55a5aa5U);
    }
  for (unsigned s = 0; s < sizeof sizes / sizeof sizes[0]; ++s)
    for (unsigned off = 0; off < 4; ++off)
      for (unsigned rounded = 0; rounded < 2; ++rounded)
        {
          unsigned n = sizes[s];
          u32 sum = 0xfffffff0U;
          for (unsigned i = 0; i < SIZE; ++i)
            {
              a[i] = i % 3 ? i * 2654435761U : values[i % 17];
              b[i] = i % 3 ? ~i * 987654321U : values[(i + off) % 17];
              d[i] = r[i] = i * 1234567U;
            }
          for (unsigned i = 0; i < n; ++i)
            {
              u32 av = a[off + i], bv = b[3 - off + i], low;
              u32 high = product (av, bv, &low)
                         - (av >> 31 ? bv : 0) - (bv >> 31 ? av : 0);
              high += rounded ? low >> 31 : 0;
              sum += high;
              r[2 + off + i] += high;
            }
          u32 got = rounded
            ? loop_rs (0xfffffff0U, a + off, b + 3 - off, n)
            : loop_s (0xfffffff0U, a + off, b + 3 - off, n);
          if (got != sum)
            __builtin_abort ();
          if (rounded)
            map_rs (d + 2 + off, a + off, b + 3 - off, n);
          else
            map_s (d + 2 + off, a + off, b + 3 - off, n);
          for (unsigned i = 0; i < SIZE; ++i)
            if (d[i] != r[i])
              __builtin_abort ();
        }
  return 0;
}
