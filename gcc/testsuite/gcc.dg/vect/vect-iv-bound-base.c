/* { dg-do run } */

/* Keep pointer IVs live after loops with shifted starts.  Check their bounds
   for forward, reverse, strided, narrow-counter and alias-versioned loops.  */

#define FN __attribute__ ((noipa))
#ifndef TEST_DRIVER_ONLY
unsigned *FN
forward (unsigned *restrict p, const unsigned *restrict q,
	 unsigned n, unsigned bias)
{
  p += bias;
  q += bias + 1;
  for (unsigned i = 0; i < n; ++i, ++p, ++q)
    *p += *q + i;
  return p;
}

unsigned *FN
reverse (unsigned *restrict p, const unsigned *restrict q,
	 unsigned n, unsigned bias)
{
  p -= bias;
  q -= bias + 1;
  for (unsigned i = 0; i < n; ++i, --p, --q)
    *p += *q + i;
  return p;
}

unsigned *FN
strided (unsigned *restrict p, const unsigned *restrict q,
	 unsigned n, unsigned bias)
{
  p += bias;
  q += bias;
  for (unsigned i = 0; i < n; ++i, p += 2, q += 3)
    *p += *q + i;
  return p;
}

unsigned *FN
narrow (unsigned *restrict p, const unsigned *restrict q,
	unsigned n, unsigned bias)
{
  p += bias + 1;
  q += bias + 2;
  for (unsigned char i = 0; i < n; ++i, ++p, ++q)
    *p += *q + i;
  return p;
}

unsigned *FN
alias (unsigned *p, const unsigned *q, unsigned n, unsigned bias)
{
  p += bias;
  q += bias + 1;
  for (unsigned i = 0; i < n; ++i, ++p, ++q)
    *p += *q + i;
  return p;
}
#else
unsigned *forward (unsigned *, const unsigned *, unsigned, unsigned);
unsigned *reverse (unsigned *, const unsigned *, unsigned, unsigned);
unsigned *strided (unsigned *, const unsigned *, unsigned, unsigned);
unsigned *narrow (unsigned *, const unsigned *, unsigned, unsigned);
unsigned *alias (unsigned *, const unsigned *, unsigned, unsigned);
#endif

#ifndef TEST_FUNCTIONS_ONLY
#define SIZE 1024
static unsigned a[SIZE] __attribute__ ((aligned (64)));
static unsigned d[SIZE] __attribute__ ((aligned (64)));
static unsigned r[SIZE] __attribute__ ((aligned (64)));

static void __attribute__ ((noipa, optimize ("O0")))
check (void)
{
  for (unsigned i = 0; i < SIZE; ++i)
    if (d[i] != r[i])
      __builtin_abort ();
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  unsigned *(*const functions[]) (unsigned *, const unsigned *, unsigned,
				 unsigned)
    = { forward, reverse, strided, narrow, alias };
  static const unsigned sizes[]
    = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, 17, 31, 32, 33, 63, 64, 65,
	127, 128, 129, 254, 255 };
  for (unsigned s = 0; s < sizeof sizes / sizeof sizes[0]; ++s)
    for (unsigned bias = 0; bias < 8; ++bias)
      {
	unsigned n = sizes[s];
	for (unsigned k = 0; k < 5; ++k)
	  {
	    for (unsigned i = 0; i < SIZE; ++i)
	      {
		a[i] = i * 2654435761U + n;
		d[i] = r[i] = ~i * 1234567U + bias;
	      }
	    int start = k == 1 ? 512 : 8;
	    int pi = start + (k == 1 ? -(int) bias : (int) bias + (k == 3));
	    int qi = pi + (k != 2 ? (k == 1 ? -1 : 1) : 0);
	    int ps = k == 1 ? -1 : k == 2 ? 2 : 1;
	    int qs = k == 2 ? 3 : ps;
	    for (unsigned i = 0; i < n; ++i, pi += ps, qi += qs)
	      r[pi] += a[qi] + i;
	    if (functions[k] (d + start, a + start, n, bias) != d + pi)
	      __builtin_abort ();
	    check ();
	  }
	for (unsigned off = 0; off < 8; ++off)
	  {
	    for (unsigned i = 0; i < SIZE; ++i)
	      d[i] = r[i] = i * 2654435761U + n;
	    for (unsigned i = 0; i < n; ++i)
	      r[8 + bias + i] += r[4 + off + bias + 1 + i] + i;
	    if (alias (d + 8, d + 4 + off, n, bias) != d + 8 + bias + n)
	      __builtin_abort ();
	    check ();
	  }
      }
  return 0;
}
#endif
