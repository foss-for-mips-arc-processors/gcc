/* { dg-do run } */
/* { dg-additional-options "--param=vect-epilogues-nomask=0" } */

/* Check constant offsets in the scalar tail, including offsets carried by
   MEM_REF, negative displacements and scalar-only entry.  */

typedef __INT32_TYPE__ i32;
typedef __SIZE_TYPE__ index_type;
typedef __PTRDIFF_TYPE__ offset_type;
#define FN __attribute__ ((noipa))
#define Q31(A, B) \
  ({ long long t = ((long long) (A) * (B)) >> 31; \
     t > 2147483647 ? 2147483647 : t; })

#ifndef TEST_DRIVER_ONLY
void FN
q31_offset (i32 *restrict d, const i32 *restrict a,
	    const i32 *restrict b, unsigned n)
{
  for (index_type i = 0; i < n; ++i)
    d[i + 3] = Q31 (a[i + 1], b[i + 2]);
}

void FN
q31_negative (i32 *restrict d, const i32 *restrict a,
	      const i32 *restrict b, unsigned n)
{
  for (index_type i = 0; i < n; ++i)
    d[i] = Q31 (a[(offset_type) i - 1], b[(offset_type) i - 2]);
}

void FN
q31_shifted (i32 *restrict d, const i32 *restrict a,
	     const i32 *restrict b, unsigned n)
{
  d += 3;
  a += 1;
  b += 2;
  for (index_type i = 0; i < n; ++i)
    d[i] = Q31 (a[i], b[i]);
}

void FN
q31_aligned_offset (i32 *restrict d, const i32 *restrict a,
		    const i32 *restrict b, unsigned n)
{
  d = __builtin_assume_aligned (d, 8);
  a = __builtin_assume_aligned (a, 8);
  b = __builtin_assume_aligned (b, 8);
  for (index_type i = 0; i < n; ++i)
    d[i + 6] = Q31 (a[i + 2], b[i + 4]);
}

void FN
q31_aligned_negative (i32 *restrict d, const i32 *restrict a,
		      const i32 *restrict b, unsigned n)
{
  d = __builtin_assume_aligned (d, 8);
  a = __builtin_assume_aligned (a, 8);
  b = __builtin_assume_aligned (b, 8);
  for (index_type i = 0; i < n; ++i)
    d[i] = Q31 (a[(offset_type) i - 2], b[(offset_type) i - 4]);
}
#else
void q31_offset (i32 *, const i32 *, const i32 *, unsigned);
void q31_negative (i32 *, const i32 *, const i32 *, unsigned);
void q31_shifted (i32 *, const i32 *, const i32 *, unsigned);
void q31_aligned_offset (i32 *, const i32 *, const i32 *, unsigned);
void q31_aligned_negative (i32 *, const i32 *, const i32 *, unsigned);
#endif

#ifndef TEST_FUNCTIONS_ONLY
#define SIZE 288
static i32 a[SIZE] __attribute__ ((aligned (64)));
static i32 b[SIZE] __attribute__ ((aligned (64)));
static i32 d[SIZE] __attribute__ ((aligned (64)));
static i32 r[SIZE] __attribute__ ((aligned (64)));

static i32 __attribute__ ((noipa, optimize ("O0")))
reference (i32 x, i32 y)
{
  long long t = (long long) x * y;
  t >>= 31;
  if (t > 2147483647)
    t = 2147483647;
  return t;
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  static const unsigned sizes[]
    = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
	31, 32, 63, 64, 127, 128, 129, 255, 256 };
  static const i32 edges[]
    = { (-2147483647 - 1), 2147483647, 0, 1, -1, 65536, -65536, 1073741824 };
  void (*const functions[]) (i32 *, const i32 *, const i32 *, unsigned)
    = { q31_offset, q31_negative, q31_shifted, q31_aligned_offset,
	q31_aligned_negative };
  const int ad[] = { 1, -1, 1, 2, -2 };
  const int bd[] = { 2, -2, 2, 4, -4 };
  const unsigned dd[] = { 3, 0, 3, 6, 0 };
#ifdef TRACE_RUN
  const unsigned patterns = 2, offsets = 2, aliases = 1;
#else
  const unsigned patterns = 8, offsets = 4, aliases = 2;
#endif
  for (unsigned k = 0; k < 5; ++k)
    for (unsigned p = 0; p < patterns; ++p)
      for (unsigned ao = 0; ao < offsets; ++ao)
	for (unsigned bo = 0; bo < offsets; ++bo)
	  for (unsigned alias = 0; alias < aliases; ++alias)
	    for (unsigned s = 0; s < sizeof sizes / sizeof sizes[0]; ++s)
	      {
		unsigned n = sizes[s];
		unsigned scale = k >= 3 ? 2 : 1;
		i32 *dp = d + 8 + scale * ((ao + bo) & 3);
		const i32 *ap = a + 8 + scale * ao;
		const i32 *bp = (alias ? a : b) + 8 + scale * bo;
		for (unsigned i = 0; i < SIZE; ++i)
		  {
		    a[i] = p < 4 ? edges[(i + p) & 7]
				 : (i32) (i * 2654435761U + p * 1234567U);
		    b[i] = p < 4 ? edges[(3 * i + p) & 7]
				 : (i32) (~i * 1234567U + p);
		    d[i] = r[i] = 0x5a5a5a5a;
		  }
		for (unsigned i = 0; i < n; ++i)
		  r[dp - d + i + dd[k]]
		    = reference (ap[(offset_type) i + ad[k]],
				 bp[(offset_type) i + bd[k]]);
		functions[k] (dp, ap, bp, n);
		for (unsigned i = 0; i < SIZE; ++i)
		  if (d[i] != r[i])
		    __builtin_abort ();
	      }
  return 0;
}
#endif
