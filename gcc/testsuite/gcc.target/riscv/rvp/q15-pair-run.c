/* { dg-do run } */
/* { dg-options "-O3" } */

#include "q15-pair.h"

static short __attribute__ ((noipa, optimize ("O0")))
wrap (long long value)
{
  unsigned int bits = (unsigned long long) value & 65535;
  return bits < 32768 ? (int) bits : (int) bits - 65536;
}

/* Use widened division with floor correction, independently of the tested
   multiply, shift and narrow idioms.  */
static short __attribute__ ((noipa, optimize ("O0")))
reference (short a, short b, unsigned int kind)
{
  long long product = kind == 7 ? (long long) (unsigned short) a * b
			       : (long long) a * b;
  if (kind == 6)
    product = wrap (product);
  product += kind == 1 ? 16384 : kind == 3 ? 16383 : 0;
  long long divisor = kind == 4 ? 65536 : 32768;
  long long result = product / divisor;
  if (product < 0 && product % divisor)
    --result;
  int limit = kind == 2 ? 32766 : 32767;
  if (kind != 5 && kind != 6 && result > limit)
    result = limit;
  return wrap (result);
}

static int __attribute__ ((noipa, optimize ("O0")))
check (v2hi a, v2hi b)
{
  typedef v2hi (*kernel) (v2hi, v2hi);
  static const kernel functions[] = { exact, rounding, wrong_limit,
    wrong_round, wrong_shift, unclamped, narrowed, mixed };
  for (unsigned int kind = 0; kind < 8; ++kind)
    {
      v2hi result = functions[kind] (a, b);
      for (unsigned int lane = 0; lane < 2; ++lane)
	if (result[lane] != reference (a[lane], b[lane], kind))
	  return 1;
    }
  v2si w = wide (a, b), r = wide_round (a, b), saved, saved_round;
  v2hi s = shared (a, b, &saved);
  v2hi t = shared_round (a, b, &saved_round);
  for (unsigned int lane = 0; lane < 2; ++lane)
    {
      if (w[lane] != reference (a[lane], b[lane], 0)
	  || s[lane] != w[lane])
	return 2;
      if (r[lane] != reference (a[lane], b[lane], 1)
	  || t[lane] != r[lane])
	return 3;
      int product = (int) a[lane] * b[lane];
      if (saved[lane] != product || saved_round[lane] != product)
	return 4;
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
  unsigned int state = 0x12345678;
  for (unsigned int i = 0; i < 8192; ++i)
    {
      v2hi a, b;
      for (unsigned int j = 0; j < 2; ++j)
	{
	  state = state * 1664525 + 1013904223;
	  a[j] = wrap (state >> 16);
	  state = state * 1664525 + 1013904223;
	  b[j] = wrap (state >> 16);
	}
      if (check (a, b))
	return 2;
    }
  return 0;
}
