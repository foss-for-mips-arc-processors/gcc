/* { dg-do run } */
/* { dg-require-effective-target int32 } */

typedef unsigned int u32;
typedef unsigned long long u64;

#define TEST(NAME, EXPR) \
  u64 __attribute__ ((noipa)) \
  NAME (u32 a, u32 b, u32 c) \
  { \
    u32 low = ((a << 3) ^ (c >> 5)) + a * c; \
    u32 word = (unsigned short) low | (b << 16); \
    return (EXPR); \
  }

TEST (negative, (int) word < 0)
TEST (nonnegative, (int) word >= 0)
TEST (sign_cleared, (int) (word & 0x7fffffffU) < 0)
TEST (full_word, word)
TEST (extended_word, (long long) (int) word)
TEST (equal_zero, word == 0)
TEST (negated_sign, ((u32) -word) >> 31)
TEST (complemented_sign, (~word) >> 31)

/* Use unsigned, wider arithmetic to construct the expected bits.  */
static void __attribute__ ((noipa, optimize ("O0")))
check (u32 a, u32 b, u32 c)
{
  u64 x = a, y = b, z = c;
  u64 low = ((((x << 3) & 0xffffffffULL) ^ (z >> 5))
	     + x * z) & 0xffffffffULL;
  u64 word = 0;
  for (unsigned int i = 0; i < 16; ++i)
    {
      word |= ((low >> i) & 1) << i;
      word |= ((y >> i) & 1) << (16 + i);
    }
  u64 sign = (word >> 31) & 1;
  if (negative (a, b, c) != sign
      || nonnegative (a, b, c) != 1 - sign
      || sign_cleared (a, b, c) != 0
      || full_word (a, b, c) != word
      || extended_word (a, b, c)
	 != (sign ? word | 0xffffffff00000000ULL : word)
      || equal_zero (a, b, c) != (word == 0)
      || negated_sign (a, b, c)
	 != (((0x100000000ULL - word) & 0xffffffffULL) >> 31)
      || complemented_sign (a, b, c) != 1 - sign)
    __builtin_abort ();
}

int
main (void)
{
  static const u32 edge[] = {
    0, 1, 127, 128, 255, 256, 32767, 32768,
    65535, 65536, 0x7fffffff, 0x80000000, 0xffffffff
  };
  for (unsigned int i = 0; i < sizeof (edge) / sizeof (edge[0]); ++i)
    for (unsigned int j = 0; j < sizeof (edge) / sizeof (edge[0]); ++j)
      for (unsigned int k = 0; k < sizeof (edge) / sizeof (edge[0]); ++k)
	check (edge[i], edge[j], edge[k]);
  return 0;
}
