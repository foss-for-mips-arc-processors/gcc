/* { dg-do run } */

#include <stdint.h>

#ifndef TEST_DRIVER_ONLY
__attribute__ ((noipa)) void
counted (uint32_t *d, const uint32_t *s, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] += s[i];
}

/* A zero bound means 256 iterations, not an empty loop.  The number of
   latch executions is representable in the counter type but the total
   number of iterations need not be.  */
__attribute__ ((noipa)) void
wrapping (uint32_t *d, const uint32_t *s, unsigned char n)
{
  unsigned char i = 0;
  do
    {
      *d++ += *s++;
      ++i;
    }
  while (i != n);
}

/* Exercise an uncounted loop as well: there is no trip-count expression
   to use in a profitability guard.  */
__attribute__ ((noipa)) unsigned
until_zero (uint32_t *restrict d, const uint32_t *restrict s)
{
  unsigned i = 0;
  while (s[i] != 0)
    {
      d[i] += s[i];
      ++i;
    }
  return i;
}
#else
void counted (uint32_t *, const uint32_t *, unsigned);
void wrapping (uint32_t *, const uint32_t *, unsigned char);
unsigned until_zero (uint32_t *, const uint32_t *);
#endif

#ifndef TEST_FUNCTIONS_ONLY
#define SIZE 544
static uint32_t actual[SIZE] __attribute__ ((aligned (64)));
static uint32_t expected[SIZE] __attribute__ ((aligned (64)));
static uint32_t input[SIZE] __attribute__ ((aligned (64)));

int __attribute__ ((optimize ("no-tree-vectorize,no-tree-slp-vectorize")))
main (void)
{
  static const unsigned offsets[][2]
    = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 }, { 0, 8 }, { 8, 0 },
	{ 1, 9 }, { 9, 1 }, { 0, 272 }, { 272, 0 } };
  for (unsigned n = 0; n <= 257; ++n)
    for (unsigned layout = 0;
	 layout < sizeof offsets / sizeof offsets[0]; ++layout)
      {
	unsigned d = offsets[layout][0];
	unsigned s = offsets[layout][1];
	for (unsigned kind = 0; kind < 2; ++kind)
	  {
	    for (unsigned i = 0; i < SIZE; ++i)
	      actual[i] = expected[i] = (i + n) * 2654435761U;
	    unsigned count = n;
	    if (kind)
	      {
		count = (unsigned char) n;
		if (count == 0)
		  count = 256;
	      }
	    /* Keep the scalar read-after-write order for overlapping arrays.  */
	    for (unsigned i = 0; i < count; ++i)
	      expected[d + i] += expected[s + i];
	    if (kind)
	      wrapping (actual + d, actual + s, n);
	    else
	      counted (actual + d, actual + s, n);
	    for (unsigned i = 0; i < SIZE; ++i)
	      if (actual[i] != expected[i])
		__builtin_abort ();
	  }
	for (unsigned stop = 0; stop <= n; stop = stop ? stop * 2 : 1)
	  {
	    for (unsigned i = 0; i < SIZE; ++i)
	      {
		actual[i] = expected[i] = (i + n) * 2654435761U;
		input[i] = i + 1;
	      }
	    input[s + stop] = 0;
	    for (unsigned i = 0; i < stop; ++i)
	      expected[d + i] += input[s + i];
	    if (until_zero (actual + d, input + s) != stop)
	      __builtin_abort ();
	    for (unsigned i = 0; i < SIZE; ++i)
	      if (actual[i] != expected[i])
		__builtin_abort ();
	  }
      }
  return 0;
}
#endif
