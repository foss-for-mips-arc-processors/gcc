#include <stdint-gcc.h>

/* The load and store of D use the same initial pointer and the same
   loop-variant step in each of these loops.  */

void __attribute__ ((noipa))
ptr_iv_map_u (uint32_t *d, const uint32_t *a, const uint32_t *b,
	      unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] += (uint32_t) (((uint64_t) a[i] * b[i]) >> 32);
}

void __attribute__ ((noipa))
ptr_iv_add (uint32_t *d, const uint32_t *a, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] += a[i];
}

void __attribute__ ((noipa))
ptr_iv_inplace (uint32_t *d, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = d[i] * 7 + 3;
}

/* Equal steps do not imply that the initial pointers are equal.  */

void __attribute__ ((noipa))
ptr_iv_separate (uint32_t *d, const uint32_t *a, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = a[i] + 3;
}

/* A common base does not make differently displaced pointers equal.  */

void __attribute__ ((noipa))
ptr_iv_offset (uint32_t *d, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = d[i + 1] + 3;
}

/* Equal initial pointers do not imply that the steps are equal.  */

void __attribute__ ((noipa))
ptr_iv_stride (uint32_t *d, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = d[2 * i] + 3;
}

/* Retain the final pointer as well as the memory results.  */

uint32_t * __attribute__ ((noipa))
ptr_iv_liveout (uint32_t *d, const uint32_t *a, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      *d += a[i];
      ++d;
    }
  return d;
}

/* The conditional pointer update need not match a vector pointer IV.  */

uint32_t * __attribute__ ((noipa))
ptr_iv_conditional (uint32_t *d, const uint32_t *a, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      *d += a[i];
      d += a[i] & 1;
    }
  return d;
}

/* Character accesses may alias the word accesses, including in-place.  */

void __attribute__ ((noipa))
ptr_iv_mixed (uint32_t *d, const unsigned char *a, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] += a[4 * i];
}
