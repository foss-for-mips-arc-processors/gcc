/* { dg-do run } */
/* { dg-options "-O3" } */

#include "mulhi-acc-loop.h"

/* All products use independent 16-bit limbs.  KIND selects signedness:
   signed/signed, unsigned/unsigned, signed/unsigned, unsigned/signed.  */
static u32 __attribute__ ((noipa, optimize ("O0")))
high_word (u32 a, u32 b, unsigned kind, u64 bias, u32 *low)
{
  u32 a0 = a & 65535, a1 = a >> 16;
  u32 b0 = b & 65535, b1 = b >> 16;
  u32 t = a0 * b0;
  u32 bottom = t & 65535;
  t = a1 * b0 + (t >> 16);
  u32 middle = t & 65535;
  u32 high = t >> 16;
  t = a0 * b1 + middle;
  u32 lo = (t << 16) | bottom;
  high += a1 * b1 + (t >> 16);
  if ((kind == 0 || kind == 2) && a >> 31)
    high -= b;
  if ((kind == 0 || kind == 3) && b >> 31)
    high -= a;
  *low = lo + (u32) bias;
  return high + (u32) (bias >> 32) + (*low < lo);
}

#define SIZE 136
static i32 a[SIZE] __attribute__ ((aligned (64)));
static i32 b[SIZE] __attribute__ ((aligned (64)));
static u32 ua[SIZE] __attribute__ ((aligned (64)));
static u32 ub[SIZE] __attribute__ ((aligned (64)));
static u32 d[SIZE] __attribute__ ((aligned (64)));
static u32 r[SIZE];
static i64 saved[SIZE];

static u32 __attribute__ ((noipa, optimize ("O0")))
prepare (unsigned kind, u64 bias, unsigned n, unsigned offset)
{
  u32 sum = 0xfffffff0U;
  for (unsigned i = 0; i < SIZE; ++i)
    d[i] = r[i] = i * 1234567U;
  for (unsigned i = 0; i < n; ++i)
    {
      u32 low;
      u32 high = high_word (ua[offset + i], ub[3 - offset + i],
			    kind, bias, &low);
      sum += high;
      r[2 + offset + i] += high;
    }
  return sum;
}

#define CHECK(NAME, KIND, BIAS, A, B) \
do \
  { \
    u32 want = prepare (KIND, BIAS, n, offset); \
    if (reduce_##NAME (0xfffffff0U, A + offset, B + 3 - offset, n) != want) \
      __builtin_abort (); \
    map_##NAME (d + 2 + offset, A + offset, B + 3 - offset, n); \
    for (unsigned i = 0; i < SIZE; ++i) \
      if (d[i] != r[i]) \
	__builtin_abort (); \
  } \
while (0)

#define ALIAS(NAME, KIND, A, B) \
do \
  { \
    for (unsigned i = 0; i < SIZE; ++i) \
      A[i] = r[i] = i * 2654435761U; \
    for (unsigned i = 0; i < n; ++i) \
      { \
	u32 low; \
	r[delta + i] += high_word (r[i], (u32) B[i], KIND, \
				  0x80000000ULL, &low); \
      } \
    map_##NAME ((u32 *) A + delta, A, B, n); \
    for (unsigned i = 0; i < SIZE; ++i) \
      if ((u32) A[i] != r[i]) \
	__builtin_abort (); \
  } \
while (0)

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const u32 values[]
    = { 0, 1, 2, 3, 0x7fff, 0x8000, 0xffff, 0x10000, 0x10001,
	0x3fffffff, 0x40000000, 0x7ffffffe, 0x7fffffff, 0x80000000,
	0x80000001, 0xfffffffe, 0xffffffff };
  static const unsigned sizes[]
    = { 0, 1, 2, 3, 4, 7, 8, 15, 16, 17, 31, 32, 33, 63, 64,
	65, 127, 128 };
  static const u64 biases[]
    = { 0, 1, 0x40000000ULL, 0x80000000ULL, 0xffffffffULL,
	0xffffffffffffffffULL };
  for (unsigned s = 0; s < sizeof sizes / sizeof sizes[0]; ++s)
    for (unsigned offset = 0; offset < 4; ++offset)
      for (unsigned pattern = 0; pattern < 2; ++pattern)
	{
	  unsigned n = sizes[s];
	  for (unsigned i = 0; i < SIZE; ++i)
	    {
	      a[i] = ua[i] = pattern ? i * 2654435761U : values[i % 17];
	      b[i] = ub[i] = pattern ? ~i * 987654321U
				    : values[(i + offset) % 17];
	      saved[i] = 0x13579bdf2468aceLL;
	    }
	  CHECK (s, 0, 0, a, b);
	  CHECK (u, 1, 0, ua, ub);
	  CHECK (su, 2, 0, a, ub);
	  CHECK (us, 3, 0, ua, b);
	  CHECK (rs, 0, 0x80000000ULL, a, b);
	  CHECK (ru, 1, 0x80000000ULL, ua, ub);
	  CHECK (rsu, 2, 0x80000000ULL, a, ub);
	  CHECK (rus, 3, 0x80000000ULL, ua, b);
	  u32 want = prepare (0, 0x80000000ULL, n, offset);
	  if (shared_round (0xfffffff0U, a + offset, b + 3 - offset,
			    saved + 2 + offset, n) != want
	      || volatile_round (0xfffffff0U, a + offset,
				 b + 3 - offset, n) != want)
	    __builtin_abort ();
	  for (unsigned i = 0; i < SIZE; ++i)
	    {
	      u64 expected = 0x13579bdf2468aceULL;
	      if (i >= 2 + offset && i < 2 + offset + n)
		{
		  unsigned j = i - 2 - offset;
		  u32 low;
		  u32 high = high_word (ua[offset + j], ub[3 - offset + j],
					0, 0, &low);
		  expected = ((u64) high << 32) | low;
		}
	      if ((u64) saved[i] != expected)
		__builtin_abort ();
	    }
	  want = prepare (0, 0x40000000ULL, n, offset);
	  if (wrong_bias (0xfffffff0U, a + offset, b + 3 - offset, n) != want)
	    __builtin_abort ();
	  want = 0xfffffff0U;
	  for (unsigned i = 0; i < n; ++i)
	    {
	      u32 low;
	      u32 high = high_word (ua[offset + i], ub[3 - offset + i],
				    0, 0x80000000ULL, &low);
	      want += (high << 1) | (low >> 31);
	    }
	  if (wrong_shift (0xfffffff0U, a + offset, b + 3 - offset, n) != want)
	    __builtin_abort ();
	  for (unsigned j = 0; j < sizeof biases / sizeof biases[0]; ++j)
	    {
	      want = prepare (1, biases[j], n, offset);
	      if (variable_bias (0xfffffff0U, ua + offset, ub + 3 - offset,
				 biases[j], n) != want)
		__builtin_abort ();
	    }
	  for (unsigned delta = 0; delta < 2; ++delta)
	    {
	      ALIAS (rs, 0, a, b);
	      ALIAS (ru, 1, ua, ub);
	      ALIAS (rsu, 2, a, ub);
	      ALIAS (rus, 3, ua, b);
	    }
	}
  return 0;
}
