/* { dg-do run } */

#include <stdint.h>

#define ATTR __attribute__ ((noipa))
#define TYPES(M) \
  M (uint8_t, byte) \
  M (uint16_t, half) \
  M (uint32_t, word)

#ifndef TEST_DRIVER_ONLY
#define FORWARD(T, N) \
  ATTR void forward_##N (T *restrict d, const T *restrict a, unsigned n) \
  { \
    for (unsigned i = 0; i < n; ++i) \
      d[i] = (a[i] >> 1) + (a[i] & 1); \
  }
TYPES (FORWARD)

ATTR void
alias_word (uint32_t *d, const uint32_t *a, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = (a[i] >> 1) + (a[i] & 1);
}

ATTR void
aligned_alias_half (uint16_t *d, const uint16_t *a, unsigned n)
{
  d = __builtin_assume_aligned (d, 8);
  a = __builtin_assume_aligned (a, 8);
  for (unsigned i = 0; i < n; ++i)
    d[i] = (a[i] >> 1) + (a[i] & 1);
}

ATTR void
reverse_word (uint32_t *restrict d, const uint32_t *restrict a, unsigned n)
{
  for (unsigned i = n; i != 0; --i)
    d[i - 1] = (a[i - 1] >> 1) + (a[i - 1] & 1);
}

ATTR void
stride_half (uint16_t *restrict d, const uint16_t *restrict a, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    d[i] = (a[2 * i + 1] >> 1) + (a[2 * i + 1] & 1);
}

ATTR void
wrap_word (uint32_t *restrict d, const uint32_t *restrict a, unsigned n,
	   unsigned start)
{
  for (unsigned i = start; i != start + n; ++i)
    d[i - start] = (a[i - start] >> 1) + (a[i - start] & 1);
}

ATTR void
tiny_word (uint32_t *restrict d, const uint32_t *restrict a, unsigned char n,
	   unsigned char start)
{
  for (unsigned char i = start; i != (unsigned char) (start + n); ++i)
    {
      unsigned char j = i - start;
      d[j] = (a[j] >> 1) + (a[j] & 1);
    }
}
#else
#define DECLARE(T, N) \
  void forward_##N (T *, const T *, unsigned);
TYPES (DECLARE)
void alias_word (uint32_t *, const uint32_t *, unsigned);
void aligned_alias_half (uint16_t *, const uint16_t *, unsigned);
void reverse_word (uint32_t *, const uint32_t *, unsigned);
void stride_half (uint16_t *, const uint16_t *, unsigned);
void wrap_word (uint32_t *, const uint32_t *, unsigned, unsigned);
void tiny_word (uint32_t *, const uint32_t *, unsigned char, unsigned char);
#endif

#ifndef TEST_FUNCTIONS_ONLY
#define SIZE 288
#define ARRAYS(T, N) \
  static T a_##N[SIZE] __attribute__ ((aligned (64))); \
  static T d_##N[SIZE] __attribute__ ((aligned (64))); \
  static T r_##N[SIZE] __attribute__ ((aligned (64)));
TYPES (ARRAYS)

static uint32_t
input (unsigned i)
{
  static const uint32_t edge[]
    = { 0, 1, 2, 3, 0x7fffffffU, 0x80000000U, 0xfffffffeU, 0xffffffffU };
  return i % 3 ? edge[i % 8] : i * 2654435761U;
}

int __attribute__ ((optimize ("no-tree-vectorize,no-tree-slp-vectorize")))
main (void)
{
  for (unsigned n = 0; n <= 129; ++n)
    for (unsigned da = 0; da < 8; ++da)
      for (unsigned sa = 0; sa < 8; ++sa)
	{
#define CHECK(T, N) \
  for (unsigned i = 0; i < SIZE; ++i) \
    { \
      a_##N[i] = (T) input (i + n); \
      d_##N[i] = r_##N[i] = (T) 0xa5a5a5a5U; \
    } \
  for (unsigned i = 0; i < n; ++i) \
    r_##N[da + i] = ((uint64_t) a_##N[sa + i] + 1) / 2; \
  forward_##N (d_##N + da, a_##N + sa, n); \
  for (unsigned i = 0; i < SIZE; ++i) \
    if (d_##N[i] != r_##N[i]) \
      __builtin_abort ();
	  TYPES (CHECK)
#undef CHECK

	  for (unsigned i = 0; i < SIZE; ++i)
	    d_word[i] = 0xa5a5a5a5U;
	  reverse_word (d_word + da, a_word + sa, n);
	  for (unsigned i = 0; i < SIZE; ++i)
	    if (d_word[i] != r_word[i])
	      __builtin_abort ();
	  for (unsigned i = 0; i < SIZE; ++i)
	    d_word[i] = 0xa5a5a5a5U;
	  wrap_word (d_word + da, a_word + sa, n, ~0U - n / 2);
	  for (unsigned i = 0; i < SIZE; ++i)
	    if (d_word[i] != r_word[i])
	      __builtin_abort ();

	  for (unsigned i = 0; i < SIZE; ++i)
	    d_half[i] = r_half[i] = 0xa5a5;
	  for (unsigned i = 0; i < n; ++i)
	    r_half[da + i] = ((uint32_t) a_half[sa + 2 * i + 1] + 1) / 2;
	  stride_half (d_half + da, a_half + sa, n);
	  for (unsigned i = 0; i < SIZE; ++i)
	    if (d_half[i] != r_half[i])
	      __builtin_abort ();

	  /* Exercise both nonoverlapping and overlapping alias versions.
	     The reference preserves the scalar read-after-write order.  */
	  for (unsigned i = 0; i < SIZE; ++i)
	    d_word[i] = r_word[i] = input (i + n);
	  for (unsigned i = 0; i < n; ++i)
	    r_word[da + i] = ((uint64_t) r_word[sa + i] + 1) / 2;
	  alias_word (d_word + da, d_word + sa, n);
	  for (unsigned i = 0; i < SIZE; ++i)
	    if (d_word[i] != r_word[i])
	      __builtin_abort ();

	  /* The alignment promise must also hold on the scalar path.  */
	  if ((da | sa) % 4 == 0)
	    {
	      for (unsigned i = 0; i < SIZE; ++i)
		d_half[i] = r_half[i] = (uint16_t) input (i + n);
	      for (unsigned i = 0; i < n; ++i)
		r_half[da + i] = ((uint32_t) r_half[sa + i] + 1) / 2;
	      aligned_alias_half (d_half + da, d_half + sa, n);
	      for (unsigned i = 0; i < SIZE; ++i)
		if (d_half[i] != r_half[i])
		  __builtin_abort ();
	    }
        }
  for (unsigned n = 0; n <= 255; ++n)
    for (unsigned off = 0; off < 8; ++off)
      {
	for (unsigned i = 0; i < SIZE; ++i)
	  {
	    a_word[i] = input (i + n);
	    d_word[i] = r_word[i] = 0xa5a5a5a5U;
	  }
	for (unsigned i = 0; i < n; ++i)
	  r_word[off + i] = ((uint64_t) a_word[off + i] + 1) / 2;
	tiny_word (d_word + off, a_word + off, n, 255 - n / 2);
	for (unsigned i = 0; i < SIZE; ++i)
	  if (d_word[i] != r_word[i])
	    __builtin_abort ();
      }
  return 0;
}
#endif
