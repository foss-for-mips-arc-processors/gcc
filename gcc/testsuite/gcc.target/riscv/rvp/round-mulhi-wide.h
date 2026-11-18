#include <stdint.h>

void __attribute__ ((noipa))
round_s_wide_loop (int64_t *restrict d, const int32_t *restrict a,
		   const int32_t *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = ((int64_t) a[i] * b[i] + INT64_C (2147483648)) >> 32;
}

void __attribute__ ((noipa))
round_u_wide_loop (uint64_t *restrict d, const uint32_t *restrict a,
		   const uint32_t *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = ((uint64_t) a[i] * b[i] + UINT64_C (2147483648)) >> 32;
}

void __attribute__ ((noipa))
round_su_wide_loop (int64_t *restrict d, const int32_t *restrict a,
		    const uint32_t *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = ((int64_t) a[i] * (int64_t) b[i]
	    + INT64_C (2147483648)) >> 32;
}

void __attribute__ ((noipa))
round_full_loop (uint64_t *restrict d, const uint32_t *restrict a,
		 const uint32_t *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = (uint64_t) a[i] * b[i] + UINT64_C (2147483648);
}

void __attribute__ ((noipa))
round_unknown_loop (uint64_t *restrict d, const uint64_t *restrict a,
		    const uint64_t *restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = (a[i] * b[i] + UINT64_C (2147483648)) >> 32;
}
