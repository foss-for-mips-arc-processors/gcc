/* { dg-do run } */
/* { dg-options "-O3" } */

typedef short v2hi __attribute__ ((vector_size (4)));
typedef int v2si __attribute__ ((vector_size (8)));

#define DEF(NAME, SHIFT, LIMIT)                                        \
v2hi __attribute__ ((noipa))                                          \
NAME (v2hi a, v2hi b)                                                 \
{                                                                    \
  v2hi out;                                                          \
  for (unsigned int i = 0; i < 2; ++i)                                \
    {                                                                \
      int result = ((int) a[i] * b[i] + 16384) >> (SHIFT);             \
      out[i] = result > (LIMIT) ? (LIMIT) : result;                    \
    }                                                                \
  return out;                                                        \
}

DEF (unclamped, 15, 2147483647)
DEF (wrong_limit, 15, 32766)
DEF (wrong_shift, 14, 32767)

v2si __attribute__ ((noipa))
unscaled (v2hi a, v2hi b)
{
  v2si result;
  for (unsigned int i = 0; i < 2; ++i)
    result[i] = (int) a[i] * b[i] + 16384;
  return result;
}

static short __attribute__ ((noipa, optimize ("O0")))
wrap (long long value)
{
  unsigned int bits = (unsigned long long) value & 65535;
  return bits < 32768 ? (int) bits : (int) bits - 65536;
}

static int __attribute__ ((noipa, optimize ("O0")))
check (v2hi a, v2hi b)
{
  v2hi results[] = { unclamped (a, b), wrong_limit (a, b),
		     wrong_shift (a, b) };
  v2si products = unscaled (a, b);
  for (unsigned int lane = 0; lane < 2; ++lane)
    {
      long long value = (long long) a[lane] * b[lane] + 16384;
      if (products[lane] != value)
	return 1;
      for (unsigned int kind = 0; kind < 3; ++kind)
	{
	  long long divisor = kind == 2 ? 16384 : 32768;
	  long long want = value / divisor;
	  if (value < 0 && value % divisor)
	    --want;
	  int limit = kind == 1 ? 32766 : 32767;
	  if (kind && want > limit)
	    want = limit;
	  if (results[kind][lane] != wrap (want))
	    return 2;
	}
    }
  return 0;
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const short edges[] = { -32768, -32767, -16385, -16384, -1, 0,
				1, 16383, 16384, 16385, 32766, 32767 };
  for (unsigned int edge = 0; edge < 12; ++edge)
    for (unsigned int bits = 0; bits < 65536; bits += 2)
      {
	v2hi a = { wrap (bits), wrap (bits + 1) };
	v2hi b = { edges[edge], edges[edge] };
	if (check (a, b))
	  return 1;
      }
  return 0;
}
