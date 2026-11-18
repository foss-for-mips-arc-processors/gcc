/* { dg-do run } */
/* { dg-options "-O3" } */

#include "masked-word-mul.h"

int __attribute__ ((optimize ("O0")))
main (void)
{
  unsigned int state = 1;
  const unsigned int edges[] = {
    0, 1, 15, 127, 2047, 2048, -2048u, -2049u, 0x80000000u, -1u
  };
  for (unsigned int i = 0; i < 1024; ++i)
    {
      v2si a, b;
      for (unsigned int j = 0; j < 2; ++j)
	{
	  state = state * 1664525u + 1013904223u;
	  a[j] = i < 10 ? edges[i] : state;
	  state = state * 1664525u + 1013904223u;
	  b[j] = i < 10 ? edges[(i + j + 3) % 10] : state;
	}
      v2si both = masked_both (a, b);
      v2si asymmetric = masked_asymmetric (a, b);
      v2si commuted = masked_commuted (a, b);
      v2si shared = masked_shared (a, b);
      v2si one = masked_one (a, b);
      v2si nonimmediate = masked_nonimmediate (a, b);
      v2si left, right;
      v2si retained = masked_retained (a, b, &left, &right);
      v2si aliased;
      v2si retained_alias = masked_retained (a, b, &aliased, &aliased);
      for (unsigned int j = 0; j < 2; ++j)
	{
	  unsigned int lmask = j ? 127 : -2048u;
	  unsigned int rmask = j ? -1u : 2047;
	  unsigned int badmask = j ? -2049u : 2048;
	  unsigned int product = (a[j] & 15) * (b[j] & 127);
	  if (both[j] != product || commuted[j] != product
	      || retained[j] != product || retained_alias[j] != product
	      || asymmetric[j] != (a[j] & lmask) * (b[j] & rmask)
	      || shared[j] != (a[j] & 15) * (a[j] & 127)
	      || one[j] != (a[j] & 15) * b[j]
	      || nonimmediate[j] != (a[j] & badmask) * (b[j] & 127)
	      || left[j] != (a[j] & 15) || right[j] != (b[j] & 127)
	      || aliased[j] != (b[j] & 127))
	    __builtin_abort ();
	}
    }

  unsigned int a[136] __attribute__ ((aligned (16)));
  unsigned int b[136] __attribute__ ((aligned (16)));
  unsigned int out[136] __attribute__ ((aligned (16)));
  unsigned int original_a[136], original_b[136];
  for (unsigned int n = 0; n <= 129; ++n)
    for (unsigned int layout = 0; layout < 4; ++layout)
      {
	unsigned int ao = layout, bo = (layout + 1) % 4;
	unsigned int offset = (layout + 2) % 4;
	for (unsigned int j = 0; j < 136; ++j)
	  {
	    state = state * 1664525u + 1013904223u;
	    a[j] = original_a[j] = state;
	    state = state * 1664525u + 1013904223u;
	    b[j] = original_b[j] = state;
	    out[j] = 0x1234abcd;
	  }
	masked_loop (out + offset, a + ao, b + bo, n);
	unsigned int sum = 0;
	for (unsigned int j = 0; j < 136; ++j)
	  {
	    unsigned int expected = 0x1234abcd;
	    unsigned int k = j - offset;
	    if (k < n)
	      expected = ((original_a[ao + k] & 2047)
			  * (original_b[bo + k] & -2048u));
	    if (out[j] != expected || a[j] != original_a[j]
		|| b[j] != original_b[j])
	      __builtin_abort ();
	  }
	for (unsigned int j = 0; j < n; ++j)
	  sum += (original_a[ao + j] & 15) * (original_b[bo + j] & 127);
	if (masked_sum (a + ao, b + bo, n) != sum)
	  __builtin_abort ();
	for (unsigned int j = 0; j < 136; ++j)
	  if (a[j] != original_a[j] || b[j] != original_b[j])
	    __builtin_abort ();
      }
  return 0;
}
