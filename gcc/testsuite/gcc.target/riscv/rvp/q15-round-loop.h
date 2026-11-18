/* Rounded Q15 loops, including equal-width sign changes and live products.  */
#define FN __attribute__ ((noipa))
#define LOOP(NAME, TYPE, EXPR, LIMIT)                                  \
void FN                                                              \
NAME (short *__restrict out, const short *__restrict a,                \
      const short *__restrict b, unsigned int n)                      \
{                                                                    \
  for (unsigned int i = 0; i < n; ++i)                                \
    {                                                                \
      TYPE product = (TYPE) a[i] * b[i];                             \
      TYPE result = (EXPR);                                         \
      out[i] = result > (LIMIT) ? (LIMIT) : result;                    \
    }                                                                \
}

LOOP (q15_round_wide, long long, (product + 16384) >> 15, 32767)
LOOP (q15_round_two_shifts, int, ((product >> 14) + 1) >> 1, 32767)
LOOP (q15_round_wide_two_shifts, long long,
      ((product >> 14) + 1) >> 1, 32767)
LOOP (q15_round_modular, int,
      (int) ((unsigned int) product + 16384) >> 15, 32767)

void FN
q15_round_shared (short *__restrict out, int *__restrict saved,
		  const short *__restrict a, const short *__restrict b,
		  unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      int product = (int) a[i] * b[i];
      int result = ((product >> 14) + 1) >> 1;
      saved[i] = product;
      out[i] = result > 32767 ? 32767 : result;
    }
}

#ifndef Q15_ROUND_POSITIVE_ONLY
LOOP (q15_round_bad_constant, long long, (product + 16383) >> 15, 32767)
LOOP (q15_round_bad_bound, long long, (product + 16384) >> 15, 32766)
LOOP (q15_round_logical, int,
      ((unsigned int) product + 16384) >> 15, 32767)
LOOP (q15_round_inner_logical, int,
      ((int) ((unsigned int) product >> 14) + 1) >> 1, 32767)
LOOP (q15_round_truncated_product, int,
      ((short) product + 16384) >> 15, 32767)
LOOP (q15_round_bad_two_shifts, int, ((product >> 14) + 2) >> 1, 32767)
LOOP (q15_round_truncated_shift, int,
      ((short) (product >> 14) + 1) >> 1, 32767)
#endif
