/* { dg-do run } */
/* { dg-additional-options "--param=vect-epilogues-nomask=0" } */

/* Check final data-pointer reuse, including scalar-only entry, all tails,
   live induction values, alias versions and unsupported access patterns.  */

#define FN __attribute__ ((noipa))
#define VALUE(A, B, I) ((A) + 3U * (B) + (I))

#ifndef TEST_DRIVER_ONLY
void FN
indexed (unsigned *restrict d, const unsigned *restrict a,
	 const unsigned *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = VALUE (a[i], b[i], i);
}

void FN
pointers (unsigned *restrict d, const unsigned *restrict a,
	  const unsigned *restrict b, unsigned n)
{
  for (unsigned i = 0; n != 0; --n, ++i, ++d, ++a, ++b)
    *d = VALUE (*a, *b, i);
}

void FN
alias (unsigned *d, const unsigned *a, const unsigned *b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = VALUE (a[i], b[i], i);
}

void FN
offset (unsigned *restrict d, const unsigned *restrict a,
	const unsigned *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = VALUE (a[i + 1], b[i + 2], i);
}

void FN
strided (unsigned *restrict d, const unsigned *restrict a,
	 const unsigned *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = VALUE (a[2 * i], b[i], i);
}

void FN
reversed (unsigned *restrict d, const unsigned *restrict a,
	  const unsigned *restrict b, unsigned n)
{
  for (unsigned i = n; i != 0; --i)
    d[i - 1] = VALUE (a[i - 1], b[i - 1], i - 1);
}

void FN
early_exit (unsigned *restrict d, const unsigned *restrict a,
	    const unsigned *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    {
      if ((a[i] & 31) == 0)
	break;
      d[i] = VALUE (a[i], b[i], i);
    }
}

void FN
paired (unsigned *restrict d, const unsigned *restrict a,
	const unsigned *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    {
      d[2 * i] = VALUE (a[2 * i], b[2 * i], i);
      d[2 * i + 1] = VALUE (a[2 * i + 1], b[2 * i + 1], i);
    }
}

unsigned *FN
live_out (unsigned *restrict d, const unsigned *restrict a,
	  const unsigned *restrict b, unsigned n)
{
  for (unsigned i = 0; i < n; ++i, ++d, ++a, ++b)
    *d = VALUE (*a, *b, i);
  return d;
}
#else
void indexed (unsigned *, const unsigned *, const unsigned *, unsigned);
void pointers (unsigned *, const unsigned *, const unsigned *, unsigned);
void alias (unsigned *, const unsigned *, const unsigned *, unsigned);
void offset (unsigned *, const unsigned *, const unsigned *, unsigned);
void strided (unsigned *, const unsigned *, const unsigned *, unsigned);
void reversed (unsigned *, const unsigned *, const unsigned *, unsigned);
void early_exit (unsigned *, const unsigned *, const unsigned *, unsigned);
void paired (unsigned *, const unsigned *, const unsigned *, unsigned);
unsigned *live_out (unsigned *, const unsigned *, const unsigned *, unsigned);
#endif

#ifndef TEST_FUNCTIONS_ONLY
#define SIZE 224
static unsigned a[SIZE] __attribute__ ((aligned (64)));
static unsigned b[SIZE] __attribute__ ((aligned (64)));
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
  void (*const functions[]) (unsigned *, const unsigned *, const unsigned *,
			    unsigned)
    = { indexed, pointers, alias, offset, strided, reversed, early_exit,
	paired };
  for (unsigned n = 0; n <= 97; ++n)
    for (unsigned da = 0; da < 4; ++da)
      for (unsigned aa = 0; aa < 4; ++aa)
	for (unsigned ba = 0; ba < 4; ++ba)
	  {
	    for (unsigned i = 0; i < SIZE; ++i)
	      {
		a[i] = i * 2654435761U + n;
		b[i] = i % 2 ? ~i : i * 1234567U;
	      }
	    for (unsigned k = 0; k < sizeof functions / sizeof functions[0]; ++k)
	      {
		for (unsigned i = 0; i < SIZE; ++i)
		  d[i] = r[i] = 0xa5a5a5a5U;
		for (unsigned i = 0; i < n; ++i)
		  {
		    if (k == 6 && (a[aa + i] & 31) == 0)
		      break;
		    if (k == 7)
		      {
			r[da + 2 * i] = VALUE (a[aa + 2 * i], b[ba + 2 * i], i);
			r[da + 2 * i + 1]
			  = VALUE (a[aa + 2 * i + 1], b[ba + 2 * i + 1], i);
		      }
		    else
		      r[da + i] = VALUE (a[aa + (k == 4 ? 2 * i : i) + (k == 3)],
				  b[ba + i + (k == 3 ? 2 : 0)], i);
		  }
		functions[k] (d + da, a + aa, b + ba, n);
		check ();
	      }
	    for (unsigned i = 0; i < SIZE; ++i)
	      d[i] = r[i] = 0xa5a5a5a5U;
	    for (unsigned i = 0; i < n; ++i)
	      r[da + i] = VALUE (a[aa + i], b[ba + i], i);
	    if (live_out (d + da, a + aa, b + ba, n) != d + da + n)
	      __builtin_abort ();
	    check ();

	    /* Preserve scalar ordering for overlapping alias versions.  */
	    for (unsigned i = 0; i < SIZE; ++i)
	      d[i] = r[i] = a[i];
	    for (unsigned i = 0; i < n; ++i)
	      r[da + i] = VALUE (r[aa + i], r[ba + i], i);
	    alias (d + da, d + aa, d + ba, n);
	    check ();
	  }
  return 0;
}
#endif
