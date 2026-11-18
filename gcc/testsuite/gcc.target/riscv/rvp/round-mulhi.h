#include <stdint.h>

int32_t __attribute__ ((noipa))
round_s (int32_t a, int32_t b)
{
  return ((int64_t) a * b + INT64_C (2147483648)) >> 32;
}

uint32_t __attribute__ ((noipa))
round_u (uint32_t a, uint32_t b)
{
  return ((uint64_t) a * b + UINT64_C (2147483648)) >> 32;
}

int32_t __attribute__ ((noipa))
round_su (int32_t a, uint32_t b)
{
  return ((int64_t) a * (int64_t) b + INT64_C (2147483648)) >> 32;
}

int32_t __attribute__ ((noipa))
round_us (uint32_t b, int32_t a)
{
  return ((int64_t) b * a + INT64_C (2147483648)) >> 32;
}

int64_t __attribute__ ((noipa))
round_s_wide (int32_t a, int32_t b)
{
  return ((int64_t) a * b + INT64_C (2147483648)) >> 32;
}

uint64_t __attribute__ ((noipa))
round_u_wide (uint32_t a, uint32_t b)
{
  return ((uint64_t) a * b + UINT64_C (2147483648)) >> 32;
}

int64_t __attribute__ ((noipa))
round_su_wide (int32_t a, uint32_t b)
{
  return ((int64_t) a * (int64_t) b + INT64_C (2147483648)) >> 32;
}

void __attribute__ ((noipa))
round_s_loop (int32_t *restrict d, const int32_t *restrict a,
	      const int32_t *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = ((int64_t) a[i] * b[i] + INT64_C (2147483648)) >> 32;
}

void __attribute__ ((noipa))
round_u_loop (uint32_t *restrict d, const uint32_t *restrict a,
	      const uint32_t *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = ((uint64_t) a[i] * b[i] + UINT64_C (2147483648)) >> 32;
}

void __attribute__ ((noipa))
round_su_loop (int32_t *restrict d, const int32_t *restrict a,
	       const uint32_t *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = ((int64_t) a[i] * (int64_t) b[i]
	    + INT64_C (2147483648)) >> 32;
}

void __attribute__ ((noipa))
round_us_loop (int32_t *restrict d, const uint32_t *restrict a,
	       const int32_t *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = ((int64_t) a[i] * b[i] + INT64_C (2147483648)) >> 32;
}
