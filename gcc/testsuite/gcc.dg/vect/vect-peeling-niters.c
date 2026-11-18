/* { dg-do run } */

#include <stdint.h>

#ifndef TEST_DRIVER_ONLY
__attribute__ ((noipa)) void
counted (uint16_t *restrict d, const uint16_t *restrict s, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] += s[i];
}

__attribute__ ((noipa)) void
signed_counted (uint16_t *restrict d, const uint16_t *restrict s, int n)
{
  for (int i = 0; i < n; ++i)
    d[i] += s[i];
}

/* N == 0 denotes a full period, not an empty loop.  */
__attribute__ ((noipa)) void
wrapping (uint16_t *restrict d, const uint16_t *restrict s, unsigned char n)
{
  unsigned char i = 0;
  do
    {
      *d++ += *s++;
      ++i;
    }
  while (i != n);
}

/* Exercise the same boundary after a nonzero initial counter value.  */
__attribute__ ((noipa)) void
wrapping_from (uint16_t *restrict d, const uint16_t *restrict s,
	       unsigned char first, unsigned char last)
{
  unsigned char i = first;
  do
    {
      *d++ += *s++;
      ++i;
    }
  while (i != last);
}
#else
void counted (uint16_t *, const uint16_t *, unsigned);
void signed_counted (uint16_t *, const uint16_t *, int);
void wrapping (uint16_t *, const uint16_t *, unsigned char);
void wrapping_from (uint16_t *, const uint16_t *, unsigned char, unsigned char);
#endif

#ifndef TEST_FUNCTIONS_ONLY
#define SIZE 288
static uint16_t actual[SIZE] __attribute__ ((aligned (64)));
static uint16_t expected[SIZE] __attribute__ ((aligned (64)));
static uint16_t input[SIZE] __attribute__ ((aligned (64)));

int __attribute__ ((optimize ("no-tree-vectorize,no-tree-slp-vectorize")))
main (void)
{
  for (unsigned n = 0; n <= 257; ++n)
    for (unsigned d = 0; d < 8; ++d)
      for (unsigned s = 0; s < 8; ++s)
	for (unsigned kind = 0; kind < 4; ++kind)
	  {
	    for (unsigned i = 0; i < SIZE; ++i)
	      {
		actual[i] = expected[i] = (i + n) * 251U;
		input[i] = (i * 257U) ^ 0xabcdU;
	      }
	    unsigned count = n;
	    int signed_n = (int) n - 3;
	    unsigned char first = n * 73U;
	    if (kind == 1)
	      count = signed_n > 0 ? signed_n : 0;
	    else if (kind >= 2)
	      {
		count = (unsigned char) n;
		if (count == 0)
		  count = 256;
	      }
	    for (unsigned i = 0; i < count; ++i)
	      expected[d + i] += input[s + i];
	    if (kind == 0)
	      counted (actual + d, input + s, n);
	    else if (kind == 1)
	      signed_counted (actual + d, input + s, signed_n);
	    else if (kind == 2)
	      wrapping (actual + d, input + s, n);
	    else
	      wrapping_from (actual + d, input + s, first, first + n);
	    for (unsigned i = 0; i < SIZE; ++i)
	      if (actual[i] != expected[i]
		  || input[i] != (uint16_t) ((i * 257U) ^ 0xabcdU))
		__builtin_abort ();
	  }
  return 0;
}
#endif
